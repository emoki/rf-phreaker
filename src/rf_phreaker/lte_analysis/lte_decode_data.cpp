#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include <stdio.h>

#include "rf_phreaker/common/ipp_array.h"

#include "lte_analysis.h"
#include "lte_synchronization.h"

#include "lte_channel_estimation.h"
#include "lte_pbch.h" 
#include "lte_pcfich.h"
#include "lte_pdcch.h"
#include "lte_pdsch.h"
#include "lte_turbo_code_rate_match.h"
#include "lte_turbo_code.h"
#include "rf_phreaker/lte_analysis/lte_si_tracker.h"
#include <iostream>

namespace rf_phreaker {

/* Static Allocation of  memory for Channel Estimates per frame for all the antennas */
Ipp32fc h_est[OFDM_SYMBOLS_PER_FRAME * NUM_FRAMES * MAX_FFT_SIZE * NUM_ANTENNA_MAX];

// TODO - signal_max_size should be dynamic.
static int signal_max_size = 655345;

static double SampleRate192 = 1.92e6;

int framecount = 0;

int lte_decode_data(const Ipp32fc* SignalSamples,
	unsigned int NumSamples,
	unsigned int NumHalfFramesToProcess,
	lte_measurements &LteData,
	int meas_to_process,
	lte_si_info_group *si_scheduling_hints,
	std::atomic_bool *is_cancelled = nullptr) {
	//unsigned int current_frame_number = 0;

	// TODO - Declaring the signal statically is OK for now because the processing functions are protected by a mutex 
	// so only one thread will enter this function at a time.  However once multhreading is implmented we should switch it to 
	// a member variable.
	static ipp_32fc_array signal_384;
	if(signal_384.length() < (int)NumSamples)
		signal_384.reset(NumSamples + FRAMENUMSAMPLES_FFT1024 * 2);

	ippsCopy_32fc(SignalSamples, signal_384.get(), NumSamples);

	unsigned int num_filter_output = 0;
	unsigned int frameStartSampleIndex, subframeStartSampleIndex;
	unsigned int ratio_dl_vrb_step_rb;
	Ipp32f hNoiseVariance[256];

	double SampleRate;

	//for(unsigned int ii = 0; ii <LteData.size(); ii++)
	if(meas_to_process < 0)
		return -1;

	int ii = meas_to_process;

	switch(LteData[ii].Bandwidth) {
	case LteBandwidth_1_4MHZ:
		LteData[ii].fftSize = FFTSIZE_128;
		LteData[ii].frameNumSamples = FRAMENUMSAMPLES_FFT512;
		break;

	case LteBandwidth_3MHZ:
		SampleRate = 3.84e6;
		LteData[ii].fftSize = FFTSIZE_256;
		LteData[ii].frameNumSamples = FRAMENUMSAMPLES_FFT256;
		LteData[ii].cPSamplesSymbol0 = CP_SAMPLES_FFT256_SYMBOL_0;
		LteData[ii].cPSamplesSymbol1to6 = CP_SAMPLES_FFT256_SYMBOL_1TO6;
		LteData[ii].numResouceBlocks = NUMRESOURCEBLOCKS_FFT256;
		LteData[ii].fft_subcarrier_start_index = ((LteData[ii].fftSize)
			- (LteData[ii].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK)) / 2;
		LteData[ii].num_bits_dci_1A = NUM_BITS_DCI_1A_3MHZ;

		LteData[ii].n_gap_1 = lte_n_gap_1_3mhz;
		LteData[ii].n_gap_2 = LTE_NULL;
		LteData[ii].num_dl_vrb_gap_1 = 2 * std::min(LteData[ii].n_gap_1, (LteData[ii].numResouceBlocks - LteData[ii].n_gap_1));
		LteData[ii].num_dl_vrb_gap_2 = (LteData[ii].numResouceBlocks / (2 * LteData[ii].n_gap_2)) * 2 * LteData[ii].n_gap_2;
		LteData[ii].num_step_rb = lte_n_step_rb_3mhz;

		ratio_dl_vrb_step_rb = LteData[ii].num_dl_vrb_gap_1 / LteData[ii].num_step_rb;

		LteData[ii].resource_block_assign_1c_bits = (unsigned int)ceil(log((float)ratio_dl_vrb_step_rb * (float)(ratio_dl_vrb_step_rb + 1) / 2)*LOG2_BASE_E);

		LteData[ii].num_bits_dci_1C = lte_num_bits_gap_value_dci_1c_3mhz
			+ LteData[ii].resource_block_assign_1c_bits
			+ lte_num_bits_mcs_dci_1c;
		LteData[ii].rbg_size_p = lte_rbg_size_p_3mhz;

		break;

	case LteBandwidth_5MHZ:
		SampleRate = 7.68e6;
		LteData[ii].fftSize = FFTSIZE_512;
		LteData[ii].frameNumSamples = FRAMENUMSAMPLES_FFT512;
		LteData[ii].cPSamplesSymbol0 = CP_SAMPLES_FFT512_SYMBOL_0;
		LteData[ii].cPSamplesSymbol1to6 = CP_SAMPLES_FFT512_SYMBOL_1TO6;
		LteData[ii].numResouceBlocks = NUMRESOURCEBLOCKS_FFT512;
		LteData[ii].fft_subcarrier_start_index = ((LteData[ii].fftSize)
			- (LteData[ii].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK)) / 2;
		LteData[ii].num_bits_dci_1A = NUM_BITS_DCI_1A_5MHZ;

		LteData[ii].n_gap_1 = lte_n_gap_1_5mhz;
		LteData[ii].n_gap_2 = LTE_NULL;
		LteData[ii].num_dl_vrb_gap_1 = 2 * std::min(LteData[ii].n_gap_1, (LteData[ii].numResouceBlocks - LteData[ii].n_gap_1));
		LteData[ii].num_dl_vrb_gap_2 = (LteData[ii].numResouceBlocks / (2 * LteData[ii].n_gap_2)) * 2 * LteData[ii].n_gap_2;
		LteData[ii].num_step_rb = lte_n_step_rb_5mhz;

		ratio_dl_vrb_step_rb = LteData[ii].num_dl_vrb_gap_1 / LteData[ii].num_step_rb;

		LteData[ii].resource_block_assign_1c_bits = (unsigned int)ceil(log((float)ratio_dl_vrb_step_rb * (float)(ratio_dl_vrb_step_rb + 1) / 2)*LOG2_BASE_E);

		LteData[ii].num_bits_dci_1C = lte_num_bits_gap_value_dci_1c_5mhz
			+ LteData[ii].resource_block_assign_1c_bits
			+ lte_num_bits_mcs_dci_1c;
		LteData[ii].rbg_size_p = lte_rbg_size_p_5mhz;
		break;

	case LteBandwidth_10MHZ:
		SampleRate = 15.36e6;
		LteData[ii].fftSize = FFTSIZE_1024;
		LteData[ii].frameNumSamples = FRAMENUMSAMPLES_FFT1024;
		LteData[ii].cPSamplesSymbol0 = CP_SAMPLES_FFT1024_SYMBOL_0;
		LteData[ii].cPSamplesSymbol1to6 = CP_SAMPLES_FFT1024_SYMBOL_1TO6;
		LteData[ii].numResouceBlocks = NUMRESOURCEBLOCKS_FFT1024;
		LteData[ii].fft_subcarrier_start_index = ((LteData[ii].fftSize)
			- (LteData[ii].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK)) / 2;
		LteData[ii].num_bits_dci_1A = NUM_BITS_DCI_1A_10MHZ;

		LteData[ii].n_gap_1 = lte_n_gap_1_10mhz;
		LteData[ii].n_gap_2 = lte_n_gap_2_10mhz;
		LteData[ii].num_dl_vrb_gap_1 = 2 * std::min(LteData[ii].n_gap_1, (LteData[ii].numResouceBlocks - LteData[ii].n_gap_1));
		LteData[ii].num_dl_vrb_gap_2 = (LteData[ii].numResouceBlocks / (2 * LteData[ii].n_gap_2)) * 2 * LteData[ii].n_gap_2;
		LteData[ii].num_step_rb = lte_n_step_rb_10mhz;

		ratio_dl_vrb_step_rb = LteData[ii].num_dl_vrb_gap_1 / LteData[ii].num_step_rb;

		LteData[ii].resource_block_assign_1c_bits = (unsigned int)ceil(log((float)ratio_dl_vrb_step_rb * (float)(ratio_dl_vrb_step_rb + 1) / 2)*LOG2_BASE_E);

		LteData[ii].num_bits_dci_1C = lte_num_bits_gap_value_dci_1c_10mhz
			+ LteData[ii].resource_block_assign_1c_bits
			+ lte_num_bits_mcs_dci_1c;
		LteData[ii].rbg_size_p = lte_rbg_size_p_10mhz;



		break;

	case LteBandwidth_15MHZ:
		SampleRate = 23.04e6;
		LteData[ii].fftSize = FFTSIZE_1536;
		LteData[ii].frameNumSamples = FRAMENUMSAMPLES_FFT1536;
		LteData[ii].cPSamplesSymbol0 = CP_SAMPLES_FFT1536_SYMBOL_0;
		LteData[ii].cPSamplesSymbol1to6 = CP_SAMPLES_FFT1536_SYMBOL_1TO6;
		LteData[ii].numResouceBlocks = NUMRESOURCEBLOCKS_FFT1536;
		LteData[ii].fft_subcarrier_start_index = ((LteData[ii].fftSize)
			- (LteData[ii].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK)) / 2;
		LteData[ii].num_bits_dci_1A = NUM_BITS_DCI_1A_15MHZ;

		LteData[ii].n_gap_1 = lte_n_gap_1_15mhz;
		LteData[ii].n_gap_2 = lte_n_gap_2_15mhz;
		LteData[ii].num_dl_vrb_gap_1 = 2 * std::min(LteData[ii].n_gap_1, (LteData[ii].numResouceBlocks - LteData[ii].n_gap_1));
		LteData[ii].num_dl_vrb_gap_2 = (LteData[ii].numResouceBlocks / (2 * LteData[ii].n_gap_2)) * 2 * LteData[ii].n_gap_2;
		LteData[ii].num_step_rb = lte_n_step_rb_15mhz;

		ratio_dl_vrb_step_rb = LteData[ii].num_dl_vrb_gap_1 / LteData[ii].num_step_rb;

		LteData[ii].resource_block_assign_1c_bits = (unsigned int)ceil(log((float)ratio_dl_vrb_step_rb * (float)(ratio_dl_vrb_step_rb + 1) / 2)*LOG2_BASE_E);

		LteData[ii].num_bits_dci_1C = lte_num_bits_gap_value_dci_1c_15mhz
			+ LteData[ii].resource_block_assign_1c_bits
			+ lte_num_bits_mcs_dci_1c;
		LteData[ii].rbg_size_p = lte_rbg_size_p_15mhz;
		break;

	case LteBandwidth_20MHZ:
		SampleRate = 30.72e6;
		LteData[ii].fftSize = FFTSIZE_2048;
		LteData[ii].frameNumSamples = FRAMENUMSAMPLES_FFT2048;
		LteData[ii].cPSamplesSymbol0 = CP_SAMPLES_FFT2048_SYMBOL_0;
		LteData[ii].cPSamplesSymbol1to6 = CP_SAMPLES_FFT2048_SYMBOL_1TO6;
		LteData[ii].numResouceBlocks = NUMRESOURCEBLOCKS_FFT2048;
		LteData[ii].fft_subcarrier_start_index = ((LteData[ii].fftSize)
			- (LteData[ii].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK)) / 2;
		LteData[ii].num_bits_dci_1A = NUM_BITS_DCI_1A_20MHZ;

		LteData[ii].n_gap_1 = lte_n_gap_1_20mhz;
		LteData[ii].n_gap_2 = lte_n_gap_2_20mhz;
		LteData[ii].num_dl_vrb_gap_1 = 2 * std::min(LteData[ii].n_gap_1, (LteData[ii].numResouceBlocks - LteData[ii].n_gap_1));
		LteData[ii].num_dl_vrb_gap_2 = (LteData[ii].numResouceBlocks / (2 * LteData[ii].n_gap_2)) * 2 * LteData[ii].n_gap_2;
		LteData[ii].num_step_rb = lte_n_step_rb_20mhz;

		ratio_dl_vrb_step_rb = LteData[ii].num_dl_vrb_gap_1 / LteData[ii].num_step_rb;

		LteData[ii].resource_block_assign_1c_bits = (unsigned int)ceil(log((float)ratio_dl_vrb_step_rb * (float)(ratio_dl_vrb_step_rb + 1) / 2)*LOG2_BASE_E);

		LteData[ii].num_bits_dci_1C = lte_num_bits_gap_value_dci_1c_20mhz
			+ LteData[ii].resource_block_assign_1c_bits
			+ lte_num_bits_mcs_dci_1c;
		LteData[ii].rbg_size_p = lte_rbg_size_p_20mhz;
		break;

	default:
		LteData[ii].fftSize = FFTSIZE_UNKNOWN;
		LteData[ii].frameNumSamples = FRAMENUMSAMPLES_FFT512;
		break;

	}

	// Nothing to decode.
	if(LteData[ii].fftSize == FFTSIZE_UNKNOWN || LteData[ii].fftSize == FFTSIZE_128) {
		return -1;
	}


	//DisplayLTEData(LteData);

	LteData[ii].si_window = si_scheduling_hints ? si_scheduling_hints->si_window_length_ms() : LTE_NULL;
	LteData[ii].dci_format = si_scheduling_hints ? si_scheduling_hints->dci_format_ : lte_dci_format_unknown;

	frameStartSampleIndex = LteData[ii].RsRecord.StartSampleNum;

	LteData[ii].current_frame_number = LteData[ii].frame_number;

	// For debug purposes.
	int current_frame_number = LteData[ii].frame_number;
	auto &current_physical_cell_id = LteData[ii].RsRecord.ID;
	auto &current_layer_3 = LteData[ii].layer_3_;
	
	auto &meas = LteData[ii];
	bool looking_for_si = false;
	bool looking_for_sib1 = true;
	int starting_frame = 0;
	int starting_subframe = 0;
	lte_si_info_group internal_scheduling_hints;

	while((frameStartSampleIndex + LteData[ii].frameNumSamples) < (NumHalfFramesToProcess / 2 * LteData[ii].frameNumSamples)) {
		lte_si_info *relevant_si_info = nullptr;
		if(si_scheduling_hints) {
			looking_for_sib1 = false;
			for(auto &info : si_scheduling_hints->g_) {
				if(!info.decoded_ && info.is_relevant_frame(current_frame_number)) {
					relevant_si_info = &info;
					starting_subframe = info.starting_subframe();
					//si_window_in_subframe = si_scheduling_hints->si_window_length_ms();
					//looking_for_si = true;
					//starting_frame = current_frame_number;
					break;
				}
			}
		}
		else
			looking_for_sib1 = true;

		if(is_cancelled && is_cancelled)
			break;

		if((looking_for_sib1 && current_frame_number % 2 == 0) || (relevant_si_info && !relevant_si_info->decoded_)) {

			memset(h_est, 0, OFDM_SYMBOLS_PER_FRAME * NUM_FRAMES * MAX_FFT_SIZE * NUM_ANTENNA_MAX * 8);
			/* Channel Estimation per Frame per Antenna */
			for(int antNum = 0; antNum < LteData[ii].NumAntennaPorts; antNum++) {
				LteChannelEst(h_est + antNum * OFDM_SYMBOLS_PER_FRAME * NUM_FRAMES * LteData[ii].fftSize,
					hNoiseVariance + antNum*NUM_SUBFRAMES_PER_FRAME,
					signal_384.get(),//signal768,
					frameStartSampleIndex,
					LteData[ii].RsRecord.ID,
					LteData[ii].CyclicPrefix,
					antNum,
					NUM_FRAMES,
					LteData[ii].Bandwidth
					);
				//std::cout << "LteChannelEst Time elapsed: " << lte_diffclock(end,begin) << " ms\n";
				//exit(0);
			}



			/* Process Subframes*/
			for(unsigned int subFrameIndex = starting_frame == current_frame_number ? starting_subframe : 0; subFrameIndex < NUM_SUBFRAMES_PER_FRAME; ++subFrameIndex) {
				
				// Skip all other frames until we have decoded sib1
				if(looking_for_sib1 && subFrameIndex != 5 && current_frame_number % 2 == 0)
					continue;
				// Skip frame once we've decoded the relevant SI.
				else if(relevant_si_info && relevant_si_info->decoded_)
					break;
				// Skip SIB1 decoding if we have scheduling info.
				else if(si_scheduling_hints && subFrameIndex == 5 && current_frame_number % 2 == 0)
					continue;
				else if(is_cancelled && is_cancelled)
					break;
				
				subframeStartSampleIndex = frameStartSampleIndex + subFrameIndex * LteData[ii].frameNumSamples / NUM_SUBFRAMES_PER_FRAME;

				/*Decode Physical Confrol Format Indicator Channel (PCFICH) */

				//printf("Decoding :          Frame Number  == %d        SubFrame Number == %d\n",current_frame_number,subFrameIndex);


				lteDecodePCFICH(signal_384.get(),//signal768,
					h_est,
					hNoiseVariance,
					LteData,
					ii, //CellNo
					subFrameIndex,
					subframeStartSampleIndex);
				//std::cout << "LteDecodePCFICH Time elapsed: " << lte_diffclock(end,begin) << " ms\n";

				/* Decode LTE Physical Downlink Control Channel (PDCCH) */


				lte_decode_pdcch(signal_384.get(),//signal768,
					h_est,
					hNoiseVariance,
					LteData,
					ii,//cell_no
					subFrameIndex,
					subframeStartSampleIndex);


				// std::cout << "LteDecodePDCCH Time elapsed: " << lte_diffclock(end,begin) << " ms\n";

				// For debug..
				current_physical_cell_id;
				current_layer_3;
				current_frame_number;
				auto current_dci_format = dci_format_info;

				/* Decode LTE Physical Downlink Control Channel (PDCCH) -End*/
				for(unsigned int index_dci_1a = 0; index_dci_1a < dci_format_info.num_dci_format_1a; index_dci_1a++) {
					auto status = lte_pdsch_decode(signal_384.get(),//signal768,
						h_est,
						hNoiseVariance,
						LteData,
						ii,
						subFrameIndex,
						subframeStartSampleIndex,
						dci_format_info, lte_dci_format_1a, index_dci_1a);
					//std::cout << "LteDecodePDSCH Time elapsed: " << lte_diffclock(end,begin) << " ms\n";

					if(status == LTE_SUCCESS) {
						meas.dci_format = lte_dci_format_1a;
						if(relevant_si_info) relevant_si_info->decoded_ = true;
						break;
					}
				}

				for(unsigned int index_dci_1c = 0; index_dci_1c < dci_format_info.num_dci_format_1c; index_dci_1c++) {

					auto status = lte_pdsch_decode(signal_384.get(),//signal768,
						h_est,
						hNoiseVariance,
						LteData,
						ii,
						subFrameIndex,
						subframeStartSampleIndex,
						dci_format_info, lte_dci_format_1c, index_dci_1c);
					//std::cout << "LteDecodePDSCH Time elapsed: " << lte_diffclock(end,begin) << " ms\n";

					if(status == LTE_SUCCESS) {
						meas.dci_format = lte_dci_format_1c;
						if(relevant_si_info) relevant_si_info->decoded_ = true;
						break;
					}
				}

				// If no hints check to see if we decoded sib 1, if so use the scheduling info for current measurement.
				if(si_scheduling_hints == nullptr && meas.layer_3_.sib1_.decoded_) {
					internal_scheduling_hints = lte_si_info_group::create_lte_si_info_group(meas);
					si_scheduling_hints = &internal_scheduling_hints;
					break;
				}


			}//Subframe processing end

			/*Process Subframe End */


			//std::cout<<"\nTotal frame count ==\n"<<framecount++;
			//goto label1;
		}

		/* Go to the next frame */
		frameStartSampleIndex = frameStartSampleIndex + LteData[ii].frameNumSamples;
		current_frame_number++;
		LteData[ii].current_frame_number++;
	}

	return 0;
};

}