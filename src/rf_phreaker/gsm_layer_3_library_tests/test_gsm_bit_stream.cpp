#include "rf_phreaker/gsm_layer_3_library_tests/test_gsm_bit_stream.h"
#include <boost/assert.hpp>

uint8_t test_gsm_bit_stream::test_bit_stream_[test_gsm_bit_stream::bs_size_];

test_gsm_bit_stream::test_gsm_bit_stream(const uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused, uint32_t bits_consumed_thus_far)
	: gsm_bit_stream(bit_stream, num_bytes, bits_unused, bits_consumed_thus_far)
{
}

test_gsm_bit_stream::test_gsm_bit_stream(uint32_t bits_consumed)
	: gsm_bit_stream(test_bit_stream_, bs_size_, bits_consumed)
{
	memset(test_bit_stream_, 0, bs_size_ * sizeof(test_bit_stream_[0]));
}

test_gsm_bit_stream::~test_gsm_bit_stream(void)
{
}

void test_gsm_bit_stream::run_automated_tests()
{
	const uint32_t bits_in_byte = 8;

	gsm_bit_stream bs(test_bit_stream_, bs_size_, 0);
	BOOST_ASSERT(bs.current_position_in_bit_stream() == &test_bit_stream_[0]);
	BOOST_ASSERT(bs.bytes_consumed_thus_far() == 0);
	BOOST_ASSERT(bs.bits_consumed_thus_far() == 0);
	BOOST_ASSERT(bs.num_bytes_in_bit_stream() == bs_size_);
	BOOST_ASSERT(bs.num_bits_in_bit_stream() == bs_size_ * bits_in_byte);
	BOOST_ASSERT(bs.num_bits_unused_in_bit_stream() == 0);

	uint32_t bits_to_consume = 10;
	uint32_t bytes_consumed = 1;
	bs.consume_more_bits(bits_to_consume);
	BOOST_ASSERT(bs.bits_consumed_thus_far() == bits_to_consume);
	BOOST_ASSERT(bs.bytes_consumed_thus_far() == bytes_consumed);
	BOOST_ASSERT(bs.current_position_in_bit_stream() == &test_bit_stream_[bytes_consumed]);


	uint32_t bits_not_used = 5;
	uint32_t bits_consumed_thus_far = 33;
	uint32_t bytes_consumed_thus_far = 4;
	uint32_t current_byte_position = 4; 
	gsm_bit_stream bs_2(test_bit_stream_, bs_size_, bits_not_used, bits_consumed_thus_far);
	BOOST_ASSERT(bs_2.current_position_in_bit_stream() == &test_bit_stream_[current_byte_position]);
	BOOST_ASSERT(bs_2.bytes_consumed_thus_far() == bytes_consumed_thus_far);
	BOOST_ASSERT(bs_2.bits_consumed_thus_far() == bits_consumed_thus_far);
	BOOST_ASSERT(bs_2.num_bytes_in_bit_stream() == bs_size_);
	BOOST_ASSERT(bs_2.num_bits_in_bit_stream() == bs_size_ * bits_in_byte);
	BOOST_ASSERT(bs_2.num_bits_unused_in_bit_stream() == bits_not_used);

	uint32_t bits_consumed_border_condition_good = bs_2.num_bits_in_bit_stream() - bits_consumed_thus_far - bits_not_used;
	uint32_t too_many_bits_consumed_border_condition = bits_consumed_border_condition_good + 1;

	bool threw_error = false;
	try { bs_2.verify_bit_stream(0); } catch(std::exception err) { threw_error = true; }
	BOOST_ASSERT(threw_error ==  false);

	threw_error = false;
	try { bs_2.verify_bit_stream(bits_consumed_border_condition_good); } catch(std::exception err) { threw_error = true; }
	BOOST_ASSERT(threw_error ==  false);

	threw_error = false;
	std::string error_str;
	try { bs_2.verify_bit_stream(too_many_bits_consumed_border_condition); } catch(std::exception err) { threw_error = true; error_str = err.what(); }
	BOOST_ASSERT(threw_error ==  true);
	BOOST_ASSERT(error_str == "Error decoding GSM bit stream.  1 additional bit(s) are needed to continue current decode.");

}