#pragma once

#include <stdint.h>
#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker
{

// Default Values
static const bool settings_output_raw_packets_default = false;
static const int settings_log_level_default = 3;
static const frequency_type settings_sampling_rate_default = 4875000;
static const frequency_type settings_bandwidth_default = 5000000;
static const time_type settings_collection_time_default = (32000000);
static const int settings_layer_3_max_update_threshold_default = 150;
static const int settings_layer_3_min_collection_round_default = 5;
static const int settings_layer_3_decode_threshold_default = -13;
static const int settings_layer_3_min_decode_threshold_default = -21;
static const int settings_umts_general_sensitivity_default = -23;
static const int settings_umts_general_full_scan_interval_default = 1;
static const int settings_umts_general_num_coherent_slots_default = 2;
static const bool settings_output_default = false;
static const int gps_collection_period_ms_default = 800;
static const int num_items_in_flight_default = 0;
static const int initial_frequency_correction_offset_start_default = (-3000);
static const int initial_frequency_correction_offset_end_default = (3000);
static const bool use_rf_board_adjustment_default = true;
static const int blade_log_level_default = 2;
static const int blade_rx_sync_num_buffers_default = 5;
static const int blade_rx_sync_buffer_size_default = 1024 * 4;
static const int blade_rx_sync_num_transfers_default = 4;
static const int blade_rx_sync_timeout_default = 2000;
static const std::string output_directory_default = "NULL";
static const bool output_in_binary_default = true;

class output_settings {
public:
	bool scanner_;
	bool gps_;
	bool umts_sweep_;
	bool umts_layer_3_;
	bool lte_sweep_;
	bool lte_layer_3_;
};

class collection_settings {
public:
	frequency_type sampling_rate_;
	bandwidth_type bandwidth_;
	time_type collection_time_;
};

class layer_3_settings {
public:
	int32_t max_update_threshold_;
	int32_t minimum_collection_round_;
	double decode_threshold_;
	double decode_minimum_threshold_;
};

class umts_general_settings /* Find a better description? */
{
public:
	double sensitivity_;
	int32_t full_scan_interval_;
	int32_t num_coherent_slots_;
};

class frequency_correction_settings {
public:
	int initial_frequency_correction_range_start_;
	int initial_frequency_correction_range_end_;
	//int initial_increment_;
	//int second_increment_;

	umts_general_settings general_settings_;
};

class scanner_settings {};
class blade_settings : public scanner_settings {
public:
	blade_settings()
		: log_level_(blade_log_level_default)
		, rx_sync_num_buffers_(blade_rx_sync_num_buffers_default)
		, rx_sync_buffer_size_(blade_rx_sync_buffer_size_default)
		, rx_sync_num_transfers_(blade_rx_sync_num_transfers_default)
		, rx_sync_timeout_(blade_rx_sync_timeout_default) {}
	int log_level_;
	int rx_sync_num_buffers_;
	int rx_sync_buffer_size_;
	int rx_sync_num_transfers_;
	int rx_sync_timeout_;
};

class settings {
public:
	// TODO - Change these to system settings, general settings or something.
	int log_level_;
	int gps_collection_period_ms_;
	int num_items_in_flight_;
	bool use_rf_board_adjustment_;
	std::string output_directory_;
	bool output_in_binary_;

	blade_settings blade_settings_;

	output_settings packet_output_;
	output_settings standard_output_;
	output_settings file_output_;
	output_settings signal_slots_;

	collection_settings umts_sweep_collection_;
	collection_settings umts_layer_3_collection_;
	collection_settings lte_sweep_collection_;
	collection_settings lte_layer_3_collection_;

	layer_3_settings umts_decode_layer_3_;
	layer_3_settings lte_decode_layer_3_;

	umts_general_settings umts_sweep_general_;
	umts_general_settings umts_layer_3_general_;

	frequency_correction_settings frequency_correction_settings_;


	//double umts_fast_sweep_threshold_;
	//double umts_deep_sweep_threshold_;
	//double umts_sweep_threshold_;
	//double umts_scan_threshold_;
	//int32_t umts_full_scan_interval_;
};

}