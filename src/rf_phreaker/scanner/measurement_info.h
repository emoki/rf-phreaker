#pragma once

#include <iostream>
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/scanner/gain.h"
#include "rf_phreaker/scanner/rf_adjustment.h"



namespace rf_phreaker { namespace scanner {


class measurement_info;
inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

class measurement_info : public rf_phreaker::raw_signal
{
public:
	measurement_info()
		:raw_signal(0, -1, -1, -1, std::chrono::milliseconds(0))
		, gain_(lms::LNA_UNKNOWN, -1, -1)
		, collection_round_(-1)
		, operating_band_(OPERATING_BAND_UNKNOWN)
		, serial_("00000000000000000000000000000000")
	{}

	measurement_info(int num_samples, rf_phreaker::frequency_type frequency, rf_phreaker::bandwidth_type bandwidth,
		rf_phreaker::frequency_type sampling_rate, const gain_type &gain, std::chrono::milliseconds orgin_time_pc = std::chrono::milliseconds(0), rf_adjustment blade_adj = {},
		rf_adjustment band_adj = {}, int64_t cr = 0, const std::string &serial = "00000000000000000000000000000000")
		: raw_signal(num_samples, frequency, bandwidth, sampling_rate, orgin_time_pc)
		, gain_(gain)
		, collection_round_(cr)
		, operating_band_(OPERATING_BAND_UNKNOWN)
		, blade_adjustments_(blade_adj)
		, rf_board_adjustments_(band_adj)
		, serial_(serial) {}

	measurement_info(const measurement_info& other)
		: raw_signal(other)
		, collection_round_(other.collection_round_)
		, gain_(other.gain_)
		, operating_band_(other.operating_band_)
		, blade_adjustments_(other.blade_adjustments_)
		, rf_board_adjustments_(other.rf_board_adjustments_)
		, serial_(other.serial_)
	{}

	measurement_info(measurement_info&& other)
		: raw_signal(std::move(other))
		, gain_(std::move(other.gain_))
		, collection_round_(std::move(other.collection_round_))
		, operating_band_(std::move(other.operating_band_))
		, blade_adjustments_(std::move(other.blade_adjustments_))
		, rf_board_adjustments_(std::move(other.rf_board_adjustments_))
		, serial_(std::move(other.serial_))
	{}

	measurement_info& operator =(measurement_info other) {
		measurement_info tmp(other);
		tmp.swap(*this);
		return *this;
	}

	bool operator ==(const measurement_info &a) const {
		return gain_ == a.gain() &&
			collection_round_ == a.collection_round() &&
			operating_band_ == a.operating_band_ &&
			blade_adjustments_ == a.blade_adjustments() &&
			rf_board_adjustments_ == a.rf_board_adjustments() &&
			serial_ == a.serial() &&
			raw_signal::operator==(a);
	}

	void swap(measurement_info &other)
	{
		raw_signal::swap(other);
		std::swap(this->collection_round_, other.collection_round_);
		std::swap(this->gain_, other.gain_);
		std::swap(this->operating_band_, other.operating_band_);
		std::swap(this->blade_adjustments_, other.blade_adjustments_);
		std::swap(this->rf_board_adjustments_, other.rf_board_adjustments_);
		std::swap(this->serial_, other.serial_);
	}

	const gain_type& gain() const { return gain_; }
	int64_t collection_round() const { return collection_round_; }
	operating_band get_operating_band() const { return operating_band_; }
	const rf_adjustment& blade_adjustments() const { return blade_adjustments_; }
	void gain(const gain_type &gain) { gain_ = gain; }
	const rf_adjustment& rf_board_adjustments() const { return rf_board_adjustments_; }
	double blade_adjustment_value(frequency_type freq) const { return blade_adjustments_.find_adjustment(freq); }
	double rf_board_adjustment_value(frequency_type freq) const { return rf_board_adjustments_.find_adjustment(freq); }
	std::string serial() const { return serial_; }

	void collection_round(int64_t cr) { collection_round_ = cr; }
	void set_operating_band(operating_band band) { operating_band_ = band; }
	void blade_adjustments(rf_adjustment adj) { blade_adjustments_ = adj; }
	void rf_board_adjustments(rf_adjustment adj) { rf_board_adjustments_ = adj; }
	void serial(std::string serial) { serial_ = serial; }

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

private:
	int64_t collection_round_;
	gain_type gain_;
	operating_band operating_band_;
	rf_adjustment blade_adjustments_;
	rf_adjustment rf_board_adjustments_;
	std::string serial_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t)
{
	const char* header = "measurement";
	os << header << "\t";
	os << 3 << "\t";
	os << t.collection_round_ << "\t";
	os << t.operating_band_ << "\t";
	os << t.gain_.lna_gain_ << "\t";
	os << t.gain_.rxvga1_ << "\t";
	os << t.gain_.rxvga2_ << "\t";
	os << t.blade_adjustments_.path_.low_freq_ << "\t";
	os << t.blade_adjustments_.path_.high_freq_ << "\t";
	os << t.blade_adjustments_.spacing_ << "\t";
	os << t.blade_adjustments_.rf_adjustments_.size() << "\t";
	for(const auto i : t.blade_adjustments_.rf_adjustments_)
		os << i << "\t";
	os << t.rf_board_adjustments_.path_.low_freq_ << "\t";
	os << t.rf_board_adjustments_.path_.high_freq_ << "\t";
	os << t.rf_board_adjustments_.spacing_ << "\t";
	os << t.rf_board_adjustments_.rf_adjustments_.size() << "\t";
	for(const auto i : t.rf_board_adjustments_.rf_adjustments_)
		os << i << "\t";
	os << t.serial_ << "\n";
	os << static_cast<const rf_phreaker::raw_signal&>(t);
	return os;
}

inline std::istream& operator>>(std::istream &is, rf_phreaker::scanner::measurement_info &t)
{
	const char* header = "measurement";
	std::string tmp;
	std::vector<std::string> parsed_data;
	std::regex pattern("\t");
	do {
		std::getline(is, tmp);
		parsed_data = tokenize(tmp, pattern);
	}
	while(is.good() && (parsed_data.size() == 0 || parsed_data.begin()->compare(header) != 0));

	if(parsed_data.size() && parsed_data.begin()->compare(header) == 0) {

		int pos = 1;
		int version = stoi(parsed_data[pos++]);
		if(version >= 1) {
			t.collection_round_ = stoll(parsed_data[pos++]);
			int i = stoi(parsed_data[pos++]); t.operating_band_ = static_cast<operating_band>(i);
			i = stoi(parsed_data[pos++]);  t.gain_.lna_gain_ = lms::to_lna_gain(i);
			t.gain_.rxvga1_ = stoi(parsed_data[pos++]);
			t.gain_.rxvga2_ = stoi(parsed_data[pos++]);
		}
		if(version == 2) {
			t.blade_adjustments_ = rf_adjustment(frequency_path(), std::stod(parsed_data[pos++]));
			t.rf_board_adjustments_ = rf_adjustment(frequency_path(), std::stod(parsed_data[pos++]));
			t.serial_ = parsed_data[pos++];
		}
		else if(version == 3) {
			t.blade_adjustments_.path_.low_freq_ = std::stoll(parsed_data[pos++]);
			t.blade_adjustments_.path_.high_freq_ = std::stoll(parsed_data[pos++]);
			t.blade_adjustments_.spacing_ = std::stoll(parsed_data[pos++]);
			int tmp_size = std::stoi(parsed_data[pos++]);
			for(int i = 0; i < tmp_size; ++i) 
				t.blade_adjustments_.rf_adjustments_.push_back(std::stod(parsed_data[i + pos]));
			pos += tmp_size;

			t.rf_board_adjustments_.path_.low_freq_ = std::stoll(parsed_data[pos++]);
			t.rf_board_adjustments_.path_.high_freq_ = std::stoll(parsed_data[pos++]);
			t.rf_board_adjustments_.spacing_ = std::stoll(parsed_data[pos++]);
			tmp_size = std::stoi(parsed_data[pos++]);
			for(int i = 0; i < tmp_size; ++i)
				t.rf_board_adjustments_.rf_adjustments_.push_back(std::stod(parsed_data[i + pos]));
			pos += tmp_size;

			t.serial_ = parsed_data[pos++];
		}

		is >> static_cast<rf_phreaker::raw_signal&>(t);

		// If version 2 complete the adjustments after we've populated frequency.
		if(version >= 2) {
			t.blade_adjustments_.path_.low_freq_ = t.frequency();
			t.blade_adjustments_.path_.high_freq_ = t.frequency();
			t.rf_board_adjustments_.path_.low_freq_ = t.frequency();
			t.rf_board_adjustments_.path_.high_freq_ = t.frequency();
		}
	}
	else
		throw rf_phreaker_error("Error reading measurement_info.");

	return is;

}

}}

