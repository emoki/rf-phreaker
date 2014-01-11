#pragma once


#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"



class si_2_bis_rest_octets : public information_element_type_3
{


	
public:	

	si_2_bis_rest_octets(format_of_information_elements format);
   ~si_2_bis_rest_octets();

     void info_element_specific_decode();
	 void verify();


};