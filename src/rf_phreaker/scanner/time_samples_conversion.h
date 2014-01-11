#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/scanner/scanner_types.h"

namespace rf_phreaker { namespace scanner {

class time_samples_conversion
{
public:
	time_samples_conversion(rf_phreaker::frequency_type pll_reference_clock = freq_ref_hz_default)
		: pll_reference_clock_(pll_reference_clock)
	{}

	void set_pll_reference_clock(rf_phreaker::frequency_type pll_reference_clock) { pll_reference_clock_ = pll_reference_clock; }

	int convert_to_samples(int time_ms, rf_phreaker::frequency_type actual_sampling_rate_used)
	{
		// TODO - Check for max snapshot length!
		return static_cast<int>(time_ms / 1e3 * actual_sampling_rate_used);
	}

private:
	rf_phreaker::frequency_type pll_reference_clock_;

};

}}