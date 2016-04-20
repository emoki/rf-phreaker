// fir_filter.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "rf_phreaker/fir_filter/fir_filter_impl.h"
#include "rf_phreaker/fir_filter/filter_specs.h"
#include "rf_phreaker/common/ipp_array.h"

using namespace rf_phreaker;

fir_filter::fir_filter()
	: impl_(new fir_filter_impl)
{}


//fir_filter::fir_filter(int up_factor, int down_factor)
//	: impl_(new fir_filter_impl(up_factor, down_factor))
//{}

fir_filter::fir_filter(int64_t original_sampling_rate, int64_t new_sampling_rate)
: impl_(new fir_filter_impl(original_sampling_rate, new_sampling_rate))
{}

fir_filter::~fir_filter(){
	delete impl_;
}

int fir_filter::length() const{
	return impl_->length();
}

void fir_filter::set_up_down_factor_based_on_sampling_rates(int64_t original_sampling_rate, int64_t new_sampling_rate)
{
	impl_->set_up_down_factor_based_on_sampling_rates(original_sampling_rate, new_sampling_rate);
}

void fir_filter::set_up_down_factor(int up_factor, int down_factor)
{
	impl_->set_up_down_factor(up_factor, down_factor);
}

int fir_filter::num_samples_delay() const{
	return impl_->num_samples_delay();
}

void fir_filter::set_zero_delay(bool zero_delay){
	impl_->set_zero_delay(zero_delay);
}

int fir_filter::set_taps(int length, double norm_factor, double norm_cutoff_freq)
{
	return impl_->set_taps(length, norm_factor, norm_cutoff_freq);
}

int fir_filter::set_taps(const Ipp32fc *taps, int length){
	return impl_->set_taps(taps, length);
}

int fir_filter::set_taps(const double *taps, int length){
	return impl_->set_taps(taps, length);
}

int fir_filter::filter(Ipp32fc *in, int num_iters) const{
	return impl_->filter(in, num_iters);
}

int fir_filter::filter(const Ipp32fc *in, Ipp32fc *out, int num_iters) const{
	return impl_->filter(in, out, num_iters);
}

int fir_filter::filter(const Ipp32fc *in, int num_input_samples_to_filter,
						Ipp32fc *out, int num_samples_output_buffer_capacity,
						int& num_output_filtered_samples) const{
	return impl_->filter(in, num_input_samples_to_filter, out, num_samples_output_buffer_capacity, num_output_filtered_samples);	
}

int fir_filter::num_input_samples_required(int num_output_samples_desired) const{
	return impl_->num_input_samples_required(num_output_samples_desired);
}

int fir_filter::num_output_samples_required(int num_input_samples_desired) const{
	return impl_->num_output_samples_required(num_input_samples_desired);
}

int fir_filter::ensure_output_samples_large_enough(int num_output_samples_desired) const {
	return impl_->ensure_output_samples_large_enough(num_output_samples_desired);
}

int fir_filter::num_iterations_required(int num_input_samples_desired) const{
	return impl_->num_iterations_required(num_input_samples_desired);
}
	
int fir_filter::up_factor() const {
	return impl_->up_factor();
}

int fir_filter::down_factor() const {
	return impl_->down_factor();
}





resampling_filter::resampling_filter(int up_factor, int down_factor, const Ipp32fc *filter_coefficients, unsigned int filter_length)
				: fir_filter(up_factor, down_factor) {
	set_zero_delay(true);
	set_taps(filter_coefficients, filter_length);
};

resampling_filter::resampling_filter(int up_factor, int down_factor, const double *filter_coefficients, unsigned int filter_length)
				: fir_filter(up_factor, down_factor) {
	set_zero_delay(true);
	set_taps(filter_coefficients, filter_length);
};

resampling_filter::resampling_filter(const char* spec_filename) {
	filter_specs<ipp_32fc_array> specs(spec_filename);
	set_up_down_factor(specs.up_factor(), specs.down_factor());
	set_zero_delay(true);
	set_taps(specs.taps().get(), specs.taps().length());
}
