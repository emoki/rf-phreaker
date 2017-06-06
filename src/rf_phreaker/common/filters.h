#pragma once
#include <map>
#include <memory>
#include "rf_phreaker/fir_filter/fir_filter.h"

namespace rf_phreaker {

struct sampling_rates {
	sampling_rates() : input_sampling_rate_(0), output_sampling_rate_(0) {}
	sampling_rates(rf_phreaker::frequency_type i, rf_phreaker::frequency_type o, double norm_cutoff_freq) 
		: input_sampling_rate_(i), output_sampling_rate_(o), norm_cutoff_freq_(norm_cutoff_freq) {}
	sampling_rates(const sampling_rates &a) : input_sampling_rate_(a.input_sampling_rate_), 
		output_sampling_rate_(a.output_sampling_rate_), norm_cutoff_freq_(a.norm_cutoff_freq_) {}
	rf_phreaker::frequency_type input_sampling_rate_;
	rf_phreaker::frequency_type output_sampling_rate_;
	double norm_cutoff_freq_;
	bool operator()(const sampling_rates &a, const sampling_rates &b) const {
		if(a.input_sampling_rate_ == b.input_sampling_rate_) {
			if(a.output_sampling_rate_ == b.output_sampling_rate_)
				return a.norm_cutoff_freq_ < b.norm_cutoff_freq_;
			else
				return a.output_sampling_rate_ < b.output_sampling_rate_;
		}
		else
			return a.input_sampling_rate_ < b.input_sampling_rate_;
	}
};

class filters {
public:
	filters() 
	: norm_factor_(1)
	, taps_length_(-1) {}

	filters(double norm_factor, int taps_length) 
		: norm_factor_(norm_factor)
		, taps_length_(taps_length) {}

	filters(const filters &f) 
		: norm_factor_(f.norm_factor_)
		, taps_length_(f.taps_length_) {
		for(auto &i : f.filters_) {
			get_filter(i.first.input_sampling_rate_, i.first.output_sampling_rate_);
		}
	}

	fir_filter& get_filter(frequency_type input_sampling_rate, frequency_type output_sampling_rate, double norm_cutoff_freq = -1) {
		sampling_rates wanted(sampling_rates(input_sampling_rate, output_sampling_rate, norm_cutoff_freq));
		auto it = filters_.find(wanted);
		if(it == filters_.end()) {
			auto filter = std::make_shared<rf_phreaker::fir_filter>();
			filter->set_zero_delay(true);
			filter->set_up_down_factor_based_on_sampling_rates(input_sampling_rate, output_sampling_rate);
			filter->set_taps(taps_length_, norm_factor_, norm_cutoff_freq);
			it = filters_.insert(std::make_pair(wanted, filter)).first;
		}
		return *it->second;
	}

private:
	std::map<sampling_rates, std::shared_ptr<rf_phreaker::fir_filter>, sampling_rates> filters_;

	double norm_factor_;
	int taps_length_;
};

}