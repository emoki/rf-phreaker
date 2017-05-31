#pragma once

#include <map>
#include <algorithm>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/operating_band_range_specifier.h"
#include "rf_phreaker/common/power_spectrum_calculator.h"
#include "rf_phreaker/lte_analysis/lte_types.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/gsm_analysis/gsm_defs.h"

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
		return mhz(14);
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

inline bandwidth_type get_upper_scanner_bandwidth(frequency_type bw) {
	// These should be valid bandwidths for bladeRF.  
	if(bw > mhz(20))
		return mhz(28);
	else if(bw > mhz(14))
		return mhz(20);
	else if(bw > mhz(12))
		return mhz(14);
	else if(bw > mhz(10))
		return mhz(12);
	else if(bw > khz(8750))
		return mhz(10);
	else if(bw > mhz(7))
		return khz(8750);
	else if(bw > mhz(6))
		return mhz(7);
	else if(bw > khz(5500))
		return mhz(6);
	else if(bw > mhz(5))
		return khz(5500);
	else if(bw > khz(3840))
		return mhz(5);
	else if(bw > mhz(3))
		return khz(3840);
	else if(bw > khz(2750))
		return mhz(3);
	else if(bw > khz(2500))
		return khz(2750);
	else if(bw > khz(1750))
		return khz(2500);
	else if(bw > khz(1500))
		return khz(1750);
	else
		return khz(1500);
}

inline bandwidth_type get_lower_scanner_bandwidth(frequency_type bw) {
	// These should be valid bandwidths for bladeRF.  
	if(bw < khz(1750))
		return khz(1500);
	else if(bw < khz(2500))
		return khz(1750);
	else if(bw < khz(2750))
		return khz(2500);
	else if(bw < khz(3))
		return khz(2750);
	else if(bw < khz(3840))
		return mhz(3);
	else if(bw < mhz(5))
		return khz(3840);
	else if(bw < khz(5500))
		return mhz(5);
	else if(bw < mhz(6))
		return khz(5500);
	else if(bw < mhz(7))
		return mhz(6);
	else if(bw < khz(8750))
		return mhz(7);
	else if(bw < mhz(10))
		return khz(8750);
	else if(bw < mhz(12))
		return mhz(10);
	else if(bw < mhz(14))
		return mhz(12);
	else if(bw < mhz(20))
		return mhz(14);
	else if(bw < mhz(28))
		return mhz(20);
	else
		return mhz(28);
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

class gsm_frequency_tracker {
public:
	void clear() {
		added_freqs_.clear();
	}

	void insert(frequency_type freq) {
		added_freqs_.insert(freq);
	}

	bool do_we_add_freq(frequency_type freq) const {
		if(added_freqs_.find(freq) != added_freqs_.end())
			return false;
		bool within_lower_freq = distance_to_lesser(freq) != -1 
			&& distance_to_lesser(freq) <= high_bandwidth_range_ + gsm_processing_if_;
		bool within_higher_freq = distance_to_higher(freq) != -1 
			&& distance_to_higher(freq) <= low_bandwidth_range_;
		return !within_lower_freq && !within_higher_freq;
	}
	frequency_type distance_to_lesser(frequency_type freq) const {
		auto lesser = greatest_less(added_freqs_, freq);
		if(lesser != added_freqs_.end()) 
			return freq - *lesser;
		else
			return -1;
	}

	frequency_type distance_to_higher(frequency_type freq) const {
		auto greater = added_freqs_.upper_bound(freq);
		if(greater != added_freqs_.end())
			return *greater - freq;
		else
			return -1;
	}
	
	frequency_type calculate_closest_freq(frequency_type freq, operating_band b) const {
		auto range = range_specifier_.get_band_freq_range(b);
		auto lower_distance = distance_to_lesser(freq);
		auto higher_distance = distance_to_higher(freq);
		frequency_type new_freq;
		if(lower_distance != -1 && higher_distance != -1) {
			if(higher_distance > total_processing_bandwidth_)
				new_freq = freq + low_bandwidth_range_;
			else if(lower_distance > total_processing_bandwidth_)
				new_freq = freq - high_bandwidth_range_;
			else {
				new_freq = rf_phreaker::round_to_nearest<khz(100)>((freq + higher_distance + freq - lower_distance) / 2);
			}

		}
		else if(higher_distance == -1) {
			new_freq = freq + low_bandwidth_range_;
		}
		else if(lower_distance == -1) {
			new_freq = freq - high_bandwidth_range_;
		}
		else { // no other freqs
			new_freq = freq + low_bandwidth_range_;
		}

		if(new_freq < range.low_freq_hz_)
			new_freq = range.low_freq_hz_;
		else if(new_freq > range.high_freq_hz_)
			new_freq = range.high_freq_hz_;

		return ensure_proper_processing_if(new_freq);
	}

	frequency_type ensure_proper_processing_if(frequency_type freq) const {
		if(freq % khz(200) == 0)
			return freq - gsm_processing_if_;
		else
			return freq;
	}

private:
	std::set<frequency_type> added_freqs_;
	static const bandwidth_type total_processing_bandwidth_ = GSM_PROCESSING_BANDWIDTH;
	static const bandwidth_type low_bandwidth_range_ = GSM_LOW_BANDWIDTH_HZ;
	static const bandwidth_type high_bandwidth_range_ = GSM_HIGH_BANDWIDTH_HZ;
	static const bandwidth_type gsm_processing_if_ = GSM_PROCESSING_IF;
	operating_band_range_specifier range_specifier_;
};

class power_spectrum_approximator {
public:
	power_spectrum_approximator()
		: max_num_samples_(mhz(3))
		, min_fft_order_(3)
		, max_fft_order_(15)
		, max_bandwidth_(get_upper_scanner_bandwidth(mhz(28)))
		, min_sampling_rate_(khz(1500)) // Minimum sampling_rate must be at least 1.5khz to support the lowest scanner bandwidth of 1.5khz
		, max_sampling_rate_(mhz(32))
		, num_windows_(30)
	{}

	void determine_spectrum_parameters(frequency_type start_freq, frequency_type span, frequency_type bin_size, time_type dwell_time_ns, int64_t identifier) {
		// Using the same dwell time the processing time doubles (1.15x) every increment of fft_order.
		// Given a bin size required we can calculate the sampling rate and fft order.  This will give us the max 
		// bandwidth we can use.  Get the closest nuand bandwidth and then adjust center freq so the start freq is
		// at the beginning of the bin.task
		// TODO - make sure the bandwidth can be the same as the sampling_rate since we're downconverting.
		power_specs_.clear();
		determine_spectrum_parameters_(start_freq, span, bin_size, dwell_time_ns, identifier);
	}
	
	frequency_type calculate_allowed_bandwidth(frequency_type sampling_rate) {
		// Because we're converting signal to baseband we can actually get away with using the sampling_rate as the actual bandwidth.
		return sampling_rate;
	}

	std::vector<power_spectrum_spec>& power_specs() { return power_specs_; }

private:	
	void determine_spectrum_parameters_(frequency_type start_freq, frequency_type span, frequency_type bin_size, time_type dwell_time_ns, int64_t identifier) {
		// Using the same dwell time the processing time doubles (1.15x) every increment of fft_order.
		// Given a bin size required we can calculate the sampling rate and fft order.  This will give us the max 
		// bandwidth we can use.  Get the closest nuand bandwidth and then adjust center freq so the start freq is
		// at the center of a bin.
		// TODO - make sure the bandwidth can be the same as the sampling_rate since we're downconverting.

		power_spectrum_spec spec;
		spec.bin_size_ = bin_size;
		spec.step_size_ = bin_size;
		spec.identifier_ = identifier;

		auto fft_order = min_fft_order_ - 1;
		frequency_type sampling_rate = 0;		
		frequency_type scanner_bandwidth = 0;
		while(fft_order < max_fft_order_) {
			fft_order = fft_order + 1;
			sampling_rate = power_spectrum_calculator::determine_sampling_rate(fft_order, bin_size);
			if(sampling_rate < min_sampling_rate_ || sampling_rate > max_sampling_rate_) {
				scanner_bandwidth = 0;
				continue;
			}
			scanner_bandwidth = get_upper_scanner_bandwidth(calculate_allowed_bandwidth(sampling_rate));
			if(scanner_bandwidth > span) {
				break;
			}
		}

		if(scanner_bandwidth < span) {
			determine_spectrum_parameters_(start_freq, span / 2, bin_size, dwell_time_ns, identifier);
			determine_spectrum_parameters_(start_freq + span / 2, span / 2, bin_size, dwell_time_ns, identifier);
		}
		else {
			spec.window_length_ = (int)pow(2, fft_order);
			spec.sampling_rate_ = sampling_rate;
			auto min_dwell_time = rf_phreaker::convert_to_time(spec.window_length_ * num_windows_, spec.sampling_rate_);
			auto max_dwell_time = rf_phreaker::convert_to_time(max_num_samples_, spec.sampling_rate_);
			spec.dwell_time_ = std::max(std::min(max_dwell_time, dwell_time_ns), min_dwell_time);
			spec.num_windows_ = rf_phreaker::convert_to_samples(spec.dwell_time_, spec.sampling_rate_) / spec.window_length_;
			spec.start_frequency_ = start_freq - bin_size / 2;
			spec.end_frequency_ = start_freq + span - bin_size / 2;
			spec.span_ = span;
			power_specs_.push_back(spec);
		}
	}

	int max_num_samples_;
	int min_fft_order_;
	int max_fft_order_;
	frequency_type max_bandwidth_;
	frequency_type min_sampling_rate_;
	frequency_type max_sampling_rate_;
	int num_windows_;
	std::vector<power_spectrum_spec> power_specs_;
};

}}