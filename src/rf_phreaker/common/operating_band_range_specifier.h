#pragma once

#include <stdint.h>
#include <vector>

#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker {

struct operating_band_range
{
public:
	operating_band_range(operating_band band, frequency_type low, frequency_type high)
		: band_(band), low_freq_hz_(low), high_freq_hz_(high) 
	{}

	operating_band_range() 
	{}

	operating_band band_;
	frequency_type low_freq_hz_;
	frequency_type high_freq_hz_;
};

class operating_band_range_specifier
{
public:
	operating_band_range_specifier(void);

	~operating_band_range_specifier(void);

	operating_band_range get_band_freq_range(operating_band band) const;

	std::vector<operating_band_range> find_avaliable_gsm_operating_bands(frequency_type freq) const;

	std::vector<operating_band_range> find_avaliable_umts_operating_bands(frequency_type freq) const;

	std::vector<operating_band_range> find_avaliable_lte_operating_bands(frequency_type freq) const;

private:
	std::vector<operating_band_range> find_avaliable_operating_bands(frequency_type freq, operating_band begin, operating_band inclusive_end) const;

	std::vector<operating_band_range> operating_bands_;
};




}