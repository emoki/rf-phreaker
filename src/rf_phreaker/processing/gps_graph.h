#pragma once

#include "rf_phreaker/processing/gps_body.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/delegate_sink.h"
#include <memory>


namespace rf_phreaker { namespace processing {

class gps_graph
{
public:
	gps_graph() 
	{}

	~gps_graph() {}

	void start(rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const settings &config)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		if(thread_ && thread_->joinable()) {
			cancel();
			wait();
		}

		thread_.reset(new std::thread([this](rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const settings &config) {
			try {
				start_node_.reset();
				nodes_.clear();

				graph_ = (std::make_shared<tbb::flow::graph>());

				start_node_ = std::make_shared<gps_start_node>(*graph_, [=](tbb::flow::continue_msg&) { return true; }, false);

				auto gps = std::make_shared<gps_node>(*graph_, tbb::flow::serial, gps_body(sc, out, config));

				start_node_->register_successor(*gps);

				nodes_.push_back(gps);

				start_node_->activate();

				graph_->wait_for_all();
			}
			catch(const rf_phreaker::rf_phreaker_error &err) {
				delegate_sink_async::instance().log_error(err.what(), -49999);
			}
			catch(const std::exception &err) {
				delegate_sink_async::instance().log_error(err.what(), -49998);
			}
			catch(...) {
				delegate_sink_async::instance().log_error("An unknown error has occurred.", -50000);
			}
		}, sc, out, config));
	}

	void cancel_and_wait()
	{
		std::lock_guard<std::recursive_mutex> lock(mutex_);
		cancel();
		wait();
	}

private:

	void wait()
	{
		std::lock_guard<std::recursive_mutex> lock(mutex_);
		if(thread_ && thread_->joinable()) {
			thread_->join();
		}
	}

	void cancel()
	{
		std::lock_guard<std::recursive_mutex> lock(mutex_);
		if(thread_ && thread_->joinable()) {
			graph_->root_task()->cancel_group_execution();
		}
	}
	std::shared_ptr<tbb::flow::graph> graph_;

	std::vector<std::shared_ptr<tbb::flow::graph_node>> nodes_;

	std::shared_ptr<gps_start_node> start_node_;

	std::unique_ptr<std::thread> thread_;

	std::recursive_mutex mutex_;
};

}}
