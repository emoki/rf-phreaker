#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
#include "rf_phreaker/processing/processing_and_feedback_helper.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/power_spectrum_calculator.h"
#include "rf_phreaker/common/filters.h"
#include "tbb/flow_graph.h"
#include <tuple>

namespace rf_phreaker { namespace processing {

class iq_data_output_body
{
public:
	iq_data_output_body(data_output_async *io)
		: io_(io) {}

	iq_data_output_body(const iq_data_output_body &body)
		: io_(body.io_)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	tbb::flow::continue_msg operator()(measurement_package package) {
		auto &meas = *package.measurement_info_.get();

		helper_.remove_futures();

		auto iq = convert_to_iq_data(meas);

		helper_.track_future(io_->output(std::move(iq)));

		return tbb::flow::continue_msg();
	}

private:
	data_output_async *io_;

	processing_and_feedback_helper helper_;
};

}}
