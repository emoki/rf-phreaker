#pragma once

#include <stdint.h>
#include "rf_phreaker/common/ipp_array.h"

namespace rf_phreaker {

class moving_window_calculator
{
public:
	moving_window_calculator();
	
	~moving_window_calculator(void);

	void calculate_moving_window_of_energy(const ipp_32fc_array &signal, int32_t moving_window_length);

	void calculate_moving_window_of_rms(const ipp_32fc_array &signal, int32_t moving_window_length);

	void calculate_moving_window_of_energy(const Ipp32fc *signal, int signal_length, int32_t moving_window_length);

	void calculate_moving_window_of_rms(const Ipp32fc *signal, int signal_length, int32_t moving_window_length);

	const ipp_32f_array& get_total_power() const
	{
		return total_energy_;
	}

	const ipp_32f_array& get_rms() const
	{
		return rms_;
	}

	int  /*average_power_length*/output_length() const { return output_length_; }

	int moving_window_length() const { return moving_window_length_; }


private:
	void configure(int32_t max_signal_length, int32_t moving_window_length);

	int output_length_;
	int moving_window_length_;
	ipp_32f_array power_spectrum_;
	ipp_32f_array total_energy_;
	ipp_32f_array rms_;
	ipp_32f_array moving_window_ones_;
};

}