#pragma once

#include "rf_phreaker/gsm_layer_3_library/nonstandard_message.h"
#include "rf_phreaker/gsm_layer_3_library/cell_identity.h"
#include "rf_phreaker/gsm_layer_3_library/location_area_identification.h"
#include "rf_phreaker/gsm_layer_3_library/control_channel_description.h"
#include "rf_phreaker/gsm_layer_3_library/cell_options.h"
#include "rf_phreaker/gsm_layer_3_library/cell_selection_parameters.h"
#include "rf_phreaker/gsm_layer_3_library/rach_control_parameters.h"
#include "rf_phreaker/gsm_layer_3_library/si_3_rest_octets.h"

class system_information_type_3_message : public nonstandard_message
{
public:
	system_information_type_3_message(void);

	~system_information_type_3_message(void);

	void verify();

	cell_identity cell_identity_;

	location_area_identification location_area_identification_;

	control_channel_description control_channel_desription_;

	cell_options cell_options_;

	cell_selection_parameters cell_selection_parameters_;

	rach_control_parameters rach_control_parameters_;

	si_3_rest_octets si_3_rest_octets_;




};

