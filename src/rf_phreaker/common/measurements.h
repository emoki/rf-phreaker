#pragma once

#include <stdint.h>
#include <vector>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/license.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"

namespace rf_phreaker {

	struct frequency_path
	{
		frequency_path() : low_freq_(-1), high_freq_(-1) {}
		frequency_path(frequency_type start, frequency_type end) : low_freq_(start), high_freq_(end) {}
		frequency_type low_freq_;
		frequency_type high_freq_;
	};

	enum device_speed 
	{
		USB_HI_SPEED,
		USB_SUPER_SPEED,
		UNKNOWN_SPEED
	};
	
	struct hardware 
	{
		scanner_serial_type scanner_id_;
		device_speed device_speed_;
		int64_t frequency_correction_calibration_date_;
		int64_t rf_calibration_date_;
		std::vector<frequency_path> frequency_paths_;
		license license_data_;
	};

	struct gps
	{
		scanner_serial_type scanner_id_;
		bool lock_;
		int64_t coordinated_universal_time_;  
		int32_t visible_satellites_;
		int32_t tracking_satellites_;
		double latitude_;
		double longitude_;
		int32_t speed_;
		int64_t raw_status_;
	};


	struct basic_data
	{
		//scanner_serial_type scanner_id_;
		int64_t collection_round_;
		frequency_type carrier_frequency_;
		bandwidth_type carrier_bandwidth_;
		double carrier_signal_level_;
		int64_t time_;
		int32_t status_flags_;
	};

	struct umts_data : public basic_data
	{
		channel_type uarfcn_;
		operating_band operating_band_;
		int32_t cpich_;
		double ecio_;
		double rscp_;
		layer_3_information::umts_bcch_bch_message_aggregate layer_3_;
	};

	struct lte_data : public basic_data
	{
		channel_type earfcn_;
		operating_band operating_band_;
		int32_t physical_cell_id_;
		double rsrp_;
		double rsrq_;
		double rssi_;
		int32_t psch_id_;
		double psch_quality_;
		int32_t ssch_id_;
		double ssch_quality_;
		double rs_quality_;
		int cyclic_prefix_;
		int num_antenna_ports_;
		int dl_bandwidth_;
		int32_t frame_number_;
		layer_3_information::lte_rrc_message_aggregate layer_3_;
	};

}