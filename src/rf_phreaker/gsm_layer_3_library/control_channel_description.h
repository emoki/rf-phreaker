#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"


static const int32_t  control_channel_description_value_bit_size = 24;


class control_channel_description : public information_element_type_3
{
public:
	control_channel_description(format_of_information_elements format);

	~control_channel_description(void);

	void info_element_specific_decode();

	void verify();

	
};