#pragma once
#include <map>
#include <fstream>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker {

class gps_stats;
class meas_stats;

std::ofstream& operator<<(std::ofstream &f, const rf_phreaker::gps_stats &s);
std::ofstream& operator<<(std::ofstream &f, const rf_phreaker::meas_stats &s);

class gps_stats {
public:
	using key = uint64_t;
	key get_key() const {
		return (uint64_t)(sats_visible_) << 32 | (uint64_t)sats_tracking_;
	}
	void update(const gps_stats &s) {
		if(sats_tracking_ != s.sats_tracking_ || sats_visible_ != s.sats_visible_)
			throw rf_phreaker_error("Updating gps_stats with wrong key");
		if(current_second_ != s.current_second_) {
			current_second_ = s.current_second_;
			seconds_seen_ += s.seconds_seen_;
		}
	}
	static void output_header(std::ofstream &f) {
		f << "sats_tracking\tsats_visible\ttotal_,mins_seen)\n";
	}
	int64_t current_second_;
	int seconds_seen_;
	int sats_visible_;
	int sats_tracking_;
};

class meas_stats {
public:
	using key = uint64_t;
	key get_key() const {
		auto t = (freq_) << 28 | (identifier_ & 0xFFFF);
		return t;
	}
	void update(const meas_stats &s) {
		if(freq_ != s.freq_ || identifier_ != s.identifier_)
			throw rf_phreaker_error("Updating meas_stats with wrong key.");
		count_ += s.count_;
		total_sl_watts_ += total_sl_watts_;
		if(max_sl_ < s.max_sl_) max_sl_ = s.max_sl_;
		if(min_sl_ > s.min_sl_) min_sl_ = s.min_sl_;
		total_interference_watts_ += s.total_interference_watts_;
		if(max_interference_ < s.max_interference_) max_interference_ = s.max_interference_;
		if(min_interference_ > s.min_interference_) min_interference_ = s.min_interference_;
		if(s.decoded_layer_3_) decoded_layer_3_ = true;
	}
	static void output_header(std::ofstream &f) {
		//f << "freq\tbsic\\cpich\\pcid\tmax_sl\tmax_interference\tmin_sl\tmin_interference\tavg_sl\tavg_interference\tdecoded_layer_3\n";
		f << "freq\tbsic\\cpich\\pcid\tmax_sl\tmax_interference\tmin_sl\tmin_interference\n";
	}
	frequency_type freq_;
	int32_t identifier_;
	int64_t count_;
	double total_sl_watts_;
	double max_sl_;
	double min_sl_;
	double total_interference_watts_;
	double max_interference_;
	double min_interference_;
	bool decoded_layer_3_;
};

inline std::ofstream& operator<<(std::ofstream &f, const gps_stats &s) {
	f << s.sats_tracking_ << "\t"
		<< s.sats_visible_ << "\t"
		<< s.seconds_seen_ / 60;
	return f;
}

inline std::ofstream& operator<<(std::ofstream &f, const meas_stats &s) {
	f << s.freq_ / 1e6 << "\t"
		<< s.identifier_ << "\t"
		<< s.max_sl_ << "\t"
		<< s.max_interference_ << "\t"
		<< s.min_sl_ << "\t"
		<< s.min_interference_; 
		// Summing the doubles introduces too much error.
		/*<< "\t"
		<< 10 * log10(s.total_sl_watts_ / s.count_) << "\t"
		<< 10 * log10(s.total_interference_watts_ / s.count_);
		<< s.decoded_layer_3_ ? "TRUE" : "FALSE";*/
	return f;
}

template<typename Stats>
class stats_tracker {
public:
	stats_tracker() {}
	
	template<typename Data>
	void add(const Data &data) {
		auto stats = Stats(data);
		auto i = stats_.insert(std::make_pair(stats.get_key(), stats));
		if(i.second == false) {
			i.first->second.update(data);
		}
	}

	std::vector<typename Stats> get_stats() const {
		std::vector<Stats> t;
		for(auto &i : stats_)
			t.push_back(i.second);
		return t;
	}

	using stats_map = std::map<typename Stats::key, Stats>;
	stats_map stats_;
};
	
}