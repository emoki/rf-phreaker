#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/scanner/scanner_types.h"

namespace rf_phreaker { namespace scanner {

class time_samples_conversion
{
public:
	time_samples_conversion()
	{}

	int convert_to_samples(time_type time_ns, rf_phreaker::frequency_type actual_sampling_rate_used)
	{
		// TODO - Check for max snapshot length!
		return static_cast<int>(time_ns / 1e9 * actual_sampling_rate_used);
	}
};

}}