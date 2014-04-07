#pragma once

#include <stdint.h>
#include "rf_phreaker/umts_analysis/umts_types.h"

namespace rf_phreaker {

enum umts_scan_type
{
	full_scan_type,
	candidate_all_timeslots_scan_type,
	candidate_one_timeslot_scan_type
};



class umts_config 
{
public:
	umts_config()
		: sampling_rate_(4875000)
		, clock_rate_(9750000)
		, max_signal_length_(292864)
	{}

	umts_config(int sampling_rate, int clock_rate, int max_signal_length)
		: sampling_rate_(sampling_rate)
		, clock_rate_(clock_rate)
		, max_signal_length_(max_signal_length)
	{}

	bool benchmark_umts_brute_force() const { return false; }

	std::string umts_brute_force_filename() const { return "benchmark_umts_psch_with_brute_force.txt"; }

	int max_signal_length() const { return max_signal_length_; }
	int sampling_rate() const { return sampling_rate_; }
	int clock_rate() const { return clock_rate_; }
	double over_sampling_rate() const { return (double)sampling_rate_ / UMTS_CHIP_RATE_HZ; }

	void max_signal_length(int max_signal_length)  { max_signal_length_ = max_signal_length; }
	void sampling_rate(int sampling_rate) { sampling_rate_ = sampling_rate; }
	void clock_rate(int clock_rate)  { clock_rate_ = clock_rate; }

private:
	int max_signal_length_;
	int sampling_rate_;
	int clock_rate_;
};

}