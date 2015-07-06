#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
#include "rf_phreaker/processing/output_and_feedback_helper.h"
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
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out)
	{
		helper_.remove_futures();

		// Output basic tech.
		helper_.track_future(io_->output(convert_to_basic_data(*info.meas_, info.power_info_group_[0].avg_rms_), std::vector<umts_data>()));

		if(info.processed_data_.size()) {
			// Add the freq to the layer_3_decoder.
			std::get<0>(out).try_put(add_collection_info(umts_layer_3_collection_info(info.meas_->frequency(), info.meas_->get_operating_band()), UMTS_LAYER_3_DECODE));
		}
		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	data_output_async *io_;

	output_and_feedback_helper<void> helper_;
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
		helper_.remove_futures();

		// Add the freq to the layer_3_decoder.
		if(info.remove_) {
			std::get<0>(out).try_put(remove_collection_info(umts_layer_3_collection_info(info.meas_->frequency(), info.meas_->get_operating_band()), UMTS_LAYER_3_DECODE));
		}

		std::vector<umts_data> umts_group;

		if(!info.processed_data_.empty()) {
			for(const auto &dat : info.processed_data_)
				umts_group.push_back(convert_to_umts_data(*info.meas_, dat));
		}
		helper_.track_future(io_->output(std::move(umts_group), convert_to_basic_data(*info.meas_, info.power_info_group_[0].avg_rms_)));

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	data_output_async *io_;

	output_and_feedback_helper<void> helper_;
};

}}
