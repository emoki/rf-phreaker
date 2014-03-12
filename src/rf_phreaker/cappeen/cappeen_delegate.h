#pragma once

#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace cappeen_api {

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

	void initialize(processing::data_output_async *data_output)
	{
		data_output->connect_hardware(boost::bind(&cappeen_delegate::output_hardware, this, _1)).wait();
		data_output->connect_gps(boost::bind(&cappeen_delegate::output_gps, this, _1)).wait();
		data_output->connect_umts_sweep(boost::bind(&cappeen_delegate::output_umts_sweep, this, _1)).wait();
		data_output->connect_umts_layer_3(boost::bind(&cappeen_delegate::output_umts_layer_3, this, _1)).wait();
		data_output->connect_lte_sweep(boost::bind(&cappeen_delegate::output_lte_sweep, this, _1)).wait();
		data_output->connect_lte_layer_3(boost::bind(&cappeen_delegate::output_lte_layer_3, this, _1)).wait();
	}

	void output_hardware(const hardware &t)
	{
		// Do nothing.  Do we need hardware output??
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
	}
	
	void output_umts_layer_3(const std::vector<umts_data> &t)
	{
	}
	
	void output_lte_sweep(const basic_data &t)
	{}
	
	void output_lte_layer_3(const std::vector<lte_data> &t)
	{}

	void output_message(const std::exception &err)
	{
		output_error(err.what(), beagle_api::STD_EXCEPTION_ERROR);
	}

	void output_message(const rf_phreaker::rf_phreaker_error &err)
	{
		output_message(err.what(), (int)err.error_code_);
	}

	void output_error(const std::string &s, int code)
	{
		if(delegate_ != nullptr) {
			delegate_->available_error(beagle_id_, code, s.c_str(), s.size() + 1);
			if(beagle_info_.state_ == beagle_api::BEAGLE_COLLECTING
				   || beagle_info_.state_ == beagle_api::BEAGLE_USBOPENED
				   || beagle_info_.state_ == beagle_api::BEAGLE_READY
				   || beagle_info_.state_ == beagle_api::BEAGLE_WARMINGUP)
			   change_beagle_state(beagle_api::BEAGLE_ERROR);
		}
	}

	void output_message(const std::string &s, int code)
	{
		if(delegate_ != nullptr)
			delegate_->available_error(beagle_id_, code, s.c_str(), s.size() + 1);
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
		beagle_info_.dds_clock_correction_calibration_date_ = 0;
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
		
		//valid_licenses_.push_back(beagle_api::LTE_BAND_12);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_13);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_14);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_17);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_28);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_29);

		//valid_licenses_.push_back(beagle_api::LTE_BAND_5);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_6);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_18);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_19);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_20);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_26);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_27);

		//valid_licenses_.push_back(beagle_api::LTE_BAND_8);

		//valid_licenses_.push_back(beagle_api::LTE_BAND_3);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_9);

		//valid_licenses_.push_back(beagle_api::LTE_BAND_2);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_25);

		//valid_licenses_.push_back(beagle_api::LTE_BAND_1);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_4);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_10);
		//valid_licenses_.push_back(beagle_api::LTE_BAND_23);

		//valid_licenses_.push_back(beagle_api::LTE_BAND_7);

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
private:
	beagle_api::beagle_delegate *delegate_;

	beagle_api::beagle_info beagle_info_;

	std::vector<beagle_api::BANDS> bands_;

	std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> valid_licenses_;

	static const int beagle_id_ = 1;

};

}}