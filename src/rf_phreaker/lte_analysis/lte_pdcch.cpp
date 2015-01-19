/*
*********************************************************************************************************
* Copyright (c)
* File : LtePdcch.cpp
* Brief : Decoding LTE Control Channel
* Author:Rajesh S. Bagul
* History :
*********************************************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <cmath>
#include "lte_common.h"
#include "lte_analysis.h"

#include "lte_pdcch.h"
#include "lte_pdcch_dci_table.h"
#include "lte_crc_16.h"

namespace rf_phreaker {

//lte_info_dci_format_1a pdcch_info_dci_format_1a[6];
lte_info_dci_format dci_format_info;

ipp_32f_array pdcch_llr_buf(4096 * 100);
ipp_32f_array descrambled_pdcch_llr_buf2(4096 * 100);
ipp_32u_array scrambling_seq_pdcch_buf(4096 * 10);



/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_decode_pdcch(Ipp32fc* inSignal,
	Ipp32fc* h_est,
	Ipp32f* h_noise_var,
	lte_measurements &LteData,
	unsigned int cell_no,
	unsigned int subFrameIndex,
	unsigned int subframeStartSampleIndex)

{
	Ipp32fc fft_output[3][4096], fft_output_shifted[3][4096];	// Static Allocation for Maximum size FFT 
	Ipp32fc h_est_pdcch[NUM_RE_PER_REG * NUM_ANTENNA_MAX];
	Ipp32fc lte_pdcch_reg_symbols[NUM_RE_PER_REG];
	st_pdcch_regs pdcch_regs[1024]; // PDCCH Resource Element Groups

	Ipp32u re_index_kk = 0, re_index_ll = 0, num_reg_pdcch = 0;
	Ipp32u pdcch_regs_interleaved_shifted_index[1024]/*,scrambling_seq_pdcch[4096]*/;

	Ipp32u temp;//Number of REGS for PDCCH
	Ipp32u c_init, nSlotNum = 0;

	pdcch_llr_buf.zero_out();
	descrambled_pdcch_llr_buf2.zero_out();
	scrambling_seq_pdcch_buf.zero_out();
	Ipp32f *pdcch_llr = pdcch_llr_buf.get();
	Ipp32f *descrambled_pdcch_llr = descrambled_pdcch_llr_buf2.get();
	Ipp32u *scrambling_seq_pdcch = scrambling_seq_pdcch_buf.get();


	dci_format_info.num_dci_format_1a = 0;
	dci_format_info.current_idx_dci_format_1a = 0;

	dci_format_info.num_dci_format_1c = 0;
	dci_format_info.current_idx_dci_format_1c = 0;

	//h_noise_var[0] = h_noise_var[1] = 169800.0;
	h_noise_var[0] = h_noise_var[1] = 10000.0;
	//h_noise_var[0] = h_noise_var[1] = 100.0;

	// TODO - ecs removed - if(subFrameIndex==5)
	temp = 0;

	//FFT Operation
	for(unsigned int control_symbol_idx = 0; control_symbol_idx < LteData[cell_no].lteControlSysmbolLenght; control_symbol_idx++) {
		if(control_symbol_idx > 0) {
			myfft(&fft_output[control_symbol_idx][0], //Frequency Domain Output
				inSignal + subframeStartSampleIndex
				+ LteData[cell_no].cPSamplesSymbol0
				+ control_symbol_idx * LteData[cell_no].fftSize
				+ control_symbol_idx * LteData[cell_no].cPSamplesSymbol1to6, //Time Domain Input
				LteData[cell_no].fftSize); //FFT Size
		}
		else {
			myfft(&fft_output[control_symbol_idx][0], //Frequency Domain Output
				inSignal + subframeStartSampleIndex + LteData[cell_no].cPSamplesSymbol0, //Time Domain Input
				LteData[cell_no].fftSize); //FFT Size

		}


		myfftshift(&fft_output_shifted[control_symbol_idx][0], //Destination
			&fft_output[control_symbol_idx][0], //Source
			LteData[cell_no].fftSize); //FFT Size
	}


	//Determine PDCCH Frequency Indices
	lte_get_freq_indices_pdcch(LteData, cell_no, pdcch_regs, num_reg_pdcch, fft_output_shifted);


	//PDCCH Interleave and cyclic shift
	lte_pdcch_interleave_shift(LteData, cell_no, num_reg_pdcch, pdcch_regs_interleaved_shifted_index);

	//MIMO Detection per PDCCH REG
	for(unsigned int regs = 0; regs < num_reg_pdcch; regs++) {

		for(unsigned ff = 0; ff < NUM_RE_PER_REG; ++ff) //NUM_RE_PER_REG ==4
		{
			re_index_kk = pdcch_regs[regs].kk[ff];
			re_index_ll = pdcch_regs[regs].ll;

			lte_pdcch_reg_symbols[ff] = fft_output_shifted[re_index_ll][re_index_kk];

			for(unsigned int antNum = 0; antNum < LteData[cell_no].NumAntennaPorts; antNum++) {
				h_est_pdcch[antNum * NUM_RE_PER_REG + ff] = h_est[antNum * LteData[cell_no].fftSize * OFDM_SYMBOLS_PER_FRAME
					+ subFrameIndex * OFDM_SYMBOLS_PER_SUBFRAME *LteData[cell_no].fftSize
					+ re_index_ll * LteData[cell_no].fftSize
					+ re_index_kk
				];
			}


		}
		/* MIMO Detection - Transmit Diversity */
		stDiversityDet(&pdcch_llr[(2 * NUM_RE_PER_REG * pdcch_regs_interleaved_shifted_index[regs])],
			lte_pdcch_reg_symbols, // PDCCH REG modulation symbols
			h_est_pdcch,
			NUM_RE_PER_REG,//Value == 4
			LteData[cell_no].NumAntennaPorts, // Number of Antennas 
			MQPSK,//Modulation Type == QPSK
			h_noise_var);
	}
	//Descrambling

	//num_reg_pdcch = 144;
	/* Descrambling */
	nSlotNum = 2 * subFrameIndex;
	c_init = (nSlotNum / 2) *(1 << 9) + LteData[cell_no].RsRecord.ID; //6.7.1 TS36.211

	generate_PN_seq(scrambling_seq_pdcch, //PDCCH Scambling Sequence
		c_init, //c_init
		num_reg_pdcch* NUM_RE_PER_REG * 2);


	softDeSrambling(descrambled_pdcch_llr,// Output Descrambled LLR Data
		pdcch_llr,//Input LLR data
		num_reg_pdcch* NUM_RE_PER_REG * 2,//lenght of the sequence
		scrambling_seq_pdcch);//Scrambling bits

	//Lte common search space blind decoding
	lte_pdcch_common_search_space_decode(LteData, cell_no, descrambled_pdcch_llr, num_reg_pdcch);

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_get_freq_indices_pdcch
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_get_freq_indices_pdcch(lte_measurements &LteData,
	unsigned int cell_no,
	st_pdcch_regs *pdcch_regs,
	Ipp32u &num_reg_pdcch,
	Ipp32fc(*fft_output_shifted)[4096])

{

	Ipp8u regs_flag[MAX_FFT_SIZE][MAX_CONTROL_SYMBOL_LENGHT];
	//Ipp8u reference_signal[NUM_SUBCARRIER_PER_RESOURCE_BLOCK][MAX_CONTROL_SYMBOL_LENGHT];
	Ipp8u reference_signal[MAX_FFT_SIZE][MAX_CONTROL_SYMBOL_LENGHT];
	Ipp8u ref_signal_start_index;
	Ipp32u kb, k;

	//ippsSet_8u(ZEROS,(Ipp8u*)regs_flag,MAX_CONTROL_SYMBOL_LENGHT * MAX_FFT_SIZE);
	//ippsSet_8u(ONES,(Ipp8u*)reference_signal,MAX_CONTROL_SYMBOL_LENGHT * NUM_SUBCARRIER_PER_RESOURCE_BLOCK);

	memset(regs_flag, ZEROS, MAX_CONTROL_SYMBOL_LENGHT * MAX_FFT_SIZE);
	memset(reference_signal, ZEROS, MAX_CONTROL_SYMBOL_LENGHT * NUM_SUBCARRIER_PER_RESOURCE_BLOCK);

	ref_signal_start_index = LteData[cell_no].RsRecord.ID % 3;

	//Marking Resource Elements occupied by Reference Signal in first symbol of first slot of the Resource Block - 6.2.4 TS36.211
	reference_signal[ref_signal_start_index][0] = 1;
	reference_signal[ref_signal_start_index + 3][0] = 1;
	reference_signal[ref_signal_start_index + 6][0] = 1;
	reference_signal[ref_signal_start_index + 9][0] = 1;

	//Marking the first resource element of the REG belonging to first symbol - 6.2.4 TS36.211
	regs_flag[0][0] = regs_flag[6][0] = 1;//Symbol 0,Slot 0

	//Marking the first element of the REG and Reference signal Resource Element in the second symbol of the first slot - 6.2.4 TS36.211
	if(LteData[cell_no].lteControlSysmbolLenght > 1) {
		if(LteData[cell_no].NumAntennaPorts <= 2) {
			regs_flag[0][1] = 1; //Symbol 1, Slot 0
			regs_flag[4][1] = 1;
			regs_flag[8][1] = 1;
		}
		else //Num Antennas greater than 2
		{
			regs_flag[0][1] = regs_flag[6][1] = 1;//Symbol 1,Slot 0

			reference_signal[ref_signal_start_index][1] = 1;
			reference_signal[ref_signal_start_index + 3][1] = 1;
			reference_signal[ref_signal_start_index + 6][1] = 1;
			reference_signal[ref_signal_start_index + 9][1] = 1;
		}
	}
	//Marking the first element of the REG and Reference signal Resource Element in the third symbol of the first slot - 6.2.4 TS36.211
	if(LteData[cell_no].lteControlSysmbolLenght > 2) {
		regs_flag[0][2] = 1; //Symbol 2, Slot 0
		regs_flag[4][2] = 1;
		regs_flag[8][2] = 1;
	}

	//Marking the first element of the REG and Reference signal Resource Element in the fourth symbol of the first slot - 6.2.4 TS36.211
	if(LteData[cell_no].lteControlSysmbolLenght > 3) {
		if(LteData[cell_no].CyclicPrefix == Normal) {
			regs_flag[0][3] = 1; //Symbol 3, Slot 0
			regs_flag[4][3] = 1;
			regs_flag[8][3] = 1;
		}
		else // Extended Cyclic Prefix
		{
			regs_flag[0][3] = regs_flag[6][3] = 1;//Symbol 1,Slot 0

			reference_signal[ref_signal_start_index][3] = 1;
			reference_signal[ref_signal_start_index + 3][3] = 1;
			reference_signal[ref_signal_start_index + 6][3] = 1;
			reference_signal[ref_signal_start_index + 9][3] = 1;
		}
	}

	//Populate the rest of the Resouce Blocks

	for(unsigned int ii = 1; ii <= LteData[cell_no].numResouceBlocks; ii++) {
		memcpy(&regs_flag[ii*NUM_SUBCARRIER_PER_RESOURCE_BLOCK][0],
			&regs_flag[0][0],
			48);// Size = 48 = Subcarriers per RB(12) * MAX_CONTROL_SYMBOL_LENGHT(4)

		memcpy(&reference_signal[ii*NUM_SUBCARRIER_PER_RESOURCE_BLOCK][0],
			&reference_signal[0][0],
			48);// Size = 48 = Subcarriers per RB(12) * MAX_CONTROL_SYMBOL_LENGHT(4)
	}


	//Mark the REGs occupied by PCFICH

	// Resource Element number of the first PCFICH quadruplet
	kb = 6 * ((LteData[cell_no].RsRecord.ID) % (2 * LteData[cell_no].numResouceBlocks)); //6.7.4 TS 36.211

	for(unsigned int zp = 0; zp < 4; zp++) {
		//Calculating PCFICH Subcarrier Index - Resource Element
		k = ((kb + (unsigned int)floor((double)zp*LteData[cell_no].numResouceBlocks / 2)
			* NUM_SUBCARRIER_PER_RESOURCE_BLOCK / 2))
			%
			(LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK);
		//6.7.4 TS 36.211
		regs_flag[k][0] = 2; //Marking PCFICH REGs with label ==2

	}

	//Mark the REGs occupied by PHICH
	lte_regs_mapping_phich(LteData, regs_flag, cell_no);

	//Get PDCCH REG indices
	lte_regs_mapping_pdcch(LteData, cell_no, regs_flag, reference_signal, pdcch_regs, num_reg_pdcch, fft_output_shifted);

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_regs_mapping_phich
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_regs_mapping_phich(lte_measurements &LteData,
	Ipp8u(*regs_flag)[MAX_CONTROL_SYMBOL_LENGHT],
	unsigned int cell_no) {
	Ipp32u n_group_phich; //Number of PHICH Groups
	Ipp8u duration_phich;
	Ipp32u regs_non_pcfich[MAX_CONTROL_SYMBOL_LENGHT][MAX_FFT_SIZE];
	Ipp32u len_regs_non_pcfich[MAX_CONTROL_SYMBOL_LENGHT], k, ni_b;

	//6.9 TS36.211
	n_group_phich = (LteData[cell_no].phich_resources *
		LteData[cell_no].numResouceBlocks / 8) / 6 + 1;//phich_resources = 1,3,6,12 hence dividing it by 1/6, 6.9 TS36.211

	if(LteData[cell_no].phich_duration == 1) {
		duration_phich = 1;
	}
	else {
		duration_phich = 3;
	}

	//Select the REGs not assigned to PCFICH
	for(unsigned int ll = 0; ll < duration_phich; ++ll) {
		len_regs_non_pcfich[ll] = 0;
		for(unsigned int kk = 0; kk < LteData[cell_no].numResouceBlocks * NUM_SUBCARRIER_PER_RESOURCE_BLOCK; ++kk) {
			if(regs_flag[kk][ll] == 1) {
				regs_non_pcfich[ll][len_regs_non_pcfich[ll]] = kk;
				++len_regs_non_pcfich[ll];
			}
		}
	}

	//6.9.3 TS36.211 Steps 1-10
	for(unsigned int m1 = 0; m1 < n_group_phich; m1++) {
		if(duration_phich = 1) //Step 8, 6.9.3 TS36.211
		{
			//First PHICH Quadruplet (i==0)
			ni_b = (Ipp32u)(floor((double)LteData[cell_no].RsRecord.ID * len_regs_non_pcfich[0] / len_regs_non_pcfich[0]) + m1)
				% len_regs_non_pcfich[0];
			k = regs_non_pcfich[0][ni_b];
			regs_flag[k][0] = 3; //Tagging PHICH REGs with label ==3;

			//Second PHICH Quadruplet (i==1)
			ni_b = (Ipp32u)((floor((double)LteData[cell_no].RsRecord.ID * len_regs_non_pcfich[0] / len_regs_non_pcfich[0]) + m1) + floor((double)len_regs_non_pcfich[0] / 3))
				% len_regs_non_pcfich[0];
			k = regs_non_pcfich[0][ni_b];
			regs_flag[k][0] = 3; //Tagging PHICH REGs with label ==3;

			//Third PHICH Quadruplet (i==2)
			ni_b = (Ipp32u)((floor((double)LteData[cell_no].RsRecord.ID * len_regs_non_pcfich[0] / len_regs_non_pcfich[0]) + m1) + floor((double)2 * len_regs_non_pcfich[0] / 3))
				% len_regs_non_pcfich[0];
			k = regs_non_pcfich[0][ni_b];
			regs_flag[k][0] = 3; //Tagging PHICH REGs with label ==3;

		}
		else //Extended PHICH duration, MBSFN 
		{

			//First PHICH Quadruplet (i==0)
			ni_b = (Ipp32u)(floor((double)LteData[cell_no].RsRecord.ID * len_regs_non_pcfich[0] / len_regs_non_pcfich[1]) + m1)
				% len_regs_non_pcfich[0];
			k = regs_non_pcfich[0][ni_b];
			regs_flag[k][0] = 3; //Tagging PHICH REGs with label ==3;

			//Second PHICH Quadruplet (i==1)
			ni_b = (Ipp32u)((floor((double)LteData[cell_no].RsRecord.ID * len_regs_non_pcfich[1] / len_regs_non_pcfich[1]) + m1) + floor((double)len_regs_non_pcfich[0] / 3))
				% len_regs_non_pcfich[0];
			k = regs_non_pcfich[0][ni_b];
			regs_flag[k][0] = 3; //Tagging PHICH REGs with label ==3;

			//Third PHICH Quadruplet (i==2)
			ni_b = (Ipp32u)((floor((double)LteData[cell_no].RsRecord.ID * len_regs_non_pcfich[2] / len_regs_non_pcfich[1]) + m1) + floor(2 * (double)len_regs_non_pcfich[0] / 3))
				% len_regs_non_pcfich[0];
			k = regs_non_pcfich[0][ni_b];
			regs_flag[k][0] = 3; //Tagging PHICH REGs with label ==3;

		}
	}
	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_regs_mapping_pdcch
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_regs_mapping_pdcch(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp8u(*regs_flag)[MAX_CONTROL_SYMBOL_LENGHT],
	Ipp8u(*reference_signal)[MAX_CONTROL_SYMBOL_LENGHT],
	st_pdcch_regs *pdcch_regs,
	Ipp32u &num_reg_pdcch,
	Ipp32fc(*fft_output_shifted)[4096]) {
	Ipp32u reg_re_count = 0, ref_signal_re_count = 0;


	//LteData[cell_no].rssi = 0;
	//LteData[cell_no].rsrp = 0;


	for(unsigned int kk = 0; kk < LteData[cell_no].numResouceBlocks * NUM_SUBCARRIER_PER_RESOURCE_BLOCK; kk++) {
		for(unsigned int ll = 0; ll < LteData[cell_no].lteControlSysmbolLenght; ll++) {
#if 0
			if (ll == 0)
			{

				LteData[cell_no].rssi = (fft_output_shifted[ll][kk].re * fft_output_shifted[ll][kk].re)
					+ (fft_output_shifted[ll][kk].im * fft_output_shifted[ll][kk].im);

				if ((kk - LteData[cell_no].fft_subcarrier_start_index) >= 0 )
				{
					if (reference_signal[kk - LteData[cell_no].fft_subcarrier_start_index][ll] == 1)
					{
						LteData[cell_no].rsrp = (fft_output_shifted[ll][kk].re * fft_output_shifted[ll][kk].re)
							+ (fft_output_shifted[ll][kk].im * fft_output_shifted[ll][kk].im);
						ref_signal_re_count++;
					}

				}


			}
#endif

			if(regs_flag[kk][ll] == 1) {
				regs_flag[kk][ll] = 4;//Tagging the PDCCH REGs with label==4;		

				pdcch_regs[num_reg_pdcch].ll = ll;
				reg_re_count = 0;

				for(unsigned int jj = 0; jj < 6; jj++) {

					if(reference_signal[(kk % NUM_SUBCARRIER_PER_RESOURCE_BLOCK) + jj][ll] == 0) {
						if((kk + jj) < (LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK / 2))
							pdcch_regs[num_reg_pdcch].kk[reg_re_count] = kk + jj + LteData[cell_no].fft_subcarrier_start_index;
						else
							pdcch_regs[num_reg_pdcch].kk[reg_re_count] = kk + jj + LteData[cell_no].fft_subcarrier_start_index + 1;

						if(++reg_re_count == NUM_RE_PER_REG)
							break;
					}
				}

				num_reg_pdcch++;
			}
		}
	}

	//PDCCH Quadruplets Interleaving

	//LteData[cell_no].rsrp = (LteData[cell_no].rsrp) / (ref_signal_re_count);

	//LteData[cell_no].rsrq =  10 * log10(LteData[cell_no].numResouceBlocks * LteData[cell_no].rsrp / LteData[cell_no].rssi);

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_pdcch_interleave_shift
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
//5.1.4.2.1, TS36.212
int lte_pdcch_interleave_shift(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32u in_lenght,
	Ipp32u *pdcch_regs_interleaved_shifted_index) {

	Ipp8u c_cc_subblock = 32;
	Ipp32u r_cc_subblock; //Number of rows
	Ipp32u n_null;
	Ipp32u interleave_matrix[128][32];//allocating a static interleaver matrix with rows ==128, column ==32
	Ipp32u k_pi, column_idx, row_idx, idx = 0, output_indices[1024];
	Ipp8u permutation_column[32] = {1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, //5.1.4.2.1 TS36.212
		15, 31, 0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26,
		6, 22, 14, 30};

	r_cc_subblock = in_lenght / c_cc_subblock + 1;
	k_pi = r_cc_subblock * c_cc_subblock;

	n_null = k_pi - in_lenght;

	//Fill the interleaver matrix row-wise
	for(unsigned int ii = 0; ii < k_pi; ii++) {
		if(ii < n_null) {
			//output_indices[ii] = 0;
			interleave_matrix[ii / 32][ii % 32] = 0xFFFF; //Null Element
		}
		else {
			//output_indices[ii] = ii - n_null;
			interleave_matrix[ii / 32][ii % 32] = ii - n_null;
		}
	}

	//Read the matrix column wise according to the column permutation vector

	for(unsigned int cc = 0; cc < 32; cc++) {
		column_idx = permutation_column[cc];

		for(unsigned int row_idx = 0; row_idx < r_cc_subblock; row_idx++) {
			if(interleave_matrix[row_idx][column_idx] != 0xFFFF) {
				output_indices[idx] = interleave_matrix[row_idx][column_idx];
				++idx;
			}
		}
	}
	//cyclic Shift to the interleaved PDCCH quadruplets - 6.8.5 TS36.211
	for(unsigned int ii = 0; ii < in_lenght; ii++) {
		pdcch_regs_interleaved_shifted_index[ii] = output_indices[(ii + LteData[cell_no].RsRecord.ID) % in_lenght];
	}

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_pdcch_common_search_space_decode
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_pdcch_common_search_space_decode(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32f *descrambled_pdcch_llr,
	Ipp32u num_reg_pdcch
	) {
	Ipp32u cce_size, m_l, bit_size;
	Ipp8u aggregation_level[] = {4, 8};

	if(num_reg_pdcch > 144)
		num_reg_pdcch = 144; //common search space consists of 16 CCEs = 16 X 9 = 144 REGs - 9.1.1, TS36.213


	cce_size = num_reg_pdcch / NUM_REG_PER_CCE; //NUM_REG_PER_CCE = 9

	for(unsigned int ii = 0; ii < 2; ii++)//Two aggregation level
	{
		m_l = cce_size / aggregation_level[ii];
		bit_size = aggregation_level[ii] * 72;

		for(unsigned int jj = 0; jj < m_l; jj++) {


			//Decoding DCI FORMAT 1A
			lte_pdcch_decode_dci_1a(LteData, cell_no, &descrambled_pdcch_llr[jj*bit_size], bit_size);
			//lte_pdcch_decode_dci_1c
			lte_pdcch_decode_dci_1c(LteData, cell_no, &descrambled_pdcch_llr[jj*bit_size], bit_size);
		}


	}

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_pdcch_decode_dci_1c
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_pdcch_decode_dci_1c(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32f *descrambled_pdcch_llr,
	Ipp32u len_llr) {
	Ipp32f rate_dematched_llr[512];
	Ipp32u dci_1c_bitsize, dci_1c_bits[64], temp[64], crc_checksum;
	unsigned char CRCByteSeq[2], dateByteSeq[64];

	//dci_1c_bitsize = 41;
	dci_1c_bitsize = LteData[cell_no].num_bits_dci_1C + 16;
	//Rate Dematching
	lte_cc_rate_dematching(rate_dematched_llr, 3 * dci_1c_bitsize, descrambled_pdcch_llr, len_llr);
	//CC Decoding
	LTE_CC_decoding(dci_1c_bits, rate_dematched_llr, 3 * dci_1c_bitsize);

	for(unsigned int ii = (dci_1c_bitsize - 16); ii < dci_1c_bitsize; ii++) {
		if(dci_1c_bits[ii])
			dci_1c_bits[ii] = 0;
		else
			dci_1c_bits[ii] = 1;

	}

	//bit2byte(dateByteSeq, dci_1a_bits, 41, 0);
	bit2byte(dateByteSeq, dci_1c_bits, dci_1c_bitsize, 0);

	//lte_crc_16(&crc_checksum, dateByteSeq, 41);
	lte_crc_16(&crc_checksum, dateByteSeq, dci_1c_bitsize);


	if(crc_checksum == 0) //crc_checksum == 0 for a correctly decoded DCI
	{

		dci_format_info.num_dci_format_1c = dci_format_info.num_dci_format_1c + 1;
		dci_format_info.current_idx_dci_format_1c = dci_format_info.num_dci_format_1c - 1;
		lte_get_info_dci_format_1c(dci_1c_bits, dci_format_info, LteData, cell_no);

	}


	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_pdcch_decode_dci_1a
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_pdcch_decode_dci_1a(lte_measurements &LteData,
	unsigned int cell_no,
	Ipp32f *descrambled_pdcch_llr,
	Ipp32u len_llr) {
	Ipp32f rate_dematched_llr[512];
	Ipp32u dci_1a_bitsize, dci_1a_bits[64], temp[64], crc_checksum;
	unsigned char CRCByteSeq[2], dateByteSeq[64];

	//dci_1a_bitsize = 41;
	dci_1a_bitsize = LteData[cell_no].num_bits_dci_1A;
	//Rate Dematching
	lte_cc_rate_dematching(rate_dematched_llr, 3 * dci_1a_bitsize, descrambled_pdcch_llr, len_llr);
	//CC Decoding
	LTE_CC_decoding(dci_1a_bits, rate_dematched_llr, 3 * dci_1a_bitsize);

	//CRC Check

	//for(unsigned int ii = 25;ii<41;ii++)
	for(unsigned int ii = (dci_1a_bitsize - 16); ii < dci_1a_bitsize; ii++) {
		if(dci_1a_bits[ii])
			dci_1a_bits[ii] = 0;
		else
			dci_1a_bits[ii] = 1;

	}

	//bit2byte(dateByteSeq, dci_1a_bits, 41, 0);
	bit2byte(dateByteSeq, dci_1a_bits, dci_1a_bitsize, 0);

	//lte_crc_16(&crc_checksum, dateByteSeq, 41);
	lte_crc_16(&crc_checksum, dateByteSeq, dci_1a_bitsize);


	if(crc_checksum == 0) //crc_checksum == 0 for a correctly decoded DCI
	{

		dci_format_info.num_dci_format_1a = dci_format_info.num_dci_format_1a + 1;
		dci_format_info.current_idx_dci_format_1a = dci_format_info.num_dci_format_1a - 1;
		lte_get_info_dci_format_1a(dci_1a_bits, dci_format_info, LteData, cell_no);

	}

	return LTE_SUCCESS;
}
/*
*********************************************************************************************************
* Function:lte_cc_rate_dematching
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_cc_rate_dematching(Ipp32f *output_llr, Ipp32u output_len, Ipp32f *input_llr, Ipp32u input_len) {

	Ipp8u c_cc_subblock = 32;
	Ipp32u r_cc_subblock; //Number of rows
	Ipp32u n_null, k_w, in_lenght;
	Ipp32u interleave_matrix[128][32];//allocating a static interleaver matrix with rows ==128, column ==32
	Ipp32u k_pi, column_idx, row_idx, idx = 0, w_k[2048], e[2048], j = 0, k = 0, temp;
	Ipp8u permutation_column[32] = {1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, //5.1.4.2.1 TS36.212
		15, 31, 0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26,
		6, 22, 14, 30};


	in_lenght = output_len / 3;
	r_cc_subblock = in_lenght / c_cc_subblock + 1;
	k_pi = r_cc_subblock * c_cc_subblock;
	k_w = 3 * k_pi;
	n_null = k_pi - in_lenght;

	for(unsigned ll = 0; ll < 512; ll++) {
		output_llr[ll] = 0;
	}

	for(unsigned int kp = 0; kp < 3; kp++) {
		//Fill the interleaver matrix row-wise
		for(unsigned int ii = 0; ii < k_pi; ii++) {
			if(ii < n_null) {
				//output_indices[ii] = 0;
				interleave_matrix[ii / 32][ii % 32] = LTE_NULL; //Null Element
			}
			else {
				//output_indices[ii] = ii - n_null;
				interleave_matrix[ii / 32][ii % 32] = (kp*in_lenght) + ii - n_null;
			}
		}

		//Read the matrix column wise according to the column permutation vector

		for(unsigned int cc = 0; cc < 32; cc++) {
			column_idx = permutation_column[cc];

			for(unsigned int row_idx = 0; row_idx < r_cc_subblock; row_idx++) {
				//if(interleave_matrix[row_idx][column_idx]!=0xFFFF)	
				{
					w_k[idx] = interleave_matrix[row_idx][column_idx];
					++idx;
				}
			}
		}
	}

	while(k < input_len) {
		temp = w_k[j % k_w];
		if(temp != LTE_NULL) {
			e[k] = temp;
			k = k + 1;
		}
		j = j + 1;
	}

	for(j = 0; j < input_len; j++)
		//for(j=0;j<123;j++)
	{
		k = e[j];
		output_llr[k] = output_llr[k] + input_llr[j];
	}

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:lte_get_info_dci_format_1a
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_get_info_dci_format_1a(Ipp32u *dci_1a_bits, lte_info_dci_format &dci_format_info, lte_measurements &LteData, unsigned int cell_no) {
	unsigned char index_dci_1a, bit_position, temp = 0;
	unsigned int l_crbs = 0, t1 = 0, t2 = 0, numbits_resource_assignment = 0;
	float fnumbits_resource_assignment = 0;

	index_dci_1a = dci_format_info.current_idx_dci_format_1a;

	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].dci_format_type = dci_1a_bits[0];
	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].vrb_type = dci_1a_bits[1];

	if(dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].vrb_type == LOCALISED_VRB) {
		fnumbits_resource_assignment = ceil(log((float)LteData[cell_no].numResouceBlocks
			*(float)(LteData[cell_no].numResouceBlocks + 1) / 2) * LOG2_BASE_E);

		numbits_resource_assignment = (unsigned int)fnumbits_resource_assignment;

		dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].resource_block_assignment = 0x0;
		for(unsigned int ii = 0; ii < numbits_resource_assignment; ii++) {
			dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].resource_block_assignment += dci_1a_bits[2 + ii] << (numbits_resource_assignment - 1 - ii);
			//temp += dci_1a_bits[2+ii]<<(numbits_resource_assignment-1-ii); 
		}

		t1 = dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].resource_block_assignment / LteData[cell_no].numResouceBlocks;
		t2 = dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].resource_block_assignment % LteData[cell_no].numResouceBlocks;

		if(t1 <= LteData[cell_no].numResouceBlocks / 2) //7.1.6.3,TS36.213
		{
			l_crbs = t1 + 1;
			dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].start_rb_idx = t2;
			if(l_crbs > LteData[cell_no].numResouceBlocks - dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].start_rb_idx) {
				l_crbs = LteData[cell_no].numResouceBlocks - t1 + 1;
				dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].start_rb_idx = LteData[cell_no].numResouceBlocks - t2 - 1;
			}

		}
		else {
			l_crbs = LteData[cell_no].numResouceBlocks - t1 + 1;
			dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].start_rb_idx = LteData[cell_no].numResouceBlocks - t2 - 1;
		}

	}

	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].end_rb_idx = dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].start_rb_idx + l_crbs - 1;

	//Modulation and Coding Scheme

	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].mcs = 0x0;
	for(unsigned int jj = 0; jj < NUM_BITS_MCS_DCI_FORMAT_1A; jj++) {
		dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].mcs += dci_1a_bits[2 + numbits_resource_assignment + jj] << (NUM_BITS_MCS_DCI_FORMAT_1A - 1 - jj);
	}
	bit_position = 2 + numbits_resource_assignment + NUM_BITS_MCS_DCI_FORMAT_1A;

	//TODO-- Handling for HARQ Process Number - TDD case (4 bits)

	//HARQ Process number - FDD (3 bits)
	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].harq_process_num = 0x0;
	for(unsigned int kk = 0; kk < NUM_BITS_HARQ_PROCESS_FDD; kk++) {
		dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].harq_process_num += dci_1a_bits[bit_position] << (NUM_BITS_HARQ_PROCESS_FDD - 1 << kk);
	}

	bit_position = bit_position + NUM_BITS_HARQ_PROCESS_FDD;

	//New Data Indicator

	//Checking the N_GAP Values always assuming FORMAT 1A is scrambled by SI-RNTI,P-RNTI,RA-RNTI
	if(LteData[cell_no].numResouceBlocks >= 50) {
		if(dci_1a_bits[bit_position])
			dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].n_gap = 0xFFFF;//TODO -- N_gap2
		else
			dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].n_gap = 0xEEEE;//TODO -- N_gap1

	}
	else {
		dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].new_data_indicator_bit = dci_1a_bits[bit_position];
	}

	bit_position = bit_position + 1;

	//Redundancy Version

	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].redundancy_version = (dci_1a_bits[bit_position] << 1) + dci_1a_bits[bit_position + 1];

	bit_position = bit_position + 2;

	//TPC Command for PUCCH - 2 bits
	//Assuming FORMAT 1A is scrambled with SI-RNTI,P-RNTI,RA-RNTI
	if(dci_1a_bits[bit_position + 1])
		dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].n_1a_prb = 3;
	else
		dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].n_1a_prb = 2;

	bit_position = bit_position + 2;

	//Downlink Assignment Index - for TDD only

	//Consulting Table 7.1.7.1-1,TS36.213
	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].modulation_order =
		modulation_tbs_index[dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].mcs][0];
	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].tbs_index = dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].mcs;

	//modulation_tbs_index[dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].mcs][1];


	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].tbs_size =
		transport_block_size_table[dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].tbs_index][dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].n_1a_prb - 1];

	// We assume that format 1A is using SI-RNTI.  Therefore it always has a modulation type of MQPSK.
	dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].lte_moduation_type = MQPSK;
	//switch(dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].modulation_order)
	//{
	//	case(lte_modulation_qpsk):
	//							  dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].lte_moduation_type = MQPSK;
	//							  break;
	//	case(lte_modulation_16_qam):
	//							  dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].lte_moduation_type = M16QAM;
	//							  break;
	//
	//	case(lte_modulation_64_qam):
	//							   dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].lte_moduation_type = M64QAM;
	//							   break;
	//
	//	default:
	//		return LTE_ERROR_PDCCH_MODULATION_ORDER;
	//
	//};

	temp = 0;

	//printf("\nDecoded DCI 1A :\n\tStart RB Index == %d\n\tEnd RB Index == %d\n\tRedundancy Version == %d\n\tTBS == %d\n\n",dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].start_rb_idx,
	//	     dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].end_rb_idx,dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].redundancy_version,dci_format_info.pdcch_info_dci_format_1a[index_dci_1a].tbs_size);

	return LTE_SUCCESS;
}



/*
*********************************************************************************************************
* Function:lte_get_info_dci_format_1c
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
//Section 5.3.3.1.4  TS 36.212
int lte_get_info_dci_format_1c(Ipp32u *dci_1c_bits, lte_info_dci_format &dci_format_info, lte_measurements &LteData, unsigned int cell_no) {

	unsigned char index_dci_1c, bit_position = 0;
	unsigned int l_crbs = 0, t1 = 0, t2 = 0, n_dl_vrb_dash = 0;

	index_dci_1c = dci_format_info.current_idx_dci_format_1c;

	dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].n_gap = 0; //default Ngap = Ngap1

	if(LteData[cell_no].numResouceBlocks >= 50) {
		dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].n_gap = dci_1c_bits[bit_position];
		bit_position++;
	}

	lte_vrb_to_prb_mapping(dci_format_info, LteData, cell_no, dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].n_gap);

	dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].resource_block_assignment = 0;

	for(unsigned int kk = 0; kk < LteData[cell_no].resource_block_assign_1c_bits; kk++) {
		dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].resource_block_assignment += dci_1c_bits[bit_position + kk] << (LteData[cell_no].resource_block_assign_1c_bits - 1 - kk);
	}

	// 7.1.6.3, TS 36.213

	n_dl_vrb_dash = LteData[cell_no].num_dl_vrb_gap_1 / LteData[cell_no].num_step_rb;

	t1 = dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].resource_block_assignment / n_dl_vrb_dash;
	t2 = dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].resource_block_assignment % n_dl_vrb_dash;

	if(t1 <= n_dl_vrb_dash / 2)				// 7.1.6.3, TS36.213
	{
		l_crbs = t1 + 1;
		dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].start_vrb_idx = t2;
		if(l_crbs > n_dl_vrb_dash - dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].start_vrb_idx) {
			l_crbs = n_dl_vrb_dash - t1 + 1;
			dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].start_vrb_idx = n_dl_vrb_dash - t2 - 1;
		}

	}
	else {
		l_crbs = n_dl_vrb_dash - t1 + 1;
		dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].start_vrb_idx = n_dl_vrb_dash - t2 - 1;
	}


	l_crbs = l_crbs * LteData[cell_no].num_step_rb;

	dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].start_vrb_idx = dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].start_vrb_idx * LteData[cell_no].num_step_rb;

	dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].end_vrb_idx = dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].start_vrb_idx + l_crbs - 1;

	//Modulation and Coding Scheme


	//Modulation and Coding scheme
	bit_position = bit_position + LteData[cell_no].resource_block_assign_1c_bits;

	dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].mcs = 0;

	for(unsigned int kk = 0; kk < lte_num_bits_mcs_dci_1c; kk++) {
		dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].mcs += dci_1c_bits[bit_position + kk] << (lte_num_bits_mcs_dci_1c - 1 - kk);
	}

	dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].tbs_index = dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].mcs;
	dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].tbs_size = transport_block_size_table_1c[dci_format_info.pdcch_info_dci_format_1c[index_dci_1c].tbs_index];

	return LTE_SUCCESS;


}

/*
*********************************************************************************************************
* Function:lte_get_info_dci_format_1c
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_vrb_to_prb_mapping(lte_info_dci_format &dci_format_info, lte_measurements &LteData, unsigned int cell_no, unsigned char n_gap) {
	unsigned char row_len = 0, column_len = 0, n_dl_vrb_dash = 0, n_null, n_gap_value, col_idx_odd_slot = 0;
	unsigned char n_null_row_start, interleave_matrix[32][4], row_idx, col_idx, vrb_num = 0, prb_num = 0, null;

	column_len = lte_vrb_prb_mapping_interleaving_column_len;
	null = LTE_NULL;

	if(n_gap == lte_n_gap_1) {
		n_dl_vrb_dash = LteData[cell_no].num_dl_vrb_gap_1;
		n_gap_value = LteData[cell_no].n_gap_1;
	}
	else {
		n_dl_vrb_dash = 2 * LteData[cell_no].n_gap_2;
		n_gap_value = LteData[cell_no].n_gap_2;
	}


	row_len = ceil((float)n_dl_vrb_dash / (4 * (float)LteData[cell_no].rbg_size_p)) * LteData[cell_no].rbg_size_p;

	n_null = (row_len * column_len) - n_dl_vrb_dash;

	n_null_row_start = row_len - (n_null / 2);

	//Fill the interleaving matrix row wise
	for(row_idx = 0; row_idx < row_len; row_idx++) {
		for(col_idx = 0; col_idx < column_len; col_idx++) {
			if((col_idx == 1 || col_idx == 3) && (row_idx >= n_null_row_start)) {
				interleave_matrix[row_idx][col_idx] = LTE_NULL;
				vrb_num++;

			}
			else {
				interleave_matrix[row_idx][col_idx] = vrb_num++;
			}

		}// for - col_idx
	}//for- row_idx

	//Read the interleaving matrix column wise

	for(col_idx = 0; col_idx < column_len; col_idx++) {
		col_idx_odd_slot = (col_idx + 2) % column_len;

		for(row_idx = 0; row_idx < row_len; row_idx++) {
			if(interleave_matrix[row_idx][col_idx] != null) {
				dci_format_info.vrb_to_prb_mapping_even_slot[prb_num] = interleave_matrix[row_idx][col_idx];
				dci_format_info.vrb_to_prb_mapping_odd_slot[prb_num] = interleave_matrix[row_idx][col_idx_odd_slot];
				prb_num++;
			}
			else {
				for(unsigned char rr = 0; rr < (n_gap_value - (n_dl_vrb_dash / 2)); rr++) {
					dci_format_info.vrb_to_prb_mapping_even_slot[prb_num] = LTE_NULL;
					dci_format_info.vrb_to_prb_mapping_odd_slot[prb_num] = LTE_NULL;
					prb_num++;
				}
				row_idx = row_len;

			}//else

		}

	}// for - col_idx




	return LTE_SUCCESS;
}

}//namespace