#pragma once

#include <vector>
#include <map>
#include "boost/serialization/access.hpp"
#include "boost/serialization/vector.hpp"
#include "boost/serialization/map.hpp"
#include "boost/serialization/version.hpp"
#include "rf_phreaker/scanner/gain.h"
#include "rf_phreaker/scanner/eeprom_defines.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/serialization_helper.h"

namespace boost { namespace serialization {
	template<class Archive>
	void serialize(Archive & ar, rf_phreaker::frequency_path &path, const unsigned int version)
	{
		ar & path.low_freq_;
		ar & path.high_freq_;
	}
}}

namespace rf_phreaker { namespace scanner {

static const char* rf_switch_header = "RF Switch Settings";
static const char* rf_board_calibration_header = "RF Board Calibration";
static const char* nuand_calibration_header = "Nuand RF Calibration";

class rf_switch_setting
{
public:
	rf_switch_setting() : identifier_(0), bandwidth_(0), switch_setting_(0), switch_mask_(0), path_(-1, -1) {}
	rf_switch_setting(band_identifier_type id, bandwidth_type bw, frequency_type low_freq, frequency_type high_freq, uint32_t setting, uint32_t switch_mask)
		: identifier_(id)
		, bandwidth_(bw)
		, path_(low_freq, high_freq)
		, switch_setting_(setting)
		, switch_mask_(switch_mask)
	{}
	rf_switch_setting& operator=(const rf_switch_setting &s)
	{
		identifier_ = s.identifier_;
		bandwidth_ = s.bandwidth_;
		path_.low_freq_ = s.path_.low_freq_;
		path_.high_freq_ = s.path_.high_freq_;
		switch_setting_ = s.switch_setting_;
		switch_mask_ = s.switch_mask_;
		return *this;
	}
	bool operator==(const rf_switch_setting &s) const {
		return identifier_ == s.identifier_ && bandwidth_ == s.bandwidth_ && path_.low_freq_ == s.path_.low_freq_ && path_.high_freq_ == s.path_.high_freq_ &&
			switch_setting_ == s.switch_setting_ && switch_mask_ == s.switch_mask_;
	}
	band_identifier_type identifier_;
	bandwidth_type bandwidth_;
	frequency_path path_;
	uint32_t switch_setting_;
	uint32_t switch_mask_;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & identifier_;
		ar & bandwidth_;
		ar & path_;
		ar & switch_setting_;
		ar & switch_mask_;
	}
};

class rf_adjustment
{
public:
	rf_adjustment() : path_(-1, -1), spacing_(-1) {}
	rf_adjustment(const rf_adjustment &s)
		: path_(s.path_.low_freq_, s.path_.high_freq_)
		, spacing_(s.spacing_)
		, rf_adjustments_(s.rf_adjustments_)
	{}
	rf_adjustment& operator=(const rf_adjustment &s)
	{
		path_.low_freq_ = s.path_.low_freq_;
		path_.high_freq_ = s.path_.high_freq_;
		spacing_ = s.spacing_;
		rf_adjustments_ = s.rf_adjustments_;
		return *this;
	}
	void clear() { path_.low_freq_ = -1; path_.high_freq_ = -1; spacing_ = -1; rf_adjustments_.clear(); }
	bool operator==(const rf_adjustment &s) const {
		return path_.low_freq_ == s.path_.low_freq_ && path_.high_freq_ == s.path_.high_freq_ &&
			spacing_ == s.spacing_ && rf_adjustments_ == s.rf_adjustments_;
	}

	frequency_path path_;
	frequency_type spacing_;
	std::vector<double> rf_adjustments_;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & path_;
		ar & spacing_;
		ar & rf_adjustments_;
	}

};

class rf_path_adjustment
{
public:
	rf_path_adjustment() : identifier_(-1) {}
	rf_path_adjustment& operator=(const rf_path_adjustment& s) {
		identifier_ = s.identifier_;
		adj_ = s.adj_;
		return *this;
	}
	bool operator==(const rf_path_adjustment &s) const {
		return identifier_ == s.identifier_ && adj_ == s.adj_;
	}
	band_identifier_type identifier_;
	rf_adjustment adj_;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & identifier_;
		ar & adj_;
	}
};

class lna_adjustment {
public:
	lna_adjustment() : lna_gain_(lms::LNA_UNKNOWN) {}
	lna_adjustment& operator=(const lna_adjustment& s) {
		lna_gain_ = s.lna_gain_;
		adj_ = s.adj_;
		return *this;
	}
	bool operator==(const lna_adjustment &s) const {
		return lna_gain_ == s.lna_gain_ && adj_ == s.adj_;
	}
	lms::lna_gain_enum lna_gain_;
	rf_adjustment adj_;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & lna_gain_;
		ar & adj_;
	}
};

class calibration
{
public:
	calibration() : nuand_calibration_date_(0), rf_board_calibration_date_(0), hw_id_(0) {}
	rf_switch_setting get_rf_switch(frequency_type freq, bandwidth_type bw) const;
	double get_rf_board_adjustment(frequency_type freq, bandwidth_type bw)  const;
	double get_nuand_adjustment(lms::lna_gain_enum gain, frequency_type freq)  const;
	void read_rf_switch_file(const std::string &file);
	void read_rf_board_calibration_file(const std::string &file);
	void read_nuand_calibration_file(const std::string &file);

	rf_path_adjustment parse_rf_path_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end);
	lna_adjustment parse_lna_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end);
	rf_adjustment parse_rf_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end);
	rf_switch_setting parse_rf_switch_setting(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end);

	void clear();

	calibration& operator=(const calibration& cal) {
		nuand_serial_ = cal.nuand_serial_;
		nuand_calibration_date_ = cal.nuand_calibration_date_;
		hw_id_ = cal.hw_id_;
		rf_board_serial_ = cal.rf_board_serial_;
		rf_board_calibration_date_ = cal.rf_board_calibration_date_;
		nuand_adjustments_ = cal.nuand_adjustments_;
		rf_board_adjustments_ = cal.rf_board_adjustments_;
		rf_switches_ = cal.rf_switches_;
		return *this;
	}

	bool operator==(const calibration &cal) {
		return nuand_serial_ == cal.nuand_serial_ &&
			nuand_calibration_date_ == cal.nuand_calibration_date_ &&
			rf_board_serial_ == cal.rf_board_serial_ &&
			rf_board_calibration_date_ == cal.rf_board_calibration_date_ &&
			nuand_adjustments_ == cal.nuand_adjustments_ &&
			rf_board_adjustments_ == cal.rf_board_adjustments_ &&
			rf_switches_ == cal.rf_switches_;
	}

	std::string nuand_serial_;
	time_t nuand_calibration_date_;

	std::string rf_board_serial_;
	time_t rf_board_calibration_date_;

	uint32_t hw_id_;
	
	std::map<lms::lna_gain_enum, lna_adjustment> nuand_adjustments_;
	std::map<band_identifier_type, rf_path_adjustment> rf_board_adjustments_;
	std::map<bandwidth_type, std::map<frequency_type, rf_switch_setting>> rf_switches_;

	bool init(const std::vector<uint8_t> &bytes) {
		auto success = serialization_helper::init(bytes, *this, true);
		LOG_IF(LERROR, !success) << "Calibration failed verification.  It appears corrupt.";
		return success;
	}
	std::vector<uint8_t> serialize_to_bytes() const {
		return serialization_helper::serialize_to_bytes(*this, RF_PHREAKER_FLASH_PAGE_SIZE, true);
	}

private:
	double interpolate_adjustment(double position, const rf_adjustment &adj) const;

	std::vector<std::string> parse_line(std::istream &is, const std::string &filename = "unknown file");

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & nuand_serial_;
		ar & nuand_calibration_date_;
		ar & hw_id_;
		ar & rf_board_serial_;
		ar & rf_board_calibration_date_;
		ar & nuand_adjustments_;
		ar & rf_board_adjustments_;
		ar & rf_switches_;
	}
};

}}

BOOST_CLASS_VERSION(rf_phreaker::scanner::calibration, 2)
