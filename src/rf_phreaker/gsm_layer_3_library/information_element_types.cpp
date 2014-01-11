#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

#include <boost/assert.hpp>


information_element_type_1::information_element_type_1(format_of_information_elements format, bool value_contained_in_7_to_4_nibble)
	: generic_information_element(format, (format ==  value_only_format ? 0 : 4), 4, 0)
	, value_contained_in_7_to_4_nibble_(value_contained_in_7_to_4_nibble)
	, bit_mask_(value_contained_in_7_to_4_nibble ? 0xF0 : 0x0F)
{
	if(format_ == type_and_value_format)
		BOOST_VERIFY(value_contained_in_7_to_4_nibble_ == false);
}


information_element_type_1::~information_element_type_1()
{
}

void information_element_type_1::shift_nibble_if_necessary(uint8_t &byte)
{
	if(value_contained_in_7_to_4_nibble_)
		byte = byte >> 4;
}


information_element_type_2::information_element_type_2()
	: generic_information_element(type_only_format, 8, 0, 0)
{
}

information_element_type_2::~information_element_type_2()
{
}



information_element_type_3::information_element_type_3(format_of_information_elements format, int32_t value_bit_size)
	: generic_information_element(format, (format ==  value_only_format ? 0 : 8), value_bit_size, 0)
{
}

information_element_type_3::~information_element_type_3()
{
}



information_element_type_4::information_element_type_4(format_of_information_elements format, int32_t value_bit_size)
	: generic_information_element(format, (format ==  length_and_value_format ? 0 : 8), value_bit_size, 8)
{
}

information_element_type_4::~information_element_type_4()
{
}

void information_element_type_4::parse_bit_stream(gsm_bit_stream &bs)
{
	if(value_bit_size_ == 0)
		determine_value_bit_size(bs);

	generic_information_element::parse_bit_stream(bs);
}

void information_element_type_4::determine_value_bit_size(const gsm_bit_stream &bs)
{
	bs.verify_bit_stream(bits_to_consume_);
	
	BOOST_ASSERT(format_ == length_and_value_format || format_ == type_length_and_value_format);

	if(format_ == length_and_value_format)
		value_bit_size_ = bs.current_position_in_bit_stream()[0];
	else
		value_bit_size_ = bs.current_position_in_bit_stream()[1];	
}




information_element_type_5::information_element_type_5(format_of_information_elements format, int32_t value_bit_size)
	: generic_information_element(format, (format ==  variable_length ? 0 : 8), value_bit_size, 8)
{
}

information_element_type_5::~information_element_type_5()
{
}

void information_element_type_5::parse_bit_stream(gsm_bit_stream &bs)
{
	
}

void information_element_type_5::determine_value_bit_size(const gsm_bit_stream &bs)
{
	
}









