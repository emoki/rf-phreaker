#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
#include "rf_phreaker/processing/processing_and_feedback_helper.h"
#include "rf_phreaker/common/common_utility.h"
#include "tbb/flow_graph.h"
#include <tuple>

namespace rf_phreaker { namespace processing {

class umts_sweep_output_and_feedback_body
{
public:
	umts_sweep_output_and_feedback_body(data_output_async *io)
		: io_(io) {}

	umts_sweep_output_and_feedback_body(const umts_sweep_output_and_feedback_body &body)
		: io_(body.io_) 
		, helper_(body.helper_)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		helper_.remove_futures();

		// Output basic tech.
		for(auto &i : info.power_info_group_)
			helper_.track_future(io_->output(convert_to_basic_data(meas, i), std::vector<umts_data>()));

		if(info.processed_data_.size()) {
			std::get<0>(out).try_put(add_collection_info(umts_layer_3_collection_info(meas.frequency(), meas.get_umts_band(), true)));
		}
		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

protected:
	data_output_async *io_;

	processing_and_feedback_helper helper_;
};

class umts_sweep_if_output_and_feedback_body : public umts_sweep_output_and_feedback_body
{
public:
	umts_sweep_if_output_and_feedback_body(data_output_async *io)
		: umts_sweep_output_and_feedback_body(io) {}

	umts_sweep_if_output_and_feedback_body(const umts_sweep_if_output_and_feedback_body &body)
		: umts_sweep_output_and_feedback_body(body)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out) {
		auto meas = *info.measurement_package_.measurement_info_.get();
		helper_.remove_futures();

		// Output basic tech.
		for(auto &i : info.power_info_group_)
			helper_.track_future(io_->output(convert_to_basic_data(meas, i), std::vector<umts_data>()));

		if(info.processed_data_.size()) {
			std::set<frequency_type> freqs;
			for(const auto i : info.processed_data_) {
				freqs.insert(meas.frequency() + i.intermediate_frequency_);
			}
			for(const auto &i : freqs) {
				std::get<0>(out).try_put(add_collection_info(umts_layer_3_collection_info(i, meas.get_umts_band(), true)));
			}
		}
		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}
};

class umts_layer_3_output_and_feedback_body
{
public:
	umts_layer_3_output_and_feedback_body(data_output_async *io)
		: io_(io) {}

	umts_layer_3_output_and_feedback_body(const umts_layer_3_output_and_feedback_body &body)
		: io_(body.io_)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		helper_.remove_futures();

		if(info.remove_ && info.measurement_package_.can_remove_) {
			std::get<0>(out).try_put(remove_collection_info(umts_layer_3_collection_info(meas.frequency(), meas.get_umts_band(), info.measurement_package_.can_remove_)));
		}

		std::vector<umts_data> umts_group;

		if(!info.processed_data_.empty()) {
			for(const auto &dat : info.processed_data_)
				umts_group.push_back(convert_to_umts_data(meas, dat));
		}
		helper_.track_future(io_->output(std::move(umts_group), convert_to_basic_data(meas, info.power_info_group_[0].avg_rms_)));

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	data_output_async *io_;

	processing_and_feedback_helper helper_;
};

}}
