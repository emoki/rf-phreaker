#pragma once

#include "rf_phreaker/gsm_layer_3_library/nonstandard_message.h"
#include "rf_phreaker/gsm_layer_3_library/neighbour_cell_description.h"
#include "rf_phreaker/gsm_layer_3_library/rach_control_parameters.h"
#include "rf_phreaker/gsm_layer_3_library/si_2_bis_rest_octets.h"

class system_information_type_2bis_message : public nonstandard_message
{
public:
	system_information_type_2bis_message(void);

	~system_information_type_2bis_message(void);

	void verify();

	neighbour_cell_description neighbour_cell_description_;

	rach_control_parameters rach_control_parameters_;

	si_2_bis_rest_octets si_2_bis_rest_octets_;

	

};

