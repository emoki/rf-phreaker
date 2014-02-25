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

	EXPECT_EQ(settings_output_raw_packets_default, set.output_raw_packets_);
	EXPECT_EQ(settings_log_level_default, set.log_level_);

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

	EXPECT_EQ(settings_layer_3_max_update_threshold_default, set.umts_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(settings_layer_3_decode_threshold_default, set.umts_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(settings_layer_3_min_decode_threshold_default, set.umts_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(settings_layer_3_max_update_threshold_default, set.lte_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(settings_layer_3_decode_threshold_default, set.lte_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(settings_layer_3_min_decode_threshold_default, set.lte_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(settings_umts_general_sensitivity_default, set.umts_sweep_general_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.umts_sweep_general_.full_scan_interval_);

	EXPECT_EQ(settings_umts_general_sensitivity_default, set.umts_layer_3_general_.sensitivity_);
	EXPECT_EQ(settings_umts_general_full_scan_interval_default, set.umts_layer_3_general_.full_scan_interval_);

	// Alter and store new settings. 
	int tmp = 0;
	set.output_raw_packets_ = true;
	set.log_level_ = tmp++;
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
	set.umts_decode_layer_3_.max_update_threshold_ = tmp++;
	set.umts_decode_layer_3_.decode_threshold_ = tmp++;
	set.umts_decode_layer_3_.decode_minimum_threshold_ = tmp++;
	set.lte_decode_layer_3_.max_update_threshold_ = tmp++;
	set.lte_decode_layer_3_.decode_threshold_ = tmp++;
	set.lte_decode_layer_3_.decode_minimum_threshold_ = tmp++;
	set.umts_sweep_general_.sensitivity_ = tmp++;
	set.umts_sweep_general_.full_scan_interval_ = tmp++;
	set.umts_layer_3_general_.sensitivity_ = tmp++;
	set.umts_layer_3_general_.full_scan_interval_ = tmp++;
	set_io.write(set);
	
	settings set2;
	set_io.read(set2);
	EXPECT_EQ(set.output_raw_packets_, set2.output_raw_packets_);
	EXPECT_EQ(set.log_level_, set2.log_level_);

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

	EXPECT_EQ(set.umts_decode_layer_3_.max_update_threshold_, set2.umts_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(set.umts_decode_layer_3_.decode_threshold_, set2.umts_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(set.umts_decode_layer_3_.decode_minimum_threshold_, set2.umts_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(set.lte_decode_layer_3_.max_update_threshold_, set2.lte_decode_layer_3_.max_update_threshold_);
	EXPECT_EQ(set.lte_decode_layer_3_.decode_threshold_, set2.lte_decode_layer_3_.decode_threshold_);
	EXPECT_EQ(set.lte_decode_layer_3_.decode_minimum_threshold_, set2.lte_decode_layer_3_.decode_minimum_threshold_);

	EXPECT_EQ(set.umts_sweep_general_.sensitivity_, set2.umts_sweep_general_.sensitivity_);
	EXPECT_EQ(set.umts_sweep_general_.full_scan_interval_, set2.umts_sweep_general_.full_scan_interval_);

	EXPECT_EQ(set.umts_layer_3_general_.sensitivity_, set2.umts_layer_3_general_.sensitivity_);
	EXPECT_EQ(set.umts_layer_3_general_.full_scan_interval_, set2.umts_layer_3_general_.full_scan_interval_);

	// Store default settings.
	set_io.clear();
	set_io.read(set);
	set_io.write(set);
}

TEST(QtSpecific, WriteDefaultSettings)
{
	//using namespace rf_phreaker;

	//settings set;
	//settings_io set_io("rf_phreaker", "cappeen");

	//set.output_raw_packets_ = false;
	//set.log_level_ = 3;

	//set.umts_sweep_collection_.sampling_rate_ = khz(3840);
	//set.umts_sweep_collection_.bandwidth_ = mhz(5);
	//set.umts_sweep_collection_.collection_time_ = milli_to_nano(32);

	//set.umts_layer_3_collection_.sampling_rate_ = khz(3840);
	//set.umts_layer_3_collection_.bandwidth_ = mhz(5);
	//set.umts_layer_3_collection_.collection_time_ = milli_to_nano(32);

	//set.lte_sweep_collection_.sampling_rate_ = khz(3840);
	//set.lte_sweep_collection_.bandwidth_ = mhz(5);
	//set.lte_sweep_collection_.collection_time_ = milli_to_nano(32);

	//set.lte_layer_3_collection_.sampling_rate_ = khz(3840);
	//set.lte_layer_3_collection_.bandwidth_ = mhz(5);
	//set.lte_layer_3_collection_.collection_time_ = milli_to_nano(32);

	//set.umts_decode_layer_3_.max_update_threshold_ = 110;
	//set.umts_decode_layer_3_.decode_threshold_ = -13;
	//set.umts_decode_layer_3_.decode_minimum_threshold_ = -25;

	//set.lte_decode_layer_3_.max_update_threshold_ = 110;
	//set.lte_decode_layer_3_.decode_threshold_ = -13;
	//set.lte_decode_layer_3_.decode_minimum_threshold_ = -25;

	//set.umts_sweep_general_.sensitivity_ = -21;
	//set.umts_sweep_general_.full_scan_interval_ = 1;

	//set.umts_layer_3_general_.sensitivity_ = -28;
	//set.umts_layer_3_general_.full_scan_interval_ = 150;

	//set_io.write(set);
}