#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"


static const int32_t  rach_control_parameters_value_bit_size = 24;


class rach_control_parameters : public information_element_type_3
{
public:
	rach_control_parameters(format_of_information_elements format);

	~rach_control_parameters(void);

	void info_element_specific_decode();

	void verify();

	
};