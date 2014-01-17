#include "rf_phreaker/umts_layer_3_decoder_tests/test_bit_stream_container.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include <fstream>
#include <vector>
#include <boost/assert.hpp>

test_bit_stream_container::test_bit_stream_container(void)
{}


test_bit_stream_container::~test_bit_stream_container(void)
{}

void test_bit_stream_container::run_automated_tests()
{
	general_test();
}

void test_bit_stream_container::general_test()
{
	const int size = 4;
	std::vector<uint8_t> bytes;
	bytes.push_back(0x11);
	bytes.push_back(0x22);
	bytes.push_back(0x22);
	bytes.push_back(0xff);

	bit_stream_container t(&bytes[0], size, 0);
	
	std::string str("test");
	{
		std::ofstream file(str);

		BOOST_ASSERT(file);

		file << t;
	}

	bit_stream_container_mem t2;
	{
		std::ifstream file(str);

		BOOST_ASSERT(file);

		file >> t2;
	}

	for(int i = 0; i < size; ++i)
		BOOST_ASSERT(t.bit_stream()[i] == t2.bit_stream()[i]);

}
