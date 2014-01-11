

#include "rf_phreaker/gsm_layer_3_library_tests/test_system_information_type_2_ter_message.h"

const uint8_t bit_stream_si2_1[] = {0x12, 0x06, 0x03, 0xDF, 0x16, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x2B, 0x2B, 0x2B};

test_system_information_type_2_ter_message::test_system_information_type_2_ter_message()
{

}

test_system_information_type_2_ter_message::~test_system_information_type_2_ter_message()
{

}

void test_system_information_type_2_ter_message::run_automated_tests()
{
	system_information_type_2ter_message si2ter;

	gsm_bit_stream bs(bit_stream_si2_1, sizeof(bit_stream_si2_1), 0);

	
	si2ter.decode(bs);


}