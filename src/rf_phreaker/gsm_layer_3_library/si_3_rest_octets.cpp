#include "rf_phreaker/gsm_layer_3_library/si_3_rest_octets.h"


optional_selection_parameters::optional_selection_parameters()
{

}

optional_selection_parameters::~optional_selection_parameters()
{

}

optional_power_offset::optional_power_offset()
{

}

optional_power_offset::~optional_power_offset()
{

}

scheduling_if_where::scheduling_if_where()
{

}

scheduling_if_where::~scheduling_if_where()
{

}

gprs_indicator::gprs_indicator()
{

}

gprs_indicator::~gprs_indicator()
{

}

si_3_rest_octets::si_3_rest_octets(format_of_information_elements format)
								: information_element_type_3(format, si_3_rest_octects_value_bit_size)
{

}

si_3_rest_octets::~si_3_rest_octets()
{

}

void si_3_rest_octets::extract_bits()
{

 uint8_t data = 0, index = 1;
 
 for(int8_t ii = bits_to_consume_/8; ii >= 0;ii--)
 {
	data = raw_bit_stream_[value_byte_position()+ii];
	
	for(uint8_t bit_pos = 0; bit_pos <8; bit_pos++)
	{		
		si_bits[index++] = (data>>bit_pos) & 0x1;		

	}//loop-bit_pos

 }//loop-ii



}


void si_3_rest_octets::info_element_specific_decode()
{
	uint8_t orig_offset = 0;
	
	extract_bits();

	//decode optional selection parameters

	orig_offset++ ; // skip one bit L/H

	optional_selection_parameters_.cbq = si_bits[orig_offset];

	orig_offset++;

	optional_selection_parameters_.cell_reselect_offset = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
																			   + (si_bits[orig_offset + 2] << 2) 
																			   + (si_bits[orig_offset + 3] << 3) 
																			   + (si_bits[orig_offset + 4] << 4) 
																			   + (si_bits[orig_offset + 5] << 5);

	orig_offset = orig_offset + 6;

	optional_selection_parameters_.temporary_offset = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
																		   + (si_bits[orig_offset + 2] << 2);

	orig_offset = orig_offset + 3;

	optional_selection_parameters_.penalty_time = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
																	   + (si_bits[orig_offset + 2] << 2) 
																	   + (si_bits[orig_offset + 3] << 3) 
																	   + (si_bits[orig_offset + 4] << 4); 

	orig_offset = orig_offset + 5;

	//decode optional power offset

	orig_offset++ ; // skip one bit L/H

	optional_power_offset_.power_offset = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1);

	orig_offset = orig_offset + 2;

	//decode system information 2ter indicator

	orig_offset++ ; // skip one bit L/H

	//decode early classmark sending control

	orig_offset++ ; // skip one bit L/H

	//deocode scheduling if and where

	orig_offset++ ; // skip one bit L/H

	scheduling_if_where_.wheres =  si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
														+ (si_bits[orig_offset + 2] << 2);

	orig_offset = orig_offset + 3;

	//Decode GPRS indicator

	orig_offset++ ; // skip one bit L/H

	gprs_indicator_.ra_color = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
													+ (si_bits[orig_offset + 2] << 2);

	orig_offset = orig_offset + 3;

	gprs_indicator_.si_3_position = si_bits[orig_offset];

	orig_offset++;

	//decode 3g early classmark sending restriction

	orig_offset++ ; // skip one bit L/H

	//decode SI2 quarter indicator

	si2_quarter_indicator_ = si_bits[orig_offset];

	orig_offset++ ;

	//decode lu indicator

    lu_indicator_ = si_bits[orig_offset];

	orig_offset++ ;

	//decode system information 21 indicator

	system_information_21_indicator_ = si_bits[orig_offset];			

}

void si_3_rest_octets::verify()
{

}

void si_3_rest_octets::parse_bit_stream(gsm_bit_stream &bs)
{
	

	bits_to_consume_ = bs.num_bits_in_bit_stream() - bs.num_bits_unused_in_bit_stream() - bs.bits_consumed_thus_far();
		
	calculate_skip_bits(bs);

	copy_to_raw_bit_stream(bs);

	bs.consume_more_bits(bits_to_consume_);



}

void si_3_rest_octets::decode(gsm_bit_stream &bs)
{
	parse_bit_stream(bs);

	info_element_specific_decode();
}
