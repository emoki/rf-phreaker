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

class power_spectrum_processing_and_output_body
{
public:
	power_spectrum_processing_and_output_body(data_output_async *io)
		: io_(io)
		, filters_(1, 513)
	{}

	power_spectrum_processing_and_output_body(const power_spectrum_processing_and_output_body &body)
		: io_(body.io_)
		, filters_(1, 513)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}

	tbb::flow::continue_msg operator()(power_spectrum_package package)
	{
		auto &meas = *package.measurement_info_.get();
		auto &params = package.params_;
		auto sig_length = params.num_windows_ * params.window_length_;
		helper_.remove_futures();

		std::string no_filter;
		auto &filter = filters_.get_filter(meas.sampling_rate(), meas.sampling_rate(), ((params.span_) / meas.sampling_rate()) * .5);

		if(buffer_.length() < sig_length) {
			buffer_.reset(filter.ensure_output_samples_large_enough(sig_length));
		}
		buffer_.zero_out();
		int output_length = 0;
		filter.filter(meas.get_iq().get(), sig_length, buffer_.get(), buffer_.length(), output_length);

		if(output_length < sig_length) {
			params.num_windows_ = output_length / params.window_length_;
			sig_length = output_length;
		}

		// For debug output.
		if(0) {
			buffer_.copy(meas.get_iq().get(), sig_length);
		}

		calculator_.calculate_power_spectrum(buffer_, params.window_length_, sig_length);

		power_spectrum_data power_spec = convert_to_power_spectrum_data(meas, calculator_.power_spectra(), params);

		// For debug output
		if(0) {
			no_filter = "no_filter_";
			static int i = 0;
			std::ofstream f1(std::string("power_spectrum_matlab_" + no_filter + std::to_string(i) + ".txt"));
			f1 << meas << std::endl;
			auto tmp_spec_no_data = convert_to_power_spectrum_data(meas, ipp_32f_array(params.window_length_), params);
			std::ofstream f2(std::string("power_specs_" + no_filter + std::to_string(i) + ".txt"));
			f2 << "samp_rate:\t" << meas.sampling_rate() << "\tnorm_cutoff_freq:\t" << ((params.span_) / meas.sampling_rate() * .5)
				<< "\tcutoff_freq:\t" << (params.span_ / 2) << std::endl;
			f2 << tmp_spec_no_data << std::endl;
			calculator_.power_spectra().output_matlab_compatible_array(std::string("power_spectrum_" + no_filter + std::to_string(i) + ".txt"));
			++i;
		}

		helper_.track_future(io_->output(std::move(power_spec)));

		return tbb::flow::continue_msg();
	}

private:
	data_output_async *io_;

	processing_and_feedback_helper helper_;

	power_spectrum_calculator calculator_;

	filters filters_;

	ipp_32fc_array buffer_;
};

}}
