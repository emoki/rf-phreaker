#pragma once

#include <algorithm>
#include <vector>
#include <list>
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/settings.h"

namespace rf_phreaker { namespace processing {

class collection_scheduler {
public:
collection_scheduler(const collection_scheduler &a) 
	: details_group_(a.details_group_)
	, ordered_containers_(a.ordered_containers_)
	, ordered_containers_it_(a.ordered_containers_it_)
	, settings_(a.settings_)
	, include_first_position_(a.include_first_position_)
	, is_done_(a.is_done_)
	, has_multiple_scans_(a.has_multiple_scans_)
	, first_iteration_(a.first_iteration_) {}

collection_scheduler(collection_info_containers *containers, const settings *s_settings, bool has_multiple_scans_ = true)
	: settings_(s_settings)
	, include_first_position_(true)
	, is_done_(false)
	, has_multiple_scans_(has_multiple_scans_)
	, first_iteration_(true) {
	create_schedule(containers);
}

void create_schedule(collection_info_containers *containers) {
	first_iteration_ = true;
	switch(settings_->scheduling_algorithm_) {
	case tech_based:
		for(auto &i : *containers)
			details_group_.emplace_back(container_details(&i, 1));
		create_tech_based_order();
		break;
	case collection_round_based:
	case packet_based:
		for(auto &i : *containers)
			details_group_.emplace_back(container_details(&i, calculate_priority(i)));
		create_packet_or_collection_round_based_order();
		break;
	case sweep_first_collection_round_based:
	case sweep_first_packet_based:
		for(auto &i : *containers) 
			details_group_.emplace_back(container_details(&i, calculate_priority(i)));
		create_sweep_first_order();
		break;
	default:
		throw rf_phreaker_error("Unknown scheduling algorithm.");
	}
}

void reset() {
	ordered_containers_it_ = ordered_containers_.begin();
	include_first_position_ = true;
	first_iteration_ = true;
	is_done_ = false;
	for(auto &c : details_group_)
		c.container_->reset();
}

bool update() {
	bool needs_update = false;
	// We only update if we've reached the beginning of the containers.
	// This simplifies handling the ordered_container_iterator (we just set it to the beginning after modifying the order.
	// Do not update if we are prioritizing sweep and it's still the first iteration.
	if(ordered_containers_it_ == ordered_containers_.begin() && 
		!(first_iteration_ && (settings_->scheduling_algorithm_ == sweep_first_collection_round_based
			|| settings_->scheduling_algorithm_ == sweep_first_packet_based))) {
		for(auto &c : details_group_) {
			if(c.container_->collection_info_group_.size() != c.current_collection_round_size_) {
				needs_update = true;
				break;
			}
		}
		if(needs_update) {
			for(auto &c : details_group_) {
				c.current_collection_round_size_ = c.container_->collection_info_group_.size();
				c.priority_ = calculate_priority(*c.container_);
			}
			if(settings_->scheduling_algorithm_ == tech_based)
				create_tech_based_order();
			else // handle all other type of algorithms (after the first iteration they are all the same)
				create_packet_or_collection_round_based_order();
		}
	}
	return needs_update;
}

void create_tech_based_order() {
	ordered_containers_.clear();
	for(auto &i : details_group_) {
		ordered_containers_.push_back(i.container_);
	}
	ordered_containers_it_ = ordered_containers_.begin();
	include_first_position_ = true;
}

void create_packet_or_collection_round_based_order() {
	ordered_containers_.clear();
	std::sort(details_group_.begin(), details_group_.end());

	if(details_group_.empty())
		throw rf_phreaker_error("No containers for collection.");

	size_t first = 0;
	for(; first < details_group_.size(); ++first) {
		if(details_group_[first].priority_ > 0) break;
	}
	size_t last = details_group_.size() - 1;
	for(; last >= 0; --last) {
		if(details_group_[last].priority_ > 0) break;
	}

	if(first > last)
		throw rf_phreaker_error("No valid collection_info within collection containers.");

	auto first_count = details_group_[last].priority_ / details_group_[first].priority_;

	for(int i = 0; i < first_count; ++i)
		ordered_containers_.push_back(details_group_[first].container_);

	for(size_t i = first + 1; i <= last; ++i) {
		if(details_group_[i].priority_ <= 0)
			continue;
		int num_elements = (int)(details_group_[last].priority_ / details_group_[i].priority_);
		auto spacing = ordered_containers_.size() / num_elements;
		double j = rand() % (int)num_elements;
		for(int k = 0; k < num_elements; ++k) {
			if((size_t)std::round(j) > ordered_containers_.size())
				j -= ordered_containers_.size();
			ordered_containers_.insert(std::next(ordered_containers_.begin(), (size_t)std::round(j)), details_group_[i].container_);
			j += spacing + 1; // Plus 1 to account for the insertion.
		}
	}

	ordered_containers_it_ = ordered_containers_.begin();
	include_first_position_ = true;
}

void create_sweep_first_order() {
	for(auto &i : details_group_) {
		if(i.specs_.has_spec(GSM_SWEEP) || i.specs_.has_spec(UMTS_SWEEP) || i.specs_.has_spec(LTE_SWEEP))
			ordered_containers_.push_back(i.container_);
	}
	ordered_containers_it_ = ordered_containers_.begin();
	include_first_position_ = true;

	if(ordered_containers_it_ == ordered_containers_.end())
		create_packet_or_collection_round_based_order();
}

double calculate_priority(const collection_info_container &container) const {
	// If the scheduling algorithm is collection_round_based and(!) the container is not a sweep container then
	// we make sure the priority is calculated using the the current number of channels specified in a collection round.  
	auto modifier = 1.0;
	if((settings_->scheduling_algorithm_ == collection_round_based || settings_->scheduling_algorithm_ == sweep_first_collection_round_based) && 
		!(container.has_specifier(GSM_SWEEP) || container.has_specifier(UMTS_SWEEP) || container.has_specifier(LTE_SWEEP))) {
		modifier = container.collection_info_group_.size();
	}
	if(container.specs_.size() == 1) {
		auto spec = container.specs_.front();
		switch(spec) {
		case GSM_SWEEP:
			return calculate_priority(settings_->gsm_sweep_collection_.priority_, modifier);
		case GSM_LAYER_3_DECODE:
			return calculate_priority(settings_->gsm_layer_3_collection_.priority_, modifier);
		//case CDMA_SWEEP:
		//	return ;
		//case CDMA_LAYER_3_DECODE:
		//	return ;
		case UMTS_SWEEP:
			return calculate_priority(settings_->umts_sweep_collection_.priority_, modifier);
		case UMTS_LAYER_3_DECODE:
			return calculate_priority(settings_->umts_layer_3_collection_.priority_, modifier);
		case LTE_SWEEP:
			return calculate_priority(settings_->lte_sweep_collection_.priority_, modifier);
		case LTE_LAYER_3_DECODE:
			return calculate_priority(settings_->lte_layer_3_collection_.priority_, modifier);
		case IQ_DATA:
			return calculate_priority(settings_->iq_data_priority_, modifier);
		case POWER_SPECTRUM:
			return calculate_priority(settings_->power_spectrum_priority_, modifier);
		default:
			throw rf_phreaker_error("Unknown specifier when determining priority.");
		}
	}
	// Assume it's a generic sweep if more than one specifier.
	else {
		return calculate_priority(settings_->sweep_collection_.priority_, modifier);
	}
}

double calculate_priority(double p, double group_size = 1) const {
	return group_size == 0 ?  0 : (1 / p * 100) / group_size;
}

bool get_next_collection_info(collection_info &c) {
	while(!is_done_) {
		collection_info_container *container;
		switch(settings_->scheduling_algorithm_) {
		case tech_based:
			container = get_container_for_tech_based();
			break;
		case collection_round_based:
		case packet_based:
		case sweep_first_collection_round_based:
		case sweep_first_packet_based:
			container = get_next_container();
			break;
		default:
			throw rf_phreaker_error("Unknown scheduling algorithm.");
		}
		if(container->get_auto_info(c))
			break;
	}
	// After we have gotten the next packet check to see if collection round has increased.
	if((*ordered_containers_it_)->collection_round() > 0)
		first_iteration_ = false;

	return !is_done_;
}

collection_info_container* get_container_for_tech_based() {
	if(include_first_position_) {
		include_first_position_ = false;
	}

	if((*ordered_containers_it_)->is_finished()) {
		if(++ordered_containers_it_ == ordered_containers_.end()) {
			first_iteration_ = false;
			ordered_containers_it_ = ordered_containers_.begin();
			if(has_multiple_scans_) {
				for(auto &c : details_group_)
					c.container_->reset();
			}
			else
				is_done_ = true;
		}
	}
	return *ordered_containers_it_;
}

collection_info_container* get_next_container() {
	if(include_first_position_)
		include_first_position_ = false;
	else
		++ordered_containers_it_;

	if(ordered_containers_it_ == ordered_containers_.end()) {
		if(has_multiple_scans_)
			ordered_containers_it_ = ordered_containers_.begin();
		else
			is_done_;
	}

	return *ordered_containers_it_;
}

collection_info_container* get_current_container() {
	return *ordered_containers_it_;
}

bool is_done() const { return is_done_; }

int64_t current_container_collection_round() const { return (*ordered_containers_it_)->collection_round(); }

bool has_multiple_scans() const { return has_multiple_scans_; }

private:
	class container_details {
	public:
		container_details(collection_info_container *container, double priority) 
			: container_(container)
			, specs_(container->specs_)
			, priority_(priority)
			, current_collection_round_size_(container->collection_info_group_.size()) {}

		bool operator <(const container_details &a) { return priority_ < a.priority_; }
		bool operator >(const container_details &a) { return priority_ > a.priority_; }
		collection_info_container *container_;
		double current_collection_round_size_;
		specifiers specs_;
		double priority_;
	};

	std::vector<container_details> details_group_;
	std::vector<collection_info_container*> ordered_containers_;
	std::vector<collection_info_container*>::iterator ordered_containers_it_;
	const settings *settings_;
	bool include_first_position_;
	bool is_done_;
	bool has_multiple_scans_;
	bool first_iteration_;
};

}}