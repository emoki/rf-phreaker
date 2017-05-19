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
	data.measurement_signal_level_ = scanner::signal_level_calculator::calculate_sl(avg_rms, info);
	data.measurement_bandwidth_ = info.bandwidth();
	data.measurement_frequency_ = info.frequency();
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

inline void convert_to_basic_data(basic_data &data, const scanner::measurement_info &info, const power_info &p_info) {
	data.serial_ = info.serial();
	data.measurement_signal_level_ = scanner::signal_level_calculator::calculate_sl(p_info.avg_rms_, info);
	data.measurement_bandwidth_ = p_info.bandwidth_;
	data.measurement_frequency_ = p_info.freq_;
	data.collection_round_ = info.collection_round();
	data.status_flags_ = 0;
	data.time_ = info.origin_time_pc().count();
}

inline basic_data convert_to_basic_data(const scanner::measurement_info &info, const power_info &p_info) {
	basic_data data;
	convert_to_basic_data(data, info, p_info);
	return data;
}

inline void convert_to_basic_data(basic_data &data, const scanner::measurement_info &info, const gsm_measurement &gsm) {
	data.serial_ = info.serial();
	data.measurement_signal_level_ = scanner::signal_level_calculator::calculate_sl(gsm.channel_power_, info, gsm.center_frequency_);
	data.measurement_bandwidth_ = khz(200);
	data.measurement_frequency_ = gsm.center_frequency_;
	data.collection_round_ = info.collection_round();
	data.status_flags_ = 0;
	data.time_ = info.origin_time_pc().count();
}

inline basic_data convert_to_basic_data(const scanner::measurement_info &info, const gsm_measurement &gsm) {
	basic_data data;
	convert_to_basic_data(data, info, gsm);
	return data;
}

inline void convert_to_gsm_data(gsm_data &data, const scanner::measurement_info &info, const gsm_measurement &gsm) {
	convert_to_basic_data(data, info, gsm);
	data.bsic_ = gsm.bsic_;
	data.tdma_frame_number_ = gsm.tdma_frame_number_;
	data.ctoi_ = gsm.c_i_ratio_;
	data.operating_band_ = info.get_gsm_band();
	data.cell_signal_level_ = scanner::signal_level_calculator::calculate_sl(gsm.rms_corr_power_, info, gsm.center_frequency_);
	data.layer_3_ = gsm.layer_3_;
	static channel_conversion conversion;
	data.arfcn_ = conversion.frequency_to_arfcn(gsm.center_frequency_, info.get_gsm_band()).channel_;
}

inline gsm_data convert_to_gsm_data(const scanner::measurement_info &info, const gsm_measurement &gsm) {
	gsm_data data;
	convert_to_gsm_data(data, info, gsm);
	return data;
}

inline void convert_to_umts_data(umts_data &data, const scanner::measurement_info &info, const umts_measurement &umts) {
	convert_to_basic_data(data, info, umts.rms_signal_);
	data.measurement_frequency_ += umts.intermediate_frequency_;
	data.cpich_ = umts.cpich_;
	data.ecio_ = umts.ecio_;
	data.operating_band_ = info.get_umts_band();
	data.rscp_ = data.measurement_signal_level_ + data.ecio_;
	data.layer_3_ = umts.layer_3_;
	static channel_conversion conversion;
	data.uarfcn_ = conversion.frequency_to_uarfcn(data.measurement_frequency_, info.get_umts_band()).channel_;
}

inline umts_data convert_to_umts_data(const scanner::measurement_info &info, const umts_measurement &umts) {
	umts_data data;
	convert_to_umts_data(data, info, umts);
	return data;
}

inline void convert_to_lte_data(lte_data &data, const scanner::measurement_info &info, const lte_measurement &lte, double avg_rms)
{
	convert_to_basic_data(data, info, avg_rms);
	data.measurement_frequency_ += lte.intermediate_frequency_;
	data.cyclic_prefix_ = lte.CyclicPrefix;
	data.dl_bandwidth_ = convert_bandwidth(lte.Bandwidth);
	data.frame_number_ = lte.frame_number;
	data.layer_3_ = lte.layer_3_;
	data.num_antenna_ports_ = lte.NumAntennaPorts;
	static channel_conversion conversion;
	data.operating_band_ = info.get_lte_band();
	data.earfcn_ = conversion.frequency_to_earfcn(data.measurement_frequency_, info.get_lte_band()).channel_;
	data.physical_cell_id_ = lte.RsRecord.ID;
	data.psch_id_ = lte.PschRecord.ID;
	data.psch_quality_ = lte.PschRecord.NormCorr;
	data.rsrp_ = scanner::signal_level_calculator::calculate_sl(lte.estimated_rsrp, info);
	data.rssi_ = scanner::signal_level_calculator::calculate_sl(lte.estimated_rssi, info);
	data.rsrq_ = lte.estimated_rsrq;
	data.ssch_id_ = lte.SschRecord.ID;
	data.ssch_quality_ = lte.SschRecord.NormCorr;
	data.sync_quality_ = lte.sync_quality;
}

inline lte_data convert_to_lte_data(const scanner::measurement_info &info, const lte_measurement &lte, double avg_rms)
{
	lte_data data;
	convert_to_lte_data(data, info, lte, avg_rms);
	return data;
}

inline void convert_to_power_spectrum_data(power_spectrum_data &data, const scanner::measurement_info &info, const ipp_32f_array &power_array, const power_spectrum_spec &spec) {
	Ipp32f sum = 0;
	if(power_array.length())
		ippsSum_32f(power_array.get(), power_array.length(), &sum, ippAlgHintFast);
	convert_to_basic_data(data, info, sum);
	data.params_ = spec;
	data.power_.resize(spec.span_ / spec.bin_size_);
	auto packet_start_freq = info.frequency() - (info.sampling_rate() / 2);
	int start_bin = static_cast<int>((spec.start_frequency_ - packet_start_freq) / spec.bin_size_);
	int end_bin = static_cast<int>((spec.end_frequency_ - packet_start_freq) / spec.bin_size_);
	if(end_bin > power_array.length())
		throw processing_error("power_spectrum_array is too small for conversion");
	for(size_t i = 0; i < data.power_.size(); ++i) {
		data.power_[i] = scanner::signal_level_calculator::calculate_sl(power_array[start_bin + i],
			info, static_cast<frequency_type>(data.params_.start_frequency_ + data.params_.step_size_ * i));
	}
}

inline power_spectrum_data convert_to_power_spectrum_data(const scanner::measurement_info &info, const ipp_32f_array &power_array, const power_spectrum_spec &spec) {
	power_spectrum_data data;
	convert_to_power_spectrum_data(data, info, power_array, spec);
	return data;
}

inline void convert_to_iq_data(iq_data &data, const scanner::measurement_info &info) {
	auto avg_rms = ipp_helper::calculate_average_rms(info.get_iq().get(), info.get_iq().length());
	convert_to_basic_data(data, info, avg_rms);

	data.dwell_time_ = (int64_t)(info.get_iq().length()) * 1e9L / info.sampling_rate();
	data.sampling_rate_ = info.sampling_rate();

	auto blade = info.blade_adjustments();
	auto rf_board = info.rf_board_adjustments();
	// Use interpolation (if necessary) to reconcile rf_blade and nuand adjustments.
	data.power_adjustment_.path_.low_freq_ = std::max(blade.path_.low_freq_, rf_board.path_.low_freq_);
	data.power_adjustment_.path_.high_freq_ = std::min(blade.path_.high_freq_, rf_board.path_.high_freq_);
	data.power_adjustment_.step_size_ = khz(500);

	// We add one to adj_size because the last freq is inclusive.
	auto adj_size_required = (double)((data.power_adjustment_.path_.high_freq_ - data.power_adjustment_.path_.low_freq_) / data.power_adjustment_.step_size_) + 1;
	data.power_adjustment_.power_.resize((size_t)std::ceil(adj_size_required));

	// Add an additional step_size to end_freq so that we are gauranteed to have the last freq.
	auto end_freq = data.power_adjustment_.path_.high_freq_ + data.power_adjustment_.step_size_;
	auto j = 0;
	for(auto i = data.power_adjustment_.path_.low_freq_; i < end_freq; i += data.power_adjustment_.step_size_) {
		data.power_adjustment_.power_[j++] = blade.find_adjustment(i) + rf_board.find_adjustment(i);
	}

	data.samples_.resize(info.get_iq().length() * 2);
	memcpy(data.samples_.data(), info.get_iq().get(), info.get_iq().length() * sizeof(scanner::measurement_info::sample_type));
}

inline iq_data convert_to_iq_data(const scanner::measurement_info &info) {
	iq_data data;
	convert_to_iq_data(data, info);
	return data;
}


}}