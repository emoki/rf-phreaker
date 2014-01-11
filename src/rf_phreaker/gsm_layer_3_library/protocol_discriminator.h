#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

typedef protocol_discriminator_code protocol_discriminator_type;

class protocol_discriminator :public information_element_type_1
{
public:
	protocol_discriminator(format_of_information_elements format, bool value_contained_in_upper_nibble);

	~protocol_discriminator();

	void info_element_specific_decode();

	void verify();

	protocol_discriminator_type protocol_discriminator_;
};

