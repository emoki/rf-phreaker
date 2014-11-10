#pragma once

#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include <memory>
#include <string>

class QSettings;

namespace rf_phreaker {
// Group keys
static const std::string standard_output_group_key = "standard_output";
static const std::string signal_slot_output_group_key = "signal_slot_output";
static const std::string packet_output_group_key = "packet_output";
static const std::string file_output_group_key = "file_output";
static const std::string umts_sweep_collection_group_key = "umts_sweep_collection";
static const std::string umts_layer_3_collection_group_key = "umts_layer_3_collection";
static const std::string lte_sweep_collection_group_key = "lte_sweep_collection";
static const std::string lte_layer_3_collection_group_key = "lte_layer_3_collection";
static const std::string umts_decode_thresholds_group_key = "umts_decode_thresholds";
static const std::string lte_decode_thresholds_group_key = "lte_decode_thresholds";
static const std::string umts_sweep_general_group_key = "umts_sweep_general";
static const std::string umts_layer_3_general_group_key = "umts_layer_3_general";
static const std::string frequency_correction_group_key = "frequency_correction";
static const std::string nuand_group_key = "nuand";

// Value keys
static const std::string scanner_output_key = "scanner_output";
static const std::string gps_output_key = "gps_output";
static const std::string umts_sweep_output_key = "umts_sweep_output";
static const std::string umts_layer_3_output_key = "umts_layer_3_output";
static const std::string lte_sweep_output_key = "lte_sweep_output";
static const std::string lte_layer_3_output_key = "lte_layer_3_output";
static const std::string output_raw_packets_key = "output_raw_packets";
static const std::string log_level_key = "log_level";
static const std::string sampling_rate_key = "sampling_rate";
static const std::string bandwidth_key = "bandwidth";
static const std::string collection_time_key = "collection_time";
static const std::string max_update_threshold_key = "max_update_threshold";
static const std::string min_collection_round_key = "min_collection_round";
static const std::string decode_threshold_key = "decode_threshold";
static const std::string min_decode_threshold_key = "min_decode_threshold";
static const std::string sensitivity_key = "sensitivity";
static const std::string full_scan_interval_key = "full_scan_interval";
static const std::string num_coherent_slots_key = "num_coherent_slots";
static const std::string gps_collection_period_ms_key = "gps_collection_period";
static const std::string num_items_in_flight_key = "num_items_in_flight";
static const std::string initial_frequency_correction_offset_start_key = "start_offset";
static const std::string initial_frequency_correction_offset_end_key = "end_offset";
static const std::string use_rf_board_adjustment_key = "use_rf_board_adjustment";
static const std::string blade_log_level_key = "log_level";
static const std::string blade_rx_sync_num_buffers_key = "rx_sync_num_buffers";
static const std::string blade_rx_sync_buffer_size_key = "rx_sync_buffer_size";
static const std::string blade_rx_sync_num_transfers_key = "rx_sync_num_transfers";
static const std::string blade_rx_sync_timeout_key = "rx_sync_num_timeout";
static const std::string output_directory_key = "output_directory";
static const std::string output_in_binary_key = "output_in_binary";
class settings_io {
public:
	settings_io(const std::string &application_name, const std::string &organization);

	settings_io(const std::string &filename);

	~settings_io();

	void read(settings &settings);

	void read(output_settings &settings, const std::string &group_key);

	void read(collection_settings &settings, const std::string &group_key);

	void read(layer_3_settings &settings, const std::string &group_key);

	void read(umts_general_settings &settings, const std::string &group_key);

	void read(frequency_correction_settings &settings, const std::string &group_key);

	void read(blade_settings &settings);

	void write(const settings &settings);

	void write(const output_settings &settings, const std::string &group_key);

	void write(const collection_settings &settings, const std::string &group_key);

	void write(const layer_3_settings &settings, const std::string &group_key);

	void write(const umts_general_settings &settings, const std::string &group_key);

	void write(const frequency_correction_settings &settings, const std::string &group_key);

	void write(const blade_settings &settings);

	void clear();

private:
	std::unique_ptr<QSettings> qsettings_;
};


}