#include "gtest/gtest.h"

#include "rf_phreaker/common/operating_band_range_specifier.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;

TEST(OperatingBandRangeSpecifier, TestMain)
{
	operating_band_range_specifier specifier;

	auto unknown = specifier.get_band_freq_range(OPERATING_BAND_UNKNOWN);
	EXPECT_EQ(OPERATING_BAND_UNKNOWN, unknown.band_);
	EXPECT_EQ(-1, unknown.low_freq_hz_);
	EXPECT_EQ(-1, unknown.high_freq_hz_);

	auto valid_bands = specifier.find_avaliable_gsm_operating_bands(mhz(936));
	EXPECT_EQ(4, valid_bands.size());
	EXPECT_EQ(GSM_P_900, valid_bands[0].band_);
	EXPECT_EQ(GSM_E_900, valid_bands[1].band_);
	EXPECT_EQ(GSM_R_900, valid_bands[2].band_);
	EXPECT_EQ(GSM_ER_900, valid_bands[3].band_);

	valid_bands = specifier.find_avaliable_umts_operating_bands(mhz(2140));
	EXPECT_EQ(3, valid_bands.size());
	EXPECT_EQ(UMTS_OPERATING_BAND_1, valid_bands[0].band_);
	EXPECT_EQ(UMTS_OPERATING_BAND_4, valid_bands[1].band_);
	EXPECT_EQ(UMTS_OPERATING_BAND_10, valid_bands[2].band_);
	
	valid_bands = specifier.find_avaliable_lte_operating_bands(mhz(950));
	EXPECT_EQ(1, valid_bands.size());
	EXPECT_EQ(LTE_OPERATING_BAND_8, valid_bands[0].band_);

	valid_bands = specifier.find_avaliable_lte_operating_bands(mhz(961));
	EXPECT_EQ(0, valid_bands.size());
}
