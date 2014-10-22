#pragma once

#include <stdint.h>
#include <boost/assert.hpp>
#include "rf_phreaker/layer_3_decoder_common/asn1_types.h"

static int digit_placement[5] = { 1, 10, 100, 1000, 10000 };


inline uint32_t create_num_from_bit_stream(const bit_stream_type &bit_stream)
{
    BOOST_VERIFY(bit_stream.size <= (int)sizeof(uint32_t));

	uint8_t tmp[4];
	memset(tmp, 0, sizeof(tmp));

	int index = bit_stream.size - 1;
	for(int i = 0; i < bit_stream.size; i++)	
		memcpy(&tmp[index--], &bit_stream.buf[i], 1);

	uint32_t tmp_32 = *(uint32_t*)tmp;

	tmp_32 = tmp_32 >> bit_stream.bits_unused;

	return tmp_32;
}

inline layer_3_information::cid_type create_cid(const bit_stream_type &bit_stream)
{
	return (layer_3_information::cid_type)create_num_from_bit_stream(bit_stream);
}

inline uint32_t create_num_from_octet_stream(const octet_stream_type &oct_stream)
{
    BOOST_VERIFY(oct_stream.size <= (int)sizeof(uint32_t));

	uint8_t tmp[4];
	memset(tmp, 0, sizeof(tmp));
	
	int index = oct_stream.size - 1;
	for(int i = 0; i < oct_stream.size; i++)	
		memcpy(&tmp[index--], &oct_stream.buf[i], 1);

	return *(uint32_t*)tmp;
}

inline layer_3_information::lac_type create_lac(const octet_stream_type &oct_stream)
{
	return (layer_3_information::lac_type)create_num_from_octet_stream(oct_stream);
};

inline uint32_t create_num_from_digit_sequence(long **digits, int num_of_digits)
{
	uint32_t tmp = 0;
	int digit_placement_position = 0;
	for(int i = num_of_digits - 1; i >= 0 ; i--)
	{
		const long *digit = digits[i];
		tmp += *digit * digit_placement[digit_placement_position++];
	}
	return tmp;
}

inline layer_3_information::mcc_type create_mcc_type(long **digits, int num_of_digits)
{
	return layer_3_information::mcc_type(digits, num_of_digits);
}

inline layer_3_information::mnc_type create_mnc_type(long **digits, int num_of_digits)
{
	return layer_3_information::mnc_type(digits, num_of_digits);
}

