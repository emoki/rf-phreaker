#include "gtest/gtest.h"

#include "rf_phreaker/scanner/measurement_info.h"

using namespace rf_phreaker::scanner;

TEST(MeasurementInfo, TestMain)
{
	const int signal_size = 1000;
	gain_type g(lms::LNA_MAX, 30, 10);
	rf_phreaker::frequency_type freq = 1001;
	measurement_info test(signal_size, freq, 1002, 1003, g, std::chrono::milliseconds(1004), rf_adjustment{{freq, freq}, 1}, rf_adjustment{{freq, freq}, 2}, 1004, "1234567891234567891234");
	test.set_operating_bands(rf_phreaker::operating_bands({rf_phreaker::UMTS_OPERATING_BAND_1, rf_phreaker::LTE_OPERATING_BAND_10}));

	for(int i = 0; i < signal_size; ++i) {
		test.get_iq()[i].re = (float)i;
		test.get_iq()[i].im = (float)(i * 5);
	}

	std::string filename("test_meas.txt");
	{
		std::ofstream out(filename);
		ASSERT_TRUE(out.good());
		out << test;
	}

	{
		std::ifstream in(filename);
		ASSERT_TRUE(in.good());
		measurement_info new_sig;
		in >> new_sig;

		EXPECT_EQ(new_sig.get_iq().length(), signal_size);
		for(int i = 0; i < signal_size; ++i) {
			EXPECT_DOUBLE_EQ(test.get_iq()[i].re, i);
			EXPECT_DOUBLE_EQ(test.get_iq()[i].im, i * 5);
		}
		EXPECT_EQ(new_sig.frequency(), freq);
		EXPECT_EQ(new_sig.bandwidth(), 1002);
		EXPECT_EQ(new_sig.sampling_rate(), 1003);
		EXPECT_EQ(new_sig.origin_time_pc(), std::chrono::milliseconds(1004));
		EXPECT_EQ(new_sig.gain().lna_gain_, lms::LNA_MAX);
		EXPECT_EQ(new_sig.gain().rxvga1_, 30);
		EXPECT_EQ(new_sig.gain().rxvga2_, 10);
		EXPECT_EQ(new_sig.blade_adjustment_value(test.frequency()), 1);
		EXPECT_EQ(new_sig.rf_board_adjustment_value(test.frequency()), 2);
		EXPECT_EQ(new_sig.collection_round(), 1004);
		EXPECT_EQ(new_sig.serial(), "1234567891234567891234");
	}
}