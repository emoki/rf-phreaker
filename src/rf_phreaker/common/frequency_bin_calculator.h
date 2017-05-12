#pragma once 
#include <vector>
#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/fft_helper.h"
#include "rf_phreaker/common/moving_window_calculator.h"
#include "rf_phreaker/common/raw_signal.h"

namespace rf_phreaker {

class frequency_bin_calculator
{
public:
	frequency_bin_calculator() 
		: sampling_rate_(0)
		, bin_size_hz_(0)
		, length_(0)
		, freq_resolution_(0) {}

	power_info_group calculate_power_info_group(const raw_signal &sig, frequency_type bin_size_hz, frequency_type step_size_hz,
		frequency_type low_if, frequency_type high_if, int length = 0, frequency_type center_freq = 0) {
		calculate_power_in_bins(sig.get_iq(), sig.sampling_rate(), bin_size_hz, length);
		
		if(center_freq == 0)
			center_freq = sig.frequency();

		power_info_group group;
		for(auto inter_freq = low_if; inter_freq <= high_if; inter_freq += step_size_hz) {
			group.push_back(power_info(center_freq + inter_freq, (bandwidth_type)bin_size_hz, get_power_in_bin(inter_freq)));
		}
		return group;
	}

	void calculate_power_in_bins(const ipp_32fc_array &src, frequency_type sampling_rate, frequency_type bin_size_hz, int length = 0) {
		sampling_rate_ = sampling_rate;
		bin_size_hz_ = bin_size_hz;
		length_ = length == 0 ? src.length() : length;
		freq_resolution_ = sampling_rate / (double)length_;

		helper_.reset_based_on_signal_length(length_);

		calculate_power_buffer_.reset(length_);

		helper_.fft_forward(src, calculate_power_buffer_);

		helper_.fft_shift(calculate_power_buffer_);

		int moving_window = (int)std::round(bin_size_hz / freq_resolution_);

		moving_window_calculator_.calculate_moving_window_of_energy(calculate_power_buffer_, moving_window);
	}

	float get_power_in_bin(frequency_type intermediate_frequency) {
		// Because the the bins start at -max_freq we add max_freq to the intermediate_frequency.
		auto max_freq = sampling_rate_ / 2;
		int location = (int)std::round((intermediate_frequency + max_freq) / freq_resolution_);
		if(location < 0 || location >= moving_window_calculator_.get_total_power().length())
			throw ipp_error("Intermediate frequency is outside the range of moving_window_calculator.");
		return sqrt(moving_window_calculator_.get_total_power().get_value(location));
	}

	const ipp_32f_array& get_bins() { 
		return moving_window_calculator_.get_total_power();
	}

private:
	frequency_type sampling_rate_;
	frequency_type bin_size_hz_;
	double freq_resolution_;
	int length_;

	ipp_32fc_array calculate_power_buffer_;

	fft_helper helper_;

	moving_window_calculator moving_window_calculator_;

};

}