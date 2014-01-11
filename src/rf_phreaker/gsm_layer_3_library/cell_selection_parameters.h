#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"


static const int32_t cell_selection_parameters_value_bit_size = 24;


class cell_selection_parameters : public information_element_type_3
{


public:
	cell_selection_parameters(format_of_information_elements format);

	~cell_selection_parameters(void);

	void info_element_specific_decode();

	void verify();

	uint8_t cell_reselect_hysteresis_;

	uint8_t ms_txpwr_max_cch_;

	uint8_t acs_;

	uint8_t neci_;

	uint8_t rxlev_access_min_;

	
};
