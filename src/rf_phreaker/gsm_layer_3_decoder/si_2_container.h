#pragma once

#include "rf_phreaker/gsm_layer_3_decoder/populate_data_interface.h"
#include "rf_phreaker/gsm_layer_3_library/system_information_type_2_message.h"

class si_2_container : public populate_data_interface
{
public:
	si_2_container(void);

	~si_2_container(void);

	void populate_data(gsm_bit_stream &bit_stream, layer_3_information::gsm_layer_3_message_aggregate &message);

	system_information_type_2_message si_2;
};

