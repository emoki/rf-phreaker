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
	gps_graph() {
		is_initialized_ = false;
	}

	~gps_graph() {}

	void start(rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const settings &config) {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		if(thread_ && thread_->joinable()) {
			cancel();
			wait();
		}

		is_initialized_ = false;

		thread_.reset(new std::thread([this](rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const settings &config) {
			try {
				start_node_.reset();
				gps_command_entry_point_.reset();
				nodes_.clear();

				graph_ = (std::make_shared<tbb::flow::graph>());

				start_node_ = std::make_shared<gps_start_node>(*graph_, [=](gps_command&) { return true; }, false);

				auto gps = std::make_shared<gps_node>(*graph_, tbb::flow::serial, gps_body(sc, out, config));

				start_node_->register_successor(*gps);

				gps_command_entry_point_ = std::make_shared<gps_queue_node>(*graph_);
				
				gps_command_entry_point_->register_successor(*gps);

				nodes_.push_back(gps);

				start_node_->activate();

				is_initialized_ = true;

				graph_->wait_for_all();
			}
			catch(const rf_phreaker::rf_phreaker_error &err) {
				delegate_sink::instance().log_error(err);
			}
			catch(const std::exception &err) {
				delegate_sink::instance().log_error(err.what(), generic_error_type, STD_EXCEPTION_ERROR);
			}
			catch(...) {
				delegate_sink::instance().log_error("An unknown error has occurred.", generic_error_type, UNKNOWN_ERROR);
			}
		}, sc, out, config));
	}

	void enable_1pps_calibration() {
		if(thread_ && gps_command_entry_point_) {
			gps_command_entry_point_->try_put(gps_command::ENABLE_1PPS);
		}
	}

	void disable_1pps_calibration() {
		if(thread_ && gps_command_entry_point_) {
			gps_command_entry_point_->try_put(gps_command::DISABLE_1PPS);
		}
	}

	void cancel_and_wait() {
		std::lock_guard<std::recursive_mutex> lock(mutex_);
		cancel();
		wait();
		is_initialized_ = false;
	}

private:

	void wait() {
		std::lock_guard<std::recursive_mutex> lock(mutex_);
		if(thread_ && thread_->joinable()) {
			thread_->join();
		}
	}

	void cancel() {
		std::lock_guard<std::recursive_mutex> lock(mutex_);
		if(thread_ && thread_->joinable()) {
			int count = 0;
			while(!is_initialized_) {
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
				if(count++ > 500)
					throw processing_error("Unable to stop graph.");
			}
			graph_->root_task()->cancel_group_execution();
		}
	}
	std::shared_ptr<tbb::flow::graph> graph_;

	std::vector<std::shared_ptr<tbb::flow::graph_node>> nodes_;

	std::shared_ptr<gps_start_node> start_node_;

	std::shared_ptr<gps_queue_node> gps_command_entry_point_;

	std::unique_ptr<std::thread> thread_;

	std::recursive_mutex mutex_;

	std::atomic_bool is_initialized_;
};

}}
