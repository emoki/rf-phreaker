/*
*********************************************************************************************************
* Copyright (c) 
* File : lte_pdsch.h
* Brief : Header file used for decoding the LTE Data Channel
* Author:Rajesh S. Bagul
* History : 
*********************************************************************************************************
*/

#ifndef  __LTEPDSCH_H__
#define  __LTEPDSCH_H__



#define LTE_PDSCH_CRC_LEN              24
#define LTE_PDSCH_TURBO_TAIL_BITS       4
#define LTE_TURBO_CODE_NUM_ITERATION    4


enum lte_re_type
{
	lte_re_unused = 0x0,
	lte_re_sync_signal = 0x2,
	lte_re_reference_signal = 0x3,
	lte_re_pbch = 0x4,	
	lte_re_reserved = 0xff
};



int lte_pdsch_decode(Ipp32fc* inSignal,
	                Ipp32fc* h_est,
	                Ipp32f* h_noise_var,	
	                lte_measurements &LteData,
					unsigned int cell_no,
					unsigned int sub_frame_index,
					unsigned int subframe_start_sample_index,
					lte_info_dci_format &dci_format_info,
					unsigned int dci_type,
					unsigned int dci_index);

int lte_pdsch_get_subframe_map( lte_measurements &LteData,
					            unsigned int cell_no,
					            unsigned int sub_frame_index);

int lte_pdsch_get_symbols (Ipp32fc* inSignal,
	                       Ipp32fc* h_est,
	                       unsigned int &pdsch_re_count,
	                       lte_measurements &LteData,
					       unsigned int cell_no,
					       unsigned int sub_frame_index,
						   unsigned int subframe_start_sample_index,
						   unsigned int start_rb,
						   unsigned int end_rd);










#endif