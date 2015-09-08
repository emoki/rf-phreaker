#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate_io.h"

namespace layer_3_information {

inline std::ostream& header(std::ostream &os, const gsm_si_base &t);
inline std::ostream& header(std::ostream &os, const gsm_si_1 &t);
inline std::ostream& header(std::ostream &os, const gsm_si_2 &t);
inline std::ostream& header(std::ostream &os, const gsm_si_2bis &t);
inline std::ostream& header(std::ostream &os, const gsm_si_2ter &t);
inline std::ostream& header(std::ostream &os, const gsm_si_2quater &t);
inline std::ostream& header(std::ostream &os, const gsm_si_3 &t);
inline std::ostream& header(std::ostream &os, const gsm_si_4 &t);
inline std::ostream& header(std::ostream &os, const gsm_si_7 &t);
inline std::ostream& header(std::ostream &os, const gsm_si_8 &t);

inline std::ostream& operator<<(std::ostream &os, const gsm_si_base &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_1 &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2 &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2bis &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2ter &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2quater &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_3 &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_4 &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_7 &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_si_8 &t);
inline std::ostream& operator<<(std::ostream &os, const gsm_layer_3_message_aggregate &t);

inline std::ostream& header(std::ostream &os, const gsm_si_base &t) {
	os << "is_decoded";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_base &t) {
	os << (t.is_decoded() ? "YES" : "NO");
	return os;
}

inline std::ostream& output_empty_gsm_si_1(std::ostream &os) {
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_1 &t) {
	os << "si_1_band_indicator";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_1 &t) {
	switch(t.band_indicator_) {
	case dcs_1800_was_used:
		os << "dcs_1800_was_used";
		break;
	case pcs_1900_was_used:
		os << "pcs_1900_was_used";
		break;
	case unknown_band_was_used:
	default:
		os << "unknown_band";
	}
	return os;
}


inline std::ostream& output_empty_gsm_si_2(std::ostream &os) {
	for(int i = 0; i < 2; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_2 &t) {
	os	<< "si_2_ba_ind" << main_delim
		<< "si_2_ext_ind" << main_delim
		<< "si_2_bcch_neighbor_cells [bcch]";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2 &t) {
	os << t.gsm_ba_ind_ << main_delim
		<< t.bcch_neighbors_has_extension_ << main_delim;
	os << begin_delim;
	for(auto &i : t.bcch_neighbors_)
		os << i << spacer;
	os << end_delim;
	return os;
}


inline std::ostream& output_empty_gsm_si_2bis(std::ostream &os) {
	for(int i = 0; i < 4; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_2bis &t) {
	os 	<< "si_2bis_ba_ind" << main_delim
		<< "si_2bis_ext_ind" << main_delim
		<< "si_2bis_extended_bcch_neighbor_cells [bcch]" << main_delim
		<< "si_2bis_rest_octet_index" << main_delim
		<< "si_2bis_rest_octet_count";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2bis &t) {
	os << t.gsm_ba_ind_ << main_delim
		<< t.bcch_neighbors_has_extension_ << main_delim;
	os << begin_delim;
	for(auto &i : t.extended_bcch_neighbors_)
		os << i << spacer;
	os << end_delim << main_delim;
	os << t.rest_octet_index_ << main_delim;
	os << t.rest_octet_count_;
	return os;
}


inline std::ostream& output_empty_gsm_si_2ter(std::ostream &os) {
	for(int i = 0; i < 5; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_2ter &t) {
	os 	<< "si_2ter_bcch_neighbors_ba_ind" << main_delim
		<< "si_2ter_bcch_neighbors_multiband_reporting" << main_delim
		<< "si_2ter_extended_bcch_neighbor_cells [bcch]" << main_delim
		<< "si_2ter_rest_octet_index" << main_delim
		<< "si_2ter_rest_octet_count" << main_delim
		<< "si_2ter_utran_neighbors [uarfcn : duplex : bandwidth]";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const duplex_type &t) {
	t == fdd ? (os << "fdd") : (os << "tdd");
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const utran_bandwidth_type&t) {
	switch(t) {
	case utran_3_84_mcps:
		os << "3.84mcps";
	break; 
	case utran_1_24_mcps:
		os << "1.24mcps";
	break; 
	case utran_2_mcps:
		os << "2mcps";
	break;
	case utran_3_mcps:
		os << "3mcps";
	break;
	case utran_4_mcps:
		os << "4mcps";
	break;
	case utran_5_mcps:
		os << "5mcps";
	break;
	case utran_6_mcps:
		os << "6mcps";
	break;
	case utran_7_mcps:
		os << "7mcps";
	break;
	default:
		os << "unknown";
	}
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2ter &t) {
	os << t.gsm_ba_ind_ << main_delim
		<< t.bcch_neighbors_multiband_reporting_ << main_delim;
	os << begin_delim;
	for(auto &i : t.extended_bcch_neighbors_)
		os << i << spacer;
	os << end_delim << main_delim;
	os << t.rest_octet_index_ << main_delim;
	os << t.rest_octet_count_ << main_delim;
	os << begin_delim;
	for(auto &i : t.utran_neighbors_) {
		os << i.arfcn_ << spacer2 << i.duplexing_ << spacer2 << i.bandwidth_ << spacer;
		os << begin_delim;
		for(auto &j : i.scrambling_codes_)
			os << j << spacer;
		os << end_delim;
	}
	os << end_delim;
	return os;
}


inline std::ostream& output_empty_gsm_si_2quater(std::ostream &os) {
	for(int i = 0; i < 8; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_2quater &t) {
	os << "si_2quater_ba_ind" << main_delim
		<< "si_2quater_3g_ind" << main_delim
		<< "si_2quater_rest_octet_index" << main_delim
		<< "si_2quater_rest_octet_count" << main_delim
		<< "si_2quater_utran_neighbor_cell_start_index" << main_delim
		<< "si_2quater_utran_neighbor_cell_absolute_start_emr" << main_delim
		<< "si_2quater_utran_neighbors [uarfcn : duplex : bandwidth : [scrambling_codes]]" << main_delim
		<< "si_2quater_eutran_neighbors [earfcn : bandwidth : priority : threshold_high : threshold_low : qrxlevmin : [allowed_pcids] [not_allowed_pcids] [same_tracking_area groups][different_tracking_area_groups]]" << main_delim
		<< "si_2quater_extended_eutran_nieghbors [earfcn]";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const eutran_bandwidth_type &t) {
	switch(t) {
	case num_resource_blocks_6:
		os << "num_resource_blocks_6";
		break; 
	case num_resource_blocks_15:
		os << "num_resource_blocks_15";
		break;
	case num_resource_blocks_25:
		os << "num_resource_blocks_25";
		break;
	case num_resource_blocks_50:
		os << "num_resource_blocks_50";
		break;
	case num_resource_blocks_75:
		os << "num_resource_blocks_75";
		break;
	case num_resource_blocks_100:
		os << "num_resource_blocks_100";
	default:;
	}
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_2quater &t) {
	os << t.gsm_ba_ind_ << main_delim
		<< t.p3g_ba_ind_ << main_delim
		<< t.rest_octet_index_ << main_delim
		<< t.rest_octet_count_ << main_delim
		<< t.utran_neighbor_cell_index_start_3g_ << main_delim
		<< t.utran_neighbor_cell_absolute_index_start_emr_ << main_delim;
	os << begin_delim;
	for(auto &i : t.utran_neighbors_) {
		os << i.arfcn_ << spacer2 << i.duplexing_ << spacer2 << i.bandwidth_ << spacer;
		os << begin_delim;
		for(auto &j : i.scrambling_codes_)
			os << j << spacer;
		os << end_delim;
	}
	os << end_delim;
	os << main_delim;
	os << begin_delim;
	for(auto &i : t.eutran_neighbors_) {
		os << i.earfcn_ << spacer2 << i.bandwidth_ << spacer2 << i.priority_ << spacer2
			<< i.threshold_high_ << spacer2 << i.threshold_low_ << spacer2 << i.qrxlevmin_ << spacer;
		os << begin_delim;
		for(auto &j : i.pcids_allowed_)
			os << j << spacer;
		os << end_delim;
		os << begin_delim;
		for(auto &j : i.pcids_not_allowed_)
			os << j << spacer;
		os << end_delim;
		os << begin_delim;
		for(auto &j : i.pcids_same_tracking_area_) {
			os << begin_delim;
			for(auto &k : j)
				os << k << spacer;
			os << end_delim;
		}
		os << end_delim;
		os << begin_delim;
		for(auto &j : i.pcids_different_tracking_area_) {
			os << begin_delim;
			for(auto &k : j)
				os << k << spacer;
			os << end_delim;
		}
		os << end_delim;
	}
	os << end_delim << main_delim;
	os << begin_delim;
	for(auto &i : t.extended_eutran_neighbors_)
		os << i << spacer;
	os << end_delim;
	return os;
}


inline std::ostream& output_empty_gsm_si_3(std::ostream &os) {
	for(int i = 0; i < 11; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_3 &t) {
	os << "si_3_mcc" << main_delim
		<< "si_3_mnc" << main_delim
		<< "si_3_lac" << main_delim
		<< "si_3_cid" << main_delim
		<< "si_3_cell_reselect_hysteresis_db" << main_delim
		<< "si_3_cbq" << main_delim
		<< "si_3_cell_reselect_offset" << main_delim
		<< "si_3_temporary_offset" << main_delim
		<< "si_3_penalty_offset" << main_delim
		<< "si_3_is_2ter_present" << main_delim
		<< "si_3_is_2quater_present" << main_delim
		<< "si_3_bs_ag_blks_res";
		return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_3 &t) {
	os << t.plmn_.mcc_ << main_delim
		<< t.plmn_.mnc_ << main_delim
		<< t.location_area_code_ << main_delim
		<< t.cell_id_ << main_delim
		<< t.cell_reselect_hysteresis_db_ << main_delim
		<< t.selection_parameters_.cbq_ << main_delim
		<< t.selection_parameters_.cell_reselect_offset_ << main_delim
		<< t.selection_parameters_.temporary_offset_ << main_delim
		<< t.selection_parameters_.penalty_time_ << main_delim
		<< t.is_2ter_present_ << main_delim
		<< t.is_2quater_present_ << main_delim
		<< t.bs_ag_blks_res_;
	return os;
}


inline std::ostream& output_empty_gsm_si_4(std::ostream &os) {
	for(int i = 0; i < 10; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_4 &t) {
	os << "si_4_mcc" << main_delim
		<< "si_4_mnc" << main_delim
		<< "si_4_lac" << main_delim
		<< "si_4_cid" << main_delim
		<< "si_4_cell_reselect_hysteresis_db" << main_delim
		<< "si_4_cbq" << main_delim
		<< "si_4_cell_reselect_offset" << main_delim
		<< "si_4_temporary_offset" << main_delim
		<< "si_4_penalty_offset" << main_delim
		<< "is_cbch_present" << main_delim
		<< "have_additional_si7_si8_param";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_4 &t) {
	os << t.plmn_.mcc_ << main_delim
		<< t.plmn_.mnc_ << main_delim
		<< t.location_area_code_ << main_delim
		<< t.cell_id_ << main_delim
		<< t.cell_reselect_hysteresis_db_ << main_delim
		<< t.selection_parameters_.cbq_ << main_delim
		<< t.selection_parameters_.cell_reselect_offset_ << main_delim
		<< t.selection_parameters_.temporary_offset_ << main_delim
		<< t.selection_parameters_.penalty_time_ << main_delim
		<< t.is_cbch_present_ << main_delim
		<< t.have_additional_param_in_si7_si8_;
	return os;
}


inline std::ostream& output_empty_gsm_si_7(std::ostream &os) {
	for(int i = 0; i < 6; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_7 &t) {
	os << "si_7_mcc" << main_delim
		<< "si_7_mnc" << main_delim
		<< "si_7_cid" << main_delim
		<< "si_7_cbq" << main_delim
		<< "si_7_cell_reselect_offset" << main_delim
		<< "si_7_temporary_offset" << main_delim
		<< "si_7_penalty_offset";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_7 &t) {
	os << t.plmn_.mcc_ << main_delim
		<< t.plmn_.mnc_ << main_delim
		<< t.cell_id_ << main_delim
		<< t.selection_parameters_.cbq_ << main_delim
		<< t.selection_parameters_.cell_reselect_offset_ << main_delim
		<< t.selection_parameters_.temporary_offset_ << main_delim
		<< t.selection_parameters_.penalty_time_;
	return os;
}


inline std::ostream& output_empty_gsm_si_8(std::ostream &os) {
	for(int i = 0; i < 6; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const gsm_si_8 &t) {
	os << "si_8_mcc" << main_delim
		<< "si_8_mnc" << main_delim
		<< "si_8_cid" << main_delim
		<< "si_8_cbq" << main_delim
		<< "si_8_cell_reselect_offset" << main_delim
		<< "si_8_temporary_offset" << main_delim
		<< "si_8_penalty_offset";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const gsm_si_8 &t) {
	os << t.plmn_.mcc_ << main_delim
		<< t.plmn_.mnc_ << main_delim
		<< t.cell_id_ << main_delim
		<< t.selection_parameters_.cbq_ << main_delim
		<< t.selection_parameters_.cell_reselect_offset_ << main_delim
		<< t.selection_parameters_.temporary_offset_ << main_delim
		<< t.selection_parameters_.penalty_time_;
	return os;
}


inline std::ostream& header(std::ostream &os, const gsm_layer_3_message_aggregate &t) {
	header(os, t.si_1_) << main_delim;
	header(os, t.si_2_) << main_delim;
	header(os, t.si_2bis_) << main_delim;
	header(os, t.si_2ter_) << main_delim;
	header(os, t.si_2quater_) << main_delim;
	header(os, t.si_3_) << main_delim;
	header(os, t.si_4_) << main_delim;
	header(os, t.si_7_) << main_delim;
	header(os, t.si_8_);
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const gsm_layer_3_message_aggregate &t) {
	if(t.si_1_.is_decoded())
		os << t.si_1_ << main_delim;
	else
		output_empty_gsm_si_1(os) << main_delim;
	if(t.si_2_.is_decoded())
		os << t.si_2_ << main_delim;
	else
		output_empty_gsm_si_2(os) << main_delim;
	if(t.si_2bis_.is_decoded())
		os << t.si_2bis_ << main_delim;
	else
		output_empty_gsm_si_2bis(os) << main_delim;
	if(t.si_2ter_.is_decoded())
		os << t.si_2ter_ << main_delim;
	else
		output_empty_gsm_si_2ter(os) << main_delim;
	if(t.si_2quater_.is_decoded())
		os << t.si_2quater_ << main_delim;
	else
		output_empty_gsm_si_2quater(os) << main_delim;
	if(t.si_3_.is_decoded())
		os << t.si_3_ << main_delim;
	else
		output_empty_gsm_si_3(os) << main_delim;
	if(t.si_4_.is_decoded())
		os << t.si_4_ << main_delim;
	else
		output_empty_gsm_si_4(os) << main_delim;
	if(t.si_7_.is_decoded())
		os << t.si_7_ << main_delim;
	else
		output_empty_gsm_si_7(os) << main_delim;
	if(t.si_8_.is_decoded())
		os << t.si_8_;
	else
		output_empty_gsm_si_8(os) << main_delim;
	return os;
}


}