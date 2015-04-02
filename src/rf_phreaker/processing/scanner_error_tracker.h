#pragma once

#include "rf_phreaker/common/singleton.h"
#include <chrono>
#include <mutex>

namespace rf_phreaker { namespace processing {

class scanner_error_tracker;
typedef singleton<scanner_error_tracker> g_scanner_error_tracker;

class scanner_error_tracker
{
public:
	scanner_error_tracker() 
		: before_settling_(3.0 / 38400000, .5 / 38400000, 1.0 / 38400000)
		, after_settling_(1.5 / 38400000, .25 / 38400000, .25 / 38400000) {
		reset();
	}

	void reset() {
		std::lock_guard<std::mutex> lock(mutex_);
		correction_type_ = CORR_FREQ;
		settling_time_ = 5 * 60 + 30;
		start_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		last_error_correction_ = -1;
		has_passed_settling_time_ = false;
	}

	double current_error() {
		std::lock_guard<std::mutex> lock(mutex_);

		if(has_passed_settling_time()) {
			if(has_correction())
				return correction_type_ == CORR_1PPS ? after_settling_.pps_ : after_settling_.freq_corr_;
			else
				return after_settling_.max_error_;
		}
		else {
			if(has_correction())
				return correction_type_ == CORR_1PPS ? before_settling_.pps_ : before_settling_.freq_corr_;
			else
				return before_settling_.max_error_;
		}
	}

	void new_freq_correction() {
		std::lock_guard<std::mutex> lock(mutex_);
		correction_type_ = CORR_FREQ;
		last_error_correction_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	void new_1pps_correction() {
		std::lock_guard<std::mutex> lock(mutex_);
		correction_type_ = CORR_1PPS;
		last_error_correction_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

private:
	bool has_passed_settling_time() {
		if(!has_passed_settling_time_)
			has_passed_settling_time_ = start_time_ + settling_time_ < std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		return has_passed_settling_time_;
	}

	bool has_correction() {
		return last_error_correction_ != -1;
	}

	enum correction_type {
		CORR_FREQ,
		CORR_1PPS
	};
	correction_type correction_type_;
	time_t settling_time_;
	time_t last_error_correction_;
	time_t start_time_;
	struct errors {
		errors(double m, double p, double f) : max_error_(m), pps_(p), freq_corr_(f) {}
		double max_error_;
		double pps_;
		double freq_corr_;
	};
	errors before_settling_;
	errors after_settling_;

	bool has_passed_settling_time_;
	std::mutex mutex_;
};


}}