#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"
#include "rf_phreaker/gsm_layer_3_library/decode_interface.h"

typedef uint32_t l2_pseduo_length_type;

static const l2_pseduo_length_type system_information_type_3_l2_pseduo_length = 18;


class l2_pseudo_length_element : public information_element_type_3
{
public:
	l2_pseudo_length_element(format_of_information_elements format);

	~l2_pseudo_length_element(void);

	void verify();

	l2_pseduo_length_type l2_pseudo_length_;

protected:
	void info_element_specific_decode();

};

