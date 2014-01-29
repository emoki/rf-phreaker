#pragma once

#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/scanner/gain.h"
#include <iostream>



namespace rf_phreaker { namespace scanner {


class measurement_info;
inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

// Contains all information necessary to process the IQ data.
// Needs scanner info, calibration data..
class measurement_info : public rf_phreaker::raw_signal
{
public:
	measurement_info() 
	{}

	measurement_info(int num_samples, rf_phreaker::frequency_type frequency, rf_phreaker::bandwidth_type bandwidth, 
		rf_phreaker::frequency_type sampling_rate, gain_type gain)
		: raw_signal(num_samples, frequency, bandwidth, sampling_rate)
		, gain_(gain)
	{}

    measurement_info(const measurement_info& other)
		: raw_signal(other)
		, gain_(other.gain_)
    {
    }

    measurement_info(measurement_info&& other)
		: raw_signal(std::move(other))
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
		raw_signal::swap(other);
		std::swap(this->gain_, other.gain_);
    }

	const gain_type& gain() const { return gain_; }

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

private:
	gain_type gain_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t)
{
	os << 1 << "\t";
	os << t.gain_.lna_gain_ << "\t";
	os << t.gain_.rxvga1_ << "\t";
	os << t.gain_.rxvga2_ << "\n";

	os << static_cast<const rf_phreaker::raw_signal&>(t);
	return os;
}

inline std::istream& operator>>(std::istream &is, rf_phreaker::scanner::measurement_info &t)
{
	int version;
	is >> version;
	int i; is >> i;  t.gain_.lna_gain_ = static_cast<lms::lna_gain_enum>(i);
	is >> t.gain_.rxvga1_;
	is >> t.gain_.rxvga2_;

	is >> static_cast<rf_phreaker::raw_signal&>(t);
	return is;
}

}}

