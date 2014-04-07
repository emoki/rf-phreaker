#pragma once

#include "ipp.h"
#include "lte_analysis.h"


namespace rf_phreaker {

void LteChannelEst(Ipp32fc* H, Ipp32f* pVar, Ipp32fc* inSignal, 
	unsigned int frameStart, unsigned int cellID, CYCLICPREFIX cyclicPrefixMode,   
	unsigned int antPort, unsigned int framesToProcess, unsigned int DLBW);

}