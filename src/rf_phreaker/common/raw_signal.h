#pragma once

#include <iostream>
#include <chrono>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/ipp_array.h"


namespace rf_phreaker {


class raw_signal;
inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::raw_signal &t);
inline std::istream& operator>>(std::istream &os, rf_phreaker::raw_signal &t);

// Contains the raw signal.
class raw_signal
{
public:
	raw_signal() {}

	raw_signal(int num_samples, rf_phreaker::frequency_type frequency, rf_phreaker::bandwidth_type bandwidth,
		rf_phreaker::frequency_type sampling_rate, std::chrono::milliseconds origin_time)
		: ipp_array_(num_samples)
		, bandwidth_(bandwidth)
		, sampling_rate_(sampling_rate)
		, frequency_(frequency)
		, origin_time_pc_(origin_time) {}

	raw_signal(const raw_signal& other)
		: ipp_array_((other.ipp_array_))
		, bandwidth_((other.bandwidth_))
		, sampling_rate_((other.sampling_rate_))
		, frequency_((other.frequency_))
		, origin_time_pc_(other.origin_time_pc_) {}

	raw_signal(raw_signal&& other)
		: ipp_array_(std::move(other.ipp_array_))
		, bandwidth_(std::move(other.bandwidth_))
		, sampling_rate_(std::move(other.sampling_rate_))
		, frequency_(std::move(other.frequency_))
		, origin_time_pc_(std::move(other.origin_time_pc_)) {}

	raw_signal& operator =(raw_signal other) {
		raw_signal tmp(other);
		tmp.swap(*this);
		return *this;
	}

	bool operator == (const raw_signal &a) const {
		return bandwidth_ == a.bandwidth() &&
			sampling_rate_ == a.sampling_rate() &&
			frequency_ == a.frequency() &&
			origin_time_pc_ == a.origin_time_pc() &&
			ipp_array_ == a.get_iq();
	}

	void swap(raw_signal &other) {
		ipp_array_.swap(other.ipp_array_);
		std::swap(this->bandwidth_, other.bandwidth_);
		std::swap(this->sampling_rate_, other.sampling_rate_);
		std::swap(this->frequency_, other.frequency_);
		std::swap(this->origin_time_pc_, other.origin_time_pc_);
	}

	ipp_32fc_array& get_iq() { return ipp_array_; }

	const ipp_32fc_array& get_iq() const { return ipp_array_; }

	rf_phreaker::bandwidth_type bandwidth() const { return bandwidth_; }

	rf_phreaker::frequency_type sampling_rate() const { return sampling_rate_; }

	rf_phreaker::frequency_type frequency() const { return frequency_; }

	time_type time_ns() const { return static_cast<time_type>(ipp_array_.length() / (double)sampling_rate_ * 1e9); }

	std::chrono::milliseconds origin_time_pc() const { return origin_time_pc_; }

	void bandwidth(rf_phreaker::bandwidth_type b) { bandwidth_ = b; }

	void sampling_rate(rf_phreaker::frequency_type s) { sampling_rate_ = s; }

	void frequency(rf_phreaker::frequency_type f) { frequency_ = f; }

	void origin_time_pc(std::chrono::milliseconds t) { origin_time_pc_ = t; }

	typedef ipp_32fc_array::data_type_ sample_type;

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::raw_signal &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::raw_signal &t);

private:
	ipp_32fc_array ipp_array_;

	rf_phreaker::bandwidth_type bandwidth_;

	rf_phreaker::frequency_type sampling_rate_;

	rf_phreaker::frequency_type frequency_;

	std::chrono::milliseconds origin_time_pc_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::raw_signal &t) {
	const char* header = "signal";
	os << header << "\t";
	os << 2 << "\t";
	os << t.frequency_ << "\t";
	os << t.sampling_rate_ << "\t";
	os << t.bandwidth_ << "\t";
	os << t.origin_time_pc_.count() << "\n";
	os << t.get_iq();
	return os;
}

inline std::istream& operator>>(std::istream &is, rf_phreaker::raw_signal &t) {
	const char* header = "signal";
	std::string tmp;
	std::vector<std::string> parsed_data;
	std::regex pattern("\t");
	do {
		std::getline(is, tmp);
		parsed_data = tokenize(tmp, pattern);
	}
	while(is.good() && (parsed_data.size() == 0 || parsed_data.begin()->compare(header) != 0));

	if(parsed_data.size() && parsed_data.begin()->compare(header) == 0) {

		int version = stoi(parsed_data[1]);
		if(version >= 1) {
			t.frequency_ = stoll(parsed_data[2]);
			t.sampling_rate_ = stoll(parsed_data[3]);
			t.bandwidth_ = stol(parsed_data[4]);
		}
		if(version >= 2) {
			t.origin_time_pc_ = std::chrono::milliseconds(stoll(parsed_data[5]));
		}

		is >> t.get_iq();
	}
	else
		throw file_io_error("Error reading raw_signal.");


	return is;
}

}