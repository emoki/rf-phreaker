#pragma once
#include <tuple>
#include <memory>
#include <vector>
#include "tbb/flow_graph.h"
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/gsm_analysis/gsm_measurement.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"

namespace rf_phreaker { namespace processing {

class measurement_package {
public:
	measurement_package(bool can_remove = true) : can_remove_(can_remove) {}
	measurement_package(std::shared_ptr<scanner::measurement_info> &info, bool can_remove = true)
		: measurement_info_(info)
		, can_remove_(can_remove) {}
	std::shared_ptr<scanner::measurement_info> measurement_info_;
	bool can_remove_;
};

class power_spectrum_package {
public:
	power_spectrum_package() {}
	power_spectrum_package(std::shared_ptr<scanner::measurement_info> &info, const power_spectrum_spec &params)
		: measurement_info_(info)
		, params_(params) {}
	std::shared_ptr<scanner::measurement_info> measurement_info_;
	power_spectrum_spec params_;
};

template<typename Data>
class analysis_data
{
public:
	analysis_data() : remove_(false)
	{}
	analysis_data(measurement_package &&meas, Data &&data, power_info_group &&p_info = {}, bool remove = false)
		: measurement_package_(std::move(meas))
		, processed_data_(std::move(data))
		, power_info_group_(std::move(p_info))
		, remove_(remove)
	{}

	measurement_package measurement_package_;
	Data processed_data_;
	bool remove_;
	power_info_group power_info_group_;
};

typedef analysis_data<gsm_measurements> gsm_info;
typedef analysis_data<umts_measurements> umts_info;
typedef analysis_data<lte_measurements> lte_info;

typedef tbb::flow::source_node<add_remove_collection_info> start_node;

typedef tbb::flow::limiter_node<add_remove_collection_info> limiter_node;

typedef tbb::flow::queue_node<add_remove_collection_info> queue_node;

#define UMTS_SWEEP_PORT 0
#define UMTS_LAYER3_PORT 1
#define LTE_SWEEP_PORT 2
#define LTE_LAYER3_PORT 3
#define GSM_SWEEP_PORT 4
#define GSM_LAYER3_PORT 5
#define POWER_SPECTRUM_PORT 6
#define IQ_DATA_PORT 7
#define LIMITER_PORT 8

// Use port defines for tech_measurement_ports
typedef tbb::flow::tuple<measurement_package, measurement_package, measurement_package, measurement_package, 
						measurement_package, measurement_package, power_spectrum_package, measurement_package, 
						tbb::flow::continue_msg> tech_measurement_ports;
typedef tbb::flow::multifunction_node<add_remove_collection_info, tech_measurement_ports, tbb::flow::rejecting> collection_manager_node;

typedef tbb::flow::function_node<measurement_package, gsm_info> gsm_cell_search_node;
typedef tbb::flow::function_node<measurement_package, umts_info> umts_cell_search_node;
typedef tbb::flow::function_node<measurement_package, lte_info> lte_cell_search_node;

typedef tbb::flow::function_node<gsm_info, gsm_info> gsm_layer_3_decode_node;
typedef tbb::flow::function_node<umts_info, umts_info> umts_layer_3_decode_node;
typedef tbb::flow::function_node<lte_info, lte_info> lte_layer_3_decode_node;

typedef tbb::flow::multifunction_node<gsm_info, std::tuple<add_remove_collection_info, tbb::flow::continue_msg>> gsm_output_and_feedback_node;
typedef tbb::flow::multifunction_node<umts_info, std::tuple<add_remove_collection_info, tbb::flow::continue_msg>> umts_output_and_feedback_node;
typedef tbb::flow::multifunction_node<lte_info, std::tuple<add_remove_collection_info, tbb::flow::continue_msg>> lte_output_and_feedback_node;
typedef tbb::flow::multifunction_node<measurement_package, std::tuple<add_remove_collection_info, tbb::flow::continue_msg>> frequency_correction_node;

typedef tbb::flow::function_node<power_spectrum_package, tbb::flow::continue_msg> power_spectrum_processing_and_output_node;

typedef tbb::flow::function_node<measurement_package, tbb::flow::continue_msg> iq_data_output_node;

struct gps_command {
	enum GPS_COMMAND
	{
		COLLECT_GPS,
		ENABLE_1PPS,
		DISABLE_1PPS,
	};
	gps_command(GPS_COMMAND c) : cmd_(c) {}
	gps_command() : cmd_(COLLECT_GPS) {}
	GPS_COMMAND cmd_;
};
typedef tbb::flow::source_node <gps_command> gps_start_node;
typedef tbb::flow::function_node<gps_command, tbb::flow::continue_msg, tbb::flow::rejecting> gps_node;
typedef tbb::flow::queue_node<gps_command> gps_queue_node;



}}
