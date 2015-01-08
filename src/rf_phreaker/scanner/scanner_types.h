#ifndef __VAR_TYPES_H__
#define __VAR_TYPES_H__

#include <stdint.h>
#include <string>
#include <vector>
#include <chrono>

namespace rf_phreaker { namespace scanner {

typedef std::vector<char> buf_type;

// Keep unsigned due to bitwise operations.
typedef uint8_t lms_register_type;

typedef uint8_t lms_value_type;

typedef short sample_type;

typedef int32_t band_identifier_type;

struct iq_sample_type
{
	sample_type i;
	sample_type q;
};

struct gps_1pps_integration {
	gps_1pps_integration() : seconds_integrated_(0), clock_ticks_(0), time_calculated_(0), reference_clock_(38400000) {}
	int64_t clock_ticks() { return clock_ticks_; }
	int seconds_integrated() { return seconds_integrated_; }
	bool is_valid() { return clock_ticks_ != 0; }
	double error_in_hz() { return clock_ticks_ / (double)seconds_integrated_ - reference_clock_; }
	bool within_tolerance() { return abs(seconds_integrated_ * reference_clock_ - clock_ticks_) < reference_clock_ / 2; }
	void set_clock_ticks(int64_t ticks, time_t current_time) {
		clock_ticks_ = ticks;
		time_calculated_ = current_time;
	}
	void reset(int seconds_integrated) { 
		seconds_integrated_ = seconds_integrated; 
		clock_ticks_ = 0;
		time_calculated_ = 0;
	}
	time_t time_calculated() { return time_calculated_; }
private:
	int seconds_integrated_;
	int64_t clock_ticks_;
	int64_t reference_clock_;
	time_t time_calculated_;
};


}}

#endif
