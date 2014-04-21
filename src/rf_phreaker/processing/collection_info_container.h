#pragma once

#include "rf_phreaker/processing/collection_info.h"
#include "rf_phreaker/common/common_types.h"
#include <algorithm>
#include <vector>

namespace rf_phreaker { namespace processing {

class collection_info_container;
typedef std::vector<collection_info_container> collection_info_containers;

class add_remove_collection_info
{
public:
	add_remove_collection_info() : tech_(UNKOWN_SPECIFIER) {};
	add_remove_collection_info(const add_remove_collection_info &info) : add_(info.add_), remove_(info.remove_), tech_(info.tech_) {};
	collection_info_group_type add_;
	collection_info_group_type remove_;
	specifier tech_;
};

class add_collection_info : public add_remove_collection_info
{
public:
	add_collection_info(collection_info info, specifier tech = UNKOWN_SPECIFIER)
	{
		add_.push_back(std::move(info));
		tech_ = tech;
	}
};

class remove_collection_info : public add_remove_collection_info
{
public:
	remove_collection_info(collection_info info, specifier tech = UNKOWN_SPECIFIER)
	{
		remove_.push_back(std::move(info));
		tech_ = tech;
	}
};


class collection_info_container
{
public:
	class collection_info_container(specifier tech = UNKOWN_SPECIFIER, bool finish_after_iteration = false)
		: position_(0)
		, include_first_position_(true)
		, finished_(false)
		, collection_round_(0)
		, tech_(tech)
		, finish_after_iteration_(finish_after_iteration) 
	{}

	void adjust(add_remove_collection_info param)
	{
		if(!collection_info_group_.empty() && param.remove_.size()) {
			// Remove entries from the beginning of the manager to our current position (current position is inclusive!) keeping track of removals.
			uint32_t remove_count = 0;
			collection_info_group_.erase(std::remove_if(std::begin(collection_info_group_), std::begin(collection_info_group_) + position_ + 1, [&](const collection_info &p) {
				bool ret = (std::find(std::begin(param.remove_), std::end(param.remove_), p) != param.remove_.end());
				if(ret) ++remove_count;
				return ret;
			}), std::begin(collection_info_group_) + position_ + 1);

			// find new current_parameters.
			if(remove_count > position_) {
				include_first_position_ = true;
				position_ = 0;
			}
			else
				position_ -= remove_count;

			// remove entries from position_ to end.
			collection_info_group_.erase(std::remove_if(std::begin(collection_info_group_) + position_, std::end(collection_info_group_), [&](const collection_info &p) {
				return std::find(std::begin(param.remove_), std::end(param.remove_), p) != param.remove_.end();
			}), std::end(collection_info_group_));
		}

		// add new entries.
		if(param.add_.size()) {
			// If we add freqs then restart collection by saying we're not finished.
			finished_ = false;


			collection_info_group_.reserve(collection_info_group_.size() + param.add_.size());
			std::for_each(std::begin(param.add_), std::end(param.add_), [&](const collection_info &p) {
				if(std::find(std::begin(collection_info_group_), std::end(collection_info_group_), p) == collection_info_group_.end())
					collection_info_group_.push_back(p);
			});
		}

	}

	bool current_info(collection_info &p)
	{
		if(finished_ || collection_info_group_.empty())
			return false;
		p = collection_info_group_[position_];
		return true;
	}

	collection_info try_get_current_info()
	{
		collection_info info;
		current_info(info);
		return info;
	}

	bool get_next_info(collection_info &p)
	{
		increment();
		if(finished_)
			return false;
		p = collection_info_group_[position_];
		return true;
	}

	collection_info try_get_next_info()
	{
		collection_info info;
		get_next_info(info);
		return info;
	}

	void increment()
	{
		if(collection_info_group_.empty()) {
			position_ = 0;
			include_first_position_ = true;
			finished_ = true;
			}
			else {
			if(include_first_position_)
				include_first_position_ = false;
			else
				++position_;

			if(position_ >= collection_info_group_.size()) {
				position_ = 0;
				++collection_round_;

				if(finish_after_iteration_)
					finished_ = true;
			}
		}
	}

	bool is_empty() { return collection_info_group_.empty(); }

	int64_t collection_round() { return collection_round_; }

	specifier get_technology() { return tech_; }

	void set_technology(specifier tech) { tech_ = tech; }

	bool is_finished() { return finished_; }

	void reset() 
	{ 
		collection_round_ = 0;
		include_first_position_ = true; 
		position_ = 0; 
		finished_ = false; 
	}

	collection_info_group_type collection_info_group_;

	collection_info_group_type::size_type position_;

	bool include_first_position_;

	bool finished_;

	int64_t collection_round_;

	specifier tech_;

	bool finish_after_iteration_;
};


}}