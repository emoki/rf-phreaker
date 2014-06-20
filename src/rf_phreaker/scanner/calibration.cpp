#include <fstream>
#include <regex>
#include "boost/math/special_functions.hpp"
#include "rf_phreaker/scanner/calibration.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker { namespace scanner {

void calibration::clear()
{
	nuand_serial_.clear();
	nuand_calibration_date_ = 0;
	nuand_freq_correction_value_ = 0;
	nuand_freq_correction_date_ = 0;
	rf_board_serial_.clear();
	rf_board_calibration_date_ = 0;
	nuand_adjustment_.clear();
	rf_board_adjustments_.clear();
	rf_switches_.clear();
}

rf_switch_setting calibration::get_rf_switch(frequency_type freq) const
{
	auto it = rf_switches_.lower_bound(freq);
	if(it == rf_switches_.end())
		return rf_switch_setting();
	else
		return it->second;

}

double calibration::get_rf_board_adjustment(frequency_type freq) const 
{
	auto it = rf_switches_.lower_bound(freq);
	if(it == rf_switches_.end() || it->second.identifier_ == 0)
		return 0;
	else {
		auto adj_it = rf_board_adjustments_.find(it->second.identifier_);
		if(adj_it != rf_board_adjustments_.end()) {
			auto diff = freq - adj_it->second.adj_.path_.low_freq_;
			if(diff < 0)
				return 0;
			auto pos = (size_t)(boost::math::round(diff / (double)adj_it->second.adj_.spacing_));
			if(pos > adj_it->second.adj_.rf_adjustments_.size())
				return 0;
			else
				return adj_it->second.adj_.rf_adjustments_[pos];
		}
		else
			return 0;
	}
}

double calibration::get_nuand_adjustment(frequency_type freq) const
{
	auto diff = freq - nuand_adjustment_.path_.low_freq_;
	if(diff < 0)
		return 0;
	auto pos = (size_t)boost::math::round(diff / (double)nuand_adjustment_.spacing_);
	if(pos > (int)nuand_adjustment_.rf_adjustments_.size())
		return 0;
	else
		return nuand_adjustment_.rf_adjustments_[pos];
}

void calibration::read_rf_switch_file(const std::string &filename)
{
	rf_switches_.clear();

	const std::string desc("RF Switch Settings");
	std::ifstream f(filename);
	auto header_group = parse_line(f, desc);
	if(header_group.empty() || header_group[0] != rf_switch_header)
		throw rf_phreaker_error(desc + " header does not match.");

	header_group = parse_line(f, desc);
	if(header_group.empty())
		throw rf_phreaker_error("Wrong " + desc + " format.  2nd line should be \"version\".");
	
	do {
		auto line = parse_line(f, desc);
		if(line.size()) {
			auto sw = parse_rf_switch_setting(line.begin(), line.end());
			rf_switches_.insert(std::make_pair(sw.path_.high_freq_, sw));
		}
	} while(!f.eof());
}

void calibration::read_rf_board_calibration_file(const std::string &filename)
{
	rf_board_adjustments_.clear();
	rf_board_serial_.clear();
	rf_board_calibration_date_ = 0;

	const std::string desc("RF Board Calibration");
	std::ifstream f(filename);
	auto header_group = parse_line(f, desc);
	if(header_group.empty() || header_group[0] != rf_board_calibration_header)
		throw rf_phreaker_error(desc + " header does not match.");

	header_group = parse_line(f, desc);
	if(header_group.empty())
		throw rf_phreaker_error("Wrong " + desc + " format.  2nd line should be \"version, rf_board_serial, seconds_since_1970_jan_1\".");
	
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
	} while(!f.eof());
}

void calibration::read_nuand_calibration_file(const std::string &filename)
{
	nuand_adjustment_.clear();
	nuand_serial_.clear();
	nuand_calibration_date_ = 0;

	const std::string desc("Nuand RF Calibration");
	std::ifstream f(filename);
	auto header_group = parse_line(f, desc);
	if(header_group.empty() || header_group[0] != nuand_calibration_header)
		throw rf_phreaker_error(desc + " header does not match.");

	header_group = parse_line(f, desc);
	if(header_group.empty())
		throw rf_phreaker_error("Wrong " + desc + " format.  2nd line should be \"version, nuand_serial, seconds_since_1970_jan_1\".");

	int version = std::stoi(header_group[0]);
	if(version >= 1) {
		nuand_serial_ = trim_whitespace(header_group[1]);
		nuand_calibration_date_ = std::stoll(header_group[2]);
	}

	do {
		auto line = parse_line(f, desc);
		if(line.size()) {
			nuand_adjustment_ = parse_rf_adjustment(line.begin(), line.end());
		}
	} while(!f.eof());
}

std::vector<std::string> calibration::parse_line(std::istream &is, const std::string &filename)
{
	std::string line;
	std::getline(is, line);
	if(is.fail() && !is.eof())
		throw rf_phreaker_error("Error reading " + filename + ".");

	return tokenize(line, std::regex(","));
}

rf_path_adjustment calibration::parse_rf_path_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end)
{
	auto it = begin;
	rf_path_adjustment adj;
	adj.identifier_ = std::stoi(*it++); ;
	adj.adj_ = parse_rf_adjustment(it, end);
	return adj;
}

rf_adjustment calibration::parse_rf_adjustment(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end)
{
	auto it = begin;
	rf_adjustment adj;
	adj.path_.low_freq_ = std::stoll(*it++) * mhz(1); 
	adj.path_.high_freq_ = std::stoll(*it++) * mhz(1);
	adj.spacing_ = std::stoll(*it++) * mhz(1);

	auto count = (adj.path_.high_freq_ - adj.path_.low_freq_) / adj.spacing_ + 1;
	for(int i = 0; i < count; ++i) {
		if(it == end)
			throw rf_phreaker_error("Error parsing rf adjustment.");
		adj.rf_adjustments_.push_back(std::stod(*it++));
	}

	return adj;
}

rf_switch_setting calibration::parse_rf_switch_setting(const std::vector<std::string>::iterator &begin, const std::vector<std::string>::iterator &end)
{
	auto it = begin;
	rf_switch_setting sw;
	sw.path_.low_freq_ = std::stoll(*it++) * mhz(1);
	sw.path_.high_freq_ = std::stoll(*it++) * mhz(1);
	sw.identifier_ = std::stoi(*it++);
	sw.switch_setting_ = std::stoul(*it++, 0, 16);
	sw.switch_mask_ = std::stoul(*it++, 0, 16);
	return sw;
}


}}