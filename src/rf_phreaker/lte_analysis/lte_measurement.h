#pragma once

#include "rf_phreaker/lte_analysis/lte_types.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include <vector>

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
	unsigned int num_bits_dci_1A;
	unsigned int frame_number;
	double rsrp;
	double rssi;
	double rsrq;
	double sync_quality;
	layer_3_information::lte_rrc_message_aggregate layer_3_;

	lte_measurement& operator=(lte_measurement meas)
	{
		meas.swap(*this);
		return *this;
	}

	void swap(lte_measurement &meas)
	{
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
		std::swap(meas.rsrp, rsrp);
		std::swap(meas.rssi, rssi);
		std::swap(meas.rsrq, rsrq);
		std::swap(meas.sync_quality, sync_quality);
		meas.layer_3_.swap(layer_3_);
	}
};