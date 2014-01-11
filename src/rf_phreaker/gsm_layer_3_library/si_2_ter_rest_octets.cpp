
#include "rf_phreaker/gsm_layer_3_library/si_2_ter_rest_octets.h"

utran_fdd_description_ter::utran_fdd_description_ter()
{

}

utran_fdd_description_ter::~utran_fdd_description_ter()
{

}

utran_tdd_description_ter::utran_tdd_description_ter()
{

}

utran_tdd_description_ter::~utran_tdd_description_ter()
{

}

si_2_ter_rest_octets::si_2_ter_rest_octets(format_of_information_elements format)
	: information_element_type_3(format, si_2_rest_octects_value_bit_size)
{
}


si_2_ter_rest_octets::~si_2_ter_rest_octets()
{
}

void si_2_ter_rest_octets::extract_bits()
{

 uint8_t data = 0, index = 1;
 
 for(int8_t ii = 1; ii >= 0;ii--)
 {
	data = raw_bit_stream_[value_byte_position()+ii];
	
	for(uint8_t bit_pos = 0; bit_pos <8; bit_pos++)
	{		
		si_bits[index++] = (data>>bit_pos) & 0x1;		

	}//loop-bit_pos

 }//loop-ii



}

void si_2_ter_rest_octets::info_element_specific_decode()
{
	uint8_t orig_offset = 0;

	extract_bits();

	orig_offset++;// skip one bit L/H

	//decode si2 ter mp change mark

	si2_ter_mp_change_mark_ = si_bits[orig_offset];

	orig_offset++;

	//decode si2 ter 3g change mark

	si2_ter_3g_change_mark_ = si_bits[orig_offset];

	orig_offset++;

	//decode si 2 ter index

	si2_ter_index_ = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
										  + (si_bits[orig_offset + 2] << 2);


	orig_offset = orig_offset + 3;

	//decode si 2 ter count

	si2_ter_count_ = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
										  + (si_bits[orig_offset + 2] << 2);


	orig_offset = orig_offset + 3;

	//decode utran fdd description

	if(si_bits[orig_offset]) //check if utran fdd is present
	{
		//move one bit
		orig_offset++ ;
		
		//Skip two bits
		orig_offset = orig_offset + 2;

		// decode arfcn		
		utran_fdd_description_.arfcn = si_bits[orig_offset ] + (si_bits[orig_offset + 1] << 1) 
										                        + (si_bits[orig_offset + 2] << 2)
																+ (si_bits[orig_offset + 3] << 3)
																+ (si_bits[orig_offset + 4] << 4)
															    + (si_bits[orig_offset + 5] << 5)
																+ (si_bits[orig_offset + 6] << 6)
															    + (si_bits[orig_offset + 7] << 7)
																+ (si_bits[orig_offset + 8] << 8)
																+ (si_bits[orig_offset + 9] << 9)
															    + (si_bits[orig_offset + 10] << 10)
															    + (si_bits[orig_offset + 11] << 11)
															    + (si_bits[orig_offset + 12] << 12)
															    + (si_bits[orig_offset + 13] << 13);

		orig_offset = orig_offset + 14;


		// Decode bandwidth	
		if(si_bits[orig_offset])
		{
			//move one bit
			orig_offset++ ;

			utran_fdd_description_.bandwidth = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
																	+ (si_bits[orig_offset + 2] << 2);
		}
		else
		{
			//move one bit
			orig_offset++ ;
	
		}

	
	} //utran fdd 

	else
	{
		orig_offset++;
	}

	//decode utran tdd description

	if(si_bits[orig_offset]) //check if utran tdd is present
	{
		//move one bit
		orig_offset++ ;
		
		//Skip two bits
		orig_offset = orig_offset + 2;

		// decode arfcn		
		utran_tdd_description_.arfcn = si_bits[orig_offset ] + (si_bits[orig_offset + 1] << 1) 
										                        + (si_bits[orig_offset + 2] << 2)
																+ (si_bits[orig_offset + 3] << 3)
																+ (si_bits[orig_offset + 4] << 4)
															    + (si_bits[orig_offset + 5] << 5)
																+ (si_bits[orig_offset + 6] << 6)
															    + (si_bits[orig_offset + 7] << 7)
																+ (si_bits[orig_offset + 8] << 8)
																+ (si_bits[orig_offset + 9] << 9)
															    + (si_bits[orig_offset + 10] << 10)
															    + (si_bits[orig_offset + 11] << 11)
															    + (si_bits[orig_offset + 12] << 12)
															    + (si_bits[orig_offset + 13] << 13);

		orig_offset = orig_offset + 14;


		// Decode bandwidth	
		if(si_bits[orig_offset])
		{
			//move one bit
			orig_offset++ ;

			utran_tdd_description_.bandwidth = si_bits[orig_offset] + (si_bits[orig_offset + 1] << 1) 
																	+ (si_bits[orig_offset + 2] << 2);
		}
		else
		{
			//move one bit
			orig_offset++ ;
	
		}

	
	} //utran fdd 

	else
	{
		orig_offset++;
	}







}
	

void si_2_ter_rest_octets::verify()
{
	
}

void si_2_ter_rest_octets::parse_bit_stream(gsm_bit_stream &bs)
{
	

	bits_to_consume_ = bs.num_bits_in_bit_stream() - bs.num_bits_unused_in_bit_stream() - bs.bits_consumed_thus_far();
		
	calculate_skip_bits(bs);

	copy_to_raw_bit_stream(bs);

	bs.consume_more_bits(bits_to_consume_);



}

void si_2_ter_rest_octets::decode(gsm_bit_stream &bs)
{
	parse_bit_stream(bs);

	info_element_specific_decode();
}

