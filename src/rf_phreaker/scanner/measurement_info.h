#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/ipp_custom/ipp_array.h"
#include "rf_phreaker/scanner/gain.h"
#include <iostream>



namespace rf_phreaker { namespace scanner {


class measurement_info;
inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

// Contains all information necessary to process the IQ data.
// Needs scanner info, calibration data..
class measurement_info
{
public:
	measurement_info() 
	{}

	measurement_info(int num_samples, rf_phreaker::frequency_type frequency, rf_phreaker::bandwidth_type bandwidth, 
		rf_phreaker::frequency_type sampling_rate, int time_ms, gain_type gain)
		: ipp_array_(num_samples)
		, bandwidth_(bandwidth)
		, sampling_rate_(sampling_rate)
		, frequency_(frequency)
		, time_ms_(time_ms)
		, gain_(gain)
	{}

    measurement_info(const measurement_info& other)
        : ipp_array_((other.ipp_array_))
        , bandwidth_((other.bandwidth_))
        , sampling_rate_((other.sampling_rate_))
        , frequency_((other.frequency_))
        , time_ms_((other.time_ms_))
		, gain_(other.gain_)
    {
    }

    measurement_info(measurement_info&& other)
		: ipp_array_(std::move(other.ipp_array_))
		, bandwidth_(std::move(other.bandwidth_))
		, sampling_rate_(std::move(other.sampling_rate_))
		, frequency_(std::move(other.frequency_))
		, time_ms_(std::move(other.time_ms_))
		, gain_(std::move(other.gain_))
	{
	}

    measurement_info& operator =(measurement_info other)
    {
        measurement_info tmp(other);
        tmp.swap(*this);
        return *this;
    }

    void swap(measurement_info &other)
    {
        ipp_array_.swap(other.ipp_array_);
        std::swap(this->bandwidth_, other.bandwidth_);
        std::swap(this->sampling_rate_, other.sampling_rate_);
        std::swap(this->frequency_, other.frequency_);
        std::swap(this->time_ms_, other.time_ms_);
		std::swap(this->gain_, other.gain_);
    }

	ipp_32fc_array& get_iq() { return ipp_array_; }

	const ipp_32fc_array& get_iq_const() const { return ipp_array_; }

	rf_phreaker::bandwidth_type bandwidth() const { return bandwidth_; }

	rf_phreaker::frequency_type sampling_rate() const { return sampling_rate_; }

	rf_phreaker::frequency_type frequency() const { return frequency_; }

	int time_ms() const { return time_ms_; }

	const gain_type& gain() const { return gain_; }

	void bandwidth(rf_phreaker::bandwidth_type b) { bandwidth_ = b; }

	void sampling_rate(rf_phreaker::frequency_type s) { sampling_rate_ = s; }

	void frequency(rf_phreaker::frequency_type f) { frequency_ = f; }

    void time_ms(int time_ms) { time_ms_ = time_ms; }

	void gain(gain_type g) { gain_ = g; }

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

private:
	ipp_32fc_array ipp_array_;

	rf_phreaker::bandwidth_type bandwidth_;

	rf_phreaker::frequency_type sampling_rate_;

	rf_phreaker::frequency_type frequency_;

	int time_ms_;

	gain_type gain_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t)
{
	os << 1 << "\t";
	os << t.time_ms_ << "\t";
	os << t.frequency_ << "\t";
	os << t.sampling_rate_ << "\t";
	os << t.bandwidth_ << "\t";
	os << t.gain_.lna_gain_ << "\t";
	os << t.gain_.rxvga1_ << "\t";
	os << t.gain_.rxvga2_ << "\t";
	os << t.get_iq_const();
	return os;
}

inline std::istream& operator>>(std::istream &is, rf_phreaker::scanner::measurement_info &t)
{
	int version;
	is >> version;
	is >> t.time_ms_;
	is >> t.frequency_;
	is >> t.sampling_rate_;
	is >> t.bandwidth_;
	int i; is >> i;  t.gain_.lna_gain_ = static_cast<lms::lna_gain_enum>(i);
	is >> t.gain_.rxvga1_;
	is >> t.gain_.rxvga2_;
	is >> t.get_iq();
	return is;
}

}}

