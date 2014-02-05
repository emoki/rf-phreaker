#pragma once

#include <stdint.h>

#define TRUE							1
#define FALSE							0
#define PI								3.1415926


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
	int systemFrameNum; //0~255, 8 bits
	//spare, 10bits
}MASTERIB;


typedef struct
{
	int ID;
	double NormCorr;
	double RMSCorr;
	int StartSampleNum;
} CORR_RECORD_TYPE;

enum LteFftSize
{
	FFTSIZE_UNKNOWN = 0,
	FFTSIZE_128 = 128,
	FFTSIZE_256 = 256,
	FFTSIZE_512 = 512,
	FFTSIZE_1024 = 1024,
	FFTSIZE_1536 = 1536,
	FFTSIZE_2048 = 2048,
};

enum LteFrameNumSamples
{
	FRAMENUMSAMPLES_FFT256 = 38400,
	FRAMENUMSAMPLES_FFT512 = 76800,
	FRAMENUMSAMPLES_FFT1024 = 153600,
};

enum LteCyclicPrefixSamples
{
	CP_SAMPLES_FFT256_SYMBOL_0 = 20,
	CP_SAMPLES_FFT256_SYMBOL_1TO6 = 18,
	CP_SAMPLES_FFT512_SYMBOL_0 = 40,
	CP_SAMPLES_FFT512_SYMBOL_1TO6 = 36,
	CP_SAMPLES_FFT1024_SYMBOL_0 = 80,
	CP_SAMPLES_FFT1024_SYMBOL_1TO6 = 72,

};

enum LteNumResourceBlocks
{
	NUMRESOURCEBLOCKS_FFT256 = 15,
	NUMRESOURCEBLOCKS_FFT512 = 25,
	NUMRESOURCEBLOCKS_FFT1024 = 50,
};

enum CYCLICPREFIX
{
	Normal = 1,
	Extended = 2
};
enum lte_num_bits_dci_1a
{
	NUM_BITS_DCI_1A_3MHZ = 38,
	NUM_BITS_DCI_1A_5MHZ = 41,
	NUM_BITS_DCI_1A_10MHZ = 43,

};

typedef uint16_t EARFCNTYPE;
typedef uint16_t CELLIDTYPE;
typedef uint16_t PHYSICALCELLIDTYPE;
typedef double CORRELATIONTYPE;
typedef double FRAMEBOUNDRYTYPE;
typedef uint8_t PSCHIDTYPE;
typedef uint8_t SSCHIDTYPE;
typedef uint32_t CARRIERBANDWIDTHTYPE;
typedef uint16_t DELAYSPREADTYPE;
typedef uint16_t SUBCARRIERSPACING;

