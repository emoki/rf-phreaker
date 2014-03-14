#include "gtest/gtest.h"

#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;

TEST(ChannelConversion, TestMain)
{
	operating_band_range_specifier ranges;
	channel_conversion conv;

	// Only implemented a subset for now..
	for(auto band = FIRST_UMTS_OPERATING_BAND; band <= UMTS_OPERATING_BAND_8; band = (operating_band)((int)band + 1)) {
		auto range = ranges.get_band_freq_range(band);

		for(auto freq = range.low_freq_hz_; freq <= range.high_freq_hz_; freq += khz(100))
		{
			if(freq % khz(200) != 0 && freq % khz(500) != 0)
				continue;
			std::cout << conv.frequency_to_channel(freq, band) << "\t";
		}
		
	}
}