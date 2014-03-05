#pragma once

#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include <memory>
#include <string>

class QSettings;

namespace rf_phreaker
{
// Group keys
static const std::string umts_sweep_collection_group_key = "umts_sweep_collection";
static const std::string umts_layer_3_collection_group_key = "umts_layer_3_collection";
static const std::string lte_sweep_collection_group_key = "lte_sweep_collection";
static const std::string lte_layer_3_collection_group_key = "lte_layer_3_collection";
static const std::string umts_decode_thresholds_group_key = "umts_decode_thresholds";
static const std::string lte_decode_thresholds_group_key = "lte_decode_thresholds";
static const std::string umts_sweep_general_group_key = "umts_sweep_general";
static const std::string umte_layer_3_general_group_key = "umts_layer_3_general";

// Value keys
static const std::string output_raw_packets_key = "output_raw_packets";
static const std::string log_level_key = "log_level";
static const std::string sampling_rate_key = "sampling_rate";
static const std::string bandwidth_key = "bandwidth";
static const std::string collection_time_key = "collection_time";
static const std::string max_update_threshold_key = "max_update_threshold";
static const std::string decode_threshold_key = "decode_threshold";
static const std::string min_decode_threshold_key = "min_decode_threshold";
static const std::string sensitivity_key = "sensitivity";
static const std::string full_scan_interval_key = "full_scan_interval";

// Default Values
static const bool settings_output_raw_packets_default = false;
static const int settings_log_level_default = 3;
static const frequency_type settings_sampling_rate_default = 3840000;
static const frequency_type settings_bandwidth_default = 5000000;
static const time_type settings_collection_time_default = milli_to_nano(32);
static const int settings_layer_3_max_update_threshold_default = 150;
static const int settings_layer_3_decode_threshold_default = -13;
static const int settings_layer_3_min_decode_threshold_default = -25;
static const int settings_umts_general_sensitivity_default = -25;
static const int settings_umts_general_full_scan_interval_default = 1;

class settings_io
{
public:
	settings_io(const std::string &application_name, const std::string &organization);

	~settings_io();

	void read(settings &settings);

	void read(collection_settings &settings, const std::string &group_key);

	void read(layer_3_settings &settings, const std::string &group_key);

	void read(umts_general_settings &settings, const std::string &group_key);

	void write(settings &settings);

	void write(collection_settings &settings, const std::string &group_key);

	void write(layer_3_settings &settings, const std::string &group_key);

	void write(umts_general_settings &settings, const std::string &group_key);

	void clear();


private:
	std::unique_ptr<QSettings> qsettings_;
};


} 