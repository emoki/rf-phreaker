#pragma once

#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/scanner/calibration.h"

namespace rf_phreaker { namespace processing {

inline void convert_to_basic_data(basic_data &data, const scanner::measurement_info &info, double avg_rms)
{
	static scanner::calibration cali;
	data.carrier_signal_level_ = cali.calculate_sl(avg_rms, info.gain());
	data.carrier_bandwidth_ = info.bandwidth();
	data.carrier_frequency_ = info.frequency();
	data.collection_round_ = info.collection_round();
	data.status_flags_ = 0;
	data.time_ = info.time_ns();
}
	
inline basic_data convert_to_basic_data(const scanner::measurement_info &info, double avg_rms)
{		
	basic_data data;
	convert_to_basic_data(data, info, avg_rms);
	return data;
}

inline void convert_to_umts_data(umts_data &data, const scanner::measurement_info &info, const umts_measurement &umts)
{
	convert_to_basic_data(data, info, umts.rms_signal_);
	data.cpich_ = umts.cpich_;
	data.ecio_ = umts.ecio_;
	data.operating_band_ = info.get_operating_band();
	data.rscp_ = data.carrier_signal_level_ + data.ecio_;
	data.layer_3_ = umts.layer_3_;
	static channel_conversion conversion;
	data.uarfcn_ = conversion.frequency_to_uarfcn(info.frequency(), info.get_operating_band());
}

inline umts_data convert_to_umts_data(const scanner::measurement_info &info, const umts_measurement &umts)
{
	umts_data data;
	convert_to_umts_data(data, info, umts);
	return data;
}

inline void convert_to_lte_data(lte_data &data, const scanner::measurement_info &info, const lte_measurement &lte, double avg_rms)
{
	convert_to_basic_data(data, info, avg_rms);
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
	static scanner::calibration cali;
	data.rsrp_ = cali.calculate_sl(lte.rsrp, info.gain());
	data.rssi_ = cali.calculate_sl(lte.rssi, info.gain());
	data.rsrq_ = lte.rsrq;
	data.ssch_id_ = lte.SschRecord.ID;
	data.ssch_quality_ = 20 * log10(lte.SschRecord.NormCorr);
	data.rs_quality_ = -9999;
}

inline lte_data convert_to_lte_data(const scanner::measurement_info &info, const lte_measurement &lte, double avg_rms)
{
	lte_data data;
	convert_to_lte_data(data, info, lte, avg_rms);
	return data;
}


}}