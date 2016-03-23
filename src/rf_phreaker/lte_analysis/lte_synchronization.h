#pragma once

#include "lte_analysis.h"
#include "lte_pss.h"


namespace rf_phreaker {

//typedef struct
//{
//	unsigned int ID;
//	CORRELATIONTYPE NormCorr;
//	CORRELATIONTYPE RMSCorr;
//	unsigned int StartSampleNum;
//} LTEProc_CorrRecordType;
typedef CORR_RECORD_TYPE LTEProc_CorrRecordType;


void sampleRateConv2(Ipp32fc *signal192, Ipp32fc *signal384, unsigned int signalLength,
	double* pDelayTime, int sampling_factor);


int getSignalPower(const Ipp32fc *signal384, unsigned int signalLength);


void getHalfFrameTiming(LTEProc_CorrRecordType *pPSCHCorrRecord,
	unsigned int *pNumPschPeaks, const Ipp32fc *signal192,
	unsigned int NumHalfFramesToProcess, double minimum_relative_peak_threshold);

void getCPMode(CYCLICPREFIX *pCyclicPrefixMode, Ipp32fc *signal192, unsigned int PSSStartSample,
	unsigned int numSamplesToProcess);

void getChannelEstFromPSS(Ipp32fc *H_est, Ipp32fc *signal192, unsigned int PSSStartSample,
	unsigned int cellID2, int PSS_No, CYCLICPREFIX cyclicPrefixMode, int freqOffset);

void getFrameTiming(Ipp32fc *signal192, unsigned int numSamplesToProcess,
	LTEProc_CorrRecordType *pPSCHCorrRecord, unsigned int NumCellID2,
	LTEProc_CorrRecordType *pSSCHCorrRecord, unsigned int *pNumCellID,
	CYCLICPREFIX *pCyclicPrefixMode);

unsigned char verifyCellIDFromRS(const Ipp32fc *signal384, unsigned int cellIDAll,
	unsigned int frameStartSample, CYCLICPREFIX cyclicPrefixMode,
	CORRELATIONTYPE *RSStrength, CORRELATIONTYPE *RSNorm);

int calculateRSValues(const Ipp32fc *signal384, unsigned int cellIDAll,
	unsigned int frameStartSample, CYCLICPREFIX cyclicPrefixMode,
	CORRELATIONTYPE *RSStrength, CORRELATIONTYPE *RSNorm, double *AvgDigitalVoltage);



//class WIND_LtePssSearcher
//{
//public:
//	WIND_LtePssSearcher(unsigned int SampleRateHz=4875000);
//	~WIND_LtePssSearcher();
//	int SetNewSampleRate(unsigned int SampleRateHz);
//	int Search(const Ipp32fc *Signal, unsigned int NumSamples, WindPssSearchData *Results);
//protected:
//	static const unsigned int m_MaxNumIFChannels;
//	unsigned int m_SampleRateHz;
//	Ipp32fc m_DownConverter_OneLteFrameBuffer[65536];
//	Ipp32fc m_DownConverterBuffer[65536];
//	Ipp32fc *m_DownConverterFrame, *m_DownConverterRandom;
//	LtePrimarySyncSequence *m_PssTemplates[LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF];
//	int DownConvert(const Ipp32fc *Src, Ipp32fc *Dest, unsigned int NumSamples, int NumIFChannelShift);
//	int IFUpShiftOne(const Ipp32fc *Src, Ipp32fc *Dst, unsigned int NumSamples) const;
//};

}