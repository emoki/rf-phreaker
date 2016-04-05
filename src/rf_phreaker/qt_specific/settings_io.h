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
static const std::string sweep_collection_group_key = "sweep_collection";
static const std::string gsm_decode_thresholds_group_key = "gsm_layer_3_general";
static const std::string umts_decode_thresholds_group_key = "umts_layer_3_general";
static const std::string lte_decode_thresholds_group_key = "lte_layer_3_general";
static const std::string lte_sweep_general_group_key = "lte_sweep_general";
static const std::string lte_layer_3_general_group_key = "lte_layer_3_general";
static const std::string umts_sweep_general_group_key = "umts_sweep_general";
static const std::string umts_layer_3_general_group_key = "umts_layer_3_general";
static const std::string frequency_correction_group_key = "frequency_correction";
static const std::string nr_general_group_key = "nr_general";
static const std::string nr_full_streaming_group_key = "nr_full_streaming";
static const std::string nr_intermittent_streaming_group_key = "nr_intermittent_streaming";
static const std::string gsm_sweep_collection_group_key = "gsm_sweep_collection";
static const std::string gsm_layer_3_collection_group_key = "gsm_layer_3_collection";
static const std::string gsm_sweep_general_group_key = "gsm_sweep_general";
static const std::string gsm_layer_3_general_group_key = "gsm_layer_3_general";
static const std::string output_interval_group_key = "output_interval";


// Value keys
static const std::string scanner_output_key = "scanner_output";
static const std::string gps_output_key = "gps_output";
static const std::string gsm_sweep_output_key = "gsm_sweep_output";
static const std::string gsm_layer_3_output_key = "gsm_layer_3_output";
static const std::string umts_sweep_output_key = "umts_sweep_output";
static const std::string umts_layer_3_output_key = "umts_layer_3_output";
static const std::string lte_sweep_output_key = "lte_sweep_output";
static const std::string lte_layer_3_output_key = "lte_layer_3_output";
static const std::string sweep_output_key = "sweep_output";
static const std::string output_raw_packets_key = "output_raw_packets";
static const std::string log_level_key = "log_level";
static const std::string scheduling_algorithm_key = "scheduling_algorithm";
static const std::string sampling_rate_key = "sampling_rate";
static const std::string bandwidth_key = "bandwidth";
static const std::string collection_time_key = "collection_time";
static const std::string is_streaming_key = "is_streaming";
static const std::string overlap_time_key = "overlap_time";
static const std::string priority_key = "priority";
static const std::string max_update_threshold_key = "max_update_threshold";
static const std::string min_collection_round_key = "min_collection_round";
static const std::string decode_threshold_key = "decode_threshold";
static const std::string min_decode_threshold_key = "min_decode_threshold";
static const std::string layer_3_wanted_key = "layer_3";
static const std::string should_prioritize_layer_3_key = "prioritize_layer_3";
static const std::string minimum_decode_count_key = "minimum_decode_count";
static const std::string complete_decode_interval_key = "complete_decode_interval";
static const std::string sync_quality_confidence_threshold_key = "sync_quality_confidence_threshold";
static const std::string pbch_decoding_threshold_key = "pbch_decoding_threshold";
static const std::string minimum_relative_peak_threshold_key = "minimum_relative_peak_threshold";
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
static const std::string simultaneous_collection_key = "simultaneous_collection";
static const std::string eeprom_update_period_for_1pps_calibration_minutes_key = "eeprom_update_period_for_1pps_calibration_minutes";
static const std::string log_gps_general_key = "log_gps";
static const std::string log_gps_parsing_key = "log_gps_parsing";
static const std::string log_collection_key = "log_collection";
static const std::string gsm_band_power_threshold_key = "band_power_threshold";
static const std::string gsm_side_power_threshold_key = "side_power_threshold";
static const std::string gsm_perform_sync_correlations_key = "perform_sync_correlations";
static const std::string gsm_c_i_ratio_confidence_threshold_key = "c_i_ratio_confidence_threshold";
static const std::string low_intermediate_frequency_key = "low_intermediate_frequency";
static const std::string high_intermediate_frequency_key = "high_intermediate_frequency";
static const std::string step_size_key = "step_size";


class settings_io {
public:
	settings_io(const std::string &application_name, const std::string &organization);

	settings_io(const std::string &filename);

	~settings_io();

	bool does_exist() const;

	std::string filename() const;

	void read(settings &settings);

	void read(output_settings &settings, const std::string &group_key);

	void read(collection_settings &settings, const std::string &group_key);

	void read(layer_3_settings &settings, const std::string &group_key);

	void read(umts_general_settings &settings, const std::string &group_key);

	void read(lte_general_settings &settings, const std::string &group_key);

	void read(gsm_general_settings &settings, const std::string &group_key);

	void read(frequency_correction_settings &settings, const std::string &group_key);

	void read(blade_settings &settings);

	void read(blade_rx_settings &settings, const std::string &group_key);

	void read(output_interval_settings &settings, const std::string &group_key);

	void write(const settings &settings);

	void write(const output_settings &settings, const std::string &group_key);

	void write(const collection_settings &settings, const std::string &group_key);

	void write(const layer_3_settings &settings, const std::string &group_key);

	void write(const umts_general_settings &settings, const std::string &group_key);

	void write(const lte_general_settings &settings, const std::string &group_key);

	void write(const gsm_general_settings &settings, const std::string &group_key);

	void write(const frequency_correction_settings &settings, const std::string &group_key);

	void write(const blade_settings &settings);

	void write(const blade_rx_settings &settings, const std::string &group_key);

	void write(const output_interval_settings &settings, const std::string &group_key);

	void clear();

private:
	std::unique_ptr<QSettings> qsettings_;
};


}