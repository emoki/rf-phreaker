

#include "rf_phreaker/gsm_layer_3_library/frequency_algorithm.h"


uint8_t frequency_algorithm::power_of_two[32] =  {1,1,2,2,4,4,4,4,8,8,8,8,8,8,8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,32};


frequency_algorithm::frequency_algorithm(uint32_t num, bool ext)
	                :num_ba(num),
					 extended(ext)
{


}

frequency_algorithm::~frequency_algorithm()
{


}

void frequency_algorithm::extract_bits(uint32_t num_byte, std::vector<uint8_t> bit_stream, uint32_t start_index)
{

 uint8_t data = 0, index = 1;
 
 for(int8_t ii = num_byte; ii >= 0;ii--)
 {
	//data = raw_bit_stream_[value_byte_position()+ii];

	data = bit_stream[start_index + ii];
	
	
	for(uint8_t bit_pos = 0; bit_pos <8; bit_pos++)
	{		
		ba_list_bits[index++] = (data>>bit_pos) & 0x1;		

	}//loop-bit_pos

 }//loop-ii

};


void frequency_algorithm::decode_frequency(uint32_t max_index, uint32_t range, bool extended)
{
uint32_t index, n;

f[0] = w[0];

if(!extended)
	num_ba = 0;

for(uint32_t k = 1; k <=max_index; k++)
{
 
	uint32_t j;

	index = k;

	j = power_of_two[index];

	n = w[index];

	if(n == 0)
	{
		f[k] = 0;
	    continue;
	}

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

//num_ba++;
f[k+num_ba] = smod((w[0] + n ),1024);

}

}