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
		: num_coherent_psch_slots_(4)
		, max_num_psch_peaks_(25)
		, max_num_candidates_(1000)
		, psch_confidence_threshold_(11)
		, cpich_confidence_threshold_(13) 
	{}

	bool benchmark_umts_brute_force() const { return false; }

	std::string umts_brute_force_filename() const { return "benchmark_umts_psch_with_brute_force.txt"; }

	int max_signal_length() const { return max_signal_length_; }
	double sample_rate() const { return sample_rate_; }
	double clock_rate() const { return clock_rate_; }
	double over_sampling_rate() const { return (double)up_factor_ / down_factor_; }
	int up_factor() const { return up_factor_; }
	int down_factor() const { return down_factor_; }
	int num_coherent_psch_slots() const { return num_coherent_psch_slots_; }
	int max_num_psch_peaks() const { return max_num_psch_peaks_; }
	int max_num_candidates() const { return max_num_candidates_; }
	double psch_confidence_threshold() const { return psch_confidence_threshold_; }
	double cpich_confidence_threshold() const { return cpich_confidence_threshold_; }

	void max_signal_length(int max_signal_length)  { max_signal_length_ = max_signal_length; }
	void sample_rate(double sample_rate)  { sample_rate_ = sample_rate; }
	void clock_rate(double clock_rate)  { clock_rate_ = clock_rate; }
	void up_factor(int up_factor)  { up_factor_ = up_factor; }
	void down_factor(int down_factor)  { down_factor_ = down_factor; }
	void num_coherent_psch_slots(int num_coherent_psch_slots) { num_coherent_psch_slots_ = num_coherent_psch_slots; }
	void max_num_psch_peaks(int max_num_psch_peaks) { max_num_psch_peaks_ = max_num_psch_peaks; }
	void max_num_candidates(int max_num_candidates) { max_num_candidates_ = max_num_candidates; }
	void psch_confidence_threshold(double psch_confidence_threshold) { psch_confidence_threshold_ = psch_confidence_threshold; }
	void cpich_confidence_threshold(double cpich_confidence_threshold)  { cpich_confidence_threshold_ = cpich_confidence_threshold; }

private:
	int max_signal_length_;
	double sample_rate_;
	double clock_rate_;
	int up_factor_;
	int down_factor_;
	int num_coherent_psch_slots_;
	int max_num_psch_peaks_;
	int max_num_candidates_;
	double psch_confidence_threshold_;
	double cpich_confidence_threshold_;
};