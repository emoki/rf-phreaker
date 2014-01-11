
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "rf_phreaker/lte_analysis/lte_types.h"
#include "rf_phreaker/ipp_custom/ipp.h"
#include "rf_phreaker/lte_analysis/lte_errors.h"

#define TRUE							1
#define FALSE							0
#define PI								3.1415926

//typedef short IQDATA;
//
//struct DATASAMPLE
//{
//	IQDATA I;  // Real
//	IQDATA Q;  // Imaginary
//};
//
//
//typedef unsigned __int16 CELLIDTYPE;
//typedef double CORRELATIONTYPE;
//typedef double FRAMEBOUNDRYTYPE;
//
//enum CYCLICPREFIX0
//{
//	Normal = 1,
//	Extended = 2
//};
//
//typedef enum CYCLICPREFIX0 CYCLICPREFIX;
//

#define ZEROS             0
#define ONES              1

#define OFDM_SYMBOLS_PER_SLOT		 7
#define NUM_SLOTS_PER_SUBFRAME		 2
#define	NUM_SUBFRAMES_PER_FRAME		 10     
#define NUM_ANTENNA_MAX				 4
#define NUM_FRAMES					 1
#define FFT_SIZE                     2048
#define MAX_FFT_SIZE                 2048
#define MAX_CONTROL_SYMBOL_LENGHT    4

#define NUM_RE_PER_REG               4

#define NUM_SUBCARRIER_PER_RESOURCE_BLOCK   12
	
#define NUM_PCFICH_MODULATION_SYMBOLS    16

#define OFDM_SYMBOLS_PER_FRAME  OFDM_SYMBOLS_PER_SLOT * NUM_SLOTS_PER_SUBFRAME * NUM_SUBFRAMES_PER_FRAME
#define OFDM_SYMBOLS_PER_SUBFRAME OFDM_SYMBOLS_PER_SLOT * NUM_SLOTS_PER_SUBFRAME


enum LteChannelBandwidth
{
	LteBandwidth_Unknown = 0,
	LteBandwidth_1_4MHZ = 1400000,
	LteBandwidth_3MHZ = 3000000,
	LteBandwidth_5MHZ = 5000000,
	LteBandwidth_10MHZ = 10000000,
	LteBandwidth_15MHZ = 15000000,
	LteBandwidth_20MHZ = 20000000
};

enum LteNumAntennaPorts
{
	LteAntPorts_Unknown = 0,
	LteAntPorts_1 = 1,
	LteAntPorts_2 = 2,
	LteAntPorts_4 = 4
};

enum PHICHDURATION0
{
	PHICH_Normal = 1,
	PHICH_Extended = 2
};
typedef enum PHICHDURATION0 PHICHDURATION;

enum PHICHRESOURCE0 //should divide bt 6
{
	PHICH_Unknown = 0,
	PHICH_oneSixth = 1,
	PHICH_half = 3,
	PHICH_one = 6,
	PHICH_two = 12
};
typedef enum PHICHRESOURCE0 PHICHRESOURCE;

enum LteModulation
{
	MBPSK = 0,
	MQPSK = 1,
	M16QAM = 2,
	M64QAM = 3
};

typedef enum LteModulation LTEMODULATION;

typedef struct
{
	PHICHDURATION PhichDuration;
	PHICHRESOURCE PhichResource;

}PHICHCONFIG;

typedef struct
{
	LteChannelBandwidth Bandwidth;
	PHICHCONFIG PHICHConfig;
	unsigned int systemFrameNum; //0~255, 8 bits
	//spare, 10bits
}MASTERIB;


typedef struct
{
	CELLIDTYPE ID;
	CORRELATIONTYPE NormCorr;
	CORRELATIONTYPE RMSCorr;
	unsigned int StartSampleNum;
} CORR_RECORD_TYPE;

enum LteFftSize
{
FFTSIZE_UNKNOWN =0,
FFTSIZE_128   = 128,
FFTSIZE_256   = 256,
FFTSIZE_512   = 512,
FFTSIZE_1024  = 1024,
FFTSIZE_1536  = 1536,
FFTSIZE_2048  = 2048,
};

enum LteFrameNumSamples
{
FRAMENUMSAMPLES_FFT256    = 38400,
FRAMENUMSAMPLES_FFT512    = 76800,
FRAMENUMSAMPLES_FFT1024   = 153600,
};

enum LteCyclicPrefixSamples
{
CP_SAMPLES_FFT256_SYMBOL_0     = 20,
CP_SAMPLES_FFT256_SYMBOL_1TO6  = 18,
CP_SAMPLES_FFT512_SYMBOL_0     = 40,
CP_SAMPLES_FFT512_SYMBOL_1TO6  = 36,
CP_SAMPLES_FFT1024_SYMBOL_0    = 80,
CP_SAMPLES_FFT1024_SYMBOL_1TO6 = 72,

};

enum LteNumResourceBlocks
{
NUMRESOURCEBLOCKS_FFT256  = 15,
NUMRESOURCEBLOCKS_FFT512  = 25,
NUMRESOURCEBLOCKS_FFT1024 = 50,
};

enum lte_num_bits_dci_1a
{
NUM_BITS_DCI_1A_3MHZ = 38,
NUM_BITS_DCI_1A_5MHZ = 41,
NUM_BITS_DCI_1A_10MHZ = 43,

};

// Changed 8/11/2010 Ethan Steffens
// Bandwidth moved from WindLteData into LteMeasurement to accommodate multiple bandwidths.
// AvgChannelRMSVoltage (used for CarrierSL) is always scaled using a 1.4mHz bandwidth and therefore
// stays in WindLteData, for now...
struct LteMeasurement
{
	CORR_RECORD_TYPE PschRecord;
	CORR_RECORD_TYPE SschRecord;
	CORR_RECORD_TYPE RsRecord;
	CYCLICPREFIX CyclicPrefix;
	LteNumAntennaPorts NumAntennaPorts;
	double AvgDigitalVoltage;
	LteChannelBandwidth Bandwidth;
	LteFftSize fftSize;
	LteFrameNumSamples frameNumSamples;
	LteCyclicPrefixSamples cPSamplesSymbol0;
	LteCyclicPrefixSamples cPSamplesSymbol1to6;
	LteNumResourceBlocks numResouceBlocks;
	unsigned int lteControlSysmbolLenght;
	unsigned int phich_duration;
	unsigned int phich_resources;
	unsigned int fft_subcarrier_start_index;
	unsigned int num_bits_dci_1A;
	unsigned int frame_number;
    Ipp32f rsrp;
	Ipp32f rssi;
	Ipp32f rsrq;
	unsigned int cid;
	unsigned int lac;
	char mcc[4];
    char mnc[4];
};

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


void multMatVect_fc(Ipp32fc *destVec,  Ipp32fc *srcMat, unsigned int rows, 
	unsigned int cols, Ipp32fc *srcVec);

void stDiversityDet(Ipp32f* detLLR, Ipp32fc* signalF, Ipp32fc* H, unsigned int subcarrierNum, 
	unsigned int antNum,  LTEMODULATION modulate_mode,  Ipp32f *noiseVar);

void softDeSrambling(Ipp32f* outLLR, Ipp32f* inLLR, unsigned int len, 
	unsigned int *scramblingBits);

#ifdef __cplusplus
}
#endif

