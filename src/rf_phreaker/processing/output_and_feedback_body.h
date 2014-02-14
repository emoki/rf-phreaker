#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/measurement_output_async.h"
#include "rf_phreaker/processing/measurement_wrappers.h"
#include "rf_phreaker/common/common_utility.h"
#include "tbb/flow_graph.h"
#include <tuple>

namespace rf_phreaker { namespace processing {

class sweep_output_and_feedback_body
{
public:
	sweep_output_and_feedback_body(measurement_output_async *io)
		: io_(io)
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out)
	{
		// Output basic tech.
		basic_data_wrap data(*info.meas_);
		data.internal_.carrier_signal_level_ = info.avg_rms_;
		io_->output(data.internal_);

		if(info.processed_data_.size())
		{
			// Convert measurements here.
			// For now just output raw meas.
			io_->output(info.processed_data_);

			// Remove from sweeper surrounding freqs that are within the bandwidth of this valid signal.
			//for(int i = info.)
			//std::get<0>(out).try_put(remove_collection_info(umts_sweep_collection_info(info.meas_.frequency()), umts_sweep));

			// Add the freq to the layer_3_decoder.
			std::get<1>(out).try_put(add_collection_info(umts_layer_3_collection_info(info.meas_->frequency()), umts_layer_3_decode));
		}
		//std::get<0>(out).try_put(add_remove_collection_info());
	}

private:
	measurement_output_async *io_;
};

class layer_3_output_and_feedback_body
{
public:
	layer_3_output_and_feedback_body(measurement_output_async *io)
		: io_(io)
	{}

	void operator()(umts_info info, umts_output_and_feedback_node::output_ports_type &out)
	{
		if(!info.processed_data_.empty()) {
			// Convert measurements here.
			// For now just output raw meas.
			io_->output(info.processed_data_);

			// Add the freq to the layer_3_decoder.
			if(info.remove_)
				std::get<1>(out).try_put(remove_collection_info(umts_layer_3_collection_info(info.meas_->frequency()), umts_layer_3_decode));
		}
	}

private:
	measurement_output_async *io_;
};

}}
