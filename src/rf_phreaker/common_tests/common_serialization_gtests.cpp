#include "gtest/gtest.h"

#include "rf_phreaker/common/common_serialization.h"
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

using namespace rf_phreaker;

TEST(Serialization, TestMain) {
	raw_signal sig;
	sig.bandwidth(mhz(2));
	sig.sampling_rate(mhz(4));
	sig.frequency(mhz(1960));

	int sig_length = 100;
	sig.get_iq().reset(sig_length);
	for(int i = 0; i < sig_length; ++i) {
		sig.get_iq()[i].re = (Ipp32f)i;
		sig.get_iq()[i].im = (Ipp32f)i * 2;
	}

	{
		std::ofstream f("test_raw_sig_serialization.txt");
		boost::archive::text_oarchive oa(f);
		oa & sig;
	}
	raw_signal sig2;
	{
		std::ifstream f("test_raw_sig_serialization.txt");
		boost::archive::text_iarchive ia(f);
		ia & sig2;
	}
	EXPECT_TRUE(sig == sig2);
	{
		std::ofstream f("test_raw_sig_serialization.bin", std::ios::binary);
		boost::archive::binary_oarchive oa(f);
		oa & sig;
	}
	raw_signal sig3;
	{
		std::ifstream f("test_raw_sig_serialization.bin", std::ios::binary);
		boost::archive::binary_iarchive ia(f);
		ia & sig3;
	}
	EXPECT_TRUE(sig == sig3);

}
