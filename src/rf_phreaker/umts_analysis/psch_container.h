#pragma once

#include "rf_phreaker/umts_analysis/umts_types.h"
#include "rf_phreaker/common/ipp_array.h"
#include "ipp.h"

namespace rf_phreaker { class fir_filter; }

class psch_container
{
public:
	psch_container();

	psch_container(int up_factor, int down_factor);

	psch_container(const std::string &filter_spec_filename);

	~psch_container();

	void generate_resampled_psch(int up_factor, int down_factor);

	void generate_resampled_psch(const std::string &filter_spec_filename);

	const Ipp32fc* resampled_psch_ptr() { return resampled_psch_.get(); }

	const ipp_32fc_array& resampled_psch_array() { return resampled_psch_; }

	int up_factor() { return up_factor_; }

	int down_factor() { return down_factor_; }

private:
	void configure(int up_factor, int down_factor);

	void generate_resampled_psch(rf_phreaker::fir_filter *filter);

	ipp_32fc_array resampled_psch_;
	int num_chips_;
	int up_factor_;
	int down_factor_;
	double over_sampling_rate_;
	int resampled_psch_length_;
};

