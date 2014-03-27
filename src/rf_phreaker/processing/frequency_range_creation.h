#pragma once

#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/common/operating_band_range_specifier.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker { namespace processing {

class frequency_range_creation 
{
public:
	static void adjust_umts_sweep_collection_info(const operating_band_range &range, collection_info_container &c)
	{
		for(auto freq = range.low_freq_hz_ - khz(2400), end_freq = range.high_freq_hz_ + khz(2400); freq <= end_freq; freq += khz(100)) {
			if(freq % khz(200) != 0 && freq % khz(500) != 0)
				continue;
			c.adjust(add_collection_info(umts_sweep_collection_info(freq, range.band_)));
		}
	}

	static void adjust_lte_sweep_collection_info(const operating_band_range &range, collection_info_container &c)
	{
		for(auto freq = range.low_freq_hz_ - khz(1400), end_freq = range.high_freq_hz_ + khz(1400); freq <= end_freq; freq += khz(100)) {
			c.adjust(add_collection_info(lte_sweep_collection_info(freq, lte_sweep_collection_info::bandwidth__, range.band_)));
		}
	}
};


}}