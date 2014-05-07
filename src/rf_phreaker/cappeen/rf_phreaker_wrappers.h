#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/cappeen/beagle_defines.h"
#include <list>

namespace rf_phreaker { namespace cappeen_api {

class lte_sib1_wrapper
{
public:
	lte_sib1_wrapper() {};
	lte_sib1_wrapper(lte_sib1_wrapper &&s)
		: s_(std::move(s.s_))
		, plmns_(std::move(s.plmns_))
		, scheduled_sibs_(std::move(s.scheduled_sibs_))
	{}
	lte_sib1_wrapper(const layer_3_information::lte_sib1_type &s)
	{
		s_.decoded_ = s.decoded_;
		s_.cid_ = s.cell_id_;
		s_.tac_ = s.tracking_area_code_;

		for(auto &i : s.multiple_plmn_) {
			beagle_api::plmn p;
			memcpy(p.mcc_, i.mcc_.to_string(), i.mcc_.num_characters());
			p.mcc_[i.mcc_.num_characters()] = 0;
			memcpy(p.mnc_, i.mnc_.to_string(), i.mnc_.num_characters());
			p.mnc_[i.mnc_.num_characters()] = 0;
			plmns_.push_back(p);
		}
		s_.plmns_.num_elements_ = plmns_.size();
		s_.plmns_.elements_ = plmns_.size() ? &plmns_[0] : 0;

		for(auto &i : s.scheduling_info_list_) {
			beagle_api::lte_scheduled_sib sch_s;
			sch_s.periodicity_in_frames_ = i.periodicity_in_frames_;
			for(auto &j : i.sib_mapping_info_) {
				sch_s.sib = (beagle_api::LTE_SIB_TYPE)j;
				scheduled_sibs_.push_back(sch_s);
			}
		}
		s_.scheduled_sibs_.num_elements_ = scheduled_sibs_.size();
		s_.scheduled_sibs_.elements_ = scheduled_sibs_.size() ? &scheduled_sibs_[0] : 0;
	}
	beagle_api::lte_sib_1 s_;
	std::vector<beagle_api::plmn> plmns_;
	std::vector<beagle_api::lte_scheduled_sib> scheduled_sibs_;
};

class lte_sib4_wrapper
{
public:
	lte_sib4_wrapper() {};
	lte_sib4_wrapper(lte_sib4_wrapper &&s)
		: s_(std::move(s.s_))
		, intra_cells_(std::move(s.intra_cells_))
		, intra_blacks_(std::move(s.intra_blacks_))
	{}
	lte_sib4_wrapper(const layer_3_information::lte_sib4_type &s)
	{
		s_.decoded_ = s.decoded_;

		for(auto &i : s.intra_freq_neighbor_cell_list_) {
			beagle_api::lte_neighbor_cell t;
			t.physical_cell_id_ = i.physical_cell_id_;
			intra_cells_.push_back(t);
		}
		s_.intra_freq_neighbor_cell_list_.num_elements_ = intra_cells_.size();
		s_.intra_freq_neighbor_cell_list_.elements_ = intra_cells_.size() ? &intra_cells_[0] : 0;

		for(auto &i : s.intra_freq_black_cell_list_) {
			beagle_api::lte_physical_cell_id_range t;
			t.start_ = i.start_;
			t.range_ = i.range_;
			intra_blacks_.push_back(t);
		}
		s_.intra_freq_black_cell_list_.num_elements_ = intra_blacks_.size();
		s_.intra_freq_black_cell_list_.elements_ = intra_blacks_.size() ? &intra_blacks_[0] : 0;

		s_.csg_physical_cellid_range_.start_ = s.csg_physical_cellid_range_.start_;
		s_.csg_physical_cellid_range_.range_ = s.csg_physical_cellid_range_.range_;
	}

	beagle_api::lte_sib_4 s_;
	std::vector<beagle_api::lte_neighbor_cell> intra_cells_;
	std::vector<beagle_api::lte_physical_cell_id_range> intra_blacks_;
};

class lte_sib5_wrapper
{
public:
	lte_sib5_wrapper() {};
	lte_sib5_wrapper(lte_sib5_wrapper &&s)
		: s_(std::move(s.s_))
		, inter_neighbors_(std::move(s.inter_neighbors_))
		, inter_cells_(std::move(s.inter_cells_))
		, inter_blacks_(std::move(s.inter_blacks_))
	{}
	lte_sib5_wrapper(const layer_3_information::lte_sib5_type &s)
	{
		s_.decoded_ = s.decoded_;

		for(auto &i : s.inter_freq_carrier_info_list_) {
			beagle_api::lte_neighbor_inter t;
			t.downlink_arfcn_value_eutra_ = i.downlink_arfcn_value_eutra_;
			t.allowed_measurement_bandwidth_ = i.allowed_measurement_bandwidth_;
			t.presence_antenna_port_1_ = i.presence_antenna_port_1_;
			
			inter_cells_.push_back(std::vector<beagle_api::lte_neighbor_cell>());
			auto &cells = inter_cells_.back();
			for(auto &j : i.inter_freq_neighbor_cell_list_) {
				beagle_api::lte_neighbor_cell t;
				t.physical_cell_id_ = j.physical_cell_id_;
				cells.push_back(t);
			}
			t.inter_freq_neighbor_cell_list_.num_elements_ = cells.size();
			t.inter_freq_neighbor_cell_list_.elements_ = cells.size() ? &cells[0] : 0;


			inter_blacks_.push_back(std::vector<beagle_api::lte_physical_cell_id_range>());
			auto &blacks = inter_blacks_.back();
			for(auto &j : i.inter_freq_black_cell_list_) {
				beagle_api::lte_physical_cell_id_range t;
				t.start_ = j.start_;
				t.range_ = j.range_;
				blacks.push_back(t);
			}
			t.inter_freq_black_cell_list_.num_elements_ = blacks.size();
			t.inter_freq_black_cell_list_.elements_ = blacks.size() ? &blacks[0] : 0;

			inter_neighbors_.push_back(t);
		}
		s_.inter_freq_carrier_info_list_.num_elements_ = inter_neighbors_.size();
		s_.inter_freq_carrier_info_list_.elements_ = inter_neighbors_.size() ? &inter_neighbors_[0] : 0;

	}

	beagle_api::lte_sib_5 s_;
	std::vector<beagle_api::lte_neighbor_inter> inter_neighbors_;
	std::list<std::vector<beagle_api::lte_neighbor_cell>> inter_cells_;
	std::list<std::vector<beagle_api::lte_physical_cell_id_range>> inter_blacks_;
};

class lte_sib6_wrapper
{
public:
	lte_sib6_wrapper() {};
	lte_sib6_wrapper(lte_sib6_wrapper &&s)
		: s_(std::move(s.s_))
		, fdd_(std::move(s.fdd_))
		, tdd_(std::move(s.tdd_))
	{}
	lte_sib6_wrapper(const layer_3_information::lte_sib6_type &s)
	{
		s_.decoded_ = s.decoded_;

		for(auto &i : s.carrier_freq_list_utra_fdd_) {
			beagle_api::channel_type t;
			t = i.arfcn_value_utra_;
			fdd_.push_back(t);
		}
		s_.carrier_freq_list_utra_fdd_.num_elements_ = fdd_.size();
		s_.carrier_freq_list_utra_fdd_.elements_ = fdd_.size() ? &fdd_[0] : 0;

		for(auto &i : s.carrier_freq_list_utra_tdd_) {
			beagle_api::channel_type t;
			t = i.arfcn_value_utra_;
			tdd_.push_back(t);
		}
		s_.carrier_freq_list_utra_tdd_.num_elements_ = tdd_.size();
		s_.carrier_freq_list_utra_tdd_.elements_ = tdd_.size() ? &tdd_[0] : 0;
	}

	beagle_api::lte_sib_6 s_;
	std::vector<beagle_api::channel_type> fdd_;
	std::vector<beagle_api::channel_type> tdd_;
};

class lte_sib7_wrapper
{
public:
	lte_sib7_wrapper() {};
	lte_sib7_wrapper(lte_sib7_wrapper &&s)
		: s_(std::move(s.s_))
		, gerans_(std::move(s.gerans_))
		, channels_(std::move(s.channels_))
	{}
 	lte_sib7_wrapper(const layer_3_information::lte_sib7_type &s)
	{
		s_.decoded_ = s.decoded_;

		for(auto &i : s.carrier_freqs_info_list_geran_) {
			beagle_api::lte_neighbor_inter_rat_geran t;
			t.band_indicator_ = i.carrier_freqs_.band_indicator_ == layer_3_information::dcs_1800_was_used ? beagle_api::DCS_1800_WAS_USED : beagle_api::PCS_1900_WAS_USED;

			channels_.push_back(std::vector<beagle_api::channel_type>());
			auto &tmp_channels = channels_.back();
			for(auto &j : i.carrier_freqs_.following_arfcns_) {
				beagle_api::channel_type t;
				t = j;
				tmp_channels.push_back(t);
			}
			t.arfcns_.num_elements_ = tmp_channels.size();
			t.arfcns_.elements_ = tmp_channels.size() ? &tmp_channels[0] : 0;

			gerans_.push_back(t);
		}
		s_.carrier_freqs_.num_elements_ = gerans_.size();
		s_.carrier_freqs_.elements_ = gerans_.size() ? &gerans_[0] : 0;
	}

	beagle_api::lte_sib_7 s_;
	std::vector<beagle_api::lte_neighbor_inter_rat_geran> gerans_;
	std::list<std::vector<beagle_api::channel_type>> channels_;
};

class lte_sib8_wrapper
{
public:
	lte_sib8_wrapper() {};
	lte_sib8_wrapper(lte_sib8_wrapper &&s)
		: s_(std::move(s.s_))
		, hrpd_(std::move(s.hrpd_))
		, xrtt_(std::move(s.xrtt_))
		, channels_(std::move(s.channels_))
	{}
	lte_sib8_wrapper(const layer_3_information::lte_sib8_type &s)
	{
		s_.decoded_ = s.decoded_;

		for(auto &i : s.parameters_hrpd_.neighbor_cell_list_) {
			beagle_api::lte_neighbor_inter_rat_cdma_2000 t;
			t.band_ = (beagle_api::BAND_CLASS_CMDA_2000)i.band_;
			
			for(auto &j : i.neighbor_cells_per_freq_list_) {
				t.arfcn_value_cmda_2000_ = j.arfcn_value_cmda_2000_;

				channels_.push_back(std::vector<beagle_api::channel_type>());
				auto &tmp_channels = channels_.back();
				for(auto &k : j.physical_cell_ids_) {
					beagle_api::channel_type t = k;
					tmp_channels.push_back(t);
				}
				t.physical_cell_ids_.num_elements_ = tmp_channels.size();
				t.physical_cell_ids_.elements_ = tmp_channels.size() ? &tmp_channels[0] : 0;
			}
		}
		s_.parameters_hrpd_.num_elements_ = hrpd_.size();
		s_.parameters_hrpd_.elements_ = hrpd_.size() ? &hrpd_[0] : 0;

		for(auto &i : s.parameters_1xrtt_.neighbor_cell_list_) {
			beagle_api::lte_neighbor_inter_rat_cdma_2000 t;
			t.band_ = (beagle_api::BAND_CLASS_CMDA_2000)i.band_;

			for(auto &j : i.neighbor_cells_per_freq_list_) {
				t.arfcn_value_cmda_2000_ = j.arfcn_value_cmda_2000_;

				channels_.push_back(std::vector<beagle_api::channel_type>());
				auto &tmp_channels = channels_.back();
				for(auto &k : j.physical_cell_ids_) {
					beagle_api::channel_type t = k;
					tmp_channels.push_back(t);
				}
				t.physical_cell_ids_.num_elements_ = tmp_channels.size();
				t.physical_cell_ids_.elements_ = tmp_channels.size() ? &tmp_channels[0] : 0;
			}
		}
		s_.parameters_1xrtt_.num_elements_ = xrtt_.size();
		s_.parameters_1xrtt_.elements_ = xrtt_.size() ? &xrtt_[0] : 0;
	}

	beagle_api::lte_sib_8 s_;
	std::vector<beagle_api::lte_neighbor_inter_rat_cdma_2000> hrpd_;
	std::vector<beagle_api::lte_neighbor_inter_rat_cdma_2000> xrtt_;
	std::list <std::vector<beagle_api::channel_type>> channels_;
};

}}