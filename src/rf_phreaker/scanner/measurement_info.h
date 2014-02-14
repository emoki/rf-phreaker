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
					 rf_phreaker::frequency_type sampling_rate, gain_type gain, int64_t cr = 0)
					 : raw_signal(num_samples, frequency, bandwidth, sampling_rate)
					 , gain_(gain)
					 , collection_round_(cr)
	{}

	measurement_info(const measurement_info& other)
		: raw_signal(other)
		, gain_(other.gain_)
		, collection_round_(other.collection_round_)
	{}

	measurement_info(measurement_info&& other)
		: raw_signal(std::move(other))
		, gain_(std::move(other.gain_))
		, collection_round_(std::move(other.collection_round_))
	{}

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
		std::swap(this->collection_round_, other.collection_round_);
	}

	const gain_type& gain() const { return gain_; }

	int64_t collection_round() const { return collection_round_; }

	void collection_round(int64_t cr) { collection_round_ = cr; }

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

private:
	int64_t collection_round_;
	gain_type gain_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t)
{
	os << 1 << "\t";
	os << t.collection_round_ << "\t";
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
	is >> t.collection_round_;
	int i; is >> i;  t.gain_.lna_gain_ = static_cast<lms::lna_gain_enum>(i);
	is >> t.gain_.rxvga1_;
	is >> t.gain_.rxvga2_;
	is >> static_cast<rf_phreaker::raw_signal&>(t);
	return is;
}

}}

