#include "gtest/gtest.h"

#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/common/settings.h"

TEST(QtSpecific, TestSettingsIO)
{
	using namespace rf_phreaker;
	
	settings set;
	settings_io set_io("qt_specific_tests", "cappeen");

	set_io.clear();

	set_io.read(set);

	EXPECT_EQ(settings_log_level_default, set.log_level_);
	EXPECT_EQ(gps_collection_period_ms_default, set.gps_collection_period_ms_);
	EXPECT_EQ(num_items_in_flight_default, set.num_items_in_flight_);
	EXPECT_EQ(use_rf_board_adjustment_default, set.use_rf_board_adjustment_);
	//EXPECT_EQ(output_directory_default, set.output_directory_);  // Manually verify.
	EXPECT_EQ(output_in_binary_default, set.output_in_binary_);
	EXPECT_EQ(simultaneous_collection_default, set.simultaneous_collection_);
	EXPECT_EQ(eeprom_update_period_for_1pps_calibration_minutes_default, set.eeprom_update_period_for_1pps_calibration_minutes_);

	EXPECT_EQ(log_gps_general_default, set.log_gps_general_);
	EXPECT_EQ(log_gps_parsing_default, set.log_gps_parsing_);
	EXPECT_EQ(log_collection_default, set.log_collection_);

	EXPECT_EQ(settings_output_default, set.standard_output_.scanner_);
	EXPECT_EQ(settings_output_default, set.standard_output_.gps_);
	EXPECT_EQ(settings_output_default, set.standard_output_.umts_sweep_);
	EXPECT_EQ(settings_output_default, set.standard_output_.umts_layer_3_);
	EXPECT_EQ(settings_output_default, set.standard_output_.lte_sweep_);
	EXPECT_EQ(settings_output_default, set.standard_output_.lte_layer_3_);

	EXPECT_EQ(settings_output_default, set.signal_slots_.scanner_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.gps_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.umts_sweep_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.umts_layer_3_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.lte_sweep_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.lte_layer_3_);

	EXPECT_EQ(settings_output_default, set.packet_output_.scanner_);
	EXPECT_EQ(settings_output_default, set.packet_output_.gps_);
	EXPECT_EQ(settings_output_default, set.packet_output_.umts_sweep_);
	EXPECT_EQ(settings_output_default, set.packet_output_.umts_layer_3_);
	EXPECT_EQ(settings_output_default, set.packet_output_.lte_sweep_);
	EXPECT_EQ(settings_output_default, set.packet_output_.lte_layer_3_);

	EXPECT_EQ(settings_sampling_rate_default, set.umts_sweep_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.umts_sweep_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.umts_sweep_collection_.collection_time_);

	EXPECT_EQ(settings_sampling_rate_default, set.umts_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.umts_layer_3_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.umts_layer_3_collection_.collection_time_);

	EXPECT_EQ(settings_sampling_rate_default, set.lte_sweep_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.lte_sweep_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.lte_sweep_collection_.collection_time_);

	EXPECT_EQ(settings_sampling_rate_default, set.lte_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.lte_layer_3_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.lte_layer_3_collection_.collection_time_);

	EXPECT_EQ(settings_sampling_rate_default, set.sweep_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.sweep_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.sweep_collection_.collection_time_);

	EXPECT_EQ(settings_layer_3_max_update_threshold_default, set.umts_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(settings_layer_3_min_collection_round_default, set.umts_decode_layer_3_.minimum_collection_round_);
	EXPECT_EQ(settings_layer_3_decode_threshold_default, set.umts_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(settings_layer_3_min_decode_threshold_default, set.umts_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(settings_layer_3_max_update_threshold_default, set.lte_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(settings_layer_3_min_collection_round_default, set.lte_decode_layer_3_.minimum_collection_round_);
	EXPECT_EQ(settings_layer_3_decode_threshold_default, set.lte_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(settings_layer_3_min_decode_threshold_default, set.lte_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(settings_umts_general_sensitivity_default, set.umts_sweep_general_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.umts_sweep_general_.full_scan_interval_);
	EXPECT_EQ(settings_umts_general_num_coherent_slots_default, set.umts_sweep_general_.num_coherent_slots_);

	EXPECT_EQ(settings_umts_general_sensitivity_default, set.umts_layer_3_general_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.umts_layer_3_general_.full_scan_interval_);
	EXPECT_EQ(settings_umts_general_num_coherent_slots_default, set.umts_layer_3_general_.num_coherent_slots_);

	EXPECT_EQ(initial_frequency_correction_offset_start_default, set.frequency_correction_settings_.initial_frequency_correction_range_start_);
	EXPECT_EQ(initial_frequency_correction_offset_end_default, set.frequency_correction_settings_.initial_frequency_correction_range_end_);
	EXPECT_EQ(settings_umts_general_sensitivity_default, set.frequency_correction_settings_.general_settings_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.frequency_correction_settings_.general_settings_.full_scan_interval_);
	EXPECT_EQ(settings_umts_general_num_coherent_slots_default, set.frequency_correction_settings_.general_settings_.num_coherent_slots_);

	EXPECT_EQ(blade_log_level_default, set.blade_settings_.log_level_);
	EXPECT_EQ(blade_rx_sync_num_buffers_default, set.blade_settings_.rx_sync_num_buffers_);
	EXPECT_EQ(blade_rx_sync_buffer_size_default, set.blade_settings_.rx_sync_buffer_size_);
	EXPECT_EQ(blade_rx_sync_num_transfers_default, set.blade_settings_.rx_sync_num_transfers_);
	EXPECT_EQ(blade_rx_sync_timeout_default, set.blade_settings_.rx_sync_timeout_);

	// Alter and store new settings. 
	int tmp = 0;
	set.log_level_ = tmp++;
	set.log_gps_general_ = true;
	set.log_gps_parsing_ = true;
	set.log_collection_ = true;
	set.gps_collection_period_ms_ = tmp++;
	set.num_items_in_flight_ = tmp++;
	set.use_rf_board_adjustment_ = true;
	set.output_directory_ = "c:/";
	set.output_in_binary_ = false;
	set.simultaneous_collection_ = false;
	set.eeprom_update_period_for_1pps_calibration_minutes_ = tmp++;
	set.standard_output_.scanner_ = true;
	set.standard_output_.gps_ = true;
	set.standard_output_.umts_sweep_ = true;
	set.standard_output_.umts_layer_3_ = true;
	set.standard_output_.lte_sweep_ = true;
	set.standard_output_.lte_layer_3_ = true;
	set.signal_slots_.scanner_ = true;
	set.signal_slots_.gps_ = true;
	set.signal_slots_.umts_sweep_ = true;
	set.signal_slots_.umts_layer_3_ = true;
	set.signal_slots_.lte_sweep_ = true;
	set.signal_slots_.lte_layer_3_ = true;
	set.packet_output_.scanner_ = true;
	set.packet_output_.gps_ = false;
	set.packet_output_.umts_sweep_ = true;
	set.packet_output_.umts_layer_3_ = false;
	set.packet_output_.lte_sweep_ = false;
	set.packet_output_.lte_layer_3_ = true;
	set.umts_sweep_collection_.sampling_rate_ = tmp++;
	set.umts_sweep_collection_.bandwidth_ = tmp++;
	set.umts_sweep_collection_.collection_time_ = tmp++;
	set.umts_layer_3_collection_.sampling_rate_ = tmp++;
	set.umts_layer_3_collection_.bandwidth_ = tmp++;
	set.umts_layer_3_collection_.collection_time_ = tmp++;
	set.lte_sweep_collection_.sampling_rate_ = tmp++;
	set.lte_sweep_collection_.bandwidth_ = tmp++;
	set.lte_sweep_collection_.collection_time_ = tmp++;
	set.lte_layer_3_collection_.sampling_rate_ = tmp++;
	set.lte_layer_3_collection_.bandwidth_ = tmp++;
	set.lte_layer_3_collection_.collection_time_ = tmp++;
	set.sweep_collection_.sampling_rate_ = tmp++;
	set.sweep_collection_.bandwidth_ = tmp++;
	set.sweep_collection_.collection_time_ = tmp++;
	set.umts_decode_layer_3_.max_update_threshold_ = tmp++;
	set.umts_decode_layer_3_.minimum_collection_round_= tmp++;
	set.umts_decode_layer_3_.decode_threshold_ = tmp++;
	set.umts_decode_layer_3_.decode_minimum_threshold_ = tmp++;
	set.lte_decode_layer_3_.max_update_threshold_ = tmp++;
	set.lte_decode_layer_3_.minimum_collection_round_ = tmp++;
	set.lte_decode_layer_3_.decode_threshold_ = tmp++;
	set.lte_decode_layer_3_.decode_minimum_threshold_ = tmp++;
	set.umts_sweep_general_.sensitivity_ = tmp++;
	set.umts_sweep_general_.full_scan_interval_ = tmp++;
	set.umts_sweep_general_.num_coherent_slots_ = tmp++;
	set.umts_layer_3_general_.sensitivity_ = tmp++;
	set.umts_layer_3_general_.full_scan_interval_ = tmp++;
	set.frequency_correction_settings_.initial_frequency_correction_range_start_ = tmp++;
	set.frequency_correction_settings_.initial_frequency_correction_range_end_ = tmp++;
	set.frequency_correction_settings_.general_settings_.full_scan_interval_ = tmp++;
	set.frequency_correction_settings_.general_settings_.num_coherent_slots_ = tmp++;
	set.frequency_correction_settings_.general_settings_.sensitivity_ = tmp++;
	set.blade_settings_.log_level_ = tmp++;
	set.blade_settings_.rx_sync_buffer_size_ = tmp++;
	set.blade_settings_.rx_sync_num_buffers_ = tmp++;
	set.blade_settings_.rx_sync_num_transfers_ = tmp++;
	set.blade_settings_.rx_sync_timeout_ = tmp++;
	set_io.write(set);
	
	settings set2;
	set_io.read(set2);
	EXPECT_EQ(set.log_level_, set2.log_level_);
	EXPECT_EQ(set.gps_collection_period_ms_, set2.gps_collection_period_ms_);
	EXPECT_EQ(set.num_items_in_flight_, set2.num_items_in_flight_);
	EXPECT_EQ(set.use_rf_board_adjustment_, set2.use_rf_board_adjustment_);
	EXPECT_EQ(set.output_directory_, set2.output_directory_);
	EXPECT_EQ(set.output_in_binary_, set2.output_in_binary_);
	EXPECT_EQ(set.simultaneous_collection_, set2.simultaneous_collection_);
	EXPECT_EQ(set.eeprom_update_period_for_1pps_calibration_minutes_, set2.eeprom_update_period_for_1pps_calibration_minutes_);

	EXPECT_EQ(set.log_gps_general_, set2.log_gps_general_);
	EXPECT_EQ(set.log_gps_parsing_, set2.log_gps_parsing_);
	EXPECT_EQ(set.log_collection_, set2.log_collection_);

	EXPECT_EQ(set.standard_output_.scanner_, set2.standard_output_.scanner_);
	EXPECT_EQ(set.standard_output_.gps_, set2.standard_output_.gps_);
	EXPECT_EQ(set.standard_output_.umts_sweep_, set2.standard_output_.umts_sweep_);
	EXPECT_EQ(set.standard_output_.umts_layer_3_, set2.standard_output_.umts_layer_3_);
	EXPECT_EQ(set.standard_output_.lte_sweep_, set2.standard_output_.lte_sweep_);
	EXPECT_EQ(set.standard_output_.lte_layer_3_, set2.standard_output_.lte_layer_3_);

	EXPECT_EQ(set.signal_slots_.scanner_, set2.signal_slots_.scanner_);
	EXPECT_EQ(set.signal_slots_.gps_, set2.signal_slots_.gps_);
	EXPECT_EQ(set.signal_slots_.umts_sweep_, set2.signal_slots_.umts_sweep_);
	EXPECT_EQ(set.signal_slots_.umts_layer_3_, set2.signal_slots_.umts_layer_3_);
	EXPECT_EQ(set.signal_slots_.lte_sweep_, set2.signal_slots_.lte_sweep_);
	EXPECT_EQ(set.signal_slots_.lte_layer_3_, set2.signal_slots_.lte_layer_3_);

	EXPECT_EQ(set.umts_sweep_collection_.sampling_rate_, set2.umts_sweep_collection_.sampling_rate_);
	EXPECT_EQ(set.umts_sweep_collection_.bandwidth_, set2.umts_sweep_collection_.bandwidth_);
	EXPECT_EQ(set.umts_sweep_collection_.collection_time_, set2.umts_sweep_collection_.collection_time_);

	EXPECT_EQ(set.umts_layer_3_collection_.sampling_rate_, set2.umts_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(set.umts_layer_3_collection_.bandwidth_, set2.umts_layer_3_collection_.bandwidth_);
	EXPECT_EQ(set.umts_layer_3_collection_.collection_time_, set2.umts_layer_3_collection_.collection_time_);

	EXPECT_EQ(set.lte_sweep_collection_.sampling_rate_, set2.lte_sweep_collection_.sampling_rate_);
	EXPECT_EQ(set.lte_sweep_collection_.bandwidth_, set2.lte_sweep_collection_.bandwidth_);
	EXPECT_EQ(set.lte_sweep_collection_.collection_time_, set2.lte_sweep_collection_.collection_time_);

	EXPECT_EQ(set.lte_layer_3_collection_.sampling_rate_, set2.lte_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(set.lte_layer_3_collection_.bandwidth_, set2.lte_layer_3_collection_.bandwidth_);
	EXPECT_EQ(set.lte_layer_3_collection_.collection_time_, set2.lte_layer_3_collection_.collection_time_);

	EXPECT_EQ(set.sweep_collection_.sampling_rate_, set2.sweep_collection_.sampling_rate_);
	EXPECT_EQ(set.sweep_collection_.bandwidth_, set2.sweep_collection_.bandwidth_);
	EXPECT_EQ(set.sweep_collection_.collection_time_, set2.sweep_collection_.collection_time_);

	EXPECT_EQ(set.umts_decode_layer_3_.max_update_threshold_, set2.umts_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(set.umts_decode_layer_3_.minimum_collection_round_, set2.umts_decode_layer_3_.minimum_collection_round_);
	EXPECT_EQ(set.umts_decode_layer_3_.decode_threshold_, set2.umts_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(set.umts_decode_layer_3_.decode_minimum_threshold_, set2.umts_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(set.lte_decode_layer_3_.max_update_threshold_, set2.lte_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(set.lte_decode_layer_3_.minimum_collection_round_, set2.lte_decode_layer_3_.minimum_collection_round_);
	EXPECT_EQ(set.lte_decode_layer_3_.decode_threshold_, set2.lte_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(set.lte_decode_layer_3_.decode_minimum_threshold_, set2.lte_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(set.umts_sweep_general_.sensitivity_, set2.umts_sweep_general_.sensitivity_);
	EXPECT_EQ(set.umts_sweep_general_.full_scan_interval_, set2.umts_sweep_general_.full_scan_interval_);
	EXPECT_EQ(set.umts_sweep_general_.num_coherent_slots_, set2.umts_sweep_general_.num_coherent_slots_);

	EXPECT_EQ(set.umts_layer_3_general_.sensitivity_, set2.umts_layer_3_general_.sensitivity_);
	EXPECT_EQ(set.umts_layer_3_general_.full_scan_interval_, set2.umts_layer_3_general_.full_scan_interval_);
	EXPECT_EQ(set.umts_layer_3_general_.num_coherent_slots_, set2.umts_layer_3_general_.num_coherent_slots_);

	EXPECT_EQ(set.frequency_correction_settings_.initial_frequency_correction_range_start_, set2.frequency_correction_settings_.initial_frequency_correction_range_start_);
	EXPECT_EQ(set.frequency_correction_settings_.initial_frequency_correction_range_end_, set2.frequency_correction_settings_.initial_frequency_correction_range_end_);
	EXPECT_EQ(set.frequency_correction_settings_.general_settings_.full_scan_interval_, set2.frequency_correction_settings_.general_settings_.full_scan_interval_);
	EXPECT_EQ(set.frequency_correction_settings_.general_settings_.num_coherent_slots_, set2.frequency_correction_settings_.general_settings_.num_coherent_slots_);
	EXPECT_EQ(set.frequency_correction_settings_.general_settings_.sensitivity_, set2.frequency_correction_settings_.general_settings_.sensitivity_);

	EXPECT_EQ(set.blade_settings_.log_level_, set2.blade_settings_.log_level_);
	EXPECT_EQ(set.blade_settings_.rx_sync_buffer_size_, set2.blade_settings_.rx_sync_buffer_size_);
	EXPECT_EQ(set.blade_settings_.rx_sync_num_buffers_, set2.blade_settings_.rx_sync_num_buffers_);
	EXPECT_EQ(set.blade_settings_.rx_sync_num_transfers_, set2.blade_settings_.rx_sync_num_transfers_);
	EXPECT_EQ(set.blade_settings_.rx_sync_timeout_, set2.blade_settings_.rx_sync_timeout_);

	// Store default settings.
	set_io.clear();
	set_io.read(set);
	set_io.write(set);
}

TEST(QtSpecific, TestLocation) {
	using namespace rf_phreaker;

	settings set;
	settings_io set_io("cappeen_api", "cappeen");

	set_io.read(set);

	int i = 0;
}