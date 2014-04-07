#include "gtest/gtest.h"

#include "rf_phreaker/common/raw_signal.h"

using namespace rf_phreaker;

TEST(RawSignal, TestMain)
{
	const int signal_size = 1000;
	raw_signal test(signal_size, 1001, 1002, 1003);

	for(int i = 0; i < signal_size; ++i) {
		test.get_iq()[i].re = (float)i;
		test.get_iq()[i].im = (float)(i * 5);
	}

	std::string filename("test_raw_signal.txt");
	{
		std::ofstream out(filename);
		ASSERT_TRUE(out.good());
		out << test;
	}

	{
		std::ifstream in(filename);
		ASSERT_TRUE(in.good());
		raw_signal new_sig;
		in >> new_sig;

		EXPECT_EQ(new_sig.get_iq().length(), signal_size);
		for(int i = 0; i < signal_size; ++i) {
			EXPECT_DOUBLE_EQ(test.get_iq()[i].re, i);
			EXPECT_DOUBLE_EQ(test.get_iq()[i].im, i * 5);
		}
		EXPECT_EQ(new_sig.frequency(), 1001);
		EXPECT_EQ(new_sig.bandwidth(), 1002);
		EXPECT_EQ(new_sig.sampling_rate(), 1003);
	}
}

TEST(RawSignal, WithMeasurementInfo)
{
	const int signal_size = 1000;
	raw_signal test(signal_size, 1001, 1002, 1003);

	for(int i = 0; i < signal_size; ++i) {
		test.get_iq()[i].re = (float)i;
		test.get_iq()[i].im = (float)(i * 5);
	}

	std::string filename("test_raw_signal2.txt");
	{
		std::ofstream out(filename);
		ASSERT_TRUE(out.good());
		out << "measurement \t111\t1111\t1111\n";
		out << test;
	}

	{
		std::ifstream in(filename);
		ASSERT_TRUE(in.good());
		raw_signal new_sig;
		in >> new_sig;

		EXPECT_EQ(new_sig.get_iq().length(), signal_size);
		for(int i = 0; i < signal_size; ++i) {
			EXPECT_DOUBLE_EQ(test.get_iq()[i].re, i);
			EXPECT_DOUBLE_EQ(test.get_iq()[i].im, i * 5);
		}
		EXPECT_EQ(new_sig.frequency(), 1001);
		EXPECT_EQ(new_sig.bandwidth(), 1002);
		EXPECT_EQ(new_sig.sampling_rate(), 1003);
	}
}

TEST(RawSignal, BadFile)
{
	std::string filename("test_raw_signal3.txt");
	{
		std::ofstream out(filename);
		ASSERT_TRUE(out.good());
		for(int i = 0; i < 10000; ++i)
			out << "measurement \t111\t1111\t1111\n";
	}
	{
		std::ifstream in(filename);
		ASSERT_TRUE(in.good());
		raw_signal new_sig;
		
		EXPECT_ANY_THROW(in  >> new_sig);

	}
}