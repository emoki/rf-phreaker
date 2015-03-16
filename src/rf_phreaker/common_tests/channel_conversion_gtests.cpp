#include "gtest/gtest.h"

#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;

TEST(ChannelConversion, TestUarfcnConversion) {
	operating_band_range_specifier ranges;
	channel_conversion conv;

	conv.uarfcn_to_frequency(1342);

	// Only implemented a subset for now..
	for(auto band = FIRST_UMTS_OPERATING_BAND; band <= UMTS_OPERATING_BAND_8; band = (operating_band)((int)band + 1)) {
		auto range = ranges.get_band_freq_range(band);
		
		for(auto freq = range.low_freq_hz_; freq <= range.high_freq_hz_; freq += khz(100)) {
			if(freq % khz(200) != 0)
				continue;
			EXPECT_EQ(freq, conv.uarfcn_to_frequency(conv.frequency_to_channel(freq, band).channel_).freq_);
		}

		std::vector<channel_freq> valid_conversions;
		for(auto freq = range.low_freq_hz_; freq <= range.high_freq_hz_; freq += khz(100)) {
			auto tmp = freq % khz(200);
			if(freq % khz(200) == 0 || freq % khz(500) != 0)
				continue;
			auto cf = conv.uarfcn_to_frequency(conv.frequency_to_channel(freq, band).channel_);
			if(cf.is_valid())
				valid_conversions.push_back(cf);
		}

		for(auto cf : valid_conversions) {
			switch(cf.band_) {
			case UMTS_OPERATING_BAND_2:
				switch(cf.freq_) {
				case khz(1932500):
				case khz(1937500):
				case khz(1942500):
				case khz(1947500):
				case khz(1952500):
				case khz(1957500):
				case khz(1962500):
				case khz(1967500):
				case khz(1972500):
				case khz(1977500):
				case khz(1982500):
				case khz(1987500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_4:
				switch(cf.freq_) {
				case khz(2112500):
				case khz(2117500):
				case khz(2122500):
				case khz(2127500):
				case khz(2132500):
				case khz(2137500):
				case khz(2142500):
				case khz(2147500):
				case khz(2152500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_5:
				switch(cf.freq_) {
				case khz(871500):
				case khz(872500):
				case khz(876500):
				case khz(877500):
				case khz(882500):
				case khz(887500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_6:
				switch(cf.freq_) {
				case khz(877500):
				case khz(882500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_7:
				switch(cf.freq_) {
				case khz(2622500):
				case khz(2627500):
				case khz(2632500):
				case khz(2637500):
				case khz(2642500):
				case khz(2647500):
				case khz(2652500):
				case khz(2657500):
				case khz(2662500):
				case khz(2667500):
				case khz(2672500):
				case khz(2677500):
				case khz(2682500):
				case khz(2687500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_10:
				switch(cf.freq_) {
				case khz(2112500):
				case khz(2117500):
				case khz(2122500):
				case khz(2127500):
				case khz(2132500):
				case khz(2137500):
				case khz(2142500):
				case khz(2147500):
				case khz(2152500):
				case khz(2157500):
				case khz(2162500):
				case khz(2167500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_12:
				switch(cf.freq_) {
				case khz(731500):
				case khz(736500):
				case khz(737500):
				case khz(742500):
				case khz(743500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_13:
				switch(cf.freq_) {
				case khz(748500):
				case khz(753500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_14:
				switch(cf.freq_) {
				case khz(760500):
				case khz(765500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_19:
				switch(cf.freq_) {
				case khz(877500):
				case khz(882500):
				case khz(887500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			case UMTS_OPERATING_BAND_25:
				switch(cf.freq_) {
				case khz(1932500):
				case khz(1937500):
				case khz(1942500):
				case khz(1947500):
				case khz(1952500):
				case khz(1957500):
				case khz(1962500):
				case khz(1967500):
				case khz(1972500):
				case khz(1977500):
				case khz(1982500):
				case khz(1987500):
				case khz(1992500):
					break;
				default:
					EXPECT_TRUE(false);
				}
				break;

			default:
				;// Do nothing for bands that do not have extra conversions.
			}
		}
		
	}
}

TEST(ChannelConversion, TestEarfcnConversion) {
	operating_band_range_specifier ranges;
	channel_conversion conv;

	for(auto band = FIRST_LTE_OPERATING_BAND; band <= LAST_LTE_OPERATING_BAND; band = (operating_band)((int)band + 1)) {
		auto range = ranges.get_band_freq_range(band);

		// No longer a valid band.
		if(band == LTE_OPERATING_BAND_30)
			continue;

		for(auto freq = range.low_freq_hz_; freq < range.high_freq_hz_; freq += khz(100)) {
			EXPECT_EQ(freq, conv.earfcn_to_frequency(conv.frequency_to_channel(freq, band).channel_).freq_);
		}
	}
}
