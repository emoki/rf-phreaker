#pragma once
#include "gtest/gtest.h"
#include "rf_phreaker/common/measurements.h"

using namespace rf_phreaker;
using namespace layer_3_information;

class MeasManager : public ::testing::Test
{
protected:
	MeasManager() {
		h_ = create_hardware();
		gps_ = create_gps();
		for(int i = 0; i < 5; ++i)
			gsm_.push_back(create_gsm(i));
		for(int i = 0; i < 5; ++i)
			umts_.push_back(create_umts(i));
		for(int i = 0; i < 5; ++i)
			lte_.push_back(create_lte(i));
	}
	hardware create_hardware(int tmp = 0) {
		hardware h;
		h.device_communication_ = rf_phreaker::USB_SUPER_SPEED;
		h.frequency_correction_calibration_date_ = tmp++;
		h.hw_id_ = tmp++;
		h.license_data_.bytes_ = {0, 2, 3, 4};
		h.serial_ = "83hsdf";
		h.frequency_paths_ = {{tmp++, tmp++}, {tmp++, tmp++}};
		return h;
	}
	gps create_gps(int tmp = 0) {
		gps g;
		g.serial_ = "adlfkjapo";
		g.lock_ = false;
		g.coordinated_universal_time_ = tmp++;
		g.visible_satellites_ = tmp++;
		g.tracking_satellites_ = tmp++;
		g.latitude_ = tmp++;
		g.longitude_ = tmp++;
		g.altitude_= tmp++;
		g.angle_ = tmp++;
		g.speed_ = tmp++;
		g.dilution_of_precision_ = tmp++;
		g.horizontal_accuracy_meters_ = tmp++;
		g.vertical_accuracy_meters_= tmp++;
		g.raw_status_ = tmp++;
		for(int i = 0; i < 12; ++i) {
			gps::satellite sat;
			sat.prn_ = tmp++;
			sat.snr_ = tmp++;
			sat.elevation_ = tmp++;
			sat.azimuth_ = tmp++;
			g.satellites_.push_back(sat);
		}
		return g;
	}
	gsm_data create_gsm(int tmp = 0) {
		gsm_data gsm;
		{
			basic_data &b = gsm;
			b.measurement_bandwidth_ = tmp++;
			b.measurement_frequency_ = tmp++;
			b.measurement_signal_level_ = tmp++;
			b.collection_round_ = tmp++;
			b.serial_ = "aldskfj";
			b.status_flags_ = tmp++;
			b.time_ = tmp++;
		}
		gsm.arfcn_ = tmp++;
		gsm.bsic_ = tmp++;
		gsm.cell_signal_level_ = tmp++;
		gsm.ctoi_ = tmp++;
		gsm.operating_band_ = rf_phreaker::GSM_450;
		gsm.tdma_frame_number_ = tmp++;

		{
			layer_3_information::gsm_si_1 si;
			si.is_decoded_ = true;
			si.band_indicator_ = layer_3_information::dcs_1800_was_used;
			gsm.layer_3_.si_1_ = si;
		}
		{
			layer_3_information::gsm_si_2 si;
			int32_t tmp = 0;

			si.is_decoded_ = true;
			si.bcch_neighbors_has_extension_ = rand() % 2 == 0;
			si.gsm_ba_ind_ = tmp++;
			for(int i = 0; i < 5; ++i)
				si.bcch_neighbors_.push_back(tmp++);
			gsm.layer_3_.si_2_ = si;
		}
		{
			layer_3_information::gsm_si_2bis si;
			int32_t tmp = 0;

			si.is_decoded_ = true;
			si.bcch_neighbors_has_extension_ = rand() % 2 == 0;
			si.gsm_ba_ind_ = tmp++;
			si.rest_octet_count_ = tmp++;
			si.rest_octet_index_ = tmp++;
			for(int i = 0; i < 5; ++i)
				si.extended_bcch_neighbors_.push_back(tmp++);
			gsm.layer_3_.si_2bis_ = si;
		}
		{
			layer_3_information::gsm_si_2ter si;
			int32_t tmp = 0;

			si.is_decoded_ = true;
			si.bcch_neighbors_multiband_reporting_ = tmp++;
			si.gsm_ba_ind_ = tmp++;
			si.rest_octet_count_ = tmp++;
			si.rest_octet_index_ = tmp++;
			for(int i = 0; i < 5; ++i)
				si.extended_bcch_neighbors_.push_back(tmp++);

			for(int i = 0; i < 5; ++i) {
				layer_3_information::utran_neighbor u;
				u.arfcn_ = tmp++;
				u.duplexing_ = rand() % 2 == 0 ? layer_3_information::fdd : layer_3_information::tdd;
				u.bandwidth_ = (utran_bandwidth_type)(rand() % 6);
				for(int j = 0; j < 5; ++j)
					u.scrambling_codes_.push_back(tmp++);
				si.utran_neighbors_.push_back(u);
			}
			gsm.layer_3_.si_2ter_ = si;
		}
		{
			layer_3_information::gsm_si_2quater si;
			int32_t tmp = 0;

			si.is_decoded_ = true;
			si.gsm_ba_ind_ = tmp++;
			si.p3g_ba_ind_ = tmp++;
			si.utran_neighbor_cell_absolute_index_start_emr_ = tmp++;
			si.utran_neighbor_cell_index_start_3g_ = tmp++;
			si.rest_octet_count_ = tmp++;
			si.rest_octet_index_ = tmp++;

			for(int i = 0; i < 5; ++i) {
				layer_3_information::utran_neighbor u;
				u.arfcn_ = tmp++;
				u.duplexing_ = rand() % 2 == 0 ? layer_3_information::fdd : layer_3_information::tdd;
				u.bandwidth_ = (utran_bandwidth_type)(rand() % 6);
				for(int j = 0; j < 5; ++j)
					u.scrambling_codes_.push_back(tmp++);
				si.utran_neighbors_.push_back(u);
			}

			for(int i = 0; i < 5; ++i) {
				layer_3_information::eutran_neighbor e;
				e.earfcn_ = tmp++;
				e.bandwidth_ = (eutran_bandwidth_type)(rand() % 6);
				for(int j = 0; j < 5; ++j)
					e.pcids_allowed_.push_back(tmp++);
				for(int j = 0; j < 5; ++j)
					e.pcids_not_allowed_.push_back(tmp++);
				for(int j = 0; j < 5; ++j) {
					std::vector<int32_t> pcids;
					for(int k = 0; k < 5; ++k)
						pcids.push_back(tmp++);
					e.pcids_same_tracking_area_.push_back(pcids);
				}
				for(int j = 0; j < 5; ++j) {
					std::vector<int32_t> pcids;
					for(int k = 0; k < 5; ++k)
						pcids.push_back(tmp++);
					e.pcids_different_tracking_area_.push_back(pcids);
				}

				e.priority_ = tmp++;
				e.threshold_high_db_ = tmp++;
				e.threshold_low_db_ = tmp++;
				e.qrxlevmin_db_ = tmp++;

				si.eutran_neighbors_.push_back(e);
			}

			for(int i = 0; i < 5; ++i)
				si.extended_eutran_neighbors_.push_back(tmp++);
			gsm.layer_3_.si_2quater_ = si;
		}
		{
			layer_3_information::gsm_si_3 si;
			int32_t tmp = 0;

			si.is_decoded_ = true;
			si.plmn_.mcc_ = std::string("010");
			si.plmn_.mnc_ = std::string("230");
			si.location_area_code_ = tmp++;
			si.cell_id_ = tmp++;
			si.selection_parameters_.cell_reselect_offset_db_ = tmp++;
			si.cell_reselect_hysteresis_db_ = tmp++;
			si.is_2ter_present_ = rand() % 2 == 0;
			si.is_2quater_present_ = rand() % 2 == 0;
			gsm.layer_3_.si_3_ = si;
		}
		{
			layer_3_information::gsm_si_4 si;
			int32_t tmp = 0;

			si.is_decoded_ = true;
			si.plmn_.mcc_ = std::string("023");
			si.plmn_.mnc_ = tmp++;
			si.location_area_code_ = tmp++;
			si.cell_id_ = tmp++;
			si.selection_parameters_.cell_reselect_offset_db_ = tmp++;
			si.cell_reselect_hysteresis_db_ = tmp++;
			si.is_cbch_present_ = rand() % 2 == 0;
			gsm.layer_3_.si_4_ = si;
		}

		return gsm;
	}
	umts_data create_umts(int var = 0) {
		umts_data u;
		{
			basic_data &b = u;
			b.measurement_bandwidth_ = var++;
			b.measurement_frequency_ = var++;
			b.measurement_signal_level_ = var++;
			b.collection_round_ = var++;
			b.serial_ = "aldskfj";
			b.status_flags_ = var++;
			b.time_ = var++;
		}
		u.cpich_ = var++;
		u.ecio_ = var++;
		u.operating_band_ = rf_phreaker::UMTS_OPERATING_BAND_11;
		u.rscp_ = var++;
		u.uarfcn_ = var++;

		{
			layer_3_information::umts_mib_type s;
			s.is_decoded_ = true;
			s.plmn_.mcc_ = std::string("303");
			s.plmn_.mnc_ = std::string("2");
			s.multiple_plmns_.push_back(s.plmn_);
			s.multiple_plmns_.push_back(s.plmn_);
			u.layer_3_.mib_ = s;
		}
		{
			layer_3_information::umts_sib1_type s;
			s.is_decoded_ = true;
			s.lac_ = var++;
			u.layer_3_.sib1_ = s;
		}
		{
			layer_3_information::umts_sib3_type s;
			s.is_decoded_ = true;
			s.cid_ = var++;
			u.layer_3_.sib3_ = s;
		}
		{
			layer_3_information::umts_sib4_type s;
			s.is_decoded_ = true;
			s.cid_ = var++;
			u.layer_3_.sib4_ = s;
		}
		{
			layer_3_information::umts_sib11_type s;
			s.is_decoded_ = true;
			for(auto i = 0; i < 5; ++i)
				s.neighbor_intra_group_.push_back(i);
			for(auto i = 0; i < 5; ++i) {
				neighbor_inter t;
				t.cpich_ = var++;
				t.uarfcn_ = var++;
				s.neighbor_inter_group_.push_back(t);
			}
			for(auto i = 0; i < 5; ++i) {
				neighbor_inter_rat t;
				t.arfcn_ = var++;
				t.band_indicator_ = layer_3_information::dcs_1800_was_used;
				t.bsic_ = var++;
				t.qrx_lev_min_ = var++;
				s.neighbor_inter_rat_group_.push_back(t);
			}
			u.layer_3_.sib11_ = s;
		}
		{
			layer_3_information::umts_sib11_bis_type s;
			s.is_decoded_ = true;
			for(auto i = 0; i < 5; ++i)
				s.neighbor_intra_group_.push_back(i);
			for(auto i = 0; i < 5; ++i) {
				neighbor_inter t;
				t.cpich_ = var++;
				t.uarfcn_ = var++;
				s.neighbor_inter_group_.push_back(t);
			}
			for(auto i = 0; i < 5; ++i) {
				neighbor_inter_rat t;
				t.arfcn_ = var++;
				t.band_indicator_ = layer_3_information::dcs_1800_was_used;
				t.bsic_ = var++;
				t.qrx_lev_min_ = var++;
				s.neighbor_inter_rat_group_.push_back(t);
			}
			u.layer_3_.sib11_bis_ = s;
		}
		return u;
	}
	lte_data create_lte(int var = 0) {
		lte_data lte;
		{
			basic_data &b = lte;
			b.measurement_bandwidth_ = var++;
			b.measurement_frequency_ = var++;
			b.measurement_signal_level_ = var++;
			b.collection_round_ = var++;
			b.serial_ = "aldskfj";
			b.status_flags_ = var++;
			b.time_ = var++;
		}
		lte.cyclic_prefix_ = var++;
		lte.dl_bandwidth_ = var++;
		lte.earfcn_ = var++;
		lte.frame_number_ = var++;
		lte.num_antenna_ports_ = var++;
		lte.operating_band_ = rf_phreaker::LTE_OPERATING_BAND_22;
		lte.physical_cell_id_ = var++;
		lte.psch_id_ = var++;
		lte.psch_quality_ = var++;
		lte.rsrp_ = var++;
		lte.rsrq_ = var++;
		lte.rssi_ = var++;
		lte.ssch_id_ = var++;
		lte.ssch_quality_ = var++;

		{
			lte_sib1_type sib1;
			sib1.is_decoded_ = true;
			sib1.cell_id_ = 1000;
			sib1.tracking_area_code_ = 2000;
			for(int i = 0; i < 4; ++i) {
				layer_3_information::plmn p;
				p.mcc_ = std::string("310");
				p.mnc_ = std::to_string(i);
				sib1.multiple_plmn_.push_back(p);
			}
			sib1.si_window_length_ms_ = var++;
			layer_3_information::scheduling_info list;
			list.periodicity_in_frames_ = var++;
			list.sib_mapping_info_.push_back(SIB_1);
			list.sib_mapping_info_.push_back(SIB_3);
			sib1.scheduling_info_list_.push_back(list);
			list.periodicity_in_frames_ = var++;
			list.sib_mapping_info_.push_back(SIB_5);
			sib1.scheduling_info_list_.push_back(list);
			lte.layer_3_.sib1_ = sib1;
		}
		{
			lte_sib3_type sib;
			sib.is_decoded_ = true;
			sib.cell_reselection_serving_freq_info_.cell_reselection_priority_ = var++;
			sib.cell_reselection_serving_freq_info_.s_non_intra_search_ = var++;
			sib.cell_reselection_serving_freq_info_.threshold_serving_low_ = var++;
			sib.intra_freq_cell_reselection_info_.s_intra_search_ = var++;
			sib.s_intra_search_v920_.p_ = var++;
			sib.s_intra_search_v920_.q_ = var++;
			sib.s_non_intra_search_v920_.p_ = var++;
			sib.s_non_intra_search_v920_.q_ = var++;
			sib.threshold_serving_low_q_ = var++;
			lte.layer_3_.sib3_ = sib;
		}
		{
			lte_sib4_type sib;
			sib.is_decoded_ = true;
			sib.csg_physical_cellid_range_.range_ = var++;
			sib.csg_physical_cellid_range_.start_ = var++;
			physical_cellid_range tmp;
			tmp.range_ = var++; tmp.start_ = var++;
			sib.intra_freq_black_cell_list_.push_back(tmp);
			tmp.range_ = var++; tmp.start_ = var++;
			sib.intra_freq_black_cell_list_.push_back(tmp);
			neighbor_cell tmp1;
			tmp1.physical_cell_id_ = var++; tmp1.q_offset_cell_ = var++;
			sib.intra_freq_neighbor_cell_list_.push_back(tmp1);
			tmp1.physical_cell_id_ = var++; tmp1.q_offset_cell_ = var++;
			sib.intra_freq_neighbor_cell_list_.push_back(tmp1);
			lte.layer_3_.sib4_ = sib;
		}
		{
			lte_sib5_type sib;
			sib.is_decoded_ = true;
			inter_freq_carrier_freq_info tmp;
			tmp.allowed_measurement_bandwidth_ = var++;
			tmp.cell_reselection_priority_ = var++;
			tmp.downlink_arfcn_value_eutra_ = var++;
			tmp.presence_antenna_port_1_ = true;
			tmp.q_offset_freq_ = var++;
			tmp.q_rx_lev_min_ = var++;
			tmp.threshold_x_high_ = var++;
			tmp.threshold_x_high_q_r9_ = var++;
			tmp.threshold_x_low_ = var++;
			tmp.threshold_x_low_q_r9_ = var++;
			physical_cellid_range tmp1;
			tmp1.range_ = var++; tmp1.start_ = var++;
			tmp.inter_freq_black_cell_list_.push_back(tmp1);
			tmp1.range_ = var++; tmp1.start_ = var++;
			tmp.inter_freq_black_cell_list_.push_back(tmp1);
			neighbor_cell tmp2;
			tmp2.physical_cell_id_ = var++; tmp2.q_offset_cell_ = var++;
			tmp.inter_freq_neighbor_cell_list_.push_back(tmp2);
			tmp2.physical_cell_id_ = var++; tmp2.q_offset_cell_ = var++;
			tmp.inter_freq_neighbor_cell_list_.push_back(tmp2);
			sib.inter_freq_carrier_info_list_.push_back(tmp);
			lte.layer_3_.sib5_ = sib;
		}
		{
			lte_sib6_type sib;
			sib.is_decoded_ = true;
			layer_3_information::carrier_freq_utra tmp;
			tmp.arfcn_value_utra_ = var++;
			tmp.cell_reselection_priority_ = var++;
			tmp.threshold_x_high_ = var++;
			tmp.threshold_x_high_q_r9_ = var++;
			tmp.threshold_x_low_ = var++;
			tmp.threshold_x_low_q_r9_ = var++;
			sib.carrier_freq_list_utra_fdd_.push_back(tmp);

			tmp.arfcn_value_utra_ = var++;
			tmp.cell_reselection_priority_ = var++;
			tmp.threshold_x_high_ = var++;
			tmp.threshold_x_high_q_r9_ = var++;
			tmp.threshold_x_low_ = var++;
			tmp.threshold_x_low_q_r9_ = var++;
			sib.carrier_freq_list_utra_tdd_.push_back(tmp);
			lte.layer_3_.sib6_ = sib;
		}
		{
			lte_sib7_type sib;
			sib.is_decoded_ = true;
			carrier_freqs_info_geran tmp;
			tmp.carrier_freqs_.band_indicator_ = layer_3_information::dcs_1800_was_used;
			tmp.carrier_freqs_.following_arfcns_.push_back(var);
			tmp.carrier_freqs_.starting_arfcn_ = var++;
			tmp.carrier_freqs_.following_arfcns_.push_back(var++);
			tmp.common_info_.cell_reselection_priority_ = var++;
			tmp.common_info_.threshold_x_high_ = var++;
			tmp.common_info_.threshold_x_low_ = var++;
			sib.carrier_freqs_info_list_geran_.push_back(tmp);
			lte.layer_3_.sib7_ = sib;
		}
		{
			lte_sib8_type sib;
			sib.is_decoded_ = true;
			neighbor_cell_cdma_2000 tmp;
			tmp.band_ = layer_3_information::bc4;
			neighbor_cells_per_band_class_cdma_2000 tmp1;
			tmp1.arfcn_value_cmda_2000_ = var++;
			tmp1.physical_cell_ids_.push_back(var++);
			tmp1.physical_cell_ids_.push_back(var++);
			tmp.neighbor_cells_per_freq_list_.push_back(tmp1);
			sib.parameters_1xrtt_.neighbor_cell_list_.push_back(tmp);
			tmp.neighbor_cells_per_freq_list_.clear();
			tmp1.physical_cell_ids_.clear();
			tmp.band_ = layer_3_information::bc3;
			tmp1.arfcn_value_cmda_2000_ = var++;
			tmp1.physical_cell_ids_.push_back(var++);
			tmp1.physical_cell_ids_.push_back(var++);
			tmp.neighbor_cells_per_freq_list_.push_back(tmp1);
			sib.parameters_hrpd_.neighbor_cell_list_.push_back(tmp);
			lte.layer_3_.sib8_ = sib;
		}
		return lte;
	}

	hardware h_;
	gps gps_;
	std::vector<gsm_data> gsm_;
	std::vector<umts_data> umts_;
	std::vector<lte_data> lte_;
};
