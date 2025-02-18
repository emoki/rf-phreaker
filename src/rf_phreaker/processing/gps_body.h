#pragma once

#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/scanner_error_tracker.h"
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
		, calibration_requested_(false)
		, min_integration_time_(25)
		, max_integration_time_(25)		
		, current_integration_time_(min_integration_time_)
		, gps_1pps_calibration_enabled_(true)
		, error_count_(0)
	{}
	
	gps_body(const gps_body &body)
		: scanner_(body.scanner_)
		, data_output_(body.data_output_)
		, sleep_time_ms_(body.sleep_time_ms_)
		, calibration_requested_(body.calibration_requested_)
		, min_integration_time_(body.min_integration_time_)
		, max_integration_time_(body.max_integration_time_)
		, current_integration_time_(body.current_integration_time_)
		, gps_1pps_calibration_enabled_(body.gps_1pps_calibration_enabled_)
		, error_count_(0)
		// Cannot copy std::vector<std::future<>>. Use new one.
	{}
		
	tbb::flow::continue_msg operator()(gps_command cmd)
	{
		try {
			auto start = std::chrono::steady_clock::now();

			if(cmd.cmd_ == gps_command::DISABLE_1PPS) {
				gps_1pps_calibration_enabled_ = false;
				gps_1pps_calibration_stopped();
				LOG(LDEBUG) << "Disabling GPS 1PPS calibration.";
			}
			else if(cmd.cmd_ == gps_command::ENABLE_1PPS) {
				gps_1pps_calibration_enabled_ = true;
				LOG(LDEBUG) << "Enabling GPS 1PPS calibration.";
			}

			auto g = scanner_->get_gps_data().get();

			remove_completed_output();

			if(gps_1pps_calibration_enabled_) {
				if(g.lock_ && !calibration_requested_) {
					gps_1pps_calibration_started();
					scanner_->start_gps_1pps_integration(current_integration_time_).get();
					start_1pps_integration_time_ = std::chrono::steady_clock::now();
				}
				else if(calibration_requested_ && std::chrono::steady_clock::now() - start_1pps_integration_time_ > std::chrono::seconds(current_integration_time_ + 1)) {
					if(scanner_->attempt_gps_1pps_calibration().get()) {

						processing::g_scanner_error_tracker::instance().new_1pps_correction();

						current_integration_time_ = static_cast<int>(current_integration_time_ * 1.5);
						if(current_integration_time_ > max_integration_time_)
							current_integration_time_ = max_integration_time_;
					}
					else {
						current_integration_time_ = static_cast<int>(current_integration_time_ * .5);
						if(current_integration_time_ < min_integration_time_)
							current_integration_time_ = min_integration_time_;
					}

					gps_1pps_calibration_stopped();
				}
			}

			past_output_.push_back(data_output_->output(g));

			auto time_spent = std::chrono::steady_clock::now() - start;
			if(time_spent < sleep_time_ms_) {
				auto dur = sleep_time_ms_ - time_spent;
				std::this_thread::sleep_for(dur);
			}

			clear_errors();
		}
		catch(const rf_phreaker_error &err) {
			if(++error_count_ > 7) {
				throw err;
			}
			else {
				LOG(LERROR) << "Error during GPS communication. " << err.what() << ".  Retrying...";
			}
		}
		catch(const std::exception &err) {
			if(++error_count_ > 7) {
				throw err;
			}
			else {
				LOG(LERROR) << "Error during GPS communication. " << err.what() << ".  Retrying...";
			}
		}
		catch(...) {
			if(++error_count_ > 7)
				throw std::current_exception();
			else {
				LOG(LERROR) << "Unknown error during GPS communication.  Retrying...";
			}
		}

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

	void clear_errors() {
		error_count_ = 0;
	}

	void gps_1pps_calibration_started() {
		calibration_requested_ = true;
		processing::g_scanner_error_tracker::instance().gps_1pps_calibration_started();
	}

	void gps_1pps_calibration_stopped() {
		calibration_requested_ = false;
		processing::g_scanner_error_tracker::instance().gps_1pps_calibration_stopped();
	}

	rf_phreaker::scanner::scanner_controller_interface *scanner_;
	data_output_async *data_output_;
	std::chrono::duration<std::chrono::steady_clock::rep, std::chrono::steady_clock::period> sleep_time_ms_;
	std::vector<std::future<void>> past_output_;
	bool calibration_requested_;
	std::chrono::steady_clock::time_point start_1pps_integration_time_;
	int min_integration_time_;
	int max_integration_time_;
	int current_integration_time_;
	bool gps_1pps_calibration_enabled_;
	int error_count_;
};

}}