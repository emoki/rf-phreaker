#include "rf_phreaker/gsm_layer_3_library_tests/test_system_information_type_2_message.h"

// 49061B2B97130062CC17C8000A59604479800080208043
const uint8_t bit_stream_si2_1[] = {0x59, 0x06, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x06, 0xCB, 0x3A, 0x48};

const uint8_t bit_stream_si2_2[] = {0x59, 0x06, 0x1a, 0x8b, 0x1f, 0x0d, 0xfc, 0x09, 0xff, 0xc1, 0x07, 0xff, 0xff, 0xd6, 0x08, 0x42, 0x00, 0x00, 0x00, 0xff, 0xb9, 0x00, 0x00 };


test_system_information_type_2_message::test_system_information_type_2_message(void)
{
}


test_system_information_type_2_message::~test_system_information_type_2_message(void)
{
}

void test_system_information_type_2_message::run_automated_tests()
{
	system_information_type_2_message si2;

	gsm_bit_stream bs(bit_stream_si2_1, sizeof(bit_stream_si2_1), 0);

	si2.decode(bs);

	gsm_bit_stream bs1(bit_stream_si2_2, sizeof(bit_stream_si2_2), 0);
	
	
	si2.decode(bs1);
	


	int i  = 0 ;
}
