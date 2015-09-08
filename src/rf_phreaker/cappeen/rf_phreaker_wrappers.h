#pragma once

#include <list>
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include "rf_phreaker/cappeen/beagle_defines.h"

namespace rf_phreaker { namespace cappeen_api {

inline void copy_mcc_mnc(char m[4], const layer_3_information::uint16_string &str) {
	memset(m, 0, 4);
	auto size = str.num_characters() > 3 ? 3 : str.num_characters();
	memcpy(m, str.to_string(), size);
}

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
		s_.decoded_ = s.is_decoded_;
		s_.cid_ = s.cell_id_;
		s_.tac_ = s.tracking_area_code_;

		for(auto &i : s.multiple_plmn_) {
			beagle_api::plmn p;
			copy_mcc_mnc(p.mcc_, i.mcc_);
			copy_mcc_mnc(p.mnc_, i.mnc_);
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

class lte_sib3_wrapper {
public:
	lte_sib3_wrapper() {};
	lte_sib3_wrapper(lte_sib3_wrapper &&s)
		: s_(std::move(s.s_))
		{}
	lte_sib3_wrapper(const layer_3_information::lte_sib3_type &s) {
		s_.decoded_ = s.is_decoded_;
		s_.cell_reselection_serving_freq_info_.cell_reselection_priority_ = s.cell_reselection_serving_freq_info_.cell_reselection_priority_;
		s_.cell_reselection_serving_freq_info_.s_non_intra_search_ = s.cell_reselection_serving_freq_info_.s_non_intra_search_.reselection_threshold();
		s_.cell_reselection_serving_freq_info_.threshold_serving_low_ = s.cell_reselection_serving_freq_info_.threshold_serving_low_.reselection_threshold();
		s_.intra_freq_cell_reselection_info_.s_intra_search_ = s.intra_freq_cell_reselection_info_.s_intra_search_.reselection_threshold();
		s_.s_intra_search_v920_.reselection_threshold_p_ = s.s_intra_search_v920_.p_.reselection_threshold();
		s_.s_intra_search_v920_.reselection_threshold_q_ = s.s_intra_search_v920_.q_;
		s_.s_non_intra_search_v920_.reselection_threshold_p_ = s.s_non_intra_search_v920_.p_.reselection_threshold();
		s_.s_non_intra_search_v920_.reselection_threshold_q_ = s.s_non_intra_search_v920_.q_;
		s_.threshold_serving_low_q_ = s.threshold_serving_low_q_;
	}

	beagle_api::lte_sib_3 s_;
};

class lte_sib4_wrapper {
public:
	lte_sib4_wrapper() {};
	lte_sib4_wrapper(lte_sib4_wrapper &&s)
		: s_(std::move(s.s_))
		, intra_cells_(std::move(s.intra_cells_))
		, intra_blacks_(std::move(s.intra_blacks_)) {}
	lte_sib4_wrapper(const layer_3_information::lte_sib4_type &s) {
		s_.decoded_ = s.is_decoded_;

		for(auto &i : s.intra_freq_neighbor_cell_list_) {
			beagle_api::lte_neighbor_cell t;
			t.physical_cell_id_ = i.physical_cell_id_;
			t.q_offset_cell_ = i.q_offset_cell_;
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
		s_.decoded_ = s.is_decoded_;

		for(auto &i : s.inter_freq_carrier_info_list_) {
			beagle_api::lte_neighbor_inter t;
			t.downlink_arfcn_value_eutra_ = i.downlink_arfcn_value_eutra_;
			t.allowed_measurement_bandwidth_ = i.allowed_measurement_bandwidth_;
			t.presence_antenna_port_1_ = i.presence_antenna_port_1_;
			t.q_rx_lev_min_ = i.q_rx_lev_min_;
			t.q_offset_freq_ = i.q_offset_freq_;
			t.threshold_x_high_ = i.threshold_x_high_.reselection_threshold();
			t.threshold_x_low_ = i.threshold_x_low_.reselection_threshold();
			t.threshold_x_high_q_r9_ = i.threshold_x_high_q_r9_;
			t.threshold_x_low_q_r9_ = i.threshold_x_low_q_r9_;
			t.cell_reselection_priority_ = i.cell_reselection_priority_;
			inter_cells_.push_back(std::vector<beagle_api::lte_neighbor_cell>());
			auto &cells = inter_cells_.back();
			for(auto &j : i.inter_freq_neighbor_cell_list_) {
				beagle_api::lte_neighbor_cell t;
				t.physical_cell_id_ = j.physical_cell_id_;
				t.q_offset_cell_ = j.q_offset_cell_;
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
		s_.decoded_ = s.is_decoded_;

		for(auto &i : s.carrier_freq_list_utra_fdd_) {
			beagle_api::carrier_freq_utra t;
			t.arfcn_value_utra_ = i.arfcn_value_utra_;
			t.cell_reselection_priority_ = i.cell_reselection_priority_;
			t.threshold_x_high_ = i.threshold_x_high_.reselection_threshold();
			t.threshold_x_high_q_r9_ = i.threshold_x_high_q_r9_;
			t.threshold_x_low_ = i.threshold_x_low_.reselection_threshold();
			t.threshold_x_low_q_r9_ = i.threshold_x_low_q_r9_;
			fdd_.push_back(t);
		}
		s_.carrier_freq_list_utra_fdd_.num_elements_ = fdd_.size();
		s_.carrier_freq_list_utra_fdd_.elements_ = fdd_.size() ? &fdd_[0] : 0;

		for(auto &i : s.carrier_freq_list_utra_tdd_) {
			beagle_api::carrier_freq_utra t;
			t.arfcn_value_utra_ = i.arfcn_value_utra_;
			t.cell_reselection_priority_ = i.cell_reselection_priority_;
			t.threshold_x_high_ = i.threshold_x_high_.reselection_threshold();
			t.threshold_x_high_q_r9_ = i.threshold_x_high_q_r9_;
			t.threshold_x_low_ = i.threshold_x_low_.reselection_threshold();
			t.threshold_x_low_q_r9_ = i.threshold_x_low_q_r9_;
			tdd_.push_back(t);
		}
		s_.carrier_freq_list_utra_tdd_.num_elements_ = tdd_.size();
		s_.carrier_freq_list_utra_tdd_.elements_ = tdd_.size() ? &tdd_[0] : 0;
	}

	beagle_api::lte_sib_6 s_;
	std::vector<beagle_api::carrier_freq_utra> fdd_;
	std::vector<beagle_api::carrier_freq_utra> tdd_;
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
		s_.decoded_ = s.is_decoded_;

		for(auto &i : s.carrier_freqs_info_list_geran_) {
			beagle_api::lte_neighbor_inter_rat_geran t;
			t.band_indicator_ = i.carrier_freqs_.band_indicator_ == layer_3_information::dcs_1800_was_used ? beagle_api::DCS_1800_WAS_USED : beagle_api::PCS_1900_WAS_USED;
			t.common_info_.cell_reselection_priority_ = i.common_info_.cell_reselection_priority_;
			t.common_info_.threshold_x_high_ = i.common_info_.threshold_x_high_.reselection_threshold();
			t.common_info_.threshold_x_low_ = i.common_info_.threshold_x_low_.reselection_threshold();

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
		s_.decoded_ = s.is_decoded_;

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
			hrpd_.push_back(t);
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
			xrtt_.push_back(t);
		}
		s_.parameters_1xrtt_.num_elements_ = xrtt_.size();
		s_.parameters_1xrtt_.elements_ = xrtt_.size() ? &xrtt_[0] : 0;
	}

	beagle_api::lte_sib_8 s_;
	std::vector<beagle_api::lte_neighbor_inter_rat_cdma_2000> hrpd_;
	std::vector<beagle_api::lte_neighbor_inter_rat_cdma_2000> xrtt_;
	std::list<std::vector<beagle_api::channel_type>> channels_;
};

class gsm_si_2_wrapper {
public:
	gsm_si_2_wrapper() {}
	gsm_si_2_wrapper(gsm_si_2_wrapper &&s)
		: s_(std::move(s.s_))
		, bcchs_(std::move(s.bcchs_)) {}
	gsm_si_2_wrapper(const layer_3_information::gsm_si_2 &s) {
		s_.decoded_ = s.is_decoded_;
		s_.ba_ind_ = s.gsm_ba_ind_;
		s_.ext_ind_ = s.bcch_neighbors_has_extension_;
		for(const auto &i : s.bcch_neighbors_) {
			bcchs_.push_back(i);
		}
		s_.bcch_neighbors_.num_elements_ = bcchs_.size();
		s_.bcch_neighbors_.elements_ = bcchs_.size() ? &bcchs_[0] : 0;
	}

	beagle_api::gsm_si_2 s_;
	std::vector<beagle_api::channel_type> bcchs_;
};

class gsm_si_2bis_wrapper {
public:
	gsm_si_2bis_wrapper() {}
	gsm_si_2bis_wrapper(gsm_si_2bis_wrapper &&s)
		: s_(std::move(s.s_)) 
		, bcchs_(std::move(s.bcchs_)) {}
	gsm_si_2bis_wrapper(const layer_3_information::gsm_si_2bis &s) {
		s_.decoded_ = s.is_decoded_;
		s_.ba_ind_ = s.gsm_ba_ind_;
		s_.ext_ind_ = s.bcch_neighbors_has_extension_;
		for(const auto &i : s.extended_bcch_neighbors_) {
			bcchs_.push_back(i);
		}
		s_.bcch_neighbors_.num_elements_ = bcchs_.size();
		s_.bcch_neighbors_.elements_ = bcchs_.size() ? &bcchs_[0] : 0;
		s_.rest_octet_count_ = s.rest_octet_count_;
		s_.rest_octet_index_ = s.rest_octet_index_;
	}

	beagle_api::gsm_si_2bis s_;
	std::vector<beagle_api::channel_type> bcchs_;
};

class gsm_si_2ter_wrapper {
public:
	gsm_si_2ter_wrapper() {}
	gsm_si_2ter_wrapper(gsm_si_2ter_wrapper &&s)
		: s_(std::move(s.s_)) 
		, bcchs_(std::move(s.bcchs_))
		, scrambling_codes_(std::move(s.scrambling_codes_))
		, utran_(std::move(s.utran_)) {}
	gsm_si_2ter_wrapper(const layer_3_information::gsm_si_2ter &s) {
		s_.decoded_ = s.is_decoded_;
		s_.ba_ind_ = s.gsm_ba_ind_;
		s_.bcch_neighbor_multiband_reporting_ = s.bcch_neighbors_multiband_reporting_;
		for(const auto &i : s.extended_bcch_neighbors_) {
			bcchs_.push_back(i);
		}
		s_.bcch_neighbors_.num_elements_ = bcchs_.size();
		s_.bcch_neighbors_.elements_ = bcchs_.size() ? &bcchs_[0] : 0;
		
		for(const auto &i : s.utran_neighbors_) {
			beagle_api::gsm_utran_neighbor u;
			u.uarfcn_ = i.arfcn_;
			u.duplexing_= (beagle_api::DUPLEX)i.duplexing_;
			u.bandwidth_ = (beagle_api::UTRAN_BANDWIDTH)i.bandwidth_;

			scrambling_codes_.push_back(std::vector<beagle_api::channel_type>());
			auto &tmp = scrambling_codes_.back();
			for(const auto &j : i.scrambling_codes_) {
				tmp.push_back(j);
			}
			u.scrambling_codes_.num_elements_ = tmp.size();
			u.scrambling_codes_.elements_ = tmp.size() ? &tmp[0] : 0;

			utran_.push_back(u);
		}
		s_.utran_neighbors_.num_elements_ = utran_.size();
		s_.utran_neighbors_.elements_ = utran_.size() ? &utran_[0] : 0;

		s_.rest_octet_count_ = s.rest_octet_count_;
		s_.rest_octet_index_ = s.rest_octet_index_;
	}

	beagle_api::gsm_si_2ter s_;
	std::vector<beagle_api::channel_type> bcchs_;
	std::list<std::vector<beagle_api::channel_type>> scrambling_codes_;
	std::vector<beagle_api::gsm_utran_neighbor> utran_;
};

inline int convert(const layer_3_information::eutran_bandwidth_type b) {
	using namespace layer_3_information;
	switch(b) {
	case num_resource_blocks_6: return 6;
	case num_resource_blocks_15: return 15;
	case num_resource_blocks_25: return 25;
	case num_resource_blocks_50: return 50;
	case num_resource_blocks_75: return 75;
	case num_resource_blocks_100:
	default:
		return 100;
	}
}
class gsm_si_2quater_wrapper {
public:
	gsm_si_2quater_wrapper() {}
	gsm_si_2quater_wrapper(gsm_si_2quater_wrapper &&s)
		: s_(std::move(s.s_))
		, scrambling_codes_(std::move(s.scrambling_codes_))
		, utran_(std::move(s.utran_))
		, allowed_(std::move(s.allowed_))
		, not_allowed_(std::move(s.not_allowed_))
		, same_ta_(std::move(s.same_ta_))
		, different_ta_(std::move(s.different_ta_)) 
		, same_tas_(std::move(s.same_tas_))
		, different_tas_(std::move(s.different_tas_))
		, eutran_(std::move(s.eutran_))
	{}
	gsm_si_2quater_wrapper(const layer_3_information::gsm_si_2quater &s) {
		s_.decoded_ = s.is_decoded_;
		s_.ba_ind_ = s.gsm_ba_ind_;
		s_.ba_ind_3g_ = s.p3g_ba_ind_;

		for(const auto &i : s.utran_neighbors_) {
			beagle_api::gsm_utran_neighbor u;
			u.uarfcn_ = i.arfcn_;
			u.duplexing_ = (beagle_api::DUPLEX)i.duplexing_;
			u.bandwidth_ = (beagle_api::UTRAN_BANDWIDTH)i.bandwidth_;
			scrambling_codes_.push_back(std::vector<beagle_api::channel_type>());
			auto &tmp = scrambling_codes_.back();
			for(const auto &j : i.scrambling_codes_) {
				tmp.push_back(j);
			}
			u.scrambling_codes_.num_elements_ = tmp.size();
			u.scrambling_codes_.elements_ = tmp.size() ? &tmp[0] : 0;

			utran_.push_back(u);
		}
		s_.utran_neighbors_.num_elements_ = utran_.size();
		s_.utran_neighbors_.elements_ = utran_.size() ? &utran_[0] : 0;

		for(const auto &i : s.eutran_neighbors_) {
			beagle_api::gsm_eutran_neighbor e;
			e.earfcn_ = i.earfcn_;
			e.bandwidth_in_resource_blocks_ = convert(i.bandwidth_);
			
			allowed_.push_back(std::vector<beagle_api::channel_type>());
			auto &a = allowed_.back();
			for(const auto &j : i.pcids_allowed_) {
				a.push_back(j);
			}
			e.pcids_allowed_.num_elements_ = a.size();
			e.pcids_allowed_.elements_ = a.size() ? &a[0] : 0;
			
			not_allowed_.push_back(std::vector<beagle_api::channel_type>());
			auto &na = not_allowed_.back();
			for(const auto &j : i.pcids_not_allowed_) {
				na.push_back(j);
			}
			e.pcids_not_allowed_.num_elements_ = na.size();
			e.pcids_not_allowed_.elements_ = na.size() ? &na[0] : 0;

			{
				same_tas_.push_back(std::vector<beagle_api::gsm_pcid_group>());
				auto &ta_list = same_tas_.back();
				for(const auto &j : i.pcids_same_tracking_area_) {
					ta_list.push_back(beagle_api::gsm_pcid_group());
					auto &pcid_group = ta_list.back();
					same_ta_.push_back(std::vector<beagle_api::channel_type>());
					auto &t = same_ta_.back();
					for(const auto &k : j) {
						t.push_back(k);
					}
					pcid_group.num_elements_ = t.size();
					pcid_group.elements_ = t.size() ? &t[0] : 0;
				}
				e.pcids_same_tracking_area_.num_elements_ = ta_list.size();
				e.pcids_same_tracking_area_.elements_ = ta_list.size() ? &ta_list[0] : 0;
			}

			{
				different_tas_.push_back(std::vector<beagle_api::gsm_pcid_group>());
				auto &ta_list = different_tas_.back();
				for(const auto &j : i.pcids_different_tracking_area_) {
					ta_list.push_back(beagle_api::gsm_pcid_group());
					auto &pcid_group = ta_list.back();
					different_ta_.push_back(std::vector<beagle_api::channel_type>());
					auto &t = different_ta_.back();
					for(const auto &k : j) {
						t.push_back(k);
					}
					pcid_group.num_elements_ = t.size();
					pcid_group.elements_ = t.size() ? &t[0] : 0;
				}
				e.pcids_different_tracking_area_.num_elements_ = ta_list.size();
				e.pcids_different_tracking_area_.elements_ = ta_list.size() ? &ta_list[0] : 0;
			}

			e.priority_ = i.priority_;
			e.threshold_high_ = i.threshold_high_;
			e.threshold_low_ = i.threshold_low_;
			e.qrxlevmin_ = i.qrxlevmin_;

			eutran_.push_back(e);
		}
		s_.eutran_neighbors_.num_elements_ = eutran_.size();
		s_.eutran_neighbors_.elements_ = eutran_.size() ? &eutran_[0] : 0;

		for(auto &i : s.extended_eutran_neighbors_) {
			extended_earfcns_.push_back(i);
		}
		s_.extended_earfcns_.num_elements_ = extended_earfcns_.size();
		s_.extended_earfcns_.elements_ = extended_earfcns_.size() ? &extended_earfcns_[0] : 0;
		
		s_.rest_octet_count_ = s.rest_octet_count_;
		s_.rest_octet_index_ = s.rest_octet_index_;
	}

	beagle_api::gsm_si_2quater s_;
	std::list<std::vector<beagle_api::channel_type>> scrambling_codes_;
	std::vector<beagle_api::gsm_utran_neighbor> utran_;
	std::list<std::vector<beagle_api::channel_type>> allowed_;
	std::list<std::vector<beagle_api::channel_type>> not_allowed_;
	std::list<std::vector<beagle_api::channel_type>> same_ta_;
	std::list<std::vector<beagle_api::channel_type>> different_ta_;
	std::list<std::vector<beagle_api::gsm_pcid_group>> same_tas_;
	std::list<std::vector<beagle_api::gsm_pcid_group>> different_tas_;
	std::vector<beagle_api::gsm_eutran_neighbor> eutran_;
	std::vector<beagle_api::channel_type> extended_earfcns_;
};

class gsm_si_3_wrapper {
public:
	gsm_si_3_wrapper() {}
	gsm_si_3_wrapper(gsm_si_3_wrapper &&s)
		: s_(std::move(s.s_)) {}
	gsm_si_3_wrapper(const layer_3_information::gsm_si_3 &s) {
		s_.decoded_ = s.is_decoded_;
		copy_mcc_mnc(s_.plmn_.mcc_, s.plmn_.mcc_);
		copy_mcc_mnc(s_.plmn_.mnc_, s.plmn_.mnc_);
		s_.lac_ = s.location_area_code_;
		s_.cid_ = s.cell_id_;
		s_.cell_reselect_hysteresis_db_ = s.cell_reselect_hysteresis_db_;
		s_.cell_reselect_offset_ = s.selection_parameters_.cell_reselect_offset_;
		s_.is_2ter_present_ = s.is_2ter_present_;
		s_.is_2quater_present_ = s.is_2quater_present_;
	}
	beagle_api::gsm_si_3 s_;
};

class gsm_si_4_wrapper {
public:
	gsm_si_4_wrapper() {}
	gsm_si_4_wrapper(gsm_si_4_wrapper &&s)
		: s_(std::move(s.s_)) {}
	gsm_si_4_wrapper(const layer_3_information::gsm_si_4 &s) {
		s_.decoded_ = s.is_decoded_;
		copy_mcc_mnc(s_.plmn_.mcc_, s.plmn_.mcc_);
		copy_mcc_mnc(s_.plmn_.mnc_, s.plmn_.mnc_);
		s_.lac_ = s.location_area_code_;
		s_.cid_ = s.cell_id_;
		s_.cell_reselect_hysteresis_db_ = s.cell_reselect_hysteresis_db_;
		s_.cell_reselect_offset_ = s.selection_parameters_.cell_reselect_offset_;
		s_.is_cbch_present_ = s.is_cbch_present_;
	}
	beagle_api::gsm_si_4 s_;
};


}}