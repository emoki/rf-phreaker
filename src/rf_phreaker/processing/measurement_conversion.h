#pragma once

#include "rf_phreaker/processing/processing_utility.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/scanner/signal_level_calculator.h"

namespace rf_phreaker { namespace processing {

inline void convert_to_basic_data(basic_data &data, const scanner::measurement_info &info, double avg_rms)
{
	data.serial_ = info.serial();
	data.carrier_signal_level_ = scanner::signal_level_calculator::calculate_sl(avg_rms, info);
	data.carrier_bandwidth_ = info.bandwidth();
	data.carrier_frequency_ = info.frequency();
	data.collection_round_ = info.collection_round();
	data.status_flags_ = 0;
	data.time_ = info.origin_time_pc().count();
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
	data.uarfcn_ = conversion.frequency_to_uarfcn(info.frequency(), info.get_operating_band()).channel_;
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
	data.dl_bandwidth_ = convert_bandwidth(lte.Bandwidth);
	data.frame_number_ = lte.frame_number;
	data.layer_3_ = lte.layer_3_;
	data.num_antenna_ports_ = lte.NumAntennaPorts;
	static channel_conversion conversion;
	data.operating_band_ = info.get_operating_band();
	data.earfcn_ = conversion.frequency_to_earfcn(info.frequency(), info.get_operating_band()).channel_;
	data.physical_cell_id_ = lte.RsRecord.ID;
	data.psch_id_ = lte.PschRecord.ID;
	data.psch_quality_ = 20 * log10(lte.PschRecord.NormCorr);
	data.rsrp_ = scanner::signal_level_calculator::calculate_sl(lte.estimated_rsrp, info);
	data.rssi_ = scanner::signal_level_calculator::calculate_sl(lte.estimated_rssi, info);
	data.rsrq_ = 20 * log10(lte.estimated_rsrq);
	data.ssch_id_ = lte.SschRecord.ID;
	data.ssch_quality_ = 20 * log10(lte.SschRecord.NormCorr);
	data.sync_quality_ = 20 * log10(lte.sync_quality);
}

inline lte_data convert_to_lte_data(const scanner::measurement_info &info, const lte_measurement &lte, double avg_rms)
{
	lte_data data;
	convert_to_lte_data(data, info, lte, avg_rms);
	return data;
}


}}