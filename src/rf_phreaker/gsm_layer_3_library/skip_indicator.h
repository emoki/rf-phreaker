#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

typedef bool skip_indicator_type;

class skip_indicator : public information_element_type_1
{
public:
	skip_indicator(format_of_information_elements format, bool value_contained_in_upper_nibble);
	~skip_indicator();

	void verify();

	skip_indicator_type skip_indicator_;

protected:
	void info_element_specific_decode();
};

