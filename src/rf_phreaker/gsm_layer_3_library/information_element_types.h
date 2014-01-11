#pragma once

#include "rf_phreaker/gsm_layer_3_library/generic_information_element.h"


// 3GPP TS 24.007 version 10.0.0 Release 10 - 11.2.1.1.4



class information_element_type_1 : public generic_information_element
{
public:
	information_element_type_1(format_of_information_elements format, bool value_contained_in_upper_nibble);
	~information_element_type_1(void);

	uint32_t value_byte_position() { return 0; }

	void shift_nibble_if_necessary(uint8_t &byte);

protected:
	//3GPP TS 24.007 version 10.0.0 Release 10 - 11.1.2 Octets
	bool value_contained_in_7_to_4_nibble_;
	uint8_t bit_mask_;
};


class information_element_type_2 : public generic_information_element
{
public:
	information_element_type_2();
	~information_element_type_2();

	uint32_t value_byte_position() { return 0; }
};


class information_element_type_3 : public generic_information_element
{
public:
	information_element_type_3(format_of_information_elements format, int32_t value_bit_size);
	~information_element_type_3();

	uint32_t value_byte_position() { return format_ == value_only_format ? 0 : 1; }
};


class information_element_type_4 : public generic_information_element
{
public:
	information_element_type_4(format_of_information_elements format, int32_t value_bit_size = 0);
	~information_element_type_4();

	virtual void parse_bit_stream(gsm_bit_stream &bs);
	
	void determine_value_bit_size(const gsm_bit_stream &bs);

	uint32_t value_byte_position() { return format_ == length_and_value_format ? 1 : 2; }

};

class information_element_type_5 : public generic_information_element
{
public:
	information_element_type_5(format_of_information_elements format, int32_t value_bit_size = 0);
	~information_element_type_5();

	virtual void parse_bit_stream(gsm_bit_stream &bs);
	
	void determine_value_bit_size(const gsm_bit_stream &bs);

	uint32_t value_byte_position() { return 0; }

};


// information element type 6 not supported.
