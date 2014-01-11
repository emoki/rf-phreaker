#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"


static const int32_t  si_3_rest_octects_value_bit_size = 32;

class optional_selection_parameters
{

public:
	optional_selection_parameters();
	~optional_selection_parameters();

	uint8_t cbq;
	uint8_t cell_reselect_offset;
	uint8_t temporary_offset;
	uint8_t penalty_time;

};

class optional_power_offset
{
public:
	optional_power_offset();
	~optional_power_offset();

	uint8_t power_offset;

};

class scheduling_if_where
{
public:
	scheduling_if_where();
	~scheduling_if_where();

	uint8_t wheres;
};

class gprs_indicator
{

public:
	gprs_indicator();
	~gprs_indicator();

	uint8_t ra_color;
	uint8_t si_3_position;

};



class si_3_rest_octets : public information_element_type_3
{
public:
	si_3_rest_octets(format_of_information_elements format);

	~si_3_rest_octets(void);

	void info_element_specific_decode();

	void verify();

	void extract_bits();

	void parse_bit_stream(gsm_bit_stream &bs);

	void decode(gsm_bit_stream &bs);

	uint8_t si_bits[32];


	optional_selection_parameters optional_selection_parameters_;

	optional_power_offset  optional_power_offset_;

	uint8_t system_info_2ter_indicator_;

	uint8_t  early_classmark_sending_control_;

	scheduling_if_where scheduling_if_where_;

	gprs_indicator gprs_indicator_;

	uint8_t three_g_early_classmark_sending_restriction_;

	uint8_t si2_quarter_indicator_;

	uint8_t lu_indicator_;

	uint8_t system_information_21_indicator_;


	
};