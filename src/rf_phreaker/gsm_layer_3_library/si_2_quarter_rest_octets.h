
#pragma once

#include <stdint.h>
#include <vector>


#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

static const int32_t  si_2_quarter_rest_octects_bit_size = 160;

enum
	{
	 duplex_mode_fdd = 0,
	 duplex_mode_tdd = 1
	};

class non_aligned_element
{

public:
	non_aligned_element(){};
	~non_aligned_element(){};

	uint8_t lenght;
	uint8_t offset;
	void extract();

};


class measurement_parameter_desription
{
public:
	measurement_parameter_desription();
	~measurement_parameter_desription();

	void decode(uint8_t *data_bits, uint8_t &origin_offset);

	



};

class gprs_real_time_difference_description
{

public:
	gprs_real_time_difference_description();
	~gprs_real_time_difference_description();

	void decode(uint8_t *data_bits, uint8_t &origin_offset);

	




};

class gprs_bsic_description
{
public:
	gprs_bsic_description();
	~gprs_bsic_description();

	void decode(uint8_t *data_bits, uint8_t &origin_offset);



};


class gprs_report_priority_description
{
public:
	gprs_report_priority_description();
	~gprs_report_priority_description();

	void decode(uint8_t *data_bits, uint8_t &origin_offset);

};

class gprs_measurement_paramters_description
{
public:
	 gprs_measurement_paramters_description();
	~gprs_measurement_paramters_description();

	void decode(uint8_t *data_bits, uint8_t &origin_offset);

};

class nc_measurement_parameters
{
public:
	nc_measurement_parameters();
	~nc_measurement_parameters();

	void decode(uint8_t *data_bits, uint8_t &origin_offset);

};

class extension_si_2_q
{

public:
	extension_si_2_q();
	~extension_si_2_q();

	void decode(uint8_t *data_bits, uint8_t &origin_offset);



};

class repeated_neighbour_cells
{
public:
	repeated_neighbour_cells();
	~repeated_neighbour_cells();
	

	uint32_t arfcn;
	uint8_t indico;
	uint8_t nr_of_cells;
	uint8_t total_num_cells;
	uint8_t cell_information[128];
	uint32_t w[16];
	uint32_t f[16];

	static uint8_t power_of_two[32];

	static uint8_t p[32], q[32];

	void decode_cell_info(uint32_t duplex_mode);

};

class utran_description_quarter
{
public:
	utran_description_quarter(){};
	~utran_description_quarter(){};

	uint8_t bandwidth;
	repeated_neighbour_cells  repeated_utran_neighbour_cells_[8];

};


class three_g_neighbour_cell_description
{
public:
	three_g_neighbour_cell_description();
	~three_g_neighbour_cell_description();

	uint8_t lenght;
	uint8_t offset;

	uint8_t index_start_3g;
	uint8_t absolute_index_start_emr;
	utran_description_quarter utran_fdd_description;
	utran_description_quarter utran_tdd_description;




	void decode(uint8_t *data_bits, uint8_t &origin_offset);


};






class si_2_quarter_rest_octets : public information_element_type_3
{
public:
	si_2_quarter_rest_octets(format_of_information_elements format);
	~si_2_quarter_rest_octets();

	uint8_t si_octect_size;

	uint8_t ba_ind;
	uint8_t three_g_ba_ind;
	uint8_t mp_change_mark;
	uint8_t si_2_quarter_index;
	uint8_t si_2_quarter_count;

	uint8_t offset;

	uint8_t si_bits[160]; // 20 octets

	measurement_parameter_desription measurement_parameter_desription_;

	gprs_real_time_difference_description gprs_real_time_difference_description_;

	gprs_bsic_description gprs_bsic_description_;

	gprs_report_priority_description gprs_report_priority_description_;

	gprs_measurement_paramters_description gprs_measurement_paramters_description_;

	nc_measurement_parameters  nc_measurement_parameters_;

	extension_si_2_q  extension_si_2_q_;

	three_g_neighbour_cell_description three_g_neighbour_cell_description_;
	

	void extract_bits(uint8_t *src, uint8_t *dest, uint8_t num_octects);

	void info_element_specific_decode();

	void parse_bit_stream(gsm_bit_stream &bs);

	void decode(gsm_bit_stream &bs);

	
	void verify();



};