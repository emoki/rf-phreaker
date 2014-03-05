#include "stdafx.h"
#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/switch_body.h"
#include "rf_phreaker/processing/collection_manager_body.h"
#include "rf_phreaker/processing/umts_cell_search_body.h"
#include "rf_phreaker/processing/output_and_feedback_body.h"
#include "rf_phreaker/processing/measurement_output_async.h"
#include "rf_phreaker/processing/processing_lte.h"


using namespace rf_phreaker::scanner;
using namespace rf_phreaker::processing;

std::atomic<bool> processing_;

processing_graph::processing_graph(void)
{
	processing_.store(false, std::memory_order_relaxed);
}


processing_graph::~processing_graph(void)
{
}

void processing_graph::initialize(scanner_controller_interface *sc, const collection_info_containers &collection_info, const rf_phreaker::settings &config)
{
	initialize_packets(config);

	auto g = std::shared_ptr<tbb::flow::graph>(new tbb::flow::graph);

	graphs_.push_back(g);

	io_ = std::make_shared<measurement_output_async>();

	start_node_ = std::make_shared<start_node>(*g, [=](add_remove_collection_info &info) { return processing_.load(std::memory_order_relaxed); }, false);
	collection_manager_node_ = std::make_shared<collection_manager_node>(*g, 1, collection_manager_body(processing_, sc, collection_info));
	
	auto umts_sweep_cell_search = std::make_shared<umts_cell_search_node>(*g, 1, umts_cell_search_body(umts_cell_search_settings()));
	auto umts_sweep_output_feedback = std::make_shared<umts_output_and_feedback_node>(*g, tbb::flow::unlimited, sweep_output_and_feedback_body(io_.get()));
	auto umts_layer_3_cell_search = std::make_shared<umts_cell_search_node>(*g, 1, umts_cell_search_body(umts_cell_search_settings()));
	auto umts_layer_3_decode = std::make_shared<umts_layer_3_decode_node>(*g, 1, umts_cell_search_body(umts_cell_search_settings()));
	auto umts_layer_3_output_feedback = std::make_shared<umts_output_and_feedback_node>(*g, tbb::flow::unlimited, layer_3_output_and_feedback_body(io_.get()));

	auto collection_queue = std::make_shared<queue_node>(*g);

	start_node_->register_successor(*collection_manager_node_);
	collection_queue->register_successor(*collection_manager_node_);

	tbb::flow::output_port<UMTS_SWEEP_PORT>(*collection_manager_node_).register_successor(*umts_sweep_cell_search);
	umts_sweep_cell_search->register_successor(*umts_sweep_output_feedback);
	tbb::flow::output_port<0>(*umts_sweep_output_feedback).register_successor(*collection_queue);
	tbb::flow::output_port<1>(*umts_sweep_output_feedback).register_successor(*collection_queue);

	tbb::flow::output_port<UMTS_LAYER3_PORT>(*collection_manager_node_).register_successor(*umts_layer_3_cell_search);
	umts_layer_3_cell_search->register_successor(*umts_layer_3_decode);
	umts_layer_3_decode->register_successor(*umts_layer_3_output_feedback);
	tbb::flow::output_port<0>(*umts_layer_3_output_feedback).register_successor(*collection_queue);
	tbb::flow::output_port<1>(*umts_layer_3_output_feedback).register_successor(*collection_queue);

	nodes_.push_back(collection_queue);
	nodes_.push_back(umts_sweep_cell_search);
	nodes_.push_back(umts_sweep_output_feedback);
	nodes_.push_back(umts_layer_3_cell_search);
	nodes_.push_back(umts_layer_3_decode);
	nodes_.push_back(umts_layer_3_output_feedback);
}

void processing_graph::initialize_packets(const rf_phreaker::settings &config)
{
	umts_sweep_collection_info::bandwidth__ = config.umts_sweep_collection_.bandwidth_;
	umts_sweep_collection_info::sampling_rate__ = config.umts_sweep_collection_.sampling_rate_;
	umts_sweep_collection_info::time_ns__ = config.umts_sweep_collection_.collection_time_;

	umts_layer_3_collection_info::bandwidth__ = config.umts_layer_3_collection_.bandwidth_;
	umts_layer_3_collection_info::sampling_rate__ = config.umts_layer_3_collection_.sampling_rate_;
	umts_layer_3_collection_info::time_ns__ = config.umts_layer_3_collection_.collection_time_;

	lte_sweep_collection_info::bandwidth__ = config.lte_sweep_collection_.bandwidth_;
	lte_sweep_collection_info::sampling_rate__ = config.lte_sweep_collection_.sampling_rate_;
	lte_sweep_collection_info::time_ns__ = config.lte_sweep_collection_.collection_time_;

	lte_layer_3_collection_info::bandwidth__ = config.lte_layer_3_collection_.bandwidth_;
	lte_layer_3_collection_info::sampling_rate__ = config.lte_layer_3_collection_.sampling_rate_;
	lte_layer_3_collection_info::time_ns__ = config.lte_layer_3_collection_.collection_time_;
}

void processing_graph::start()
{
	processing_.store(true, std::memory_order_release);
	start_node_->activate();
	//for(int i = 0; i < 20; ++i)
	//	collection_manager_node_->try_put(add_remove_collection_info());
}

void processing_graph::wait()
{
	for(auto &g : graphs_)
		g->wait_for_all();
}

void processing_graph::cancel()
{
	processing_.store(false, std::memory_order_release);

	for(auto &g : graphs_)
		g->root_task()->cancel_group_execution();

	for(auto &g : graphs_)
		g->wait_for_all();
}
