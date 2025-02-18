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
#include <iostream>
#include <cstring>
#include <string>

#include <algorithm>
#include <map>

#include "lte_common.h"
#include "lte_analysis.h"
#include "lte_turbo_code_rate_match.h"
#include "lte_turbo_code.h"

#include "lte_pdcch.h"
#include "lte_pdsch.h"
#include "lte_crc_16.h"

#include <fstream>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <stdint.h>
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/lte_analysis/lte_io.h"

//#define OUTPUT_LTE_DEBUG

namespace rf_phreaker {

unsigned int lte_subframe_map[OFDM_SYMBOLS_PER_SUBFRAME][MAX_FFT_SIZE];
Ipp32fc lte_pdsch_fft[OFDM_SYMBOLS_PER_SUBFRAME][MAX_FFT_SIZE], lte_pdsch_fft_shifted[OFDM_SYMBOLS_PER_SUBFRAME][MAX_FFT_SIZE];
unsigned char lte_pdsch_byte_seq[512];
#define MAX_SUBCARRIER_MODULATION_SIZE MAX_SUBCARRIERS * MAX_MODULATION_ORDER * MAX_MODULATION_SIZE
//#define MAX_SUBCARRIER_MODULATION_SIZE 6144
std::vector<unsigned int> scrambling_seq_pdsch_buf(MAX_SUBCARRIER_MODULATION_SIZE);
std::vector<unsigned int> turbo_decoded_bits_buf(MAX_SUBCARRIER_MODULATION_SIZE);
ipp_32fc_array h_est_pdsch_buf(MAX_SUBCARRIER_MODULATION_SIZE);
ipp_32fc_array h_est_pdsch_temp_buf(NUM_ANTENNA_MAX * MAX_SUBCARRIER_MODULATION_SIZE);
ipp_32fc_array lte_pdsch_re_buf(MAX_SUBCARRIER_MODULATION_SIZE);
ipp_32f_array lte_pdsch_demod_llr_buf(MAX_SUBCARRIER_MODULATION_SIZE);
ipp_32f_array descrambled_pdcch_llr_buf(MAX_SUBCARRIER_MODULATION_SIZE);
ipp_32f_array deinterleaved_llr_buf(MAX_SUBCARRIER_MODULATION_SIZE);

unsigned int *scrambling_seq_pdsch = &scrambling_seq_pdsch_buf[0];
unsigned int *turbo_decoded_bits = &turbo_decoded_bits_buf[0];
Ipp32fc *h_est_pdsch = h_est_pdsch_buf.get();
Ipp32fc *h_est_pdsch_temp = h_est_pdsch_temp_buf.get();
Ipp32fc *lte_pdsch_re = lte_pdsch_re_buf.get();
Ipp32f *lte_pdsch_demod_llr = lte_pdsch_demod_llr_buf.get();
Ipp32f *descrambled_pdcch_llr = descrambled_pdcch_llr_buf.get();
Ipp32f *deinterleaved_llr = deinterleaved_llr_buf.get();



/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_pdsch_decode(Ipp32fc* inSignal,
	Ipp32fc* h_est,
	Ipp32f* h_noise_var,
	lte_measurements &LteData,
	unsigned int cell_no,
	unsigned int sub_frame_index,
	unsigned int subframe_start_sample_index,
	lte_info_dci_format &dci_format_info,
	unsigned int dci_type,
	unsigned int dci_index) {
	memset(lte_subframe_map, 0, OFDM_SYMBOLS_PER_SUBFRAME * MAX_FFT_SIZE * sizeof(unsigned int));
	memset(lte_pdsch_fft, 0, OFDM_SYMBOLS_PER_SUBFRAME * MAX_FFT_SIZE * sizeof(Ipp32fc));
	memset(lte_pdsch_fft_shifted, 0, OFDM_SYMBOLS_PER_SUBFRAME * MAX_FFT_SIZE * sizeof(Ipp32fc));
	memset(&lte_pdsch_byte_seq, 0, 512);
	memset(&scrambling_seq_pdsch_buf[0], 0, MAX_SUBCARRIER_MODULATION_SIZE * sizeof(unsigned int));
	memset(&turbo_decoded_bits_buf[0], 0, MAX_SUBCARRIER_MODULATION_SIZE * sizeof(unsigned int));
	ipp_32f_array noise_var(NUM_ANTENNA_MAX);
	h_est_pdsch_buf.zero_out();
	h_est_pdsch_temp_buf.zero_out();
	lte_pdsch_re_buf.zero_out();
	lte_pdsch_demod_llr_buf.zero_out();
	descrambled_pdcch_llr_buf.zero_out();
	deinterleaved_llr_buf.zero_out();
	auto turbo_decoded_bits_debug = turbo_decoded_bits;
	auto deinterleaved_llr_debug = deinterleaved_llr;
	auto descrambled_pdcch_llr_debug = descrambled_pdcch_llr;
	auto scrambling_seq_pdsch_debug = scrambling_seq_pdsch;
	auto lte_pdsch_demod_llr_debug = lte_pdsch_demod_llr;
	auto h_est_pdsch_debug = h_est_pdsch;
	auto lte_pdsch_re_debug = lte_pdsch_re;
	auto lte_pdsch_byte_seq_debug = lte_pdsch_byte_seq;

	unsigned int pdsch_re_count, start_rb_index, end_rb_index, transport_block_size, redundancy_version, k, i;
	LTEMODULATION modulation_type;
	unsigned char modulation_order;
	int c_init;
	unsigned int n_rnti = 0xFFFF, temp, lte_pdsch_crc;
	unsigned int q = 0; // For single port and transmit diversity only 1 codeword is allowed hence q = 0.
	// Removing hardcoded noise
	//h_noise_var[0] = h_noise_var[1] = 10000.0;//raj: 4th Oct 2014
	//h_noise_var[0] = h_noise_var[1] = 100.0;
	//h_noise_var[0] = h_noise_var[1] = 169800.0;
	//h_noise_var[0] = h_noise_var[1] = 2.2149e5;
	//lte_pdsch_get_subframe_map
	lte_pdsch_get_subframe_map(LteData, cell_no, sub_frame_index);

	if(dci_type == lte_dci_format_1a) {
		start_rb_index = dci_format_info.pdcch_info_dci_format_1a[dci_index].start_rb_idx;
		end_rb_index = dci_format_info.pdcch_info_dci_format_1a[dci_index].end_rb_idx;
		modulation_type = dci_format_info.pdcch_info_dci_format_1a[dci_index].lte_moduation_type;
		modulation_order = dci_format_info.pdcch_info_dci_format_1a[dci_index].modulation_order;
		if(modulation_order < 6)
			modulation_order = 6; // hardset to 6 (the highest mod order?)
		redundancy_version = dci_format_info.pdcch_info_dci_format_1a[dci_index].redundancy_version;
		transport_block_size = dci_format_info.pdcch_info_dci_format_1a[dci_index].tbs_size;
		int vrb_type = dci_format_info.pdcch_info_dci_format_1a[dci_index].vrb_type;
		int gap = dci_format_info.pdcch_info_dci_format_1a[dci_index].n_gap;
		if(vrb_type == LOCALISED_VRB) {
			lte_pdsch_get_symbols(inSignal,
				h_est,
				pdsch_re_count,
				LteData,
				cell_no,
				sub_frame_index,
				subframe_start_sample_index,
				start_rb_index, end_rb_index);
		}
		else if(vrb_type == DISTRIBUTED_VRB) {
			lte_pdsch_get_symbols_vrb(inSignal,
				h_est,
				pdsch_re_count,
				LteData,
				cell_no,
				sub_frame_index,
				subframe_start_sample_index,
				start_rb_index, end_rb_index,
				dci_format_info);
		}
	}
	else if(dci_type == lte_dci_format_1c) {
		start_rb_index = dci_format_info.pdcch_info_dci_format_1c[dci_index].start_vrb_idx;
		end_rb_index = dci_format_info.pdcch_info_dci_format_1c[dci_index].end_vrb_idx;
		modulation_type = MQPSK;
		modulation_order = 2;
		//modulation_order = 6; // hardset to 6 (the highest mod order?)
		int gap = dci_format_info.pdcch_info_dci_format_1c[dci_index].n_gap;

		transport_block_size = dci_format_info.pdcch_info_dci_format_1c[dci_index].tbs_size;

		//5.3.1  TS 36.321	
		if(LteData[cell_no].current_frame_number % 2 == 0 && sub_frame_index == 5) // for SIB1
		{
			k = (LteData[cell_no].current_frame_number / 2) % 4;
		}
		else {
			i = (LteData[cell_no].current_frame_number * NUM_SUBFRAMES_PER_FRAME + sub_frame_index) % (LteData[cell_no].si_window);
			k = i % 4;

		}
		redundancy_version = (unsigned int)(ceil((float)(3 / 2) * (float)k)) % 4; //ceil


		lte_pdsch_get_symbols_vrb(inSignal,
			h_est,
			pdsch_re_count,
			LteData,
			cell_no,
			sub_frame_index,
			subframe_start_sample_index,
			start_rb_index, end_rb_index,
			dci_format_info);

	}

	// The presumption is the we're only looking at one subframe here.
	// Change this when/if we change noise estimate.
	auto ant_i = 0;
	for(unsigned int jj = 0; jj<4; jj++) {
		if(jj == 2) continue;
		auto ant_start_idx = jj * NUM_SUBFRAMES_PER_FRAME;
		noise_var[ant_i++] = ant_start_idx + sub_frame_index;
	}


	/* MIMO Detection - Transmit Diversity */
	stDiversityDet(lte_pdsch_demod_llr,
		lte_pdsch_re, // PDSCH Modulation Symbols - Resource Elements
		h_est_pdsch,
		pdsch_re_count,
		LteData[cell_no].NumAntennaPorts, // Number of Antennas 
		modulation_type,//MQPSK,//Modulation Type == QPSK
		h_noise_var);


	//Soft desrambling 
	c_init = (n_rnti)*(1 << 14) + q*(1 << 13) + ((sub_frame_index) << 9) + LteData[cell_no].RsRecord.ID;

	generate_PN_seq(scrambling_seq_pdsch, //PDCCH Scambling Sequence
		c_init, //c_init
		pdsch_re_count*modulation_order);

	softDeSrambling(descrambled_pdcch_llr,  // Output Descrambled LLR Data
		lte_pdsch_demod_llr,    //Input LLR data
		pdsch_re_count*modulation_order,      //lenght of the sequence
		scrambling_seq_pdsch);   //Scrambling bits


	//Turbo coded subblock deinterleaver
	lte_turbocoded_sublock_interleaver(deinterleaved_llr, descrambled_pdcch_llr, pdsch_re_count*modulation_order,
		transport_block_size + LTE_PDSCH_CRC_LEN + LTE_PDSCH_TURBO_TAIL_BITS,
		redundancy_version);

	//Turbo decoder
	clock_t begin_turbo = clock();
	lte_turbo_code_decoder(deinterleaved_llr, turbo_decoded_bits, transport_block_size + LTE_PDSCH_CRC_LEN, LTE_TURBO_CODE_NUM_ITERATION);
	//lte_turbo_code_decoder(deinterleaved_llr, turbo_decoded_bits, transport_block_size + LTE_PDSCH_CRC_LEN, 5);
	clock_t end_turbo = clock();
	//std::cout << "Lte Turbo Decoder Time elapsed: " << lte_diffclock(end_turbo,begin_turbo) << " ms\n";
	//CRC Check
	//lte_debug_filewrite("CDeinterleaved_3MHZ.txt",deinterleaved_llr, 552);


	//lte_debug_filewrite("CTurboInput.txt",deinterleaved_llr, 612);
	//lte_debug_filewrite("CTurboOut.txt",turbo_decoded_bits, 200);
	//turbo_decoded_bits[11] = turbo_decoded_bits[26] = 0;
	bit2byte(lte_pdsch_byte_seq, turbo_decoded_bits, transport_block_size + LTE_PDSCH_CRC_LEN, 0);


	lte_crc_24(&lte_pdsch_crc, lte_pdsch_byte_seq, (transport_block_size + LTE_PDSCH_CRC_LEN) / 8);

#ifdef OUTPUT_LTE_DEBUG
	descrambled_pdcch_llr_buf.output_matlab_compatible_array("descrambled_pdcch_llr.txt");
	lte_pdsch_demod_llr_buf.output_matlab_compatible_array("pdsch_demod_llr.txt");
	lte_pdsch_re_buf.output_matlab_compatible_array("lte_pdsch_re.txt");
	h_est_pdsch_buf.output_matlab_compatible_array("h_est_pdsch.txt");
	descrambled_pdcch_llr_buf.output_matlab_compatible_array("descrambled_pdcch_llr.txt");
	deinterleaved_llr_buf.output_matlab_compatible_array("deinterleaved_llr.txt");
#endif

	if(lte_pdsch_crc == 0) {
		auto num_bit_stream_bytes = (transport_block_size + LTE_PDSCH_CRC_LEN) / 8;

		lte_asn1_decoder decoder;

		layer_3_information::lte_rrc_message_aggregate tmp;
		decoder.decode_bcch_bch_message(lte_pdsch_byte_seq, 512, 0, tmp);

		LteData[cell_no].layer_3_.update_info(tmp);

		return LTE_SUCCESS;
	}

	return -1;
}



/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_pdsch_get_subframe_map(lte_measurements &LteData,
	unsigned int cell_no,
	unsigned int sub_frame_index) {
	unsigned int v_shift, v_0, v_1, k_0, k_1, kk;

	auto debug_lte_subframe_map = lte_subframe_map;

	auto n_symb = LteData[cell_no].ofdm_symbols_per_slot();

	memset(lte_subframe_map, ZEROS, OFDM_SYMBOLS_PER_SUBFRAME * MAX_FFT_SIZE * sizeof(unsigned int));

	// Determine primary sync signal locations - refer to 136.211 6.11.1
	// Only handles FDD.  
	// Note - it looks like the reserve subcarriers are only for frame structure 2 but it appears in
	// matlab that they are reserved for frame structure 1 as well - so we do it.
	if(sub_frame_index == 0 || sub_frame_index == 5) {
		for(int nn = -5; nn <= 66; nn++) {
			kk = nn - 31 + (LteData[cell_no].numResouceBlocks * NUM_SUBCARRIER_PER_RESOURCE_BLOCK) / 2;
			if((nn < 0) || (nn>61)) {
				lte_subframe_map[n_symb - 1][kk] = lte_re_reserved; // last OFDM symbol in slots 0 and 10
			}
			else {
				lte_subframe_map[n_symb - 1][kk] = lte_re_sync_signal; // last OFDM symbol in slots 0 and 10
			}
		}
	}
	// Determine secondary sync signal locations - 136.211 6.11.2
	// Only handles FDD.  
	if(sub_frame_index == 0 || sub_frame_index == 5) {
		for(int nn = -5; nn <= 66; nn++) {
			kk = nn - 31 + (LteData[cell_no].numResouceBlocks * NUM_SUBCARRIER_PER_RESOURCE_BLOCK) / 2;
			if((nn < 0) || (nn>61)) {
				lte_subframe_map[n_symb - 2][kk] = lte_re_reserved;
			}
			else {
				lte_subframe_map[n_symb - 2][kk] = lte_re_sync_signal;
			}
		}
	}

	////Determine reference signal symbol locations - 6.10.1.2, TS36.211
	// Antenna port 0
	v_shift = LteData[cell_no].RsRecord.ID % 6;

	// Antenna port 0
	if((LteData[cell_no].NumAntennaPorts - 1) >= 0) {
		v_0 = 0;
		v_1 = 3;

		k_0 = (v_shift + v_0) % 6;
		k_1 = (v_shift + v_1) % 6;

		for(unsigned int mm = 0; mm < 2 * LteData[cell_no].numResouceBlocks; mm++) {
			// slot n0
			lte_subframe_map[0][6 * mm + k_0] = lte_re_reference_signal;
			lte_subframe_map[n_symb - 3][6 * mm + k_1] = lte_re_reference_signal;
			// slot n1
			lte_subframe_map[n_symb][6 * mm + k_0] = lte_re_reference_signal;
			lte_subframe_map[n_symb * 2 - 3][6 * mm + k_1] = lte_re_reference_signal;
		}
	}
	// Antenna port 1
	if((LteData[cell_no].NumAntennaPorts - 1) >= 1) {
		v_0 = 3;
		v_1 = 0;

		k_0 = (v_shift + v_0) % 6;
		k_1 = (v_shift + v_1) % 6;

		for(unsigned int mm = 0; mm < 2 * LteData[cell_no].numResouceBlocks; mm++) {
			// slot n0
			lte_subframe_map[0][6 * mm + k_0] = lte_re_reference_signal;
			lte_subframe_map[n_symb - 3][6 * mm + k_1] = lte_re_reference_signal;
			// slot n1
			lte_subframe_map[n_symb][6 * mm + k_0] = lte_re_reference_signal;
			lte_subframe_map[n_symb * 2 - 3][6 * mm + k_1] = lte_re_reference_signal;
		}

	}

	// Antenna port 2
	if((LteData[cell_no].NumAntennaPorts - 1) >= 2) {

		v_0 = 3 * ((2 * sub_frame_index) % 2); // slot n0 
		v_1 = 3 * ((2 * sub_frame_index + 1) % 2); // slot n1 
		k_0 = (v_shift + v_0) % 6;
		k_1 = (v_shift + v_1) % 6;
		for(unsigned int mm = 0; mm < 2 * LteData[cell_no].numResouceBlocks; mm++) {
			lte_subframe_map[1][6 * mm + k_0] = lte_re_reference_signal;
			lte_subframe_map[n_symb + 1][6 * mm + k_1] = lte_re_reference_signal;
		}

	}

	// Antenna port 3
	if((LteData[cell_no].NumAntennaPorts - 1) >= 3) {

		v_0 = 3 + 3 * ((2 * sub_frame_index) % 2); // slot 0 of subframe
		v_1 = 3 + 3 * ((2 * sub_frame_index + 1) % 2); // slot 1 of subframe
		k_0 = (v_shift + v_0) % 6;
		k_1 = (v_shift + v_1) % 6;
		for(unsigned int mm = 0; mm < 2 * LteData[cell_no].numResouceBlocks; mm++) {
			lte_subframe_map[1][6 * mm + k_0] = lte_re_reference_signal;
			lte_subframe_map[n_symb + 1][6 * mm + k_1] = lte_re_reference_signal;
		}
	}

	//Determine PBCH symbol locations
	if(sub_frame_index == 0) {
		k_0 = (LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK) / 2 - 36; //6.6.4, TS36.211
		for(unsigned int kk = 0; kk <= 71; kk++) {
			lte_subframe_map[n_symb][k_0 + kk] = lte_subframe_map[n_symb + 1][k_0 + kk] = lte_re_pbch;
			lte_subframe_map[n_symb + 2][k_0 + kk] = lte_subframe_map[n_symb + 3][k_0 + kk] = lte_re_pbch;
		}
	}

#ifdef OUTPUT_LTE_DEBUG
	std::ofstream lte_map("lte_map.txt");
	lte_map << "matlab_idx\tsym_0\tsym_1\tsym_2\tsym_3\tsym_4\tsym_5\tsym_6\tsym_7\tsym_8\tsym_9\tsym_10\tsym_11\tsym_12\tsym_13\n";
	for(auto j = 0; j < MAX_FFT_SIZE; ++j) {
		lte_map << (j + 1) << "\t";
		for(auto i = 0; i < OFDM_SYMBOLS_PER_SUBFRAME; ++i) {
			lte_map << lte_subframe_map[i][j] << "\t";
		}
		lte_map << "\n";
	}
#endif
	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_pdsch_get_symbols(Ipp32fc* inSignal,
	Ipp32fc* h_est,
	unsigned int &pdsch_re_count,
	lte_measurements &LteData,
	unsigned int cell_no,
	unsigned int sub_frame_index,
	unsigned int subframe_start_sample_index,
	unsigned int start_rb,
	unsigned int end_rb) {
	// Changed the size of fft_index to match that of h_est_pdsch_temp
	const int fft_index_size = MAX_SUBCARRIERS * OFDM_SYMBOLS_PER_SUBFRAME;
	const int max_num_symbols = 6144;
	unsigned int fft_index[fft_index_size], temp;

	for(unsigned int symbol_idx = LteData[cell_no].lteControlSysmbolLenght; symbol_idx < OFDM_SYMBOLS_PER_SUBFRAME; symbol_idx++) {
		if(symbol_idx < OFDM_SYMBOLS_PER_SLOT) {
			myfft(&lte_pdsch_fft[symbol_idx][0], //Frequency Domain Output
				inSignal + subframe_start_sample_index
				+ LteData[cell_no].cPSamplesSymbol0
				+ symbol_idx * LteData[cell_no].fftSize
				+ symbol_idx * LteData[cell_no].cPSamplesSymbol1to6, //Time Domain Input
				LteData[cell_no].fftSize); //FFT Size
		}
		else {
			myfft(&lte_pdsch_fft[symbol_idx][0], //Frequency Domain Output
				inSignal + subframe_start_sample_index
				+ 2 * LteData[cell_no].cPSamplesSymbol0
				+ symbol_idx * LteData[cell_no].fftSize
				+ (symbol_idx - 1) * LteData[cell_no].cPSamplesSymbol1to6, //Time Domain Input
				LteData[cell_no].fftSize); //FFT Size

		}

		myfftshift(&lte_pdsch_fft_shifted[symbol_idx][0], //Destination
			&lte_pdsch_fft[symbol_idx][0], //Source
			LteData[cell_no].fftSize); //FFT Size  
	}


#ifdef OUTPUT_LTE_DEBUG
	// Debug output to compare against matlab.
	static std::ofstream vrb_debug("local_vrb_debug.txt");
#endif

	pdsch_re_count = 0; // Should this be moved into the loop?
	for(unsigned int symbol_idx = LteData[cell_no].lteControlSysmbolLenght; symbol_idx < OFDM_SYMBOLS_PER_SUBFRAME; symbol_idx++) {
		for(unsigned int kk = (start_rb*NUM_SUBCARRIER_PER_RESOURCE_BLOCK); kk<(end_rb + 1)*NUM_SUBCARRIER_PER_RESOURCE_BLOCK; kk++) {
			if(lte_subframe_map[symbol_idx][kk] == lte_re_unused) {
				if(kk>(LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK / 2))
					//if((start_rb*NUM_SUBCARRIER_PER_RESOURCE_BLOCK)>(LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK/2))
					fft_index[pdsch_re_count] = kk + LteData[cell_no].fft_subcarrier_start_index + 1;
				else
					fft_index[pdsch_re_count] = kk + LteData[cell_no].fft_subcarrier_start_index;


				lte_pdsch_re[pdsch_re_count] = lte_pdsch_fft_shifted[symbol_idx][fft_index[pdsch_re_count]];
				for(unsigned int antNum = 0; antNum < LteData[cell_no].NumAntennaPorts; antNum++) {
					h_est_pdsch_temp[antNum * MAX_SUBCARRIER_MODULATION_SIZE + pdsch_re_count] = h_est[antNum * LteData[cell_no].fftSize * OFDM_SYMBOLS_PER_FRAME
						+ sub_frame_index * OFDM_SYMBOLS_PER_SUBFRAME *LteData[cell_no].fftSize
						+ symbol_idx * LteData[cell_no].fftSize
						+ fft_index[pdsch_re_count]];
				}

#ifdef OUTPUT_LTE_DEBUG
				vrb_debug << symbol_idx * LteData[cell_no].numResouceBlocks * NUM_SUBCARRIER_PER_RESOURCE_BLOCK + kk + 1 << std::endl;
#endif
				pdsch_re_count++;
				// Temporary bug fix: pdsch_re_count can overstep the fft_index.  Is pdsch_re_count supposed to be reset to 0 in the outer loop?
				if(pdsch_re_count >= max_num_symbols)
					break;
			}
			else 
				int i = 0; // Compiled out in release mode - only used for debugging.
		}
		// Temporary bug fix: pdsch_re_count can overstep the fft_index.  Is pdsch_re_count supposed to be reset to 0 in the outer loop?
		if(pdsch_re_count >= max_num_symbols)
			break;
	}

	h_est_pdsch_buf.zero_out();

	for(unsigned int antNum = 0; antNum < LteData[cell_no].NumAntennaPorts; antNum++) {
		for(unsigned int kk = 0; kk < pdsch_re_count; kk++) {
			h_est_pdsch[antNum*pdsch_re_count + kk] = h_est_pdsch_temp[antNum * MAX_SUBCARRIER_MODULATION_SIZE + kk];
		}
	}

#ifdef OUTPUT_LTE_DEBUG
	// Debug output to compare against matlab.
	vrb_debug << "\n\n" << std::endl;
#endif

	return LTE_SUCCESS;
}

int lte_pdsch_get_symbols_vrb(Ipp32fc* inSignal,
	Ipp32fc* h_est,
	unsigned int &pdsch_re_count,
	lte_measurements &LteData,
	unsigned int cell_no,
	unsigned int sub_frame_index,
	unsigned int subframe_start_sample_index,
	unsigned int start_rb_vrb,
	unsigned int end_rb_vrb,
	lte_info_dci_format &dci_format_info) {
	// Changed the size of fft_index to match that of h_est_pdsch_temp
	const int fft_index_size = MAX_SUBCARRIERS * OFDM_SYMBOLS_PER_SUBFRAME;
	unsigned int fft_index[fft_index_size], temp, vrb_idx, start_rb, end_rb, odd_rb = LTE_NULL, even_rb = LTE_NULL;
	const int max_vrb_prb_slot_num = 128;
	unsigned int vrb_prb_slot_map[max_vrb_prb_slot_num][2];
	const int max_num_symbols = 6144;
	
	pdsch_re_count = 0;

	const auto debug_lte_pdsch_fft = lte_pdsch_fft;
	const auto debug_lte_pdsch_fft_shifted = lte_pdsch_fft_shifted;
	const auto debug_dci_format_info = dci_format_info;
	memset(vrb_prb_slot_map, 0, 128 * 2 * sizeof(unsigned int));
	memset(lte_pdsch_fft_shifted, 0, OFDM_SYMBOLS_PER_SUBFRAME * MAX_FFT_SIZE * sizeof(Ipp32fc));

	for(unsigned int symbol_idx = LteData[cell_no].lteControlSysmbolLenght; symbol_idx < OFDM_SYMBOLS_PER_SUBFRAME; symbol_idx++) {
		if(symbol_idx < OFDM_SYMBOLS_PER_SLOT) {
			myfft(&lte_pdsch_fft[symbol_idx][0], //Frequency Domain Output
				inSignal + subframe_start_sample_index
				+ LteData[cell_no].cPSamplesSymbol0
				+ symbol_idx * LteData[cell_no].fftSize
				+ symbol_idx * LteData[cell_no].cPSamplesSymbol1to6, //Time Domain Input
				LteData[cell_no].fftSize); //FFT Size
		}
		else {
			myfft(&lte_pdsch_fft[symbol_idx][0], //Frequency Domain Output
				inSignal + subframe_start_sample_index
				+ 2 * LteData[cell_no].cPSamplesSymbol0
				+ symbol_idx * LteData[cell_no].fftSize
				+ (symbol_idx - 1) * LteData[cell_no].cPSamplesSymbol1to6, //Time Domain Input
				LteData[cell_no].fftSize); //FFT Size

		}

		myfftshift(&lte_pdsch_fft_shifted[symbol_idx][0], //Destination
			&lte_pdsch_fft[symbol_idx][0], //Source
			LteData[cell_no].fftSize); //FFT Size  
	}

#if 0

	for (vrb_idx = start_rb_vrb; vrb_idx <= (end_rb_vrb - start_rb_vrb + 1 )/2; vrb_idx++)
	{
		//if ((vrb_idx % 2) == 0) 
		{

			for (unsigned char zz = 0; zz < LteData[cell_no].numResouceBlocks; zz++) // even slot
			{
				if (dci_format_info.vrb_to_prb_mapping_even_slot[zz] == vrb_idx)
				{
					vrb_prb_slot_map[2 * vrb_idx][0] = zz;
				}

			}

			for (unsigned char zz = 0; zz < LteData[cell_no].numResouceBlocks; zz++) // odd slot
			{
				if (dci_format_info.vrb_to_prb_mapping_odd_slot[zz] == vrb_idx)
				{
					vrb_prb_slot_map[2 * vrb_idx][1] = zz;
				}

			}

		{
			temp = vrb_prb_slot_map[2 * vrb_idx][0];
			vrb_prb_slot_map[2 * vrb_idx + 1][0] = vrb_prb_slot_map[2 * vrb_idx][1];
			vrb_prb_slot_map[2 * vrb_idx + 1][1] = temp;

		}
		}		

	}
#endif

	if(end_rb_vrb >= max_vrb_prb_slot_num)
		return -1;
#if 1
	for(vrb_idx = start_rb_vrb; vrb_idx <= end_rb_vrb; vrb_idx++) {

		for(unsigned char zz = 0; zz < LteData[cell_no].numResouceBlocks; zz++) // even slot
		{
			if(dci_format_info.vrb_to_prb_mapping_even_slot[zz] == vrb_idx) {
				vrb_prb_slot_map[vrb_idx][0] = zz;
			}

		}

		for(unsigned char zz = 0; zz < LteData[cell_no].numResouceBlocks; zz++) // odd slot
		{
			if(dci_format_info.vrb_to_prb_mapping_odd_slot[zz] == vrb_idx) {
				vrb_prb_slot_map[vrb_idx][1] = zz;
			}

		}
	}
#endif

#ifdef OUTPUT_LTE_DEBUG
	// Debug output to compare against matlab.
	static std::ofstream vrb_debug("dis_vrb_debug.txt");
#endif

	//for (vrb_idx = start_rb_vrb; vrb_idx <= end_rb_vrb; vrb_idx++)
	{
		auto lowest_odd = UINT_MAX;
		auto lowest_odd_idx = 0;
		auto lowest_even = UINT_MAX;
		auto lowest_even_idx = 0;
		for(vrb_idx = start_rb_vrb; vrb_idx <= end_rb_vrb; vrb_idx++) {
			if(vrb_prb_slot_map[vrb_idx][1] < lowest_odd) {
				lowest_odd = vrb_prb_slot_map[vrb_idx][1];
				lowest_odd_idx = vrb_idx;
			}
			if(vrb_prb_slot_map[vrb_idx][0] < lowest_even) {
				lowest_even = vrb_prb_slot_map[vrb_idx][0];
				lowest_even_idx = vrb_idx;
			}
		}
		int odd_start_idx = lowest_odd_idx;
		int even_start_idx = lowest_even_idx;

		auto &lte_subframe_map_debug = lte_subframe_map;
		for(unsigned int symbol_idx = LteData[cell_no].lteControlSysmbolLenght; symbol_idx < OFDM_SYMBOLS_PER_SUBFRAME; symbol_idx++) {
			for(vrb_idx = start_rb_vrb; vrb_idx <= end_rb_vrb; vrb_idx++) {


#if 1
				if(symbol_idx < OFDM_SYMBOLS_PER_SLOT) { // even slot	
					auto tmp_idx = (even_start_idx + vrb_idx) % (end_rb_vrb - start_rb_vrb + 1) + start_rb_vrb;
					if(tmp_idx >= max_vrb_prb_slot_num)
						return -1;
					start_rb = end_rb = vrb_prb_slot_map[tmp_idx][0];
				}
				else { // odd slot 
					auto tmp_idx = (odd_start_idx + vrb_idx) % (end_rb_vrb - start_rb_vrb + 1) + start_rb_vrb;
					if(tmp_idx >= max_vrb_prb_slot_num)
						return -1;
					start_rb = end_rb = vrb_prb_slot_map[tmp_idx][1];
				}
#endif

				for(unsigned int kk = (start_rb * NUM_SUBCARRIER_PER_RESOURCE_BLOCK); kk < (end_rb + 1)*NUM_SUBCARRIER_PER_RESOURCE_BLOCK; kk++) {
					if(lte_subframe_map[symbol_idx][kk] == lte_re_unused) {
						if(kk>(LteData[cell_no].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK / 2))
							fft_index[pdsch_re_count] = kk + LteData[cell_no].fft_subcarrier_start_index + 1;

						//fft_index[pdsch_re_count] = 1200 + kk + 1 + 1;
						else
							fft_index[pdsch_re_count] = kk + LteData[cell_no].fft_subcarrier_start_index;
						//fft_index[pdsch_re_count] = 1200 + kk + 1;

						lte_pdsch_re[pdsch_re_count] = lte_pdsch_fft_shifted[symbol_idx][fft_index[pdsch_re_count]];
						for(unsigned int antNum = 0; antNum < LteData[cell_no].NumAntennaPorts; antNum++) {
							h_est_pdsch_temp[antNum * MAX_SUBCARRIER_MODULATION_SIZE + pdsch_re_count] = h_est[antNum * LteData[cell_no].fftSize * OFDM_SYMBOLS_PER_FRAME
								+ sub_frame_index * OFDM_SYMBOLS_PER_SUBFRAME *LteData[cell_no].fftSize
								+ symbol_idx * LteData[cell_no].fftSize
								+ fft_index[pdsch_re_count]];
						}

#ifdef OUTPUT_LTE_DEBUG
						vrb_debug << symbol_idx * LteData[cell_no].numResouceBlocks * NUM_SUBCARRIER_PER_RESOURCE_BLOCK + kk + 1 << std::endl;
#endif
						pdsch_re_count++;

						// Temporary bug fix: pdsch_re_count can overstep the fft_index.  Is pdsch_re_count supposed to be reset to 0 in the outer loop?
						if(pdsch_re_count >= max_num_symbols)
							break;
					}
					else
						int i = 0; // Compiled out in release mode - only used for debugging.
				}//kk
			}//vrb_idx_in

			// Temporary bug fix: pdsch_re_count can overstep the fft_index.  Is pdsch_re_count supposed to be reset to 0 in the outer loop?
			if(pdsch_re_count >= max_num_symbols)
				break;
			//}
		} // symbol_idx
	}//vrb_idx

	h_est_pdsch_buf.zero_out();

	for(unsigned int antNum = 0; antNum < LteData[cell_no].NumAntennaPorts; antNum++) {
		for(unsigned int kk = 0; kk < pdsch_re_count; kk++) {
			h_est_pdsch[antNum*pdsch_re_count + kk] = h_est_pdsch_temp[antNum * MAX_SUBCARRIER_MODULATION_SIZE + kk];
		}
	}

#ifdef OUTPUT_LTE_DEBUG
	// Debug output to compare against matlab.
	vrb_debug << "\n\n" << std::endl;
#endif

	return LTE_SUCCESS;



}

}//namespace