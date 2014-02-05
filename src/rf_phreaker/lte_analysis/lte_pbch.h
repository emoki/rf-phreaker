
#pragma once

#include "ipp.h"
#include "lte_common.h"


typedef struct
{
	MASTERIB MasterIB;
	LteNumAntennaPorts NumAntPorts;
}PBCHINFO;


int BCH_decoding(PBCHINFO* pbchInfo, Ipp32fc* inSignal, Ipp32fc* H,  Ipp32f* noiseVar, 
	CELLIDTYPE cellID, CYCLICPREFIX cyclicPrefixMode, unsigned int frameStart, 
	unsigned int framesToProcess, LteChannelBandwidth Bandwidth);

