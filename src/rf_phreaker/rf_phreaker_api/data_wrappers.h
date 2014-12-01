#pragma once

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
			if(++i >= RP_FREQUENCY_PATH_SIZE)
				break;
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
		buf_.speed_ = t.speed_;
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

class umts_wrap {
public:
	umts_wrap(const umts_data &t) {
		buf_.base_ = basic_wrap(t).buf_;
		buf_.uarfcn_ = t.uarfcn_;
		buf_.operating_band_ = to_api_operating_band(t.operating_band_);
		buf_.cpich_ = t.cpich_;
		buf_.ecio_ = t.ecio_;
		buf_.rscp_ = t.rscp_;
	}
	rp_umts buf_;
	typedef rp_umts buf_type;
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
	}
	rp_lte buf_;
	typedef rp_lte buf_type;
};




}}