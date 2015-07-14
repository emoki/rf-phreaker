#pragma once
#include <vector>
#include "boost/serialization/vector.hpp"
#include "boost/serialization/version.hpp"
#include "boost/serialization/access.hpp"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/log.h"

namespace boost { namespace serialization {
	template<class Archive>
	void serialize(Archive & ar, rf_phreaker::frequency_path &path, const unsigned int version)
	{
		ar & path.low_freq_;
		ar & path.high_freq_;
	}
}}

namespace rf_phreaker { namespace scanner {

class rf_adjustment
{
public:
	rf_adjustment() : path_(-1, -1), spacing_(-1) {}

	rf_adjustment(frequency_path path, frequency_type spacing, const std::vector<double> &adjs) 
		: path_(path)
		, spacing_(spacing)
		, rf_adjustments_(adjs) {}
	
	// This constructor provides backwards compatibility with our old measurement info which was only
	// one adjustment value.
	rf_adjustment(frequency_path path, double adj)
		: path_(path)
		, spacing_(1)
		, rf_adjustments_({adj}) {}

	rf_adjustment(const rf_adjustment &s)
		: path_(s.path_.low_freq_, s.path_.high_freq_)
		, spacing_(s.spacing_)
		, rf_adjustments_(s.rf_adjustments_) {}
	
	rf_adjustment& operator=(const rf_adjustment &s) {
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
	
	double find_adjustment(frequency_type freq) const {
		// Not initialized so there is no adjustment.
		if(path_.low_freq_ == -1 || path_.high_freq_ == -1 || spacing_ == -1)
			return 0;
		auto diff = freq - path_.low_freq_;
		if(diff < 0) {
			LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is below lower limit within calibration adjustment table.";
			return 0;
		}
		auto pos = diff / (double)spacing_;
		if(std::ceil(pos) > rf_adjustments_.size() - 1) {
			LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is above upper limit within calibration adjustment table.";
			return 0;
		}
		else
			return interpolate_adjustment(pos);
	}

	rf_adjustment create_rf_adjustment(frequency_type freq, bandwidth_type bandwidth) const {
		auto low_pos = find_low_position(freq - bandwidth / 2);
		auto high_pos = find_high_position(freq + bandwidth / 2);
		rf_adjustment adj;
		adj.path_.low_freq_ = path_.low_freq_ + low_pos * spacing_;
		adj.path_.high_freq_ = path_.low_freq_ + high_pos * spacing_;
		adj.spacing_ = spacing_;
		for(int i = low_pos; i <= high_pos; ++i)
			adj.rf_adjustments_.push_back(rf_adjustments_[i]);
		return adj;
	}
	
	frequency_path path_;

	frequency_type spacing_;

	std::vector<double> rf_adjustments_;

private:
	int find_low_position(frequency_type freq) const {
		auto low = find_high_position(freq) - 1;
		LOG_IF(LDEBUG, low < 0) << "Frequency (" << freq / 1e6 << " mhz) is below lower limit within calibration adjustment table.";
		return low < 0 ? 0 : low;
	}

	int find_high_position(frequency_type freq) const {
		auto diff = freq - path_.low_freq_;
		if(diff < 0) {
			LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is below lower limit within calibration adjustment table.";
			return 0;
		}
		auto pos = std::ceil(diff / (double)spacing_);
		if(std::ceil(pos) > rf_adjustments_.size() - 1) {
			LOG(LDEBUG) << "Frequency (" << freq / 1e6 << " mhz) is above upper limit within calibration adjustment table.";
			return rf_adjustments_.size() - 1;
		}
		return (int)pos;
	}

	double interpolate_adjustment(double position) const {
		size_t before = (size_t)std::floor(position);
		size_t after = (size_t)std::ceil(position);
		if(after > rf_adjustments_.size()) {
			LOG(LDEBUG) << "Unable to interpolate because the position is beyond the bounds of the adjustment table.";
			return 0;
		}
		auto ratio = position - before;
		auto interpolation = rf_adjustments_[before] + (rf_adjustments_[after] - rf_adjustments_[before]) * ratio;
		return interpolation;
	}

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & path_;
		ar & spacing_;
		ar & rf_adjustments_;
	}
};

}}