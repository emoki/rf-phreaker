#pragma once

#include "rf_phreaker/gsm_layer_3_library/nonstandard_message.h"
#include "rf_phreaker/gsm_layer_3_library/neighbour_cell_description.h"

class system_information_type_5_message : public nonstandard_message
{
public:
	system_information_type_5_message(void);

	~system_information_type_5_message(void);

	void verify();

	neighbour_cell_description neighbour_cell_description_;

	

};