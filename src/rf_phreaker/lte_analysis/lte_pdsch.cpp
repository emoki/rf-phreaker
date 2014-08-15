/*
*********************************************************************************************************
* Copyright (c) 
* File : LtePdcch.cpp
* Brief : Decoding LTE Control Channel
* Author:Rajesh S. Bagul
* History : 
*********************************************************************************************************
*/
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <iostream>
#include <cstring>
#include <string>

#include "windows.h"

#include "lte_common.h"
#include "lte_analysis.h"
#include "lte_turbo_code_rate_match.h"
#include "lte_turbo_code.h"

#include "lte_pdcch.h"
#include "lte_pdsch.h"
#include "lte_crc_16.h"

#include <fstream>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <stdint.h>
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/lte_analysis/lte_io.h"

namespace rf_phreaker {

unsigned int lte_subframe_map[OFDM_SYMBOLS_PER_SUBFRAME][MAX_FFT_SIZE];
unsigned int scrambling_seq_pdsch[6144],turbo_decoded_bits[6144];
Ipp32fc lte_pdsch_fft[OFDM_SYMBOLS_PER_SUBFRAME][MAX_FFT_SIZE],lte_pdsch_fft_shifted[OFDM_SYMBOLS_PER_SUBFRAME][MAX_FFT_SIZE];
Ipp32fc h_est_pdsch[6144];
Ipp32fc h_est_pdsch_temp[NUM_ANTENNA_MAX][6144];
Ipp32fc lte_pdsch_re[6144];
Ipp32f lte_pdsch_demod_llr[6144],descrambled_pdcch_llr[6144],deinterleaved_llr[6144];
unsigned char lte_pdsch_byte_seq[512];


//layer_3_information::lte_rrc_message_aggregate message;
extern HANDLE  hConsole;



/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_pdsch_decode(Ipp32fc* inSignal,
	                Ipp32fc* h_est,
	                Ipp32f* h_noise_var,	
					lte_measurements &LteData,
					unsigned int cell_no,
					unsigned int sub_frame_index,
					unsigned int subframe_start_sample_index,
					lte_info_dci_format &dci_format_info,
					unsigned int dci_type,
					unsigned int dci_index)
{
	memset(&lte_pdsch_byte_seq, 0, 512);

unsigned int pdsch_re_count,start_rb_index,end_rb_index,transport_block_size,redundancy_version;
LTEMODULATION modulation_type;
unsigned char modulation_order;
int c_init;
unsigned int n_rnti= 0xFFFF,q=0,temp,lte_pdsch_crc;

//h_noise_var[0] = h_noise_var[1] = 169800.0;
h_noise_var[0] = h_noise_var[1] = 2.2149e5;
//lte_pdsch_get_subframe_map
lte_pdsch_get_subframe_map(LteData,cell_no,sub_frame_index);

if(dci_type == lte_dci_format_1a)
{
start_rb_index         =  dci_format_info.pdcch_info_dci_format_1a[dci_index].start_rb_idx;
end_rb_index           =  dci_format_info.pdcch_info_dci_format_1a[dci_index].end_rb_idx; 
modulation_type        =  dci_format_info.pdcch_info_dci_format_1a[dci_index].lte_moduation_type;
modulation_order       =  dci_format_info.pdcch_info_dci_format_1a[dci_index].modulation_order;
redundancy_version     =  dci_format_info.pdcch_info_dci_format_1a[dci_index].redundancy_version;
transport_block_size   =  dci_format_info.pdcch_info_dci_format_1a[dci_index].tbs_size;
}
//////////////// temp - ecs - testing
else
	std::cout << "wrong dci format.";
if(modulation_type != MQPSK)
	return 1;


//lte_get_pdsch_symbols
lte_pdsch_get_symbols (inSignal,
	                    h_est,
	                    pdsch_re_count,
	                    LteData,
					    cell_no,
					    sub_frame_index,
						subframe_start_sample_index,
						start_rb_index,end_rb_index);


/* MIMO Detection - Transmit Diversity */
stDiversityDet(lte_pdsch_demod_llr,
		    lte_pdsch_re, // PDSCH Modulation Symbols - Resource Elements
			h_est_pdsch,
		    pdsch_re_count,
	        LteData[cell_no].NumAntennaPorts, // Number of Antennas 
	        modulation_type,//MQPSK,//Modulation Type == QPSK
	        h_noise_var);

//Soft desrambling
c_init = (n_rnti)*(1<<14) + q*(1<<13) + ((sub_frame_index)<<9) + LteData[cell_no].RsRecord.ID;
//c_init = 1073728051;

generate_PN_seq(scrambling_seq_pdsch, //PDCCH Scambling Sequence
		        c_init, //c_init
			    pdsch_re_count*modulation_order); 

softDeSrambling(descrambled_pdcch_llr,  // Output Descrambled LLR Data
		        lte_pdsch_demod_llr,    //Input LLR data
		        pdsch_re_count*modulation_order,      //lenght of the sequence
		        scrambling_seq_pdsch);   //Scrambling bits


//Turbo coded subblock deinterleaver
lte_turbocoded_sublock_interleaver(deinterleaved_llr,descrambled_pdcch_llr, pdsch_re_count*modulation_order,
	                               transport_block_size + LTE_PDSCH_CRC_LEN + LTE_PDSCH_TURBO_TAIL_BITS,
								   redundancy_version);
//Turbo decoder
clock_t begin_turbo=clock();
lte_turbo_code_decoder(deinterleaved_llr,turbo_decoded_bits,transport_block_size + LTE_PDSCH_CRC_LEN,LTE_TURBO_CODE_NUM_ITERATION);
clock_t end_turbo=clock();
//std::cout << "Lte Turbo Decoder Time elapsed: " << lte_diffclock(end_turbo,begin_turbo) << " ms\n";
//CRC Check
//lte_debug_filewrite("CDeinterleaved_3MHZ.txt",deinterleaved_llr, 552);

// TODO - ecs removed - if(sub_frame_index==5)
{

temp=0;
//lte_debug_filewrite("CTurboInput.txt",deinterleaved_llr, 612);
//lte_debug_filewrite("CTurboOut.txt",turbo_decoded_bits, 200);
//turbo_decoded_bits[11] = turbo_decoded_bits[26] = 0;
bit2byte(lte_pdsch_byte_seq, turbo_decoded_bits, transport_block_size + LTE_PDSCH_CRC_LEN, 0);


lte_crc_24(&lte_pdsch_crc,lte_pdsch_byte_seq ,(transport_block_size + LTE_PDSCH_CRC_LEN)/8);




// TODO - ecs removed - if(lte_pdsch_crc == 0 && sub_frame_index == 5 )
if(lte_pdsch_crc == 0)
{

clock_t begin_asn=clock();

lte_asn1_decoder decoder;

layer_3_information::lte_rrc_message_aggregate tmp;
decoder.decode_bcch_bch_message(lte_pdsch_byte_seq, 512, 0, tmp);

// Only update sibs.
if(!LteData[cell_no].layer_3_.sib1_.decoded_) {
	LteData[cell_no].layer_3_.mcc_ = tmp.mcc_;
	LteData[cell_no].layer_3_.mnc_ = tmp.mnc_;
	LteData[cell_no].layer_3_.lac_ = tmp.lac_;
	LteData[cell_no].layer_3_.cid_ = tmp.cid_;
	LteData[cell_no].layer_3_.sib1_ = tmp.sib1_;
}
if(!LteData[cell_no].layer_3_.sib3_.decoded_) {
	LteData[cell_no].layer_3_.sib3_ = tmp.sib3_;
}
if(!LteData[cell_no].layer_3_.sib4_.decoded_) {
	LteData[cell_no].layer_3_.sib4_ = tmp.sib4_;
}
if(!LteData[cell_no].layer_3_.sib5_.decoded_) {
	LteData[cell_no].layer_3_.sib5_ = tmp.sib5_;
}
if(!LteData[cell_no].layer_3_.sib6_.decoded_) {
	LteData[cell_no].layer_3_.sib6_ = tmp.sib6_;
}
if(!LteData[cell_no].layer_3_.sib7_.decoded_) {
	LteData[cell_no].layer_3_.sib7_ = tmp.sib7_;
}
if(!LteData[cell_no].layer_3_.sib8_.decoded_) {
	LteData[cell_no].layer_3_.sib8_ = tmp.sib8_;
}

clock_t end_asn =clock();
//std::cout << "Lte ASN Time elapsed: " << lte_diffclock(end_asn,begin_asn) << " ms\n";

//std::cout<<"\n Decoded PDSCH \n";

	//static std::ofstream file("debug_lte_layer_3_bitstream.txt");
	//static bool write_header = true;
	//if(write_header) {
	//	write_header = false;
	//	file << "sub_frame_index\tsubframe_start_sample_index\t";
	//	output_lte_meas_debug_header(file);
	//}
	//file << sub_frame_index << "\t" << subframe_start_sample_index << "\t" << LteData[cell_no] << "\t";
	//for(uint32_t i = 0, end = 512; i < end; ++i)
	//	file << std::hex << std::setw(2) << std::setfill('0') << (int)lte_pdsch_byte_seq[i] << " ";
	//file << std::dec << "\t" << tmp << std::endl;
} 

}

return LTE_SUCCESS;
}



/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_pdsch_get_subframe_map(lte_measurements &LteData,
					            unsigned int cell_no,
					            unsigned int sub_frame_index)
{
unsigned int v_shift,v_0,v_1,k_0,k_1,kk;

memset(&lte_subframe_map[0], ZEROS, OFDM_SYMBOLS_PER_SUBFRAME * MAX_FFT_SIZE *4);

//Determine synchronisaton symbol locations
// TODO - ecs removed - if(sub_frame_index == 0 || sub_frame_index==5)
{
	for(int nn=-5;nn<67;nn++)
	{
		kk = nn - 31 + (LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK)/2;
		if((nn<0) || (nn>61))
		{
		  lte_subframe_map[5][kk] = lte_re_reserved;
		  lte_subframe_map[6][kk] = lte_re_reserved;
		}
		else
		{
		  lte_subframe_map[5][kk] = lte_re_sync_signal;
		  lte_subframe_map[6][kk] = lte_re_sync_signal;		
		}
	}


}

//Determine reference signal symbol locations - 6.10.1.2, TS36.211

v_shift = LteData[cell_no].RsRecord.ID % 6;

v_0 = 0;
v_1 = 3;

k_0 = (v_shift + v_0) % 6;
k_1 = (v_shift + v_1) % 6;

for(unsigned int mm=0;mm<2*LteData[cell_no].numResouceBlocks;mm++)
{
	lte_subframe_map[0][6*mm + k_0] = lte_subframe_map[7][6*mm + k_0]   = lte_re_reference_signal;
	lte_subframe_map[4][6*mm + k_1] = lte_subframe_map[11][6*mm + k_1]  = lte_re_reference_signal;
}
	
if((LteData[cell_no].NumAntennaPorts)>=2)
{
	v_0 = 3;
	v_1 = 0;

	k_0 = (v_shift + v_0) % 6;
	k_1 = (v_shift + v_1) % 6;

	for(unsigned int mm=0;mm<2*LteData[cell_no].numResouceBlocks;mm++)
	{
		lte_subframe_map[0][6*mm + k_0] = lte_subframe_map[7][6*mm + k_0]   = lte_re_reference_signal;
		lte_subframe_map[4][6*mm + k_1] = lte_subframe_map[11][6*mm + k_1]  = lte_re_reference_signal;
	}

}

if((LteData[cell_no].NumAntennaPorts)>=3)
{

	v_0 = 3*((2*sub_frame_index) % 2);
	k_0 = (v_shift + v_0) % 6;
   for(unsigned int mm=0;mm<2*LteData[cell_no].numResouceBlocks;mm++)
   {
		lte_subframe_map[1][6*mm + k_0] = lte_subframe_map[8][6*mm + k_0]   = lte_re_reference_signal;		
   }

}


if((LteData[cell_no].NumAntennaPorts)>=3)
{

	v_0 = 3 + 3*((2*sub_frame_index) % 2);
	k_0 = (v_shift + v_0) % 6;
   for(unsigned int mm=0;mm<2*LteData[cell_no].numResouceBlocks;mm++)
   {
		lte_subframe_map[1][6*mm + k_0] = lte_subframe_map[8][6*mm + k_0]   = lte_re_reference_signal;		
   }

}

//Determine PBCH symbol locations
if(sub_frame_index==0)
{
	k_0 = (LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK)/2 - 36 ; //6.6.4, TS36.211
	for(unsigned int kk=0;kk<72;kk++)
	{
		lte_subframe_map[7][k_0 + kk] = 	lte_subframe_map[8][k_0 + kk] = lte_re_pbch;
		lte_subframe_map[9][k_0 + kk] = 	lte_subframe_map[10][k_0 + kk] = lte_re_pbch;
	}

	}

return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_pdsch_get_symbols (Ipp32fc* inSignal,
	                       Ipp32fc* h_est,
	                       unsigned int &pdsch_re_count,
						   lte_measurements &LteData,
					       unsigned int cell_no,
					       unsigned int sub_frame_index,
						   unsigned int subframe_start_sample_index,
						   unsigned int start_rb,
						   unsigned int end_rb)
{
	// Changed the size of fft_index to match that of h_est_pdsch_temp
	const int fft_index_size = 6144/*4096*/;
	unsigned int fft_index[fft_index_size], temp;

for(unsigned int symbol_idx = LteData[cell_no].lteControlSysmbolLenght;symbol_idx<OFDM_SYMBOLS_PER_SUBFRAME;symbol_idx++)
{
   if(symbol_idx < OFDM_SYMBOLS_PER_SLOT)
   {	   
	   myfft(&lte_pdsch_fft[symbol_idx][0], //Frequency Domain Output
		  inSignal + subframe_start_sample_index
		  + LteData[cell_no].cPSamplesSymbol0
		  + symbol_idx * LteData[cell_no].fftSize
		  + symbol_idx * LteData[cell_no].cPSamplesSymbol1to6, //Time Domain Input
		  LteData[cell_no].fftSize); //FFT Size
   }
   else
   { 
       myfft(&lte_pdsch_fft[symbol_idx][0], //Frequency Domain Output
		  inSignal + subframe_start_sample_index
		  + 2*LteData[cell_no].cPSamplesSymbol0
		  + symbol_idx * LteData[cell_no].fftSize
		  + (symbol_idx -1) * LteData[cell_no].cPSamplesSymbol1to6, //Time Domain Input
		  LteData[cell_no].fftSize); //FFT Size
   
   }
	   
	myfftshift(&lte_pdsch_fft_shifted[symbol_idx][0], //Destination
		       &lte_pdsch_fft[symbol_idx][0], //Source
		       LteData[cell_no].fftSize); //FFT Size  
}



pdsch_re_count =0; // Should this be moved into the loop?
for(unsigned int symbol_idx = LteData[cell_no].lteControlSysmbolLenght;symbol_idx<OFDM_SYMBOLS_PER_SUBFRAME;symbol_idx++)
{
	for(unsigned int kk = (start_rb*NUM_SUBCARRIER_PER_RESOURCE_BLOCK);kk<(end_rb+1)*NUM_SUBCARRIER_PER_RESOURCE_BLOCK;kk++)
	{
      if(lte_subframe_map[symbol_idx][kk]==lte_re_unused)
	  {
			if(kk>(LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK/2))
			//if((start_rb*NUM_SUBCARRIER_PER_RESOURCE_BLOCK)>(LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK/2))
			  fft_index[pdsch_re_count] = kk + LteData[cell_no].fft_subcarrier_start_index +1;
			else
			  fft_index[pdsch_re_count] = kk + LteData[cell_no].fft_subcarrier_start_index ;


			lte_pdsch_re[pdsch_re_count] = lte_pdsch_fft_shifted[symbol_idx][fft_index[pdsch_re_count]];
			for (unsigned int antNum =0 ; antNum < LteData[cell_no].NumAntennaPorts; antNum++)
			{
			  h_est_pdsch_temp[antNum][pdsch_re_count] = h_est[antNum * LteData[cell_no].fftSize * OFDM_SYMBOLS_PER_FRAME
													          + sub_frame_index * OFDM_SYMBOLS_PER_SUBFRAME *LteData[cell_no].fftSize
													          + symbol_idx * LteData[cell_no].fftSize
												    	      + fft_index[pdsch_re_count]];
			}

			pdsch_re_count++;
			
	  }
	// Temporary bug fix: pdsch_re_count can overstep the fft_index.  Is pdsch_re_count supposed to be reset to 0 in the outer loop?
	if(pdsch_re_count >= fft_index_size)
		break;
	}
	// Temporary bug fix: pdsch_re_count can overstep the fft_index.  Is pdsch_re_count supposed to be reset to 0 in the outer loop?
	if(pdsch_re_count >= fft_index_size)
		break;
}

memset(h_est_pdsch,0,2048*4*2);

for (unsigned int antNum =0 ; antNum < LteData[cell_no].NumAntennaPorts; antNum++)
{
	for(unsigned int kk=0;kk<pdsch_re_count;kk++)
	{
         h_est_pdsch[antNum*pdsch_re_count+kk]=h_est_pdsch_temp[antNum][kk];
	}
}


return LTE_SUCCESS;
}

}