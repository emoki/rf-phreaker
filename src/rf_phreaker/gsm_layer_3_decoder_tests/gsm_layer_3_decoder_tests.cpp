// test_gsm_layer_3_decoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdint.h>
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_decoder.h"
#include <boost/assert.hpp>

// 49061B2B97130062CC17C8000A59604479800080208043
const uint8_t valid_bit_stream_1[] = { 0x49, 0x06, 0x1B, 0x2B, 0x97, 0x13, 0x00, 0x62, 0xCC, 0x17, 0xC8, 0x00, 0x0A, 0x59, 0x60, 0x44, 0x79, 0x80, 0x00, 0x80, 0x20, 0x80, 0x43 };

//49061B376C1300627D66C8000A59604479000080208043
const uint8_t valid_bit_stream_2[] = { 0x49, 0x06, 0x1B, 0x37, 0x6C, 0x13, 0x00, 0x62, 0x7D, 0x66, 0xC8, 0x00, 0x0A, 0x59, 0x60, 0x44, 0x79, 0x00, 0x00, 0x80, 0x20, 0x80, 0x43 };

const uint8_t invalid_bit_stream_1[] = { 0x55, 0x06, 0x19, 0x8F, 0x19, 0xA0, 0x00, 0x40, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x80, 0x00, 0x6B };

int main(int argc, char* argv[])
{
	layer_3_information::gsm_layer_3_message_aggregate message;

	gsm_layer_3_decoder decoder;

	int32_t status = decoder.decode_bcch_message(valid_bit_stream_1, 23, 0, message);
	BOOST_ASSERT(status == 0);

	status = decoder.decode_bcch_message(valid_bit_stream_2, 23, 0, message);
	BOOST_ASSERT(status == 0);

	decoder.decode_bcch_message(invalid_bit_stream_1, 23, 0, message);
	BOOST_ASSERT(status == 0);



	return 0;
}

