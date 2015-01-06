/*
*********************************************************************************************************
* Copyright (c)
* File : LtePdcch.h
* Brief : Header file used for decoding the LTE Control Channel
* Author:Rajesh S. Bagul
* History :
*********************************************************************************************************
*/

#ifndef  __LTEPDCCH_H__
#define  __LTEPDCCH_H__

namespace rf_phreaker {

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

	unsigned char vrb_type;
	unsigned int resource_block_assignment;
	unsigned char mcs;
	unsigned char harq_process_num;
	unsigned char new_data_indicator_bit;
	unsigned char redundancy_version;
	unsigned char n_1a_prb;
}lte_info_dci_format_1c;

typedef struct
{
	unsigned char num_dci_format_1a;
	unsigned char num_dci_format_1c;
	unsigned char current_idx_dci_format_1a;
	unsigned char current_idx_dci_format_1c;
	lte_info_dci_format_1a pdcch_info_dci_format_1a[6];
	lte_info_dci_format_1c pdcch_info_dci_format_1c[6];
}lte_info_dci_format;


typedef struct
{
	Ipp32u kk[4];  //PDCCH REG frequency indices
	Ipp32u ll;  //PDCCH REG symbol indices
}st_pdcch_regs;

extern lte_info_dci_format dci_format_info;

int lte_decode_pdcch(Ipp32fc* inSignal,
	Ipp32fc* hEst,
	Ipp32f* hNoiseVar,
	lte_measurements &LteData,
	unsigned int cellNo,
	unsigned int subFrameIndex,
	unsigned int subframeStartSampleIndex);

int lte_get_freq_indices_pdcch(lte_measurements &LteData,
	unsigned int cell_no,
	st_pdcch_regs *pdcch_regs,
	Ipp32u &num_reg_pdcch,
	Ipp32fc(*fft_output_shifted)[4096]);

int lte_regs_mapping_phich(lte_measurements &LteData,
	Ipp8u(*regs_flag)[MAX_CONTROL_SYMBOL_LENGHT],
	unsigned int cell_no);

int lte_regs_mapping_pdcch(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp8u(*regs_flag)[MAX_CONTROL_SYMBOL_LENGHT],
	Ipp8u(*reference_signal)[MAX_CONTROL_SYMBOL_LENGHT],
	st_pdcch_regs *pdcch_regs,
	Ipp32u &num_reg_pdcch,
	Ipp32fc(*fft_output_shifted)[4096]);


int lte_pdcch_interleave_shift(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32u in_lenght,
	Ipp32u *pdcch_regs_interleaved_shifted_index);
int lte_pdcch_common_search_space_decode(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32f *descrambled_pdcch_llr,
	Ipp32u num_reg_pdcch
	);

int lte_pdcch_decode_dci_1c(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32f *descrambled_pdcch_llr,
	Ipp32u len_llr);

int lte_pdcch_decode_dci_1a(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32f *descrambled_pdcch_llr,
	Ipp32u len_llr);


int lte_cc_rate_dematching(Ipp32f *output_llr, Ipp32u output_len, Ipp32f *input_llr, Ipp32u input_len);

int lte_get_info_dci_format_1a(Ipp32u *dci_1a_bits, lte_info_dci_format &dci_format_info, lte_measurements &LteData, unsigned int cell_no);

}

#endif