#pragma once

#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/scanner/gain.h"
#include <iostream>



namespace rf_phreaker { namespace scanner {


class measurement_info;
inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

class measurement_info : public rf_phreaker::raw_signal
{
public:
	measurement_info()
		:raw_signal(0, -1, -1, -1)
		, gain_(lms::LNA_UNKNOWN, -1, -1)
		, collection_round_(-1)
		, operating_band_(OPERATING_BAND_UNKNOWN)
		, blade_adjustment_(0)
		, rf_board_adjustment_(0)
		, serial_("00000000000000000000000000000000")
	{}

	measurement_info(int num_samples, rf_phreaker::frequency_type frequency, rf_phreaker::bandwidth_type bandwidth,
					 rf_phreaker::frequency_type sampling_rate, const gain_type &gain, double blade_adj = 0, 
					 double band_adj = 0, int64_t cr = 0, const std::string &serial = "00000000000000000000000000000000")
					 : raw_signal(num_samples, frequency, bandwidth, sampling_rate)
					 , gain_(gain)
					 , collection_round_(cr)
					 , operating_band_(OPERATING_BAND_UNKNOWN)
					 , blade_adjustment_(blade_adj)
					 , rf_board_adjustment_(band_adj)
					 , serial_(serial)

	{}

	measurement_info(const measurement_info& other)
		: raw_signal(other)
		, collection_round_(other.collection_round_)
		, gain_(other.gain_)
		, operating_band_(other.operating_band_)
		, blade_adjustment_(other.blade_adjustment_)
		, rf_board_adjustment_(other.rf_board_adjustment_)
		, serial_(other.serial_)
	{}

	measurement_info(measurement_info&& other)
		: raw_signal(std::move(other))
		, gain_(std::move(other.gain_))
		, collection_round_(std::move(other.collection_round_))
		, operating_band_(std::move(other.operating_band_))
		, blade_adjustment_(std::move(other.blade_adjustment_))
		, rf_board_adjustment_(std::move(other.rf_board_adjustment_))
		, serial_(std::move(other.serial_))
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
		std::swap(this->collection_round_, other.collection_round_);
		std::swap(this->gain_, other.gain_);
		std::swap(this->operating_band_, other.operating_band_);
		std::swap(this->blade_adjustment_, other.blade_adjustment_);
		std::swap(this->rf_board_adjustment_, other.rf_board_adjustment_);
		std::swap(this->serial_, other.serial_);
	}

	const gain_type& gain() const { return gain_; }
	void gain(const gain_type &gain) { gain_ = gain; }
	int64_t collection_round() const { return collection_round_; }
	void collection_round(int64_t cr) { collection_round_ = cr; }
	operating_band get_operating_band() const { return operating_band_; }
	void set_operating_band(operating_band band) { operating_band_ = band; }
	double blade_adjustment() const { return blade_adjustment_; }
	void blade_adjustment(double adj) { blade_adjustment_ = adj; }
	double rf_board_adjustment() const { return rf_board_adjustment_; }
	void rf_board_adjustment(double adj) { rf_board_adjustment_ = adj; }
	std::string serial() { return serial_; }
	void serial(std::string serial) { serial_ = serial; }

	friend inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t);
	friend inline std::istream& operator>>(std::istream &os, rf_phreaker::scanner::measurement_info &t);

private:
	int64_t collection_round_;
	gain_type gain_;
	operating_band operating_band_;
	double blade_adjustment_;
	double rf_board_adjustment_;
	std::string serial_;
};

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::scanner::measurement_info &t)
{
	const char* header = "measurement";
	os << header << "\t";
	os << 2 << "\t";
	os << t.collection_round_ << "\t";
	os << t.operating_band_ << "\t";
	os << t.gain_.lna_gain_ << "\t";
	os << t.gain_.rxvga1_ << "\t";
	os << t.gain_.rxvga2_ << "\t";
	os << t.blade_adjustment_ << "\t";
	os << t.rf_board_adjustment_ << "\t";
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

		int version = stoi(parsed_data[1]);
		if(version >= 1) {
			t.collection_round_ = stoll(parsed_data[2]);
			int i = stoi(parsed_data[3]); t.operating_band_ = static_cast<operating_band>(i);
			i = stoi(parsed_data[4]);  t.gain_.lna_gain_ = static_cast<lms::lna_gain_enum>(i);
			t.gain_.rxvga1_ = stoi(parsed_data[5]);
			t.gain_.rxvga2_ = stoi(parsed_data[6]);
		}
		if(version >= 2) {
			t.blade_adjustment_ = std::stod(parsed_data[7]);
			t.rf_board_adjustment_ = std::stod(parsed_data[8]);
			t.serial_ = parsed_data[9];
		}

		is >> static_cast<rf_phreaker::raw_signal&>(t);
	}
	else
		throw rf_phreaker_error("Error reading measurement_info.");

	return is;

}

}}

