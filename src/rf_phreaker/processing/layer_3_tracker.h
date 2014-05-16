#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/common/common_types.h"

#include <map>

namespace rf_phreaker { namespace processing {

namespace lte_layer_3
{
	enum lte_layer_3
	{
		SIB1,
		SIB4,
		SIB5,
		SIB6,
		SIB7,
		SIB8,
		NUM_LAYER_3
	};
	inline layer_3_information::lte_sib_type convert(int a)
	{
		using namespace layer_3_information;
		switch((lte_layer_3)a)
		{
		case SIB4:
			return sib_4;
		case SIB5:
			return sib_5;
		case SIB6:
			return sib_6;
		case SIB7:
			return sib_7;
		case SIB8:
			return sib_8;
		default:
			return spare_1;
		}
	}
};
namespace umts_layer_3
{
	enum umts_layer_3
	{
		MIB,
		SIB1,
		SIB3_SIB4,
		SIB11,
		NUM_LAYER_3
	};
}

template<typename Ta> class layer_3_tracker;
typedef layer_3_tracker<lte_layer_3::lte_layer_3> lte_layer_3_tracker;
typedef layer_3_tracker<umts_layer_3::umts_layer_3> umts_layer_3_tracker;



template<typename Layer_3>
class all_layer_3_decoded
{
public:
	all_layer_3_decoded(int unique_identifer, int max_update) : num_updated_(0), max_update_(max_update), unique_identifer_(unique_identifer) {
		all_layer_3_.resize(Layer_3::NUM_LAYER_3);
		for (auto layer_3 : all_layer_3_)
			layer_3 = false;
	}

	bool is_fully_decoded() {
		for (auto layer_3 : all_layer_3_) {
			if (!layer_3)
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

	std::vector<bool> all_layer_3_;
};

template<> template<> inline int all_layer_3_decoded<umts_layer_3::umts_layer_3>::create_unique_identifier<>(const umts_measurement &data) 
{ return data.cpich_; }

template<> template<> inline int all_layer_3_decoded<lte_layer_3::lte_layer_3>::create_unique_identifier<>(const lte_measurement &data) 
{ return data.RsRecord.ID; }

template<> template<> inline void all_layer_3_decoded<umts_layer_3::umts_layer_3>::update(const umts_measurement &data)
{
	++num_updated_;

	if(data.layer_3_.is_mcc_decoded())
		all_layer_3_[umts_layer_3::MIB] = true;
	if(data.layer_3_.is_lac_decoded())
		all_layer_3_[umts_layer_3::SIB1] = true;
	if(data.layer_3_.is_cid_decoded())
		all_layer_3_[umts_layer_3::SIB3_SIB4] = true;
	if(data.layer_3_.neighbor_intra_group_.size() || data.layer_3_.neighbor_inter_group_.size() || data.layer_3_.neighbor_inter_rat_group_.size())
		all_layer_3_[umts_layer_3::SIB11] = true;
}

template<> template<> inline void all_layer_3_decoded<lte_layer_3::lte_layer_3>::update(const lte_measurement &data)
{
	++num_updated_;

	if(data.layer_3_.sib1_.decoded_) {
		all_layer_3_[lte_layer_3::SIB1] = true;
		
		// Temporary hack - certain sibs are optional but sib1 contains the schedule list so we will set all sibs that are not scheduled to true.
		for(int i = 0; i < lte_layer_3::lte_layer_3::NUM_LAYER_3; ++i) {
			bool found = false;
			for(auto &schedule : data.layer_3_.sib1_.scheduling_info_list_) {
				auto it = std::find(schedule.sib_mapping_info_.begin(), schedule.sib_mapping_info_.end(), lte_layer_3::convert(i));
				if(it != schedule.sib_mapping_info_.end()) {
					found = true;
					break;
				}
			}
			if(found == false)
				all_layer_3_[i] = true;
		}
	}
	if(data.layer_3_.sib4_.decoded_)
		all_layer_3_[lte_layer_3::SIB4] = true;
	if(data.layer_3_.sib5_.decoded_)
		all_layer_3_[lte_layer_3::SIB5] = true;
	if(data.layer_3_.sib6_.decoded_)
		all_layer_3_[lte_layer_3::SIB6] = true;
	if(data.layer_3_.sib7_.decoded_)
		all_layer_3_[lte_layer_3::SIB7] = true;
	if(data.layer_3_.sib8_.decoded_)
		all_layer_3_[lte_layer_3::SIB8] = true;

}


template<typename Layer_3_type>
class layer_3_tracker
{
public:

    int max_update_;

    layer_3_tracker(int max_update) : max_update_(max_update) {}

	template<typename Data>
	bool is_fully_decoded(rf_phreaker::frequency_type f, const Data &data)
	{
		auto freq_history = wanted_layer_3_.find(f);

		if(freq_history != wanted_layer_3_.end()) {
			for(auto &cell_layer_3 : freq_history->second) {
				if(cell_layer_3.is_equal(data))
					return cell_layer_3.is_fully_decoded();
			}
		}
		return false;
	}

	bool is_all_decoded() {
		for (auto freq : wanted_layer_3_) {
			for (auto layer_3 : freq.second) {
				if (!layer_3.is_fully_decoded() && !layer_3.has_exceeded_max_updates())
					return false;
			}
		}
		return true;
	}

	bool is_all_decoded_on_freq(rf_phreaker::frequency_type f) {
		auto freq = wanted_layer_3_.find(f);
		if (freq != wanted_layer_3_.end()) {
			for (auto layer_3 : freq->second) {
				if (!layer_3.is_fully_decoded() && !layer_3.has_exceeded_max_updates())
					return false;
			}
		}
		return true;
	}

	bool is_freq_in_history(rf_phreaker::frequency_type f)
	{
		return wanted_layer_3_.find(f) != wanted_layer_3_.end();
	}

	// Change lte so that it uses the layer_3 lib class.
	template<typename Data>
	void update(rf_phreaker::frequency_type f, const Data &data) {
		auto freq_history = wanted_layer_3_.find(f);

		// Use initializer list?
        if (freq_history == wanted_layer_3_.end()) {
            freq_layer_3_history tmp; // gcc doesn't allow for inplace construction?
            wanted_layer_3_.insert(std::make_pair(f, push_back(tmp, data)));
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

		auto freq_history = wanted_layer_3_.find(f);
		
		if (freq_history != wanted_layer_3_.end()) {
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
		wanted_layer_3_.clear();
	}

protected:
	template<typename Data>
    std::vector<all_layer_3_decoded<Layer_3_type>> push_back(std::vector<all_layer_3_decoded<Layer_3_type>> &freq_history, const Data &data) {
		cell_history layer_3(all_layer_3_decoded<Layer_3_type>::create_unique_identifier(data), max_update_);
		layer_3.update(data);
		freq_history.push_back(layer_3);
		return freq_history;
	}


   typedef all_layer_3_decoded<Layer_3_type> cell_history;

   typedef std::vector<all_layer_3_decoded<Layer_3_type>> freq_layer_3_history;

   std::map<rf_phreaker::frequency_type, freq_layer_3_history> wanted_layer_3_;



};

}
}
