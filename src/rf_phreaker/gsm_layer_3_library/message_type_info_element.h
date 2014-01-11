#pragma once

#include "rf_phreaker/gsm_layer_3_library/gsm_layer_3_common.h"
#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

typedef message_type_code message_type;

class message_type_info_element : public information_element_type_3
{
public:
	message_type_info_element(format_of_information_elements format);

	~message_type_info_element();

	void info_element_specific_decode();

	void verify();

	message_type message_type_;
};

