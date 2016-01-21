#pragma once

#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"
#include <vector>

namespace layer_3_information
{

struct lte_sib_base {
public:
	lte_sib_base() : is_decoded_(false) {}
	virtual void clear() = 0;
	bool is_decoded() const { return is_decoded_; }
	bool is_decoded_;
};

enum lte_sib_type {
	SIB_1,
	SIB_2,
	SIB_3,
	SIB_4,
	SIB_5,
	SIB_6,
	SIB_7,
	SIB_8,
	SIB_9,
	SIB_10,
	SIB_11,
	SIB_12_V920,
	SIB_13_V920,
	SIB_14_V1130,
	SIB_15_V1130,
	SIB_16_V1130,
	SPARE_2,
	SPARE_1
};
struct scheduling_info {
	int periodicity_in_frames_;
	std::vector<lte_sib_type> sib_mapping_info_;
};
struct lte_sib1_type : public lte_sib_base {
	void clear() {
		multiple_plmn_.clear();
		tracking_area_code_ = -1;
		cell_id_ = -1;
		scheduling_info_list_.clear();
		si_window_length_ms_ = -1;
	}
	void swap(lte_sib1_type &a) {
		multiple_plmn_.swap(a.multiple_plmn_);
		std::swap(tracking_area_code_, a.tracking_area_code_);
		scheduling_info_list_.swap(a.scheduling_info_list_);
	}
	multiple_plmn_type multiple_plmn_;
	int tracking_area_code_;
	int cell_id_;
	std::vector<scheduling_info> scheduling_info_list_;
	int si_window_length_ms_;
};

// s_non_intra_search_ - Rx level threshold for cell reselection. Value is IE value * 2 {dB]
// Remove the '* 2'.  Let the user do this on their side.
struct reselection_threshold_type {
	reselection_threshold_type() : reselection_threshold_(-1) {}
	reselection_threshold_type(int t) : reselection_threshold_(/*2 * */t) {}
	reselection_threshold_type& operator=(const reselection_threshold_type &t) {
		reselection_threshold_ = t.reselection_threshold_;
		return *this;
	}
	reselection_threshold_type& operator=(int t) {
		reselection_threshold_ = t/* * 2*/;
		return *this;
	}
	void clear() { reselection_threshold_ = -1; }
	int reselection_threshold() const { return reselection_threshold_; }
private:
	int32_t reselection_threshold_;
};
typedef int reselection_threshold_q_type;
struct cell_reselection_serving_freq_info {
	reselection_threshold_type s_non_intra_search_; // reselection_threshold
	reselection_threshold_type threshold_serving_low_; // reselection_threshold
	int cell_reselection_priority_;
};
struct intra_freq_cell_reselection_info {
	reselection_threshold_type s_intra_search_; // reselection_threshold
};
struct s_search_v920 {
	reselection_threshold_type p_; // reselection_threshold
	reselection_threshold_q_type q_; // reselection_threshold_q
};
struct lte_sib3_type : public lte_sib_base {
	void clear() {
		cell_reselection_serving_freq_info_.s_non_intra_search_.clear();
		cell_reselection_serving_freq_info_.threshold_serving_low_.clear();
		cell_reselection_serving_freq_info_.cell_reselection_priority_ = -1;
		intra_freq_cell_reselection_info_.s_intra_search_.clear();
		s_intra_search_v920_.p_.clear();
		s_intra_search_v920_.q_ = -1;
		s_non_intra_search_v920_.p_.clear();
		s_non_intra_search_v920_.q_ = -1;
		threshold_serving_low_q_ = -1;
	}
	void swap(lte_sib3_type &a) {
		std::swap(cell_reselection_serving_freq_info_, a.cell_reselection_serving_freq_info_);
		std::swap(intra_freq_cell_reselection_info_, a.intra_freq_cell_reselection_info_);
		std::swap(s_intra_search_v920_, a.s_intra_search_v920_);
		std::swap(s_non_intra_search_v920_, a.s_non_intra_search_v920_);
		std::swap(threshold_serving_low_q_, a.threshold_serving_low_q_);
	}
	cell_reselection_serving_freq_info cell_reselection_serving_freq_info_;
	intra_freq_cell_reselection_info intra_freq_cell_reselection_info_;
	s_search_v920 s_intra_search_v920_;
	s_search_v920 s_non_intra_search_v920_;
	reselection_threshold_q_type threshold_serving_low_q_; // reselection_threshold_q
};


struct physical_cellid_range {
	int32_t start_;
	int32_t range_;
};
struct neighbor_cell {
	int32_t physical_cell_id_;
	int32_t q_offset_cell_;
};
struct lte_sib4_type : public lte_sib_base {
	void clear() {
		intra_freq_neighbor_cell_list_.clear();
		intra_freq_black_cell_list_.clear();
		csg_physical_cellid_range_.start_ = -1;
		csg_physical_cellid_range_.range_ = -1;
	}
	void swap(lte_sib4_type &a) {
		intra_freq_neighbor_cell_list_.swap(a.intra_freq_neighbor_cell_list_);
		intra_freq_black_cell_list_.swap(a.intra_freq_black_cell_list_);
		std::swap(csg_physical_cellid_range_, a.csg_physical_cellid_range_);
	}
	std::vector<neighbor_cell> intra_freq_neighbor_cell_list_;
	std::vector<physical_cellid_range> intra_freq_black_cell_list_;
	physical_cellid_range csg_physical_cellid_range_;
};


struct inter_freq_carrier_freq_info {
	int32_t downlink_arfcn_value_eutra_;
	int q_rx_lev_min_;
	int32_t q_offset_freq_;
	int allowed_measurement_bandwidth_;
	bool presence_antenna_port_1_;
	reselection_threshold_type threshold_x_high_;
	reselection_threshold_type threshold_x_low_;
	reselection_threshold_q_type threshold_x_high_q_r9_;
	reselection_threshold_q_type threshold_x_low_q_r9_;
	int cell_reselection_priority_;
	std::vector<neighbor_cell> inter_freq_neighbor_cell_list_;
	std::vector<physical_cellid_range> inter_freq_black_cell_list_;
};
struct lte_sib5_type : public lte_sib_base {
	void clear() {
		inter_freq_carrier_info_list_.clear();
	}
	void swap(lte_sib5_type &a) {
		inter_freq_carrier_info_list_.swap(a.inter_freq_carrier_info_list_);
	}
	std::vector<inter_freq_carrier_freq_info> inter_freq_carrier_info_list_;
	// Add multibandinfo
	// Add multibandinfolist_v9e0
	// Add dl-CarrierFreq-v9e0
};


struct carrier_freq_utra {
	int arfcn_value_utra_;
	reselection_threshold_type threshold_x_low_;
	reselection_threshold_type threshold_x_high_;
	reselection_threshold_q_type threshold_x_low_q_r9_;
	reselection_threshold_q_type threshold_x_high_q_r9_;
	int cell_reselection_priority_;
	//int q_rx_lev_min_;
	//int p_max_utra_;
	//int q_qual_min_;
};
struct lte_sib6_type : public lte_sib_base {
	void clear() {
		carrier_freq_list_utra_fdd_.clear();
		carrier_freq_list_utra_tdd_.clear();
	}
	void swap(lte_sib6_type &a) {
		carrier_freq_list_utra_fdd_.swap(a.carrier_freq_list_utra_fdd_);
		carrier_freq_list_utra_tdd_.swap(a.carrier_freq_list_utra_tdd_);
	}
	std::vector<carrier_freq_utra> carrier_freq_list_utra_fdd_;
	std::vector<carrier_freq_utra> carrier_freq_list_utra_tdd_;
};


struct carrier_freqs_geran {
	int starting_arfcn_;
	band_indicator_type band_indicator_;
	std::vector<int32_t> following_arfcns_;
};
struct geran_common_info {
	int cell_reselection_priority_;
	reselection_threshold_type threshold_x_high_;
	reselection_threshold_type threshold_x_low_;
};
struct carrier_freqs_info_geran {
	carrier_freqs_geran carrier_freqs_;
	geran_common_info common_info_;
};
struct lte_sib7_type : public lte_sib_base {
	void clear() {
		carrier_freqs_info_list_geran_.clear();
	}
	void swap(lte_sib7_type &a) {
		carrier_freqs_info_list_geran_.swap(a.carrier_freqs_info_list_geran_);
	}
	std::vector<carrier_freqs_info_geran> carrier_freqs_info_list_geran_;
};


struct neighbor_cells_per_band_class_cdma_2000 {
	int arfcn_value_cmda_2000_;
	std::vector<int32_t> physical_cell_ids_;
};
enum band_class_cmda_2000 {
	bc0,
	bc1,
	bc2,
	bc3,
	bc4,
	bc5,
	bc6,
	bc7,
	bc8,
	bc9,
	bc10,
	bc11,
	bc12,
	bc13,
	bc14,
	bc15,
	bc16,
	bc17,
	bc18_v9a0,
	bc19_v9a0,
	bc20_v9a0,
	bc21_v9a0,
	spare10,
	spare9,
	spare8,
	spare7,
	spare6,
	spare5,
	spare4,
	spare3,
	spare2,
	spare1
};
struct neighbor_cell_cdma_2000 {
	band_class_cmda_2000 band_;
	std::vector<neighbor_cells_per_band_class_cdma_2000> neighbor_cells_per_freq_list_;
};
struct cell_reselection_parameters_cmda_2000 {
	std::vector<neighbor_cell_cdma_2000> neighbor_cell_list_;
};
struct lte_sib8_type : public lte_sib_base {
	void clear() {
		parameters_hrpd_.neighbor_cell_list_.clear();
		parameters_1xrtt_.neighbor_cell_list_.clear();
	}
	void swap(lte_sib8_type &a) {
		parameters_hrpd_.neighbor_cell_list_.swap(a.parameters_hrpd_.neighbor_cell_list_);
		parameters_1xrtt_.neighbor_cell_list_.swap(a.parameters_1xrtt_.neighbor_cell_list_);
	}
	cell_reselection_parameters_cmda_2000 parameters_hrpd_;
	cell_reselection_parameters_cmda_2000 parameters_1xrtt_;
};

class lte_rrc_message_aggregate : public bcch_bch_message_aggregate {
public:
	lte_rrc_message_aggregate();
	void clear() {
		bcch_bch_message_aggregate::clear();
		sib1_.clear();
		sib3_.clear();
		sib4_.clear();
		sib5_.clear();
		sib6_.clear();
		sib7_.clear();
		sib8_.clear();
	}

	void swap(lte_rrc_message_aggregate &a) {
		bcch_bch_message_aggregate::swap(a);
		sib1_.swap(a.sib1_);
		sib3_.swap(a.sib3_);
		sib4_.swap(a.sib4_);
		sib5_.swap(a.sib5_);
		sib6_.swap(a.sib6_);
		sib7_.swap(a.sib7_);
		sib8_.swap(a.sib8_);
	}

	bool is_decoded(lte_sib_type sib_type) {
		switch(sib_type) {
		case SIB_1:
			return sib1_.is_decoded();
		case SIB_3:
			return sib3_.is_decoded();
		case SIB_4:
			return sib4_.is_decoded();
		case SIB_5:
			return sib5_.is_decoded();
		case SIB_6:
			return sib6_.is_decoded();
		case SIB_7:
			return sib7_.is_decoded();
		case SIB_8:
			return sib8_.is_decoded();
		default:
			return false;
		}
	}

	lte_sib1_type sib1_;
	lte_sib3_type sib3_;
	lte_sib4_type sib4_;
	lte_sib5_type sib5_;
	lte_sib6_type sib6_;
	lte_sib7_type sib7_;
	lte_sib8_type sib8_;
};


}