#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/ipp_array.h"
#include <iostream>



namespace rf_phreaker
{


class raw_signal;
inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::raw_signal &t);
inline std::istream& operator>>(std::istream &os, rf_phreaker::raw_signal &t);

// Contains the raw signal.
class raw_signal
{
public:
	raw_signal()
	{}

	raw_signal(int num_samples, rf_phreaker::frequency_type frequency, rf_phreaker::bandwidth_type bandwidth,
						rf_phreaker::frequency_type sampling_rate)
						: ipp_array_(num_samples)
						, bandwidth_(bandwidth)
						, sampling_rate_(sampling_rate)
						, frequency_(frequency)
	{}

	raw_signal(const raw_signal& other)
		: ipp_array_((other.ipp_array_))
		, bandwidth_((other.bandwidth_))
		, sampling_rate_((other.sampling_rate_))
		, frequency_((other.frequency_))
	{}

	raw_signal(raw_signal&& other)
		: ipp_array_(std::move(other.ipp_array_))
		, bandwidth_(std::move(other.bandwidth_))
		, sampling_rate_(std::move(other.sampling_rate_))
		, frequency_(std::move(other.frequency_))
	{}

	raw_signal& operator =(raw_signal other)
	{
		raw_signal tmp(other);
		tmp.swap(*this);
		return *this;
	}

	void swap(raw_signal &other)
	{
		ipp_array_.swap(other.ipp_array_);
		std::swap(this->bandwidth_, other.bandwidth_);
		std::swap(this->sampling_rate_, other.sampling_rate_);
		std::swap(this->frequency_, other.frequency_);
	}

	ipp_32fc_array& get_iq() { return ipp_array_; }

	const ipp_32fc_array& get_iq() const { return ipp_array_; }

	rf_phreaker::bandwidth_type bandwidth() const { return bandwidth_; }

	rf_phreaker::frequency_type sampling_rate() const { return sampling_rate_; }

	rf_phreaker::frequency_type frequency() const { return frequency_; }

	int time_ns() const { return static_cast<int>(ipp_array_.length() / (double)sampling_rate_ * 1e9); }

	void bandwidth(rf_phreaker::bandwidth_type b) { bandwidth_ = b; }

	void sampling_rate(rf_phreaker::frequency_type s) { sampling_rate_ = s; }

	void frequency(rf_phreaker::frequency_type f) { frequency_ = f; }

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::raw_signal &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::raw_signal &t);

private:
	ipp_32fc_array ipp_array_;

	rf_phreaker::bandwidth_type bandwidth_;

	rf_phreaker::frequency_type sampling_rate_;

	rf_phreaker::frequency_type frequency_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::raw_signal &t)
{
	os << 1 << "\t";
	os << t.frequency_ << "\t";
	os << t.sampling_rate_ << "\t";
	os << t.bandwidth_ << "\t";
	os << t.get_iq();
	return os;
}

inline std::istream& operator>>(std::istream &is, rf_phreaker::raw_signal &t)
{
	int version;
	is >> version;
	is >> t.frequency_;
	is >> t.sampling_rate_;
	is >> t.bandwidth_;
	is >> t.get_iq();
	return is;
}

}