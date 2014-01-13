#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"
#include "rf_phreaker/common/common_types.h"

#include <map>

namespace rf_phreaker { namespace processing {


enum lte_layer_3
{
	SIB1,
	NUM_LAYER_3
};


template<typename Ta> class layer_3_tracker;
typedef layer_3_tracker<lte_layer_3> lte_layer_3_tracker;


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
	void update(const Data &data) {
		++num_updated_;

		if (data.cid != layer_3_information::not_decoded_32)
			all_layer_3_[SIB1] = true;
	}

	int unique_identifer() { return unique_identifer_; }
protected:
	int num_updated_;

	int max_update_;

	int unique_identifer_;

	std::vector<bool> all_layer_3_;
};


template<typename Layer_3_type>
class layer_3_tracker
{
public:
	layer_3_tracker(int max_update) : max_update_(max_update) {}

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

	// Change lte so that it uses the layer_3 lib class.
	template<typename Data>
	void update(rf_phreaker::frequency_type f, const Data &data) {
		auto freq_history = wanted_layer_3_.find(f);

		// Use initializer list?
		if (freq_history == wanted_layer_3_.end()) {
			wanted_layer_3_.insert(std::make_pair(f, push_back(freq_layer_3_history(), data)));
		}
		else {
			bool found_cell = false;
			for (auto &cell_layer_3 : freq_history->second) {
				if (cell_layer_3.unique_identifer() == data.RsRecord.ID) {
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
				if (cell_layer_3.unique_identifer() == data.RsRecord.ID) {
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
		cell_history layer_3(data.RsRecord.ID, max_update_);
		layer_3.update(data);
		freq_history.push_back(layer_3);
		return freq_history;
	}




	int max_update_;

	typedef all_layer_3_decoded<Layer_3_type> cell_history;
	
	typedef std::vector<all_layer_3_decoded<Layer_3_type>> freq_layer_3_history;
	
	std::map<rf_phreaker::frequency_type, freq_layer_3_history> wanted_layer_3_;
};

}
}