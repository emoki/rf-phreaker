#include "gtest/gtest.h"
#include <boost/utility/binary.hpp>

#include "rf_phreaker/scanner/bandwidth_conversion.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker::scanner;
using namespace rf_phreaker::scanner::lms;

TEST(BandwidthConversionTest, TestBWTypeConversion)
{
	EXPECT_EQ(mhz(28), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_28_MHZ));
	EXPECT_EQ(mhz(20), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_20_MHZ));
	EXPECT_EQ(mhz(14), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_14_MHZ));
	EXPECT_EQ(mhz(12), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_12_MHZ));
	EXPECT_EQ(mhz(10), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_10_MHZ));
	EXPECT_EQ(khz(8750), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_8P75_MHZ));
	EXPECT_EQ(mhz(7), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_7_MHZ));
	EXPECT_EQ(mhz(6), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_6_MHZ));
	EXPECT_EQ(khz(5500), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_5P5_MHZ));
	EXPECT_EQ(mhz(5), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_5_MHZ));
	EXPECT_EQ(khz(3840), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_3P84_MHZ));
	EXPECT_EQ(mhz(3), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_3_MHZ));
	EXPECT_EQ(khz(2750), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_2P75_MHZ));
	EXPECT_EQ(khz(2500), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_2P5_MHZ));
	EXPECT_EQ(khz(1750), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_1P75_MHZ));
	EXPECT_EQ(khz(1500), bandwidth_conversion::convert_to_bandwidth_type(BANDWIDTH_1P5_MHZ));
}

TEST(BandwidthConversionTest, TestFindLowerBoundBW)
{
	bandwidth_enum lms_bw = BANDWIDTH_28_MHZ;

	for(rf_phreaker::bandwidth_type i = mhz(28); i <= 0; --i)
	{
		auto tmp = static_cast<bandwidth_enum>((int)lms_bw + 1);
		
		if(i == bandwidth_conversion::convert_to_bandwidth_type(tmp))
			lms_bw = tmp;

		EXPECT_EQ(lms_bw, bandwidth_conversion::find_lower_bound_bandwidth(i));
	}

	ASSERT_THROW(bandwidth_conversion::find_lower_bound_bandwidth(mhz(28)+1), rf_phreaker::misc_error);
}

TEST(BandwidthConversionTest, TestBWValue)
{
	const rf_phreaker::bandwidth_type bw = mhz(5);
	lms_value_type output = BOOST_BINARY(1001);
	output = output << 2;
	output |= 0x2; // enable lpf
	output &= ~0x1; // decode control signals

	EXPECT_EQ(output, bandwidth_conversion::get_bandwidth_and_enable_lpf_value(bw));
}

TEST(BandwidthConversionTest, TestBWPacketContainer)
{
	const rf_phreaker::bandwidth_type bw = mhz(5);
	packet_container pc = bandwidth_conversion::get_bandwidth_and_enable_lpf(bw);

	auto buf = pc.begin()->get()->serialize_to_buf_type();

	EXPECT_STRCASEEQ("lime,write,54,value,26;\r", &buf[0]);
}

