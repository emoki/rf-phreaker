
#include "rf_phreaker/gsm_layer_3_library/si_2_quarter_rest_octets.h"


measurement_parameter_desription::measurement_parameter_desription()
{
}

measurement_parameter_desription::~measurement_parameter_desription()
{

}

void measurement_parameter_desription::decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	if (data_bits[origin_offset])
	{
		origin_offset++;
		// decode paramters
		origin_offset = origin_offset + 3;
	}
	else
	{
		origin_offset++;
	}


}

gprs_real_time_difference_description::gprs_real_time_difference_description()
{

}

gprs_real_time_difference_description::~gprs_real_time_difference_description()
{

}


void gprs_real_time_difference_description::decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	uint8_t delimiter; 

	if (data_bits[origin_offset]) // check gprs_real_time_difference_description is present
	{
		// decode paramters
		origin_offset++;

		if (data_bits[origin_offset]) //Check if BA_Index_start_RTD and RTD6 is present
		{
			origin_offset++;
			if (data_bits[origin_offset]) // BA_Index_start_RTD is present
			{
				// Decode BA_Index_start_RTD
				origin_offset = origin_offset + 5;
			
			}
	

			origin_offset++;

			//Decode RTD6

			delimiter = 0;

			while(delimiter == 0 )
			{

				delimiter = data_bits[origin_offset];

				origin_offset = origin_offset + 6 + 1;			
			
			}

			

		}
		else
		{
			origin_offset++;		
		}

		

		
		if (data_bits[origin_offset]) //Check if BA_Index_start_RTD and RTD12 is present
		{
			origin_offset++;
			if (data_bits[origin_offset]) // BA_Index_start_RTD is present
			{
				// Decode BA_Index_start_RTD
				origin_offset = origin_offset + 5;
			
			}
	

			origin_offset++;

			//Decode RTD12

			delimiter = 0;

			while(delimiter == 0 )
			{

				delimiter = data_bits[origin_offset];

				origin_offset = origin_offset + 12 + 1;			
			
			}	

			

		}
		else
		{
			origin_offset++;		
		}		
		


	}
	else
	{
		origin_offset++;

	}	
	

}

gprs_bsic_description::gprs_bsic_description()
{

}


gprs_bsic_description::~gprs_bsic_description()
{

}


void gprs_bsic_description::decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	uint32_t number_remaining_bsic = 0;

	if (data_bits[origin_offset]) // Check if gprs_bsic_description is present
	{
		// Check if BA_Index_Start_BSIC is present
		origin_offset++;

		if  (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 5;
		
		}

		origin_offset++;

		// Decode BSIC
		origin_offset = origin_offset + 6;

		// Decode Number Remaining BSIC bit
		number_remaining_bsic = data_bits[origin_offset] + (data_bits[origin_offset + 1] >> 1)
														 + (data_bits[origin_offset + 2] >> 2)
														 + (data_bits[origin_offset + 3] >> 3)
														 + (data_bits[origin_offset + 4] >> 4)
														 + (data_bits[origin_offset + 5] >> 5)
														 + (data_bits[origin_offset + 6] >> 6) ;

		origin_offset = origin_offset + 7;


		//Decode Frequency Scrolling and BSIC
		origin_offset = origin_offset + (1 + 6 ) * number_remaining_bsic;

	}
	
	origin_offset = origin_offset + 1;

}

gprs_report_priority_description::gprs_report_priority_description()
{

}

gprs_report_priority_description::~gprs_report_priority_description()
{

}

void gprs_report_priority_description::decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	uint32_t number_cells = 0;

	if (data_bits[origin_offset])
	{
		origin_offset++;

		// Decode number cells
		number_cells = data_bits[origin_offset] + (data_bits[origin_offset + 1] >> 1 )
														 + (data_bits[origin_offset + 2] >> 2)
														 + (data_bits[origin_offset + 3] >> 3)
														 + (data_bits[origin_offset + 4] >> 4)
														 + (data_bits[origin_offset + 5] >> 5)
														 + (data_bits[origin_offset + 6] >> 6) ;

		origin_offset = origin_offset + 7;

		// Decode rep_priority
		origin_offset = origin_offset + number_cells;



	}
	
	origin_offset = origin_offset + 1;


}

gprs_measurement_paramters_description::gprs_measurement_paramters_description()
{

}

gprs_measurement_paramters_description::~gprs_measurement_paramters_description()
{

}

void gprs_measurement_paramters_description::decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	if (data_bits[origin_offset]) // Check if gprs_measurement_paramters_description is present
	{
		origin_offset++;

		// decode report type
		origin_offset++;

		// decode reporting rate
		origin_offset++;

		//Decode Invalid BSIC reporting 
		origin_offset++;

		//check for multiband reporting

		if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 2;
		
		}
		origin_offset++;

		//check for serving band reporting

		if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 2;
		
		}
		origin_offset++;

		//check for 900 reporting

		if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 3 + 3; // 3 bit reporting offset and 3 bits reporting threshold
		
		}
		origin_offset++;

		//check for 1800 reporting

			if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 3 + 3; // 3 bit reporting offset and 3 bits reporting threshold
		
		}
		origin_offset++;

		//check for 400 reporting

			if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 3 + 3; // 3 bit reporting offset and 3 bits reporting threshold
		
		}
		origin_offset++;

		//check for 1900 reporting

			if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 3 + 3; // 3 bit reporting offset and 3 bits reporting threshold
		
		}
		origin_offset++;

		//check for 850 reporting

			if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 3 + 3; // 3 bit reporting offset and 3 bits reporting threshold
		
		}

	}
	
	origin_offset = origin_offset + 1;

}

nc_measurement_parameters::nc_measurement_parameters()
{

}

nc_measurement_parameters::~nc_measurement_parameters()
{

}

void nc_measurement_parameters::decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	if (data_bits[origin_offset]) // check if nc_measurement_parameters is present
	{
		origin_offset++;

		//Decode Network control order

		origin_offset = origin_offset + 2;

		//Check if nc_non_drx_period , nc_reporting_period_i, nc_reporting_period_t is present 

		if (data_bits[origin_offset])
		{
			origin_offset = origin_offset + 3 // nc_non_drx_period
										  + 3 // nc_reporting_period_i
										  + 3; // nc_reporting_period_t		
		}

		origin_offset++;



	}
	
	origin_offset = origin_offset + 1;


}

extension_si_2_q::extension_si_2_q()
{

}

extension_si_2_q::~extension_si_2_q()
{

}

void extension_si_2_q:: decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	uint32_t extension_length = 0;
	
	if (data_bits[origin_offset]) // check if nc_measurement_parameters is present
	{
		origin_offset++;

		//decode extension length
		extension_length =  data_bits[origin_offset] + (data_bits[origin_offset + 1] >> 1)
														 + (data_bits[origin_offset + 2] >> 2)
														 + (data_bits[origin_offset + 3] >> 3)
														 + (data_bits[origin_offset + 4] >> 4)
														 + (data_bits[origin_offset + 5] >> 5)
														 + (data_bits[origin_offset + 6] >> 6) 
														 + (data_bits[origin_offset + 6] >> 7) ;

		origin_offset = origin_offset + 8;

		//bit val

		origin_offset = origin_offset + extension_length;

		//check if 
	}

	origin_offset = origin_offset + 1;

}

//FDD
uint8_t repeated_neighbour_cells::p[32] = {0, 10, 19, 28, 36, 44, 52, 60, 67, 74, 81, 88, 95, 102, 109, 116, 122, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

//TDD
uint8_t repeated_neighbour_cells::q[32] = {0, 9, 17, 25, 32, 39, 46, 53, 59, 65, 71, 77, 83, 89, 95, 101, 106, 111, 116, 121, 126, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t repeated_neighbour_cells::power_of_two[32] =  {1,1,2,2,4,4,4,4,8,8,8,8,8,8,8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,32};

repeated_neighbour_cells::repeated_neighbour_cells()
{

}

repeated_neighbour_cells::~repeated_neighbour_cells()
{

}



void repeated_neighbour_cells::decode_cell_info(uint32_t duplex_mode)
{
	uint32_t index, n;

	uint32_t range;

	uint8_t offset = 0;

	w[0] = 0;

	


	//extract w[x] values

if(duplex_mode) // duplex_mode == 1 TDD Mode
{
	range = 512;

	for(uint32_t ii = 1; ii <= nr_of_cells ; ii++)
	{

		if(ii==1)
		{
		  w[ii] = cell_information[offset] + (cell_information[offset+1] << 1)
			                               + (cell_information[offset+1] << 2)
										   + (cell_information[offset+1] << 3)
										   + (cell_information[offset+1] << 4)
										   + (cell_information[offset+1] << 5)
										   + (cell_information[offset+1] << 6)
									       + (cell_information[offset+1] << 7)
										   + (cell_information[offset+1] << 8);

		  offset = offset + 9;								
		  	
		
		}

		if((ii<=3) && (ii>=2))
		{
		  w[ii] = cell_information[offset] + (cell_information[offset+1] << 1)
			                               + (cell_information[offset+1] << 2)
										   + (cell_information[offset+1] << 3)
										   + (cell_information[offset+1] << 4)
										   + (cell_information[offset+1] << 5)
										   + (cell_information[offset+1] << 6)
									       + (cell_information[offset+1] << 7);
										 
		  offset = offset + 8;		
		
		}

		if((ii<=7) && (ii>=4))
		{
		  w[ii] = cell_information[offset] + (cell_information[offset+1] << 1)
			                               + (cell_information[offset+1] << 2)
										   + (cell_information[offset+1] << 3)
										   + (cell_information[offset+1] << 4)
										   + (cell_information[offset+1] << 5)
										   + (cell_information[offset+1] << 6);
									     
		  offset = offset + 7;		
		
		}

		if((ii<=15) && (ii>=8))
		{
		  w[ii] = cell_information[offset] + (cell_information[offset+1] << 1)
			                               + (cell_information[offset+1] << 2)
										   + (cell_information[offset+1] << 3)
										   + (cell_information[offset+1] << 4)
										   + (cell_information[offset+1] << 5);
									
		  offset = offset + 6;		
		
		}

		if( ii == 17 || ii == 16)
		{
			w[ii] = cell_information[offset] + (cell_information[offset+1] << 1)
			                                 + (cell_information[offset+1] << 2)
										     + (cell_information[offset+1] << 3)
										     + (cell_information[offset+1] << 4);
										 
			offset = offset + 5;
		}
	
	
	
	
	}
}
else
{

 range = 1024;

for(uint8_t ii = 1; ii <= nr_of_cells; ii++)
	{
		if( ii == 16)
		{
			w[ii] = (cell_information[offset] << 5) + (cell_information[offset+1] << 4)
			                             + (cell_information[offset+2] << 3)
										 + (cell_information[offset+3] << 2)
										 + (cell_information[offset+4] << 1)
										 + (cell_information[offset+5]);
			offset = offset + 6;
		}

		if((ii<=15) && (ii>=8))
		{
		  w[ii] = (cell_information[offset] << 6) + (cell_information[offset+1] << 5)
			                             + (cell_information[offset+2] << 4)
										 + (cell_information[offset+3] << 3)
										 + (cell_information[offset+4] << 2)
										 + (cell_information[offset+5] << 1)
										 + (cell_information[offset+6] );
		  offset = offset + 7;		
		
		}

		if((ii<=7) && (ii>=4))
		{
		  w[ii] = (cell_information[offset] << 7) + (cell_information[offset+1] << 6)
			                             + (cell_information[offset+2] << 5)
										 + (cell_information[offset+3] << 4)
										 + (cell_information[offset+4] << 3)
										 + (cell_information[offset+5] << 2)
										 + (cell_information[offset+6] << 1)
									     + (cell_information[offset+7]);
		  offset = offset + 8;		
		
		}

		if((ii<=3) && (ii>=2))
		{
		  w[ii] = (cell_information[offset] << 8) + (cell_information[offset+1] << 7)
			                             + (cell_information[offset+2] << 6)
										 + (cell_information[offset+3] << 5)
										 + (cell_information[offset+4] << 4)
										 + (cell_information[offset+5] << 3)
										 + (cell_information[offset+6] << 2)
									     + (cell_information[offset+7] << 1)
										 + (cell_information[offset+8] );
		  offset = offset + 9;		
		
		}

		if(ii==1)
		{
		  w[ii] = (cell_information[offset] << 9) + (cell_information[offset+1] << 8)
			                             + (cell_information[offset+2] << 7)
										 + (cell_information[offset+3] << 6)
										 + (cell_information[offset+4] << 5)
										 + (cell_information[offset+5] << 4)
										 + (cell_information[offset+6] << 3)
									     + (cell_information[offset+7] << 2)
										 + (cell_information[offset+8] << 1)
										 + (cell_information[offset+9] );

		  offset = offset + 10;
		  	
		
		}	
	
	
	}//for

}



f[0] = w[0];

	for(uint32_t k = 1; k <=nr_of_cells; k++)
	{
 
		uint32_t j;

		index = k;

		j = power_of_two[index];

		n = w[index];

		if(n == 0) return;

		while(index > 1)
		{
			if( 2*index < 3*j)
			{
				index = index - j / 2;

				n = (n + w[index] + range/j -2) % ((2 * range)/j - 1) + 1;
		
			}
			else
			{
				index = index - j ;

				n = (n + w[index] + (2*range)/j -2) % (2 * range/j - 1) + 1;		
		
			}

			j = j/2;	
	
	
		}

	
	f[k] = (w[0] + n ) % 1024;

	if(f[k] < 0 )
		f[k] = f[k] + 1024;

	}


}


three_g_neighbour_cell_description::three_g_neighbour_cell_description()
{

}

three_g_neighbour_cell_description::~three_g_neighbour_cell_description()
{

}

void three_g_neighbour_cell_description::decode(uint8_t *data_bits, uint8_t &origin_offset)
{
	uint8_t cell_count, num_cell_info_bits = 0, delimiter = 0;


	if (data_bits[origin_offset]) // check if three_g_neighbour_cell_description is present
	{
		origin_offset++;

		//Check if Index_start_3G is present
		if (data_bits[origin_offset])
		{			
			
		    origin_offset++;

		    // Decode Index_start_3G
			index_start_3g = (data_bits[origin_offset] << 6) + (data_bits[origin_offset + 1] << 5)
														     + (data_bits[origin_offset + 2] << 4)
														     + (data_bits[origin_offset + 3] << 3)
														     + (data_bits[origin_offset + 4] << 2)
														     + (data_bits[origin_offset + 5] << 1)
														     + (data_bits[origin_offset + 6] );


			origin_offset = origin_offset + 7;													 


		
		}
		else
		{
			origin_offset++;
		
		}

	

		//Check if Absolute Index Start EMR is present
		if (data_bits[origin_offset])
		{
			 origin_offset++;
			
			//Decode Absolute Index Start EMR 
			absolute_index_start_emr = data_bits[origin_offset]  + (data_bits[origin_offset + 1] >> 1)
																   + (data_bits[origin_offset + 2] >> 2)
																   + (data_bits[origin_offset + 3] >> 3)
																   + (data_bits[origin_offset + 4] >> 4)
																   + (data_bits[origin_offset + 5] >> 5)
																   + (data_bits[origin_offset + 6] >> 6);

			origin_offset = origin_offset + 7;		
		}
		else
		{			
			origin_offset++;		
		}


		//Check if UTRAN fdd description is present
		if (data_bits[origin_offset])
		{
			origin_offset++;

			if (data_bits[origin_offset]) //Check Bandwidth
			{
				origin_offset++;
				
				utran_fdd_description.bandwidth =  data_bits[origin_offset] + (data_bits[origin_offset + 1] >> 1)
					                                                            + (data_bits[origin_offset + 2] >> 2);
				origin_offset = origin_offset + 3;
			
			}
			else
			{
				origin_offset++;			
			}

			

			delimiter = data_bits[origin_offset];

			cell_count = 0;

			//Decode Repeated Neighbour cells

			while(delimiter == 1)
			{
				//Decode UTRAN neighbour cells

				origin_offset++;

				origin_offset++ ; // Default value Zero

				

				utran_fdd_description.repeated_utran_neighbour_cells_[cell_count].arfcn = (data_bits[origin_offset] << 13) + (data_bits[origin_offset + 1] << 12)
																											+ (data_bits[origin_offset + 2] << 11)	
																											+ (data_bits[origin_offset + 3] << 10)
																											+ (data_bits[origin_offset + 4] << 9)
																											+ (data_bits[origin_offset + 5] << 8)
																											+ (data_bits[origin_offset + 6] << 7)
																											+ (data_bits[origin_offset + 7] << 6)
																											+ (data_bits[origin_offset + 8] << 5)
																											+ (data_bits[origin_offset + 9] << 4)
																											+ (data_bits[origin_offset + 10] << 3)
																											+ (data_bits[origin_offset + 11] << 2)
																											+ (data_bits[origin_offset + 12] << 1)
																											+ (data_bits[origin_offset + 13]);

				origin_offset = origin_offset + 14;

				utran_fdd_description.repeated_utran_neighbour_cells_[cell_count].indico = data_bits[origin_offset];

				origin_offset++;

				utran_fdd_description.repeated_utran_neighbour_cells_[cell_count].nr_of_cells = (data_bits[origin_offset] << 4) + (data_bits[origin_offset + 1] << 3)
																													             + (data_bits[origin_offset + 2] << 2)	
																												                 + (data_bits[origin_offset + 3] << 1)
																												                 + (data_bits[origin_offset + 4]);

				origin_offset = origin_offset + 5;

				num_cell_info_bits = utran_fdd_description.repeated_utran_neighbour_cells_[cell_count].p[utran_fdd_description.repeated_utran_neighbour_cells_[cell_count].nr_of_cells];


				for(uint8_t ii = 0 ; ii < num_cell_info_bits ; ii++ )
				{
					utran_fdd_description.repeated_utran_neighbour_cells_[cell_count].cell_information[ii] = data_bits[origin_offset + ii];					
				
				
				}

				//decode the cell info
				utran_fdd_description.repeated_utran_neighbour_cells_[cell_count].decode_cell_info(duplex_mode_fdd);




				origin_offset = origin_offset + num_cell_info_bits;


				delimiter = data_bits[origin_offset];

				
			}//while 



		}
		else
		{
			origin_offset++;		
		}
	

		//Check if UTRAN tdd description is present
		if (data_bits[origin_offset])
		{
			origin_offset++;

			if (data_bits[origin_offset]) //Check Bandwidth
			{
				origin_offset++;
				
				utran_tdd_description.bandwidth =  data_bits[origin_offset] + (data_bits[origin_offset + 1] >> 1)
					                                                            + (data_bits[origin_offset + 2] >> 2);
				origin_offset = origin_offset + 3;
			
			}
			else
			{
				origin_offset++;			
			}

			

			delimiter = data_bits[origin_offset];

			cell_count = 0;

			//Decode Repeated Neighbour cells

			while(delimiter == 1)
			{
				//Decode UTRAN neighbour cells

				origin_offset++;

				origin_offset++ ; // Default value Zero

				

				utran_tdd_description.repeated_utran_neighbour_cells_[cell_count].arfcn = (data_bits[origin_offset] << 13) + (data_bits[origin_offset + 1] << 12)
																											+ (data_bits[origin_offset + 2] << 11)	
																											+ (data_bits[origin_offset + 3] << 10)
																											+ (data_bits[origin_offset + 4] << 9)
																											+ (data_bits[origin_offset + 5] << 8)
																											+ (data_bits[origin_offset + 6] << 7)
																											+ (data_bits[origin_offset + 7] << 6)
																											+ (data_bits[origin_offset + 8] << 5)
																											+ (data_bits[origin_offset + 9] << 4)
																											+ (data_bits[origin_offset + 10] << 3)
																											+ (data_bits[origin_offset + 11] << 2)
																											+ (data_bits[origin_offset + 12] << 1)
																											+ (data_bits[origin_offset + 13]);

				origin_offset = origin_offset + 14;

				utran_tdd_description.repeated_utran_neighbour_cells_[cell_count].indico = data_bits[origin_offset];

				origin_offset++;

				utran_tdd_description.repeated_utran_neighbour_cells_[cell_count].nr_of_cells = (data_bits[origin_offset] << 4) + (data_bits[origin_offset + 1] << 3)
																													             + (data_bits[origin_offset + 2] << 2)	
																												                 + (data_bits[origin_offset + 3] << 1)
																												                 + (data_bits[origin_offset + 4]);

				origin_offset = origin_offset + 5;

				num_cell_info_bits = utran_tdd_description.repeated_utran_neighbour_cells_[cell_count].q[utran_tdd_description.repeated_utran_neighbour_cells_[cell_count].nr_of_cells];


				for(uint8_t ii = 0 ; ii < num_cell_info_bits ; ii++ )
				{
					utran_tdd_description.repeated_utran_neighbour_cells_[cell_count].cell_information[ii] = data_bits[origin_offset + ii];					
				
				
				}

				//decode the cell info
				utran_tdd_description.repeated_utran_neighbour_cells_[cell_count].decode_cell_info(duplex_mode_tdd);


				origin_offset = origin_offset + num_cell_info_bits;


				delimiter = data_bits[origin_offset];

				
			}//while 


		}
		else
		{
			origin_offset++;
		}		

		
	}
	else
	{
		origin_offset++;
	}



}

si_2_quarter_rest_octets::si_2_quarter_rest_octets(format_of_information_elements format)
	                      : information_element_type_3(format, si_2_quarter_rest_octects_bit_size),
						   offset(0),
						   si_octect_size(20)
{

}

si_2_quarter_rest_octets::~si_2_quarter_rest_octets()
{

}

void si_2_quarter_rest_octets::extract_bits(uint8_t *src, uint8_t *dest, uint8_t num_octects)
{
	uint8_t data = 0, index = 0;
 
 for(int8_t ii = 0; ii <= num_octects;ii++)
 {
	data = src[value_byte_position()+ii];
	
	for(uint8_t bit_pos = 0; bit_pos <8; bit_pos++)
	{		
		dest[index + 7 - bit_pos] = (data>>bit_pos) & 0x1;		

		

	}//loop-bit_pos

	index = index + 8;

 }//loop-i

}

void si_2_quarter_rest_octets::info_element_specific_decode()
{

	offset = 0;

	extract_bits(&raw_bit_stream_[0], si_bits, si_octect_size);

	ba_ind =  si_bits[0];

	three_g_ba_ind = si_bits[1];

	mp_change_mark = si_bits[2];

	offset = offset + 3 + 4 + 4; //skiping SI2quarter_index and SI2quarter_Count
	
	//Measurement parameter description

	measurement_parameter_desription_.decode(si_bits, offset);

	//GPRS Real time Difference Description

	gprs_real_time_difference_description_.decode(si_bits, offset);

	//GPRS Basic Description
	gprs_bsic_description_.decode(si_bits, offset);


	//GPRS Report Priority Description
	gprs_report_priority_description_.decode(si_bits, offset);


	//GPRS Measurement parameter description
	gprs_measurement_paramters_description_.decode(si_bits, offset);

	//NC Measurement parameter
	nc_measurement_parameters_.decode(si_bits, offset);

	//extension length

	extension_si_2_q_.decode(si_bits, offset);

	//3G Neighbourr cell description
	three_g_neighbour_cell_description_.decode(si_bits, offset);


}

void si_2_quarter_rest_octets::parse_bit_stream(gsm_bit_stream &bs)
{
	

	bits_to_consume_ = bs.num_bits_in_bit_stream() - bs.num_bits_unused_in_bit_stream() - bs.bits_consumed_thus_far();
		
	calculate_skip_bits(bs);

	copy_to_raw_bit_stream(bs);

	bs.consume_more_bits(bits_to_consume_);



}

void si_2_quarter_rest_octets::decode(gsm_bit_stream &bs)
{
	parse_bit_stream(bs);

	info_element_specific_decode();
}

void si_2_quarter_rest_octets::verify()
{

}
