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
	EXPECT_EQ(scheduling_algorithm_default, set.scheduling_algorithm_);

	EXPECT_EQ(log_gps_general_default, set.log_gps_general_);
	EXPECT_EQ(log_gps_parsing_default, set.log_gps_parsing_);
	EXPECT_EQ(log_collection_default, set.log_collection_);

	EXPECT_EQ(settings_output_default, set.standard_output_.scanner_);
	EXPECT_EQ(settings_output_default, set.standard_output_.gps_);
	EXPECT_EQ(settings_output_default, set.standard_output_.gsm_sweep_);
	EXPECT_EQ(settings_output_default, set.standard_output_.gsm_layer_3_);
	EXPECT_EQ(settings_output_default, set.standard_output_.umts_sweep_);
	EXPECT_EQ(settings_output_default, set.standard_output_.umts_layer_3_);
	EXPECT_EQ(settings_output_default, set.standard_output_.lte_sweep_);
	EXPECT_EQ(settings_output_default, set.standard_output_.lte_layer_3_);
	EXPECT_EQ(settings_output_default, set.standard_output_.sweep_);

	EXPECT_EQ(settings_output_default, set.signal_slots_.scanner_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.gps_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.gsm_sweep_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.gsm_layer_3_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.umts_sweep_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.umts_layer_3_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.lte_sweep_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.lte_layer_3_);
	EXPECT_EQ(settings_output_default, set.signal_slots_.sweep_);

	EXPECT_EQ(settings_output_default, set.packet_output_.scanner_);
	EXPECT_EQ(settings_output_default, set.packet_output_.gps_);
	EXPECT_EQ(settings_output_default, set.packet_output_.gsm_sweep_);
	EXPECT_EQ(settings_output_default, set.packet_output_.gsm_layer_3_);
	EXPECT_EQ(settings_output_default, set.packet_output_.umts_sweep_);
	EXPECT_EQ(settings_output_default, set.packet_output_.umts_layer_3_);
	EXPECT_EQ(settings_output_default, set.packet_output_.lte_sweep_);
	EXPECT_EQ(settings_output_default, set.packet_output_.lte_layer_3_);
	EXPECT_EQ(settings_output_default, set.packet_output_.sweep_);

	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.scanner_);
	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.gps_);
	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.gsm_sweep_);
	EXPECT_EQ(settings_output_interval_default, set.output_intervals_.gsm_layer_3_);
	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.umts_sweep_);
	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.umts_layer_3_);
	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.lte_sweep_);
	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.lte_layer_3_);
	//EXPECT_EQ(settings_output_interval_default, set.output_intervals_.sweep_);

	EXPECT_EQ(settings_sampling_rate_default, set.gsm_sweep_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.gsm_sweep_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.gsm_sweep_collection_.collection_time_);
	EXPECT_EQ(settings_is_streaming_default, set.gsm_sweep_collection_.is_streaming_);
	EXPECT_EQ(settings_overlap_time_default, set.gsm_sweep_collection_.overlap_time_);
	EXPECT_EQ(settings_priority_default, set.gsm_sweep_collection_.priority_);

	EXPECT_EQ(settings_sampling_rate_default, set.gsm_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.gsm_layer_3_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.gsm_layer_3_collection_.collection_time_);
	EXPECT_EQ(settings_is_streaming_default, set.gsm_layer_3_collection_.is_streaming_);
	EXPECT_EQ(settings_overlap_time_default, set.gsm_layer_3_collection_.overlap_time_);
	EXPECT_EQ(settings_priority_default, set.gsm_layer_3_collection_.priority_);

	EXPECT_EQ(settings_sampling_rate_default, set.umts_sweep_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.umts_sweep_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.umts_sweep_collection_.collection_time_);
	EXPECT_EQ(settings_is_streaming_default, set.umts_sweep_collection_.is_streaming_);
	EXPECT_EQ(settings_overlap_time_default, set.umts_sweep_collection_.overlap_time_);
	EXPECT_EQ(settings_priority_default, set.umts_sweep_collection_.priority_);

	EXPECT_EQ(settings_sampling_rate_default, set.umts_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.umts_layer_3_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.umts_layer_3_collection_.collection_time_);
	EXPECT_EQ(settings_is_streaming_default, set.umts_layer_3_collection_.is_streaming_);
	EXPECT_EQ(settings_overlap_time_default, set.umts_layer_3_collection_.overlap_time_);
	EXPECT_EQ(settings_priority_default, set.umts_layer_3_collection_.priority_);

	EXPECT_EQ(settings_sampling_rate_default, set.lte_sweep_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.lte_sweep_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.lte_sweep_collection_.collection_time_);
	EXPECT_EQ(settings_is_streaming_default, set.lte_sweep_collection_.is_streaming_);
	EXPECT_EQ(settings_overlap_time_default, set.lte_sweep_collection_.overlap_time_);
	EXPECT_EQ(settings_priority_default, set.lte_sweep_collection_.priority_);

	EXPECT_EQ(settings_sampling_rate_default, set.lte_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.lte_layer_3_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.lte_layer_3_collection_.collection_time_);
	EXPECT_EQ(settings_is_streaming_default, set.lte_layer_3_collection_.is_streaming_);
	EXPECT_EQ(settings_overlap_time_default, set.lte_layer_3_collection_.overlap_time_);
	EXPECT_EQ(settings_priority_default, set.lte_layer_3_collection_.priority_);

	EXPECT_EQ(settings_sampling_rate_default, set.sweep_collection_.sampling_rate_);
	EXPECT_EQ(settings_bandwidth_default, set.sweep_collection_.bandwidth_);
	EXPECT_EQ(settings_collection_time_default, set.sweep_collection_.collection_time_);
	EXPECT_EQ(settings_is_streaming_default, set.sweep_collection_.is_streaming_);
	EXPECT_EQ(settings_overlap_time_default, set.sweep_collection_.overlap_time_);
	EXPECT_EQ(settings_priority_default, set.sweep_collection_.priority_);

	EXPECT_EQ(settings_layer_3_max_update_threshold_default, set.umts_layer_3_decode_.max_update_threshold_);
	EXPECT_EQ(settings_layer_3_min_collection_round_default, set.umts_layer_3_decode_.minimum_collection_round_);
	EXPECT_EQ(settings_layer_3_decode_threshold_default, set.umts_layer_3_decode_.decode_threshold_);
	EXPECT_EQ(settings_layer_3_min_decode_threshold_default, set.umts_layer_3_decode_.decode_minimum_threshold_);
	EXPECT_EQ(settings_layer_3_minimum_decode_count_default, set.umts_layer_3_decode_.minimum_decode_count_);
	EXPECT_EQ(settings_layer_3_should_prioritize_layer_3_default, set.umts_layer_3_decode_.should_prioritize_layer_3_);
	EXPECT_EQ(0, set.umts_layer_3_decode_.wanted_layer_3_.size());

	EXPECT_EQ(settings_layer_3_max_update_threshold_default, set.lte_layer_3_decode_.max_update_threshold_);
	EXPECT_EQ(settings_layer_3_min_collection_round_default, set.lte_layer_3_decode_.minimum_collection_round_);
	EXPECT_EQ(settings_layer_3_decode_threshold_default, set.lte_layer_3_decode_.decode_threshold_);
	EXPECT_EQ(settings_layer_3_min_decode_threshold_default, set.lte_layer_3_decode_.decode_minimum_threshold_);
	EXPECT_EQ(settings_layer_3_minimum_decode_count_default, set.lte_layer_3_decode_.minimum_decode_count_);
	EXPECT_EQ(settings_layer_3_should_prioritize_layer_3_default, set.lte_layer_3_decode_.should_prioritize_layer_3_);
	EXPECT_EQ(0, set.lte_layer_3_decode_.wanted_layer_3_.size());

	EXPECT_EQ(settings_gsm_general_side_power_threshold_default, set.gsm_sweep_general_.side_power_threshold_);
	EXPECT_EQ(settings_gsm_general_band_power_threshold_default, set.gsm_sweep_general_.band_power_threshold_);
	EXPECT_EQ(settings_gsm_general_perform_sync_correlations_default, set.gsm_sweep_general_.perform_sync_correlations_);
	EXPECT_EQ(settings_gsm_general_c_i_ratio_confidence_threshold_default, set.gsm_sweep_general_.c_i_ratio_confidence_threshold_);

	EXPECT_EQ(settings_gsm_general_side_power_threshold_default, set.gsm_layer_3_general_.side_power_threshold_);
	EXPECT_EQ(settings_gsm_general_band_power_threshold_default, set.gsm_layer_3_general_.band_power_threshold_);
	EXPECT_EQ(settings_gsm_general_perform_sync_correlations_default, set.gsm_layer_3_general_.perform_sync_correlations_);
	EXPECT_EQ(settings_gsm_general_c_i_ratio_confidence_threshold_default, set.gsm_layer_3_general_.c_i_ratio_confidence_threshold_);

	EXPECT_EQ(settings_umts_general_sensitivity_default, set.umts_sweep_general_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.umts_sweep_general_.full_scan_interval_);
	EXPECT_EQ(settings_umts_general_num_coherent_slots_default, set.umts_sweep_general_.num_coherent_slots_);

	EXPECT_EQ(settings_umts_general_sensitivity_default, set.umts_layer_3_general_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.umts_layer_3_general_.full_scan_interval_);
	EXPECT_EQ(settings_umts_general_num_coherent_slots_default, set.umts_layer_3_general_.num_coherent_slots_);

	EXPECT_EQ(settings_lte_general_full_scan_interval_default, set.lte_sweep_general_.full_scan_interval_);
	EXPECT_EQ(settings_lte_general_sync_quality_confidence_threshold_default, set.lte_sweep_general_.sync_quality_confidence_threshold_);

	EXPECT_EQ(settings_lte_general_full_scan_interval_default, set.lte_layer_3_general_.full_scan_interval_);
	EXPECT_EQ(settings_lte_general_sync_quality_confidence_threshold_default, set.lte_layer_3_general_.sync_quality_confidence_threshold_);

	EXPECT_EQ(initial_frequency_correction_offset_start_default, set.frequency_correction_settings_.initial_frequency_correction_range_start_);
	EXPECT_EQ(initial_frequency_correction_offset_end_default, set.frequency_correction_settings_.initial_frequency_correction_range_end_);
	EXPECT_EQ(settings_umts_general_sensitivity_default, set.frequency_correction_settings_.general_settings_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.frequency_correction_settings_.general_settings_.full_scan_interval_);
	EXPECT_EQ(settings_umts_general_num_coherent_slots_default, set.frequency_correction_settings_.general_settings_.num_coherent_slots_);

	EXPECT_EQ(blade_log_level_default, set.blade_settings_.log_level_);
	EXPECT_EQ(blade_rx_sync_num_buffers_default, set.blade_settings_.intermittent_streaming_rx_.rx_sync_num_buffers_);
	EXPECT_EQ(blade_rx_sync_buffer_size_default, set.blade_settings_.intermittent_streaming_rx_.rx_sync_buffer_size_);
	EXPECT_EQ(blade_rx_sync_num_transfers_default, set.blade_settings_.intermittent_streaming_rx_.rx_sync_num_transfers_);
	EXPECT_EQ(blade_rx_sync_timeout_default, set.blade_settings_.intermittent_streaming_rx_.rx_sync_timeout_);
	EXPECT_EQ(blade_rx_sync_num_buffers_default, set.blade_settings_.full_streaming_rx_.rx_sync_num_buffers_);
	EXPECT_EQ(blade_rx_sync_buffer_size_default, set.blade_settings_.full_streaming_rx_.rx_sync_buffer_size_);
	EXPECT_EQ(blade_rx_sync_num_transfers_default, set.blade_settings_.full_streaming_rx_.rx_sync_num_transfers_);
	EXPECT_EQ(blade_rx_sync_timeout_default, set.blade_settings_.full_streaming_rx_.rx_sync_timeout_);

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
	set.scheduling_algorithm_ = packet_based;
	set.standard_output_.scanner_ = true;
	set.standard_output_.gps_ = true;
	set.standard_output_.gsm_sweep_ = true;
	set.standard_output_.gsm_layer_3_ = true;
	set.standard_output_.umts_sweep_ = true;
	set.standard_output_.umts_layer_3_ = true;
	set.standard_output_.lte_sweep_ = true;
	set.standard_output_.lte_layer_3_ = true;
	set.standard_output_.sweep_ = true;
	set.signal_slots_.scanner_ = true;
	set.signal_slots_.gps_ = true;
	set.signal_slots_.gsm_sweep_ = true;
	set.signal_slots_.gsm_layer_3_ = true;
	set.signal_slots_.umts_sweep_ = true;
	set.signal_slots_.umts_layer_3_ = true;
	set.signal_slots_.lte_sweep_ = true;
	set.signal_slots_.lte_layer_3_ = true;
	set.signal_slots_.sweep_ = true;
	set.packet_output_.scanner_ = true;
	set.packet_output_.gps_ = false;
	set.packet_output_.gsm_sweep_ = true;
	set.packet_output_.gsm_layer_3_ = false;
	set.packet_output_.umts_sweep_ = true;
	set.packet_output_.umts_layer_3_ = false;
	set.packet_output_.lte_sweep_ = false;
	set.packet_output_.lte_layer_3_ = true;
	set.packet_output_.sweep_ = true;
	set.output_intervals_.gsm_layer_3_ = tmp++;
	set.gsm_sweep_collection_.sampling_rate_ = tmp++;
	set.gsm_sweep_collection_.bandwidth_ = tmp++;
	set.gsm_sweep_collection_.collection_time_ = tmp++;
	set.gsm_sweep_collection_.is_streaming_ = true;
	set.gsm_sweep_collection_.overlap_time_ = tmp++;
	set.gsm_sweep_collection_.priority_ = tmp++;
	set.gsm_layer_3_collection_.sampling_rate_ = tmp++;
	set.gsm_layer_3_collection_.bandwidth_ = tmp++;
	set.gsm_layer_3_collection_.collection_time_ = tmp++;
	set.gsm_layer_3_collection_.is_streaming_ = true;
	set.gsm_layer_3_collection_.overlap_time_ = tmp++;
	set.gsm_layer_3_collection_.priority_ = tmp++;
	set.umts_sweep_collection_.sampling_rate_ = tmp++;
	set.umts_sweep_collection_.bandwidth_ = tmp++;
	set.umts_sweep_collection_.collection_time_ = tmp++;
	set.umts_sweep_collection_.is_streaming_ = true;
	set.umts_sweep_collection_.overlap_time_ = tmp++;
	set.umts_sweep_collection_.priority_ = tmp++;
	set.umts_layer_3_collection_.sampling_rate_ = tmp++;
	set.umts_layer_3_collection_.bandwidth_ = tmp++;
	set.umts_layer_3_collection_.collection_time_ = tmp++;
	set.umts_layer_3_collection_.is_streaming_ = true;
	set.umts_layer_3_collection_.overlap_time_ = tmp++;
	set.umts_layer_3_collection_.priority_ = tmp++;
	set.lte_sweep_collection_.sampling_rate_ = tmp++;
	set.lte_sweep_collection_.bandwidth_ = tmp++;
	set.lte_sweep_collection_.collection_time_ = tmp++;
	set.lte_sweep_collection_.is_streaming_ = true;
	set.lte_sweep_collection_.overlap_time_ = tmp++;
	set.lte_sweep_collection_.priority_ = tmp++;
	set.lte_layer_3_collection_.sampling_rate_ = tmp++;
	set.lte_layer_3_collection_.bandwidth_ = tmp++;
	set.lte_layer_3_collection_.collection_time_ = tmp++;
	set.lte_layer_3_collection_.is_streaming_ = true;
	set.lte_layer_3_collection_.overlap_time_ = tmp++;
	set.lte_layer_3_collection_.priority_ = tmp++;
	set.sweep_collection_.sampling_rate_ = tmp++;
	set.sweep_collection_.bandwidth_ = tmp++;
	set.sweep_collection_.collection_time_ = tmp++;
	set.sweep_collection_.is_streaming_ = true;
	set.sweep_collection_.overlap_time_ = tmp++;
	set.sweep_collection_.priority_ = tmp++;
	set.gsm_layer_3_decode_.max_update_threshold_ = tmp++;
	set.gsm_layer_3_decode_.minimum_collection_round_ = tmp++;
	set.gsm_layer_3_decode_.decode_threshold_ = tmp++;
	set.gsm_layer_3_decode_.decode_minimum_threshold_ = tmp++;
	set.gsm_layer_3_decode_.minimum_decode_count_ = tmp++;
	set.gsm_layer_3_decode_.should_prioritize_layer_3_ = false;
	tmp = 0;
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.umts_layer_3_decode_.max_update_threshold_ = tmp++;
	set.umts_layer_3_decode_.minimum_collection_round_ = tmp++;
	set.umts_layer_3_decode_.decode_threshold_ = tmp++;
	set.umts_layer_3_decode_.decode_minimum_threshold_ = tmp++;
	set.umts_layer_3_decode_.minimum_decode_count_ = tmp++;
	set.umts_layer_3_decode_.should_prioritize_layer_3_ = false;
	tmp = 0;
	set.umts_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.umts_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.umts_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.umts_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.max_update_threshold_ = tmp++;
	set.lte_layer_3_decode_.minimum_collection_round_ = tmp++;
	set.lte_layer_3_decode_.decode_threshold_ = tmp++;
	set.lte_layer_3_decode_.decode_minimum_threshold_ = tmp++;
	set.lte_layer_3_decode_.minimum_decode_count_ = tmp++;
	set.lte_layer_3_decode_.should_prioritize_layer_3_ = false;
	tmp = 0;
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.lte_layer_3_decode_.wanted_layer_3_.push_back(tmp++);
	set.gsm_sweep_general_.side_power_threshold_ = tmp++;
	set.gsm_sweep_general_.band_power_threshold_ = tmp++;
	set.gsm_sweep_general_.perform_sync_correlations_ = false;
	set.gsm_sweep_general_.c_i_ratio_confidence_threshold_ = tmp++;
	set.gsm_layer_3_general_.side_power_threshold_ = tmp++;
	set.gsm_layer_3_general_.band_power_threshold_ = tmp++;
	set.gsm_layer_3_general_.perform_sync_correlations_ = false;
	set.gsm_layer_3_general_.c_i_ratio_confidence_threshold_ = tmp++;
	set.umts_sweep_general_.sensitivity_ = tmp++;
	set.umts_sweep_general_.full_scan_interval_ = tmp++;
	set.umts_sweep_general_.num_coherent_slots_ = tmp++;
	set.umts_layer_3_general_.sensitivity_ = tmp++;
	set.umts_layer_3_general_.full_scan_interval_ = tmp++;
	set.lte_sweep_general_.sync_quality_confidence_threshold_ = tmp++;
	set.lte_sweep_general_.full_scan_interval_ = tmp++;
	set.lte_layer_3_general_.sync_quality_confidence_threshold_ = tmp++;
	set.lte_layer_3_general_.full_scan_interval_ = tmp++;
	set.frequency_correction_settings_.initial_frequency_correction_range_start_ = tmp++;
	set.frequency_correction_settings_.initial_frequency_correction_range_end_ = tmp++;
	set.frequency_correction_settings_.general_settings_.full_scan_interval_ = tmp++;
	set.frequency_correction_settings_.general_settings_.num_coherent_slots_ = tmp++;
	set.frequency_correction_settings_.general_settings_.sensitivity_ = tmp++;
	set.blade_settings_.log_level_ = tmp++;
	set.blade_settings_.intermittent_streaming_rx_.rx_sync_buffer_size_ = tmp++;
	set.blade_settings_.intermittent_streaming_rx_.rx_sync_num_buffers_ = tmp++;
	set.blade_settings_.intermittent_streaming_rx_.rx_sync_num_transfers_ = tmp++;
	set.blade_settings_.intermittent_streaming_rx_.rx_sync_timeout_ = tmp++;
	set.blade_settings_.full_streaming_rx_.rx_sync_buffer_size_ = tmp++;
	set.blade_settings_.full_streaming_rx_.rx_sync_num_buffers_ = tmp++;
	set.blade_settings_.full_streaming_rx_.rx_sync_num_transfers_ = tmp++;
	set.blade_settings_.full_streaming_rx_.rx_sync_timeout_ = tmp++;
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
	EXPECT_EQ(set.scheduling_algorithm_, set2.scheduling_algorithm_);

	EXPECT_EQ(set.log_gps_general_, set2.log_gps_general_);
	EXPECT_EQ(set.log_gps_parsing_, set2.log_gps_parsing_);
	EXPECT_EQ(set.log_collection_, set2.log_collection_);

	EXPECT_EQ(set.standard_output_.scanner_, set2.standard_output_.scanner_);
	EXPECT_EQ(set.standard_output_.gps_, set2.standard_output_.gps_);
	EXPECT_EQ(set.standard_output_.gsm_sweep_, set2.standard_output_.gsm_sweep_);
	EXPECT_EQ(set.standard_output_.gsm_layer_3_, set2.standard_output_.gsm_layer_3_);
	EXPECT_EQ(set.standard_output_.umts_sweep_, set2.standard_output_.umts_sweep_);
	EXPECT_EQ(set.standard_output_.umts_layer_3_, set2.standard_output_.umts_layer_3_);
	EXPECT_EQ(set.standard_output_.lte_sweep_, set2.standard_output_.lte_sweep_);
	EXPECT_EQ(set.standard_output_.lte_layer_3_, set2.standard_output_.lte_layer_3_);
	EXPECT_EQ(set.standard_output_.sweep_, set2.standard_output_.sweep_);

	EXPECT_EQ(set.signal_slots_.scanner_, set2.signal_slots_.scanner_);
	EXPECT_EQ(set.signal_slots_.gps_, set2.signal_slots_.gps_);
	EXPECT_EQ(set.signal_slots_.gsm_sweep_, set2.signal_slots_.gsm_sweep_);
	EXPECT_EQ(set.signal_slots_.gsm_layer_3_, set2.signal_slots_.gsm_layer_3_);
	EXPECT_EQ(set.signal_slots_.umts_sweep_, set2.signal_slots_.umts_sweep_);
	EXPECT_EQ(set.signal_slots_.umts_layer_3_, set2.signal_slots_.umts_layer_3_);
	EXPECT_EQ(set.signal_slots_.lte_sweep_, set2.signal_slots_.lte_sweep_);
	EXPECT_EQ(set.signal_slots_.lte_layer_3_, set2.signal_slots_.lte_layer_3_);
	EXPECT_EQ(set.signal_slots_.sweep_, set2.signal_slots_.sweep_);

	EXPECT_EQ(set.packet_output_.scanner_, set2.packet_output_.scanner_);
	EXPECT_EQ(set.packet_output_.gps_, set2.packet_output_.gps_);
	EXPECT_EQ(set.packet_output_.gsm_sweep_, set2.packet_output_.gsm_sweep_);
	EXPECT_EQ(set.packet_output_.gsm_layer_3_, set2.packet_output_.gsm_layer_3_);
	EXPECT_EQ(set.packet_output_.umts_sweep_, set2.packet_output_.umts_sweep_);
	EXPECT_EQ(set.packet_output_.umts_layer_3_, set2.packet_output_.umts_layer_3_);
	EXPECT_EQ(set.packet_output_.lte_sweep_, set2.packet_output_.lte_sweep_);
	EXPECT_EQ(set.packet_output_.lte_layer_3_, set2.packet_output_.lte_layer_3_);
	EXPECT_EQ(set.packet_output_.sweep_, set2.packet_output_.sweep_);

	//EXPECT_EQ(set.output_intervals_.scanner_, set2.output_intervals_.scanner_);
	//EXPECT_EQ(set.output_intervals_.gps_, set2.output_intervals_.gps_);
	//EXPECT_EQ(set.output_intervals_.gsm_sweep_, set2.output_intervals_.gsm_sweep_);
	EXPECT_EQ(set.output_intervals_.gsm_layer_3_, set2.output_intervals_.gsm_layer_3_);
	//EXPECT_EQ(set.output_intervals_.umts_sweep_, set2.output_intervals_.umts_sweep_);
	//EXPECT_EQ(set.output_intervals_.umts_layer_3_, set2.output_intervals_.umts_layer_3_);
	//EXPECT_EQ(set.output_intervals_.lte_sweep_, set2.output_intervals_.lte_sweep_);
	//EXPECT_EQ(set.output_intervals_.lte_layer_3_, set2.output_intervals_.lte_layer_3_);
	//EXPECT_EQ(set.output_intervals_.sweep_, set2.output_intervals_.sweep_);

	EXPECT_EQ(set.gsm_sweep_collection_.sampling_rate_, set2.gsm_sweep_collection_.sampling_rate_);
	EXPECT_EQ(set.gsm_sweep_collection_.bandwidth_, set2.gsm_sweep_collection_.bandwidth_);
	EXPECT_EQ(set.gsm_sweep_collection_.collection_time_, set2.gsm_sweep_collection_.collection_time_);
	EXPECT_EQ(set.gsm_sweep_collection_.is_streaming_, set2.gsm_sweep_collection_.is_streaming_);
	EXPECT_EQ(set.gsm_sweep_collection_.overlap_time_, set2.gsm_sweep_collection_.overlap_time_);
	EXPECT_EQ(set.gsm_sweep_collection_.priority_, set2.gsm_sweep_collection_.priority_);

	EXPECT_EQ(set.gsm_layer_3_collection_.sampling_rate_, set2.gsm_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(set.gsm_layer_3_collection_.bandwidth_, set2.gsm_layer_3_collection_.bandwidth_);
	EXPECT_EQ(set.gsm_layer_3_collection_.collection_time_, set2.gsm_layer_3_collection_.collection_time_);
	EXPECT_EQ(set.gsm_layer_3_collection_.is_streaming_, set2.gsm_layer_3_collection_.is_streaming_);
	EXPECT_EQ(set.gsm_layer_3_collection_.overlap_time_, set2.gsm_layer_3_collection_.overlap_time_);
	EXPECT_EQ(set.gsm_layer_3_collection_.priority_, set2.gsm_layer_3_collection_.priority_);

	EXPECT_EQ(set.umts_sweep_collection_.sampling_rate_, set2.umts_sweep_collection_.sampling_rate_);
	EXPECT_EQ(set.umts_sweep_collection_.bandwidth_, set2.umts_sweep_collection_.bandwidth_);
	EXPECT_EQ(set.umts_sweep_collection_.collection_time_, set2.umts_sweep_collection_.collection_time_);
	EXPECT_EQ(set.umts_sweep_collection_.is_streaming_, set2.umts_sweep_collection_.is_streaming_);
	EXPECT_EQ(set.umts_sweep_collection_.overlap_time_, set2.umts_sweep_collection_.overlap_time_);
	EXPECT_EQ(set.umts_sweep_collection_.priority_, set2.umts_sweep_collection_.priority_);

	EXPECT_EQ(set.umts_layer_3_collection_.sampling_rate_, set2.umts_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(set.umts_layer_3_collection_.bandwidth_, set2.umts_layer_3_collection_.bandwidth_);
	EXPECT_EQ(set.umts_layer_3_collection_.collection_time_, set2.umts_layer_3_collection_.collection_time_);
	EXPECT_EQ(set.umts_layer_3_collection_.is_streaming_, set2.umts_layer_3_collection_.is_streaming_);
	EXPECT_EQ(set.umts_layer_3_collection_.overlap_time_, set2.umts_layer_3_collection_.overlap_time_);
	EXPECT_EQ(set.umts_layer_3_collection_.priority_, set2.umts_layer_3_collection_.priority_);

	EXPECT_EQ(set.lte_sweep_collection_.sampling_rate_, set2.lte_sweep_collection_.sampling_rate_);
	EXPECT_EQ(set.lte_sweep_collection_.bandwidth_, set2.lte_sweep_collection_.bandwidth_);
	EXPECT_EQ(set.lte_sweep_collection_.collection_time_, set2.lte_sweep_collection_.collection_time_);
	EXPECT_EQ(set.lte_sweep_collection_.is_streaming_, set2.lte_sweep_collection_.is_streaming_);
	EXPECT_EQ(set.lte_sweep_collection_.overlap_time_, set2.lte_sweep_collection_.overlap_time_);
	EXPECT_EQ(set.lte_sweep_collection_.priority_, set2.lte_sweep_collection_.priority_);

	EXPECT_EQ(set.lte_layer_3_collection_.sampling_rate_, set2.lte_layer_3_collection_.sampling_rate_);
	EXPECT_EQ(set.lte_layer_3_collection_.bandwidth_, set2.lte_layer_3_collection_.bandwidth_);
	EXPECT_EQ(set.lte_layer_3_collection_.collection_time_, set2.lte_layer_3_collection_.collection_time_);
	EXPECT_EQ(set.lte_layer_3_collection_.is_streaming_, set2.lte_layer_3_collection_.is_streaming_);
	EXPECT_EQ(set.lte_layer_3_collection_.overlap_time_, set2.lte_layer_3_collection_.overlap_time_);
	EXPECT_EQ(set.lte_layer_3_collection_.priority_, set2.lte_layer_3_collection_.priority_);

	EXPECT_EQ(set.sweep_collection_.sampling_rate_, set2.sweep_collection_.sampling_rate_);
	EXPECT_EQ(set.sweep_collection_.bandwidth_, set2.sweep_collection_.bandwidth_);
	EXPECT_EQ(set.sweep_collection_.collection_time_, set2.sweep_collection_.collection_time_);
	EXPECT_EQ(set.sweep_collection_.is_streaming_, set2.sweep_collection_.is_streaming_);
	EXPECT_EQ(set.sweep_collection_.overlap_time_, set2.sweep_collection_.overlap_time_);
	EXPECT_EQ(set.sweep_collection_.priority_, set2.sweep_collection_.priority_);

	EXPECT_EQ(set.gsm_layer_3_decode_.max_update_threshold_, set2.gsm_layer_3_decode_.max_update_threshold_);
	EXPECT_EQ(set.gsm_layer_3_decode_.minimum_collection_round_, set2.gsm_layer_3_decode_.minimum_collection_round_);
	EXPECT_EQ(set.gsm_layer_3_decode_.decode_threshold_, set2.gsm_layer_3_decode_.decode_threshold_);
	EXPECT_EQ(set.gsm_layer_3_decode_.decode_minimum_threshold_, set2.gsm_layer_3_decode_.decode_minimum_threshold_);
	EXPECT_EQ(set.gsm_layer_3_decode_.minimum_decode_count_, set2.gsm_layer_3_decode_.minimum_decode_count_);
	EXPECT_EQ(set.gsm_layer_3_decode_.should_prioritize_layer_3_, set2.gsm_layer_3_decode_.should_prioritize_layer_3_);
	{
		EXPECT_EQ(set.gsm_layer_3_decode_.wanted_layer_3_.size(), set2.gsm_layer_3_decode_.wanted_layer_3_.size());
		auto j = set2.gsm_layer_3_decode_.wanted_layer_3_.begin();
		for(auto i : set.gsm_layer_3_decode_.wanted_layer_3_)
			EXPECT_EQ(i, *j++);
	}

	EXPECT_EQ(set.umts_layer_3_decode_.max_update_threshold_, set2.umts_layer_3_decode_.max_update_threshold_);
	EXPECT_EQ(set.umts_layer_3_decode_.minimum_collection_round_, set2.umts_layer_3_decode_.minimum_collection_round_);
	EXPECT_EQ(set.umts_layer_3_decode_.decode_threshold_, set2.umts_layer_3_decode_.decode_threshold_);
	EXPECT_EQ(set.umts_layer_3_decode_.decode_minimum_threshold_, set2.umts_layer_3_decode_.decode_minimum_threshold_);
	EXPECT_EQ(set.umts_layer_3_decode_.minimum_decode_count_, set2.umts_layer_3_decode_.minimum_decode_count_);
	EXPECT_EQ(set.umts_layer_3_decode_.should_prioritize_layer_3_, set2.umts_layer_3_decode_.should_prioritize_layer_3_);
	{
		EXPECT_EQ(set.umts_layer_3_decode_.wanted_layer_3_.size(), set2.umts_layer_3_decode_.wanted_layer_3_.size());
		auto j = set2.umts_layer_3_decode_.wanted_layer_3_.begin();
		for(auto i : set.umts_layer_3_decode_.wanted_layer_3_)
			EXPECT_EQ(i, *j++);
	}

	EXPECT_EQ(set.lte_layer_3_decode_.max_update_threshold_, set2.lte_layer_3_decode_.max_update_threshold_);
	EXPECT_EQ(set.lte_layer_3_decode_.minimum_collection_round_, set2.lte_layer_3_decode_.minimum_collection_round_);
	EXPECT_EQ(set.lte_layer_3_decode_.decode_threshold_, set2.lte_layer_3_decode_.decode_threshold_);
	EXPECT_EQ(set.lte_layer_3_decode_.decode_minimum_threshold_, set2.lte_layer_3_decode_.decode_minimum_threshold_);
	EXPECT_EQ(set.lte_layer_3_decode_.minimum_decode_count_, set2.lte_layer_3_decode_.minimum_decode_count_);
	EXPECT_EQ(set.lte_layer_3_decode_.should_prioritize_layer_3_, set2.lte_layer_3_decode_.should_prioritize_layer_3_);
	{
		EXPECT_EQ(set.lte_layer_3_decode_.wanted_layer_3_.size(), set2.lte_layer_3_decode_.wanted_layer_3_.size());
		auto j = set2.lte_layer_3_decode_.wanted_layer_3_.begin();
		for(auto i : set.lte_layer_3_decode_.wanted_layer_3_)
			EXPECT_EQ(i, *j++);
	}

	EXPECT_EQ(set.gsm_sweep_general_.side_power_threshold_, set2.gsm_sweep_general_.side_power_threshold_);
	EXPECT_EQ(set.gsm_sweep_general_.band_power_threshold_, set2.gsm_sweep_general_.band_power_threshold_);
	EXPECT_EQ(set.gsm_sweep_general_.perform_sync_correlations_, set2.gsm_sweep_general_.perform_sync_correlations_);
	EXPECT_EQ(set.gsm_sweep_general_.c_i_ratio_confidence_threshold_, set2.gsm_sweep_general_.c_i_ratio_confidence_threshold_);

	EXPECT_EQ(set.gsm_layer_3_general_.side_power_threshold_, set2.gsm_layer_3_general_.side_power_threshold_);
	EXPECT_EQ(set.gsm_layer_3_general_.band_power_threshold_, set2.gsm_layer_3_general_.band_power_threshold_);
	EXPECT_EQ(set.gsm_layer_3_general_.perform_sync_correlations_, set2.gsm_layer_3_general_.perform_sync_correlations_);
	EXPECT_EQ(set.gsm_layer_3_general_.c_i_ratio_confidence_threshold_, set2.gsm_layer_3_general_.c_i_ratio_confidence_threshold_);

	EXPECT_EQ(set.umts_sweep_general_.sensitivity_, set2.umts_sweep_general_.sensitivity_);
	EXPECT_EQ(set.umts_sweep_general_.full_scan_interval_, set2.umts_sweep_general_.full_scan_interval_);
	EXPECT_EQ(set.umts_sweep_general_.num_coherent_slots_, set2.umts_sweep_general_.num_coherent_slots_);

	EXPECT_EQ(set.umts_layer_3_general_.sensitivity_, set2.umts_layer_3_general_.sensitivity_);
	EXPECT_EQ(set.umts_layer_3_general_.full_scan_interval_, set2.umts_layer_3_general_.full_scan_interval_);
	EXPECT_EQ(set.umts_layer_3_general_.num_coherent_slots_, set2.umts_layer_3_general_.num_coherent_slots_);

	EXPECT_EQ(set.lte_sweep_general_.sync_quality_confidence_threshold_, set2.lte_sweep_general_.sync_quality_confidence_threshold_);
	EXPECT_EQ(set.lte_sweep_general_.full_scan_interval_, set2.lte_sweep_general_.full_scan_interval_);

	EXPECT_EQ(set.lte_layer_3_general_.sync_quality_confidence_threshold_, set2.lte_layer_3_general_.sync_quality_confidence_threshold_);
	EXPECT_EQ(set.lte_layer_3_general_.full_scan_interval_, set2.lte_layer_3_general_.full_scan_interval_);

	EXPECT_EQ(set.frequency_correction_settings_.initial_frequency_correction_range_start_, set2.frequency_correction_settings_.initial_frequency_correction_range_start_);
	EXPECT_EQ(set.frequency_correction_settings_.initial_frequency_correction_range_end_, set2.frequency_correction_settings_.initial_frequency_correction_range_end_);
	EXPECT_EQ(set.frequency_correction_settings_.general_settings_.full_scan_interval_, set2.frequency_correction_settings_.general_settings_.full_scan_interval_);
	EXPECT_EQ(set.frequency_correction_settings_.general_settings_.num_coherent_slots_, set2.frequency_correction_settings_.general_settings_.num_coherent_slots_);
	EXPECT_EQ(set.frequency_correction_settings_.general_settings_.sensitivity_, set2.frequency_correction_settings_.general_settings_.sensitivity_);

	EXPECT_EQ(set.blade_settings_.log_level_, set2.blade_settings_.log_level_);
	EXPECT_EQ(set.blade_settings_.intermittent_streaming_rx_.rx_sync_buffer_size_, set2.blade_settings_.intermittent_streaming_rx_.rx_sync_buffer_size_);
	EXPECT_EQ(set.blade_settings_.intermittent_streaming_rx_.rx_sync_num_buffers_, set2.blade_settings_.intermittent_streaming_rx_.rx_sync_num_buffers_);
	EXPECT_EQ(set.blade_settings_.intermittent_streaming_rx_.rx_sync_num_transfers_, set2.blade_settings_.intermittent_streaming_rx_.rx_sync_num_transfers_);
	EXPECT_EQ(set.blade_settings_.intermittent_streaming_rx_.rx_sync_timeout_, set2.blade_settings_.intermittent_streaming_rx_.rx_sync_timeout_);
	EXPECT_EQ(set.blade_settings_.full_streaming_rx_.rx_sync_buffer_size_, set2.blade_settings_.full_streaming_rx_.rx_sync_buffer_size_);
	EXPECT_EQ(set.blade_settings_.full_streaming_rx_.rx_sync_num_buffers_, set2.blade_settings_.full_streaming_rx_.rx_sync_num_buffers_);
	EXPECT_EQ(set.blade_settings_.full_streaming_rx_.rx_sync_num_transfers_, set2.blade_settings_.full_streaming_rx_.rx_sync_num_transfers_);
	EXPECT_EQ(set.blade_settings_.full_streaming_rx_.rx_sync_timeout_, set2.blade_settings_.full_streaming_rx_.rx_sync_timeout_);
}

TEST(QtSpecific, TestLocation) {
	using namespace rf_phreaker;

	settings set;
	settings_io set_io("cappeen_api", "cappeen");

	set_io.read(set);
}

TEST(QtSpecific, TestExist) {
	using namespace rf_phreaker;
	{
		// Qt creates ini file on destruction.
		settings set;
		settings_io set_io("test_exist", "cappeen");
		set_io.write(set);
	}
	settings_io set_io("test_exist", "cappeen");
	EXPECT_TRUE(set_io.does_exist());

	settings_io t("alskdjfakljfa", "cappeen");
	EXPECT_FALSE(t.does_exist());
}