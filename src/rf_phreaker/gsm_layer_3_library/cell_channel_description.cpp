
#include "rf_phreaker/gsm_layer_3_library/cell_channel_description.h"



cell_channel_description::cell_channel_description(format_of_information_elements format)
							: information_element_type_3(format, ie_lenght),
							  frequency_algorithm(0, false)
{
	
};

cell_channel_description::~cell_channel_description()
{

};


void cell_channel_description::determine_format_id()
{
	

if(ba_list_bits[128]==0 && ba_list_bits[127] == 0) 
{
	 format_id = bit_map_0; 
	 return;
}
 
 if(ba_list_bits[128] == 1 && ba_list_bits[127] == 0 && ba_list_bits[124] == 0)
 {
	 format_id = range_1024;
	 range = 1024;
	 max_index = 16;
	 return;
 }

  if(ba_list_bits[128] == 1 && ba_list_bits[127] == 0 && ba_list_bits[124] == 1 && ba_list_bits[123] == 0 && ba_list_bits[122] == 0)
  {
	  format_id = range_512;
	  range = 512;
	  max_index = 17;
      return;
  }

  if(ba_list_bits[128] == 1 && ba_list_bits[127] == 0 && ba_list_bits[124] == 1 && ba_list_bits[123] == 0 && ba_list_bits[122] == 1)
  {
	  format_id = range_256;
	  range = 256;
	  max_index = 21;
      return;
  }

   if(ba_list_bits[128] == 1 && ba_list_bits[127] == 0 && ba_list_bits[124] == 1 && ba_list_bits[123] == 1 && ba_list_bits[122] == 0)
   {
	  format_id = range_128;
	  range = 128;
	  max_index = 29;
	  return;
   }

    if(ba_list_bits[128] == 1 && ba_list_bits[127] == 0 && ba_list_bits[124] == 1 && ba_list_bits[123] == 1 && ba_list_bits[122] == 1)
   {
	  format_id = variable_bit_map;
	  //range = 128;
	  //max_index = 29;
	  return;
   }

   format_id = reserved;

}



void cell_channel_description::determine_frequency_bit_map_0()
{
	if(!extended)
	num_ba = 0;

	for(uint8_t ii = 1; ii < 125; ii++)
	{
	 if(ba_list_bits[ii])
		 f[num_ba++] = ii;

	}

}

void cell_channel_description::determine_frequency_range_1024()
{
	
	int32_t offset = 1, range = 1024;

	for(uint8_t ii = 16; ii <=1; ii++)
	{
		if( ii == 16)
		{
			w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5);
			offset = offset + 6;
		}

		if((ii<=15) && (ii>=8))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5)
										 + (ba_list_bits[offset+6] << 6);
		  offset = offset + 7;		
		
		}

		if((ii<=7) && (ii>=4))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5)
										 + (ba_list_bits[offset+6] << 6)
									     + (ba_list_bits[offset+7] << 7);
		  offset = offset + 8;		
		
		}

		if((ii<=3) && (ii>=2))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5)
										 + (ba_list_bits[offset+6] << 6)
									     + (ba_list_bits[offset+7] << 7)
										 + (ba_list_bits[offset+8] << 8);
		  offset = offset + 9;		
		
		}

		if(ii==1)
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5)
										 + (ba_list_bits[offset+6] << 6)
									     + (ba_list_bits[offset+7] << 7)
										 + (ba_list_bits[offset+8] << 8)
										 + (ba_list_bits[offset+9] << 9);
		  	
		
		}	
	
	
	}//for

//Map W values to Frequency - F values
//Table 10.5.2.13.3.1, TS 44.018



decode_frequency(max_index, range, extended);
	
}

void cell_channel_description::determine_frequency_range_512()
{
 uint8_t offset = 1;
 
for(uint8_t ii = 17; ii <=1; ii++)
	{
		if( ii == 17 || ii == 16)
		{
			w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4);
										 
			offset = offset + 5;
		}

		if((ii<=15) && (ii>=8))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5);
									
		  offset = offset + 6;		
		
		}

		if((ii<=7) && (ii>=4))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5)
										 + (ba_list_bits[offset+1] << 6);
									     
		  offset = offset + 7;		
		
		}

		if((ii<=3) && (ii>=2))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5)
										 + (ba_list_bits[offset+1] << 6)
									     + (ba_list_bits[offset+1] << 7);
										 
		  offset = offset + 8;		
		
		}

		if(ii==1)
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5)
										 + (ba_list_bits[offset+1] << 6)
									     + (ba_list_bits[offset+1] << 7)
										 + (ba_list_bits[offset+1] << 8);

		  offset = offset + 9;
									
		  	
		
		}	
	
	
	}//for

w[0] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5)
										 + (ba_list_bits[offset+1] << 6)
									     + (ba_list_bits[offset+1] << 7)
										 + (ba_list_bits[offset+1] << 8);


//Map W values to Frequency - F values
//Table 10.5.2.13.4.1, TS 44.018


decode_frequency(max_index, range, extended);

}


void cell_channel_description::determine_frequency_range_256()
{
uint8_t offset = 2;
 
for(uint8_t ii = 21; ii >=1; ii--)
	{
		if((ii<=21) && (ii>=16))
		{
			w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3);
										 
										 
			offset = offset + 4;
		}

		if((ii<=15) && (ii>=8))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4);
										 
		  offset = offset + 5;		
		
		}

		if((ii<=7) && (ii>=4))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5);
										
									     
		  offset = offset + 6;		
		
		}

		if((ii<=3) && (ii>=2))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5)
										 + (ba_list_bits[offset+6] << 6);
									    
										 
		  offset = offset + 7;		
		
		}

		if(ii==1)
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5)
										 + (ba_list_bits[offset+6] << 6)
									     + (ba_list_bits[offset+7] << 7);
										 
		  offset = offset + 8;
									
		  	
		
		}	
	
	
	}//for

w[0] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+2] << 2)
										 + (ba_list_bits[offset+3] << 3)
										 + (ba_list_bits[offset+4] << 4)
										 + (ba_list_bits[offset+5] << 5)
										 + (ba_list_bits[offset+6] << 6)
									     + (ba_list_bits[offset+7] << 7)
										 + (ba_list_bits[offset+8] << 8)
                                         + (ba_list_bits[offset+9] << 9);


decode_frequency(max_index, range, extended);

}

void cell_channel_description::determine_frequency_range_128()
{

uint8_t offset = 1;
 
for(uint8_t ii = max_index; ii <=1; ii++)
	{
		if( ii <= 31 || ii >= 16)
		{
			w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2);
										
			offset = offset + 3;
		}

		if((ii<=15) && (ii>=8))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3);
										 
									
		  offset = offset + 4;		
		
		}

		if((ii<=7) && (ii>=4))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4);
										 
									     
		  offset = offset + 5;		
		
		}

		if((ii<=3) && (ii>=2))
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5);
										 
										 
		  offset = offset + 6;		
		
		}

		if(ii==1)
		{
		  w[ii] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5)
										 + (ba_list_bits[offset+1] << 6);
									   
		  offset = offset + 9;
									
		  	
		
		}	
	
	
	}//for

w[0] = ba_list_bits[offset] + (ba_list_bits[offset+1] << 1)
			                             + (ba_list_bits[offset+1] << 2)
										 + (ba_list_bits[offset+1] << 3)
										 + (ba_list_bits[offset+1] << 4)
										 + (ba_list_bits[offset+1] << 5)
										 + (ba_list_bits[offset+1] << 6)
									     + (ba_list_bits[offset+1] << 7)
										 + (ba_list_bits[offset+1] << 8);

decode_frequency(max_index, range, extended);

}

void cell_channel_description::determine_frequency_variable_bit_map()
{

	w[0] = (ba_list_bits[121] << 9) + (ba_list_bits[120] << 8)
		                            + (ba_list_bits[119] << 7)
									+ (ba_list_bits[118] << 6)
									+ (ba_list_bits[117] << 5)
									+ (ba_list_bits[116] << 4)
									+ (ba_list_bits[115] << 3)
									+ (ba_list_bits[114] << 2)
									+ (ba_list_bits[113] << 1)
									+ (ba_list_bits[112]);

	
	

	f[0] = w[0];

	for(uint8_t ii = 111; ii >=1; ii--)
	{
	 if(ba_list_bits[ii])
	 {
		 num_ba++;

		 ba_list_bits[num_ba] = ii;
		 
	     f[num_ba] = w[0] + 111 - ii + 1;
	 }

	}

}

void cell_channel_description::info_element_specific_decode()
{


	extract_bits(15,raw_bit_stream_, value_byte_position());

	determine_format_id();

	extended = false;

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


void cell_channel_description::verify()
{



}