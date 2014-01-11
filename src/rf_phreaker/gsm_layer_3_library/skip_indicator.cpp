#include "rf_phreaker/gsm_layer_3_library/skip_indicator.h"
#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

skip_indicator::skip_indicator(format_of_information_elements format, bool value_contained_in_upper_nibble)
	: information_element_type_1(format, value_contained_in_upper_nibble)
{
}


skip_indicator::~skip_indicator(void)
{
}

void skip_indicator::info_element_specific_decode()
{
	if((raw_bit_stream_[value_byte_position()] & bit_mask_) != 0)
		skip_indicator_ = true;
	else
		skip_indicator_ = false;
}

void skip_indicator::verify()
{
}
