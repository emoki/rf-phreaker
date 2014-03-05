#pragma once

#include <stdint.h>
#include "rf_phreaker/umts_analysis/umts_types.h"

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
		//, up_factor_(325)
		//, down_factor_(256)
		, max_signal_length_(292864)
	{}

	bool benchmark_umts_brute_force() const { return false; }

	std::string umts_brute_force_filename() const { return "benchmark_umts_psch_with_brute_force.txt"; }

	int max_signal_length() const { return max_signal_length_; }
	int sampling_rate() const { return sampling_rate_; }
	int clock_rate() const { return clock_rate_; }
	double over_sampling_rate() const { return (double)sampling_rate_ / UMTS_CHIP_RATE_HZ; }
	//int up_factor() const { return up_factor_; }
	//int down_factor() const { return down_factor_; }

	void max_signal_length(int max_signal_length)  { max_signal_length_ = max_signal_length; }
	void sampling_rate(int sampling_rate) { sampling_rate_ = sampling_rate; }
	void clock_rate(int clock_rate)  { clock_rate_ = clock_rate; }
	//void up_factor(int up_factor)  { up_factor_ = up_factor; }
	//void down_factor(int down_factor)  { down_factor_ = down_factor; }

private:
	int max_signal_length_;
	int sampling_rate_;
	int clock_rate_;
	//int up_factor_;
	//int down_factor_;
};