/*
*********************************************************************************************************
* Copyright (c) 
* File : LtePcfich.h
* Brief : Header file used for decoding the LTE Physical Control Format Indicator Channel (PCFICH)
* Author:Rajesh S. Bagul
* History : 
*********************************************************************************************************
*/

#ifndef  __LTEPCFICH_H__
#define  __LTEPCFICH_H__

#include "lte_common.h"

namespace rf_phreaker {

int lteDecodePCFICH(Ipp32fc* inSignal,
	                Ipp32fc* hEst,
	                Ipp32f* hNoiseVar,	
	                lte_measurements &LteData,
					unsigned int cellNo,
					unsigned int subFrameIndex,
					unsigned int subframeStartSampleIndex
					);

}



#endif