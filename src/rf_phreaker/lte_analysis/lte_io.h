#pragma once

#include "lte_common.h"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>


static std::string lte_io_delimiter = "\t";
static std::string lte_io_spacer = " | ";

inline void output_lte_meas_debug_header(std::ostream &os)
{
	os	<< "psch_id" << lte_io_delimiter
		<< "psch_norm_corr" << lte_io_delimiter
		<< "psch_rms_corr" << lte_io_delimiter
		<< "psch_start_sample" << lte_io_delimiter
		<< "ssch_id" << lte_io_delimiter
		<< "ssch_norm_corr" << lte_io_delimiter
		<< "ssch_rms_corr" << lte_io_delimiter
		<< "ssch_start_sample" << lte_io_delimiter
		<< "rs_id" << lte_io_delimiter
		<< "rs_norm_corr" << lte_io_delimiter
		<< "rs_rms_corr" << lte_io_delimiter
		<< "rs_start_sample" << lte_io_delimiter
		<< "num_ant_ports" << lte_io_delimiter
		<< "avg_dig_volt" << lte_io_delimiter
		<< "bandwidth_mhz" << lte_io_delimiter
		<< "fft_size" << lte_io_delimiter
		<< "frame_num_samples" << lte_io_delimiter
		<< "cp_samples_symbol_0" << lte_io_delimiter
		<< "cp_samples_symbol_1to6" << lte_io_delimiter
		<< "num_resource_blocks" << lte_io_delimiter
		<< "lte_control_symbol_length" << lte_io_delimiter
		<< "phich_duration" << lte_io_delimiter
		<< "phich_resources" << lte_io_delimiter
		<< "fft_sub_carrier_start_index" << lte_io_delimiter
		<< "num_bits_dci_1a" << lte_io_delimiter
		<< "frame_number" << lte_io_delimiter
		<< "rsrp" << lte_io_delimiter
		<< "rssi" << lte_io_delimiter
		<< "rsrq" << lte_io_delimiter
		<< "mcc" << lte_io_delimiter
		<< "mnc" << lte_io_delimiter
		<< "lac" << lte_io_delimiter
		<< "cid";
}

inline std::ostream& operator<<( std::ostream &os, const CORR_RECORD_TYPE &t)
{
	os  << t.ID << lte_io_delimiter
		<< t.NormCorr << lte_io_delimiter
		<< t.RMSCorr << lte_io_delimiter
		<< t.StartSampleNum;

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const CYCLICPREFIX &t)
{
	switch(t)
	{
	case Normal:
		os << "Normal";
		break;
	case Extended:
		os << "Extended";
		break;
	default:
		os << "Unknown";
	};

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const LteNumAntennaPorts &t)
{
	switch(t)
	{
	case LteAntPorts_Unknown:
		os << "Unknown";
		break;
	case LteAntPorts_1:
		os << "1";
		break;
	case LteAntPorts_2:
		os << "2";
		break;
	case LteAntPorts_4:
		os << "4";
		break;
	default:
		os << "default unknown";
	};

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const LteChannelBandwidth &t)
{
	switch(t)
	{
	case LteBandwidth_Unknown:
		os << "Unknown";
		break;
	case LteBandwidth_1_4MHZ:
		os << "1.4";
		break;
	case LteBandwidth_3MHZ:
		os << "3";
		break;
	case LteBandwidth_5MHZ:
		os << "4";
		break;
	case LteBandwidth_10MHZ:
		os << "10";
		break;
	case LteBandwidth_15MHZ:
		os << "15";
		break;
	case LteBandwidth_20MHZ:
		os << "20";
		break;
	default:
		os << "default unknown";
	};

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const LteFftSize &t)
{
	switch(t)
	{
	case FFTSIZE_UNKNOWN:
		os << "Unknown";
		break;
	case FFTSIZE_128:
		os << "128";
		break;
	case FFTSIZE_256:
		os << "256";
		break;
	case FFTSIZE_512:
		os << "512";
		break;
	case FFTSIZE_1024:
		os << "1024";
		break;
	case FFTSIZE_1536:
		os << "1536";
		break;
	case FFTSIZE_2048:
		os << "2048";
		break;
	default:
		os << "default unknown";
	};

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const LteFrameNumSamples &t)
{
	switch(t)
	{
	case FRAMENUMSAMPLES_FFT256:
		os << "38400";
		break;
	case FRAMENUMSAMPLES_FFT512:
		os << "76800";
		break;
	case FRAMENUMSAMPLES_FFT1024:
		os << "153600";
		break;
	default:
		os << "default unknown";
	};

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const LteCyclicPrefixSamples &t)
{
	switch(t)
	{
	case CP_SAMPLES_FFT256_SYMBOL_0:
		os << "20";
		break;
	case CP_SAMPLES_FFT256_SYMBOL_1TO6:
		os << "18";
		break;
	case CP_SAMPLES_FFT512_SYMBOL_0:
		os << "40";
		break;
	case CP_SAMPLES_FFT512_SYMBOL_1TO6:
		os << "36";
		break;
	case CP_SAMPLES_FFT1024_SYMBOL_0:
		os << "80";
		break;
	case CP_SAMPLES_FFT1024_SYMBOL_1TO6:
		os << "72";
		break;
	default:
		os << "default unknown";
	};

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const LteNumResourceBlocks &t)
{
	switch(t)
	{
	case NUMRESOURCEBLOCKS_FFT256:
		os << "15";
		break;
	case NUMRESOURCEBLOCKS_FFT512:
		os << "25";
		break;
	case NUMRESOURCEBLOCKS_FFT1024:
		os << "50";
		break;
	default:
		os << "default unknown";
	};

	return os;
}

inline std::ostream& operator<<( std::ostream &os, const lte_measurement &t)
{
	os	<< t.PschRecord << lte_io_delimiter 
		<< t.SschRecord << lte_io_delimiter
		<< t.RsRecord << lte_io_delimiter
		<< t.NumAntennaPorts << lte_io_delimiter
		<< t.AvgDigitalVoltage << lte_io_delimiter
		<< t.Bandwidth << lte_io_delimiter
		<< t.fftSize << lte_io_delimiter
		<< t.frameNumSamples << lte_io_delimiter
		<< t.cPSamplesSymbol0 << lte_io_delimiter
		<< t.cPSamplesSymbol1to6 << lte_io_delimiter
		<< t.numResouceBlocks << lte_io_delimiter
		<< t.lteControlSysmbolLenght << lte_io_delimiter
		<< t.phich_duration << lte_io_delimiter
		<< t.phich_resources << lte_io_delimiter
		<< t.fft_subcarrier_start_index << lte_io_delimiter
		<< t.num_bits_dci_1A << lte_io_delimiter
		<< t.frame_number << lte_io_delimiter
		<< t.rsrp << lte_io_delimiter
		<< t.rssi << lte_io_delimiter
		<< t.rsrq << lte_io_delimiter
		<< t.layer_3_.mcc_.to_string() << lte_io_delimiter
		<< t.layer_3_.mnc_.to_string() << lte_io_delimiter
		<< t.layer_3_.lac_ << lte_io_delimiter
		<< t.layer_3_.cid_ << lte_io_delimiter;

	return os;
}


