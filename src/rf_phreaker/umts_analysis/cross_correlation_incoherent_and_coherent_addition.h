#pragma once

#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/moving_window_calculator.h"

namespace rf_phreaker {

class cross_correlation_incoherent_and_coherent_addition
{
public:
	cross_correlation_incoherent_and_coherent_addition(void);

	~cross_correlation_incoherent_and_coherent_addition(void);

	void set_num_coherent_windows(int num_coherent_windows);

	void set_num_iterations(int iteration_length);

	void set_iteration_length(int iteration_length);

	void set_input_signal_and_configure_parameters(const ipp_32fc_array &signal, int signal_length, int moving_window_length, int correlation_offset_ = 0);

	void calculate_average_power();

	void do_cross_correlation_and_additions(const Ipp32fc *moving_window/*, int slide_length = 0*/);

	void normalize_output();

	void reset_num_iterations() { num_iterations_ = 0; }
	
	int num_iterations() const { return num_iterations_; }

	int num_coherent_windows() const { return num_coherent_windows_; }

	int iteration_length() const { return iteration_length_; }

	int moving_window_length() const { return moving_window_length_; }

	ipp_32f_array& get_result() { return total_correlation_magnitude_; }

	Ipp32f get_rms(int position) const { assert(position < moving_window_calculator_.output_length()); return moving_window_calculator_.get_rms()[position]; }

private:
	void set_and_verify_slide_length(/*int slide_length*/);

	void set_and_verify_num_iterations();

	int calculate_max_num_iterations();

	int calculate_max_slide_length();

	moving_window_calculator moving_window_calculator_;

	ipp_32f_array average_power_inverse_;

	ipp_32fc_array normalized_cross_correlation_;

	ipp_32fc_array coherently_combined_;

	ipp_32f_array coherently_combined_magnitude_;

	ipp_32f_array total_correlation_magnitude_;

	Ipp32fc const *signal_; 
	
	int signal_length_;

	int moving_window_length_;
	
	int num_coherent_windows_;

	int num_iterations_;

	int iteration_length_;

	int slide_length_;

	int correlation_offset_;
};

}