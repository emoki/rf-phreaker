#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

typedef uint16_t cell_identity_type;


// 3GPP TS 24.008 version 10.3.0 Release 10 - Figure 10.5.1/3GPP TS 24.008 Cell Identity information element
class cell_identity : public information_element_type_3
{
public:
	cell_identity(format_of_information_elements format);

	~cell_identity(void);

	void info_element_specific_decode();

	void verify();

	cell_identity_type cell_identity_;
};

