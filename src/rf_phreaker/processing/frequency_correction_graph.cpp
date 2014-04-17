#include "stdafx.h"
#include "rf_phreaker/processing/frequency_correction_graph.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/switch_body.h"
#include "rf_phreaker/processing/collection_manager_body.h"
#include "rf_phreaker/processing/umts_processing_body.h"
#include "rf_phreaker/processing/umts_output_and_feedback_body.h"
#include "rf_phreaker/processing/frequency_correction_body.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "tbb/task_scheduler_init.h"

using namespace rf_phreaker::scanner;
using namespace rf_phreaker::processing;

frequency_correction_graph::frequency_correction_graph(void)
{}

frequency_correction_graph::~frequency_correction_graph(void)
{}

void frequency_correction_graph::start(scanner_controller_interface *sc, data_output_async *out, const collection_info_containers &collection_info, const rf_phreaker::settings &config)
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);

	if(thread_ && thread_->joinable()) {
		cancel();
		wait();
	}

	thread_.reset(new std::thread([this](scanner_controller_interface *sc, data_output_async *out, const collection_info_containers &collection_info, const rf_phreaker::settings &config) {
		try {
			data_output_async tmp_data_output;

			start_node_.reset();
			collection_manager_node_.reset();
			nodes_.clear();

			graph_ = (std::make_shared<tbb::flow::graph>());

			start_node_ = std::make_shared<start_node>(*graph_, [=](add_remove_collection_info &info) { return true; }, false);
			collection_manager_node_ = std::make_shared<collection_manager_node>(*graph_, tbb::flow::serial, freq_correction_collection_manager_body(graph_.get(), sc, collection_info, config.packet_output_));

			// Only allow one item in flight - this allows us to change the trim value and have it affect all subsequent packets collected.
			auto max_limit = 1;

			auto limiter = std::make_shared<limiter_node>(*graph_, max_limit);

			auto umts_sweep_cell_search = std::make_shared<umts_cell_search_node>(*graph_, tbb::flow::serial, umts_processing_body(
				umts_cell_search_settings(config.umts_sweep_collection_, config.umts_decode_layer_3_, config.frequency_correction_settings_.general_settings_, 1)));
			auto umts_sweep_output_feedback = std::make_shared<umts_output_and_feedback_node>(*graph_, tbb::flow::serial, umts_sweep_output_and_feedback_body(&tmp_data_output));
			auto umts_freq_correction = std::make_shared<frequency_correction_node>(*graph_, tbb::flow::serial, frequency_correction_body(graph_.get(), sc, out,
				config.umts_sweep_collection_, config.frequency_correction_settings_, config.umts_layer_3_general_));

			auto collection_queue = std::make_shared<queue_node>(*graph_);
			auto limiter_queue = std::make_shared<tbb::flow::queue_node<tbb::flow::continue_msg>>(*graph_);

			start_node_->register_successor(*limiter);
			collection_queue->register_successor(*limiter);

			limiter->register_successor(*collection_manager_node_);
			limiter_queue->register_successor(limiter->decrement);

			tbb::flow::output_port<UMTS_SWEEP_PORT>(*collection_manager_node_).register_successor(*umts_sweep_cell_search);
			umts_sweep_cell_search->register_successor(*umts_sweep_output_feedback);
			tbb::flow::output_port<0>(*umts_sweep_output_feedback).register_successor(*collection_queue);
			tbb::flow::output_port<1>(*umts_sweep_output_feedback).register_successor(*limiter_queue);

			tbb::flow::output_port<UMTS_LAYER3_PORT>(*collection_manager_node_).register_successor(*umts_freq_correction);
			tbb::flow::output_port<0>(*umts_freq_correction).register_successor(*collection_queue);
			tbb::flow::output_port<1>(*umts_freq_correction).register_successor(*limiter_queue);

			tbb::flow::output_port<LIMITER_PORT>(*collection_manager_node_).register_successor(*limiter_queue);

			nodes_.push_back(limiter);
			nodes_.push_back(limiter_queue);
			nodes_.push_back(collection_queue);
			nodes_.push_back(umts_sweep_cell_search);
			nodes_.push_back(umts_sweep_output_feedback);
			nodes_.push_back(umts_freq_correction);

			start_node_->activate();

			graph_->wait_for_all();
		}
		catch(const rf_phreaker::rf_phreaker_error &err) {
			delegate_sink_async::instance().log_error(err.what(), GENERAL_ERROR);
		}
		catch(const std::exception &err) {
			delegate_sink_async::instance().log_error(err.what(), STD_EXCEPTION_ERROR);
		}
		catch(...) {
			delegate_sink_async::instance().log_error("An unknown error has occurred.", UNKNOWN_ERROR);
		}
	}, sc, out, collection_info, config));
}

void frequency_correction_graph::wait()
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	if(thread_ && thread_->joinable()) {
		thread_->join();
	}
}

void frequency_correction_graph::cancel()
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	if(thread_ && thread_->joinable()) {
		graph_->root_task()->cancel_group_execution();
	}
}

void frequency_correction_graph::cancel_and_wait()
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	cancel();
	wait();
}
