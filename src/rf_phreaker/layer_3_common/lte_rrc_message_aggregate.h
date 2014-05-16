#pragma once

#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"
#include <vector>

namespace layer_3_information
{

class lte_sib_base 
{
public:
	lte_sib_base() : decoded_(false) {}
	virtual void clear() = 0;
	bool decoded_;
};

enum lte_sib_type
{
	sib_3,
	sib_4,
	sib_5,
	sib_6,
	sib_7,
	sib_8,
	sib_9,
	sib_10,
	sib_11,
	sib_12_v920,
	sib_13_v920,
	sib_14_v1130,
	sib_15_v1130,
	sib_16_v1130,
	spare_2,
	spare_1
};
struct scheduling_info
{
	int periodicity_in_frames_;
	std::vector<lte_sib_type> sib_mapping_info_;
};
struct lte_sib1_type : public lte_sib_base
{
	void clear()
	{
		multiple_plmn_.clear();
		tracking_area_code_ = -1;
		cell_id_ = -1;
		scheduling_info_list_.clear();
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
};


struct physical_cellid_range
{
	int32_t start_;
	int32_t range_;
};
struct neighbor_cell 
{
	int32_t physical_cell_id_;
	int32_t q_offset_cell_;
};
struct lte_sib4_type : public lte_sib_base
{
	void clear()
	{
		intra_freq_neighbor_cell_list_.clear();
		intra_freq_black_cell_list_.clear();
		csg_physical_cellid_range_.start_ = -1;
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


struct inter_freq_carrier_freq_info
{
	int32_t downlink_arfcn_value_eutra_;
	int q_rx_lev_min_;
	int32_t q_offset_cell_;
	int allowed_measurement_bandwidth_;
	bool presence_antenna_port_1_;
	std::vector<neighbor_cell> inter_freq_neighbor_cell_list_;
	std::vector<physical_cellid_range> inter_freq_black_cell_list_;
};
struct lte_sib5_type : public lte_sib_base
{
	void clear()
	{
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


struct carrier_freq_utra
{
	int arfcn_value_utra_;
	//int q_rx_lev_min_;
	//int p_max_utra_;
	//int q_qual_min_;
};
struct lte_sib6_type : public lte_sib_base
{
	void clear()
	{
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


struct carrier_freqs_geran 
{
	int starting_arfcn_;
	band_indicator band_indicator_;
	std::vector<int32_t> following_arfcns_;
};
struct carrier_freqs_info_geran
{
	carrier_freqs_geran carrier_freqs_;
	// skip common_info.
};
struct lte_sib7_type : public lte_sib_base
{
	void clear()
	{
		carrier_freqs_info_list_geran_.clear();
	}
	void swap(lte_sib7_type &a) {
		carrier_freqs_info_list_geran_.swap(a.carrier_freqs_info_list_geran_);
	}
	std::vector<carrier_freqs_info_geran> carrier_freqs_info_list_geran_;
};


struct neighbor_cells_per_band_class_cdma_2000
{
	int arfcn_value_cmda_2000_;
	std::vector<int32_t> physical_cell_ids_;
};
enum band_class_cmda_2000
{
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
struct neighbor_cell_cdma_2000
{
	band_class_cmda_2000 band_;
	std::vector<neighbor_cells_per_band_class_cdma_2000> neighbor_cells_per_freq_list_;
};
struct cell_reselection_parameters_cmda_2000
{
	std::vector<neighbor_cell_cdma_2000> neighbor_cell_list_;
};
struct lte_sib8_type : public lte_sib_base
{
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

class lte_rrc_message_aggregate : public bcch_bch_message_aggregate
{
public:
	lte_rrc_message_aggregate();
	void clear()
	{
		bcch_bch_message_aggregate::clear();
		sib1_.clear();
		sib4_.clear();
		sib5_.clear();
		sib6_.clear();
		sib7_.clear();
		sib8_.clear();
	}

	void swap(lte_rrc_message_aggregate &a)
	{
		bcch_bch_message_aggregate::swap(a);
		sib1_.swap(a.sib1_);
		sib4_.swap(a.sib4_);
		sib5_.swap(a.sib5_);
		sib6_.swap(a.sib6_);
		sib7_.swap(a.sib7_);
		sib8_.swap(a.sib8_);
	}

	lte_sib1_type sib1_;
	lte_sib4_type sib4_;
	lte_sib5_type sib5_;
	lte_sib6_type sib6_;
	lte_sib7_type sib7_;
	lte_sib8_type sib8_;
};


}