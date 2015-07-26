#pragma once
#include <tuple>
#include <future>
#include <vector>
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/processing/layer_3_tracker.h"

namespace rf_phreaker { namespace processing {

class processing_and_feedback_helper {
public:
	processing_and_feedback_helper() : current_collection_round_(-1) {}

	processing_and_feedback_helper(const processing_and_feedback_helper &helper) 
		: current_collection_round_(helper.current_collection_round_) 
		, sweep_freq_history_(helper.sweep_freq_history_) {}

	bool has_sweep_restarted(const scanner::measurement_info &meas) {
		if(sweep_freq_history_.insert(meas.frequency()).second) 
			return false;
		else {
			sweep_freq_history_.clear();
			return true;
		}
	}

	bool has_layer_3_restarted(const scanner::measurement_info &meas) {
		bool has_restarted = false;
		if(meas.collection_round() == 0 && current_collection_round_ != 0) {
			has_restarted = true;
		}
		current_collection_round_ = meas.collection_round();
		return has_restarted;
	}

	void remove_futures() {
		int num_completed = 0;
		for(auto &fut : past_output_) {
			if(fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
				++num_completed;
			else
				break;
		}
		past_output_.erase(std::begin(past_output_), std::begin(past_output_) + num_completed);
	}

	void track_future(std::future<void> &&t) {
		past_output_.push_back(std::move(t));
	}

	template<typename Layer_3, typename Data>
	void update_tracker_if_necessary(layer_3_tracker<Layer_3> &tracker, frequency_type freq, std::vector<Data> &group, double threshold) const {
		if(!tracker.is_freq_in_history(freq)) {
			Data data;
			for(auto &tmp : group) {
				if(is_greater(tmp, data))
					data = tmp;
			}
			if(is_greater(data, threshold))
				tracker.update(freq, data);
		}
	}

private:
	template<typename Data> bool is_greater(const Data &a, const Data &b) const;
	template<typename Data> bool is_greater(const Data &a, double b) const;

	std::vector<std::future<void>> past_output_;
	std::set<frequency_type> sweep_freq_history_;
	int64_t current_collection_round_;
};

template<>
inline bool processing_and_feedback_helper::is_greater(const gsm_measurement &a, const gsm_measurement &b) const {
	return a.norm_sync_corr_ > b.norm_sync_corr_;
}

template<>
inline bool processing_and_feedback_helper::is_greater(const umts_measurement &a, const umts_measurement &b) const {
	return a.ecio_ > b.ecio_;
}

template<>
inline bool processing_and_feedback_helper::is_greater(const lte_measurement &a, const lte_measurement &b) const {
	return a.sync_quality > b.sync_quality;
}

template<>
inline bool processing_and_feedback_helper::is_greater(const gsm_measurement &a, double b) const {
	return a.norm_sync_corr_ > b;
}

template<>
inline bool processing_and_feedback_helper::is_greater(const umts_measurement &a, double b) const {
	return a.ecio_ > b;
}

template<>
inline bool processing_and_feedback_helper::is_greater(const lte_measurement &a, double b) const {
	return a.sync_quality > b;
}


}}