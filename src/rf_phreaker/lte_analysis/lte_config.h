#pragma once

#include <stdint.h>
#include <vector>
#include <rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h>

namespace rf_phreaker {

class lte_config
{
public:
	lte_config()
	: sampling_rate_(4875000)
	, clock_rate_(4875000)
	, max_signal_length_((int)(.032 * sampling_rate_))
	{}

	int max_signal_length() const { return max_signal_length_; }
	int sampling_rate() const { return sampling_rate_; }
	int clock_rate() const { return clock_rate_; }
	std::vector<layer_3_information::lte_sib_type> wanted_si() const { return wanted_si_; }

	void max_signal_length(int max_signal_length) { max_signal_length_ = max_signal_length; }
	void sampling_rate(int sampling_rate) { sampling_rate_ = sampling_rate; }
	void clock_rate(int clock_rate) { clock_rate_ = clock_rate; }
	void wanted_si(const std::vector<layer_3_information::lte_sib_type> &si) {
		wanted_si_ = si;
	}

private:
	int sampling_rate_;
	int clock_rate_;
	int max_signal_length_;
	std::vector<layer_3_information::lte_sib_type> wanted_si_;
};

}