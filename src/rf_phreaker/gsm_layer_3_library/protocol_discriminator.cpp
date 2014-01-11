#include "rf_phreaker/gsm_layer_3_library/protocol_discriminator.h"
#include "rf_phreaker/gsm_layer_3_library/gsm_layer_3_common.h"

protocol_discriminator::protocol_discriminator(format_of_information_elements format, bool value_contained_in_upper_nibble)
	: information_element_type_1(format, value_contained_in_upper_nibble)
{
}


protocol_discriminator::~protocol_discriminator(void)
{
}

void protocol_discriminator::info_element_specific_decode()
{
	protocol_discriminator_ = (protocol_discriminator_type)(raw_bit_stream_[value_byte_position()] & bit_mask_);
	shift_nibble_if_necessary((uint8_t&)protocol_discriminator_);
}

void protocol_discriminator::verify()
{
	if((protocol_discriminator_ & 0xF0) != 0 || protocol_discriminator_ == 0x0d)
		throw std::runtime_error("Error verifying protocol_discriminator.");
}
