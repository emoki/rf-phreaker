#pragma once

#include <stdint.h>

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

	void max_signal_length(int max_signal_length) { max_signal_length_ = max_signal_length; }
	void sampling_rate(int sampling_rate) { sampling_rate_ = sampling_rate; }
	void clock_rate(int clock_rate) { clock_rate_ = clock_rate; }

private:
	int sampling_rate_;
	int clock_rate_;
	int max_signal_length_;
};