#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"
#include "rf_phreaker/gsm_analysis/gsm_measurement.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/common/common_types.h"

#include <map>

namespace rf_phreaker { namespace processing {

class bit_index;
template<typename Ta, typename Ga> class layer_3_tracker;
typedef layer_3_tracker<layer_3_information::gsm_bcch_si_type, bit_index> gsm_layer_3_tracker;
typedef layer_3_tracker<layer_3_information::lte_sib_type, bool> lte_layer_3_tracker;
typedef layer_3_tracker<layer_3_information::umts_sib_type, bool> umts_layer_3_tracker;

class bit_index {
public:
	bit_index() : mask_(0), elements_(0), is_complete_(false) {}
	bit_index(bit_index &t) : mask_(t.mask_), elements_(t.elements_), is_complete_(t.is_complete_) {}
	uint64_t elements_;
	uint64_t mask_;
	bool is_complete_;
	void set_mask(uint32_t max_index) {
		mask_ = 0;
		mask_ = 1ULL << max_index;
		mask_ -= 1;
	}
	void add_bit(uint32_t element_index) { 
		elements_ |= (1ULL << element_index); 
	}
	void clear_elements() { elements_ = 0; }
	bool is_complete() { return is_complete_ || ((mask_ != 0) && (mask_ & elements_) == mask_); }
	void operator=(bool t) { is_complete_ = t; }
	operator bool() { return is_complete(); }
	//bool operator!() { return !is_complete(); }
};

template<typename Layer_3, typename T>
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

	std::map<Layer_3, T> all_layer_3_;
};

template<> template<> inline int all_layer_3_decoded<layer_3_information::gsm_bcch_si_type, bit_index>::create_unique_identifier<>(const gsm_measurement &data) { return static_cast<int>(data.center_frequency_); }

template<> template<> inline int all_layer_3_decoded<layer_3_information::umts_sib_type, bool>::create_unique_identifier<>(const umts_measurement &data) { return data.cpich_; }

template<> template<> inline int all_layer_3_decoded<layer_3_information::lte_sib_type, bool >::create_unique_identifier<>(const lte_measurement &data)
{ return data.RsRecord.ID; }

template<> template<> inline void all_layer_3_decoded<layer_3_information::gsm_bcch_si_type, bit_index>::update(const gsm_measurement &data) {
	++num_updated_;
	auto it = all_layer_3_.find(layer_3_information::SI_2);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_2_;
		if(si.is_decoded()) {
			it->second = true;
			if(si.bcch_neighbors_has_extension_ == false) {
				auto tmp = all_layer_3_.find(layer_3_information::SI_2BIS);
				if(tmp != all_layer_3_.end()) {
					tmp->second = true;
				}
			}
		}
	}
	it = all_layer_3_.find(layer_3_information::SI_2BIS);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_2bis_;
		if(si.is_decoded()) {
			if(si.rest_octet_count_ != -1) {
				it->second.set_mask(si.rest_octet_count_ + 1);
				it->second.add_bit(si.rest_octet_index_);
			}
			else
				it->second = true;
		}
	}
	it = all_layer_3_.find(layer_3_information::SI_2TER);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_2ter_;
		if(si.is_decoded()) {
			if(si.rest_octet_count_ != -1) {
				it->second.set_mask(si.rest_octet_count_ + 1);
				it->second.add_bit(si.rest_octet_index_);
			}
			else
				it->second = true;
		}
	}
	it = all_layer_3_.find(layer_3_information::SI_2QUATER);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_2quater_;
		if(si.is_decoded()) {
			it->second.set_mask(si.rest_octet_count_ + 1);
			it->second.add_bit(si.rest_octet_index_);
		}
	}
	it = all_layer_3_.find(layer_3_information::SI_3);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_3_;
		if(si.is_decoded()) {
			it->second = true;
			if(si.is_2ter_present_ == false) {
				auto tmp = all_layer_3_.find(layer_3_information::SI_2TER);
				if(tmp != all_layer_3_.end()) tmp->second = true;
			}
			if(si.is_2quater_present_ == false) {
				auto tmp = all_layer_3_.find(layer_3_information::SI_2QUATER);
				if(tmp != all_layer_3_.end()) tmp->second = true;
			}
		}
	}
	it = all_layer_3_.find(layer_3_information::SI_4);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_4_;
		if(si.is_decoded()) {
			it->second = true;
			if(si.have_additional_param_in_si7_si8_ == false) {
				auto tmp = all_layer_3_.find(layer_3_information::SI_7);
				if(tmp != all_layer_3_.end()) tmp->second = true;
				tmp = all_layer_3_.find(layer_3_information::SI_8);
				if(tmp != all_layer_3_.end()) tmp->second = true;
			}
		}
	}
	it = all_layer_3_.find(layer_3_information::SI_7);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_7_;
		if(si.is_decoded()) {
			it->second = true;
		}
	}
	it = all_layer_3_.find(layer_3_information::SI_8);
	if(it != all_layer_3_.end()) {
		const auto &si = data.layer_3_.si_8_;
		if(si.is_decoded()) {
			it->second = true;
		}
	}
	//it = all_layer_3_.find(layer_3_information::SI_23);
	//if(it != all_layer_3_.end()) {
	//}
}

template<> template<> inline void all_layer_3_decoded<layer_3_information::umts_sib_type, bool>::update(const umts_measurement &data) {
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

template<> template<> inline void all_layer_3_decoded<layer_3_information::lte_sib_type, bool>::update(const lte_measurement &data)
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


template<typename Layer_3_type, typename T>
class layer_3_tracker
{
public:
	layer_3_tracker(int max_update, int min_collection_round, int min_decode_count, const std::vector<Layer_3_type> &wanted_layer_3 = {})
		: max_update_(max_update)
		, min_collection_round_(min_collection_round)
		, min_decode_count_(min_decode_count) {
		wanted_layer_3_ = wanted_layer_3;
	}

	template<typename Data>
	bool is_fully_decoded(rf_phreaker::frequency_type f, const Data &data) {
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
		for(auto freq : all_layer_3_history_) {
			for(auto layer_3 : freq.second) {
				if(!layer_3.is_fully_decoded())
					return false;
			}
		}
		return true;
	}

	bool is_all_decoded_on_freq(rf_phreaker::frequency_type f) {
		auto freq = all_layer_3_history_.find(f);
		if(freq != all_layer_3_history_.end()) {
			for(auto layer_3 : freq->second) {
				if(!layer_3.is_fully_decoded())
					return false;
			}
		}
		return true;
	}

	bool is_freq_in_history(rf_phreaker::frequency_type f) {
		return all_layer_3_history_.find(f) != all_layer_3_history_.end();
	}

	// Change lte so that it uses the layer_3 lib class.
	template<typename Data>
	void update(rf_phreaker::frequency_type f, const Data &data) {
		auto freq_history = all_layer_3_history_.find(f);

		// Use initializer list?
		if(freq_history == all_layer_3_history_.end()) {
			freq_layer_3_history tmp; // gcc doesn't allow for inplace construction?
			all_layer_3_history_.insert(std::make_pair(f, push_back(tmp, data)));
		}
		else {
			bool found_cell = false;
			for(auto &cell_layer_3 : freq_history->second) {
				if(cell_layer_3.is_equal(data)) {
					cell_layer_3.update(data);
					found_cell = true;
					break;
				}
			}
			if(!found_cell) {
				push_back(freq_history->second, data);
			}
		}
	}

	template<typename Data>
	bool in_history(rf_phreaker::frequency_type f, const Data &data) {
		bool found_cell = false;

		auto freq_history = all_layer_3_history_.find(f);

		if(freq_history != all_layer_3_history_.end()) {
			for(auto &cell_layer_3 : freq_history->second) {
				if(cell_layer_3.is_equal(data)) {
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
		freq_decode_count_.clear();
	}

	void clear_freq(rf_phreaker::frequency_type f) {
		auto it = freq_max_updates_.find(f);
		if(it != freq_max_updates_.end())
			it->second = 0;
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

	void clear_decodes(rf_phreaker::frequency_type f) {
		auto it = freq_decode_count_.find(f);
		if(it != freq_decode_count_.end())
			it->second.first = 0;
			it->second.second = 0;
	}
	
	void update_decodes(rf_phreaker::frequency_type f, bool is_decoded) {
		auto it = freq_decode_count_.find(f);
		if(it == freq_decode_count_.end()) {
			it = freq_decode_count_.insert(std::make_pair(f, std::make_pair(0, 0))).first;
		}
		++it->second.first;
		it->second.second += is_decoded ? 1 : 0;
	}

	bool has_freq_exceeded_max_no_decodes(rf_phreaker::frequency_type f) const {
		auto it = freq_decode_count_.find(f);
		if(it != freq_decode_count_.end())
			return it->second.first > min_collection_round_ && it->second.second < min_decode_count_;
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

	int max_update_;

	int min_collection_round_;

	int min_decode_count_;

protected:
	template<typename Data>
    std::vector<all_layer_3_decoded<Layer_3_type, T>> push_back(std::vector<all_layer_3_decoded<Layer_3_type, T>> &freq_history, const Data &data) {
		cell_history layer_3(all_layer_3_decoded<Layer_3_type, T>::create_unique_identifier(data), max_update_, wanted_layer_3_);
		layer_3.update(data);
		freq_history.push_back(layer_3);
		return freq_history;
	}

   typedef all_layer_3_decoded<Layer_3_type, T> cell_history;

   typedef std::vector<cell_history> freq_layer_3_history;

   std::map<rf_phreaker::frequency_type, freq_layer_3_history> all_layer_3_history_;

   std::map<rf_phreaker::frequency_type, int> freq_max_updates_;

   std::map<rf_phreaker::frequency_type, std::pair<int, int>> freq_decode_count_;

   std::vector<Layer_3_type> wanted_layer_3_;
};

}}
