/*
*********************************************************************************************************
* Copyright (c) 
* File : lte_turbo_code.h
* Brief : Header file used for LTE turbo code processing
* Author:Rajesh S. Bagul
* History : 
*********************************************************************************************************
*/
#ifndef __LTE_TURBO_CODE_RATE_MATCH_H__
#define __LTE_TURBO_CODE_RATE_MATCH_H__

namespace rf_phreaker {

#define LTE_TURBO_NULL         0xFFFFFFFF


int lte_turbocoded_sublock_interleaver(Ipp32f* output_sequence,Ipp32f* input_sequence,unsigned int input_sequence_len,unsigned int num_bits_generated,unsigned int rv_idx);

}

#endif