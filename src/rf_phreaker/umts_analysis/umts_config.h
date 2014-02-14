#pragma once

#include <stdint.h>

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
		: sample_rate_(4875000)
		, clock_rate_(9750000)
		, up_factor_(325)
		, down_factor_(256)
		, max_signal_length_(292864)
	{}

	bool benchmark_umts_brute_force() const { return false; }

	std::string umts_brute_force_filename() const { return "benchmark_umts_psch_with_brute_force.txt"; }

	int max_signal_length() const { return max_signal_length_; }
	double sample_rate() const { return sample_rate_; }
	double clock_rate() const { return clock_rate_; }
	double over_sampling_rate() const { return (double)up_factor_ / down_factor_; }
	int up_factor() const { return up_factor_; }
	int down_factor() const { return down_factor_; }

	void max_signal_length(int max_signal_length)  { max_signal_length_ = max_signal_length; }
	void sample_rate(double sample_rate)  { sample_rate_ = sample_rate; }
	void clock_rate(double clock_rate)  { clock_rate_ = clock_rate; }
	void up_factor(int up_factor)  { up_factor_ = up_factor; }
	void down_factor(int down_factor)  { down_factor_ = down_factor; }

private:
	int max_signal_length_;
	double sample_rate_;
	double clock_rate_;
	int up_factor_;
	int down_factor_;
};