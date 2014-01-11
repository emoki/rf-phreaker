#include "rf_phreaker/gsm_layer_3_library/l2_pseudo_length_element.h"
#include "rf_phreaker/gsm_layer_3_library/gsm_layer_3_common.h"

l2_pseudo_length_element::l2_pseudo_length_element(format_of_information_elements format)
	: information_element_type_3(format, l2_pseudo_length_value_bit_size)
{
}


l2_pseudo_length_element::~l2_pseudo_length_element(void)
{
}

void l2_pseudo_length_element::info_element_specific_decode()
{
	l2_pseudo_length_ = raw_bit_stream_[value_byte_position()] >> 2;
}

void l2_pseudo_length_element::verify()
{
	if((raw_bit_stream_[value_byte_position()] & 0x03) != 0x01)
		throw std::runtime_error("Error verifying l2_pseduo_length.");
}
