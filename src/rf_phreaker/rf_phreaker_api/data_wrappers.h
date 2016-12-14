#pragma once

#include <list>
#include <vector>
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_utility.h"


namespace rf_phreaker { namespace api {


template<typename Wrap, typename External>
class vector_wrap
{
public:
	vector_wrap() {}
	vector_wrap(vector_wrap &&t)
		: buf_(std::move(t.buf_)) {}
	vector_wrap(const std::vector<External> &t) {
		for(auto &i : t) {
			buf_.push_back(Wrap(i).buf_);
		}
	}
	vector_wrap& operator=(vector_wrap t) {
		swap(std::move(t));
		return *this;
	} 
	void swap(vector_wrap &&t) {
		std::swap(buf_, t.buf_);
	}
	typename Wrap::buf_type* get() { return buf_.empty() ? nullptr : &buf_.at(0); }
	size_t size() { return buf_.size(); }
	std::vector<typename Wrap::buf_type> buf_;
};

class frequency_path_wrap {
public:
	frequency_path_wrap(const frequency_path &t) {
		buf_.high_freq_ = t.high_freq_;
		buf_.low_freq_ = t.low_freq_;
	}
	rp_frequency_path buf_;
	typedef rp_frequency_path buf_type;
};

class hardware_wrap
{
public:
	hardware_wrap(const hardware &t) {
		copy_serial(t.serial_, buf_.serial_);
		buf_.device_communication_ = to_api_device_communication(t.device_communication_);
		buf_.frequency_correction_calibration_date_ = t.frequency_correction_calibration_date_;
		buf_.rf_calibration_date_ = t.rf_calibration_date_;
		buf_.num_frequency_paths_ = t.frequency_paths_.size();
		memset(buf_.frequency_paths_, 0, RP_FREQUENCY_PATH_SIZE * sizeof(rp_frequency_path));
		int i = 0;
		for(auto path = t.frequency_paths_.begin(); path != t.frequency_paths_.end(); ++path) {
			buf_.frequency_paths_[i].high_freq_ = path->high_freq_;
			buf_.frequency_paths_[i].low_freq_ = path->low_freq_;
			if(++i >= RP_FREQUENCY_PATH_SIZE) {
				buf_.num_frequency_paths_ = RP_FREQUENCY_PATH_SIZE;
				break;
			}
		};
		buf_.num_licenses_ = 0;
	}
	rp_device_info buf_;
	typedef rp_device_info buf_type;
};

class gps_wrap {
public:
	gps_wrap(const gps &t) {
		copy_serial(t.serial_, buf_.serial_);
		buf_.lock_ = t.lock_;
		buf_.coordinated_universal_time_ = t.coordinated_universal_time_;
		buf_.visible_satellites_ = t.visible_satellites_;
		buf_.tracking_satellites_ = t.tracking_satellites_;
		buf_.latitude_ = t.latitude_;
		buf_.longitude_ = t.longitude_;
		buf_.altitude_ = t.altitude_;
		buf_.angle_ = t.angle_;
		buf_.speed_ = t.speed_;
		buf_.dilution_of_precision_ = t.dilution_of_precision_;
		buf_.horizontal_accuracy_meters_ = t.horizontal_accuracy_meters_;
		buf_.vertical_accuracy_meters_ = t.vertical_accuracy_meters_;
		buf_.raw_status_ = t.raw_status_;
	}
	rp_gps buf_;
	typedef rp_gps buf_type;
};

class basic_wrap {
public:
	basic_wrap(const basic_data &t) {
		copy_serial(t.serial_, buf_.serial_);
		buf_.collection_round_ = t.collection_round_;
		buf_.carrier_frequency_ = t.carrier_frequency_;
		buf_.carrier_bandwidth_ = t.carrier_bandwidth_;
		buf_.carrier_signal_level_ = t.carrier_signal_level_;
		buf_.time_ = t.time_;
		buf_.status_flags_ = t.status_flags_;
	}
	rp_base buf_;
	typedef rp_base buf_type;
};

class gsm_wrap {
public:
	gsm_wrap(const gsm_data &t) {
		buf_.base_ = basic_wrap(t).buf_;
		buf_.arfcn_ = t.arfcn_;
		buf_.operating_band_ = to_api_operating_band(t.operating_band_);
		buf_.tdma_frame_number_ = t.tdma_frame_number_;
		buf_.bcch_signal_level_ = t.cell_signal_level_;
		buf_.ctoi_ = t.ctoi_;

		populate_raw_layer_3(raw_layer_3_, t.layer_3_.raw_layer_3_);
		buf_.layer_3_.num_raw_layer_3_ = raw_layer_3_.size();
		buf_.layer_3_.raw_layer_3_ = raw_layer_3_.data();

		buf_.layer_3_.si1_.is_decoded_ = t.layer_3_.si_1_.is_decoded_;
		buf_.layer_3_.si1_.band_indicator_ = to_api_band_indicator(t.layer_3_.si_1_.band_indicator_);

		si_2_num_same_tracking_ = 0;
		si_2_num_different_tracking_ = 0;
		buf_.layer_3_.si2_.is_decoded_ = t.layer_3_.si_2_.is_decoded_;
		buf_.layer_3_.si2_.bcch_allocation_indication_ = t.layer_3_.si_2_.gsm_ba_ind_;
		buf_.layer_3_.si2_.extension_indication_ = t.layer_3_.si_2_.bcch_neighbors_has_extension_;
		si2_bcch_neighbors_ = t.layer_3_.si_2_.bcch_neighbors_;
		buf_.layer_3_.si2_.num_bcch_neighbors_ = si2_bcch_neighbors_.size();
		buf_.layer_3_.si2_.bcch_neighbors_ = si2_bcch_neighbors_.data();

		buf_.layer_3_.si2_ter_.is_decoded_ = t.layer_3_.si_2ter_.is_decoded_;
		buf_.layer_3_.si2_ter_.bcch_neighbors_multiband_reporting_ = t.layer_3_.si_2ter_.bcch_neighbors_multiband_reporting_;
		buf_.layer_3_.si2_ter_.gsm_bcch_allocation_indication_ = t.layer_3_.si_2ter_.gsm_ba_ind_;
		buf_.layer_3_.si2_ter_.rest_octet_count_ = t.layer_3_.si_2ter_.rest_octet_count_;
		buf_.layer_3_.si2_ter_.rest_octet_index_ = t.layer_3_.si_2ter_.rest_octet_index_;

		populate(&buf_.layer_3_.si2_ter_.extended_bcch_neighbors_, buf_.layer_3_.si2_ter_.num_extended_bcch_neighbors_,
			si2_ter_extended_bcch_neighbors_, t.layer_3_.si_2ter_.extended_bcch_neighbors_);

		populate(&buf_.layer_3_.si2_ter_.utran_neighbors_, buf_.layer_3_.si2_ter_.num_utran_neighbors_,
			si2_ter_utran_neighbors_, si2_ter_utran_neighbors_sc_, t.layer_3_.si_2ter_.utran_neighbors_);


		buf_.layer_3_.si2_quater_.is_decoded_ = t.layer_3_.si_2quater_.is_decoded_;
		buf_.layer_3_.si2_quater_.gsm_bcch_allocation_indication_ = t.layer_3_.si_2quater_.gsm_ba_ind_;
		buf_.layer_3_.si2_quater_.p3g_bcch_allocation_indication_ = t.layer_3_.si_2quater_.p3g_ba_ind_;
		buf_.layer_3_.si2_quater_.rest_octet_count_ = t.layer_3_.si_2quater_.rest_octet_count_;
		buf_.layer_3_.si2_quater_.rest_octet_index_ = t.layer_3_.si_2quater_.rest_octet_index_;
		buf_.layer_3_.si2_quater_.utran_neighbor_cell_absolute_index_start_emr_ = t.layer_3_.si_2quater_.utran_neighbor_cell_absolute_index_start_emr_;
		buf_.layer_3_.si2_quater_.utran_neighbor_cell_index_start_3g_ = t.layer_3_.si_2quater_.utran_neighbor_cell_index_start_3g_;
	
		populate(&buf_.layer_3_.si2_quater_.utran_neighbors_, buf_.layer_3_.si2_quater_.num_utran_neighbors_,
			si2_quater_utran_neighbors_, si2_quater_utran_neighbors_sc_, t.layer_3_.si_2quater_.utran_neighbors_);

		populate(&buf_.layer_3_.si2_quater_.eutran_neighbors_, buf_.layer_3_.si2_quater_.num_eutran_neighbors_, si2_quater_eutran_neighbors_,
			si2_quater_pcids_allowed_, si2_quater_pcids_not_allowed_, si2_quater_same_tracking_, si2_quater_different_tracking_,
			t.layer_3_.si_2quater_.eutran_neighbors_);


		buf_.layer_3_.si3_.is_decoded_ = t.layer_3_.si_3_.is_decoded_;
		buf_.layer_3_.si3_.bs_ag_blks_res_ = t.layer_3_.si_3_.bs_ag_blks_res_;
		buf_.layer_3_.si3_.cell_id_ = t.layer_3_.si_3_.cell_id_;
		buf_.layer_3_.si3_.cell_reselect_hysteresis_db_ = t.layer_3_.si_3_.cell_reselect_hysteresis_db_;
		buf_.layer_3_.si3_.is_2quater_present_ = t.layer_3_.si_3_.is_2quater_present_;
		buf_.layer_3_.si3_.is_2ter_present_ = t.layer_3_.si_3_.is_2ter_present_;
		buf_.layer_3_.si3_.location_area_code_ = t.layer_3_.si_3_.location_area_code_;
		populate_plmn(buf_.layer_3_.si3_.plmn_, t.layer_3_.si_3_.plmn_);
		populate(buf_.layer_3_.si3_.selection_parameters_, t.layer_3_.si_3_.selection_parameters_);


		buf_.layer_3_.si4_.is_decoded_ = t.layer_3_.si_4_.is_decoded_;
		buf_.layer_3_.si4_.cell_id_ = t.layer_3_.si_4_.cell_id_;
		buf_.layer_3_.si4_.cell_reselect_hysteresis_db_ = t.layer_3_.si_4_.cell_reselect_hysteresis_db_;
		buf_.layer_3_.si4_.have_additional_param_in_si7_si8_ = t.layer_3_.si_4_.have_additional_param_in_si7_si8_;
		buf_.layer_3_.si4_.is_cbch_present_ = t.layer_3_.si_4_.is_cbch_present_;
		buf_.layer_3_.si4_.location_area_code_ = t.layer_3_.si_4_.location_area_code_;
		populate_plmn(buf_.layer_3_.si4_.plmn_, t.layer_3_.si_4_.plmn_);
		populate(buf_.layer_3_.si4_.selection_parameters_, t.layer_3_.si_4_.selection_parameters_);
	}

	void populate(int32_t **d, int32_t &num, std::vector<int32_t> &a, const std::vector<layer_3_information::bcch_neighbor> &t) {
		a = t;
		*d = a.data();
		num = a.size();
	}
	
	void populate(rp_gsm_utran_neighbor **d, int32_t &num, std::vector<rp_gsm_utran_neighbor> &a, std::vector<std::vector<int32_t>> &b, 
		const std::vector<layer_3_information::utran_neighbor> &t) {
		a.resize(t.size());
		b.resize(t.size());
		num = a.size();
		auto i = 0;
		for(const auto &j : t) {
			a[i].arfcn_ = j.arfcn_; 
			a[i].bandwidth_ = (rp_utran_bandwidth_type)j.bandwidth_;
			a[i].duplexing_ = (rp_duplex_type)j.duplexing_;
			b[i] = j.scrambling_codes_;
			a[i].num_scrambling_codes_ = b[i].size();
			a[i].scrambling_codes_ = b[i].data();
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_gsm_eutran_neighbor **d, int32_t &num, std::vector<rp_gsm_eutran_neighbor> &a, std::vector<std::vector<int32_t>> &allowed,
		std::vector<std::vector<int32_t>> &not_allowed, std::vector<rp_pcid_group> &same_tracking,
		std::vector<rp_pcid_group> &different_tracking, const std::vector<layer_3_information::eutran_neighbor> &t) {
		a.resize(t.size());
		allowed.resize(t.size());
		not_allowed.resize(t.size());
		same_tracking.resize(t.size());
		different_tracking.resize(t.size());

		auto i = 0;
		for(auto &j : t) {
			allowed[i] = j.pcids_allowed_;
			a[i].pcids_allowed_.num_pcids_ = allowed[i].size();
			a[i].pcids_allowed_.pcids_ = allowed[i].data();
			not_allowed[i] = j.pcids_not_allowed_;
			a[i].pcids_not_allowed_.num_pcids_ = not_allowed[i].size();
			a[i].pcids_not_allowed_.pcids_ = not_allowed[i].data();
			{
				//same_tracking.resize(j.pcids_same_tracking_area_.size());
				si2_quater_same_tracking_buf_.resize(j.pcids_same_tracking_area_.size());
				for(auto &k : j.pcids_same_tracking_area_) {
					si2_quater_same_tracking_buf_[si_2_num_same_tracking_] = k;
					same_tracking[i].num_pcids_ = si2_quater_same_tracking_buf_[si_2_num_same_tracking_].size();
					same_tracking[i].pcids_ = si2_quater_same_tracking_buf_[si_2_num_same_tracking_].data();
					++si_2_num_same_tracking_;
				}
				a[i].num_pcids_same_tracking_area_ = same_tracking.size();
				a[i].pcids_same_tracking_area_ = same_tracking.data();
			}
			{
				//different_tracking.resize(j.pcids_different_tracking_area_.size());
				si2_quater_different_tracking_buf_.resize(j.pcids_different_tracking_area_.size());
				for(auto &k : j.pcids_different_tracking_area_) {
					si2_quater_different_tracking_buf_[si_2_num_different_tracking_] = k;
					different_tracking[i].num_pcids_ = si2_quater_different_tracking_buf_[si_2_num_different_tracking_].size();
					different_tracking[i].pcids_ = si2_quater_different_tracking_buf_[si_2_num_different_tracking_].data();
					++si_2_num_different_tracking_;
				}
				a[i].num_pcids_different_tracking_area_ = different_tracking.size();
				a[i].pcids_different_tracking_area_ = different_tracking.data();
			}
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_gsm_selection_parameters &a, const layer_3_information::selection_parameters &t) {
		a.apply_infinity_offset_ = t.apply_infinity_offset_;
		a.cbq_ = t.cbq_;
		a.cell_reselect_offset_db_ = t.cell_reselect_offset_db_;
		a.penalty_time_seconds_ = t.penalty_time_seconds_;
		a.subtract_reselect_cell_offset_ignore_temp_offset_ = t.subtract_reselect_cell_offset_ignore_temp_offset_;
		a.temporary_offset_db_ = t.temporary_offset_db_;
	}
	
	rp_gsm buf_; 
	typedef rp_gsm buf_type;

	std::vector<rp_raw_layer_3> raw_layer_3_;
	std::vector<int32_t> si2_bcch_neighbors_;
	std::vector<int32_t> si2_ter_extended_bcch_neighbors_;
	std::vector<rp_gsm_utran_neighbor> si2_ter_utran_neighbors_;
	std::vector<std::vector<int32_t>> si2_ter_utran_neighbors_sc_;
	std::vector<int32_t> si2_quater_extended_bcch_neighbors_;
	std::vector<rp_gsm_utran_neighbor> si2_quater_utran_neighbors_;
	std::vector<std::vector<int32_t>> si2_quater_utran_neighbors_sc_;
	std::vector<rp_gsm_eutran_neighbor> si2_quater_eutran_neighbors_;
	std::vector<std::vector<int32_t>> si2_quater_pcids_not_allowed_;
	std::vector<std::vector<int32_t>> si2_quater_pcids_allowed_;
	std::vector<rp_pcid_group> si2_quater_same_tracking_;
	std::vector<rp_pcid_group> si2_quater_different_tracking_;
	std::vector<std::vector<int32_t>> si2_quater_same_tracking_buf_;
	std::vector<std::vector<int32_t>> si2_quater_different_tracking_buf_;
	int si_2_num_same_tracking_;
	int si_2_num_different_tracking_;
};

class umts_wrap {
public:
	umts_wrap(const umts_data &t) {
		buf_.base_ = basic_wrap(t).buf_;
		buf_.uarfcn_ = t.uarfcn_;
		buf_.operating_band_ = to_api_operating_band(t.operating_band_);
		buf_.cpich_ = t.cpich_;
		buf_.ecio_ = t.ecio_;
		buf_.rscp_ = t.rscp_;

		populate_raw_layer_3(raw_layer_3_, t.layer_3_.raw_layer_3_);
		buf_.layer_3_.num_raw_layer_3_ = raw_layer_3_.size();
		buf_.layer_3_.raw_layer_3_ = raw_layer_3_.data();

		buf_.layer_3_.mib_.is_decoded_ = t.layer_3_.mib_.is_decoded_;
		populate_plmn(buf_.layer_3_.mib_.plmn_, t.layer_3_.mib_.plmn_);
		populate_plmns(plmns_, t.layer_3_.mib_.multiple_plmns_);
		buf_.layer_3_.mib_.num_multiple_plmns_ = plmns_.size();
		buf_.layer_3_.mib_.multiple_plmns_ = plmns_.data();

		buf_.layer_3_.sib1_.is_decoded_ = t.layer_3_.sib1_.is_decoded_;
		buf_.layer_3_.sib1_.lac_ = t.layer_3_.sib1_.lac_;

		buf_.layer_3_.sib3_.is_decoded_ = t.layer_3_.sib3_.is_decoded_;
		buf_.layer_3_.sib3_.cid_ = t.layer_3_.sib3_.cid_;

		buf_.layer_3_.sib4_.is_decoded_ = t.layer_3_.sib4_.is_decoded_;
		buf_.layer_3_.sib4_.cid_ = t.layer_3_.sib4_.cid_;

		buf_.layer_3_.sib11_.is_decoded_ = t.layer_3_.sib11_.is_decoded_;
		sib11_intra_neighbors_ = t.layer_3_.sib11_.neighbor_intra_group_;
		buf_.layer_3_.sib11_.num_utran_intra_neighbor_cpichs_ = sib11_intra_neighbors_.size();
		buf_.layer_3_.sib11_.utran_intra_neighbor_cpichs_ = sib11_intra_neighbors_.data();
		populate(&buf_.layer_3_.sib11_.utran_inter_neighbors_, buf_.layer_3_.sib11_.num_utran_inter_neighbors_, sib11_utran_neighbors_,
			t.layer_3_.sib11_.neighbor_inter_group_);
		populate(&buf_.layer_3_.sib11_.gsm_inter_neighbors_, buf_.layer_3_.sib11_.num_gsm_inter_neighbors_, sib11_gsm_neighbors_,
			t.layer_3_.sib11_.neighbor_inter_rat_group_);

		buf_.layer_3_.sib11_bis_.is_decoded_ = t.layer_3_.sib11_bis_.is_decoded_;
		sib11_bis_intra_neighbors_ = t.layer_3_.sib11_bis_.neighbor_intra_group_;
		buf_.layer_3_.sib11_bis_.num_utran_intra_neighbor_cpichs_ = sib11_bis_intra_neighbors_.size();
		buf_.layer_3_.sib11_bis_.utran_intra_neighbor_cpichs_ = sib11_bis_intra_neighbors_.data();
		populate(&buf_.layer_3_.sib11_bis_.utran_inter_neighbors_, buf_.layer_3_.sib11_bis_.num_utran_inter_neighbors_, sib11_bis_utran_neighbors_,
			t.layer_3_.sib11_bis_.neighbor_inter_group_);
		populate(&buf_.layer_3_.sib11_bis_.gsm_inter_neighbors_, buf_.layer_3_.sib11_bis_.num_gsm_inter_neighbors_, sib11_bis_gsm_neighbors_,
			t.layer_3_.sib11_bis_.neighbor_inter_rat_group_);
	}

	void populate(rp_wcdma_utran_neighbor** d, int32_t &num, std::vector<rp_wcdma_utran_neighbor> a, const std::vector<layer_3_information::neighbor_inter> &t) {
		a.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			a[i].uarfcn_ = j.uarfcn_;
			a[i].cpich_ = j.cpich_;
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_wcdma_gsm_neighbor** d, int32_t &num, std::vector<rp_wcdma_gsm_neighbor> a, const std::vector<layer_3_information::neighbor_inter_rat> &t) {
		a.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			a[i].arfcn_ = j.arfcn_;
			a[i].band_indicator_ = (rp_band_indicator_type)j.band_indicator_;
			a[i].bsic_ = j.bsic_.to_uint16();
			a[i].qrx_lev_min_ = j.qrx_lev_min_ == layer_3_information::not_decoded_16 ? -1 : j.qrx_lev_min_;
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	rp_wcdma buf_;
	typedef rp_wcdma buf_type;

	std::vector<rp_raw_layer_3> raw_layer_3_;
	std::vector<rp_plmn> plmns_;
	std::vector<int32_t> sib11_intra_neighbors_;
	std::vector<rp_wcdma_utran_neighbor> sib11_utran_neighbors_;
	std::vector<rp_wcdma_gsm_neighbor> sib11_gsm_neighbors_;
	std::vector<int32_t> sib11_bis_intra_neighbors_;
	std::vector<rp_wcdma_utran_neighbor> sib11_bis_utran_neighbors_;
	std::vector<rp_wcdma_gsm_neighbor> sib11_bis_gsm_neighbors_;
};

class lte_wrap {
public:
	lte_wrap(const lte_data &t) {
		buf_.base_ = basic_wrap(t).buf_;
		buf_.earfcn_ = t.earfcn_;
		buf_.operating_band_ = to_api_operating_band(t.operating_band_);
		buf_.physical_cell_id_ = t.physical_cell_id_;
		buf_.rsrp_ = t.rsrp_;
		buf_.rsrq_ = t.rsrp_;
		buf_.rssi_ = t.rssi_;
		buf_.psch_id_ = t.psch_id_;
		buf_.psch_quality_ = t.psch_quality_;
		buf_.ssch_id_ = t.ssch_id_;
		buf_.ssch_quality_ = t.ssch_quality_;
		buf_.sync_quality_ = t.sync_quality_;
		buf_.cyclic_prefix_ = t.cyclic_prefix_;
		buf_.num_antenna_ports_ = t.num_antenna_ports_;
		buf_.downlink_bandwidth_ = t.dl_bandwidth_;
		buf_.frame_number_ = t.frame_number_;

		populate_raw_layer_3(raw_layer_3_, t.layer_3_.raw_layer_3_);
		buf_.layer_3_.num_raw_layer_3_ = raw_layer_3_.size();
		buf_.layer_3_.raw_layer_3_ = raw_layer_3_.data();

		buf_.layer_3_.sib1_.is_decoded_ = t.layer_3_.sib1_.is_decoded_;
		buf_.layer_3_.sib1_.cid_ = t.layer_3_.sib1_.cell_id_;
		buf_.layer_3_.sib1_.si_window_length_ms_ = t.layer_3_.sib1_.si_window_length_ms_;
		buf_.layer_3_.sib1_.tac_ = t.layer_3_.sib1_.tracking_area_code_;
		populate_plmns(plmns_, t.layer_3_.sib1_.multiple_plmn_);
		buf_.layer_3_.sib1_.num_multiple_plmns_ = plmns_.size();
		buf_.layer_3_.sib1_.multiple_plmns_ = plmns_.data();
		populate(&buf_.layer_3_.sib1_.scheduling_info_, buf_.layer_3_.sib1_.num_scheduling_info_, t.layer_3_.sib1_.scheduling_info_list_);

		buf_.layer_3_.sib3_.is_decoded_ = t.layer_3_.sib3_.is_decoded_;
		buf_.layer_3_.sib3_.cell_reselection_serving_freq_info_.cell_reselection_priority_ = t.layer_3_.sib3_.cell_reselection_serving_freq_info_.cell_reselection_priority_;
		buf_.layer_3_.sib3_.cell_reselection_serving_freq_info_.s_non_intra_search_ = (int32_t)t.layer_3_.sib3_.cell_reselection_serving_freq_info_.s_non_intra_search_.reselection_threshold();
		buf_.layer_3_.sib3_.cell_reselection_serving_freq_info_.threshold_serving_low_ = (int32_t)t.layer_3_.sib3_.cell_reselection_serving_freq_info_.threshold_serving_low_.reselection_threshold();
		buf_.layer_3_.sib3_.intra_freq_cell_reselection_info_s_intra_search_ = (int32_t)t.layer_3_.sib3_.intra_freq_cell_reselection_info_.s_intra_search_.reselection_threshold();
		buf_.layer_3_.sib3_.s_intra_search_v920_.p_ = (int32_t)t.layer_3_.sib3_.s_intra_search_v920_.p_.reselection_threshold();
		buf_.layer_3_.sib3_.s_intra_search_v920_.q_ = (int32_t)t.layer_3_.sib3_.s_intra_search_v920_.q_;
		buf_.layer_3_.sib3_.s_non_intra_search_v920_.p_ = (int32_t)t.layer_3_.sib3_.s_non_intra_search_v920_.p_.reselection_threshold();
		buf_.layer_3_.sib3_.s_non_intra_search_v920_.q_ = (int32_t)t.layer_3_.sib3_.s_non_intra_search_v920_.q_;
		buf_.layer_3_.sib3_.threshold_serving_low_q_ = t.layer_3_.sib3_.threshold_serving_low_q_;


		buf_.layer_3_.sib4_.is_decoded_ = t.layer_3_.sib4_.is_decoded_;
		populate(&buf_.layer_3_.sib4_.intra_freq_neighbor_cell_list_, buf_.layer_3_.sib4_.num_intra_freq_neighbor_cell_list_, sib4_neighbor_cells_, 
			t.layer_3_.sib4_.intra_freq_neighbor_cell_list_);
		populate(&buf_.layer_3_.sib4_.intra_freq_black_cell_list_, buf_.layer_3_.sib4_.num_intra_freq_black_cell_list_, sib4_physical_cellid_ranges_, 
			t.layer_3_.sib4_.intra_freq_black_cell_list_);
		buf_.layer_3_.sib4_.csg_physical_cellid_range_.start_ = t.layer_3_.sib4_.csg_physical_cellid_range_.start_;
		buf_.layer_3_.sib4_.csg_physical_cellid_range_.range_ = t.layer_3_.sib4_.csg_physical_cellid_range_.range_;

		buf_.layer_3_.sib5_.is_decoded_ = t.layer_3_.sib5_.is_decoded_;
		populate(&buf_.layer_3_.sib5_.inter_freq_carrier_info_list_, buf_.layer_3_.sib5_.num_inter_freq_carrier_info_list_, sib5_inter_freq_carrier_freq_info_,
			t.layer_3_.sib5_.inter_freq_carrier_info_list_);

		buf_.layer_3_.sib6_.is_decoded_ = t.layer_3_.sib6_.is_decoded_;
		populate(&buf_.layer_3_.sib6_.carrier_freq_list_utra_fdd_, buf_.layer_3_.sib6_.num_carrier_freq_list_utra_fdd_, sib6_tdd_,
			t.layer_3_.sib6_.carrier_freq_list_utra_fdd_);
		populate(&buf_.layer_3_.sib6_.carrier_freq_list_utra_tdd_, buf_.layer_3_.sib6_.num_carrier_freq_list_utra_tdd_, sib6_tdd_,
			t.layer_3_.sib6_.carrier_freq_list_utra_tdd_);

		buf_.layer_3_.sib7_.is_decoded_ = t.layer_3_.sib7_.is_decoded_;
		populate(&buf_.layer_3_.sib7_.carrier_freqs_info_list_geran_, buf_.layer_3_.sib7_.num_carrier_freqs_info_list_geran_, sib7_geran_,
			t.layer_3_.sib7_.carrier_freqs_info_list_geran_);
		
		buf_.layer_3_.sib8_.is_decoded_ = t.layer_3_.sib8_.is_decoded_;
		populate(buf_.layer_3_.sib8_.parameters_1xrtt_, sib8_cells_hrpd_, sib8_cpb_class_xxrt_, t.layer_3_.sib8_.parameters_1xrtt_);
		populate(buf_.layer_3_.sib8_.parameters_hrpd_, sib8_cells_hrpd_, sib8_cpb_class_hrpd_, t.layer_3_.sib8_.parameters_hrpd_);
	}

	void populate(rp_lte_scheduling_info **d, int32_t &num, const std::vector<layer_3_information::scheduling_info> &t) {
		scheduling_info_.resize(t.size());
		scheduling_sibs_.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			scheduling_info_[i].periodicity_in_frames_ = j.periodicity_in_frames_;
			scheduling_sibs_[i] = (std::vector<rp_lte_sib_type>&)j.sib_mapping_info_;
			scheduling_info_[i].num_sibs_ = scheduling_sibs_[i].size();
			scheduling_info_[i].sibs = scheduling_sibs_[i].data();
			++i;
		}
		*d = scheduling_info_.data();
		num = scheduling_info_.size();
	}

	void populate(rp_lte_neighbor_cell **d, int32_t &num, std::vector<rp_lte_neighbor_cell> &a, const std::vector<layer_3_information::neighbor_cell> &t) {
		a.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			a[i].physical_cell_id_ = j.physical_cell_id_;
			a[i].q_offset_cell_ = j.q_offset_cell_;
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_lte_physical_cellid_range **d, int32_t &num, std::vector<rp_lte_physical_cellid_range> &a, const std::vector<layer_3_information::physical_cellid_range> &t) {
		a.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			a[i].range_ = j.range_;
			a[i].start_ = j.start_;
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_lte_inter_freq_carrier_freq_info **d, int32_t &num, std::vector<rp_lte_inter_freq_carrier_freq_info> &a, const std::vector<layer_3_information::inter_freq_carrier_freq_info> &t) {
		sib5_inter_freq_carrier_freq_info_.resize(t.size());
		sib5_neighbor_cells_.resize(t.size());
		sib5_physical_cellid_ranges_.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			a[i].allowed_measurement_bandwidth_ = j.allowed_measurement_bandwidth_;
			a[i].cell_reselection_priority_ = j.cell_reselection_priority_;
			a[i].downlink_arfcn_value_eutra_ = j.downlink_arfcn_value_eutra_;
			a[i].presence_antenna_port_1_ = j.presence_antenna_port_1_;
			a[i].q_offset_freq_ = j.q_offset_freq_;
			a[i].q_rx_lev_min_ = j.q_rx_lev_min_;
			a[i].threshold_x_high_ = j.threshold_x_high_.reselection_threshold();
			a[i].threshold_x_high_q_r9_ = j.threshold_x_high_q_r9_;
			a[i].threshold_x_low_ = j.threshold_x_low_.reselection_threshold();
			a[i].threshold_x_low_q_r9_ = j.threshold_x_low_q_r9_;
			populate(&a[i].inter_freq_neighbor_cell_list_, a[i].num_inter_freq_neighbor_cell_list_, sib5_neighbor_cells_[i], j.inter_freq_neighbor_cell_list_);
			populate(&a[i].inter_freq_black_cell_list_, a[i].num_inter_freq_black_cell_list_, sib5_physical_cellid_ranges_[i], j.inter_freq_black_cell_list_);
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_lte_carrier_freq_utra **d, int32_t &num, std::vector<rp_lte_carrier_freq_utra> &a, const std::vector<layer_3_information::carrier_freq_utra> &t) {
		a.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			a[i].arfcn_value_utra_ = j.arfcn_value_utra_;
			a[i].cell_reselection_priority_ = j.cell_reselection_priority_;
			a[i].threshold_x_high_ = j.threshold_x_high_.reselection_threshold();
			a[i].threshold_x_high_q_r9_ = j.threshold_x_high_q_r9_;
			a[i].threshold_x_low_ = j.threshold_x_low_.reselection_threshold();
			a[i].threshold_x_low_q_r9_ = j.threshold_x_low_q_r9_;
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_lte_carrier_freqs_info_geran **d, int32_t &num, std::vector<rp_lte_carrier_freqs_info_geran> &a, const std::vector<layer_3_information::carrier_freqs_info_geran> &t) {
		a.resize(t.size());
		auto i = 0;
		for(auto &j : t) {
			a[i].common_info_.cell_reselection_priority_ = j.common_info_.cell_reselection_priority_;
			a[i].common_info_.threshold_x_high_ = j.common_info_.threshold_x_high_.reselection_threshold();
			a[i].common_info_.threshold_x_low_ = j.common_info_.threshold_x_low_.reselection_threshold();
			a[i].carrier_freqs_.band_indicator_ = (rp_band_indicator_type)j.carrier_freqs_.band_indicator_;
			sib7_arfcns_[i] = j.carrier_freqs_.following_arfcns_;
			a[i].carrier_freqs_.arfcns_ = sib7_arfcns_[i].data();
			a[i].carrier_freqs_.num_arfcns_ = sib7_arfcns_[i].size();
			++i;
		}
		*d = a.data();
		num = a.size();
	}

	void populate(rp_lte_cell_reselection_parameters_cmda_2000 &d, std::list<std::vector<rp_lte_neighbor_cell_cdma_2000>> &b,
		std::list<std::vector<rp_lte_neighbor_cells_per_band_class_cdma_2000>> &c, const layer_3_information::cell_reselection_parameters_cmda_2000 &t) {
		populate(&d.neighbor_cell_list_, d.num_neighbor_cell_list_, b, c, t.neighbor_cell_list_);
	}

	void populate(rp_lte_neighbor_cell_cdma_2000 **d, int32_t &num, std::list<std::vector<rp_lte_neighbor_cell_cdma_2000>> &a, std::list<std::vector<rp_lte_neighbor_cells_per_band_class_cdma_2000>> &c, const std::vector<layer_3_information::neighbor_cell_cdma_2000> &t) {
		a.emplace_back();
		auto &i = a.back();
		for(auto &j : t) {
			rp_lte_neighbor_cell_cdma_2000 q;
			q.band_ = (rp_lte_band_class_cmda_2000_type)j.band_;
			populate(&q.neighbor_cells_per_freq_list_, q.num_neighbor_cells_per_freq_list_, c, j.neighbor_cells_per_freq_list_);
			i.push_back(q);
		}
		*d = a.back().data();
		num = a.back().size();
	}

	void populate(rp_lte_neighbor_cells_per_band_class_cdma_2000 **d, int32_t &num, std::list<std::vector<rp_lte_neighbor_cells_per_band_class_cdma_2000>> &a, const std::vector<layer_3_information::neighbor_cells_per_band_class_cdma_2000> &t) {
		a.emplace_back();
		auto &i = a.back();
		for(auto &j : t) {
			rp_lte_neighbor_cells_per_band_class_cdma_2000 q;
			q.arfcn_value_cmda_2000_ = j.arfcn_value_cmda_2000_;
			q.num_physical_cell_ids_ = j.physical_cell_ids_.size();
			q.physical_cell_ids_ = (int32_t*)j.physical_cell_ids_.data(); // This really should be copied.
			i.push_back(q);
		}
		*d = a.back().data();
		num = a.back().size();
	}

	rp_lte buf_;
	typedef rp_lte buf_type;

	std::vector<rp_raw_layer_3> raw_layer_3_;
	std::vector<rp_plmn> plmns_;
	std::vector<rp_lte_scheduling_info> scheduling_info_;
	std::vector<std::vector<rp_lte_sib_type>> scheduling_sibs_;
	std::vector<rp_lte_neighbor_cell> sib4_neighbor_cells_;
	std::vector<rp_lte_physical_cellid_range> sib4_physical_cellid_ranges_;
	std::vector<std::vector<rp_lte_neighbor_cell>> sib5_neighbor_cells_;
	std::vector<std::vector<rp_lte_physical_cellid_range>> sib5_physical_cellid_ranges_;
	std::vector<rp_lte_inter_freq_carrier_freq_info> sib5_inter_freq_carrier_freq_info_;
	std::vector<rp_lte_carrier_freq_utra> sib6_fdd_;
	std::vector<rp_lte_carrier_freq_utra> sib6_tdd_;
	std::vector<rp_lte_carrier_freqs_info_geran> sib7_geran_;
	std::vector<std::vector<int32_t>> sib7_arfcns_;
	std::list<std::vector<rp_lte_neighbor_cell_cdma_2000>> sib8_cells_hrpd_;
	std::list<std::vector<rp_lte_neighbor_cell_cdma_2000>> sib8_cells_xxrt_;
	std::list<std::vector<rp_lte_neighbor_cells_per_band_class_cdma_2000>> sib8_cpb_class_hrpd_;
	std::list<std::vector<rp_lte_neighbor_cells_per_band_class_cdma_2000>> sib8_cpb_class_xxrt_;
};




}}