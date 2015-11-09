#pragma once
#include <tuple>
#include "tbb/flow_graph.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
#include "rf_phreaker/processing/processing_utility.h"
#include "rf_phreaker/processing/processing_and_feedback_helper.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/lte_analysis/lte_types.h"
#include "rf_phreaker/common/delegate_sink.h"

namespace rf_phreaker { namespace processing {

class lte_sweep_output_and_feedback_body
{
public:
	lte_sweep_output_and_feedback_body(data_output_async *io)
		: io_(io)
		{}

	lte_sweep_output_and_feedback_body(const lte_sweep_output_and_feedback_body &body)
		: io_(body.io_)
		, tracker_(body.tracker_)
		, freqs_currently_added_(body.freqs_currently_added_)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	void operator()(lte_info info, lte_output_and_feedback_node::output_ports_type &out)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		if(helper_.has_sweep_restarted(meas)) {
			tracker_.clear();
		}

		helper_.remove_futures();

		//output_debug_info(info);

		// Output basic tech.
		helper_.track_future(io_->output(convert_to_basic_data(meas, info.power_info_group_[0].avg_rms_), std::vector<lte_data>()));

		if(info.processed_data_.size()) {
			tracker_.update_measurements(info.processed_data_, meas.frequency());

			if(!tracker_.is_within_stronger_measurement_bandwidth(meas.frequency())) {
				auto bw = look_for_valid_bandwidth(info.processed_data_);

				// Configure packet info and send it to collection manager.
				auto collection_sampling_rate = determine_sampling_rate(bw);
				if(collection_sampling_rate == 0)
					collection_sampling_rate = lte_layer_3_collection_info::sampling_rate__;

				auto collection_bw = determine_bandwidth_for_collection(bw);
				if(collection_bw == 0)
					collection_bw = lte_layer_3_collection_info::bandwidth__;

				auto packet = lte_layer_3_collection_info(meas.frequency(), collection_sampling_rate,
					collection_bw, meas.get_lte_band(), true);

				std::get<0>(out).try_put(add_collection_info(packet));

				// Add packet info to our freqs_currently_added_.
				freqs_currently_added_.push_back(packet);
			}

			clean_up_measurements(out);
		}
		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	void output_debug_info(const lte_info &info)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		static std::ofstream file("debug_lte_sweep_" + std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + ".txt");
		static bool write_header = true;
		if(write_header) {
			write_header = false;
			file << "freq\tcollection_round\t";
			output_lte_meas_debug_header(file) << "\n";
		}
		for(auto &lte : info.processed_data_)
			file << meas.frequency() << "\t" << meas.collection_round() << "\t" << lte << std::endl;
	}

	void clean_up_measurements(lte_output_and_feedback_node::output_ports_type &out)
	{
		std::vector<lte_layer_3_collection_info> new_list;
		add_remove_collection_info to_remove;
		for(auto info : freqs_currently_added_) {
			if(tracker_.is_within_stronger_measurement_bandwidth(info.freq_)) {
				to_remove.remove_.push_back(info);
			}
			else
				new_list.push_back(info);
		}
		if(to_remove.remove_.size()) {
			std::get<0>(out).try_put(to_remove);
			freqs_currently_added_.swap(new_list);
		}
	}
	

	data_output_async *io_;

	lte_measurement_tracker tracker_;

	std::vector<lte_layer_3_collection_info> freqs_currently_added_;

	processing_and_feedback_helper helper_;
};

class lte_layer_3_output_and_feedback_body
{
public:
	lte_layer_3_output_and_feedback_body(data_output_async *io, int minimum_collection_round)
		: io_(io)
		, minimum_collection_round_(minimum_collection_round)
		, pbchs_decoded_minimum_collection_round_(3 * minimum_collection_round)
	{}

	lte_layer_3_output_and_feedback_body(const lte_layer_3_output_and_feedback_body &body)
		: io_(body.io_)
		, minimum_collection_round_(body.minimum_collection_round_)
		, pbchs_decoded_minimum_collection_round_(body.pbchs_decoded_minimum_collection_round_)
		, tracker_(body.tracker_)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	void operator()(lte_info info, lte_output_and_feedback_node::output_ports_type &out)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		if(helper_.has_layer_3_restarted(meas)) {
			tracker_.clear();
		}

		helper_.remove_futures();

		// Remove freq if indicated.
		if(do_we_remove_collection_info(info)) {
			std::get<0>(out).try_put(remove_collection_info(lte_layer_3_collection_info(meas.frequency(), meas.sampling_rate(),
				meas.bandwidth(), meas.get_lte_band(), info.measurement_package_.can_remove_)));
		}
		
		std::vector<lte_data> lte_group;

		if(!info.processed_data_.empty()) {
			//output_debug_info(info);

			auto decoded_bw = tracker_.find_decoded_bandwidth(meas.frequency());
			// Until we get the LTE dll sorted out only output measurements with known bandwidths that match what we think to be the correct bandwidth.
			// Also only output them after we have decoded two pbchs on that channel.  Lowers the likeihood of outputting a false pbch.
			if(tracker_.is_considered_valid_channel(meas.frequency()) || tracker_.has_decoded_layer_3(info.processed_data_)) {
				for(auto &data : info.processed_data_) {
					if(data.NumAntennaPorts != LteAntPorts_Unknown && (tracker_.has_decoded_layer_3(data) || data.Bandwidth == decoded_bw)) {
						auto tmp = convert_to_lte_data(meas, data, info.power_info_group_[0].avg_rms_);
						lte_group.push_back(std::move(tmp));
					}
				}
			}

			tracker_.update_measurements(info.processed_data_, meas.frequency());
			
			if(lte_group.size()) {
				// Look up bandwidth to see if it's changed after the update.
				decoded_bw = tracker_.find_decoded_bandwidth(meas.frequency());

				if(decoded_bw != LteBandwidth_Unknown) {
					auto sampling_rate = determine_sampling_rate(decoded_bw);

					if(sampling_rate != 0 && sampling_rate != meas.sampling_rate()) {
						add_remove_collection_info params;

						params.remove_.push_back(lte_layer_3_collection_info(meas.frequency(), meas.sampling_rate(),
							meas.bandwidth(), meas.get_lte_band()));

						params.add_.push_back(lte_layer_3_collection_info(meas.frequency(), sampling_rate, determine_bandwidth_for_collection(decoded_bw),
							meas.get_lte_band(), info.measurement_package_.can_remove_));

						std::get<0>(out).try_put(params);
					}
				}
			}
		}
		helper_.track_future(io_->output(std::move(lte_group), convert_to_basic_data(meas, info.power_info_group_[0].avg_rms_)));

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	void output_debug_info(const lte_info &info)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		static std::ofstream file("debug_lte_layer_3" + std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + ".txt");
		static bool write_header = true;
		if(write_header) {
			write_header = false;
			file << "freq\tcollection_round\t";
			output_lte_meas_debug_header(file) << "\n";
		}
		for(auto &lte : info.processed_data_)
			file << meas.frequency() << "\t" << meas.collection_round() << "\t" << lte << std::endl;
	}

	bool do_we_remove_collection_info(lte_info info)
	{
		const auto freq = info.measurement_package_.measurement_info_->frequency();
		const auto cr = info.measurement_package_.measurement_info_->collection_round();
		return info.remove_ ||
			(cr > minimum_collection_round_ && (!tracker_.is_tracking(freq) || tracker_.is_within_stronger_measurement_bandwidth(freq)) ||
			!tracker_.is_considered_valid_channel(freq) && cr > pbchs_decoded_minimum_collection_round_);
	}

	data_output_async *io_;

	int minimum_collection_round_;

	int pbchs_decoded_minimum_collection_round_;

	lte_measurement_tracker tracker_;

	processing_and_feedback_helper helper_;
};

}}
