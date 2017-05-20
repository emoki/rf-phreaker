#pragma once

#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker.pb.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/scanner/measurement_info.h"

namespace rf_phreaker { namespace protobuf {

template<typename Pb>
class pb {
public:
	pb() : pb_(new Pb) {}
	pb(Pb &&p) { std::swap(pb_, p.pb_); std::swap(buf_, p.buf_); }
	const std::string &serialize() {
		pb_->SerializeToString(&buf_);
		return buf_;
	}
	const int8_t* to_bytes() const {
		return (int8_t*)buf_.data();
	}
	size_t size() const {
		return buf_.size();
	}
	typename Pb&  protobuf() { return *pb_.get(); }
	const typename Pb&  protobuf_const() const { return *pb_.get(); }
protected:
	std::unique_ptr<Pb> pb_;
	std::string buf_;
};

class message_pb : public pb<rp_message> {
public:
	message_pb() {}
	message_pb(const ::rp_status s, const std::string& str) {
		populate(s, str, pb_.get());
	}
	void populate(const ::rp_status s, const std::string& str) {
		populate(s, str, pb_.get());
	}
	static void populate(const ::rp_status s, const std::string& str, rp_message *pb) {
		pb->Clear();
		pb->set_status((rp_status)s);
		pb->set_msg(str.c_str());
	}
};

class log_pb : public pb<rp_log> {
public:
	log_pb() {}
	log_pb(const std::string& str) {
		populate(str, pb_.get());
	}
	void populate(const std::string& str) {		
		populate(str, pb_.get());
	}
	static void populate(const std::string& str, rp_log *pb) {
		pb->Clear();
		pb->set_msg(str.c_str());
	}
};

class device_info_pb : public pb<rp_device_info> {
public:
	device_info_pb() {}
	device_info_pb(const hardware &t) {
		populate(t, pb_.get());
	}
	void populate(const hardware &t) {
		populate(t, pb_.get());
	}
	hardware get_hardware() {
		hardware t;
		populate(*pb_.get(), t);
		return t;
	}
	static void populate(const rp_device_info &pb, hardware &t) {
		t.serial_ = pb.serial();
		t.device_communication_ = (rf_phreaker::device_communication)pb.device_communication();
		t.frequency_correction_calibration_date_ = pb.frequency_correction_calibration_date();
		t.rf_calibration_date_ = pb.rf_calibration_date();
		t.frequency_paths_.resize(pb.frequency_paths_size());
		auto j = 0;
		for(auto &i : t.frequency_paths_) {
			auto k = pb.frequency_paths().Get(j++);
			i.low_freq_ = k.low_freq();
			i.high_freq_ = k.high_freq();
		}
	}
	static void populate(const hardware &t, rp_device_info *pb) {
		pb->Clear();
		pb->set_serial(t.serial_);
		pb->set_device_communication((rp_device_communication)t.device_communication_);
		pb->set_frequency_correction_calibration_date(t.frequency_correction_calibration_date_);
		pb->set_rf_calibration_date(t.rf_calibration_date_);
		for(auto &i : t.frequency_paths_) {
			auto k = pb->add_frequency_paths();
			k->set_low_freq(i.low_freq_);
			k->set_high_freq(i.high_freq_);
		}
	}
};

class gps_pb : public pb<rp_gps> {
public:
	gps_pb() {}
	gps_pb(const gps &t) {
		populate(t, pb_.get());
	}
	void populate(const gps &t) {
		populate(t, pb_.get());
	}
	gps get_gps() {
		gps t;
		populate(*pb_.get(), t);
		return t;
	}
	static void populate(const rp_gps &pb, gps &t) {
		t.serial_ = pb.serial();
		t.lock_ = pb.lock();
		t.coordinated_universal_time_ = pb.coordinated_universal_time();
		t.visible_satellites_ = pb.visible_satellites();
		t.tracking_satellites_ = pb.tracking_satellites();
		t.latitude_ = pb.latitude();
		t.longitude_ = pb.longitude();
		t.altitude_ = pb.altitude();
		t.angle_ = pb.angle();
		t.speed_ = pb.speed();
		t.dilution_of_precision_ = pb.dilution_of_precision();
		t.horizontal_accuracy_meters_ = pb.horizontal_accuracy_meters();
		t.vertical_accuracy_meters_ = pb.vertical_accuracy_meters();
		t.raw_status_ = pb.raw_status();
		t.satellites_.resize(pb.satellites_size());
		auto j = 0;
		for(auto &i : t.satellites_) {
			auto sat = pb.satellites().Get(j++);
			i.prn_ = sat.prn();
			i.snr_ = sat.snr();
			i.elevation_ = sat.elevation();
			i.azimuth_ = sat.azimuth();
		}
	}
	static void populate(const gps &t, rp_gps *pb) {
		pb->Clear();
		pb->set_serial(t.serial_);
		pb->set_lock(t.lock_);
		pb->set_coordinated_universal_time(t.coordinated_universal_time_);
		pb->set_visible_satellites(t.visible_satellites_);
		pb->set_tracking_satellites(t.tracking_satellites_);
		pb->set_latitude(t.latitude_);
		pb->set_longitude(t.longitude_);
		pb->set_altitude(t.altitude_);
		pb->set_angle(t.angle_);
		pb->set_speed(t.speed_);
		pb->set_dilution_of_precision(t.dilution_of_precision_);
		pb->set_horizontal_accuracy_meters(t.horizontal_accuracy_meters_);
		pb->set_vertical_accuracy_meters(t.vertical_accuracy_meters_);
		pb->set_raw_status(t.raw_status_);
		for(auto &i : t.satellites_) {
			auto k = pb->add_satellites();
			k->set_prn(i.prn_);
			k->set_snr(i.snr_);
			k->set_elevation(i.elevation_);
			k->set_azimuth(i.azimuth_);
		}
	}
};

inline void set_raw_layer_3(const layer_3_information::bit_stream &t, rp_raw_layer_3 *pb) {
	pb->set_bytes(t.bytes_.data(), t.bytes_.size());
	pb->set_unused_bits(t.unused_bits_);
}

inline void set_raw_layer_3(const rp_raw_layer_3 &pb, layer_3_information::bit_stream &t) {
	t.bytes_.resize(pb.ByteSize());
	std::copy(pb.bytes().begin(), pb.bytes().end(), t.bytes_.begin());
	t.unused_bits_ = pb.unused_bits();
}

inline void set_plmn(const layer_3_information::plmn &t, rp_plmn *pb) {
	pb->set_mcc(t.mcc_.to_string());
	pb->set_mnc(t.mnc_.to_string());
}

inline void set_plmn(const rp_plmn &pb, layer_3_information::plmn &t) {
	t.mcc_ = pb.mcc();
	t.mnc_ = pb.mnc();
}

class base_pb : public pb<rp_base> {
public:
	base_pb() {}
	base_pb(const basic_data &t) {
		populate(t, pb_.get());
	}
	void populate(const basic_data &t) {
		populate(t, pb_.get());
	}
	basic_data get_basic_data() {
		basic_data t;
		populate(*pb_.get(), t);
		return t;
	}
	static void populate(const rp_base &pb, basic_data &t) {
		t.serial_ = pb.serial();
		t.collection_round_ = pb.collection_round();
		t.measurement_frequency_ = pb.measurement_frequency();
		t.measurement_bandwidth_ = pb.measurement_bandwidth();
		t.measurement_signal_level_ = pb.measurement_signal_level();
		t.time_ = pb.time();
		t.status_flags_ = pb.status_flags();
	}
	static void populate(const basic_data &t, rp_base *pb) {
		pb->Clear();
		pb->set_serial(t.serial_);
		pb->set_collection_round(t.collection_round_);
		pb->set_measurement_frequency(t.measurement_frequency_);
		pb->set_measurement_bandwidth(t.measurement_bandwidth_);
		pb->set_measurement_signal_level(t.measurement_signal_level_);
		pb->set_time(t.time_);
		pb->set_status_flags(t.status_flags_);
	}
};

class gsm_pb : public pb<rp_gsm> {
public:
	gsm_pb() {}
	gsm_pb(const gsm_data &t) {
		populate(t, pb_.get());
	}
	void populate(const gsm_data &t) {
		populate(t, pb_.get());
	}
	gsm_data get_gsm_data() {
		gsm_data t;
		populate(*pb_.get(), t);
		return t;
	}
	static void populate(const rp_gsm &pb, gsm_data &t) {
		base_pb::populate(pb.base(), t);
		t.arfcn_ = pb.arfcn();
		t.operating_band_ = (rf_phreaker::operating_band)pb.operating_band();
		t.bsic_ = pb.bsic();
		t.tdma_frame_number_ = pb.tdma_frame_number();
		t.cell_signal_level_ = pb.bcch_signal_level();
		t.ctoi_ = pb.ctoi();
		if(pb.has_layer_3()) {
			auto l = pb.layer_3();
			if(l.raw_layer_3_size()) {
				t.layer_3_.raw_layer_3_.resize(l.raw_layer_3_size());
				auto j = 0;
				for(auto &i : t.layer_3_.raw_layer_3_)
					set_raw_layer_3(l.raw_layer_3().Get(j++), i);
			}
			if(l.has_si1()) populate(l.si1(), t.layer_3_.si_1_); else t.layer_3_.si_1_.is_decoded_ = false;
			if(l.has_si2()) populate(l.si2(), t.layer_3_.si_2_); else t.layer_3_.si_2_.is_decoded_ = false;
			if(l.has_si2_bis()) populate(l.si2_bis(), t.layer_3_.si_2bis_); else t.layer_3_.si_2bis_.is_decoded_ = false;
			if(l.has_si2_ter()) populate(l.si2_ter(), t.layer_3_.si_2ter_); else t.layer_3_.si_2ter_.is_decoded_ = false;
			if(l.has_si2_quater()) populate(l.si2_quater(), t.layer_3_.si_2quater_); else t.layer_3_.si_2quater_.is_decoded_ = false;
			if(l.has_si3()) populate(l.si3(), t.layer_3_.si_3_); else t.layer_3_.si_3_.is_decoded_ = false;
			if(l.has_si4()) populate(l.si4(), t.layer_3_.si_4_); else t.layer_3_.si_4_.is_decoded_ = false;
		}
	}
	static void populate(const rp_gsm_si1 &pb, layer_3_information::gsm_si_1 &t) {
		t.is_decoded_ = true;
		t.band_indicator_ = (layer_3_information::band_indicator_type)pb.band_indicator();
	}
	static void populate(const rp_gsm_si2 &pb, layer_3_information::gsm_si_2 &t) {
		t.is_decoded_ = true;
		t.bcch_neighbors_.resize(pb.bcch_neighbors_size());
		auto j = 0;
		for(auto &i : t.bcch_neighbors_)
			i = pb.bcch_neighbors().Get(j++);
		t.bcch_neighbors_has_extension_ = pb.extension_indication();
		t.gsm_ba_ind_ = pb.bcch_allocation_indication();
	}
	static void populate(const rp_gsm_si2_bis &pb, layer_3_information::gsm_si_2bis &t) {
		t.is_decoded_ = true;
		t.extended_bcch_neighbors_.resize(pb.extended_bcch_neighbors_size());
		auto j = 0;
		for(auto &i : t.extended_bcch_neighbors_)
			i = pb.extended_bcch_neighbors().Get(j++);
		t.bcch_neighbors_has_extension_ = pb.extension_indication();
		t.gsm_ba_ind_ = pb.bcch_allocation_indication();
		t.rest_octet_count_ = pb.rest_octet_count();
		t.rest_octet_index_ = pb.rest_octet_index();
	}
	static void populate(const rp_gsm_si2_ter &pb, layer_3_information::gsm_si_2ter &t) {
		t.is_decoded_ = true;
		t.extended_bcch_neighbors_.resize(pb.extended_bcch_neighbors_size());
		auto j = 0;
		for(auto &i : t.extended_bcch_neighbors_)
			i = pb.extended_bcch_neighbors().Get(j++);
		t.gsm_ba_ind_ = pb.gsm_bcch_allocation_indication();
		t.bcch_neighbors_multiband_reporting_ = pb.bcch_neighbors_multiband_reporting();
		t.utran_neighbors_.resize(pb.utran_neighbors_size());
		j = 0;
		for(auto &i : t.utran_neighbors_) {
			populate(pb.utran_neighbors().Get(j++), i);
		}
		t.rest_octet_count_ = pb.rest_octet_count();
		t.rest_octet_index_ = pb.rest_octet_index();
	}
	static void populate(const rp_gsm_utran_neighbor &pb, layer_3_information::utran_neighbor &t) {
		t.duplexing_ = (layer_3_information::duplex_type)pb.duplexing();
		t.arfcn_ = pb.arfcn();
		t.bandwidth_ = (layer_3_information::utran_bandwidth_type)pb.bandwidth();
		t.scrambling_codes_.resize(pb.scrambling_codes_size());
		auto j = 0;
		for(auto &i : t.scrambling_codes_)
			i = pb.scrambling_codes().Get(j++);
	}
	static void populate(const rp_gsm_si2_quater &pb, layer_3_information::gsm_si_2quater &t) {
		t.is_decoded_ = true;
		t.gsm_ba_ind_ = pb.gsm_bcch_allocation_indication();
		t.p3g_ba_ind_ = pb.p3g_bcch_allocation_indication();
		t.utran_neighbor_cell_index_start_3g_ = pb.utran_neighbor_cell_index_start_3g();
		t.utran_neighbor_cell_absolute_index_start_emr_ = pb.utran_neighbor_cell_absolute_index_start_emr();
		t.eutran_neighbors_.resize(pb.eutran_neighbors_size());
		auto j = 0;
		for(auto &i : t.eutran_neighbors_) {
			populate(pb.eutran_neighbors().Get(j++), i);
		}
		t.utran_neighbors_.resize(pb.utran_neighbors_size());
		j = 0;
		for(auto &i : t.utran_neighbors_) {
			populate(pb.utran_neighbors().Get(j++), i);
		}
		t.rest_octet_count_ = pb.rest_octet_count();
		t.rest_octet_index_ = pb.rest_octet_index();
	}
	static void populate(const rp_gsm_eutran_neighbor &pb, layer_3_information::eutran_neighbor &t) {
		t.earfcn_ = pb.earfcn();
		t.bandwidth_ = (layer_3_information::eutran_bandwidth_type)pb.bandwidth();
		t.priority_ = pb.priority();
		t.threshold_high_db_ = pb.threshold_high_db();
		t.threshold_low_db_ = pb.threshold_low_db();
		t.qrxlevmin_db_ = pb.qrxlevmin_db();
		t.pcids_allowed_.resize(pb.pcids_allowed().pcids_size());
		auto j = 0;
		for(auto &i : t.pcids_allowed_) {
			i = pb.pcids_allowed().pcids().Get(j++);
		}
		t.pcids_not_allowed_.resize(pb.pcids_not_allowed().pcids_size());
		j = 0;
		for(auto &i : t.pcids_not_allowed_) {
			i = pb.pcids_not_allowed().pcids().Get(j++);
		}
		t.pcids_same_tracking_area_.resize(pb.pcids_same_tracking_area_size());
		j = 0;
		for(auto &i : t.pcids_same_tracking_area_) {
			auto k = pb.pcids_same_tracking_area().Get(j);
			t.pcids_same_tracking_area_[j].resize(k.pcids_size());
			auto n = 0;
			for(auto &h : i)
				h = k.pcids().Get(n++);
		}
		t.pcids_different_tracking_area_.resize(pb.pcids_different_tracking_area_size());
		j = 0;
		for(auto &i : t.pcids_different_tracking_area_) {
			auto k = pb.pcids_different_tracking_area().Get(j);
			t.pcids_different_tracking_area_[j].resize(k.pcids_size());
			auto n = 0;
			for(auto &h : i)
				h = k.pcids().Get(n++);
		}
	}
	static void populate(const rp_gsm_si3 &pb, layer_3_information::gsm_si_3 &t) {
		t.is_decoded_ = true;
		set_plmn(pb.plmn(), t.plmn_);
		t.location_area_code_ = pb.location_area_code();
		t.cell_id_ = pb.cell_id();
		t.cell_reselect_hysteresis_db_ = pb.cell_reselect_hysteresis_db();
		populate(pb.selection_parameters(), t.selection_parameters_);
	}
	static void populate(const rp_gsm_selection_parameters &pb, layer_3_information::selection_parameters &t) {
		t.cbq_ = pb.cbq();
		t.cell_reselect_offset_db_= pb.cell_reselect_offset_db();
		t.temporary_offset_db_ = pb.temporary_offset_db();
		t.penalty_time_seconds_ = pb.penalty_time_seconds();
		t.subtract_reselect_cell_offset_ignore_temp_offset_ = pb.subtract_reselect_cell_offset_ignore_temp_offset();
		t.apply_infinity_offset_ = pb.apply_infinity_offset();
	}
	static void populate(const rp_gsm_si4 &pb, layer_3_information::gsm_si_4 &t) {
		t.is_decoded_ = true;
		set_plmn(pb.plmn(), t.plmn_);
		t.location_area_code_ = pb.location_area_code();
		t.cell_id_ = pb.cell_id();
		t.cell_reselect_hysteresis_db_ = pb.cell_reselect_hysteresis_db();
		populate(pb.selection_parameters(), t.selection_parameters_);
		t.is_cbch_present_ = pb.is_cbch_present();
		t.have_additional_param_in_si7_si8_ = pb.have_additional_param_in_si7_si8();
	}

	static void populate(const gsm_data &t, rp_gsm *pb) {
		pb->Clear();
		base_pb::populate(t, pb->mutable_base());
		pb->set_arfcn(t.arfcn_);
		pb->set_operating_band((rp_operating_band)t.operating_band_);
		pb->set_bsic(t.bsic_);
		pb->set_tdma_frame_number(t.tdma_frame_number_);
		pb->set_bcch_signal_level(t.cell_signal_level_);
		pb->set_ctoi(t.ctoi_);
		if(t.layer_3_.raw_layer_3_.size()) {
			for(auto &i : t.layer_3_.raw_layer_3_)
				set_raw_layer_3(i, pb->mutable_layer_3()->add_raw_layer_3());
		}
		if(t.layer_3_.si_1_.is_decoded()) populate(t.layer_3_.si_1_, pb->mutable_layer_3()->mutable_si1());
		if(t.layer_3_.si_2_.is_decoded()) populate(t.layer_3_.si_2_, pb->mutable_layer_3()->mutable_si2());
		if(t.layer_3_.si_2bis_.is_decoded()) populate(t.layer_3_.si_2bis_, pb->mutable_layer_3()->mutable_si2_bis());
		if(t.layer_3_.si_2ter_.is_decoded()) populate(t.layer_3_.si_2ter_, pb->mutable_layer_3()->mutable_si2_ter());
		if(t.layer_3_.si_2quater_.is_decoded()) populate(t.layer_3_.si_2quater_, pb->mutable_layer_3()->mutable_si2_quater());
		if(t.layer_3_.si_3_.is_decoded()) populate(t.layer_3_.si_3_, pb->mutable_layer_3()->mutable_si3());
		if(t.layer_3_.si_4_.is_decoded()) populate(t.layer_3_.si_4_, pb->mutable_layer_3()->mutable_si4());
	}
	static void populate(const layer_3_information::gsm_si_1 &t, rp_gsm_si1 *pb) {
		pb->set_band_indicator((rp_band_indicator_type)t.band_indicator_);
	}
	static void populate(const layer_3_information::gsm_si_2 &t, rp_gsm_si2 *pb) {
		for(auto &i : t.bcch_neighbors_)
			pb->add_bcch_neighbors(i);
		pb->set_extension_indication(t.bcch_neighbors_has_extension_);
		pb->set_bcch_allocation_indication(t.gsm_ba_ind_);
	}
	static void populate(const layer_3_information::gsm_si_2bis &t, rp_gsm_si2_bis *pb) {
		for(auto &i : t.extended_bcch_neighbors_)
			pb->add_extended_bcch_neighbors(i);
		pb->set_extension_indication(t.bcch_neighbors_has_extension_);
		pb->set_bcch_allocation_indication(t.gsm_ba_ind_);
		pb->set_rest_octet_count(t.rest_octet_count_);
		pb->set_rest_octet_index(t.rest_octet_index_);
	}
	static void populate(const layer_3_information::gsm_si_2ter &t, rp_gsm_si2_ter *pb) {
		for(auto &i : t.extended_bcch_neighbors_)
			pb->add_extended_bcch_neighbors(i);
		pb->set_gsm_bcch_allocation_indication(t.gsm_ba_ind_);
		pb->set_bcch_neighbors_multiband_reporting(t.bcch_neighbors_multiband_reporting_);
		for(auto &i : t.utran_neighbors_) {
			populate(i, pb->add_utran_neighbors());
		}
		pb->set_rest_octet_count(t.rest_octet_count_);
		pb->set_rest_octet_index(t.rest_octet_index_);
	}
	static void populate(const layer_3_information::utran_neighbor &t, rp_gsm_utran_neighbor *pb) {
		pb->set_duplexing((rp_duplex_type)t.duplexing_);
		pb->set_arfcn(t.arfcn_);
		pb->set_bandwidth((rp_utran_bandwidth_type)t.bandwidth_);
		for(auto &i : t.scrambling_codes_)
			pb->add_scrambling_codes(i);
	}
	static void populate(const layer_3_information::gsm_si_2quater &t, rp_gsm_si2_quater *pb) {
		pb->set_gsm_bcch_allocation_indication(t.gsm_ba_ind_);
		pb->set_p3g_bcch_allocation_indication(t.p3g_ba_ind_);
		pb->set_utran_neighbor_cell_index_start_3g(t.utran_neighbor_cell_index_start_3g_);
		pb->set_utran_neighbor_cell_absolute_index_start_emr(t.utran_neighbor_cell_absolute_index_start_emr_);
		for(auto &i : t.eutran_neighbors_) {
			populate(i, pb->add_eutran_neighbors());
		}
		for(auto &i : t.utran_neighbors_) {
			populate(i, pb->add_utran_neighbors());
		}
		pb->set_rest_octet_count(t.rest_octet_count_);
		pb->set_rest_octet_index(t.rest_octet_index_);
	}
	static void populate(const layer_3_information::eutran_neighbor &t, rp_gsm_eutran_neighbor *pb) {
		pb->set_earfcn(t.earfcn_);
		pb->set_bandwidth((rp_eutran_bandwidth_type)t.bandwidth_);
		pb->set_priority(t.priority_);
		pb->set_threshold_high_db(t.threshold_high_db_);
		pb->set_threshold_low_db(t.threshold_low_db_);
		pb->set_qrxlevmin_db(t.qrxlevmin_db_);
		for(auto &i : t.pcids_allowed_) {
			pb->mutable_pcids_allowed()->add_pcids(i);
		}
		for(auto &i : t.pcids_not_allowed_) {
			pb->mutable_pcids_not_allowed()->add_pcids(i);
		}
		for(auto &i : t.pcids_same_tracking_area_) {
			auto k = pb->mutable_pcids_same_tracking_area()->Add();
			for(auto &j : i)
				k->add_pcids(j);
		}
		for(auto &i : t.pcids_different_tracking_area_) {
			auto k = pb->mutable_pcids_different_tracking_area()->Add();
			for(auto &j : i)
				k->add_pcids(j);
		}
	}
	static void populate(const layer_3_information::gsm_si_3 &t, rp_gsm_si3 *pb) {
		set_plmn(t.plmn_, pb->mutable_plmn());
		pb->set_location_area_code(t.location_area_code_);
		pb->set_cell_id(t.cell_id_);
		pb->set_cell_reselect_hysteresis_db(t.cell_reselect_hysteresis_db_);
		populate(t.selection_parameters_, pb->mutable_selection_parameters());
	}
	static void populate(const layer_3_information::selection_parameters &t, rp_gsm_selection_parameters *pb) {
		pb->set_cbq(t.cbq_);
		pb->set_cell_reselect_offset_db(t.cell_reselect_offset_db_);
		pb->set_temporary_offset_db(t.temporary_offset_db_);
		pb->set_penalty_time_seconds(t.penalty_time_seconds_);
		pb->set_subtract_reselect_cell_offset_ignore_temp_offset(t.subtract_reselect_cell_offset_ignore_temp_offset_);
		pb->set_apply_infinity_offset(t.apply_infinity_offset_);
	}
	static void populate(const layer_3_information::gsm_si_4 &t, rp_gsm_si4 *pb) {
		set_plmn(t.plmn_, pb->mutable_plmn());
		pb->set_location_area_code(t.location_area_code_);
		pb->set_cell_id(t.cell_id_);
		pb->set_cell_reselect_hysteresis_db(t.cell_reselect_hysteresis_db_);
		populate(t.selection_parameters_, pb->mutable_selection_parameters());
		pb->set_is_cbch_present(t.is_cbch_present_);
		pb->set_have_additional_param_in_si7_si8(t.have_additional_param_in_si7_si8_);
	}
};

class wcdma_pb : public pb<rp_wcdma> {
public:
	wcdma_pb() {}
	wcdma_pb(const umts_data &t) {
		populate(t, pb_.get());
	}
	void populate(const umts_data &t) {
		populate(t, pb_.get());
	}
	umts_data get_umts_data() {
		umts_data t;
		populate(*pb_.get(), t);
		return t;
	}
	static void populate(const rp_wcdma &pb, umts_data &t) {
		base_pb::populate(pb.base(), t);
		t.uarfcn_ = pb.uarfcn();
		t.operating_band_ = (rf_phreaker::operating_band)pb.operating_band();
		t.cpich_ = pb.cpich();
		t.ecio_ = pb.ecio();
		t.rscp_ = pb.rscp();
		if(pb.has_layer_3()) {
			auto &l = pb.layer_3();
			if(l.raw_layer_3_size()) {
				t.layer_3_.raw_layer_3_.resize(pb.layer_3().raw_layer_3_size());
				auto j = 0;
				for(auto &i : t.layer_3_.raw_layer_3_)
					set_raw_layer_3(l.raw_layer_3().Get(j++), i);
			}
			if(l.has_mib()) populate(l.mib(), t.layer_3_.mib_); else t.layer_3_.mib_.is_decoded_ = false;
			if(l.has_sib1()) populate(l.sib1(), t.layer_3_.sib1_); else t.layer_3_.sib1_.is_decoded_ = false;
			if(l.has_sib3()) populate(l.sib3(), t.layer_3_.sib3_); else t.layer_3_.sib3_.is_decoded_ = false;
			if(l.has_sib4()) populate(l.sib4(), t.layer_3_.sib4_); else t.layer_3_.sib4_.is_decoded_ = false;
			if(l.has_sib11()) populate(l.sib11(), t.layer_3_.sib11_); else t.layer_3_.sib11_.is_decoded_ = false;
			if(l.has_sib11_bis()) populate(l.sib11_bis(), t.layer_3_.sib11_bis_); else t.layer_3_.sib11_bis_.is_decoded_ = false;
		}
	}
	static void populate(const rp_wcdma_mib &pb, layer_3_information::umts_mib_type &t) {
		t.is_decoded_ = true;
		set_plmn(pb.plmn(), t.plmn_);
		t.multiple_plmns_.resize(pb.multiple_plmns_size());
		auto j = 0;
		for(auto &i : t.multiple_plmns_) {
			set_plmn(pb.multiple_plmns().Get(j++), i);
		}
	}
	static void populate(const rp_wcdma_sib1 &pb, layer_3_information::umts_sib1_type &t) {
		t.is_decoded_ = true;
		t.lac_ = pb.lac();
	}
	static void populate(const rp_wcdma_sib3 &pb, layer_3_information::umts_sib3_type &t) {
		t.is_decoded_ = true;
		t.cid_ = pb.cid();
	}
	static void populate(const rp_wcdma_sib4 &pb, layer_3_information::umts_sib4_type &t) {
		t.is_decoded_ = true;
		t.cid_ = pb.cid();
	}
	static void populate(const rp_wcdma_sib11 &pb, layer_3_information::umts_sib11_type &t) {
		t.is_decoded_ = true;
		t.neighbor_intra_group_.resize(pb.utran_intra_neighbor_cpichs_size());
		auto j = 0;
		for(auto &i : t.neighbor_intra_group_)
			i = pb.utran_intra_neighbor_cpichs().Get(j++);
		t.neighbor_inter_group_.resize(pb.utran_inter_neighbors_size());
		j = 0;
		for(auto &i : t.neighbor_inter_group_)
			populate(pb.utran_inter_neighbors().Get(j++), i);
		t.neighbor_inter_rat_group_.resize(pb.gsm_inter_neighbors_size());
		j = 0;
		for(auto &i : t.neighbor_inter_rat_group_)
			populate(pb.gsm_inter_neighbors().Get(j++), i);
	}
	static void populate(const rp_wcdma_utran_neighbor &pb, layer_3_information::neighbor_inter &t) {
		t.cpich_ = pb.cpich();
		t.uarfcn_ = pb.uarfcn();
	}
	static void populate(const rp_wcdma_gsm_neighbor &pb, layer_3_information::neighbor_inter_rat &t) {
		t.arfcn_ = pb.arfcn();
		t.band_indicator_ = (layer_3_information::band_indicator_type)pb.band_indicator();
		t.bsic_ = pb.bsic();
		t.qrx_lev_min_ = pb.qrx_lev_min();
	}
	static void populate(const rp_wcdma_sib11_bis &pb, layer_3_information::umts_sib11_bis_type &t) {
		t.is_decoded_ = true;
		t.neighbor_intra_group_.resize(pb.utran_intra_neighbor_cpichs_size());
		auto j = 0;
		for(auto &i : t.neighbor_intra_group_)
			i = pb.utran_intra_neighbor_cpichs().Get(j++);
		t.neighbor_inter_group_.resize(pb.utran_inter_neighbors_size());
		j = 0;
		for(auto &i : t.neighbor_inter_group_)
			populate(pb.utran_inter_neighbors().Get(j++), i);
		t.neighbor_inter_rat_group_.resize(pb.gsm_inter_neighbors_size());
		j = 0;
		for(auto &i : t.neighbor_inter_rat_group_)
			populate(pb.gsm_inter_neighbors().Get(j++), i);
	}

	static void populate(const umts_data &t, rp_wcdma *pb) {
		pb->Clear();
		base_pb::populate(t, pb->mutable_base());
		pb->set_uarfcn(t.uarfcn_);
		pb->set_operating_band((rp_operating_band)t.operating_band_);
		pb->set_cpich(t.cpich_);
		pb->set_ecio(t.ecio_);
		pb->set_rscp(t.rscp_);
		if(t.layer_3_.raw_layer_3_.size()) {
			for(auto &i : t.layer_3_.raw_layer_3_)
				set_raw_layer_3(i, pb->mutable_layer_3()->add_raw_layer_3());
		}
		if(t.layer_3_.mib_.is_decoded()) populate(t.layer_3_.mib_, pb->mutable_layer_3()->mutable_mib());
		if(t.layer_3_.sib1_.is_decoded()) populate(t.layer_3_.sib1_, pb->mutable_layer_3()->mutable_sib1());
		if(t.layer_3_.sib3_.is_decoded()) populate(t.layer_3_.sib3_, pb->mutable_layer_3()->mutable_sib3());
		if(t.layer_3_.sib4_.is_decoded()) populate(t.layer_3_.sib4_, pb->mutable_layer_3()->mutable_sib4());
		if(t.layer_3_.sib11_.is_decoded()) populate(t.layer_3_.sib11_, pb->mutable_layer_3()->mutable_sib11());
		if(t.layer_3_.sib11_bis_.is_decoded()) populate(t.layer_3_.sib11_bis_, pb->mutable_layer_3()->mutable_sib11_bis());

	}
	static void populate(const layer_3_information::umts_mib_type &t, rp_wcdma_mib *pb) {
		set_plmn(t.plmn_, pb->mutable_plmn());
		for(auto &i : t.multiple_plmns_) {
			set_plmn(i, pb->add_multiple_plmns());
		}
	}
	static void populate(const layer_3_information::umts_sib1_type &t, rp_wcdma_sib1 *pb) {
		pb->set_lac(t.lac_);
	}
	static void populate(const layer_3_information::umts_sib3_type &t, rp_wcdma_sib3 *pb) {
		pb->set_cid(t.cid_);
	}
	static void populate(const layer_3_information::umts_sib4_type &t, rp_wcdma_sib4 *pb) {
		pb->set_cid(t.cid_);
	}
	static void populate(const layer_3_information::umts_sib11_type &t, rp_wcdma_sib11 *pb) {
		for(auto &i : t.neighbor_intra_group_)
			pb->add_utran_intra_neighbor_cpichs(i);
		for(auto &i : t.neighbor_inter_group_)
			populate(i, pb->add_utran_inter_neighbors());
		for(auto &i : t.neighbor_inter_rat_group_)
			populate(i, pb->add_gsm_inter_neighbors());
	}
	static void populate(const layer_3_information::neighbor_inter &t, rp_wcdma_utran_neighbor *pb) {
		pb->set_cpich(t.cpich_);
		pb->set_uarfcn(t.uarfcn_);
	}
	static void populate(const layer_3_information::neighbor_inter_rat &t, rp_wcdma_gsm_neighbor *pb) {
		pb->set_arfcn(t.arfcn_);
		pb->set_band_indicator((rp_band_indicator_type)t.band_indicator_);
		pb->set_bsic(t.bsic_.to_uint16());
		pb->set_qrx_lev_min(t.qrx_lev_min_);
	}
	static void populate(const layer_3_information::umts_sib11_bis_type &t, rp_wcdma_sib11_bis *pb) {
		for(auto &i : t.neighbor_intra_group_)
			pb->add_utran_intra_neighbor_cpichs(i);
		for(auto &i : t.neighbor_inter_group_)
			populate(i, pb->add_utran_inter_neighbors());
		for(auto &i : t.neighbor_inter_rat_group_)
			populate(i, pb->add_gsm_inter_neighbors());
	}
};

class lte_pb : public pb<rp_lte> {
public:
	lte_pb() {}
	lte_pb(const lte_data &t) {
		populate(t, pb_.get());
	}
	void populate(const lte_data &t) {
		populate(t, pb_.get());
	}
	lte_data get_lte_data() {
		lte_data t;
		populate(*pb_.get(), t);
		return t;
	}
	static void populate(const rp_lte &pb, lte_data &t) {
		base_pb::populate(pb.base(), t);
		t.earfcn_ = pb.earfcn();
		t.operating_band_ = (rf_phreaker::operating_band)pb.operating_band();
		t.physical_cell_id_ = pb.physical_cell_id();
		t.rsrp_ = pb.rsrp();
		t.rsrq_ = pb.rsrq();
		t.rssi_ = pb.rssi();
		t.psch_id_ = pb.psch_id();
		t.psch_quality_ = pb.psch_quality();
		t.ssch_id_ = pb.ssch_id();
		t.ssch_quality_ = pb.ssch_quality();
		t.sync_quality_ = pb.sync_quality();
		t.cyclic_prefix_ = pb.cyclic_prefix();
		t.num_antenna_ports_ = pb.num_antenna_ports();
		t.dl_bandwidth_ = pb.downlink_bandwidth();
		t.frame_number_ = pb.frame_number();
		if(pb.has_layer_3()) {
			auto &l = pb.layer_3();
			if(l.raw_layer_3_size()) {
				t.layer_3_.raw_layer_3_.resize(l.raw_layer_3_size());
				auto j = 0;
				for(auto &i : t.layer_3_.raw_layer_3_)
					set_raw_layer_3(l.raw_layer_3().Get(j++), i);
			}
			if(l.has_sib1()) populate(pb.layer_3().sib1(), t.layer_3_.sib1_); else t.layer_3_.sib1_.is_decoded_ = false;
			if(l.has_sib3()) populate(pb.layer_3().sib3(), t.layer_3_.sib3_); else t.layer_3_.sib3_.is_decoded_ = false;
			if(l.has_sib4()) populate(pb.layer_3().sib4(), t.layer_3_.sib4_); else t.layer_3_.sib4_.is_decoded_ = false;
			if(l.has_sib5()) populate(pb.layer_3().sib5(), t.layer_3_.sib5_); else t.layer_3_.sib5_.is_decoded_ = false;
			if(l.has_sib6()) populate(pb.layer_3().sib6(), t.layer_3_.sib6_); else t.layer_3_.sib6_.is_decoded_ = false;
			if(l.has_sib7()) populate(pb.layer_3().sib7(), t.layer_3_.sib7_); else t.layer_3_.sib7_.is_decoded_ = false;
			if(l.has_sib8()) populate(pb.layer_3().sib8(), t.layer_3_.sib8_); else t.layer_3_.sib8_.is_decoded_ = false;
		}
	}
	static void populate(const rp_lte_sib1 &pb, layer_3_information::lte_sib1_type &t) {
		t.is_decoded_ = true;
		t.multiple_plmn_.resize(pb.multiple_plmns_size());
		auto j = 0;
		for(auto &i : t.multiple_plmn_)
			set_plmn(pb.multiple_plmns().Get(j++), i);
		t.tracking_area_code_ = pb.tac();
		t.cell_id_ = pb.cid();
		t.scheduling_info_list_.resize(pb.scheduling_info_size());
		j = 0;
		for(auto &i : t.scheduling_info_list_) {
			auto k = pb.scheduling_info().Get(j++);
			i.periodicity_in_frames_ = k.periodicity_in_frames();
			i.sib_mapping_info_.resize(k.sibs_size());
			auto n = 0;
			for(auto &m : i.sib_mapping_info_)
				m = (layer_3_information::lte_sib_type)k.sibs().Get(n++);
		}
		t.si_window_length_ms_ = pb.si_window_length_ms();
	}
	static void populate(const rp_lte_sib3 &pb, layer_3_information::lte_sib3_type &t) {
		t.is_decoded_ = true;
		populate(pb.cell_reselection_serving_freq_info(), t.cell_reselection_serving_freq_info_);
		t.intra_freq_cell_reselection_info_.s_intra_search_ = pb.intra_freq_cell_reselection_info_s_intra_search();
		populate(pb.s_intra_search_v920(), t.s_non_intra_search_v920_);
		populate(pb.s_intra_search_v920(), t.s_intra_search_v920_);
		t.threshold_serving_low_q_ = pb.threshold_serving_low_q();
	}
	static void populate(const rp_lte_cell_reselection_serving_freq_info &pb, layer_3_information::cell_reselection_serving_freq_info &t) {
		t.s_non_intra_search_ = pb.s_non_intra_search();
		t.threshold_serving_low_ = pb.threshold_serving_low();
		t.cell_reselection_priority_ = pb.cell_reselection_priority();
	}
	static void populate(const rp_lte_s_search_v920 &pb, layer_3_information::s_search_v920 &t) {
		t.p_ = pb.p();
		t.q_ = pb.q();
	}
	static void populate(const rp_lte_sib4 &pb, layer_3_information::lte_sib4_type &t) {
		t.is_decoded_ = true;
		t.intra_freq_neighbor_cell_list_.resize(pb.intra_freq_neighbor_cell_list_size());
		auto j = 0;
		for(auto &i : t.intra_freq_neighbor_cell_list_)
			populate(pb.intra_freq_neighbor_cell_list().Get(j++), i);
		t.intra_freq_black_cell_list_.resize(pb.intra_freq_black_cell_list_size());
		j = 0;
		for(auto &i : t.intra_freq_black_cell_list_)
			populate(pb.intra_freq_black_cell_list().Get(j++), i);
		populate(pb.csg_physical_cellid_range(), t.csg_physical_cellid_range_);
	}
	static void populate(const rp_lte_neighbor_cell &pb, layer_3_information::neighbor_cell &t) {
		t.physical_cell_id_ = pb.physical_cell_id();
		t.q_offset_cell_ = pb.q_offset_cell();
	}
	static void populate(const rp_lte_physical_cellid_range &pb, layer_3_information::physical_cellid_range &t) {
		t.start_ = pb.start();
		t.range_ = pb.range();
	}
	static void populate(const rp_lte_sib5 &pb, layer_3_information::lte_sib5_type &t) {
		t.is_decoded_ = true;
		t.inter_freq_carrier_info_list_.resize(pb.inter_freq_carrier_info_list_size());
		auto j = 0;
		for(auto &i : t.inter_freq_carrier_info_list_)
			populate(pb.inter_freq_carrier_info_list().Get(j++), i);
	}
	static void populate(const rp_lte_inter_freq_carrier_freq_info &pb, layer_3_information::inter_freq_carrier_freq_info &t) {
		t.downlink_arfcn_value_eutra_ = pb.downlink_arfcn_value_eutra();
		t.q_rx_lev_min_ = pb.q_rx_lev_min();
		t.q_offset_freq_ = pb.q_offset_freq();
		t.allowed_measurement_bandwidth_ = pb.allowed_measurement_bandwidth();
		t.presence_antenna_port_1_ = pb.presence_antenna_port_1();
		t.threshold_x_high_ = pb.threshold_x_high();
		t.threshold_x_low_ = pb.threshold_x_low();
		t.threshold_x_high_q_r9_ = pb.threshold_x_high_q_r9();
		t.threshold_x_low_q_r9_ = pb.threshold_x_low_q_r9();
		t.cell_reselection_priority_ = pb.cell_reselection_priority();
		t.inter_freq_neighbor_cell_list_.resize(pb.inter_freq_neighbor_cell_list_size());
		auto j = 0;
		for(auto &i : t.inter_freq_neighbor_cell_list_)
			populate(pb.inter_freq_neighbor_cell_list().Get(j++), i);
		t.inter_freq_black_cell_list_.resize(pb.inter_freq_black_cell_list_size());
		j = 0;
		for(auto &i : t.inter_freq_black_cell_list_)
			populate(pb.inter_freq_black_cell_list().Get(j++), i);
	}
	static void populate(const rp_lte_sib6 &pb, layer_3_information::lte_sib6_type &t) {
		t.is_decoded_ = true;
		t.carrier_freq_list_utra_fdd_.resize(pb.carrier_freq_list_utra_fdd_size());
		auto j = 0;
		for(auto &i : t.carrier_freq_list_utra_fdd_)
			populate(pb.carrier_freq_list_utra_fdd().Get(j++), i);
		t.carrier_freq_list_utra_tdd_.resize(pb.carrier_freq_list_utra_tdd_size());
		j = 0;
		for(auto &i : t.carrier_freq_list_utra_tdd_)
			populate(pb.carrier_freq_list_utra_tdd().Get(j++), i);
	}
	static void populate(const rp_lte_carrier_freq_utra &pb, layer_3_information::carrier_freq_utra&t) {
		t.arfcn_value_utra_ = pb.arfcn_value_utra();
		t.threshold_x_low_ = pb.threshold_x_low();
		t.threshold_x_high_ = pb.threshold_x_high();
		t.threshold_x_low_q_r9_ = pb.threshold_x_low_q_r9();
		t.threshold_x_high_q_r9_ = pb.threshold_x_high_q_r9();
		t.cell_reselection_priority_ = pb.cell_reselection_priority();
	}
	static void populate(const rp_lte_sib7 &pb, layer_3_information::lte_sib7_type &t) {
		t.is_decoded_ = true;
		t.carrier_freqs_info_list_geran_.resize(pb.carrier_freqs_info_list_geran_size());
		auto j = 0;
		for(auto &i : t.carrier_freqs_info_list_geran_)
			populate(pb.carrier_freqs_info_list_geran().Get(j++), i);
	}
	static void populate(const rp_lte_carrier_freqs_info_geran &pb, layer_3_information::carrier_freqs_info_geran &t) {
		auto k = pb.common_info();
		t.common_info_.cell_reselection_priority_ = k.cell_reselection_priority();
		t.common_info_.threshold_x_high_ = k.threshold_x_high();
		t.common_info_.threshold_x_low_ = k.threshold_x_low();
		populate(pb.carrier_freqs(), t.carrier_freqs_);
	}
	static void populate(const rp_lte_carrier_freqs_geran &pb, layer_3_information::carrier_freqs_geran &t) {
		t.band_indicator_ = (layer_3_information::band_indicator_type)pb.band_indicator();
		if(pb.arfcns_size())
			t.starting_arfcn_ = pb.arfcns().Get(0);
		t.following_arfcns_.resize(pb.arfcns_size());
		auto j = 0;
		for(auto &i : t.following_arfcns_)
			i = pb.arfcns().Get(j++);
	}
	static void populate(const rp_lte_sib8 &pb, layer_3_information::lte_sib8_type &t) {
		t.is_decoded_ = true;
		populate(pb.parameters_hrpd(), t.parameters_hrpd_);
		populate(pb.parameters_1xrtt(), t.parameters_1xrtt_);
	}
	static void populate(const rp_lte_cell_reselection_parameters_cmda_2000 &pb, layer_3_information::cell_reselection_parameters_cmda_2000&t) {
		t.neighbor_cell_list_.resize(pb.neighbor_cell_list_size());
		auto j = 0;
		for(auto &i : t.neighbor_cell_list_)
			populate(pb.neighbor_cell_list().Get(j++), i);
	}
	static void populate(const rp_lte_neighbor_cell_cdma_2000&pb, layer_3_information::neighbor_cell_cdma_2000&t) {
		t.band_ = (layer_3_information::band_class_cmda_2000)pb.band();
		t.neighbor_cells_per_freq_list_.resize(pb.neighbor_cells_per_freq_list_size());
		auto j = 0;
		for(auto &i : t.neighbor_cells_per_freq_list_)
			populate(pb.neighbor_cells_per_freq_list().Get(j++), i);
	}
	static void populate(const rp_lte_neighbor_cells_per_band_class_cdma_2000&pb, layer_3_information::neighbor_cells_per_band_class_cdma_2000&t) {
		t.arfcn_value_cmda_2000_ = pb.arfcn_value_cdma_2000();
		t.physical_cell_ids_.resize(pb.physical_cell_ids_size());
		auto j = 0;
		for(auto &i : t.physical_cell_ids_)
			i = pb.physical_cell_ids().Get(j++);
	}

	static void populate(const lte_data &t, rp_lte *pb) {
		pb->Clear();
		base_pb::populate(t, pb->mutable_base());
		pb->set_earfcn(t.earfcn_);
		pb->set_operating_band((rp_operating_band)t.operating_band_);
		pb->set_physical_cell_id(t.physical_cell_id_);
		pb->set_rsrp(t.rsrp_);
		pb->set_rsrq(t.rsrq_);
		pb->set_rssi(t.rssi_);
		pb->set_psch_id(t.psch_id_);
		pb->set_psch_quality(t.psch_quality_);
		pb->set_ssch_id(t.ssch_id_);
		pb->set_ssch_quality(t.ssch_quality_);
		pb->set_sync_quality(t.sync_quality_);
		pb->set_cyclic_prefix(t.cyclic_prefix_);
		pb->set_num_antenna_ports(t.num_antenna_ports_);
		pb->set_downlink_bandwidth(t.dl_bandwidth_);
		pb->set_frame_number(t.frame_number_);
		if(t.layer_3_.raw_layer_3_.size()) {
			for(auto &i : t.layer_3_.raw_layer_3_)
				set_raw_layer_3(i, pb->mutable_layer_3()->add_raw_layer_3());
		}
		if(t.layer_3_.sib1_.is_decoded()) populate(t.layer_3_.sib1_, pb->mutable_layer_3()->mutable_sib1());
		if(t.layer_3_.sib3_.is_decoded()) populate(t.layer_3_.sib3_, pb->mutable_layer_3()->mutable_sib3());
		if(t.layer_3_.sib4_.is_decoded()) populate(t.layer_3_.sib4_, pb->mutable_layer_3()->mutable_sib4());
		if(t.layer_3_.sib5_.is_decoded()) populate(t.layer_3_.sib5_, pb->mutable_layer_3()->mutable_sib5());
		if(t.layer_3_.sib6_.is_decoded()) populate(t.layer_3_.sib6_, pb->mutable_layer_3()->mutable_sib6());
		if(t.layer_3_.sib7_.is_decoded()) populate(t.layer_3_.sib7_, pb->mutable_layer_3()->mutable_sib7());
		if(t.layer_3_.sib8_.is_decoded()) populate(t.layer_3_.sib8_, pb->mutable_layer_3()->mutable_sib8());
	}
	static void populate(const layer_3_information::lte_sib1_type &t, rp_lte_sib1 *pb) {
		for(auto &i : t.multiple_plmn_)
			set_plmn(i, pb->add_multiple_plmns());
		pb->set_tac(t.tracking_area_code_);
		pb->set_cid(t.cell_id_);
		for(auto &i : t.scheduling_info_list_) {
			auto k = pb->add_scheduling_info();
			k->set_periodicity_in_frames(i.periodicity_in_frames_);
			for(auto &j : i.sib_mapping_info_)
				k->add_sibs((rp_lte_sib_type)j);
		}
		pb->set_si_window_length_ms(t.si_window_length_ms_);
	}
	static void populate(const layer_3_information::lte_sib3_type &t, rp_lte_sib3 *pb) {
		populate(t.cell_reselection_serving_freq_info_, pb->mutable_cell_reselection_serving_freq_info());
		pb->set_intra_freq_cell_reselection_info_s_intra_search(t.intra_freq_cell_reselection_info_.s_intra_search_.reselection_threshold());
		populate(t.s_non_intra_search_v920_, pb->mutable_s_intra_search_v920());
		populate(t.s_intra_search_v920_, pb->mutable_s_intra_search_v920());
		pb->set_threshold_serving_low_q(t.threshold_serving_low_q_);
	}
	static void populate(const layer_3_information::cell_reselection_serving_freq_info &t, rp_lte_cell_reselection_serving_freq_info *pb) {
		pb->set_s_non_intra_search(t.s_non_intra_search_.reselection_threshold());
		pb->set_threshold_serving_low(t.threshold_serving_low_.reselection_threshold());
		pb->set_cell_reselection_priority(t.cell_reselection_priority_);
	}
	static void populate(const layer_3_information::s_search_v920 &t, rp_lte_s_search_v920 *pb) {
		pb->set_p(t.p_.reselection_threshold());
		pb->set_q(t.q_);
	}
	static void populate(const layer_3_information::lte_sib4_type &t, rp_lte_sib4 *pb) {
		for(auto &i : t.intra_freq_neighbor_cell_list_)
			populate(i, pb->add_intra_freq_neighbor_cell_list());
		for(auto &i : t.intra_freq_black_cell_list_)
			populate(i, pb->add_intra_freq_black_cell_list());
		populate(t.csg_physical_cellid_range_, pb->mutable_csg_physical_cellid_range());
	}
	static void populate(const layer_3_information::neighbor_cell &t, rp_lte_neighbor_cell *pb) {
		pb->set_physical_cell_id(t.physical_cell_id_);
		pb->set_q_offset_cell(t.q_offset_cell_);
	}
	static void populate(const layer_3_information::physical_cellid_range &t, rp_lte_physical_cellid_range *pb) {
		pb->set_start(t.start_);
		pb->set_range(t.range_);
	}
	static void populate(const layer_3_information::lte_sib5_type &t, rp_lte_sib5 *pb) {
		for(auto &i : t.inter_freq_carrier_info_list_)
			populate(i, pb->add_inter_freq_carrier_info_list());
	}
	static void populate(const layer_3_information::inter_freq_carrier_freq_info &t, rp_lte_inter_freq_carrier_freq_info *pb) {
		pb->set_downlink_arfcn_value_eutra(t.downlink_arfcn_value_eutra_);
		pb->set_q_rx_lev_min(t.q_rx_lev_min_);
		pb->set_q_offset_freq(t.q_offset_freq_);
		pb->set_allowed_measurement_bandwidth(t.allowed_measurement_bandwidth_);
		pb->set_presence_antenna_port_1(t.presence_antenna_port_1_);
		pb->set_threshold_x_high(t.threshold_x_high_.reselection_threshold());
		pb->set_threshold_x_low(t.threshold_x_low_.reselection_threshold());
		pb->set_threshold_x_high_q_r9(t.threshold_x_high_q_r9_);
		pb->set_threshold_x_low_q_r9(t.threshold_x_low_q_r9_);
		pb->set_cell_reselection_priority(t.cell_reselection_priority_);
		for(auto &i : t.inter_freq_neighbor_cell_list_)
			populate(i, pb->add_inter_freq_neighbor_cell_list());
		for(auto &i : t.inter_freq_black_cell_list_)
			populate(i, pb->add_inter_freq_black_cell_list());
	}
	static void populate(const layer_3_information::lte_sib6_type &t, rp_lte_sib6 *pb) {
		for(auto &i : t.carrier_freq_list_utra_fdd_)
			populate(i, pb->add_carrier_freq_list_utra_fdd());
		for(auto &i : t.carrier_freq_list_utra_tdd_)
			populate(i, pb->add_carrier_freq_list_utra_tdd());
	}
	static void populate(const layer_3_information::carrier_freq_utra&t, rp_lte_carrier_freq_utra *pb) {
		pb->set_arfcn_value_utra(t.arfcn_value_utra_);
		pb->set_threshold_x_low(t.threshold_x_low_.reselection_threshold());
		pb->set_threshold_x_high(t.threshold_x_high_.reselection_threshold());
		pb->set_threshold_x_low_q_r9(t.threshold_x_low_q_r9_);
		pb->set_threshold_x_high_q_r9(t.threshold_x_high_q_r9_);
		pb->set_cell_reselection_priority(t.cell_reselection_priority_);
	}
	static void populate(const layer_3_information::lte_sib7_type &t, rp_lte_sib7 *pb) {
		for(auto &i : t.carrier_freqs_info_list_geran_)
			populate(i, pb->add_carrier_freqs_info_list_geran());
	}
	static void populate(const layer_3_information::carrier_freqs_info_geran &t, rp_lte_carrier_freqs_info_geran *pb) {
		auto k = pb->mutable_common_info();
		k->set_cell_reselection_priority(t.common_info_.cell_reselection_priority_);
		k->set_threshold_x_high(t.common_info_.threshold_x_high_.reselection_threshold());
		k->set_threshold_x_low(t.common_info_.threshold_x_low_.reselection_threshold());
		populate(t.carrier_freqs_, pb->mutable_carrier_freqs());
	}
	static void populate(const layer_3_information::carrier_freqs_geran &t, rp_lte_carrier_freqs_geran *pb) {
		pb->set_band_indicator((rp_band_indicator_type)t.band_indicator_);
		for(auto &i : t.following_arfcns_)
			pb->add_arfcns(i);
	}
	static void populate(const layer_3_information::lte_sib8_type &t, rp_lte_sib8 *pb) {
		populate(t.parameters_hrpd_, pb->mutable_parameters_hrpd());
		populate(t.parameters_1xrtt_, pb->mutable_parameters_1xrtt());
	}
	static void populate(const layer_3_information::cell_reselection_parameters_cmda_2000&t, rp_lte_cell_reselection_parameters_cmda_2000 *pb) {
		for(auto &i : t.neighbor_cell_list_)
			populate(i, pb->add_neighbor_cell_list());
	}
	static void populate(const layer_3_information::neighbor_cell_cdma_2000&t, rp_lte_neighbor_cell_cdma_2000*pb) {
		pb->set_band((rp_lte_band_class_cdma_2000_type)t.band_);
		for(auto &i : t.neighbor_cells_per_freq_list_)
			populate(i, pb->add_neighbor_cells_per_freq_list());
	}
	static void populate(const layer_3_information::neighbor_cells_per_band_class_cdma_2000&t, rp_lte_neighbor_cells_per_band_class_cdma_2000*pb) {
		pb->set_arfcn_value_cdma_2000(t.arfcn_value_cmda_2000_);
		for(auto &i : t.physical_cell_ids_)
			pb->add_physical_cell_ids(i);
	}
};

class gsm_update_pb : public pb<rp_gsm_update> {
public:
	gsm_update_pb() {}
	gsm_update_pb(const std::vector<gsm_data> &t, const basic_data &b) {
		populate(t, b, pb_.get());
	}
	void populate(const std::vector<gsm_data> &t, const basic_data &b) {
		populate(t, b, pb_.get());
	}
	static void populate(const rp_gsm_update &pb, std::vector<gsm_data> &t) {
		t.clear();
		auto j = 0;
		for(auto i = 0; i < pb.gsm_size(); ++i) {
			gsm_data g;
			gsm_pb::populate(pb.gsm().Get(j++), g);
			t.emplace_back(g);
		}
	}
	static void populate(const std::vector<gsm_data> &t, const basic_data &b, rp_gsm_update *pb) {
		pb->Clear();
		for(auto &i : t) {
			gsm_pb::populate(i, pb->add_gsm());
		}
		base_pb::populate(b, pb->mutable_base());
	}
};

class wcdma_update_pb : public pb<rp_wcdma_update> {
public:
	wcdma_update_pb() {}
	wcdma_update_pb(const std::vector<umts_data> &t, const basic_data &b) {
		populate(t, b, pb_.get());
	}
	void populate(const std::vector<umts_data> &t, const basic_data &b) {
		populate(t, b, pb_.get());
	}
	static void populate(const rp_wcdma_update &pb, std::vector<umts_data> &t) {
		t.clear();
		auto j = 0;
		for(auto i = 0; i < pb.wcdma_size(); ++i) {
			umts_data g;
			wcdma_pb::populate(pb.wcdma().Get(j++), g);
			t.emplace_back(g);
		}
	}
	static void populate(const std::vector<umts_data> &t, const basic_data &b, rp_wcdma_update *pb) {
		pb->Clear();
		for(auto &i : t) {
			wcdma_pb::populate(i, pb->add_wcdma());
		}
		base_pb::populate(b, pb->mutable_base());
	}
};

class lte_update_pb : public pb<rp_lte_update> {
public:
	lte_update_pb() {}
	lte_update_pb(const std::vector<lte_data> &t, const basic_data &b) {
		populate(t, b, pb_.get());
	}
	void populate(const std::vector<lte_data> &t, const basic_data &b) {
		populate(t, b, pb_.get());
	}
	static void populate(const rp_lte_update &pb, std::vector<lte_data> &t) {
		t.clear();
		auto j = 0;
		for(auto i = 0; i < pb.lte_size(); ++i) {
			lte_data g;
			lte_pb::populate(pb.lte().Get(j++), g);
			t.emplace_back(g);
		}
	}
	static void populate(const std::vector<lte_data> &t, const basic_data &b, rp_lte_update *pb) {
		pb->Clear();
		for(auto &i : t) {
			lte_pb::populate(i, pb->add_lte());
		}
		base_pb::populate(b, pb->mutable_base());
	}
};

class power_spectrum_pb : public pb<rp_power_spectrum> {
public:
	power_spectrum_pb() {}
	power_spectrum_pb(const power_spectrum_data &t) {
		populate(t, pb_.get());
	}
	void populate(const power_spectrum_data &t) {
		populate(t, pb_.get());
	}
	static void populate(const rp_power_spectrum &pb, power_spectrum_data &t) {
		base_pb::populate(pb.base(), t);
		t.params_.bin_size_ = pb.bin_size();
		t.params_.dwell_time_= pb.dwell_time();
		t.params_.end_frequency_ = pb.end_frequency();
		t.params_.num_windows_ = pb.num_windows();
		t.params_.sampling_rate_ = pb.sampling_rate();
		t.params_.span_ = pb.span();
		t.params_.start_frequency_ = pb.start_frequency();
		t.params_.step_size_ = pb.step_size();
		t.params_.window_length_ = pb.window_length();
		t.params_.num_windows_ = pb.num_windows();
		t.power_.resize(pb.power_size());
		for(auto i = 0; i < pb.power_size(); ++i) {
			t.power_[i] = pb.power().Get(i);
		}
	}
	static void populate(const power_spectrum_data &t, rp_power_spectrum *pb) {
		pb->Clear();
		base_pb::populate(t, pb->mutable_base());
		pb->set_bin_size(t.params_.bin_size_);
		pb->set_dwell_time(t.params_.dwell_time_);
		pb->set_sampling_rate(t.params_.sampling_rate_);
		pb->set_end_frequency(t.params_.end_frequency_);
		pb->set_span(t.params_.span_);
		pb->set_start_frequency(t.params_.start_frequency_);
		pb->set_step_size(t.params_.step_size_);
		pb->set_window_length(t.params_.window_length_);
		pb->set_num_windows(t.params_.num_windows_);
		for(auto i : t.power_) {
			pb->add_power(i);
		}
	}
};

class iq_data_pb : public pb<rp_iq_data> {
public:
	iq_data_pb() {}
	iq_data_pb(const iq_data &t) {
		populate(t, pb_.get());
	}
	void populate(const iq_data &t) {
		populate(t, pb_.get());
	}
	static void populate(const rp_iq_data &pb, iq_data &t) {
		base_pb::populate(pb.base(), t);
		t.power_adjustment_.path_.low_freq_ = pb.power_adjustment().path().low_freq();
		t.power_adjustment_.path_.high_freq_ = pb.power_adjustment().path().high_freq();
		t.power_adjustment_.step_size_ = pb.power_adjustment().step_size();
		t.power_adjustment_.power_.resize(pb.power_adjustment().power_size());
		for(auto i = 0; i < pb.power_adjustment().power_size(); ++i)
			t.power_adjustment_.power_[i] = pb.power_adjustment().power().Get(i);
		t.sampling_rate_ = pb.sampling_rate();
		t.dwell_time_ = pb.dwell_time();
		t.samples_.resize(pb.samples_size());
		for(auto i = 0; i < pb.samples_size(); ++i) {
			t.samples_[i] = pb.samples().Get(i);
		}
	}
	static void populate(const iq_data &t, rp_iq_data *pb) {
		pb->Clear();
		base_pb::populate(t, pb->mutable_base());
		pb->mutable_power_adjustment()->mutable_path()->set_low_freq(t.power_adjustment_.path_.low_freq_);
		pb->mutable_power_adjustment()->mutable_path()->set_high_freq(t.power_adjustment_.path_.high_freq_);
		pb->mutable_power_adjustment()->set_step_size(t.power_adjustment_.step_size_);
		for(auto i : t.power_adjustment_.power_) {
			pb->mutable_power_adjustment()->add_power(i);
		}
		pb->set_sampling_rate(t.sampling_rate_);
		pb->set_dwell_time(t.dwell_time_);
		for(auto i : t.samples_)
			pb->mutable_samples()->Add(i);
	}
};

class update_pb : public pb<rp_update> {
public:
	update_pb() {}
	void populate_message(const ::rp_status s, const std::string &str) {
		populate_message(s, str, pb_.get());
	}
	void populate_log(const std::string &str) {
		populate_log(str, pb_.get());
	}
	void populate_device_info(const hardware &t) {
		populate_device_info(t, pb_.get());
	}
	void populate_gps(const gps &t) {
		populate_gps(t, pb_.get());
	}
	void populate_gsm_full_scan(const std::vector<gsm_data> &t, const basic_data &b) {
		populate_gsm_full_scan(t, b, pb_.get());
	}
	void populate_wcdma_full_scan(const std::vector<umts_data> &t, const basic_data &b) {
		populate_wcdma_full_scan(t, b, pb_.get());
	}
	void populate_lte_full_scan(const std::vector<lte_data> &t, const basic_data &b) {
		populate_lte_full_scan(t, b, pb_.get());
	}
	void populate_gsm_sweep(const std::vector<gsm_data> &t, const basic_data &b) {
		populate_gsm_sweep(t, b, pb_.get());
	}
	void populate_wcdma_sweep(const std::vector<umts_data> &t, const basic_data &b) {
		populate_wcdma_sweep(t, b, pb_.get());
	}
	void populate_lte_sweep(const std::vector<lte_data> &t, const basic_data &b) {
		populate_lte_sweep(t, b, pb_.get());
	}
	void populate_power_spectrum(const power_spectrum_data &t) {
		populate_power_spectrum(t, pb_.get());
	}
	void populate_iq_data(const iq_data &t) {
		populate_iq_data(t, pb_.get());
	}

	hardware get_hardware() {
		hardware t;
		device_info_pb::populate(pb_->device(), t);
		return t;
	}
	gps get_gps() {
		gps t;
		gps_pb::populate(pb_->gps(), t);
		return t;
	}
	std::vector<gsm_data> get_gsm_full_scan() {
		std::vector<gsm_data> t;
		gsm_update_pb::populate(pb_->gsm_full_scan(), t);
		return t;
	}
	basic_data get_gsm_full_scan_basic() {
		basic_data t;
		base_pb::populate(pb_->gsm_full_scan().base(), t);
		return t;
	}
	std::vector<umts_data> get_wcdma_full_scan() {
		std::vector<umts_data> t;
		wcdma_update_pb::populate(pb_->wcdma_full_scan(), t);
		return t;
	}
	basic_data get_wcdma_full_scan_basic() {
		basic_data t;
		base_pb::populate(pb_->wcdma_full_scan().base(), t);
		return t;
	}
	std::vector<lte_data> get_lte_full_scan() {
		std::vector<lte_data> t;
		lte_update_pb::populate(pb_->lte_full_scan(), t);
		return t;
	}
	basic_data get_lte_full_scan_basic() {
		basic_data t;
		base_pb::populate(pb_->lte_full_scan().base(), t);
		return t;
	}
	std::vector<gsm_data> get_gsm_sweep() {
		std::vector<gsm_data> t;
		gsm_update_pb::populate(pb_->gsm_sweep(), t);
		return t;
	}
	basic_data get_gsm_sweep_basic() {
		basic_data t;
		base_pb::populate(pb_->gsm_sweep().base(), t);
		return t;
	}
	std::vector<umts_data> get_wcdma_sweep() {
		std::vector<umts_data> t;
		wcdma_update_pb::populate(pb_->wcdma_sweep(), t);
		return t;
	}
	basic_data get_wcdma_sweep_basic() {
		basic_data t;
		base_pb::populate(pb_->wcdma_sweep().base(), t);
		return t;
	}
	std::vector<lte_data> get_lte_sweep() {
		std::vector<lte_data> t;
		lte_update_pb::populate(pb_->lte_sweep(), t);
		return t;
	}
	basic_data get_lte_sweep_basic() {
		basic_data t;
		base_pb::populate(pb_->lte_sweep().base(), t);
		return t;
	}
	power_spectrum_data get_power_spectrum() {
		power_spectrum_data t;
		power_spectrum_pb::populate(pb_->power_spectrum(), t);
		return t;
	}
	iq_data get_iq_data() {
		iq_data t;
		iq_data_pb::populate(pb_->iq_data(), t);
		return t;
	}

	static void populate_message(const ::rp_status s, const std::string &str, rp_update *pb) {
		message_pb::populate(s, str, pb->mutable_msg());
	}
	static void populate_log(const std::string &str, rp_update *pb) {
		log_pb::populate(str, pb->mutable_log());
	}
	static void populate_device_info(const hardware &t, rp_update *pb) {
		device_info_pb::populate(t, pb->mutable_device());
	}
	static void populate_gps(const gps &t, rp_update *pb) {
		gps_pb::populate(t, pb->mutable_gps());
	}
	static void populate_gsm_full_scan(const std::vector<gsm_data> &t, const basic_data &b, rp_update *pb) {
		gsm_update_pb::populate(t, b, pb->mutable_gsm_full_scan());
	}
	static void populate_wcdma_full_scan(const std::vector<umts_data> &t, const basic_data &b, rp_update *pb) {
		wcdma_update_pb::populate(t, b, pb->mutable_wcdma_full_scan());
	}
	static void populate_lte_full_scan(const std::vector<lte_data> &t, const basic_data &b, rp_update *pb) {
		lte_update_pb::populate(t, b, pb->mutable_lte_full_scan());
	}
	static void populate_gsm_sweep(const std::vector<gsm_data> &t, const basic_data &b, rp_update *pb) {
		gsm_update_pb::populate(t, b, pb->mutable_gsm_sweep());
	}
	static void populate_wcdma_sweep(const std::vector<umts_data> &t, const basic_data &b, rp_update *pb) {
		wcdma_update_pb::populate(t, b, pb->mutable_wcdma_sweep());
	}
	static void populate_lte_sweep(const std::vector<lte_data> &t, const basic_data &b, rp_update *pb) {
		lte_update_pb::populate(t, b, pb->mutable_lte_sweep());
	}
	static void populate_power_spectrum(const power_spectrum_data &t, rp_update *pb) {
		power_spectrum_pb::populate(t, pb->mutable_power_spectrum());
	}
	static void populate_iq_data(const iq_data &t, rp_update *pb) {
		iq_data_pb::populate(t, pb->mutable_iq_data());
	}

};

}}