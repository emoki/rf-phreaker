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
	bool benchmark_umts_brute_force() const { return false; }

	std::string umts_brute_force_filename() const { return "benchmark_umts_psch_with_brute_force.txt"; }

	int max_signal_length() const { return max_signal_length_; }
	double sample_rate() const { return sample_rate_; }
	double clock_rate() const { return clock_rate_; }
	double over_sampling_rate() const { return (double)up_factor_ / down_factor_; }
	int up_factor() const { return up_factor_; }
	int down_factor() const { return down_factor_; }
	double min_psch_ecio_processing_threshold() const { return min_psch_ecio_processing_threshold_; }
	double min_cpich_ecio_processing_threshold() const { return min_cpich_ecio_processing_threshold_; }

	void max_signal_length(int max_signal_length)  { max_signal_length_ = max_signal_length; }
	void sample_rate(double sample_rate)  { sample_rate_ = sample_rate; }
	void clock_rate(double clock_rate)  { clock_rate_ = clock_rate; }
	void up_factor(int up_factor)  { up_factor_ = up_factor; }
	void down_factor(int down_factor)  { down_factor_ = down_factor; }
	void min_psch_ecio_processing_threshold(double min_psch_ecio_processing_threshold)  { min_psch_ecio_processing_threshold_ = min_psch_ecio_processing_threshold; }
	void min_cpich_ecio_processing_threshold(double min_cpich_ecio_processing_threshold)  { min_cpich_ecio_processing_threshold_ = min_cpich_ecio_processing_threshold; }

private:
	int max_signal_length_;
	double sample_rate_;
	double clock_rate_;
	int up_factor_;
	int down_factor_;
	double min_psch_ecio_processing_threshold_;
	double min_cpich_ecio_processing_threshold_;
};