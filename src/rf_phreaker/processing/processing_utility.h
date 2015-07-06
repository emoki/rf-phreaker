#pragma once

#include <map>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/lte_analysis/lte_types.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"


namespace rf_phreaker { namespace processing {

inline frequency_type determine_sampling_rate(LteChannelBandwidth bw)
{
	switch(bw) {
	case LteBandwidth_5MHZ:
		return lte_bandwidth_5_mhz_sampling_rate;
	case LteBandwidth_10MHZ:
		return lte_bandwidth_10_mhz_sampling_rate;
	case LteBandwidth_15MHZ:
		return lte_bandwidth_15_mhz_sampling_rate;
	case LteBandwidth_20MHZ:
		return lte_bandwidth_20_mhz_sampling_rate;
	case LteBandwidth_3MHZ:
		return lte_bandwidth_3_mhz_sampling_rate;
	case LteBandwidth_1_4MHZ:
		return lte_bandwidth_1_4_mhz_sampling_rate;
	default:
		return 0;
	}
}

inline bandwidth_type determine_bandwidth_for_collection(LteChannelBandwidth bw)
{
	// These should be valid bandwidths for bladeRF.  Alternatively we could ignore bandwidth when comparing collection_info for removal.
	switch(bw) {
	case LteBandwidth_5MHZ:
		return mhz(5);
	case LteBandwidth_10MHZ:
		return mhz(10);
	case LteBandwidth_15MHZ:
		return mhz(20);
	case LteBandwidth_20MHZ:
		return mhz(20);
	case LteBandwidth_3MHZ:
		return mhz(3);
	case LteBandwidth_1_4MHZ:
		return khz(1500);
	default:
		return 0;
	}
}

inline bandwidth_type convert_bandwidth(LteChannelBandwidth bw)
{
	switch(bw) {
	case LteBandwidth_5MHZ:
		return mhz(5);
	case LteBandwidth_10MHZ:
		return mhz(10);
	case LteBandwidth_15MHZ:
		return mhz(15);
	case LteBandwidth_20MHZ:
		return mhz(20);
	case LteBandwidth_3MHZ:
		return mhz(3);
	case LteBandwidth_1_4MHZ:
		return khz(1400);
	default:
		return 0;
	}
}

inline LteChannelBandwidth look_for_valid_bandwidth(const lte_measurements &measurements)
{
	auto bw = LteBandwidth_Unknown;
	auto best_sync_quality = -999.0;
	for(auto &lte : measurements) {
		// Currently multiple bandwidths can be erroneously decoded for the same channel.  For now we take the meas with the best sync_quality?
		// Fix LTE decoding!
		if(lte.Bandwidth != LteBandwidth_Unknown && lte.sync_quality > best_sync_quality) {
			bw = lte.Bandwidth;
			best_sync_quality = lte.sync_quality;
			break;
		}
	}
	return bw;
}

class lte_measurement_tracker
{
public:
	bool is_tracking(frequency_type freq)
	{
		return strongest_measurements_.find(freq) != strongest_measurements_.end();
	}

	bool is_within_stronger_measurement_bandwidth(frequency_type freq)
	{
		const auto it = strongest_measurements_.find(freq);
		for(auto &watch : strongest_measurements_) {
			if(freq != watch.first) {
				if(abs(freq - watch.first) < convert_bandwidth(watch.second.bw_) / 2 
					&& (it == strongest_measurements_.end() || it->second.sync_quality_ < watch.second.sync_quality_))
					return true;
			}
		}
		return false;
	}

	LteChannelBandwidth find_decoded_bandwidth(frequency_type freq)
	{
		auto it = strongest_measurements_.find(freq);
		if(it != strongest_measurements_.end())
			return it->second.bw_;
		return LteBandwidth_Unknown;
	}

	void clear() { strongest_measurements_.clear(); }

	void update_measurements(const lte_measurements &lte_group, frequency_type freq)
	{
		if(lte_group.size()) {
			auto bw = look_for_valid_bandwidth(lte_group);
			auto has_decoded_pbch = bw != LteBandwidth_Unknown;
			auto sync_quality = get_strongest_sync(lte_group);
			auto it = strongest_measurements_.find(freq);

			if(has_decoded_pbch) {
				if(it == strongest_measurements_.end()) 
					it = strongest_measurements_.insert(std::make_pair(freq, lte_watch(bw, sync_quality))).first;

				++it->second.num_pbch_decoded_;

				if(sync_quality > it->second.sync_quality_) {
					if(bw != LteBandwidth_Unknown)
						it->second.bw_ = bw;
					it->second.sync_quality_ = sync_quality;
				}
			}
		}
	}

	double get_strongest_sync(const lte_measurements &lte_group) const
	{
		double best_sync = -9999;
		for(auto &lte : lte_group) {
			if(best_sync < lte.sync_quality)
				best_sync = lte.sync_quality;
		}
		return best_sync;
	}

	bool has_decoded_layer_3(const lte_measurements &lte_group) const
	{
		for(auto &lte : lte_group) {
			if(has_decoded_layer_3(lte))
				return true;
		}
		return false;
	}

	bool has_decoded_layer_3 (const lte_measurement &lte) const {
		return lte.layer_3_.sib1_.is_decoded() || lte.layer_3_.sib4_.is_decoded() || lte.layer_3_.sib5_.is_decoded() || lte.layer_3_.sib6_.is_decoded()
			|| lte.layer_3_.sib7_.is_decoded() || lte.layer_3_.sib8_.is_decoded();
	}

	bool is_considered_valid_channel(frequency_type freq) const {
		auto it = strongest_measurements_.find(freq);
		if(it != strongest_measurements_.end())
			return it->second.num_pbch_decoded_ >= 1;
		else
			return false;
	}

private:
	struct lte_watch
	{
		lte_watch(LteChannelBandwidth bw, double sync_quality)
			: bw_(bw)
			, sync_quality_(sync_quality)
			, num_pbch_decoded_(0)
		{}
		LteChannelBandwidth bw_;
		double sync_quality_;
		int num_pbch_decoded_;
	};

	std::map<frequency_type, lte_watch> strongest_measurements_;
};

}}