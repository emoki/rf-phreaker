#pragma once

#include "rf_phreaker/gsm_layer_3_library/nonstandard_message.h"

#include "rf_phreaker/gsm_layer_3_library/si_2_quarter_rest_octets.h"

class system_information_type_2quarter_message : public nonstandard_message
{
public:
	system_information_type_2quarter_message(void);

	~system_information_type_2quarter_message(void);

	void verify();

	
	si_2_quarter_rest_octets si_2_quarter_rest_octets_;

	

};