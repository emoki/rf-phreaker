/*
*********************************************************************************************************
* Copyright (c) 
* File : lte_turbo_code.cpp
* Brief : LTE Turbo Code
* Author:Rajesh S. Bagul
* History : 
*********************************************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include "lte_common.h"
#include "lte_analysis.h"
#include "lte_turbo_code_rate_match.h"


namespace rf_phreaker {

Ipp32f adjusted_input[6144],adjusted_input_1[6144],sequence_intrvd_0[6144],sequence_intrvd_1[6144],sequence_intrvd_2[6144];
Ipp32f output_sequence_0[6144],output_sequence_1[6144],output_sequence_2[6144];
Ipp32f sequence_0_matrix[128][32], sequence_1_matrix[128][32];

unsigned int p[32] = {0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30,
	                  1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31};  //Permutation vector 
/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_turbocoded_sublock_interleaver(Ipp32f* output_sequence,Ipp32f* input_sequence,unsigned int input_sequence_len,unsigned int num_bits_generated,unsigned int rv_idx)
{
unsigned int lenght_count=0,total_null_elements=0,num_null_elements_subblock,rr,tt=0,mm=0,xx=0,seq_index=0,k_pi_idx;
unsigned int k_0,r_subblock,c_subblock = 32,index;

r_subblock = num_bits_generated/c_subblock + 1;

k_0 = r_subblock*(2*rv_idx*((3*c_subblock)/8 )+2);

num_null_elements_subblock = (r_subblock * c_subblock) - (num_bits_generated);

//Scalar addition of channel equalized repeated bits
memset(adjusted_input,0,6144);
if(input_sequence_len > 3*num_bits_generated)
{

	for(unsigned int ii=0;ii<((input_sequence_len/(3*num_bits_generated))+1);ii++)
	{
		for(unsigned int kk=0;kk<3*num_bits_generated;kk++)
		{
		adjusted_input[kk] = adjusted_input[kk] + input_sequence[lenght_count++];
		if(lenght_count ==input_sequence_len) break;
		}
		if(lenght_count ==input_sequence_len) break;
	}
}

//Calculating number of NULL elements
if(k_0 < r_subblock*c_subblock)
{
rr = (k_0 +1)/ r_subblock;
	for(unsigned int kk=0;kk<(rr+1);kk++)
	{
		if(p[kk] < num_null_elements_subblock)
			++total_null_elements;    
	}
}
else
{
//rr = ((k_0 -  r_subblock*c_subblock)+1)/(2*r_subblock) ;
rr = ((k_0 -  r_subblock*c_subblock))/(2*r_subblock) ;
total_null_elements = num_null_elements_subblock;
	for(unsigned int kk=0;kk<rr;kk++)
	{
		if((p[kk] ) < num_null_elements_subblock)
			total_null_elements++;
	}

total_null_elements++; //Dont know why ?
rr = (k_0 -  r_subblock*c_subblock)/(2);

	for(unsigned int kk=0;kk<rr;kk++ )
	{
		k_pi_idx = (p[kk/r_subblock] + c_subblock * (kk % r_subblock) + 1) % (r_subblock * c_subblock);
	 if((k_pi_idx ) < num_null_elements_subblock)
	 	total_null_elements++; 
	}
}


//Extracting rate-matched sequence 1 and sequence 0
for(unsigned int jj=0;jj<3*num_bits_generated;jj++)
{
adjusted_input_1[jj] = adjusted_input[(3*num_bits_generated - k_0 + total_null_elements + jj-1)%(3*num_bits_generated)];
if(jj<num_bits_generated)
sequence_intrvd_0[jj] = adjusted_input_1[jj];
}

//lte_debug_filewrite("lte_rate_match_adjusted1.txt" ,adjusted_input_1,612);
//Extracting rate-matched sequence 1 and sequence 2
for(unsigned int kk=0;kk<r_subblock*c_subblock;kk++)
{
	if((kk % r_subblock!=0)||(((kk % r_subblock)==0)&&(p[(kk/r_subblock)] >(num_null_elements_subblock-1))))
	{
	  sequence_intrvd_1[tt] = adjusted_input_1[num_bits_generated + mm];
	  tt++;
	  mm++;
	}

	if(((p[kk/r_subblock] + c_subblock * (kk % r_subblock) + 1) % (r_subblock * c_subblock)) >( num_null_elements_subblock-1))
	{
	  sequence_intrvd_2[xx] =  adjusted_input_1[num_bits_generated + mm]; 
	  xx++;
	  mm++;	
	}
}
//lte_debug_filewrite("lte_rate_match_sequence_intrvd_1.txt" ,sequence_intrvd_1,204);
//lte_debug_filewrite("lte_rate_match_sequence_intrvd_2.txt" ,sequence_intrvd_2,204);
for(unsigned int col_idx=0;col_idx<c_subblock;col_idx++)
{
	if(p[col_idx]<num_null_elements_subblock)
	{
		 sequence_0_matrix[0][p[col_idx]] = LTE_TURBO_NULL;
		 sequence_1_matrix[0][p[col_idx]] = LTE_TURBO_NULL;

		 for(unsigned int row_idx=1;row_idx<r_subblock;row_idx++)
		 {
		   sequence_0_matrix[row_idx][p[col_idx]] = sequence_intrvd_0[seq_index];
		   sequence_1_matrix[row_idx][p[col_idx]] = sequence_intrvd_1[seq_index];
		   seq_index++;
		 }	
	}
	else
	{	
		for(unsigned int row_idx=0;row_idx<r_subblock;row_idx++)
		{
		sequence_0_matrix[row_idx][p[col_idx]] = sequence_intrvd_0[seq_index];
		sequence_1_matrix[row_idx][p[col_idx]] = sequence_intrvd_1[seq_index];
		seq_index++;
		}	
	}
}

//final output, sequence 1 and sequence 2
seq_index = 0;
for(unsigned int row_idx=0;row_idx<r_subblock;row_idx++)
{
	for(unsigned int col_idx=0;col_idx<c_subblock;col_idx++)
	{
       if(sequence_0_matrix[row_idx][col_idx]!=LTE_TURBO_NULL)
	   {
		   output_sequence_0[seq_index] = sequence_0_matrix[row_idx][col_idx];
		   output_sequence_1[seq_index] = sequence_1_matrix[row_idx][col_idx];
		   seq_index++;
	   }
	}
}

//extracting sequence 2
seq_index = 0;
for(unsigned int kk=0;kk<r_subblock*c_subblock;kk++)
{
	k_pi_idx = ((p[kk/r_subblock] + c_subblock * (kk % r_subblock) + 1) % (r_subblock * c_subblock));
	if((k_pi_idx +1) > num_null_elements_subblock)
		output_sequence_2[k_pi_idx - num_null_elements_subblock] = sequence_intrvd_2[seq_index++];
}

index = 0;
for(unsigned int kk=0;kk<seq_index;kk++)
{
output_sequence[index]   = -1 * output_sequence_0[kk];
output_sequence[index+1] = -1 * output_sequence_1[kk];
output_sequence[index+2] = -1 * output_sequence_2[kk];

//output_sequence[index]   = output_sequence_0[kk];
//output_sequence[index+1] = output_sequence_1[kk];
//output_sequence[index+2] = output_sequence_2[kk];

index = index+3;
}

//lte_debug_filewrite("Coutput_sequence_0_3mhz.txt" ,output_sequence_0,172);
//lte_debug_filewrite("Coutput_sequence_1_3mhz.txt" ,output_sequence_1,172);
//lte_debug_filewrite("Coutput_sequence_2_3mhz.txt" ,output_sequence_2,172);
//lte_debug_filewrite("lte_rate_match_adjusted1.txt" ,adjusted_input_1,516);
//lte_debug_filewrite("lte_rate_match_input_sequence.txt" ,input_sequence,552);



return LTE_SUCCESS;
}

}