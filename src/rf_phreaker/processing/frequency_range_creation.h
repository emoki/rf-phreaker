#pragma once

#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/common/operating_band_range_specifier.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker { namespace processing {

class frequency_range_creation 
{
public:
	static const frequency_type gsm_step_size_hz_ = khz(3000);
	static void adjust_gsm_sweep_collection_info_with_adjustment(const operating_band_range &range, collection_info_container &c) {
		// Be sure to make sure the center freq is % khz(200) != 0
		auto adj_range = range;
		//if(adj_range.band_ == GSM_850 || adj_range.band_ == GSM_DCS_1800 || adj_range.band_ == GSM_PCS_1900) {
			adj_range.low_freq_hz_ -= khz(200);
		//}
		for(auto freq = adj_range.low_freq_hz_ + khz(1500), end_freq = adj_range.high_freq_hz_; freq < end_freq; freq += gsm_step_size_hz_) {
			if(freq >= adj_range.high_freq_hz_ - khz(1500)) {
				if(adj_range.band_ == GSM_850) {
					freq = mhz(894) - khz(1500);
				}
				else if(adj_range.band_ == GSM_R_900) {
					freq = mhz(960) - khz(1500);
				}
				else if(adj_range.band_ == GSM_DCS_1800) {
					freq = mhz(1880) - khz(1500);
				}
				else if(adj_range.band_ == GSM_PCS_1900) {
					freq = mhz(1990) - khz(1500);
				}
			}
			if(freq % khz(200) == 0)
				freq -= khz(100);
			c.adjust(add_collection_info(gsm_sweep_collection_info(freq, range.band_, false)));
		}
	}

	static void adjust_gsm_sweep_collection_info(const operating_band_range &range, collection_info_container &c) {
		// Be sure to make sure the center freq is % khz(200) != 0
		for(auto freq = range.low_freq_hz_, end_freq = range.high_freq_hz_; freq <= end_freq; freq += gsm_step_size_hz_) {
			c.adjust(add_collection_info(gsm_sweep_collection_info(freq, range.band_, false)));
			if(freq % khz(200) == 0)
				freq -= khz(100);
		}
	}

	static void adjust_umts_sweep_collection_info_with_adjustment(const operating_band_range &range, collection_info_container &c)
	{
		for(auto freq = range.low_freq_hz_ - khz(2400), end_freq = range.high_freq_hz_ + khz(2400); freq <= end_freq; freq += khz(100)) {
			if(freq % khz(200) != 0 && freq % khz(500) != 0)
				continue;
			c.adjust(add_collection_info(umts_sweep_collection_info(freq, range.band_, false)));
		}
	}

	static void adjust_umts_sweep_collection_info(const operating_band_range &range, collection_info_container &c) {
		for(auto freq = range.low_freq_hz_, end_freq = range.high_freq_hz_; freq <= end_freq; freq += khz(100)) {
			if(freq % khz(200) != 0 && freq % khz(500) != 0)
				continue;
			c.adjust(add_collection_info(umts_sweep_collection_info(freq, range.band_, false)));
		}
	}

	static void adjust_lte_sweep_collection_info(const operating_band_range &range, collection_info_container &c)
	{
		for(auto freq = range.low_freq_hz_, end_freq = range.high_freq_hz_; freq <= end_freq; freq += khz(100)) {
			c.adjust(add_collection_info(lte_sweep_collection_info(freq, lte_sweep_collection_info::bandwidth__, range.band_, false)));
		}
	}
};


}}