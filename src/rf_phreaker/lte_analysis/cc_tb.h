#pragma once

#ifndef CC__TB_H
#define CC__TB_H

#include "ipp.h"

namespace rf_phreaker {

//#ifdef __cplusplus
//extern "C" {
//#endif

void nsc_transit(int* output_p, int* trans_p, int input, int* g,
	int KK,	int nn );


void viterbiTb(int* output_u_int, int* out0, int* state0, int* out1, 
	int* state1, float* input_c, int KK, int nn, int LL, int depth);

void conv_encode(int* output_p, int* input, int* out0, int* state0,   
	int* out1, int* state1, int* tail, int KK, int LL, int nn);

void cc_decoding( unsigned int *decBits, Ipp32f* inLLR, unsigned int codeLen, 
	unsigned int *genPoly, unsigned int row, unsigned int col);

		
//#ifdef __cplusplus
//}
//#endif

}

#endif


