#pragma once

#include <stdint.h>

#include "rf_phreaker/common/common_types.h"


namespace rf_phreaker {

	struct gps
	{
		scanner_serial_type scanner_id_;
		bool lock_;
		int64_t coordinated_universal_time_;  
		int32_t visible_satelites_;
		int32_t tracking_satelites_;
		double latitude_;
		double longitude_;
		int32_t speed_;
		int64_t raw_status_;
	};


	struct basic_technology_data
	{
		scanner_serial_type scanner_id_;
		int64_t collection_round_;
		double carrier_signal_level_;
		frequency_type carrier_frequency_;
		bandwidth_type carrier_bandwidth_;
		int64_t time_;
		int32_t status_flags_;
	};


	struct lte_data
	{
		basic_technology_data basic_;
		// Temporary members
		double psch_norm_corr_;
		double ssch_norm_corr_;
		double rs_norm_corr_;
		int cyclic_prefix_;
		int num_antenna_ports_;
		double average_digital_voltage_;
		uint32_t frame_number;
		double rsrp_;
		double rssi_;
		double rsrq_;
		uint32_t  cid_;
		uint32_t lac_;
		char mcc_[4];
		char mnc_[4];

	};

}