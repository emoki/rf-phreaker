#pragma once

#ifdef FIR_FILTER_EXPORTS
#define FIR_FILTER_API __declspec(dllexport)
#else
#define FIR_FILTER_API __declspec(dllimport)
#endif

#include "rf_phreaker/ipp_custom/ipp.h"


namespace rf_phreaker {

class fir_filter_impl;

class FIR_FILTER_API fir_filter {
public:
	fir_filter();

	fir_filter(int up_factor, int down_factor);

	~fir_filter();

	int length() const;

	int num_samples_delay() const;

	void set_up_down_factor(int up_factor, int down_factor);

	void set_zero_delay(bool zero_delay);

	int set_taps(double norm_freq, int length, const double norm_factor = 1.0);

	int set_taps(const Ipp32fc *taps, int length);

	int set_taps(const double *taps, int length);

	int filter(Ipp32fc *in, int numIters) const;

	int filter(const Ipp32fc *in, Ipp32fc *out, int num_iters) const;

	int filter(const Ipp32fc *in, int num_input_samples_to_filter,
		Ipp32fc *out, int num_samples_output_buffer_capacity,
		int& num_output_filtered_samples) const;

	int num_input_samples_required(int num_output_samples_desired) const;

	int num_output_samples_required(int num_input_samples_desired) const;

	int num_iterations_required(int num_input_samples_desired) const;

private:
	fir_filter_impl *impl_;
};


class FIR_FILTER_API resampling_filter : public fir_filter
{
public:
	resampling_filter(int up_factor, int down_factor, const Ipp32fc *filter_coefficients, unsigned int filter_length);
	
	resampling_filter(int up_factor, int down_factor, const double *filter_coefficients, unsigned int filter_length);

	resampling_filter(const char* spec_filename);
};


}