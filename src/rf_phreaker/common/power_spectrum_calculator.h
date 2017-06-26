#pragma once 
#include <vector>
#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/fft_helper.h"
#include "rf_phreaker/common/moving_window_calculator.h"
#include "rf_phreaker/common/raw_signal.h"

namespace rf_phreaker {

class power_spectrum_calculator
{
public:
	power_spectrum_calculator()
		: sampling_rate_(0)
		, bin_size_hz_(0)
		, window_length_(0)
		, total_length_(0)
		, freq_resolution_(0) {}

	static int determine_window_length(frequency_type sampling_rate, frequency_type bin_size) {
		return static_cast<int>(pow(2, determine_fft_order(sampling_rate, bin_size)));
	}

	static int determine_fft_order(frequency_type sampling_rate, frequency_type bin_size) {
		return static_cast<int>(std::ceil(log10(sampling_rate / bin_size) / log10(2)));
	}

	static frequency_type determine_sampling_rate(int fft_order, frequency_type bin_size) {
		return static_cast<int>(pow(2, fft_order) * bin_size);
	}

	power_info_group calculate_power_info_group(const raw_signal &sig, frequency_type bin_size_hz, frequency_type step_size_hz,
		frequency_type low_if, frequency_type high_if, int window_length, frequency_type center_freq = 0) {
	
		sampling_rate_ = sig.sampling_rate();
		bin_size_hz_ = bin_size_hz;
		freq_resolution_ = sampling_rate_ / (double)window_length;
		
		calculate_power_spectrum(sig.get_iq(), window_length);

		int moving_window = (int)std::round(bin_size_hz / freq_resolution_);

		if (center_freq == 0)
			center_freq = sig.frequency();

		power_info_group group;
		for (auto inter_freq = low_if; inter_freq <= high_if; inter_freq += step_size_hz) {
			group.push_back(power_info(center_freq + inter_freq, bin_size_hz, get_power_in_bin(inter_freq)));
		}
		return group;
	}

	void calculate_power_spectrum(const ipp_32fc_array &src, int window_length, int total_length = 0) {
		if ((window_length_ & window_length_ - 1))
			throw processing_error("window length of power spectrum must be to a power of two, not " + std::to_string(window_length) + ".");
		window_length_ = window_length;
		total_length_ = total_length == 0 ? src.length() : total_length;

		helper_.reset_based_on_signal_length(window_length_);

		calculate_power_buffer_.reset(window_length_);
		power_buffer_.reset(window_length);
		summed_power_buffer_.reset(window_length_);
		summed_power_buffer_.zero_out();

		if(window_function_.length() != window_length_) {
			window_function_.reset(window_length_);
			window_buffer_.reset(window_length);
			Ipp32fc t; t.re = 1; t.im = 1;
			window_function_.set_array_values(t);
			ipp_helper::check_status(ippsWinBartlett_32fc(window_function_.get(), window_function_.get(), window_function_.length()));
		}

		auto half_step = window_length_ / 2;
		auto num_iterations = static_cast<int>((total_length_ - 1) / half_step);
		auto overlapping_percent = num_iterations > 1 ? (total_length_ - window_length_) / (num_iterations - 1) : 0;
		for(int i = 0; i < num_iterations; ++i) {
			auto offset = static_cast<int>(overlapping_percent * i + .5);
			ipp_helper::check_status(ippsMul_32fc(src.get(offset), window_function_.get(), window_buffer_.get(), window_buffer_.length()));
			helper_.fft_forward(window_buffer_.get(), calculate_power_buffer_.get());
			ipp_helper::check_status(ippsPowerSpectr_32fc(calculate_power_buffer_.get(), power_buffer_.get(), power_buffer_.length()));
			// Removed.  I think this can be done after averaging along with signal sqrt.
			//ipp_helper::check_status(ippsDivC_32f(power_buffer_.get(), pow(window_buffer_.length(), 0.5), power_buffer_.get(), power_buffer_.length()));
			ipp_helper::check_status(ippsAdd_32f(power_buffer_.get(), summed_power_buffer_.get(), summed_power_buffer_.get(), summed_power_buffer_.length()));
		}

		helper_.fft_shift(summed_power_buffer_);

		ipp_helper::check_status(ippsDivC_32f(summed_power_buffer_.get(), (Ipp32f)num_iterations, summed_power_buffer_.get(), summed_power_buffer_.length()));
		// It should be the square root of the window size because later when calculating signal level we do 20 * log10 which means we're assuming the power
		// and the window size are not squared
		ipp_helper::check_status(ippsDivC_32f(summed_power_buffer_.get(), (Ipp32f)pow(window_buffer_.length(), 0.5), summed_power_buffer_.get(), power_buffer_.length()));
		ipp_helper::check_status(ippsSqrt_32f(summed_power_buffer_.get(), summed_power_buffer_.get(), summed_power_buffer_.length()));
	
	}

	float get_power_in_bin(frequency_type intermediate_frequency) const {
		// Because the the bins start at -max_freq we add max_freq to the intermediate_frequency.
		auto max_freq = sampling_rate_ / 2;
		int location = (int)std::round((intermediate_frequency + max_freq) / freq_resolution_);
		if (location < 0 || location >= summed_power_buffer_.length())
			throw ipp_error("Intermediate frequency is outside the range of moving_window_calculator.");
		return summed_power_buffer_.get_value(location);
	}

	const ipp_32f_array& power_spectra() const{ return summed_power_buffer_; }
private:

	frequency_type sampling_rate_;
	frequency_type bin_size_hz_;
	double freq_resolution_;
	int window_length_;
	int total_length_;

	ipp_32fc_array calculate_power_buffer_;

	ipp_32f_array summed_power_buffer_;

	ipp_32fc_array window_function_;

	ipp_32fc_array window_buffer_;

	ipp_32f_array power_buffer_;

	fft_helper helper_;
};

}