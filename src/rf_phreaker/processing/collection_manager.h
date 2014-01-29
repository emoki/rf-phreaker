#pragma once
#include <vector>
#include <map>
#include <tuple>
#include "tbb/flow_graph.h"

#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker { namespace processing {

class collection_parameters;
typedef std::tuple<std::map<rf_phreaker::frequency_type, collection_parameters>, std::map<rf_phreaker::frequency_type, collection_parameters>> add_remove_parameters_;
typedef std::tuple<std::vector<collection_parameters>, std::vector<collection_parameters>> add_remove_parameters;

class collection_parameters
{
public:
	collection_parameters()
		: freq_(0)
		, time_ns_(0)
		, bandwidth_(0)
		, sampling_rate_(0)
	{}

	collection_parameters(rf_phreaker::frequency_type freq, int time_ms, rf_phreaker::bandwidth_type bw, rf_phreaker::frequency_type sampling_rate = 0)
		: freq_(freq)
		, time_ns_(time_ms)
		, bandwidth_(bw)
		, sampling_rate_(sampling_rate)
	{}

	bool operator==(const collection_parameters &a)
	{
		return freq_ == a.freq_ && time_ns_ == a.time_ns_ && bandwidth_ == a.bandwidth_ && sampling_rate_ == a.sampling_rate_;
	}

	rf_phreaker::frequency_type freq_;
	int time_ns_;
	rf_phreaker::bandwidth_type bandwidth_;
	rf_phreaker::frequency_type sampling_rate_;
};

class collection_parameter_manager
{
public:
	collection_parameter_manager(tbb::flow::graph &g) : g_(g), position_(0), initial_run_(true) {}

	collection_parameters operator()(add_remove_parameters_ param)
	{		
		return collection_parameters();
		//manager_.erase(std::remove_if(std::begin(manager_), std::end(manager_), [&](const collection_parameters &p) { 
		//	return std::get<1>(param).find(p.freq_) != std::get<1>(param).end(); 
		//}), std::end(manager_));

		//std::for_each(std::begin(std::get<0>(param)), std::end(std::get<0>(param)), [&](const std::pair<rf_phreaker::frequency_type, collection_parameters> &p) {
		//	manager_.push_back(p.second);
		//});

		//std::sort(std::begin(manager_), std::end(manager_), [=](const collection_parameters &a, const collection_parameters &b) {
		//	return a.freq_ < b.freq_;
		//});

		//auto it = std::find_if(std::begin(manager_), std::end(manager_), [&](const collection_parameters &a) {
		//	return current_parameters_.freq_ == a.freq_;
		//});
		//
		//if(manager_.empty())
		//	g_.root_task()->cancel_group_execution();

		//else if(it == manager_.end() || ++it == manager_.end())
		//	current_parameters_ = *manager_.begin();
		//else
		//	current_parameters_ = *it;
	
		//return current_parameters_;
	}

	collection_parameters operator()(add_remove_parameters param)
	{		
		if(!manager_.empty()) {
			// Remove entries from the beginning of the manager to our current position (current position is inclusive!) keeping track of removals.
			int remove_count = 0;
			manager_.erase(std::remove_if(std::begin(manager_), std::begin(manager_) + position_ + 1, [&](const collection_parameters &p) { 
				bool ret = (std::find(std::begin(std::get<1>(param)), std::end(std::get<1>(param)), p) != std::get<1>(param).end()); 
				if(ret) ++remove_count;
				return ret;
			}), std::begin(manager_) + position_ + 1);

			// find new current_parameters.
			position_ -= remove_count;

			// remove entries from position_ to end.
			manager_.erase(std::remove_if(std::begin(manager_) + position_, std::end(manager_), [&](const collection_parameters &p) { 
				return std::find(std::begin(std::get<1>(param)), std::end(std::get<1>(param)), p) != std::get<1>(param).end(); 
			}), std::end(manager_));
		}
		// add new entries.
		manager_.reserve(manager_.size() + std::get<0>(param).size());
		std::for_each(std::begin(std::get<0>(param)), std::end(std::get<0>(param)), [&](const collection_parameters &p) {
			manager_.push_back(p);
		});

		if(manager_.empty()) {
			reset();
			g_.root_task()->cancel_group_execution();
			return collection_parameters();
		}
		else {
			if(initial_run_)
				initial_run_ = false;
			else
				++position_;

            if(position_ >= manager_.size())
				position_ = 0;
			
			return manager_[position_];	
		}
	}

	void reset() { initial_run_ = true; position_ = 0; }

	typedef std::vector<collection_parameters> internal_manager;

	internal_manager manager_;

	tbb::flow::graph &g_;

	internal_manager::size_type position_;

	bool initial_run_;
};

}}
