#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
#include "rf_phreaker/common/common_utility.h"
#include "tbb/flow_graph.h"
#include <tuple>

namespace rf_phreaker { namespace processing {

class sweep_output_and_feedback_body
{
public:
	sweep_output_and_feedback_body(data_output_async *io)
		: io_(io)
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out)
	{
		// Output basic tech.
		io_->output_umts_sweep(convert_to_basic_data(*info.meas_, info.avg_rms_)).get();

		if(info.processed_data_.size())
		{
			// Convert measurements here.
			// For now just output raw meas.
			//io_->output(info.processed_data_);

			// Remove from sweeper surrounding freqs that are within the bandwidth of this valid signal.
			//for(int i = info.)
			//std::get<0>(out).try_put(remove_collection_info(umts_sweep_collection_info(info.meas_.frequency()), UMTS_SWEEP));

			// Add the freq to the layer_3_decoder.
			std::get<0>(out).try_put(add_collection_info(umts_layer_3_collection_info(info.meas_->frequency(), info.meas_->get_operating_band()), UMTS_LAYER_3_DECODE));
		}
	
		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	data_output_async *io_;
};

class layer_3_output_and_feedback_body
{
public:
	layer_3_output_and_feedback_body(data_output_async *io)
		: io_(io)
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out)
	{
		if(!info.processed_data_.empty()) {
			std::vector<umts_data> umts;
			
			for(const auto &dat : info.processed_data_)
				umts.push_back(convert_to_umts_data(*info.meas_, dat));

			io_->output(umts).get();

			// Add the freq to the layer_3_decoder.
			if(info.remove_)
				std::get<0>(out).try_put(remove_collection_info(umts_layer_3_collection_info(info.meas_->frequency(), info.meas_->get_operating_band()), UMTS_LAYER_3_DECODE));
		}

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	data_output_async *io_;
};

}}
