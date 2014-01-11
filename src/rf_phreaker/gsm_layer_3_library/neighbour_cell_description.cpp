
#include "rf_phreaker/gsm_layer_3_library/neighbour_cell_description.h"

neighbour_cell_description::neighbour_cell_description(format_of_information_elements format)	
								:cell_channel_description(format)
{


}

neighbour_cell_description::~neighbour_cell_description()
{

}

void neighbour_cell_description::info_element_specific_decode()
{


	extract_bits(15,raw_bit_stream_, value_byte_position());

	determine_format_id();

	extended = false;

	if (ba_list_bits[126] == 1)
		extended = true;

	switch (format_id)
	{
		case bit_map_0:
			determine_frequency_bit_map_0();
			break;

		case range_1024:
			determine_frequency_range_1024();
			break;

		case range_512:
			determine_frequency_range_512();
			break;

		case range_256:
			determine_frequency_range_256();
			break;

		case range_128:
			determine_frequency_range_128();
			break;

		case variable_bit_map:
			determine_frequency_variable_bit_map();
			break;

		default:
			break;
	
	
	
	}


}