#include "rf_phreaker/layer_3_common_tests/test_uint16_string.h"
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>

// Using typedef instead of including asn1_types.h - Can we separate out the commonality in LTE and UMTS RRC? 
//#include "rf_phreaker/layer_3_decoder_common\asn1_types.h"
typedef long digit_type;

test_uint16_string::test_uint16_string(void)
{
}


test_uint16_string::~test_uint16_string(void)
{
}

void test_uint16_string::run_automated_tests()
{
	const char valid_string[] = "0123";
	layer_3_information::uint16_string a(valid_string);
	test_string(a, valid_string, calculate_num_characters(sizeof(valid_string)));

	const char valid_string_2[] = "123";
	layer_3_information::uint16_string b(valid_string_2);
	test_string(b, valid_string_2, calculate_num_characters(sizeof(valid_string_2)));
	
	const uint16_t valid_uint16 = 123;
	layer_3_information::uint16_string c(valid_uint16);
	test_string(c, "123", 3);

	const size_t num_valid_digits = 4;
	digit_type valid_digits[num_valid_digits] = { 0, 1, 2, 3 };
	digit_type *digits_ptr[num_valid_digits];
	digits_ptr[0] = &valid_digits[0];
	digits_ptr[1] = &valid_digits[1];
	digits_ptr[2] = &valid_digits[2];
	digits_ptr[3] = &valid_digits[3];
	layer_3_information::uint16_string d(digits_ptr, num_valid_digits);
	test_string(d, "0123", num_valid_digits);

	uint16_t eq_num = 100;
	layer_3_information::uint16_string test_equal(eq_num);
	BOOST_ASSERT(test_equal == eq_num);
	layer_3_information::uint16_string test_not_equal(eq_num+1);
	BOOST_ASSERT((test_not_equal != eq_num));
}

void test_uint16_string::test_string(const layer_3_information::uint16_string &a, const char string[], size_t string_length)
{
	BOOST_ASSERT(a.num_characters() == string_length);
	BOOST_ASSERT(strncmp(a.to_string(), string, string_length) == 0);
	BOOST_ASSERT(a.to_uint16() == boost::lexical_cast<uint16_t>(string));

}

size_t test_uint16_string::calculate_num_characters(size_t string_length_including_null)
{
	return string_length_including_null - 1;
}
