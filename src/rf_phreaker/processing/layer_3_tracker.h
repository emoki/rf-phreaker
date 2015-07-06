#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/common/common_types.h"

#include <map>

namespace rf_phreaker { namespace processing {

template<typename Ta> class layer_3_tracker;
typedef layer_3_tracker<layer_3_information::gsm_bcch_si_type> gsm_layer_3_tracker;
typedef layer_3_tracker<layer_3_information::lte_sib_type> lte_layer_3_tracker;
typedef layer_3_tracker<layer_3_information::umts_sib_type> umts_layer_3_tracker;



template<typename Layer_3>
class all_layer_3_decoded
{
public:
	all_layer_3_decoded(int unique_identifer, int max_update, const std::vector<Layer_3> wanted_layer_3) : num_updated_(0), max_update_(max_update), unique_identifer_(unique_identifer) {
		for(auto i = wanted_layer_3.begin(); i != wanted_layer_3.end(); ++i)
			all_layer_3_[*i] = false;
	}

	bool is_fully_decoded() {
		for (auto layer_3 : all_layer_3_) {
			if (!layer_3.second)
				return false;
		}
		return true;
	}

	bool has_exceeded_max_updates() {
		return num_updated_ > max_update_;
	}

	template<typename Data>
	void update(const Data &data);

	int unique_identifer() { return unique_identifer_; }

	template<typename Data>
	bool is_equal(const Data &data) { return unique_identifer_ == create_unique_identifier(data); }
	
	template<typename Data>
	static int create_unique_identifier(const Data &data);


protected:
	int num_updated_;

	int max_update_;

	int unique_identifer_;

	std::map<Layer_3, bool> all_layer_3_;
};

template<> template<> inline int all_layer_3_decoded<layer_3_information::umts_sib_type>::create_unique_identifier<>(const umts_measurement &data)
{ return data.cpich_; }

template<> template<> inline int all_layer_3_decoded<layer_3_information::lte_sib_type>::create_unique_identifier<>(const lte_measurement &data)
{ return data.RsRecord.ID; }

template<> template<> inline void all_layer_3_decoded<layer_3_information::umts_sib_type>::update(const umts_measurement &data)
{
	++num_updated_;
	auto it = all_layer_3_.find(layer_3_information::MIB);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.is_mcc_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::SIB1);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.is_lac_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::SIB3_SIB4);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.is_cid_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::SIB11);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.neighbor_intra_group_.size() || data.layer_3_.neighbor_inter_group_.size() || data.layer_3_.neighbor_inter_rat_group_.size())
			it->second = true;
	}
}

template<> template<> inline void all_layer_3_decoded<layer_3_information::lte_sib_type>::update(const lte_measurement &data)
{
	++num_updated_;
	auto it = all_layer_3_.find(layer_3_information::lte_sib_type::SIB_1);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.sib1_.is_decoded()) {
			it->second = true;
			// Erase any layer 3 that is not scheduled.
			auto tmp = all_layer_3_;
			tmp.erase(layer_3_information::lte_sib_type::SIB_1);
			for(const auto &i : data.layer_3_.sib1_.scheduling_info_list_) {
				for(const auto &j : i.sib_mapping_info_) 
					tmp.erase(j);
			}
			for(auto &i : tmp) {
				all_layer_3_.erase(i.first);
			}	
		}
	}
	it = all_layer_3_.find(layer_3_information::lte_sib_type::SIB_3);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.sib3_.is_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::lte_sib_type::SIB_4);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.sib4_.is_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::lte_sib_type::SIB_5);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.sib5_.is_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::lte_sib_type::SIB_6);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.sib6_.is_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::lte_sib_type::SIB_7);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.sib7_.is_decoded()) it->second = true;
	}
	it = all_layer_3_.find(layer_3_information::lte_sib_type::SIB_8);
	if(it != all_layer_3_.end()) {
		if(data.layer_3_.sib8_.is_decoded()) it->second = true;
	}
}


template<typename Layer_3_type>
class layer_3_tracker
{
public:

    int max_update_;

	layer_3_tracker(int max_update, const std::vector<Layer_3_type> &wanted_layer_3 = {})
		: max_update_(max_update) {
		wanted_layer_3_ = wanted_layer_3;
	}

	template<typename Data>
	bool is_fully_decoded(rf_phreaker::frequency_type f, const Data &data)
	{
		auto freq_history = all_layer_3_history_.find(f);

		if(freq_history != all_layer_3_history_.end()) {
			for(auto &cell_layer_3 : freq_history->second) {
				if(cell_layer_3.is_equal(data))
					return cell_layer_3.is_fully_decoded();
			}
		}
		return false;
	}

	bool is_all_decoded() {
		for (auto freq : all_layer_3_history_) {
			for (auto layer_3 : freq.second) {
				if (!layer_3.is_fully_decoded())
					return false;
			}
		}
		return true;
	}

	bool is_all_decoded_on_freq(rf_phreaker::frequency_type f) {
		auto freq = all_layer_3_history_.find(f);
		if (freq != all_layer_3_history_.end()) {
			for (auto layer_3 : freq->second) {
				if (!layer_3.is_fully_decoded())
					return false;
			}
		}
		return true;
	}

	bool is_freq_in_history(rf_phreaker::frequency_type f)
	{
		return all_layer_3_history_.find(f) != all_layer_3_history_.end();
	}

	// Change lte so that it uses the layer_3 lib class.
	template<typename Data>
	void update(rf_phreaker::frequency_type f, const Data &data) {
		auto freq_history = all_layer_3_history_.find(f);

		// Use initializer list?
        if (freq_history == all_layer_3_history_.end()) {
            freq_layer_3_history tmp; // gcc doesn't allow for inplace construction?
            all_layer_3_history_.insert(std::make_pair(f, push_back(tmp, data)));
		}
		else {
            bool found_cell = false;
			for (auto &cell_layer_3 : freq_history->second) {
				if (cell_layer_3.is_equal(data)) {
					cell_layer_3.update(data);
					found_cell = true;
					break;
				}
			}
			if (!found_cell) {
				push_back(freq_history->second, data);
			}
		}
	}

	template<typename Data>
	bool in_history(rf_phreaker::frequency_type f, const Data &data) {
		bool found_cell = false;

		auto freq_history = all_layer_3_history_.find(f);
		
		if (freq_history != all_layer_3_history_.end()) {
			for (auto &cell_layer_3 : freq_history->second) {
				if (cell_layer_3.is_equal(data)) {
					found_cell = true;
					break;
				}
			}
		}

		return found_cell;
	}

	void clear() {
		all_layer_3_history_.clear();
		freq_max_updates_.clear();
	}

	void update_freq(rf_phreaker::frequency_type f) {
		auto it = freq_max_updates_.find(f);
		if(it == freq_max_updates_.end()) {
			it = freq_max_updates_.insert(std::make_pair(f, 0)).first;
		}
		++it->second;
	}

	bool has_freq_exceeded_max_updates(rf_phreaker::frequency_type f) const {
		auto it = freq_max_updates_.find(f);
		if(it != freq_max_updates_.end())
			return it->second > max_update_;
		else
			return false;
	}

	template<typename Data>
	bool has_data_exceeded_max_updates(rf_phreaker::frequency_type f, const Data &data) {
		auto freq_history = all_layer_3_history_.find(f);

		if(freq_history != all_layer_3_history_.end()) {
			for(auto &cell_layer_3 : freq_history->second) {
				if(cell_layer_3.is_equal(data)) {
					return cell_layer_3.has_exceeded_max_updates();
				}
			}
		}
		return false;
	}

	std::vector<Layer_3_type> wanted_layer_3() const { return wanted_layer_3_; }

	void set_wanted_layer_3(const std::vector<Layer_3_type> &wanted) { wanted_layer_3_ = wanted; }

protected:
	template<typename Data>
    std::vector<all_layer_3_decoded<Layer_3_type>> push_back(std::vector<all_layer_3_decoded<Layer_3_type>> &freq_history, const Data &data) {
		cell_history layer_3(all_layer_3_decoded<Layer_3_type>::create_unique_identifier(data), max_update_, wanted_layer_3_);
		layer_3.update(data);
		freq_history.push_back(layer_3);
		return freq_history;
	}

   typedef all_layer_3_decoded<Layer_3_type> cell_history;

   typedef std::vector<cell_history> freq_layer_3_history;

   std::map<rf_phreaker::frequency_type, freq_layer_3_history> all_layer_3_history_;

   std::map<rf_phreaker::frequency_type, int> freq_max_updates_;

   std::vector<Layer_3_type> wanted_layer_3_;
};

}}
