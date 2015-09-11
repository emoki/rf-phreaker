#pragma once

#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"
#include <vector>

namespace layer_3_information {

// placeholder
enum gsm_bcch_si_type
{
	SI_1,
	SI_2,
	SI_2BIS,
	SI_2TER,
	SI_2QUATER,
	SI_3,
	SI_4,
	SI_7,
	SI_8,
	SI_23
};

typedef int32_t bcch_neighbor;

struct gsm_si_base {
	gsm_si_base() : is_decoded_(false) {}
	virtual void clear() {
		is_decoded_ = false;
	}
	void swap(gsm_si_base &si) {
		std::swap(is_decoded_, si.is_decoded_);
	}

	bool is_decoded() const { return is_decoded_; }
	bool is_decoded_;
};

struct gsm_si_1 : public gsm_si_base {
	virtual void clear() {
		gsm_si_base::clear();
		band_indicator_ = unknown_band_was_used;
	}
	void swap(gsm_si_1 &si) {
		gsm_si_base::swap(si);
		std::swap(band_indicator_, si.band_indicator_);
	}
	band_indicator band_indicator_;
};

struct gsm_si_2 : public gsm_si_base {
	virtual void clear() {
		gsm_si_base::clear();
		bcch_neighbors_.clear();
		bcch_neighbors_has_extension_ = false;
		gsm_ba_ind_ = -1;
	}
	void swap(gsm_si_2 &si) {
		gsm_si_base::swap(si);
		std::swap(bcch_neighbors_, si.bcch_neighbors_);
		std::swap(gsm_ba_ind_, si.gsm_ba_ind_);
		std::swap(bcch_neighbors_has_extension_, si.bcch_neighbors_has_extension_);
	}
	std::vector<bcch_neighbor> bcch_neighbors_;
	bool bcch_neighbors_has_extension_;
	int32_t gsm_ba_ind_;
};

struct gsm_si_2bis : public gsm_si_base {
	virtual void clear() {
		gsm_si_base::clear();
		extended_bcch_neighbors_.clear();
		rest_octet_index_ = -1;
		rest_octet_count_ = -1;
		bcch_neighbors_has_extension_ = false;
		gsm_ba_ind_ = -1;
	}
	void swap(gsm_si_2bis &si) {
		gsm_si_base::swap(si);
		std::swap(rest_octet_index_, si.rest_octet_index_);
		std::swap(rest_octet_count_, si.rest_octet_count_);
		std::swap(extended_bcch_neighbors_, si.extended_bcch_neighbors_);
		std::swap(gsm_ba_ind_, si.gsm_ba_ind_);
		std::swap(bcch_neighbors_has_extension_, si.bcch_neighbors_has_extension_);
	}
	std::vector<bcch_neighbor> extended_bcch_neighbors_;
	bool bcch_neighbors_has_extension_;
	int32_t gsm_ba_ind_;
	int32_t rest_octet_index_;
	int32_t rest_octet_count_;
};

enum duplex_type {
	fdd,
	tdd
};

enum utran_bandwidth_type {
	utran_3_84_mcps, // 0x000 bit pattern
	utran_1_24_mcps, // 0x001 bit pattern
	utran_2_mcps, 
	utran_3_mcps,
	utran_4_mcps,
	utran_5_mcps,
	utran_6_mcps,
	utran_7_mcps,
	utran_default_mcps = utran_3_84_mcps
};

struct utran_neighbor {
	duplex_type duplexing_;
	int32_t arfcn_;
	utran_bandwidth_type bandwidth_;
	std::vector<int32_t> scrambling_codes_;
};

struct gsm_si_2ter : public gsm_si_base {
	virtual void clear() { 
		gsm_si_base::clear();
		extended_bcch_neighbors_.clear();
		utran_neighbors_.clear();
		rest_octet_index_ = -1;
		rest_octet_count_ = -1;
		gsm_ba_ind_ = -1;
		bcch_neighbors_multiband_reporting_ = -1;
	}
	void swap(gsm_si_2ter &si) {
		gsm_si_base::swap(si);
		std::swap(rest_octet_index_, si.rest_octet_index_);
		std::swap(rest_octet_count_, si.rest_octet_count_);
		std::swap(gsm_ba_ind_, si.gsm_ba_ind_);
		std::swap(bcch_neighbors_multiband_reporting_, si.bcch_neighbors_multiband_reporting_);
		std::swap(extended_bcch_neighbors_, si.extended_bcch_neighbors_);
		std::swap(utran_neighbors_, si.utran_neighbors_);
	}
	std::vector<bcch_neighbor> extended_bcch_neighbors_;
	int32_t gsm_ba_ind_;
	int32_t bcch_neighbors_multiband_reporting_;
	std::vector<utran_neighbor> utran_neighbors_;
	int32_t rest_octet_index_;
	int32_t rest_octet_count_;
};

enum eutran_bandwidth_type {
	num_resource_blocks_6, // 000 bit pattern
	num_resource_blocks_15, // 001 bit pattern
	num_resource_blocks_25, // 010 bit pattern
	num_resource_blocks_50, // 011 bit pattern
	num_resource_blocks_75, // 100 bit pattern
	num_resource_blocks_100 // 101 bit pattern
	// All other reserved, if other bit pattern encountered use num_resource_blocks_100.
};

//struct utran_neighbor_quater : public utran_neighbor {
//	int32_t 
//};

struct eutran_neighbor {
	int32_t earfcn_;
	eutran_bandwidth_type bandwidth_;
	int32_t priority_;
	int32_t threshold_high_db_; // actual range 0-31 (0, 2, 4, 6,...,62db)
	int32_t threshold_low_db_; // if not present, it takes the same value as high_;
	int32_t qrxlevmin_db_; // actual range = 0-31 (-140, -138,..., -78db)) 
	std::vector<int32_t> pcids_allowed_;
	std::vector<int32_t> pcids_not_allowed_;
	std::vector<std::vector<int32_t>> pcids_same_tracking_area_;
	std::vector<std::vector<int32_t>> pcids_different_tracking_area_;
};

struct gsm_si_2quater : public gsm_si_base {
	virtual void clear() { 
		gsm_si_base::clear();
		utran_neighbors_.clear();
		eutran_neighbors_.clear();
		rest_octet_index_ = -1;
		rest_octet_count_ = -1;
		gsm_ba_ind_ = -1;
		p3g_ba_ind_ = -1;
		utran_neighbor_cell_index_start_3g_ = -1;
		utran_neighbor_cell_absolute_index_start_emr_ = -1;
	}
	void swap(gsm_si_2quater &si) {
		gsm_si_base::swap(si);
		std::swap(rest_octet_index_, si.rest_octet_index_);
		std::swap(rest_octet_count_, si.rest_octet_count_);
		std::swap(gsm_ba_ind_, si.gsm_ba_ind_);
		std::swap(p3g_ba_ind_, si.p3g_ba_ind_);
		std::swap(utran_neighbor_cell_index_start_3g_, si.utran_neighbor_cell_index_start_3g_);
		std::swap(utran_neighbor_cell_absolute_index_start_emr_, si.utran_neighbor_cell_absolute_index_start_emr_);
		std::swap(utran_neighbors_, si.utran_neighbors_);
		std::swap(eutran_neighbors_, si.eutran_neighbors_);
		std::swap(extended_eutran_neighbors_, si.extended_eutran_neighbors_);
	}
	int32_t gsm_ba_ind_;
	int32_t p3g_ba_ind_;
	int32_t utran_neighbor_cell_index_start_3g_;
	int32_t utran_neighbor_cell_absolute_index_start_emr_;
	std::vector<utran_neighbor> utran_neighbors_;
	std::vector<eutran_neighbor> eutran_neighbors_;
	std::vector<int32_t> extended_eutran_neighbors_;
	int32_t rest_octet_index_;
	int32_t rest_octet_count_;
	// Extended eutran earfcns replace the same indexed etran neighbor's earfcn (which would have a value of 65535).
};

struct gsm_si_2n : public gsm_si_base {
	virtual void clear() {
		rest_octet_index_ = -1;
		rest_octet_count_ = -1;
	}
	void swap(gsm_si_2n &si) {
		gsm_si_base::swap(si);
		std::swap(rest_octet_index_, si.rest_octet_index_);
		std::swap(rest_octet_count_, si.rest_octet_count_);
	}
	int32_t rest_octet_index_;
	int32_t rest_octet_count_;
	// Do not currently populate.  I think this corresponds to details of the gsm neighbor list (indexed against sib1 list).
};

struct selection_parameters {
	int32_t cbq_;
	int32_t cell_reselect_offset_db_; // actual range = 0-63 (0, 2, 4,...,126db)
	int32_t temporary_offset_db_; // actual range = 0-7 (0, 10, 20,...,60db, infinity)
	int32_t penalty_time_seconds_; // actual range = 0-31 (20, 40, 60,...,620 seconds)
	bool subtract_reselect_cell_offset_ignore_temp_offset_;
	bool apply_infinity_offset_;
	void clear() {
		cbq_ = -1;
		cell_reselect_offset_db_ = -1;
		temporary_offset_db_ = -1;
		penalty_time_seconds_ = -1;
		subtract_reselect_cell_offset_ignore_temp_offset_ = false;
		apply_infinity_offset_ = false;
	}
};

//struct cell_reselect_hysteresis_db {
//	/*Bits
//	8 7 6
//	0 0 0  0 dB RXLEV hysteresis for LA re - selection
//	0 0 1  2 dB RXLEV hysteresis for LA re - selection
//	0 1 0  4 dB RXLEV hysteresis for LA re - selection
//	0 1 1  6 dB RXLEV hysteresis for LA re - selection
//	1 0 0  8 dB RXLEV hysteresis for LA re - selection
//	1 0 1  10 dB RXLEV hysteresis for LA re - selection
//	1 1 0  12 dB RXLEV hysteresis for LA re - selection
//	1 1 1  14 dB RXLEV hysteresis for LA re - selection
//	*/
//	cell_reselect_hysteresis_db() { clear(); }
//	cell_reselect_hysteresis_db(int32_t encoded_hystersis) {
//		cell_reselect_hysteresis_db_ *= 2;
//	}
//	cell_reselect_hysteresis_db(cell_reselect_hysteresis_db &a) {
//		cell_reselect_hysteresis_db_ = a.cell_reselect_hysteresis_db_;
//	}
//	void clear() { cell_reselect_hysteresis_db_ = -1; }
//	int32_t cell_reselect_hysteresis_db_;
//};
typedef int32_t cell_reselect_hyseresis_db_type;

struct gsm_si_3 : public gsm_si_base {
	gsm_si_3() { clear(); }
	virtual void clear() {
		gsm_si_base::clear();
		plmn_.mcc_ = {};
		plmn_.mnc_ = {};
		location_area_code_ = -1;
		cell_id_ = -1;
		cell_reselect_hysteresis_db_ = -1;
		selection_parameters_.clear();
		is_2quater_present_ = false;
		is_2ter_present_ = false;
		bs_ag_blks_res_ = -1;
	}
	void swap(gsm_si_3 &si) {
		gsm_si_base::swap(si);
		plmn_.mcc_.swap(si.plmn_.mcc_);
		plmn_.mnc_.swap(si.plmn_.mnc_);
		std::swap(location_area_code_, si.location_area_code_);
		std::swap(cell_id_, si.cell_id_);
		std::swap(cell_reselect_hysteresis_db_, si.cell_reselect_hysteresis_db_);
		std::swap(selection_parameters_, si.selection_parameters_);
		std::swap(is_2ter_present_, si.is_2ter_present_);
		std::swap(is_2quater_present_, si.is_2quater_present_);
		std::swap(bs_ag_blks_res_, si.bs_ag_blks_res_);
	}
	plmn plmn_;
	int32_t location_area_code_;
	int32_t cell_id_;
	cell_reselect_hyseresis_db_type cell_reselect_hysteresis_db_;
	selection_parameters selection_parameters_;
	int32_t bs_ag_blks_res_;
	bool is_2ter_present_;
	bool is_2quater_present_;
};

struct gsm_si_4 : public gsm_si_base {
	gsm_si_4() { clear(); }
	virtual void clear() {
		gsm_si_base::clear();
		plmn_.mcc_ = {};
		plmn_.mnc_ = {};
		location_area_code_ = -1;
		cell_id_ = -1;
		cell_reselect_hysteresis_db_ = -1;
		selection_parameters_.clear();
		is_cbch_present_ = false;
		have_additional_param_in_si7_si8_ = false;
	}
	void swap(gsm_si_4 &si) {
		gsm_si_base::swap(si);
		plmn_.mcc_.swap(si.plmn_.mcc_);
		plmn_.mnc_.swap(si.plmn_.mnc_);
		std::swap(location_area_code_, si.location_area_code_);
		std::swap(cell_id_, si.cell_id_);
		std::swap(cell_reselect_hysteresis_db_, si.cell_reselect_hysteresis_db_);
		std::swap(selection_parameters_, si.selection_parameters_);
		std::swap(is_cbch_present_, si.is_cbch_present_);
		std::swap(have_additional_param_in_si7_si8_, si.have_additional_param_in_si7_si8_);
	}
	plmn plmn_;
	int32_t location_area_code_;
	int32_t cell_id_;
	cell_reselect_hyseresis_db_type cell_reselect_hysteresis_db_;
	selection_parameters selection_parameters_;
	bool is_cbch_present_;
	bool have_additional_param_in_si7_si8_;
};

struct gsm_si_7 : public gsm_si_base {
	gsm_si_7() { clear(); }
	virtual void clear() {
		gsm_si_base::clear();
		plmn_.mcc_ = {};
		plmn_.mnc_ = {};
		cell_id_ = -1;
		selection_parameters_.clear();
	}
	void swap(gsm_si_7 &si) {
		gsm_si_base::swap(si);
		std::swap(selection_parameters_, si.selection_parameters_);
		plmn_.mcc_.swap(si.plmn_.mcc_);
		plmn_.mnc_.swap(si.plmn_.mnc_);
		std::swap(cell_id_, si.cell_id_);
	}
	selection_parameters selection_parameters_;
	plmn plmn_;
	int32_t cell_id_;
};

struct gsm_si_8 : public gsm_si_base {
	gsm_si_8() { clear(); }
	virtual void clear() {
		gsm_si_base::clear();
		plmn_.mcc_ = {};
		plmn_.mnc_ = {};
		cell_id_ = -1;
		selection_parameters_.clear();
	}
	void swap(gsm_si_8 &si) {
		gsm_si_base::swap(si);
		std::swap(selection_parameters_, si.selection_parameters_);
		plmn_.mcc_.swap(si.plmn_.mcc_);
		plmn_.mnc_.swap(si.plmn_.mnc_);
		std::swap(cell_id_, si.cell_id_);
	}
	selection_parameters selection_parameters_;
	plmn plmn_;
	int32_t cell_id_;
};

struct gsm_si_23 : public gsm_si_base {
	gsm_si_23() { clear(); }
	virtual void clear() {
		gsm_si_base::clear();
	}
	void swap(gsm_si_23 &si) {
		gsm_si_base::swap(si);
	}
};

class gsm_layer_3_message_aggregate : public bcch_bch_message_aggregate
{
public:
	gsm_layer_3_message_aggregate();
	
	void clear() {
		si_1_.clear();
		si_2_.clear();
		si_2bis_.clear();
		si_2ter_.clear();
		si_2quater_.clear();
		si_3_.clear();
		si_4_.clear();
		si_7_.clear();
		si_8_.clear();
		si_23_.clear();
	}

	void swap(gsm_layer_3_message_aggregate &a) {
		bcch_bch_message_aggregate::swap(a);
		si_1_.swap(a.si_1_);
		si_2_.swap(a.si_2_);
		si_2bis_.swap(a.si_2bis_);
		si_2ter_.swap(a.si_2ter_);
		si_2quater_.swap(a.si_2quater_);
		si_3_.swap(a.si_3_);
		si_4_.swap(a.si_4_);
		si_7_.swap(a.si_7_);
		si_8_.swap(a.si_8_);
		si_23_.swap(a.si_23_);
	}

	gsm_si_1 si_1_;
	gsm_si_2 si_2_;
	gsm_si_2bis si_2bis_;
	gsm_si_2ter si_2ter_;
	gsm_si_2quater si_2quater_;
	gsm_si_3 si_3_;
	gsm_si_4 si_4_;
	gsm_si_7 si_7_;
	gsm_si_8 si_8_;
	gsm_si_23 si_23_;
};


};

