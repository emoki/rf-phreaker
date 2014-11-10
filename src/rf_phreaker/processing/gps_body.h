#pragma once

#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/delegate_sink.h"

namespace rf_phreaker { namespace processing {


class gps_body
{
public:
	gps_body(rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const rf_phreaker::settings &config)
		: scanner_(sc)
		, data_output_(out)
		, sleep_time_ms_(std::chrono::milliseconds(config.gps_collection_period_ms_))
	{}
	
	gps_body(const gps_body &body)
		: scanner_(body.scanner_)
		, data_output_(body.data_output_)
		, sleep_time_ms_(body.sleep_time_ms_)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}
		
	tbb::flow::continue_msg operator()(tbb::flow::continue_msg)
	{
		auto start = std::chrono::steady_clock::now();

		auto g = scanner_->get_gps_data().get();

		remove_completed_output();

		auto time_spent = std::chrono::steady_clock::now() - start;
		if(time_spent < sleep_time_ms_) {
			auto dur = sleep_time_ms_ - time_spent;
			std::this_thread::sleep_for(dur);
		}

		past_output_.push_back(data_output_->output(g));

		return tbb::flow::continue_msg();
	}
	
private:
	void remove_completed_output() {
		int num_completed = 0;
		for(auto &fut : past_output_) {
			if(fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
				++num_completed;
			else
				break;
		}
		past_output_.erase(std::begin(past_output_), std::begin(past_output_) + num_completed);
	}

	rf_phreaker::scanner::scanner_controller_interface *scanner_;
	data_output_async *data_output_;
	std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> sleep_time_ms_;
	std::vector<std::future<void>> past_output_;
};

}}