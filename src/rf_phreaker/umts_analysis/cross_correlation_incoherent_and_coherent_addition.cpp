#include "rf_phreaker/umts_analysis/cross_correlation_incoherent_and_coherent_addition.h"
#include <assert.h>

namespace rf_phreaker {

cross_correlation_incoherent_and_coherent_addition::cross_correlation_incoherent_and_coherent_addition(void)
	: num_coherent_windows_(0)
	, num_iterations_(0)
	, iteration_length_(0)
{
}


cross_correlation_incoherent_and_coherent_addition::~cross_correlation_incoherent_and_coherent_addition(void)
{
}

void cross_correlation_incoherent_and_coherent_addition::set_num_coherent_windows(int set_num_coherent_windows)
{
	assert(set_num_coherent_windows > 0);
	num_coherent_windows_ = set_num_coherent_windows;
}

void cross_correlation_incoherent_and_coherent_addition::set_iteration_length(int iteration_length)
{
	assert(iteration_length > 0);
	iteration_length_ = iteration_length;
}

void cross_correlation_incoherent_and_coherent_addition::set_num_iterations(int num_iterations)
{
	assert(num_iterations > 0);
	num_iterations_ = num_iterations;
}

void cross_correlation_incoherent_and_coherent_addition::set_input_signal_and_configure_parameters(const ipp_32fc_array &signal, int signal_length, int moving_window_length, int correlation_offset)
{
	assert(num_coherent_windows_ > 0 && 
		correlation_offset + num_coherent_windows_ * iteration_length_ < signal_length &&
		correlation_offset + num_coherent_windows_ * moving_window_length < signal_length);

	signal_ = signal.get();

	signal_length_ = signal_length;

	moving_window_length_ = moving_window_length;

	correlation_offset_ = correlation_offset;

	set_and_verify_num_iterations();

	set_and_verify_slide_length();

	normalized_cross_correlation_.reset(slide_length_);

}

void cross_correlation_incoherent_and_coherent_addition::calculate_average_power()
{
	moving_window_calculator_.calculate_moving_window_of_rms(signal_ + correlation_offset_, signal_length_ - correlation_offset_, moving_window_length_);

	average_power_inverse_.reset(moving_window_calculator_.output_length());

	average_power_inverse_.set_array_values(1);

	ipp_helper::check_status(ippsDiv_32f_I(moving_window_calculator_.get_rms().get(), average_power_inverse_.get(), moving_window_calculator_.output_length()));
}

void cross_correlation_incoherent_and_coherent_addition::do_cross_correlation_and_additions(const Ipp32fc *moving_window/*, int slide_length*/)
{
	ipp_helper::check_status(ippsCrossCorr_32fc(moving_window, moving_window_length_, signal_ + correlation_offset_, signal_length_ - correlation_offset_, normalized_cross_correlation_.get(), slide_length_, 0));

	ipp_helper::check_status(ippsMul_32f32fc_I(average_power_inverse_.get(), normalized_cross_correlation_.get(), normalized_cross_correlation_.length()));

	coherently_combined_.reset(iteration_length_);
	coherently_combined_magnitude_.reset(iteration_length_);
	total_correlation_magnitude_.reset(iteration_length_);
 
	total_correlation_magnitude_.set_array_values(0);

	for(int i = 0; i < num_iterations_; i++)
	{
		int position = i * num_coherent_windows_ * iteration_length_;

		Ipp32fc tmp; tmp.re = 0; tmp.im = 0;
		coherently_combined_.set_array_values(tmp);
		coherently_combined_magnitude_.set_array_values(0);

		memcpy(coherently_combined_.get(), normalized_cross_correlation_.get(position), coherently_combined_.length() * sizeof(Ipp32fc));

		for(int j = 1; j < num_coherent_windows_; j++)
			ipp_helper::check_status(ippsAdd_32fc_I(normalized_cross_correlation_.get(position + j * iteration_length_), coherently_combined_.get(), coherently_combined_.length()));

		ipp_helper::check_status(ippsMagnitude_32fc(coherently_combined_.get(), coherently_combined_magnitude_.get(), coherently_combined_magnitude_.length()));

		ipp_helper::check_status(ippsAdd_32f_I(coherently_combined_magnitude_.get(), total_correlation_magnitude_.get(), total_correlation_magnitude_.length()));
	}

	normalize_output();
}

void cross_correlation_incoherent_and_coherent_addition::set_and_verify_slide_length(/*int slide_length*/)
{
	// num_iterations must already be initialized.
	assert(num_iterations_ > 0 && num_coherent_windows_ > 0);

	slide_length_ = iteration_length_ * num_coherent_windows_ * num_iterations_;

	assert(slide_length_ <= calculate_max_slide_length());
}

int cross_correlation_incoherent_and_coherent_addition::calculate_max_slide_length()
{
	return signal_length_ - correlation_offset_ - moving_window_length_;
}

void cross_correlation_incoherent_and_coherent_addition::set_and_verify_num_iterations()
{
	int max_num_iterations = calculate_max_num_iterations();

	if(num_iterations_ == 0)
		num_iterations_ = max_num_iterations;

	else if(num_iterations_ > max_num_iterations)
		throw std::runtime_error("Unable to do cross correlation.  Number of iterations goes out of bounds.");
}

int cross_correlation_incoherent_and_coherent_addition::calculate_max_num_iterations()
{
	assert(iteration_length_ > 0 && 
		num_coherent_windows_ * iteration_length_ <= calculate_max_slide_length() &&
		num_coherent_windows_ * moving_window_length_ <= calculate_max_slide_length());

	int num_total_windows_available = calculate_max_slide_length() / iteration_length_;

	return num_total_windows_available / num_coherent_windows_;
}

void cross_correlation_incoherent_and_coherent_addition::normalize_output()
{
	Ipp32f normalization_value = 1.0f / (num_iterations_ * num_coherent_windows_ * moving_window_length_);

	ipp_helper::check_status(ippsMulC_32f_I(normalization_value, total_correlation_magnitude_.get(), total_correlation_magnitude_.length()));

}


}