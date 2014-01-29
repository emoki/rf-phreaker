#include "gtest/gtest.h"

#include "rf_phreaker/fir_filter/filter_specs.h"
#include "rf_phreaker/common/ipp_array.h"

using namespace rf_phreaker;

TEST(FilterSpecsTest, TestMain)
{
	ipp_32fc_array taps(10);
	
	for(int i = 0; i < 10; ++i) {
		taps[i].re = i * 1.0f;
		taps[i].im = i * 2.0f;
	}

	filter_specs<ipp_32fc_array> test(10, 20, taps);

	for(int i = 0; i < 10; ++i) {
		EXPECT_FLOAT_EQ(i * 1.0f, test.taps()[i].re);
		EXPECT_FLOAT_EQ(i * 2.0f, test.taps()[i].im);
	}

	EXPECT_EQ(10, test.up_factor());
	EXPECT_EQ(20, test.down_factor());
}

TEST(FilterSpecsTest, TestIO)
{
	ipp_32fc_array taps(10);

	for(int i = 0; i < 10; ++i) {
		taps[i].re = i * 1.0f;
		taps[i].im = i * 2.0f;
	}

	filter_specs<ipp_32fc_array> test(10, 20, taps);

	std::string filename = "test_filter_specs.txt";
	{
		std::ofstream file(filename);

		EXPECT_TRUE(file.is_open());

		file << test;
	}

	filter_specs<ipp_32fc_array> io_test(filename);

	for(int i = 0, j = test.taps().length(); i < j; ++i) {
		EXPECT_FLOAT_EQ(test.taps()[i].re, io_test.taps()[i].re);
		EXPECT_FLOAT_EQ(test.taps()[i].im, io_test.taps()[i].im);
	}

	EXPECT_EQ(test.up_factor(), io_test.up_factor());
	EXPECT_EQ(test.down_factor(), io_test.down_factor());

}
