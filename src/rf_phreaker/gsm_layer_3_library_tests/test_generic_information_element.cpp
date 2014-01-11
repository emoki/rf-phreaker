#include "rf_phreaker/gsm_layer_3_library_tests/test_generic_information_element.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_gsm_bit_stream.h"
#include <boost/assert.hpp>

test_generic_information_element::test_generic_information_element(format_of_information_elements format, int32_t type_bit_size, int32_t value_bit_size, int32_t length_bit_size)
	: generic_information_element(format, type_bit_size, value_bit_size, length_bit_size)
{
}


test_generic_information_element::~test_generic_information_element(void)
{
}

void test_generic_information_element::run_automated_tests()
{
	test_gsm_bit_stream bs = init_bit_stream();

	test_generic_information_element e1(type_only_format, 8, 0, 0);
	verify_information_element(e1, bs);

	test_generic_information_element e2(value_only_format, 0, 8, 0);
	verify_information_element(e2, bs);

	test_generic_information_element e3(type_and_value_format, 8, 8, 0);
	verify_information_element(e3, bs);

	test_generic_information_element e4(length_and_value_format, 0, 8, 8);
	verify_information_element(e4, bs);

	test_generic_information_element e5(type_length_and_value_format, 8, 8, 8);
	verify_information_element(e5, bs);

	bool threw_error = false;
	std::string error_str;
	try { test_generic_information_element e(length_and_value_eps_format, 0, 0, 0); } catch(std::exception &err) { threw_error = true; error_str = err.what(); }
	BOOST_ASSERT(threw_error == true);
	BOOST_ASSERT(error_str == "EPS Mobility Management and EPS Session Management format of information elements not supported.");

	threw_error = false;
	error_str = "";
	try { test_generic_information_element e(type_length_and_value_eps_format, 0, 0, 0); } catch(std::exception &err) { threw_error = true; error_str = err.what(); }
	BOOST_ASSERT(threw_error == true);
	BOOST_ASSERT(error_str == "EPS Mobility Management and EPS Session Management format of information elements not supported.");
}

test_gsm_bit_stream test_generic_information_element::init_bit_stream()
{
	for(int i = 0; i < test_gsm_bit_stream::bs_size_; i++)
		test_gsm_bit_stream::test_bit_stream_[i] = 1 << i % 8;

	test_gsm_bit_stream bs(test_gsm_bit_stream::test_bit_stream_, test_gsm_bit_stream::bs_size_, 0, test_bits_consumed_);

	return bs;
} 

void test_generic_information_element::verify_information_element(test_generic_information_element &e, test_gsm_bit_stream &bs)
{
	uint32_t bits_to_consume = 0;
	switch(e.format())
	{
	case type_only_format:
		bits_to_consume = e.type_bit_size();
		BOOST_ASSERT(e.value_bit_size() == 0);
		BOOST_ASSERT(e.length_bit_size() == 0);
		break;
	case value_only_format:
		bits_to_consume = e.value_bit_size();
		BOOST_ASSERT(e.type_bit_size() == 0);
		BOOST_ASSERT(e.length_bit_size() == 0);
		break;
	case type_and_value_format:
		bits_to_consume = e.type_bit_size() + e.value_bit_size();
		BOOST_ASSERT(e.length_bit_size() == 0);
		break;
	case length_and_value_format:
		bits_to_consume = e.length_bit_size() + e.value_bit_size();
		BOOST_ASSERT(e.type_bit_size() == 0);
		break;
	case type_length_and_value_format:
		bits_to_consume = e.type_bit_size() + e.length_bit_size() + e.value_bit_size();
		break;
	case length_and_value_eps_format:
	case type_length_and_value_eps_format:
		throw std::runtime_error("EPS Mobility Management and EPS Session Management format of information elements not supported.");
		break;
	default:
		throw std::runtime_error("Format of information elements unknown.");
	}

	BOOST_ASSERT(bits_to_consume == e.bits_to_consume());

	uint32_t bits_consumed_thus_far = bs.bits_consumed_thus_far();
	uint32_t bytes_consumed_thus_far = bs.bytes_consumed_thus_far();
	const uint8_t *byte_position_before_decode = bs.current_position_in_bit_stream();

	e.decode(bs);

	for(uint32_t i = 0; i < bits_to_consume / 8; i++)
		BOOST_ASSERT(e.raw_bit_stream()[i] == *(byte_position_before_decode + i));

	BOOST_ASSERT(e.skip_bits() == bits_consumed_thus_far - bytes_consumed_thus_far);
	BOOST_ASSERT(e.bits_consumed() + bits_consumed_thus_far == bs.bits_consumed_thus_far());

}





