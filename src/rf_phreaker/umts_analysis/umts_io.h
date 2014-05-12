#pragma once

#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate_io.h"

namespace rf_phreaker {

static std::string umts_io_delimiter = "\t";
static std::string umts_io_spacer = " | ";



inline std::ostream& operator<<(std::ostream &os, const umts_measurement &t)
{
	os << t.cpich_ << umts_io_delimiter
		<< t.ecio_ << umts_io_delimiter
		<< t.rms_signal_ << umts_io_delimiter
		<< t.sample_num_ << umts_io_delimiter
		<< t.time_ << umts_io_delimiter
		<< t.layer_3_.mcc_.to_string() << umts_io_delimiter
		<< t.layer_3_.mnc_.to_string() << umts_io_delimiter
		<< t.layer_3_.lac_ << umts_io_delimiter
		<< t.layer_3_.cid_ << umts_io_delimiter
		<< t.layer_3_.system_frame_number_;

	for(auto &it : t.layer_3_.neighbor_intra_group_)
		os << umts_io_delimiter << it;

	for(auto &it : t.layer_3_.neighbor_inter_group_)
		os << umts_io_delimiter << it.uarfcn_ << umts_io_spacer << it.cpich_;

	for(auto &it : t.layer_3_.neighbor_inter_rat_group_)
		os << umts_io_delimiter << it.arfcn_ << umts_io_spacer << it.bsic_ << umts_io_spacer
			<< (it.band_indicator_ == layer_3_information::dcs_1800_was_used ? "DCS_1800" :
				(it.band_indicator_ == layer_3_information::pcs_1900_was_used ? "PCS_1900" : "UNKNOWN")) 
			<< umts_io_spacer << it.qrx_lev_min_;

	return os;
}

}