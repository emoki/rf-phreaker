#pragma once


#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"



class frequency_algorithm
{

	static uint8_t power_of_two[32]; 

public:

	frequency_algorithm(uint32_t num, bool ext);

    ~frequency_algorithm();

	void extract_bits(uint32_t num_byte, std::vector<uint8_t> bit_stream, uint32_t start_index);
	
	void decode_frequency(uint32_t max_index, uint32_t range, bool extended);

	

	int32_t smod(int32_t dividend, int32_t divisor)
	{
		int32_t remainder = dividend % divisor;
		
		return(remainder < 0) ? (remainder +  divisor) : remainder;
	
	};

	
	bool extended;

	uint32_t ba_list_bits[136];

	uint32_t w[32], f[256];

	uint32_t num_ba, range, max_index;
	
};