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

#include "rf_phreaker/lte_analysis/lte_types.h"

namespace rf_phreaker {


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

int lte_get_info_dci_format_1c(Ipp32u *dci_1c_bits, lte_info_dci_format &dci_format_info, lte_measurements &LteData, unsigned int cell_no);

int lte_vrb_to_prb_mapping(lte_info_dci_format &dci_format_info, lte_measurements &LteData, unsigned int cell_no, unsigned char n_gap);
}

#endif