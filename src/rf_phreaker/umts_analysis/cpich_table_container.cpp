#include "rf_phreaker/umts_analysis/cpich_table_container.h"
#include "rf_phreaker/umts_analysis/cpich_generator.h"
#include "rf_phreaker/umts_analysis/umts_types.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/ipp_helper.h"
#include "rf_phreaker/fir_filter/fir_filter.h"

cpich_table_container::cpich_table_container()
	: up_factor_(0)
	, down_factor_(0)
	, num_chips_(0)
	, over_sampling_rate_(0)
	, resampled_cpich_length_(0)
{}

cpich_table_container::~cpich_table_container()
{}

void cpich_table_container::configure(int up_factor, int down_factor, int num_chips)
{
	up_factor_ = up_factor;
	down_factor_ = down_factor;
	num_chips_ = num_chips;
	over_sampling_rate_ = (double)up_factor / down_factor;
	resampled_cpich_length_ = num_chips_ * up_factor_ / down_factor_;

	if ( num_chips_ % down_factor_ ) 
		throw(rf_phreaker::umts_analysis_error("An invalid size has been requested for the CPICH table."));
}

void cpich_table_container::generate_raw_cpich_table(int num_chips)
{
	configure(1, 1, num_chips);

	cpich_table_.reset(N_CPICH_CODES * num_chips);

	// Get the Gold code sequence, resample, and store appropriately.
	cpich_generator cpich_generator;

	for(uint32_t i = 0, cpich_idx = 0; i < N_CPICH_CODES; i++) {
		cpich_generator.create_cpich_signal(&cpich_table_[cpich_idx], i, num_chips_);
		cpich_idx += resampled_cpich_length_;
	}

}


void cpich_table_container::generate_resampled_cpich_table(rf_phreaker::frequency_type sampling_rate, int num_chips)
{	
	rf_phreaker::fir_filter filter(UMTS_CHIP_RATE_HZ, sampling_rate);
	filter.set_zero_delay(true);

	configure(filter.up_factor(), filter.down_factor(), num_chips);

	// Use a longer length for the taps because we're only doing this once.
	filter.set_taps(6501);

	generate_resampled_cpich_table(&filter);
}

void cpich_table_container::generate_resampled_cpich_table(const std::string &filter_spec_filename, int num_chips)
{
	rf_phreaker::resampling_filter filter(filter_spec_filename.c_str());
	filter.set_zero_delay(true);

	configure(filter.up_factor(), filter.down_factor(), num_chips);

	generate_resampled_cpich_table(&filter);
}

void cpich_table_container::generate_resampled_cpich_table(rf_phreaker::fir_filter *filter)
{
	// Note that we need a size larger than num_chips_
	// in order for the ZeroDelay filter to work properly.
	int gold_code_cpich_length = num_chips_ + filter->length() / up_factor_ + 1;
	
	ipp_32fc_array tmp_cpich(gold_code_cpich_length);
	Ipp32fc tmp; tmp.re = 0; tmp.im = 0;
	tmp_cpich.set_array_values(tmp);

	cpich_table_.reset(N_CPICH_CODES * resampled_cpich_length_);

	// Get the Gold code sequence, resample, and store appropriately.
	cpich_generator cpich_generator;

	for(uint32_t i = 0, cpich_idx = 0; i < N_CPICH_CODES; i++)
	{
		cpich_generator.create_cpich_signal(tmp_cpich.get(), i, num_chips_);
		
		if(up_factor_ == 1 && down_factor_ == 1)
			memcpy(&cpich_table_[cpich_idx], tmp_cpich.get(), gold_code_cpich_length);
		else
			filter->filter(tmp_cpich.get(), &cpich_table_[cpich_idx], num_chips_ / down_factor_);

		ipp_helper::normalize_signal(&cpich_table_[cpich_idx], resampled_cpich_length_);
		
		cpich_idx += resampled_cpich_length_;
	}
}
