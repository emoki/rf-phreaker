
#include "rf_phreaker/gsm_layer_3_library/neighbour_cell_description2.h"

neighbour_cell_description2::neighbour_cell_description2(format_of_information_elements format)	
								:cell_channel_description(format)
{


}

neighbour_cell_description2::~neighbour_cell_description2()
{

}

void neighbour_cell_description2::info_element_specific_decode()
{


	extract_bits(15,raw_bit_stream_, value_byte_position());

	determine_format_id2();

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


void neighbour_cell_description2::determine_format_id2()
{
	

if(ba_list_bits[128]==0 ) 
{
	 format_id = bit_map_0; 
	 return;
}
 
 if(ba_list_bits[128] == 1 && ba_list_bits[124] == 0 )
 {
	 format_id = range_1024;
	 range = 1024;
	 max_index = 16;
	 return;
 }

  if(ba_list_bits[128] == 1 && ba_list_bits[124] == 1 && ba_list_bits[123] == 0 && ba_list_bits[122] == 0)
  {
	  format_id = range_512;
	  range = 512;
	  max_index = 17;
      return;
  }

  if(ba_list_bits[128] == 1 && ba_list_bits[124] == 1 && ba_list_bits[123] == 0 && ba_list_bits[122] == 1)
  {
	  format_id = range_256;
	  range = 256;
	  max_index = 21;
      return;
  }

   if(ba_list_bits[128] == 1 && ba_list_bits[124] == 1 && ba_list_bits[123] == 1 && ba_list_bits[122] == 0)
   {
	  format_id = range_128;
	  range = 128;
	  max_index = 29;
	  return;
   }

    if(ba_list_bits[128] == 1 && ba_list_bits[124] == 1 && ba_list_bits[123] == 1 && ba_list_bits[122] == 1)
   {
	  format_id = variable_bit_map;
	  //range = 128;
	  //max_index = 29;
	  return;
   }

   format_id = reserved;

}




