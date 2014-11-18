#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
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
		remove_completed_output();

		// Output basic tech.
		past_output_.push_back(io_->output(convert_to_basic_data(*info.meas_, info.avg_rms_), std::vector<umts_data>()));

		if(info.processed_data_.size()) {
			// Add the freq to the layer_3_decoder.
			std::get<0>(out).try_put(add_collection_info(umts_layer_3_collection_info(info.meas_->frequency(), info.meas_->get_operating_band()), UMTS_LAYER_3_DECODE));
		}
		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	void remove_completed_output() {
		int num_completed = 0;
		for(auto &fut : past_output_) {
			if(fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
				++num_completed;
			else
				break;
		}
		past_output_.erase(std::begin(past_output_), std::begin(past_output_) + num_completed);
	}

	data_output_async *io_;

	std::vector<std::future<void>> past_output_;
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
		remove_completed_output();

		// Add the freq to the layer_3_decoder.
		if(info.remove_) {
			std::get<0>(out).try_put(remove_collection_info(umts_layer_3_collection_info(info.meas_->frequency(), info.meas_->get_operating_band()), UMTS_LAYER_3_DECODE));
		}

		std::vector<umts_data> umts;

		if(!info.processed_data_.empty()) {

			for(const auto &dat : info.processed_data_)
				umts.push_back(convert_to_umts_data(*info.meas_, dat));
		}
		past_output_.push_back(io_->output(std::move(umts), convert_to_basic_data(*info.meas_, info.avg_rms_)));

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	void remove_completed_output() {
		int num_completed = 0;
		for(auto &fut : past_output_) {
			if(fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
				++num_completed;
			else
				break;
		}
		past_output_.erase(std::begin(past_output_), std::begin(past_output_) + num_completed);
	}

	data_output_async *io_;

	std::vector<std::future<void>> past_output_;
};

}}
