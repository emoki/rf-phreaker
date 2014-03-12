#include "stdafx.h"
#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/switch_body.h"
#include "rf_phreaker/processing/collection_manager_body.h"
#include "rf_phreaker/processing/umts_cell_search_body.h"
#include "rf_phreaker/processing/output_and_feedback_body.h"
#include "rf_phreaker/processing/processing_lte.h"
#include "tbb/task_scheduler_init.h"

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

void processing_graph::initialize_collection(scanner_controller_interface *sc, data_output_async *out, const collection_info_containers &collection_info, const rf_phreaker::settings &config)
{
	auto g = std::make_shared<tbb::flow::graph>();

	graphs_.push_back(g);

	start_node_ = std::make_shared<start_node>(*g, [=](add_remove_collection_info &info) { 
		return processing_.load(std::memory_order_relaxed); 
	}, false);

	auto max_limit =  tbb::task_scheduler_init::default_num_threads();
	if(config.num_items_in_flight_)
		max_limit = config.num_items_in_flight_;

	auto limiter = std::make_shared<limiter_node>(*g, max_limit);

	collection_manager_node_ = std::make_shared<collection_manager_node>(*g, tbb::flow::serial, collection_manager_body(processing_, sc, collection_info));
	
	auto umts_sweep_cell_search = std::make_shared<umts_cell_search_node>(*g, tbb::flow::serial, umts_cell_search_body(
		umts_cell_search_settings(config.umts_sweep_collection_, config.umts_decode_layer_3_, config.umts_sweep_general_)));
	auto umts_sweep_output_feedback = std::make_shared<umts_output_and_feedback_node>(*g, tbb::flow::serial, sweep_output_and_feedback_body(out));
	auto umts_layer_3_cell_search = std::make_shared<umts_cell_search_node>(*g, tbb::flow::serial, umts_cell_search_body(
		umts_cell_search_settings(config.umts_layer_3_collection_, config.umts_decode_layer_3_, config.umts_layer_3_general_)));
	auto umts_layer_3_decode = std::make_shared<umts_layer_3_decode_node>(*g, tbb::flow::serial, umts_cell_search_body(
		umts_cell_search_settings(config.umts_layer_3_collection_, config.umts_decode_layer_3_, config.umts_layer_3_general_)));
	auto umts_layer_3_output_feedback = std::make_shared<umts_output_and_feedback_node>(*g, tbb::flow::serial, layer_3_output_and_feedback_body(out));

	auto collection_queue = std::make_shared<queue_node>(*g);
	auto limiter_queue = std::make_shared<tbb::flow::queue_node<tbb::flow::continue_msg>>(*g);

	start_node_->register_successor(*limiter);
	collection_queue->register_successor(*limiter);

	limiter->register_successor(*collection_manager_node_);
	limiter_queue->register_successor(limiter->decrement);

	tbb::flow::output_port<UMTS_SWEEP_PORT>(*collection_manager_node_).register_successor(*umts_sweep_cell_search);
	umts_sweep_cell_search->register_successor(*umts_sweep_output_feedback);
	tbb::flow::output_port<0>(*umts_sweep_output_feedback).register_successor(*collection_queue);
	tbb::flow::output_port<1>(*umts_sweep_output_feedback).register_successor(*limiter_queue);

	tbb::flow::output_port<UMTS_LAYER3_PORT>(*collection_manager_node_).register_successor(*umts_layer_3_cell_search);
	umts_layer_3_cell_search->register_successor(*umts_layer_3_decode);
	umts_layer_3_decode->register_successor(*umts_layer_3_output_feedback);
	tbb::flow::output_port<0>(*umts_layer_3_output_feedback).register_successor(*collection_queue);
	tbb::flow::output_port<1>(*umts_layer_3_output_feedback).register_successor(*limiter_queue);

	nodes_.push_back(limiter);
	nodes_.push_back(limiter_queue);
	nodes_.push_back(collection_queue);
	nodes_.push_back(umts_sweep_cell_search);
	nodes_.push_back(umts_sweep_output_feedback);
	nodes_.push_back(umts_layer_3_cell_search);
	nodes_.push_back(umts_layer_3_decode);
	nodes_.push_back(umts_layer_3_output_feedback);
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

	wait();
}
