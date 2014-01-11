#include "rf_phreaker/gsm_layer_3_library/message_type_info_element.h"

message_type_info_element::message_type_info_element(format_of_information_elements format)
	: information_element_type_3(format, message_type_value_bit_size)
{
}


message_type_info_element::~message_type_info_element(void)
{
}

void message_type_info_element::info_element_specific_decode()
{
	message_type_ = (message_type)raw_bit_stream_[value_byte_position()];
}

void message_type_info_element::verify()
{
	// Currently we do not verify.
}
