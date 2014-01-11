#pragma once


#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"

#include "rf_phreaker/gsm_layer_3_library/frequency_algorithm.h"



class cell_channel_description : public information_element_type_3 ,
	                             public frequency_algorithm
{


static const uint32_t ie_lenght = 128;

 


protected:
	enum format_notation
	{
		bit_map_0,
		range_1024,
		range_512,
		range_256,
		range_128,
		variable_bit_map,
		reserved	
	};



	format_notation format_id;

	

	void determine_format_id();

	void determine_frequency_bit_map_0();

	void determine_frequency_range_1024();

	void determine_frequency_range_512();

	void determine_frequency_range_256();

	void determine_frequency_range_128();

	void determine_frequency_variable_bit_map();




public:
	cell_channel_description(format_of_information_elements format);
   ~cell_channel_description();

   virtual void info_element_specific_decode();

   void verify();





};