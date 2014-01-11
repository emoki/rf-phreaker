#include "rf_phreaker/gsm_layer_3_library_tests/test_l2_pseudo_length_element.h"
#include "rf_phreaker/gsm_layer_3_library/gsm_bit_stream.h"
#include <boost/assert.hpp>

test_l2_pseudo_length_element::test_l2_pseudo_length_element(void)
{
}


test_l2_pseudo_length_element::~test_l2_pseudo_length_element(void)
{
}


void test_l2_pseudo_length_element::decode_good_bit_stream()
{
	test_gsm_bit_stream bs;

	bs.test_bit_stream_[0] = 15 << 2;

	bs.test_bit_stream_[0] |= 0x01;
	
	l2_pseudo_length_element length(value_only_format);
	
	length.decode(bs);
	
	bool threw_error = false;
	try { length.verify(); } catch(std::exception err) { threw_error = true; }

	BOOST_ASSERT(threw_error == false);
	BOOST_ASSERT(length.l2_pseudo_length_ == 15);
}

void test_l2_pseudo_length_element::decode_bit_stream_bad_verification()
{
	test_gsm_bit_stream bs;

	bs.test_bit_stream_[0] = 15 << 2;
	
	l2_pseudo_length_element length(value_only_format);
	
	length.decode(bs);
	
	bool threw_error = false;
	std::string error_str;
	try { length.verify(); } catch(std::exception &err) { threw_error = true; error_str = err.what(); }

	BOOST_ASSERT(threw_error == true);
	BOOST_ASSERT(error_str == "Error verifying l2_pseduo_length.");
	BOOST_ASSERT(length.l2_pseudo_length_ == 15);
}