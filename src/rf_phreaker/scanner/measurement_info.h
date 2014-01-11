#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/ipp_custom/ipp_array.h"
#include <iostream>



namespace rf_phreaker { namespace scanner {


class measurement_info;
inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

// Contains all information necessary to process the IQ data.
// Scanner info, calibration data, gain data, ?
class measurement_info
{
public:
	measurement_info() 
	{}

	measurement_info(int num_samples, rf_phreaker::frequency_type frequency, rf_phreaker::bandwidth_type bandwidth, 
		rf_phreaker::frequency_type sampling_rate, int time_ms)
		: ipp_array_(num_samples)
		, bandwidth_(bandwidth)
		, sampling_rate_(sampling_rate)
		, frequency_(frequency)
		, time_ms_(time_ms)
	{}

	measurement_info(measurement_info&& other)
		: ipp_array_(std::move(other.ipp_array_))
		, bandwidth_(std::move(other.bandwidth_))
		, sampling_rate_(std::move(other.sampling_rate_))
		, frequency_(std::move(other.frequency_))
		, time_ms_(std::move(other.time_ms_))
	{
	}

	ipp_32fc_array& get_iq() { return ipp_array_; }

	const ipp_32fc_array& get_iq_const() const { return ipp_array_; }

	rf_phreaker::bandwidth_type bandwidth() const { return bandwidth_; }

	rf_phreaker::frequency_type sampling_rate() const { return sampling_rate_; }

	rf_phreaker::frequency_type frequency() const { return frequency_; }

	int time_ms() const { return time_ms_; }

	void bandwidth(rf_phreaker::bandwidth_type b) { bandwidth_ = b; }

	void sampling_rate(rf_phreaker::frequency_type s) { sampling_rate_ = s; }

	void frequency(rf_phreaker::frequency_type f) { frequency_ = f; }

	int time_ms(int time_ms) { time_ms_ = time_ms; }

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

private:
	ipp_32fc_array ipp_array_;

	rf_phreaker::bandwidth_type bandwidth_;

	rf_phreaker::frequency_type sampling_rate_;

	rf_phreaker::frequency_type frequency_;

	int time_ms_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t)
{
	os << t.time_ms_ << "\t";
	os << t.frequency_ << "\t";
	os << t.sampling_rate_ << "\t";
	os << t.bandwidth_ << "\t";
	os << t.get_iq_const();
	return os;
}

inline std::istream& operator>>(std::istream &is, rf_phreaker::scanner::measurement_info &t)
{
	is >> t.time_ms_;
	is >> t.frequency_;
	is >> t.sampling_rate_;
	is >> t.bandwidth_;
	is >> t.get_iq();
	return is;
}

}}

