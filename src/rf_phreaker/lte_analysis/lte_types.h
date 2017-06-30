#pragma once

#include "rf_phreaker/common/common_utility.h"
#include <stdint.h>
#include "ipp.h"

namespace rf_phreaker {

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

#define MAX_FFT_SIZE                 2048
#define MAX_CONTROL_SYMBOL_LENGHT    4

#define NUM_RE_PER_REG               4

#define NUM_SUBCARRIER_PER_RESOURCE_BLOCK   12

#define NUM_PCFICH_MODULATION_SYMBOLS    16

#define MAX_OFDM_SYMBOLS_PER_SUBFRAME OFDM_SYMBOLS_PER_SLOT *  NUM_SLOTS_PER_SUBFRAME

#define OFDM_SYMBOLS_PER_FRAME  OFDM_SYMBOLS_PER_SLOT * NUM_SLOTS_PER_SUBFRAME * NUM_SUBFRAMES_PER_FRAME
#define OFDM_SYMBOLS_PER_SUBFRAME OFDM_SYMBOLS_PER_SLOT * NUM_SLOTS_PER_SUBFRAME

// double check this value
#define MAX_SUBCARRIERS NUM_SUBCARRIER_PER_RESOURCE_BLOCK * NUMRESOURCEBLOCKS_FFT2048
#define MAX_MODULATION_ORDER 6
#define MAX_MODULATION_SIZE 64

static const rf_phreaker::frequency_type lte_bandwidth_1_4_mhz_sampling_rate = khz(1920);
static const rf_phreaker::frequency_type lte_bandwidth_3_mhz_sampling_rate = khz(3840);
static const rf_phreaker::frequency_type lte_bandwidth_5_mhz_sampling_rate = khz(7680);
static const rf_phreaker::frequency_type lte_bandwidth_10_mhz_sampling_rate = khz(15360);
static const rf_phreaker::frequency_type lte_bandwidth_15_mhz_sampling_rate = khz(23040);
static const rf_phreaker::frequency_type lte_bandwidth_20_mhz_sampling_rate = khz(30720);

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
	FRAMENUMSAMPLES_FFT1536 = 230400,
	FRAMENUMSAMPLES_FFT2048 = 307200,
};

enum LteCyclicPrefixSamples
{
	CP_SAMPLES_FFT256_SYMBOL_0 = 20,
	CP_SAMPLES_FFT256_SYMBOL_1TO6 = 18,
	CP_SAMPLES_FFT512_SYMBOL_0 = 40,
	CP_SAMPLES_FFT512_SYMBOL_1TO6 = 36,
	CP_SAMPLES_FFT1024_SYMBOL_0 = 80,
	CP_SAMPLES_FFT1024_SYMBOL_1TO6 = 72,
	CP_SAMPLES_FFT1536_SYMBOL_0 = 120,
	CP_SAMPLES_FFT1536_SYMBOL_1TO6 = 108,
	CP_SAMPLES_FFT2048_SYMBOL_0 = 160,
	CP_SAMPLES_FFT2048_SYMBOL_1TO6 = 144,

};

enum LteNumResourceBlocks
{
	NUMRESOURCEBLOCKS_FFT256 = 15,
	NUMRESOURCEBLOCKS_FFT512 = 25,
	NUMRESOURCEBLOCKS_FFT1024 = 50,
	NUMRESOURCEBLOCKS_FFT1536 = 75,
	NUMRESOURCEBLOCKS_FFT2048 = 100,
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
	NUM_BITS_DCI_1A_15MHZ = 43,
	NUM_BITS_DCI_1A_20MHZ = 44,

};

#define LOG2_BASE_E                   1.44269504088896340736 

#define LTE_NULL                      0xFFFF //Used as NULL in the interleaver/de-interleaver functions
#define NUM_REG_PER_CCE               9 //Number of REG per CCE

#define LOCALISED_VRB                 0
#define DISTRIBUTED_VRB               1
#define NUM_BITS_MCS_DCI_FORMAT_1A    5
#define NUM_BITS_HARQ_PROCESS_FDD     3
#define NUM_BITS_HARQ_PROCESS_TDD     4

enum lte_modulation_order
{
	lte_modulation_qpsk = 2,
	lte_modulation_16_qam = 4,
	lte_modulation_64_qam = 6,
};

enum lte_dci_format_type
{
	lte_dci_format_unknown = -1,
	lte_dci_format_0 = 0,
	lte_dci_format_1 = 1,
	lte_dci_format_1a = 2,
	lte_dci_format_1b = 3,
	lte_dci_format_1c = 4,
	lte_dci_format_1d = 5,
	lte_dci_format_2 = 6,
	lte_dci_format_2a = 7,
	lte_dci_format_3 = 8,
	lte_dci_format_3a = 9
};

enum lte_dci_format_1c_const
{
	lte_n_gap_1 = 0,
	lte_n_gap_2 = 1,

	lte_n_gap_1_3mhz = 8,
	lte_n_gap_1_5mhz = 12,
	lte_n_gap_1_10mhz = 27,
	lte_n_gap_1_15mhz = 32,
	lte_n_gap_1_20mhz = 48,

	lte_n_gap_2_10mhz = 9,
	lte_n_gap_2_15mhz = 16,
	lte_n_gap_2_20mhz = 16,

	lte_n_step_rb_3mhz = 2,
	lte_n_step_rb_5mhz = 2,
	lte_n_step_rb_10mhz = 4,
	lte_n_step_rb_15mhz = 4,
	lte_n_step_rb_20mhz = 4,

	lte_num_bits_mcs_dci_1c = 5,

	lte_num_bits_gap_value_dci_1c_3mhz = 0,
	lte_num_bits_gap_value_dci_1c_5mhz = 0,
	lte_num_bits_gap_value_dci_1c_10mhz = 1,
	lte_num_bits_gap_value_dci_1c_15mhz = 1,
	lte_num_bits_gap_value_dci_1c_20mhz = 1,

	lte_vrb_prb_mapping_interleaving_column_len = 4,

	lte_rbg_size_p_3mhz = 2,
	lte_rbg_size_p_5mhz = 2,
	lte_rbg_size_p_10mhz = 3,
	lte_rbg_size_p_15mhz = 4,
	lte_rbg_size_p_20mhz = 4,

};


//5.3.3.1.3, TS36.212
typedef struct
{
	unsigned char dci_format_type;
	unsigned char vrb_type;
	unsigned int resource_block_assignment;
	unsigned char mcs;
	unsigned char harq_process_num;
	unsigned char new_data_indicator_bit;
	unsigned char redundancy_version;
	unsigned char n_1a_prb;


	unsigned char dci_info_valid; //non -standard
	unsigned char start_rb_idx;//non -standard
	unsigned char end_rb_idx; //non -standard
	unsigned char n_gap;
	unsigned char modulation_order;//2 == QPSK,4 == 16QAM, 6 == 64QAM
	LTEMODULATION lte_moduation_type;
	unsigned char tbs_index;
	unsigned int tbs_size;
}lte_info_dci_format_1a;

//5.3.3.1.4, TS36.212
typedef struct
{
	unsigned char dci_info_valid; //non -standard

	unsigned char n_gap;
	unsigned int resource_block_assignment;
	unsigned char mcs;
	unsigned char tbs_index;
	unsigned int tbs_size;
	unsigned char start_vrb_idx;//non -standard
	unsigned char end_vrb_idx; //non -standard
}lte_info_dci_format_1c;

typedef struct
{
	unsigned char num_dci_format_1a;
	unsigned char num_dci_format_1c;
	unsigned char current_idx_dci_format_1a;
	unsigned char current_idx_dci_format_1c;
	lte_info_dci_format_1a pdcch_info_dci_format_1a[6];
	lte_info_dci_format_1c pdcch_info_dci_format_1c[6];
	unsigned char vrb_to_prb_mapping_even_slot[128];
	unsigned char vrb_to_prb_mapping_odd_slot[128];
}lte_info_dci_format;


typedef struct
{
	Ipp32u kk[4];  //PDCCH REG frequency indices
	Ipp32u ll;  //PDCCH REG symbol indices
}st_pdcch_regs;


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

}