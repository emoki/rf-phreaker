#pragma once

#include "rf_phreaker/gsm_layer_3_library/nonstandard_message.h"
#include "rf_phreaker/gsm_layer_3_library/neighbour_cell_description2.h"
#include "rf_phreaker/gsm_layer_3_library/si_2_ter_rest_octets.h"

class system_information_type_2ter_message : public nonstandard_message
{
public:
	system_information_type_2ter_message(void);

	~system_information_type_2ter_message(void);

	void verify();

	neighbour_cell_description2 neighbour_cell_description2_;

	si_2_ter_rest_octets si_2_ter_rest_octets_;

	

};