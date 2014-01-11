#pragma once

#include "rf_phreaker/gsm_layer_3_library/gsm_bit_stream.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"


class populate_data_interface abstract
{
public:
	virtual ~populate_data_interface() {};
	virtual void populate_data(gsm_bit_stream &bit_stream, layer_3_information::gsm_layer_3_message_aggregate &message) = 0;
};