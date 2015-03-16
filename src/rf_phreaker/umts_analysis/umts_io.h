#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate_io.h"

namespace rf_phreaker {

static std::string umts_io_delimiter = "\t";
static std::string umts_io_spacer = " | ";

inline std::ostream& output_umts_meas_debug_header(std::ostream &os) {
	os << "cpich" << umts_io_delimiter
		<< "ecio" << umts_io_delimiter
		<< "rms_signal" << umts_io_delimiter
		<< "sample_num" << umts_io_delimiter
		<< "time" << umts_io_delimiter
		<< "mcc" << umts_io_delimiter
		<< "mnc" << umts_io_delimiter
		<< "lac" << umts_io_delimiter
		<< "cid" << umts_io_delimiter
		<< "intra" << umts_io_delimiter
		<< "inter" << umts_io_delimiter
		<< "inter_rat";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_measurement &t)
{
	os << t.cpich_ << umts_io_delimiter
		<< t.ecio_ << umts_io_delimiter
		<< t.rms_signal_ << umts_io_delimiter
		<< t.sample_num_ << umts_io_delimiter
		<< t.time_ << umts_io_delimiter
		<< t.layer_3_;
	return os;
}

}