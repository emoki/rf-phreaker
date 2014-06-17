#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
#include "rf_phreaker/processing/processing_utility.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/lte_analysis/lte_types.h"
#include "tbb/flow_graph.h"
#include <tuple>

namespace rf_phreaker { namespace processing {

class lte_sweep_output_and_feedback_body
{
public:
	lte_sweep_output_and_feedback_body(data_output_async *io)
		: io_(io)
		, confidence_threshold_(-10.5)
		, current_collection_round_(-1)
	{}

	void operator()(lte_info info, lte_output_and_feedback_node::output_ports_type &out)
	{
		if(info.meas_->collection_round() == 0 && current_collection_round_ != 0) {
			tracker_.clear();
		}
		current_collection_round_ = info.meas_->collection_round();

		//output_debug_info(info);

		// Output basic tech.
		io_->output_lte_sweep(convert_to_basic_data(*info.meas_, info.avg_rms_))/*.get()*/;

		bool valid_lte = false;
		for(auto &lte : info.processed_data_) {
			if(lte.sync_quality > confidence_threshold_) {
				valid_lte = true;
				break;
			}
		}
		if(valid_lte) {
			tracker_.update_measurements(info.processed_data_, info.meas_->frequency());

			if(!tracker_.is_within_stronger_measurement_bandwidth(info.meas_->frequency())) {
				auto bw = look_for_valid_bandwidth(info.processed_data_);

				// Configure packet info and send it to collection manager.
				auto collection_sampling_rate = determine_sampling_rate(bw);
				if(collection_sampling_rate == 0)
					collection_sampling_rate = lte_layer_3_collection_info::sampling_rate__;

				auto collection_bw = determine_bandwidth_for_collection(bw);
				if(collection_bw == 0)
					collection_bw = lte_layer_3_collection_info::bandwidth__;

				auto packet = lte_layer_3_collection_info(info.meas_->frequency(), collection_sampling_rate,
					collection_bw, info.meas_->get_operating_band());

				std::get<0>(out).try_put(add_collection_info(packet, LTE_LAYER_3_DECODE));

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
		static std::ofstream file("debug_lte_sweep.txt");
		static bool write_header = true;
		if(write_header) {
			write_header = false;
			file << "freq" << "\t" << "cr" << "\t";
			output_lte_meas_debug_header(file);
		}
		for(auto &lte : info.processed_data_)
			file << info.meas_->frequency() << "\t" << info.meas_->collection_round() << "\t" << lte << std::endl;
	}

	void clean_up_measurements(lte_output_and_feedback_node::output_ports_type &out)
	{
		std::vector<lte_layer_3_collection_info> new_list;
		add_remove_collection_info to_remove;
		to_remove.tech_ = LTE_LAYER_3_DECODE;
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

	double confidence_threshold_;

	int64_t current_collection_round_;

	lte_measurement_tracker tracker_;

	std::vector<lte_layer_3_collection_info> freqs_currently_added_;
};

class lte_layer_3_output_and_feedback_body
{
public:
	lte_layer_3_output_and_feedback_body(data_output_async *io, int minimum_collection_round)
		: io_(io)
		, minimum_collection_round_(minimum_collection_round)
		, current_collection_round_(-1)
	{}

	void operator()(lte_info info, lte_output_and_feedback_node::output_ports_type &out)
	{
		if(info.meas_->collection_round() == 0 && current_collection_round_ != 0) {
			tracker_.clear();
		}
		current_collection_round_ = info.meas_->collection_round();

		// Remove freq if indicated.
		if(do_we_remove_collection_info(info)) {
			std::get<0>(out).try_put(remove_collection_info(lte_layer_3_collection_info(info.meas_->frequency(), info.meas_->sampling_rate(),
				info.meas_->bandwidth(), info.meas_->get_operating_band()), LTE_LAYER_3_DECODE));
		}
		
		if(!info.processed_data_.empty()) {
			//output_debug_info(info);

			std::vector<lte_data> lte;

			auto decoded_bw = tracker_.find_decoded_bandwidth(info.meas_->frequency());
				
			// Until we get the LTE dll sorted out only output measurements with known bandwidths.
			for(auto &data : info.processed_data_) {
				if(data.NumAntennaPorts != LteAntPorts_Unknown && (decoded_bw == LteBandwidth_Unknown || data.Bandwidth == decoded_bw)) {
					auto tmp = convert_to_lte_data(*info.meas_, data, info.avg_rms_);
					lte.push_back(std::move(tmp));
				}
			}
			if(lte.size()) {
				tracker_.update_measurements(info.processed_data_, info.meas_->frequency());
			
				io_->output(lte)/*.get()*/;

				if(decoded_bw != LteBandwidth_Unknown) {
					auto sampling_rate = determine_sampling_rate(decoded_bw);

					if(sampling_rate != 0 && sampling_rate != info.meas_->sampling_rate()) {
						add_remove_collection_info params;
						params.tech_ = LTE_LAYER_3_DECODE;

						params.remove_.push_back(lte_layer_3_collection_info(info.meas_->frequency(), info.meas_->sampling_rate(),
							info.meas_->bandwidth(), info.meas_->get_operating_band()));

						params.add_.push_back(lte_layer_3_collection_info(info.meas_->frequency(), sampling_rate, determine_bandwidth_for_collection(decoded_bw),
							info.meas_->get_operating_band()));

						std::get<0>(out).try_put(params);
					}
				}
			}
		}

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	void output_debug_info(const lte_info &info)
	{
		static std::ofstream file("debug_lte_layer_3.txt");
		static bool write_header = true;
		if(write_header) {
			write_header = false;
			file << "freq" << "\t" << "cr" << "\t";
			output_lte_meas_debug_header(file);
		}
		for(auto &lte : info.processed_data_)
			file << info.meas_->frequency() << "\t" << info.meas_->collection_round() << "\t" << lte << std::endl;
	}

	bool do_we_remove_collection_info(lte_info info)
	{
		const auto freq = info.meas_->frequency();
		return info.remove_ ||
			(info.meas_->collection_round() > minimum_collection_round_ &&
			(!tracker_.is_tracking(freq) || tracker_.is_within_stronger_measurement_bandwidth(freq)));
	}

	data_output_async *io_;

	int minimum_collection_round_;

	int64_t current_collection_round_;

	lte_measurement_tracker tracker_;
};

}}
