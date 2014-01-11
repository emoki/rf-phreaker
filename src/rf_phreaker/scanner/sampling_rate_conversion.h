#pragma once

#include <map>

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/scanner/packet_container.h"

namespace rf_phreaker { namespace scanner {

class sampling_rate_conversion
{
public:
	sampling_rate_conversion(rf_phreaker::frequency_type pll_reference_clock = freq_ref_hz_default);

	rf_phreaker::frequency_type find_lower_bound_sampling_rate(rf_phreaker::frequency_type sampling_rate);

	rf_phreaker::frequency_type find_lower_bound_sampling_rate(rf_phreaker::bandwidth_type bandwidth);

	int find_decimation_value(rf_phreaker::frequency_type sampling_rate);
	
	int find_decimation_value(rf_phreaker::bandwidth_type bandwidth);

private:
	rf_phreaker::frequency_type pll_reference_clock_;


	struct info {
		info(rf_phreaker::frequency_type freq, int decimation) 
			: freq_(freq), decimation_(decimation) 
		{}
		rf_phreaker::frequency_type freq_;
		int decimation_;
	};
	std::map<rf_phreaker::frequency_type, info> lookup_;

};

}}