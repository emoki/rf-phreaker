#pragma once

#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/lte_analysis/lte_types.h"
#include "rf_phreaker/lte_analysis/lte_errors.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "ipp.h"

//#ifdef __cplusplus
//extern "C" {
//#endif

namespace rf_phreaker {

void generate_cell_RS(Ipp32fc *cell_RS, unsigned int *OFDM_SymbNos, unsigned int *pSymbNum, 
	Ipp16u *frquencyIdx, unsigned int slotNo, unsigned int cellID, CYCLICPREFIX cyclicPrefixMode, 
	unsigned int N_RB_DL, unsigned int N_RB_max_DL, unsigned int antPort);

void generate_PN_seq(unsigned int *c, int c_init, int len);

void dec2binvec(Ipp8u *pDest, int src, int len);

void myfftshift(Ipp32fc *pDest, Ipp32fc *pSrc, int len);

void myfft(Ipp32fc *pSeq_F, const Ipp32fc *pSeq_T, int len);

void myifft(Ipp32fc *pSeq_T, const Ipp32fc *pSeq_F, int len);

void myfir(Ipp32fc* pDest, Ipp32fc* pSrc, int signalLen, Ipp32f* firCoef, int firLen);

void bit2byte(unsigned char *byteSeq, unsigned int *bitSeq,  unsigned int bitLen, 
		unsigned char reflect);

void computeLLR(Ipp32f *detLLR, Ipp32fc *signal, Ipp32fc *H, unsigned int len, 
	LTEMODULATION modulate_mode, double noiseVar);

void LTE_modulate(Ipp32fc* outSignal, unsigned int* inSymb, unsigned int len, 
	LTEMODULATION modulate_mode);

void *allocate(unsigned N, unsigned size);


float compute_log_sum(float *input, int length);

void linearInterplate_fc(Ipp32fc* outSeq, Ipp32fc* inSeq, Ipp16u* inIdx, 
	unsigned int inLen, unsigned int startIdx, unsigned int endIdx);

void LTE_CC_decoding(unsigned int *bitSeq, Ipp32f* inLLR, unsigned int inLen);


void multMatVect_fc(Ipp32fc *destVec, Ipp32fc *srcMat, unsigned int rows,
	unsigned int cols, Ipp32fc *srcVec);

void multMatVect_fc_fast(ipp_32fc_array &destVec, ipp_32fc_array &srcMat, unsigned int rows,
	unsigned int cols, Ipp32fc *srcVec);

void stDiversityDet(Ipp32f* detLLR, Ipp32fc* signalF, Ipp32fc* H, unsigned int subcarrierNum,
	unsigned int antNum,  LTEMODULATION modulate_mode,  Ipp32f *noiseVar);

void softDeSrambling(Ipp32f* outLLR, Ipp32f* inLLR, unsigned int len, 
	unsigned int *scramblingBits);

//#ifdef __cplusplus
//}
//#endif

}