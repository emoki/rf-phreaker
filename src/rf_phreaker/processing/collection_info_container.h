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
	add_remove_collection_info() {};
	add_remove_collection_info(const add_remove_collection_info &info) : add_(info.add_), remove_(info.remove_) {};
	collection_info_group_type add_;
	collection_info_group_type remove_;
};

class add_collection_info : public add_remove_collection_info
{
public:
	add_collection_info() {}
	add_collection_info(collection_info info)
	{
		add_.push_back(std::move(info));
	}
};

class remove_collection_info : public add_remove_collection_info
{
public:
	remove_collection_info() {}
	remove_collection_info(collection_info info)
	{
		remove_.push_back(std::move(info));
	}
};


class collection_info_container
{
public:
	collection_info_container(specifiers specs = {}, bool is_streaming = false, bool finish_after_iteration = false)
		: position_(0)
		, include_first_position_(true)
		, finished_(false)
		, collection_round_(0)
		, finish_after_iteration_(finish_after_iteration)
		, specs_(specs)
		, is_streaming_(is_streaming) {}

	// Does not support adding/removing parameters that have multiple specs.
	void adjust(const add_remove_collection_info &param) {
		if(!collection_info_group_.empty() && param.remove_.size() && specs_.does_overlap(param.remove_[0].specs_)) {
			// Remove entries from the beginning of the manager to our current position (current position is inclusive!) keeping track of removals.
			uint32_t remove_count = 0;
			collection_info_group_.erase(std::remove_if(std::begin(collection_info_group_), std::begin(collection_info_group_) + position_ + 1, [&](collection_info &p) {
				auto i = std::find_if(std::begin(param.remove_), std::end(param.remove_), [&](const collection_info &a) {
					return p.partial_equal_specs_overlap(a);
				});
				if(i != param.remove_.end()) {
					// If this is the last spec we have to remove the item.  Otherwise only remove that spec.
					if(p.specs_.size() == 1) {
						++remove_count;
						return true;
					}
					else {
						p.specs_.remove_spec(i->specs_.front());
					}
				}
				return false;
			}), std::begin(collection_info_group_) + position_ + 1);

			// find new current_parameters.
			if(remove_count > position_) {
				include_first_position_ = true;
				position_ = 0;
			}
			else
				position_ -= remove_count;

			// remove entries from position_ to end.
			collection_info_group_.erase(std::remove_if(std::begin(collection_info_group_) + position_, std::end(collection_info_group_), [&](collection_info &p) {
				auto i = std::find_if(std::begin(param.remove_), std::end(param.remove_), [&](const collection_info &a) {
					return p.partial_equal_specs_overlap(a);
				});
				if(i != param.remove_.end())
					if(p.specs_.size() == 1)
						return true;
					else {
						p.operating_bands_.remove_band(i->operating_bands_.get_first_band());
						p.specs_.remove_spec(i->specs_.front());
					}
				return false;
			}), std::end(collection_info_group_));
		}

		// add new entries.
		if(param.add_.size() && specs_.does_overlap(param.add_[0].specs_)) {
			// If we add freqs then restart collection by saying we're not finished.
			finished_ = false;

			//collection_info_group_.reserve(collection_info_group_.size() + param.add_.size());
			std::for_each(std::begin(param.add_), std::end(param.add_), [&](const collection_info &p) {
				auto i = std::find_if(std::begin(collection_info_group_), std::end(collection_info_group_), [&](const collection_info &a) {
					return p.partial_equal(a);
				});
				if(i == collection_info_group_.end())
					collection_info_group_.push_back(p);
				else {
					i->operating_bands_.add_band(p.operating_bands_.get_first_band());
					i->specs_.add_spec(p.specs_.front());
				}
			});
		}
	}

	collection_info try_get_auto_info() {
		if(is_streaming_)
			return try_get_current_info_determine_collection_round();
		else
			return try_get_next_info();
	}

	bool get_auto_info(collection_info &p) {
		if(is_streaming_)
			return current_info_determine_collection_round(p);
		else
			return get_next_info(p);
	}

	bool current_info(collection_info &p) {
		if(finished_ || collection_info_group_.empty())
			return false;
		p = collection_info_group_[position_];
		return true;
	}

	collection_info try_get_current_info() {
		collection_info info;
		current_info(info);
		return info;
	}

	bool current_info_determine_collection_round(collection_info &p) {
		if(finished_ || collection_info_group_.empty()) {
			position_ = 0;
			include_first_position_ = true;
			finished_ = true;
			return false;
		}
		if(include_first_position_) {
			include_first_position_ = false;
			collection_round_ = 0;
		}
		else {
			++collection_round_;
		}
		p = *collection_info_group_.begin();
		return true;
	}

	collection_info try_get_current_info_determine_collection_round() {
		collection_info info;
		current_info_determine_collection_round(info);
		return info;
	}

	bool get_next_info(collection_info &p) {
		increment();
		if(finished_)
			return false;
		p = collection_info_group_[position_];
		return true;
	}

	collection_info try_get_next_info() {
		collection_info info;
		get_next_info(info);
		return info;
	}

	void increment() {
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

	bool is_empty() const { return collection_info_group_.empty(); }

	int64_t collection_round() const { return collection_round_; }

	bool is_finished() const { return finished_; }

	void reset() {
		collection_round_ = 0;
		include_first_position_ = true;
		position_ = 0;
		finished_ = false;
	}

	bool has_specifier(specifier spec) const {
		return specs_.has_spec(spec);
	}

	void add_specifier(specifier spec) {
		specs_.add_spec(spec);
	}

	void remove_specifier(specifier spec) {
		specs_.remove_spec(spec);
	}

	collection_info_group_type collection_info_group_;

	collection_info_group_type::size_type position_;

	bool include_first_position_;

	bool finished_;

	int64_t collection_round_;

	bool finish_after_iteration_;

	specifiers specs_;

	bool is_streaming_;
};


}}