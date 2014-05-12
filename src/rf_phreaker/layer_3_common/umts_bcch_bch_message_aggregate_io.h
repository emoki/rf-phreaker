#pragma once 

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate_io.h"

namespace layer_3_information 
{

inline std::ostream& operator<<(std::ostream &os, const umts_bcch_bch_message_aggregate &t)
{
	os << static_cast<const bcch_bch_message_aggregate&>(t) << main_delim
		<< t.system_frame_number_ << main_delim;

	auto size = t.neighbor_intra_group_.size();
	for(const auto &intra : t.neighbor_intra_group_) {
		if(--size)
			os << intra << spacer;
		else
			os << intra << main_delim;
	}

	size = t.neighbor_inter_group_.size();
	for(const auto &inter : t.neighbor_inter_group_) {
		if(--size)
			os << inter.uarfcn_ << spacer2 << inter.cpich_ << spacer;
		else
			os << inter.uarfcn_ << spacer2 << inter.cpich_ << main_delim;
	}

	size = t.neighbor_inter_rat_group_.size();
	for(const auto &rat : t.neighbor_inter_rat_group_) {
		if(--size)
			os << rat.arfcn_ << spacer2 << rat.band_indicator_ << spacer2 << rat.bsic_ << spacer2 << rat.qrx_lev_min_ << spacer;
		else
			os << rat.arfcn_ << spacer2 << rat.band_indicator_ << spacer2 << rat.bsic_ << spacer2 << rat.qrx_lev_min_ << main_delim;
	}

	return os;
}


}