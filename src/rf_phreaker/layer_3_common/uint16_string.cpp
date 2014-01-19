#include "rf_phreaker/layer_3_common/uint16_string.h"

using namespace layer_3_information;

uint16_string::uint16_string() 
{}

uint16_string::uint16_string(const char *a) : string_(a)
{}

uint16_string::uint16_string(uint16_t a) : string_(boost::lexical_cast<std::string>(a))
{}

uint16_string::uint16_string(uint8_t* digits, int num_digits)
{
	BOOST_ASSERT(digits);
	BOOST_ASSERT(num_digits > 0);
	for(int i = 0; i < num_digits; i++) {
		string_ += boost::lexical_cast<std::string>((uint32_t)digits[i]);
	}
}

uint16_string::uint16_string(/*digit_type*/long **digits, int num_digits)
{
	BOOST_ASSERT(digits);
	BOOST_ASSERT(num_digits > 0);
	for(int i = 0; i < num_digits; i++) {
		const long *tmp = digits[i];
		BOOST_ASSERT(*tmp >= 0);
		string_ += boost::lexical_cast<std::string>(*digits[i]);
	}
}
