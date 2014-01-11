
#pragma once


#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"


static const int32_t  si_2_rest_octects_value_bit_size = 32;


class utran_fdd_description_ter
{
public:
	 utran_fdd_description_ter();
	~utran_fdd_description_ter();

	uint32_t arfcn;
	uint32_t bandwidth;

};


class utran_tdd_description_ter
{

public:
	 utran_tdd_description_ter();
	~utran_tdd_description_ter();

	uint32_t arfcn;
	uint32_t bandwidth;

};



class si_2_ter_rest_octets : public information_element_type_3
{


	
public:	

	si_2_ter_rest_octets(format_of_information_elements format);
   ~si_2_ter_rest_octets();

     void info_element_specific_decode();

	 void verify();

	 void extract_bits();

	 void parse_bit_stream(gsm_bit_stream &bs);

	 void decode(gsm_bit_stream &bs);

	 uint8_t si_bits[32];

	 uint8_t si2_ter_mp_change_mark_;

	 uint8_t si2_ter_3g_change_mark_;

	 uint8_t si2_ter_index_;

	 uint8_t si2_ter_count_;

	 utran_fdd_description_ter utran_fdd_description_;

	 utran_tdd_description_ter utran_tdd_description_;


};