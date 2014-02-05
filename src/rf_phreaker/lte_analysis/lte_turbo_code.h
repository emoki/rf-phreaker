/*
*********************************************************************************************************
* Copyright (c) 
* File : lte_turbo_code.h
* Brief : Header file used for LTE turbo code processing
* Author:Rajesh S. Bagul
* History : 
*********************************************************************************************************
*/

#ifndef  __LTE_TURBO_CODE_H__
#define  __LTE_TURBO_CODE_H__ 


int lte_turbocode_internal_interleaver_param(unsigned int k_block_size,unsigned int &f1,unsigned int &f2);
int lte_turbo_bcjr_maxlogmap(Ipp32f* received_data,Ipp32f* apriori_probability,Ipp32f* llr,unsigned int block_size);
int lte_turbo_code_decoder(Ipp32f* received_data,unsigned int *turbo_decoded_bits,unsigned int num_bits,unsigned int num_turbo_iterations);

#endif