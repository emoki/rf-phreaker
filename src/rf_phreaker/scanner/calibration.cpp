#include <fstream>
#include <regex>
#include "boost/math/special_functions.hpp"
#include "rf_phreaker/scanner/calibration.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker { namespace scanner {

void calibration::clear() {
	nuand_serial_.clear();
	nuand_calibration_date_ = 0;
	hw_id_ = 0;
	rf_board_serial_.clear();
	rf_board_calibration_date_ = 0;
	nuand_adjustments_.clear();
	rf_board_adjustments_.clear();
	rf_switches_.clear();
}

rf_switch_setting calibration::get_rf_switch(frequency_type freq, bandwidth_type bw) const {
	auto it = rf_switches_.lower_bound(bw);
	if(it == rf_switches_.end()) {
		LOG(LDEBUG) << "Bandwidth (" << bw / 1e6 << " mhz) or higher not found within RF switch settings.  Using default switch setting.";
		return rf_switch_setting();
	}
	else {
		auto freq_it = it->second.lower_bound(freq);
		if(freq_it == it->second.end()) {
			LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) not found within RF switch settings.  Using default switch setting.";
			return rf_switch_setting();
		}
		else {
			return freq_it->second;
		}
	}
}

double calibration::get_rf_board_adjustment(frequency_type freq, bandwidth_type bw) const {
	auto sw = get_rf_switch(freq, bw);
	if(sw.identifier_ == 0) {
		LOG(LDEBUG) << "RF switch setting's identifer is zero.";
		return 0;
	}
	else {
		auto adj_it = rf_board_adjustments_.find(sw.identifier_);
		if(adj_it != rf_board_adjustments_.end()) {
			auto diff = freq - adj_it->second.adj_.path_.low_freq_;
			if(diff < 0) {
				LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is below lower limit within RF board calibration table.";
				return 0;
			}
			auto pos = (size_t)(boost::math::round(diff / (double)adj_it->second.adj_.spacing_));
			if(pos > adj_it->second.adj_.rf_adjustments_.size()) {
				LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is above upper limit within RF board calibration table.";
				return 0;
			}
			else
				return adj_it->second.adj_.rf_adjustments_[pos];
		}
		else
			return 0;
	}
}

double calibration::get_nuand_adjustment(lms::lna_gain_enum gain, frequency_type freq) const {
	auto it = nuand_adjustments_.find(gain);
	if(it == nuand_adjustments_.end()) {
		LOG(LDEBUG) << "LNA gain adjustment (" << lms::to_string(gain) << ") not found within adjustment table.";
		return 0;
	}
	auto adj = it->second.adj_;
	auto diff = freq - adj.path_.low_freq_;
	if(diff < 0) {
		LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is below lower limit within LNA gain adjustment table.";
		return 0;
	}
	auto pos = (size_t)boost::math::round(diff / (double)adj.spacing_);
	if(pos > (int)adj.rf_adjustments_.size()) {
		LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is above upper limit within LNA gain adjustment table.";
		return 0;
	}
	else
		return adj.rf_adjustments_[pos];
}

void calibration::read_rf_switch_file(const std::string &filename) {
	rf_switches_.clear();

	const std::string desc("RF Switch Settings");
	std::ifstream f(filename);
	auto header_group = parse_line(f, desc);
	if(header_group.empty() || header_group[0] != rf_switch_header)
		throw rf_phreaker_error(desc + " header does not match.", CALIBRATION_ERROR);

	header_group = parse_line(f, desc);
	if(header_group.empty())
		throw rf_phreaker_error("Wrong " + desc + " format.  2nd line should be \"version\".", CALIBRATION_ERROR);

	int version = std::stoi(header_group[0]);
	if(version != 2) {
		throw rf_phreaker_error("Wrong " + desc + " version.  Only version 2 is currently supported.", CALIBRATION_ERROR);
	}

	do {
		auto line = parse_line(f, desc);
		if(line.size()) {
			auto sw = parse_rf_switch_setting(line.begin(), line.end());
			auto bw_map = rf_switches_.find(sw.bandwidth_);
			if(bw_map == rf_switches_.end())
				bw_map = rf_switches_.insert(std::make_pair(sw.bandwidth_, std::map<frequency_type, rf_switch_setting>())).first;
			bw_map->second.insert(std::make_pair(sw.path_.high_freq_, sw));
		}
	}
	while(!f.eof());
}

void calibration::read_rf_board_calibration_file(const std::string &filename) {
	rf_board_adjustments_.clear();
	rf_board_serial_.clear();
	rf_board_calibration_date_ = 0;

	const std::string desc("RF Board Calibration");
	std::ifstream f(filename);
	auto header_group = parse_line(f, desc);
	if(header_group.empty() || header_group[0] != rf_board_calibration_header)
		throw rf_phreaker_error(desc + " header does not match.", CALIBRATION_ERROR);

	header_group = parse_line(f, desc);
	if(header_group.empty())
		throw rf_phreaker_error("Wrong " + desc + " format.  2nd line should be \"version, rf_board_serial, seconds_since_1970_jan_1\".", CALIBRATION_ERROR);

	int version = std::stoi(header_group[0]);
	if(version >= 1) {
		rf_board_serial_ = trim_whitespace(header_group[1]);
		rf_board_calibration_date_ = std::stoll(header_group[2]);
	}

	do {
		auto line = parse_line(f, desc);
		if(line.size()) {
			auto adj = parse_rf_path_adjustment(line.begin(), line.end());
			rf_board_adjustments_.insert(std::make_pair(adj.identifier_, adj));
		}
	}
	while(!f.eof());
}

void calibration::read_nuand_calibration_file(const std::string &filename) {
	nuand_adjustments_.clear();
	nuand_serial_.clear();
	nuand_calibration_date_ = 0;

	const std::string desc("Nuand RF Calibration");
	std::ifstream f(filename);
	auto header_group = parse_line(f, desc);
	if(header_group.empty() || header_group[0] != nuand_calibration_header)
		throw rf_phreaker_error(desc + " header does not match.", CALIBRATION_ERROR);

	header_group = parse_line(f, desc);
	if(header_group.empty())
		throw rf_phreaker_error("Wrong " + desc + " format.  2nd line should be \"version, nuand_serial, seconds_since_1970_jan_1\".", CALIBRATION_ERROR);

	int version = std::stoi(header_group[0]);
	if(version >= 1) {
		nuand_serial_ = trim_whitespace(header_group[1]);
		nuand_calibration_date_ = std::stoll(header_group[2]);
	}

	if(version == 1) {
		do {
			auto line = parse_line(f, desc);
			if(line.size()) {
				auto adj = parse_rf_adjustment(line.begin(), line.end());
				lna_adjustment lna_adj;
				lna_adj.adj_ = adj;
				lna_adj.lna_gain_ = lms::LNA_MAX;
				nuand_adjustments_.insert(std::make_pair(lms::LNA_MAX, lna_adj));
			}
		}
		while(!f.eof());
	}
	else if(version >= 2) {
		do {
			auto line = parse_line(f, desc);
			if(line.size()) {
				auto lna_adj = parse_lna_adjustment(line.begin(), line.end());
				nuand_adjustments_.insert(std::make_pair(lna_adj.lna_gain_, lna_adj));
			}
		}
		while(!f.eof());
	}
	else
		throw rf_phreaker_error("Unknown version within Nuand calibration file.");
}

std::vector<std::string> calibration::parse_line(std::istream &is, const std::string &filename) {
	std::string line;
	std::getline(is, line);
	if(is.fail() && !is.eof())
		throw rf_phreaker_error("Error reading " + filename + ".", CALIBRATION_ERROR);

	return tokenize(line, std::regex(","));
}

rf_path_adjustment calibration::parse_rf_path_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end) {
	auto it = begin;
	rf_path_adjustment adj;
	adj.identifier_ = std::stoi(*it++);;
	adj.adj_ = parse_rf_adjustment(it, end);
	return adj;
}

lna_adjustment calibration::parse_lna_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end) {
	auto it = begin;
	lna_adjustment adj;
	adj.lna_gain_ = lms::to_lna_gain(std::stoi(*it++));;
	adj.adj_ = parse_rf_adjustment(it, end);
	return adj;
}

rf_adjustment calibration::parse_rf_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end) {
	auto it = begin;
	rf_adjustment adj;
	adj.path_.low_freq_ = std::stoll(*it++) * mhz(1);
	adj.path_.high_freq_ = std::stoll(*it++) * mhz(1);
	adj.spacing_ = std::stoll(*it++) * mhz(1);

	auto count = (adj.path_.high_freq_ - adj.path_.low_freq_) / adj.spacing_ + 1;
	for(int i = 0; i < count; ++i) {
		if(it == end)
			throw rf_phreaker_error("Error parsing rf adjustment.", CALIBRATION_ERROR);
		adj.rf_adjustments_.push_back(std::stod(*it++));
	}

	return adj;
}

rf_switch_setting calibration::parse_rf_switch_setting(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end) {
	auto it = begin;
	rf_switch_setting sw;
	sw.bandwidth_ = std::stol(*it++) * 1000000;
	sw.path_.low_freq_ = std::stoll(*it++) * mhz(1);
	sw.path_.high_freq_ = std::stoll(*it++) * mhz(1);
	sw.identifier_ = std::stoi(*it++);
	sw.switch_setting_ = std::stoul(*it++, 0, 16);
	sw.switch_mask_ = std::stoul(*it++, 0, 16);
	return sw;
}


}}