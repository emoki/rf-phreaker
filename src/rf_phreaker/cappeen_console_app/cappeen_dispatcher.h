#pragma once

#include <atomic>
#include "rf_phreaker/common/stats_tracker.h"
#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen_console_app/cappeen_delegate.h"
#include "rf_phreaker/cappeen_console_app/cappeen_io.h"

namespace cappeen_scanner {

	class gps_stats : public rf_phreaker::gps_stats {
	public:
		gps_stats(const beagle_api::gps_info &s) {
			current_second_ = s.utc_time_;
			seconds_seen_ = 1;
			sats_visible_ = s.num_visible_sat_;
			sats_tracking_ = s.num_track_sat_;
		}
	};

	class gsm_stats : public rf_phreaker::meas_stats {
	public:
		gsm_stats(const beagle_api::gsm_sector_info &s) {
			freq_ = s.carrier_freq_;
			identifier_ = s.bsic_;
			count_ = 1;
			total_sl_watts_ = pow(10, s.cell_sl_ / 10);
			max_sl_ = s.cell_sl_;
			min_sl_ = s.cell_sl_;
			total_interference_watts_ = pow(10, s.ctoi_ / 10);;
			max_interference_ = s.ctoi_;
			min_interference_ = s.ctoi_;
			decoded_layer_3_ = false;
		}
	};

	class umts_stats : public rf_phreaker::meas_stats {
	public:
		umts_stats(const umts_sector_info_wrapper &s) {
			freq_ = s.carrier_freq_;
			identifier_ = s.cpich_;
			count_ = 1;
			total_sl_watts_ = pow(10, s.rscp_ / 10.0);
			max_sl_ = s.rscp_;
			min_sl_ = s.rscp_;
			total_interference_watts_ = pow(10, s.ecio_ / 10.0);;
			max_interference_ = s.ecio_;
			min_interference_ = s.ecio_;
			decoded_layer_3_ = false;
		}
	};

	class lte_stats : public rf_phreaker::meas_stats {
	public:
		lte_stats(const lte_sector_info_wrapper &s) {
			freq_ = s.carrier_freq_;
			identifier_ = s.physical_cell_id_;
			count_ = 1;
			total_sl_watts_ = pow(10, s.carrier_sl_ / 10);
			max_sl_ = s.carrier_sl_;
			min_sl_ = s.carrier_sl_;
			auto sync_quality_watts = (pow(10, s.primary_sync_quality_ / 10) + pow(10, s.secondary_sync_quality_ / 10)) / 2.0;
			total_interference_watts_ = sync_quality_watts;
			auto sync_quality_db = 10 * log(sync_quality_watts);
			max_interference_ = sync_quality_db;
			min_interference_ = sync_quality_db;
			decoded_layer_3_ = false;
		}
	};

class cappeen_dispatcher
{
public:
	cappeen_dispatcher(boost::shared_ptr<cappeen_delegate> cappeen_delegate, const std::string &base_filename = "", bool log_to_stdout = true);

	~cappeen_dispatcher(void);

	void shut_down();

	bool has_fatal_error_occurred() const;

	bool is_calibrated() const;

	void reset_error() { fatal_error_has_occurred_ = false; }

	std::string serial() const { return beagle_info_.beagle_serial_; }

	uint32_t id() const { return beagle_info_.beagle_id_; }

	int32_t error_count() const { return error_count_; }

	rf_phreaker::stats_tracker<rf_phreaker::gps_stats> gps_stats_;
	rf_phreaker::stats_tracker<gsm_stats> gsm_stats_;
	rf_phreaker::stats_tracker<umts_stats> umts_stats_;
	rf_phreaker::stats_tracker<lte_stats> lte_stats_;

private:
	bool is_shutting_down();

	void dispatcher_thread();

	void dispatch_data();

	boost::shared_ptr<boost::thread> dispatcher_thread_;

	std::atomic_bool shutting_down_;

	boost::shared_ptr<cappeen_delegate> cappeen_delegate_;

	cappeen_io cappeen_io_;

	std::atomic_bool fatal_error_has_occurred_;

	std::atomic_bool is_calibrated_;

	std::atomic_int32_t error_count_;

	beagle_info_wrapper beagle_info_;
};


}