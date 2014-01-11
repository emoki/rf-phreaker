#pragma once

#include "rf_phreaker/gsm_layer_3_library/generic_information_element.h"

class custom_decoder
{
public:
	custom_decoder(void);
	~custom_decoder(void);

	static void decode(generic_information_element &element, uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused);
};

