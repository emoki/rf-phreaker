#pragma once

#include "rf_phreaker/gsm_layer_3_library/gsm_bit_stream.h"

class decode_interface 
{
public:
	virtual ~decode_interface() {};
	virtual void decode(gsm_bit_stream &bs) = 0;
	virtual void verify() = 0;
};



