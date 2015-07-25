#pragma once

#include "rf_phreaker/lte_analysis/lte_types.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include <vector>

namespace rf_phreaker {

class lte_measurement;
typedef std::vector<lte_measurement> lte_measurements;

class lte_measurement
{
public:
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
	lte_dci_format_type dci_format;
	unsigned int num_bits_dci_1A;
	unsigned int num_bits_dci_1C;
	unsigned int n_gap_1;
	unsigned int n_gap_2;
	unsigned int num_dl_vrb_gap_1;
	unsigned int num_dl_vrb_gap_2;
	unsigned int num_step_rb;
	unsigned int resource_block_assign_1c_bits;
	unsigned int rbg_size_p;
	unsigned int frame_number;
	unsigned int current_frame_number;
	unsigned int si_window;
	double estimated_rsrp;
	double estimated_rssi;
	double estimated_rsrq;
	double rsrp;
	double rssi;
	double rsrq;
	double sync_quality;
	layer_3_information::lte_rrc_message_aggregate layer_3_;

	lte_measurement() { clear(); }

	lte_measurement& operator=(lte_measurement meas) {
		meas.swap(*this);
		return *this;
	}

	// Change these so it handles extended cyclic prefix.
	int ofdm_symbols_per_slot() {
		return OFDM_SYMBOLS_PER_SLOT;
	}

	// Change these so it handles extended cyclic prefix.
	int ofdm_symbols_per_subframe() {
		return OFDM_SYMBOLS_PER_SUBFRAME;
	}

	void swap(lte_measurement &meas) {
		std::swap(meas.PschRecord, PschRecord);
		std::swap(meas.SschRecord, SschRecord);
		std::swap(meas.RsRecord, RsRecord);
		std::swap(meas.CyclicPrefix, CyclicPrefix);
		std::swap(meas.NumAntennaPorts, NumAntennaPorts);
		std::swap(meas.AvgDigitalVoltage, AvgDigitalVoltage);
		std::swap(meas.Bandwidth, Bandwidth);
		std::swap(meas.fftSize, fftSize);
		std::swap(meas.frameNumSamples, frameNumSamples);
		std::swap(meas.cPSamplesSymbol0, cPSamplesSymbol0);
		std::swap(meas.cPSamplesSymbol1to6, cPSamplesSymbol1to6);
		std::swap(meas.numResouceBlocks, numResouceBlocks);
		std::swap(meas.lteControlSysmbolLenght, lteControlSysmbolLenght);
		std::swap(meas.phich_duration, phich_duration);
		std::swap(meas.phich_resources, phich_resources);
		std::swap(meas.fft_subcarrier_start_index, fft_subcarrier_start_index);
		std::swap(meas.num_bits_dci_1A, num_bits_dci_1A);
		std::swap(meas.frame_number, frame_number);
		std::swap(meas.current_frame_number, current_frame_number);
		std::swap(meas.estimated_rsrp, estimated_rsrp);
		std::swap(meas.estimated_rssi, estimated_rssi);
		std::swap(meas.estimated_rsrq, estimated_rsrq);
		std::swap(meas.rsrp, rsrp);
		std::swap(meas.rssi, rssi);
		std::swap(meas.rsrq, rsrq);
		std::swap(meas.sync_quality, sync_quality);
		meas.layer_3_.swap(layer_3_);
	}

	void clear() {
		PschRecord.ID = 0;
		PschRecord.NormCorr = 0;
		PschRecord.RMSCorr = 0;
		PschRecord.StartSampleNum = 0;
		SschRecord.ID = 0;
		SschRecord.NormCorr = 0;
		SschRecord.RMSCorr = 0;
		SschRecord.StartSampleNum = 0;
		RsRecord.ID = 0;
		RsRecord.NormCorr = 0;
		RsRecord.RMSCorr = 0;
		RsRecord.StartSampleNum = 0;
		CyclicPrefix = Normal;
		NumAntennaPorts = LteAntPorts_Unknown;
		AvgDigitalVoltage = 0;
		Bandwidth = LteBandwidth_Unknown;
		fftSize = FFTSIZE_UNKNOWN;
		frameNumSamples = FRAMENUMSAMPLES_FFT256;
		cPSamplesSymbol0 = CP_SAMPLES_FFT256_SYMBOL_0;
		cPSamplesSymbol1to6 = CP_SAMPLES_FFT256_SYMBOL_0;
		numResouceBlocks = NUMRESOURCEBLOCKS_FFT256;
		lteControlSysmbolLenght = 0;
		phich_duration = 0;
		phich_resources = 0;
		fft_subcarrier_start_index = 0;
		num_bits_dci_1A = 0;
		frame_number = 0;
		current_frame_number = 0;
		estimated_rsrp = -DBL_MAX;
		estimated_rssi = -DBL_MAX;
		estimated_rsrq = -DBL_MAX;
		rsrp = -DBL_MAX;
		rssi = -DBL_MAX;
		rsrq = -DBL_MAX;
		sync_quality = -DBL_MAX;
		si_window = LTE_NULL; // Needs to be LTE_NULL for decoding purposes.
		dci_format = lte_dci_format_unknown;


		layer_3_.clear();
	}
};

}