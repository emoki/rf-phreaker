#include "rf_phreaker/gsm_layer_3_library_tests/test_system_information_type_2_quarter_message.h"

const uint8_t bit_stream_si2quarter_1[] = {0x12, 0x06, 0x07, 0xC2, 0x3C, 0x06, 0x19, 0x54, 0xEC, 0x10, 0x7F, 0x75, 0x55, 0x1E, 0x1F, 0x04, 0x60, 0x20, 0xCB, 0xA1, 0xAA, 0xF0, 0x2B };

test_system_information_type_2quarter_message::test_system_information_type_2quarter_message()
{

}

test_system_information_type_2quarter_message::~test_system_information_type_2quarter_message()
{

}

void test_system_information_type_2quarter_message::run_automated_tests()
{
	system_information_type_2quarter_message si2quarter;

	gsm_bit_stream bs(bit_stream_si2quarter_1, sizeof(bit_stream_si2quarter_1), 0);

	
	si2quarter.decode(bs);


}