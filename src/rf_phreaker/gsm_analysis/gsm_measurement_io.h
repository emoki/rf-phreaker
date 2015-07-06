#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate_io.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker {

static std::string gsm_io_delimiter = "\t";
static std::string gsm_io_spacer = " | ";

inline std::ostream& output_gsm_meas_debug_header(std::ostream &os) {
	os << "channel_index" << gsm_io_delimiter
		<< "intermediate_freq" << gsm_io_delimiter
		<< "center_freq" << gsm_io_delimiter
		<< "channel_power" << gsm_io_delimiter
		<< "fcch_freq_index" << gsm_io_delimiter
		<< "fcch_peak_power" << gsm_io_delimiter
		<< "band_power" << gsm_io_delimiter
		<< "side_power" << gsm_io_delimiter
		<< "rms_corr_power" << gsm_io_delimiter
		<< "norm_sync_corr" << gsm_io_delimiter
		<< "c_i_ratio" << gsm_io_delimiter
		<< "sync_sample_num" << gsm_io_delimiter
		<< "bsic" << gsm_io_delimiter
		<< "tdma_frame_number" << gsm_io_delimiter
		<< "sync_burst_decoded" << gsm_io_delimiter
		<< "cgi_decoded" << gsm_io_delimiter
		<< "bcch_burst_decoded" << gsm_io_delimiter
		<< "bcch_octets" << gsm_io_delimiter;
	//layer_3_information::header(os, layer_3_information::gsm_rrc_message_aggregate());
	return os;
}

inline std::ostream& output_bcch_octets(std::ostream &os, const char *t) {
	os << "0x";
	for(int i = 0; i < gsm_measurement::bcch_octet_size_; ++i)
		os << hex_conversion::to_string<2>(t[i]);
	os << std::dec;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const gsm_measurement &t) {
	os << t.channel_index_ << gsm_io_delimiter
		<< t.intermediate_frequency_ << gsm_io_delimiter
		<< t.center_frequency_ << gsm_io_delimiter
		<< t.channel_power_ << gsm_io_delimiter
		<< t.fcch_freq_index_ << gsm_io_delimiter
		<< t.fcch_peak_power_ << gsm_io_delimiter
		<< t.band_power_ << gsm_io_delimiter
		<< t.side_power_ << gsm_io_delimiter
		<< t.rms_corr_power_ << gsm_io_delimiter
		<< t.norm_sync_corr_ << gsm_io_delimiter
		<< t.c_i_ratio_ << gsm_io_delimiter
		<< t.sync_sample_num_ << gsm_io_delimiter
		<< t.bsic_ << gsm_io_delimiter
		<< t.tdma_frame_number_ << gsm_io_delimiter
		<< std::boolalpha
		<< t.sync_burst_decoded_ << gsm_io_delimiter
		<< t.cgi_decoded_ << gsm_io_delimiter
		<< t.bcch_burst_decoded_ << gsm_io_delimiter
		<< std::noboolalpha;
		output_bcch_octets(os, t.bcch_octets_);
	return os;
}

}