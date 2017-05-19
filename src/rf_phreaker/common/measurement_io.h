#pragma once
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate_io.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate_io.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate_io.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>

namespace rf_phreaker {


static std::string delimiter = "\t";
static std::string spacer = " | ";

inline std::ostream& operator<<(std::ostream &os, const hardware &t);
inline std::ostream& operator<<(std::ostream &os, const gps &t);
inline std::ostream& operator<<(std::ostream &os, const basic_data &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_data &t);
inline std::ostream& operator<<(std::ostream &os, const umts_data &t);
inline std::ostream& operator<<(std::ostream &os, const lte_data &t);
inline std::ostream& operator<<(std::ostream &os, const power_spectrum_data &t);

inline std::string file_base(const hardware &) { return "scanner_"; }
inline std::string file_base(const gps &) { return "gps_"; }
inline std::string file_base(const basic_data &) { return "basic_"; }
inline std::string file_base(const gsm_data &) { return "gsm_"; }
inline std::string file_base(const umts_data &) { return "umts_"; }
inline std::string file_base(const lte_data &) { return "lte_"; }
inline std::string file_base(const power_spectrum_data &) { return "power_spectrum_"; }

inline std::ostream& header(std::ostream &os, const hardware &t) {
	os << "scanner_serial" << delimiter
		<< "hw_id" << delimiter
		<< "freq_paths(low-high)" << delimiter
		<< "device_communication" << delimiter
		<< "rf_calibration_date" << delimiter
		<< "freq_correction_date" << delimiter
		<< "license";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const hardware &t) {
	os << t.serial_ << delimiter;
	os << t.hw_id_ << delimiter;

	for(const auto &d : t.frequency_paths_)
		os << d.low_freq_ << "-" << d.high_freq_ << spacer;

	switch(t.device_communication_) {
	case USB_HI_SPEED:
		os << "USB_HI_SPEED" << delimiter;
		break;
	case USB_SUPER_SPEED:
		os << "USB_SUPER_SPEED" << delimiter;
		break;
	case UNKNOWN_SPEED:
	default:
		os << "UNKNOWN_SPEED" << delimiter;
	}

	char mbstr[100];
	std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t.rf_calibration_date_));
	os << mbstr << delimiter; //std::put_time(t1, "%Y-%m-%d %X") << "\n";

	std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t.frequency_correction_calibration_date_));
	os << mbstr << delimiter; //std::put_time(t1, "%Y-%m-%d %X") << "\n";

	for(auto &byte : t.license_data_.bytes_) {
		os << std::hex << std::setw(2) << (int)byte;
	}
	os << std::dec;

	return os;
}

inline std::ostream& header(std::ostream &os, const gps &t) {
	os << "scanner_serial" << delimiter
		<< "gps_lock" << delimiter
		<< "utc" << delimiter
		<< "visible_satellites" << delimiter
		<< "tracking_satellites" << delimiter
		<< "latitude" << delimiter
		<< "longitude" << delimiter
		<< "altitude" << delimiter
		<< "angle_degrees" << delimiter
		<< "speed" << delimiter
		<< "dilution_of_precision" << delimiter
		<< "horizontal_accuracy_meters" << delimiter
		<< "vertical_accuracy_meters" << delimiter
		<< "raw_status" << delimiter
		<< "num_satellite_info";
		for(auto i = 0; i < 32; ++i)
			os << delimiter << "sat_prn_" << i << delimiter
			<< "sat_snr_" << i << delimiter
			<< "sat_elevation_" << i << delimiter
			<< "sat_azimuth_" << i;
		return os;
}

inline std::ostream& operator<<(std::ostream &os, const gps &t) {
	os << t.serial_ << delimiter
		<< (t.lock_ ? "TRUE" : "FALSE") << delimiter
		<< t.coordinated_universal_time_ << delimiter
		<< t.visible_satellites_ << delimiter
		<< t.tracking_satellites_ << delimiter
		<< t.latitude_ << delimiter
		<< t.longitude_ << delimiter
		<< t.altitude_ << delimiter
		<< t.angle_ << delimiter
		<< t.speed_ << delimiter
		<< t.dilution_of_precision_ << delimiter
		<< t.horizontal_accuracy_meters_ << delimiter
		<< t.vertical_accuracy_meters_ << delimiter
		<< std::setw(4) << std::setfill('0') << std::hex << t.raw_status_ << std::dec << delimiter
		<< t.satellites_.size();
	
	for(auto &i : t.satellites_)
		os << delimiter << i.prn_ << delimiter
			<< i.snr_ << delimiter
			<< i.elevation_ << delimiter
			<< i.azimuth_;
	for(size_t i = 0; i < 32 - t.satellites_.size(); ++i)
		os << delimiter << delimiter << delimiter << delimiter;
	return os;
}

inline std::ostream& header(std::ostream &os, const basic_data &t) {
	os << "scanner_serial" << delimiter
		<< "collection_round" << delimiter
		<< "measurement_freq" << delimiter
		<< "measurement_bandwidth" << delimiter
		<< "measurement_signal_level" << delimiter
		<< "time" << delimiter
		<< "status_flags";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const basic_data &t) {
	os << t.serial_ << delimiter
		<< t.collection_round_ << delimiter
		<< t.measurement_frequency_ << delimiter
		<< t.measurement_bandwidth_ << delimiter
		<< t.measurement_signal_level_ << delimiter
		<< t.time_ << delimiter
		<< t.status_flags_;
	return os;
}

inline std::ostream& header(std::ostream &os, const gsm_data &t) {
	header(os, static_cast<basic_data>(t)) << delimiter
		<< "arfcn" << delimiter
		<< "operating_band" << delimiter
		<< "bsic" << delimiter
		<< "cell_signal_level" << delimiter
		<< "c/i" << delimiter
		<< "tdma_frame_number" << delimiter;
	layer_3_information::header(os, t.layer_3_);
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const gsm_data &t) {
	os << static_cast<basic_data>(t) << delimiter
		<< t.arfcn_ << delimiter
		<< to_string(t.operating_band_) << delimiter
		<< t.bsic_ << delimiter
		<< t.cell_signal_level_ << delimiter
		<< t.ctoi_ << delimiter
		<< t.tdma_frame_number_ << delimiter
		<< t.layer_3_;
	return os;
}

inline std::ostream& header(std::ostream &os, const umts_data &t) {
	header(os, static_cast<basic_data>(t)) << delimiter
		<< "uarfcn" << delimiter
		<< "operating_band" << delimiter
		<< "cpich" << delimiter
		<< "ecio" << delimiter
		<< "rscp" << delimiter;
	layer_3_information::header(os, t.layer_3_);
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_data &t) {
	os << static_cast<basic_data>(t) << delimiter
		<< t.uarfcn_ << delimiter
		<< to_string(t.operating_band_) << delimiter
		<< t.cpich_ << delimiter
		<< t.ecio_ << delimiter
		<< t.rscp_ << delimiter
		<< t.layer_3_;
	return os;
}

inline std::ostream& header(std::ostream &os, const lte_data &t) {
	header(os, static_cast<basic_data>(t)) << delimiter
		<< "earfcn" << delimiter
		<< "operating_band" << delimiter
		<< "phys_cell_id" << delimiter
		<< "rsrp" << delimiter
		<< "rsrq" << delimiter
		<< "rssi" << delimiter
		<< "psch_id" << delimiter
		<< "psch_quality" << delimiter
		<< "ssch_id" << delimiter
		<< "ssch_quality" << delimiter
		<< "sync_quality" << delimiter
		<< "cyclic_prefix" << delimiter
		<< "num_antenna_ports" << delimiter
		<< "decoded_bandwidth" << delimiter
		<< "frame_number" << delimiter;
	layer_3_information::header(os, t.layer_3_);
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const lte_data &t) {
	os << static_cast<basic_data>(t) << delimiter
		<< t.earfcn_ << delimiter
		<< to_string(t.operating_band_) << delimiter
		<< t.physical_cell_id_ << delimiter
		<< t.rsrp_ << delimiter
		<< t.rsrq_ << delimiter
		<< t.rssi_ << delimiter
		<< t.psch_id_ << delimiter
		<< t.psch_quality_ << delimiter
		<< t.ssch_id_ << delimiter
		<< t.ssch_quality_ << delimiter
		<< t.sync_quality_ << delimiter
		<< t.cyclic_prefix_ << delimiter
		<< t.num_antenna_ports_ << delimiter
		<< t.dl_bandwidth_ << delimiter
		<< t.frame_number_ << delimiter
		<< t.layer_3_;
	return os;
}

inline std::ostream& header(std::ostream &os, const power_spectrum_spec &t) {
	os << "dwell_time" << delimiter
		<< "sampling_rate" << delimiter
		<< "start_frequency" << delimiter
		<< "end_frequency" << delimiter
		<< "span" << delimiter
		<< "window_length" << delimiter
		<< "num_windows" << delimiter
		<< "bin_size" << delimiter
		<< "step_size";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const power_spectrum_spec &t) {
	os << t.dwell_time_ << delimiter
		<< t.sampling_rate_ << delimiter
		<< t.start_frequency_ << delimiter
		<< t.end_frequency_ << delimiter
		<< t.span_ << delimiter
		<< t.window_length_ << delimiter
		<< t.num_windows_ << delimiter
		<< t.bin_size_ << delimiter
		<< t.step_size_;
	return os;
}

inline std::ostream& header(std::ostream &os, const power_spectrum_data &t) {
	header(os, static_cast<basic_data>(t)) << delimiter;
	header(os, t.params_) << delimiter
		<< "power...";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const power_spectrum_data &t) {
	os << static_cast<basic_data>(t) << delimiter
		<< t.params_;
	for(auto &i : t.power_)
		os << delimiter << i;
	return os;
}

inline std::ostream& header(std::ostream &os, const power_adjustment &t) {
	os << "low_freq" << delimiter
		<< "high_freq" << delimiter
		<< "step_size";
	// 57 is max bandwidth * 2 for 500 khz spacing.
	for(int i = 0; i < 57; ++i)
		os << delimiter << "power_adj_" << i;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const power_adjustment &t) {
	os << t.path_.low_freq_ << delimiter
		<< t.path_.high_freq_ << delimiter
		<< t.step_size_;
	for(auto i : t.power_)
		os << delimiter << i;
	// 57 is max bandwidth * 2 for 500 khz spacing.
	for(auto i = t.power_.size(); i < 57; ++i)
		os << delimiter;
	return os;
}

inline std::ostream& header(std::ostream &os, const iq_data &t) {
	header(os, static_cast<basic_data>(t)) << delimiter;
	header(os, t.power_adjustment_) << delimiter;
	os << "sampling_rate" << delimiter
		<< "dwell_time" << delimiter
		<< "num_floats" << delimiter
		<< "floats (samples [i {tab} q])";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const iq_data &t) {
	os << static_cast<basic_data>(t) << delimiter;
	os << t.power_adjustment_ << delimiter
		<< t.sampling_rate_ << delimiter
		<< t.dwell_time_ << delimiter
		<< t.samples_.size();
	for(auto &i : t.samples_)
		os << delimiter << i;
	return os;
}

template<typename Data>
inline std::ostream& header(std::ostream &os, const std::vector<Data> &t) {
	return header(os, Data());
}

template<typename Data>
inline std::ostream& operator<<(std::ostream &os, const std::vector<Data> &t) {
	for(auto &i : t)
		os << i << std::endl;
	return os;
}


}
