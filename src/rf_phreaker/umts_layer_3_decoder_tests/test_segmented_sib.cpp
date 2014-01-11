#include "test_segmented_sib.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include <boost/assert.hpp>

test_segmented_sib::test_segmented_sib(void)
{
}


test_segmented_sib::~test_segmented_sib(void)
{
}

void test_segmented_sib::run_automated_tests()
{
	combine_two_padded_segments();
	combine_four_padded_segments();
}

void test_segmented_sib::combine_two_padded_segments()
{
	uint8_t first_segment[2] = { 0xFF, 0x30 };
	bit_stream_container bit_stream1(first_segment, 2, 2);

	uint8_t second_segment[3] = { 0x56, 0x21, 0x90 };
	bit_stream_container bit_stream2(second_segment, 3, 4);

	segmented_sib test_segmented_sib;

	test_segmented_sib.set_first_segment(bit_stream1, 2);
	test_segmented_sib.set_last_segment(bit_stream2, 1);

	BOOST_VERIFY(test_segmented_sib.is_sib_complete() == true);
	
	bit_stream_container complete_sib(test_segmented_sib.get_completed_sib());

	BOOST_VERIFY(complete_sib.total_number_bits() == 34);
	//BOOST_VERIFY(complete_sib.num_of_bytes() == 5);
	//BOOST_VERIFY(complete_sib.unused_bits() == 6);

	uint8_t verify_complete_sib[] = { 0xFF, 0x31, 0x58, 0x86, 0x40 };
	BOOST_VERIFY(memcmp(complete_sib.bit_stream(), verify_complete_sib, 5) == 0);
}

void test_segmented_sib::combine_four_padded_segments()
{
	uint8_t first_segment[2] = { 0xFF, 0x33 };
	bit_stream_container bit_stream1(first_segment, 2, 0);

	uint8_t second_segment[3] = { 0x56, 0x21, 0x99 };
	bit_stream_container bit_stream2(second_segment, 3, 3);

	uint8_t third_segment[3] = { 0x48, 0x77, 0x80 };
	bit_stream_container bit_stream3(third_segment, 3, 6);

	uint8_t fourth_segment[1] = { 0x56 };
	bit_stream_container bit_stream4(fourth_segment, 1, 0);

	segmented_sib test_segmented_sib;

	test_segmented_sib.set_first_segment(bit_stream1, 4);
	test_segmented_sib.set_subsequent_segment(bit_stream2, 1);
	test_segmented_sib.set_subsequent_segment(bit_stream3, 2);
	test_segmented_sib.set_last_segment(bit_stream4, 3);

	BOOST_VERIFY(test_segmented_sib.is_sib_complete() == true);
	
	bit_stream_container complete_sib(test_segmented_sib.get_completed_sib());

	BOOST_VERIFY(complete_sib.total_number_bits() == 63);
	//BOOST_VERIFY(complete_sib.num_of_bytes() == 8);
	//BOOST_VERIFY(complete_sib.unused_bits() == 1);

	uint8_t verify_complete_sib[] = { 0xFF, 0x33, 0x56, 0x21, 0x9A, 0x43, 0xBC, 0xAC };
	BOOST_VERIFY(memcmp(complete_sib.bit_stream(), verify_complete_sib, 8) == 0);

}
