#pragma once

#include "rf_phreaker/gsm_layer_3_library/generic_information_element.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_gsm_bit_stream.h"

class test_generic_information_element : public generic_information_element
{
public:
	test_generic_information_element(format_of_information_elements format, int32_t type_bit_size, int32_t value_bit_size, int32_t length_bit_size);
	~test_generic_information_element(void);

	static void run_automated_tests();

	static test_gsm_bit_stream init_bit_stream();

	static void verify_information_element(test_generic_information_element &e, test_gsm_bit_stream &bs);

	format_of_information_elements format() { return format_; }

	uint32_t type_bit_size() { return type_bit_size_; }

	uint32_t value_bit_size() { return value_bit_size_; }

	uint32_t length_bit_size() { return length_bit_size_; }

	uint32_t bits_to_consume() { return bits_to_consume_; }

private:



	static const uint32_t test_bits_consumed_ = 3;



	// Pure virtual functions needed to instantiate.
	void info_element_specific_decode() {};
	void verify() {};

	
};

