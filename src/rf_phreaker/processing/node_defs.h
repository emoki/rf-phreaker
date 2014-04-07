#pragma once

#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "tbb/flow_graph.h"
#include <tuple>
#include <memory>

namespace rf_phreaker { namespace processing {

typedef std::shared_ptr<scanner::measurement_info> measurement_package;

template<typename Data>
class analysis_data
{
public:
	analysis_data() : avg_rms_(0), remove_(false)
	{}
	//analysis_data(scanner::measurement_info meas, Data data, double rms = 0, bool remove = false)
	//	: meas_(meas)
	//	, processed_data_(data)
	//	, avg_rms_(rms)
	//	, remove_(remove)
	//{}
	analysis_data(measurement_package meas, Data &&data, double rms = 0, bool remove = false)
		: meas_(std::move(meas))
		, processed_data_(std::move(data))
		, avg_rms_(rms)
		, remove_(remove)
	{}

	measurement_package meas_;
	Data processed_data_;
	double avg_rms_;
	bool remove_;
};

typedef analysis_data<umts_measurements> umts_info;
typedef analysis_data<lte_measurements> lte_info;

typedef tbb::flow::source_node<add_remove_collection_info> start_node;

typedef tbb::flow::limiter_node<add_remove_collection_info> limiter_node;

typedef tbb::flow::queue_node<add_remove_collection_info> queue_node;

#define UMTS_SWEEP_PORT 0
#define UMTS_LAYER3_PORT 1
#define LTE_SWEEP_PORT 2
#define LTE_LAYER3_PORT 3
#define LIMITER_PORT 4
typedef std::tuple<measurement_package, measurement_package, measurement_package, measurement_package, tbb::flow::continue_msg> tech_measurement_ports;
typedef tbb::flow::multifunction_node<add_remove_collection_info, tech_measurement_ports, tbb::flow::rejecting> collection_manager_node;

typedef tbb::flow::function_node<measurement_package, umts_info> umts_cell_search_node;
typedef tbb::flow::function_node<measurement_package, lte_info> lte_cell_search_node;

typedef tbb::flow::function_node<umts_info, umts_info> umts_layer_3_decode_node;
typedef tbb::flow::function_node<lte_info, lte_info> lte_layer_3_decode_node;

typedef tbb::flow::multifunction_node<umts_info, std::tuple<add_remove_collection_info, tbb::flow::continue_msg>> umts_output_and_feedback_node;
typedef tbb::flow::multifunction_node<lte_info, std::tuple<add_remove_collection_info, tbb::flow::continue_msg>> lte_output_and_feedback_node;
typedef tbb::flow::multifunction_node<measurement_package, std::tuple<add_remove_collection_info, tbb::flow::continue_msg>> frequency_correction_node;

typedef tbb::flow::source_node <tbb::flow::continue_msg> gps_start_node;
typedef tbb::flow::function_node<tbb::flow::continue_msg, tbb::flow::continue_msg, tbb::flow::rejecting> gps_node;



}}
