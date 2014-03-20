#pragma once

#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"

namespace rf_phreaker { namespace processing {

void convert_to_basic_data(basic_data &data, const scanner::measurement_info &info, double avg_rms)
{
	int offset = -83;
	// TODO - Assuming the LNA is maxed.
	data.carrier_signal_level_ = 20 * log10(avg_rms) - info.gain().rxvga1_ - info.gain().rxvga2_ + offset;
	data.carrier_bandwidth_ = info.bandwidth();
	data.carrier_frequency_ = info.frequency();
	data.collection_round_ = info.collection_round();
	data.status_flags_ = 0;
	data.time_ = info.time_ns();
}
	
basic_data convert_to_basic_data(const scanner::measurement_info &info, double avg_rms)
{		
	basic_data data;
	convert_to_basic_data(data, info, avg_rms);
	return data;
}

void convert_to_umts_data(umts_data &data, const scanner::measurement_info &info, const umts_measurement &umts)
{
	convert_to_basic_data(data, info, umts.rms_signal_);
	data.cpich_ = umts.cpich_;
	data.ecio_ = umts.ecio_;
	data.operating_band_ = info.get_operating_band();
	data.rscp_ = data.carrier_signal_level_ + data.ecio_;
	data.layer_3_ = umts.layer_3_;
	static channel_conversion conversion;
	if(info.get_operating_band() == UMTS_OPERATING_BAND_1 && !(info.frequency() % 200))
		const_cast<scanner::measurement_info&>(info).set_operating_band(UMTS_OPERATING_BAND_4);
	data.uarfcn_ = conversion.frequency_to_uarfcn(info.frequency(), info.get_operating_band());
}

umts_data convert_to_umts_data(const scanner::measurement_info &info, const umts_measurement &umts)
{
	umts_data data;
	convert_to_umts_data(data, info, umts);
	return data;
}

void convert_to_lte_data(lte_data &data, const scanner::measurement_info &info, const lte_measurement &lte)
{
	convert_to_basic_data(data, info, lte.AvgDigitalVoltage);
	data.cyclic_prefix_ = lte.CyclicPrefix;
	data.frame_number_ = lte.frame_number;
	data.layer_3_ = lte.layer_3_;
	data.num_antenna_ports_ = lte.NumAntennaPorts;
	static channel_conversion conversion;
	data.operating_band_ = info.get_operating_band();
	data.earfcn_ = conversion.frequency_to_earfcn(info.frequency(), info.get_operating_band());
	data.physical_cell_id_ = lte.RsRecord.ID;
	data.psch_id_ = lte.PschRecord.ID;
	data.psch_quality_ = 20 * log10(lte.PschRecord.NormCorr);
	data.rsrp_ = lte.rsrp;
	data.rsrq_ = lte.rsrq;
	data.rssi_ = lte.rssi;
	data.rs_quality_ = 20 * log10(lte.RsRecord.NormCorr);
	data.ssch_id_ = lte.SschRecord.ID;
	data.ssch_quality_ = 20 * log10(lte.SschRecord.NormCorr);
}

lte_data convert_to_lte_data(const scanner::measurement_info &info, const lte_measurement &lte)
{
	lte_data data;
	convert_to_lte_data(data, info, lte);
	return data;
}


}}