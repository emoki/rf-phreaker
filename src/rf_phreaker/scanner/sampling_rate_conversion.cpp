#include "rf_phreaker/scanner/sampling_rate_conversion.h"
#include "rf_phreaker/scanner/packet_typedefs.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

sampling_rate_conversion::sampling_rate_conversion(rf_phreaker::frequency_type pll_reference_clock)
	: pll_reference_clock_(pll_reference_clock)
{
	for(int i = 1; i < 17; ++i) {
		lookup_.insert(std::make_pair(pll_reference_clock_ / i, sampling_rate_conversion::info(pll_reference_clock_ / i, i/* - 1*/))); 
	}
}


frequency_type sampling_rate_conversion::find_lower_bound_sampling_rate(frequency_type sampling_rate)
{
	auto it = lookup_.lower_bound(sampling_rate);
	if(it == lookup_.end()) {
		// TODO - log error.  Give the largest sampling rate possible.
		--it;
	}
		
	return it->first;
}

rf_phreaker::frequency_type sampling_rate_conversion::find_lower_bound_sampling_rate(rf_phreaker::bandwidth_type bandwidth)
{
	// Ideally the sampling_rate should be twice the interested bandwidth but we can get away with 1.28?  This fits with LTE parameters.
	return find_lower_bound_sampling_rate(static_cast<frequency_type>(bandwidth * 1.28));
}

int sampling_rate_conversion::find_decimation_value(frequency_type sampling_rate)
{
	auto it = lookup_.lower_bound(sampling_rate);
	if(it == lookup_.end()) {
		// TODO - log error.  Give the largest sampling rate possible.
		--it;
	}
	return it->second.decimation_;
}

int sampling_rate_conversion::find_decimation_value(rf_phreaker::bandwidth_type bandwidth)
{
	return find_decimation_value(static_cast<frequency_type>(bandwidth * 1.5));
}


