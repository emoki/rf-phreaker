#pragma once

#include <stdint.h>
#include <vector>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/license.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"

namespace rf_phreaker {

	struct hardware 
	{
		scanner_serial_type serial_;
		int32_t hw_id_;
		device_communication device_communication_;
		int64_t frequency_correction_calibration_date_;
		int64_t rf_calibration_date_;
		std::vector<frequency_path> frequency_paths_;
		license license_data_;
	};

	struct gps
	{
		scanner_serial_type serial_;
		bool lock_;
		int64_t coordinated_universal_time_;  
		int32_t visible_satellites_;
		int32_t tracking_satellites_;
		double latitude_;
		double longitude_;
		double altitude_;
		double angle_;
		double speed_;
		double dilution_of_precision_;
		double horizontal_accuracy_meters_;
		double vertical_accuracy_meters_;
		int64_t raw_status_;
		struct satellite {
			int32_t prn_;
			double snr_;
			double elevation_;
			double azimuth_;
		};
		std::vector<satellite> satellites_;
	};


	struct basic_data
	{
		scanner_serial_type serial_;
		int64_t collection_round_;
		frequency_type measurement_frequency_;
		bandwidth_type measurement_bandwidth_;
		double measurement_signal_level_;
		time_type time_;
		int32_t status_flags_;
	};

	struct gsm_data : public basic_data {
		channel_type arfcn_;
		operating_band operating_band_;
		int32_t bsic_;
		int32_t tdma_frame_number_;
		double cell_signal_level_;
		double ctoi_;
		layer_3_information::gsm_layer_3_message_aggregate layer_3_;
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
		double sync_quality_;
		int cyclic_prefix_;
		int num_antenna_ports_;
		int dl_bandwidth_;
		int32_t frame_number_;
		layer_3_information::lte_rrc_message_aggregate layer_3_;
	};

}