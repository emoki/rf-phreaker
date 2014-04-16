#pragma once

#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include <memory>
#include <string>

class QSettings;

namespace rf_phreaker
{
// Group keys
static const std::string standard_output_group_key = "standard_output";
static const std::string signal_slot_output_group_key = "signal_slot_output";
static const std::string packet_output_group_key = "packet_output";
static const std::string umts_sweep_collection_group_key = "umts_sweep_collection";
static const std::string umts_layer_3_collection_group_key = "umts_layer_3_collection";
static const std::string lte_sweep_collection_group_key = "lte_sweep_collection";
static const std::string lte_layer_3_collection_group_key = "lte_layer_3_collection";
static const std::string umts_decode_thresholds_group_key = "umts_decode_thresholds";
static const std::string lte_decode_thresholds_group_key = "lte_decode_thresholds";
static const std::string umts_sweep_general_group_key = "umts_sweep_general";
static const std::string umts_layer_3_general_group_key = "umts_layer_3_general";
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

// Default Values
static const bool settings_output_raw_packets_default = false;
static const int settings_log_level_default = 3;
static const frequency_type settings_sampling_rate_default = 4875000;
static const frequency_type settings_bandwidth_default = 5000000;
static const time_type settings_collection_time_default = milli_to_nano(32);
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

class settings_io
{
public:
	settings_io(const std::string &application_name, const std::string &organization);

	settings_io(const std::string &filename);

	~settings_io();

	void read(settings &settings);

	void read(output_settings &settings, const std::string &group_key);

	void read(collection_settings &settings, const std::string &group_key);

	void read(layer_3_settings &settings, const std::string &group_key);

	void read(umts_general_settings &settings, const std::string &group_key);

	void write(const settings &settings);

	void write(const output_settings &settings, const std::string &group_key);

	void write(const collection_settings &settings, const std::string &group_key);

	void write(const layer_3_settings &settings, const std::string &group_key);

	void write(const umts_general_settings &settings, const std::string &group_key);

	void clear();


private:
	std::unique_ptr<QSettings> qsettings_;
};


} 