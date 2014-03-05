#pragma once

#include <stdint.h>
#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker
{

class collection_settings
{
public:
	frequency_type sampling_rate_;
	bandwidth_type bandwidth_;
	time_type collection_time_;
};

class layer_3_settings 
{
public:
	int32_t max_update_threshold_;
	double decode_threshold_;
	double decode_minimum_threshold_;
};

class umts_general_settings /* Find a better description? */
{
public:
	double sensitivity_;
	int32_t full_scan_interval_;
};

class settings
{
public:
	bool output_raw_packets_;
	int log_level_;

	collection_settings umts_sweep_collection_;
	collection_settings umts_layer_3_collection_;
	collection_settings lte_sweep_collection_;
	collection_settings lte_layer_3_collection_;

	layer_3_settings umts_decode_layer_3_;
	layer_3_settings lte_decode_layer_3_;

	umts_general_settings umts_sweep_general_;
	umts_general_settings umts_layer_3_general_;
	//double umts_fast_sweep_threshold_;
	//double umts_deep_sweep_threshold_;
	//double umts_sweep_threshold_;
	//double umts_scan_threshold_;
	//int32_t umts_full_scan_interval_;
};

}