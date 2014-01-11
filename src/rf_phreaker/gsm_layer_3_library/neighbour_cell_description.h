#pragma once


#include "rf_phreaker/gsm_layer_3_library/cell_channel_description.h"

//Section 10.5.2.22, TS 44.018 

class neighbour_cell_description : public cell_channel_description
{


	
public:	

	neighbour_cell_description(format_of_information_elements format);
   ~neighbour_cell_description();
    void info_element_specific_decode();


};