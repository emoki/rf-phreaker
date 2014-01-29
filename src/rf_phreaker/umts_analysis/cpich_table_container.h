#pragma once

#include "rf_phreaker/umts_analysis/umts_types.h"
#include "rf_phreaker/common/ipp_array.h"
#include "ipp.h"

namespace rf_phreaker { class fir_filter; }

class cpich_table_container
{
public:
	cpich_table_container();

	~cpich_table_container();

	void generate_resampled_cpich_table(int up_factor, int down_factor, int num_chips = N_TOTAL_CHIPS_CPICH);

	void generate_resampled_cpich_table(const std::string &filter_spec_filename, int num_chips = N_TOTAL_CHIPS_CPICH);

	void erase_cpich_table() { cpich_table_.reset(0); }

	const Ipp32fc* resampled_cpich_table_ptr() const { return cpich_table_.get(); }

	const ipp_32fc_array resampled_cpich_table_array() const { return cpich_table_; }

	int up_factor() { return up_factor_; }

	int down_factor() { return down_factor_; }

private:

	void configure(int up_factor, int down_factor, int num_chips);

	void generate_resampled_cpich_table(rf_phreaker::fir_filter *filter);

	ipp_32fc_array cpich_table_;
	int num_chips_;
	int up_factor_;
	int down_factor_;
	double over_sampling_rate_;
	int resampled_cpich_length_;
};

