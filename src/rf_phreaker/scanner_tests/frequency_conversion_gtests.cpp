#include "gtest/gtest.h"

#include "rf_phreaker/scanner/frequency_conversion.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker::scanner;

class FrequencyConversionTest : public ::testing::Test 
{
protected:
	FrequencyConversionTest()
	{
		lfreq.freq_select_ = BOOST_BINARY(100100);
		lfreq.x_ = 2;
		lfreq.nint_ = 139;
		lfreq.nfrac_ = 2708821;
		lfreq.reference_ = 30720000;

		freq = 2140000000;
	}

	lms::lms_freq lfreq;
	rf_phreaker::frequency_type freq;

	int nint_value;
	int nfact_msb_value;
	int nfact_mid_value;
	int nfract_lsb_value;
	int freq_select_value;
};

TEST_F(FrequencyConversionTest, TestConvertToLmsFreq)
{
	frequency_conversion freq_conv(lfreq.reference_);

	lms::lms_freq test_lfreq = freq_conv.convert_to_lms_freq(freq);

	EXPECT_EQ(lfreq.freq_select_, test_lfreq.freq_select_);
	EXPECT_EQ(lfreq.x_, test_lfreq.x_);
	EXPECT_EQ(lfreq.nint_, test_lfreq.nint_);
	EXPECT_EQ(lfreq.nfrac_, test_lfreq.nfrac_);
	EXPECT_EQ(lfreq.reference_, test_lfreq.reference_);

	EXPECT_EQ(freq, freq_conv.convert_to_hz(lfreq));
}

TEST_F(FrequencyConversionTest, TestConvertToFreqHz)
{
	frequency_conversion freq_conv(lfreq.reference_);

	EXPECT_EQ(freq, freq_conv.convert_to_hz(lfreq));
}

TEST_F(FrequencyConversionTest, TestConvertToPacketContainer)
{
	frequency_conversion freq_conv(lfreq.reference_);
	
	auto pc = freq_conv.convert_to_packet_container(freq);
	
	EXPECT_EQ(5, pc.num_packets());
	
	auto p = pc.begin();

	buf_type str;
	
	str = p->get()->serialize_to_buf_type();
	ASSERT_STRCASEEQ("lime,write,20,value,45;\r", &str.at(0));

	++p;
	str = p->get()->serialize_to_buf_type();
	ASSERT_STRCASEEQ("lime,write,21,value,a9;\r", &str.at(0));

	++p;
	str = p->get()->serialize_to_buf_type();
	ASSERT_STRCASEEQ("lime,write,22,value,55;\r", &str.at(0));

	++p;
	str = p->get()->serialize_to_buf_type();
	ASSERT_STRCASEEQ("lime,write,23,value,55;\r", &str.at(0));

	++p;
	str = p->get()->serialize_to_buf_type();
	ASSERT_STRCASEEQ("lime,write,25,value,92;\r", &str.at(0));
}

//TEST_F(FrequencyConversionTest, TestConvertToExceptions)
//{
//	frequency_conversion freq_conv(lfreq.reference_);
//
//	ASSERT_THROW(freq_conv.convert_to_lms_freq(-1), misc_error);
//
//	ASSERT_THROW(freq_conv.convert_to_lms_freq(100000000000000), misc_error);
//}

TEST_F(FrequencyConversionTest, TestTmp)
{
	frequency_conversion freq_conv;

	lms::lms_freq test_lfreq = freq_conv.convert_to_lms_freq(mhz(885));

	auto pc = freq_conv.convert_to_packet_container(mhz(885));
	
	EXPECT_EQ(5, pc.num_packets());

	std::vector<char> buf(5000);
	pc.serialize(buf.begin());
	std::string str(buf.begin(), buf.end());
}