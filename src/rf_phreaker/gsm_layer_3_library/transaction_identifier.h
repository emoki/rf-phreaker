#pragma once

#include "rf_phreaker/gsm_layer_3_library/generic_information_element.h"

class transaction_identifier : public generic_information_element
{
public:
	transaction_identifier(void);

	~transaction_identifier(void);

	void decode(uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused, uint32_t &bits_consumed_thus_far);


};

