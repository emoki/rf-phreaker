#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"


static const int32_t  cell_options_value_bit_size = 8;


class cell_options : public information_element_type_3
{
public:
	cell_options(format_of_information_elements format);

	~cell_options(void);

	void info_element_specific_decode();

	void verify();

	
};