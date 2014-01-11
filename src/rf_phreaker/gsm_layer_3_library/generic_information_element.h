#pragma once

#include <stdint.h>
#include <vector>

#include "rf_phreaker/gsm_layer_3_library/gsm_layer_3_common.h"
#include "rf_phreaker/gsm_layer_3_library/gsm_bit_stream.h"
#include "rf_phreaker/gsm_layer_3_library/decode_interface.h"

class generic_information_element : public decode_interface
{
public:
	generic_information_element(format_of_information_elements format, int32_t type_bit_size, int32_t value_bit_size, int32_t length_bit_size);

	virtual ~generic_information_element();

	void decode(gsm_bit_stream &bs);

	const uint8_t* raw_bit_stream() { return &raw_bit_stream_[0]; };

	uint32_t skip_bits() { return skip_bits_; }

	uint32_t bits_consumed() { return bits_to_consume_; }

protected:
	virtual void info_element_specific_decode() = 0;

	virtual void parse_bit_stream(gsm_bit_stream &bs);

	void determine_bits_to_consume();

	void resize_raw_bit_stream();

	void calculate_skip_bits(const gsm_bit_stream &bs);

	void copy_to_raw_bit_stream(const gsm_bit_stream &bs);

	int32_t bits_to_consume_;
	
	int32_t skip_bits_;

	format_of_information_elements format_;

	std::vector<uint8_t> raw_bit_stream_;

	// 3GPP TS 24.007 version 10.0.0 Release 10 - Section 11.2.1.1
	int32_t value_bit_size_;

	int32_t length_bit_size_;

	int32_t type_bit_size_;
};

