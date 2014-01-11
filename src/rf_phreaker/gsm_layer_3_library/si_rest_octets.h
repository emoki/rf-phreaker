#pragma once

#include <stdint.h>
#include <vector>

class utran_description
{

public:

	utran_description();
	~utran_description();

	uint32_t arfcn;
	uint32_t bandwidth;

};

class three_g_measurement_parameter_desription
{

public:
	three_g_measurement_parameter_desription();
	~three_g_measurement_parameter_desription();

	uint8_t q_search_i;
	uint8_t fdd_q_offset;
	uint8_t fdd_q_min;
	uint8_t tdd_q_offset;




};

class three_g_additional_measurement_parameter_desription
{

public:
	three_g_additional_measurement_parameter_desription();
	~three_g_additional_measurement_parameter_desription();

	uint8_t fdd_q_min_offset;
	uint8_t fdd_rscp_min;

	

		 


};