#include "rf_phreaker/umts_analysis/psch_container.h"
#include "rf_phreaker/umts_analysis/psch_generator.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "rf_phreaker/common/ipp_helper.h"

psch_container::psch_container()
: up_factor_(0)
, down_factor_(0)
, num_chips_(256)
, over_sampling_rate_(0)
, resampled_psch_length_(0)
{}

psch_container::psch_container(int up_factor, int down_factor)
: num_chips_(256)

{
	configure(up_factor, down_factor);
}

psch_container::~psch_container()
{}

void psch_container::configure(int up_factor, int down_factor)
{
	up_factor_ = up_factor;
	down_factor_ = down_factor;
	over_sampling_rate_ = (double)up_factor / down_factor;
	resampled_psch_length_ = num_chips_ * up_factor_ / down_factor_;

	if(num_chips_ % down_factor_)
		throw(rf_phreaker::umts_analysis_error("An invalid size has been requested for PSCH resampling."));
}


void psch_container::generate_resampled_psch(int up_factor, int down_factor)
{
	configure(up_factor, down_factor);

	rf_phreaker::fir_filter filter(up_factor_, down_factor_);
	filter.set_zero_delay(true);

	// Use a longer length for the taps because we're only doing this once.
	filter.set_taps(.1, 6501, 1);

	generate_resampled_psch(&filter);
}

void psch_container::generate_resampled_psch(const std::string &filter_spec_filename)
{
	rf_phreaker::resampling_filter filter(filter_spec_filename.c_str());
	filter.set_zero_delay(true);

	configure(filter.up_factor(), filter.down_factor());

	generate_resampled_psch(&filter);
}

void psch_container::generate_resampled_psch(rf_phreaker::fir_filter *filter)
{
	// Note that we need a size larger than num_chips_
	// in order for the ZeroDelay filter to work properly.
	int padded_psch_length = num_chips_ + filter->length() / up_factor_ + 1;

	ipp_32fc_array padded_psch(padded_psch_length);
	Ipp32fc tmp; tmp.re = 0; tmp.im = 0;
	padded_psch.set_array_values(tmp);

	resampled_psch_.reset(resampled_psch_length_);

	psch_generator generator;

	memcpy(padded_psch.get(), generator.psch().get(), generator.psch().length() * sizeof(Ipp32fc));

	if(up_factor_ == 1 && down_factor_ == 1)
		memcpy(resampled_psch_.get(), padded_psch.get(), num_chips_ / down_factor_);
	else
		filter->filter(padded_psch.get(), resampled_psch_.get(), num_chips_ / down_factor_);

	ipp_helper::normalize_signal(resampled_psch_.get(), resampled_psch_.length());
}
