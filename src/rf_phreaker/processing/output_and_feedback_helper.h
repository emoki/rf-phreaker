#pragma once
#include <tuple>
#include <future>
#include <vector>

namespace rf_phreaker { namespace processing {

template<typename T>
class output_and_feedback_helper {
public:
	output_and_feedback_helper() : current_collection_round_(-1) {}

	bool has_sweep_restarted(const measurement_package& meas) {
		if(sweep_freq_history_.insert(meas->frequency()).second) 
			return false;
		else {
			sweep_freq_history_.clear();
			return true;
		}
	}

	bool has_layer_3_restarted(const measurement_package& meas) {
		bool has_restarted = false;
		if(meas->collection_round() == 0 && current_collection_round_ != 0) {
			has_restarted = true;
		}
		current_collection_round_ = meas->collection_round();
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

	void track_future(std::future<T> &&t) {
		past_output_.push_back(std::move(t));
	}

private:
	std::vector<std::future<T>> past_output_;
	std::set<frequency_type> sweep_freq_history_;
	int64_t current_collection_round_;
};

}}