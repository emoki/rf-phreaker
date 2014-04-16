#pragma once

#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen/operating_band_conversion.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/processing/gps_graph.h"

namespace rf_phreaker { namespace cappeen_api {

inline int convert_message(int msg)
{
	beagle_api::ERRORCODES code;
	switch(msg) {
	case (int)UNKNOWN_ERROR:
		code = beagle_api::UNKNOWN_ERROR;
		break;
	case (int)GENERAL_ERROR:
		code = beagle_api::GENERAL_ERROR;
		break;
	case (int)STD_EXCEPTION_ERROR:
		code = beagle_api::STD_EXCEPTION_ERROR;
		break;
	default:
		code = static_cast<beagle_api::ERRORCODES>(msg);
	}
	return code;
}

class cappeen_delegate
{
public:
	cappeen_delegate(beagle_api::beagle_delegate *del)
		: delegate_(del)
	{
		if(del == nullptr)
			throw rf_phreaker::cappeen_api_error("Beagle delegate is NULL.", beagle_api::BEAGLEUNABLETOINITIALIZE);

		beagle_info_.state_ = beagle_api::BEAGLE_USBCLOSED;
		beagle_info_.beagle_id_ = beagle_id_;
		memset(beagle_info_.beagle_serial_, 0, sizeof(beagle_info_.beagle_serial_));
		beagle_info_.dds_clock_correction_calibration_date_ = 0;
		beagle_info_.rf_calibration_date_ = 0;
		beagle_info_.available_bands_in_hardware_.elements_ = 0;
		beagle_info_.available_bands_in_hardware_.num_elements_ = 0;
		beagle_info_.valid_licenses_.elements_ = 0;
		beagle_info_.valid_licenses_.num_elements_ = 0;
		beagle_info_.device_speed_ = beagle_api::UNKOWN_SPEED;
	}
	
	~cappeen_delegate()
	{}

	void initialize(processing::data_output_async *data_output, processing::processing_graph *pro, processing::gps_graph *gps)
	{
		LOG_L(VERBOSE) << "Creating connections...";
		LOG_L(VERBOSE) << "Connecting hardware.";
		data_output->connect_hardware(boost::bind(&cappeen_delegate::output_hardware, this, _1)).get();
		LOG_L(VERBOSE) << "Connecting gps.";
		data_output->connect_gps(boost::bind(&cappeen_delegate::output_gps, this, _1)).get();
		LOG_L(VERBOSE) << "Connecting umts_sweep.";
		data_output->connect_umts_sweep(boost::bind(&cappeen_delegate::output_umts_sweep, this, _1)).get();
		LOG_L(VERBOSE) << "Connecting umts_layer_3.";
		data_output->connect_umts_layer_3(boost::bind(&cappeen_delegate::output_umts_layer_3, this, _1)).get();
		LOG_L(VERBOSE) << "Connecting lte_sweep.";
		data_output->connect_lte_sweep(boost::bind(&cappeen_delegate::output_lte_sweep, this, _1)).get();
		LOG_L(VERBOSE) << "Connecting lte_layer_3.";
		data_output->connect_lte_layer_3(boost::bind(&cappeen_delegate::output_lte_layer_3, this, _1)).get();

		LOG_L(VERBOSE) << "Creating log sinks...";
		LOG_L(VERBOSE) << "Connecting error.";
		delegate_sink_async::instance().connect_error(boost::bind(&cappeen_delegate::output_error, this, _1, _2)).get();
		LOG_L(VERBOSE) << "Connecting message.";
		delegate_sink_async::instance().connect_message(boost::bind(&cappeen_delegate::output_message, this, _1, _2)).get();

		processing_graph_ = pro;
		gps_graph_ = gps;
	}

	void output_hardware(const hardware &t)
	{
		initialize_beagle_info(t);
		change_beagle_state(current_beagle_state());
		//delegate_->available_beagle_info(beagle_id_, *beagle_info_);
	}
	
	void output_gps(const gps &t)
	{
		beagle_api::gps_info g;
		g.gps_locked_ = t.lock_;
		g.hw_calibrated_ = false;
		g.lat_ = t.latitude_;
		g.lon_ = t.longitude_;
		g.num_track_sat_ = t.tracking_satellites_;
		g.num_visible_sat_ = t.visible_satellites_;
		g.raw_gps_status_ = (uint16_t)t.raw_status_;
		g.utc_time_ = t.coordinated_universal_time_;

		delegate_->available_gps_info(beagle_id_, g);
	}
	
	void output_umts_sweep(const basic_data &t)
	{
		beagle_api::umts_sweep_info a;
		a.frequency_ = (uint32_t)t.carrier_frequency_;
		a.rssi_ = (int32_t)t.carrier_signal_level_;

		delegate_->available_umts_sweep_info(beagle_id_, &a, 1);
	}
	
	void output_umts_layer_3(const std::vector<umts_data> &t)
	{
		std::vector<beagle_api::umts_sector_info> v(t.size());
		std::vector<beagle_api::gsm_neighbor_inter_rat> inter_rat_buf;
		int i = 0;
		for(auto &umts : t) {
			v[i].band_ = convert_band_to_hw_band(umts.operating_band_);
			v[i].carrier_freq_ = umts.carrier_frequency_ / 1e6;
			v[i].carrier_sl_ = umts.carrier_signal_level_;
			v[i].collection_round_ = (uint32_t)umts.collection_round_;
			v[i].cpich_ = umts.cpich_;
			v[i].uarfcn_ = umts.uarfcn_;
			v[i].ecio_ = umts.ecio_;
			v[i].rscp_ = umts.rscp_;
			v[i].mcc_ = umts.layer_3_.mcc_.to_uint16();
			v[i].mcc_three_digits_ = umts.layer_3_.mcc_.num_characters() == 3 ? true : false;
			v[i].mnc_ = umts.layer_3_.mnc_.to_uint16();
			v[i].mcc_three_digits_ = umts.layer_3_.mnc_.num_characters() == 3 ? true : false;
			v[i].lac_ = umts.layer_3_.lac_;
			v[i].cell_id_ = umts.layer_3_.cid_;
			

			v[i].neighbor_intra_group_.num_elements_ = umts.layer_3_.neighbor_intra_group_.size();
			v[i].neighbor_intra_group_.elements_ = 0;
			if(v[i].neighbor_intra_group_.num_elements_) {
				v[i].neighbor_intra_group_.elements_ = (beagle_api::cpich_type*)&umts.layer_3_.neighbor_intra_group_[0];
				//int j = 0;
				//for(auto &intra : umts.layer_3_.neighbor_intra_group_) {
				//	v[i].neighbor_intra_group_.elements_[j] = intra;
				//	++j;
				//}
			}
		

			v[i].neighbor_inter_group_.num_elements_ = umts.layer_3_.neighbor_inter_group_.size();
			v[i].neighbor_inter_group_.elements_ = 0;
			if(v[i].neighbor_inter_group_.num_elements_) {
				v[i].neighbor_inter_group_.elements_ = (beagle_api::neighbor_inter*)&umts.layer_3_.neighbor_inter_group_[0];
				//int j = 0;
				//for(auto &inter : umts.layer_3_.neighbor_inter_group_) {
				//	v[i].neighbor_inter_group_.elements_[j].channel_ = inter.uarfcn_;
				//	v[i].neighbor_inter_group_.elements_[j].cpich_ = inter.cpich_;
				//	++j;
				//}
			}
			

			v[i].gsm_neighbor_inter_rat_group_.num_elements_ = umts.layer_3_.neighbor_inter_rat_group_.size();
			v[i].gsm_neighbor_inter_rat_group_.elements_ = 0;
			if(v[i].gsm_neighbor_inter_rat_group_.num_elements_) {
				int j = 0;
				int offset = inter_rat_buf.size();
				inter_rat_buf.resize(v[i].gsm_neighbor_inter_rat_group_.num_elements_ + offset);
				for(auto &inter_rat : umts.layer_3_.neighbor_inter_rat_group_) {

					inter_rat_buf[offset + j].band_indicator_ =
						inter_rat.band_indicator_ == layer_3_information::dcs_1800_was_used ? beagle_api::dcs_1800_was_used : beagle_api::pcs_1900_was_used;
					inter_rat_buf[offset + j].channel_ = inter_rat.arfcn_;
					inter_rat_buf[offset + j].rssi_ = (int8_t)inter_rat.qrx_lev_min_;
					memcpy(inter_rat_buf[offset + j].bsic_, inter_rat.bsic_.to_string(), 3);
					++j;
				}
				v[i].gsm_neighbor_inter_rat_group_.elements_ = &inter_rat_buf[offset];
			}

			++i;
		}

		delegate_->available_umts_sector_info(beagle_id_, &v[0], v.size());
	}
	
	void output_lte_sweep(const basic_data &t)
	{
		beagle_api::lte_sweep_info a;
		a.frequency_ = (uint32_t)t.carrier_frequency_;
		a.rssi_ = (int32_t)t.carrier_signal_level_;

		delegate_->available_lte_sweep_info(beagle_id_, &a, 1);
	}
	
	void output_lte_layer_3(const std::vector<lte_data> &t)
	{
		std::vector<beagle_api::lte_sector_info> v(t.size());
		std::vector<beagle_api::lte_sib_1> sib1;
		std::vector<beagle_api::plmn> plmns;
		int i = 0;
		for(auto &lte : t) {
			v[i].antenna_ports_ = lte.num_antenna_ports_;
			v[i].carrier_bandwidth_ = lte.carrier_bandwidth_;
			v[i].carrier_freq_ = static_cast<uint32_t>(lte.carrier_frequency_);
			v[i].carrier_sl_ = lte.carrier_signal_level_;
			v[i].collection_round_ = static_cast<uint32_t>(lte.collection_round_);
			v[i].cyclic_prefix_length_ = lte.cyclic_prefix_;
			v[i].earfcn_ = lte.earfcn_;
			v[i].lte_operating_band_ = convert_band_to_tech_band(lte.operating_band_);
			v[i].physical_cell_id_ = lte.physical_cell_id_;
			v[i].primary_sync_id_ = lte.psch_id_;
			v[i].primary_sync_quality_ = lte.psch_quality_;
			v[i].rsrp_ = lte.rsrp_;
			v[i].rsrq_ = lte.rsrq_;
			v[i].rssi_ = lte.rssi_;
			v[i].secondary_sync_id_ = lte.ssch_id_;
			v[i].secondary_sync_quality_ = lte.ssch_quality_;
			v[i].system_frame_number_ = lte.frame_number_;
			v[i].sib_1_.decoded_ = lte.layer_3_.is_cid_decoded();
			if(v[i].sib_1_.decoded_) {
				v[i].sib_1_.plmns_.num_elements_ = 1;
				beagle_api::plmn p;
				memcpy(p.mcc_, lte.layer_3_.mcc_.to_string(), lte.layer_3_.mcc_.num_characters());
				memcpy(p.mnc_, lte.layer_3_.mnc_.to_string(), lte.layer_3_.mnc_.num_characters());
				plmns.push_back(p);
				v[i].sib_1_.plmns_.elements_ = &plmns[0];
			}
			else {
				v[i].sib_1_.plmns_.num_elements_ = 0;
				v[i].sib_1_.plmns_.elements_ = 0;
			}

			++i;
		}

		delegate_->available_lte_sector_info(beagle_id_, &v[0], v.size());
	}

	void output_error_as_message(const std::exception &err)
	{
		LOG_L(ERROR) << err.what();
		output_error(err.what(), beagle_api::STD_EXCEPTION_ERROR);
	}

	void output_error_as_message(const rf_phreaker::rf_phreaker_error &err)
	{
		LOG_L(ERROR) << err.what();
		output_message(err.what(), convert_message(err.error_code_));
	}

	void output_error_as_message(const std::string &s, int code)
	{
		LOG_L(ERROR) << s;
		if(delegate_ != nullptr)
			delegate_->available_error(beagle_id_, code, s.c_str(), s.size() + 1);
	}

	void output_error(const std::string &s, int code)
	{
		LOG_L(ERROR) << s;
		if(delegate_ != nullptr) {
			if(beagle_info_.state_ == beagle_api::BEAGLE_COLLECTING
				   || beagle_info_.state_ == beagle_api::BEAGLE_USBOPENED
				   || beagle_info_.state_ == beagle_api::BEAGLE_READY
				   || beagle_info_.state_ == beagle_api::BEAGLE_WARMINGUP) {
				if(processing_graph_) processing_graph_->cancel_and_wait();
				if(gps_graph_) gps_graph_->cancel_and_wait();
				change_beagle_state(beagle_api::BEAGLE_ERROR);
			}
			delegate_->available_error(beagle_id_, convert_message(code), s.c_str(), s.size() + 1);
		}
	}

	void output_message(const std::string &s, int code)
	{
		LOG_L(INFO) << s;
		if(delegate_ != nullptr)
			delegate_->available_message(beagle_id_, code, s.c_str(), s.size() + 1);
	}

	void change_beagle_state(beagle_api::BEAGLESTATE state)
	{
		beagle_info_.state_ = state;
		delegate_->available_beagle_info(beagle_id_, beagle_info_);
	}

	void initialize_beagle_info(const hardware &t)
	{
		beagle_info_.beagle_id_ = beagle_id_;
		memset(beagle_info_.beagle_serial_, 0, sizeof(beagle_info_.beagle_serial_));
		memcpy(beagle_info_.beagle_serial_, t.scanner_id_.c_str(), t.scanner_id_.size());
		beagle_info_.dds_clock_correction_calibration_date_ = t.frequency_correction_calibration_date_;
		beagle_info_.rf_calibration_date_ = t.rf_calibration_date_;

		bands_.clear();
		//for(auto &path : t.frequency_paths_) {
		//}
		bands_.push_back(beagle_api::BAND_700);
		bands_.push_back(beagle_api::BAND_850);
		bands_.push_back(beagle_api::BAND_900);
		bands_.push_back(beagle_api::BAND_1800);
		bands_.push_back(beagle_api::BAND_1900);
		bands_.push_back(beagle_api::BAND_2100);
		bands_.push_back(beagle_api::BAND_2600);
		beagle_info_.available_bands_in_hardware_.num_elements_ = bands_.size();
		beagle_info_.available_bands_in_hardware_.elements_ = &bands_[0];

		

		valid_licenses_.clear();
		//for(auto &license : t.valid_licenses_) {
		//}
		valid_licenses_.push_back(beagle_api::WCDMA_BAND_850);
		valid_licenses_.push_back(beagle_api::WCDMA_BAND_900);
		valid_licenses_.push_back(beagle_api::WCDMA_BAND_1800);
		valid_licenses_.push_back(beagle_api::WCDMA_BAND_1900);
		valid_licenses_.push_back(beagle_api::WCDMA_BAND_2100);
		
		valid_licenses_.push_back(beagle_api::LTE_BAND_12);
		valid_licenses_.push_back(beagle_api::LTE_BAND_13);
		valid_licenses_.push_back(beagle_api::LTE_BAND_14);
		valid_licenses_.push_back(beagle_api::LTE_BAND_17);
		valid_licenses_.push_back(beagle_api::LTE_BAND_28);
		valid_licenses_.push_back(beagle_api::LTE_BAND_29);

		valid_licenses_.push_back(beagle_api::LTE_BAND_5);
		valid_licenses_.push_back(beagle_api::LTE_BAND_6);
		valid_licenses_.push_back(beagle_api::LTE_BAND_18);
		valid_licenses_.push_back(beagle_api::LTE_BAND_19);
		valid_licenses_.push_back(beagle_api::LTE_BAND_20);
		valid_licenses_.push_back(beagle_api::LTE_BAND_26);
		valid_licenses_.push_back(beagle_api::LTE_BAND_27);

		valid_licenses_.push_back(beagle_api::LTE_BAND_8);

		valid_licenses_.push_back(beagle_api::LTE_BAND_3);
		valid_licenses_.push_back(beagle_api::LTE_BAND_9);

		valid_licenses_.push_back(beagle_api::LTE_BAND_2);
		valid_licenses_.push_back(beagle_api::LTE_BAND_25);

		valid_licenses_.push_back(beagle_api::LTE_BAND_1);
		valid_licenses_.push_back(beagle_api::LTE_BAND_4);
		valid_licenses_.push_back(beagle_api::LTE_BAND_10);
		valid_licenses_.push_back(beagle_api::LTE_BAND_23);

		valid_licenses_.push_back(beagle_api::LTE_BAND_7);

		beagle_info_.valid_licenses_.num_elements_ = valid_licenses_.size();
		beagle_info_.valid_licenses_.elements_ = &valid_licenses_[0];

		switch(t.device_speed_) {
		case rf_phreaker::device_speed::USB_HI_SPEED:
			beagle_info_.device_speed_ = beagle_api::USB_HI_SPEED;
			break;
		case rf_phreaker::device_speed::USB_SUPER_SPEED:
			beagle_info_.device_speed_ = beagle_api::USB_SUPER_SPEED;
			break;
		case rf_phreaker::device_speed::UNKNOWN_SPEED:
		default:
			beagle_info_.device_speed_ = beagle_api::UNKOWN_SPEED;
		}
	}

	beagle_api::BEAGLESTATE current_beagle_state() { return beagle_info_.state_; }

private:
	beagle_api::beagle_delegate *delegate_;

	beagle_api::beagle_info beagle_info_;

	std::vector<beagle_api::BANDS> bands_;

	std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> valid_licenses_;

	static const int beagle_id_ = 1;

	processing::processing_graph *processing_graph_;
	processing::gps_graph *gps_graph_;
};

}}