#pragma once

#include <stdint.h>
#include <vector>
#include <rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h>

namespace rf_phreaker {

class lte_config
{
public:
	lte_config(double pbch_decoding_threshold_db = -20.0, double minimum_relative_peak_threshold = 1/9.0)
	: sampling_rate_(4875000)
	, clock_rate_(4875000)
	, max_signal_length_((int)(.032 * sampling_rate_))
	, pbch_decoding_threshold_watts_(pow(10.0, pbch_decoding_threshold_db / 20.0))
	, minimum_relative_peak_threshold_(minimum_relative_peak_threshold) {}

	int max_signal_length() const { return max_signal_length_; }
	int sampling_rate() const { return sampling_rate_; }
	int clock_rate() const { return clock_rate_; }
	std::vector<layer_3_information::lte_sib_type> wanted_si() const { return wanted_si_; }
	double pbch_decoding_threshold_watts() const { return pbch_decoding_threshold_watts_; }
	double pbch_decoding_threshold_db() const { return 20 * log10(pbch_decoding_threshold_watts_); }
	double minimum_relative_peak_threshold() const { return minimum_relative_peak_threshold_; }


	void max_signal_length(int max_signal_length) { max_signal_length_ = max_signal_length; }
	void sampling_rate(int sampling_rate) { sampling_rate_ = sampling_rate; }
	void clock_rate(int clock_rate) { clock_rate_ = clock_rate; }
	void wanted_si(const std::vector<layer_3_information::lte_sib_type> &si) { wanted_si_ = si;	}
	void pbch_decoding_threshold_db(double pbch_decoding_threshold_db) { pbch_decoding_threshold_watts_ = pow(10.0, pbch_decoding_threshold_db / 20.0); }
	void pbch_decoding_threshold_watts(double pbch_decoding_threshold_w) { pbch_decoding_threshold_watts_ = pbch_decoding_threshold_w; }
	void minimum_relative_peak_threshold(double minimum_relative_peak_threshold) { minimum_relative_peak_threshold_ = minimum_relative_peak_threshold; }

private:
	int sampling_rate_;
	int clock_rate_;
	int max_signal_length_;
	std::vector<layer_3_information::lte_sib_type> wanted_si_;
	double pbch_decoding_threshold_watts_;
	double minimum_relative_peak_threshold_;
};

}