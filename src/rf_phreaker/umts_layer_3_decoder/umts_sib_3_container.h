#pragma once
#include "rf_phreaker/umts_layer_3_decoder/umts_system_information_container.h"

class umts_sib_3_container : public umts_system_information_container
{
public:
	umts_sib_3_container(void);
	~umts_sib_3_container(void);

	void parse_data(layer_3_information::umts_bcch_bch_message_aggregate &message);

};

