#include "rf_phreaker/umts_analysis/spur_nullifier.h"
#include "rf_phreaker/umts_analysis/sort_peaks.h"

#include <cmath>

namespace rf_phreaker {

spur_nullifier::spur_nullifier(double ecio_threshold_dbm, int signal_length)
	: peak_threshold_(ecio_threshold_dbm)
	, max_num_peaks_(500)
{
	reset(signal_length);
}


spur_nullifier::~spur_nullifier(void)
{
}

void spur_nullifier::reset(int signal_length)
{
	assert(signal_length > 0);

	int order = static_cast<int>(log10((double)signal_length) / log10(2.0));

	fft_.reset(new fft_helper(order, IPP_FFT_DIV_BY_SQRTN));

	signal_length_ = (int)std::pow(2.0, order);

	fft_result_.reset(signal_length_);

	magnitude_result_.reset(signal_length_);
}

void spur_nullifier::nullify_spurs(ipp_32fc_array &signal)
{
	assert(signal_length_ <= signal.length());

	fft_->fft_forward(signal, fft_result_);

	find_max_and_relative_peaks();

	sort_peaks();

	null_relative_peaks_within_threshold();

	fft_->fft_inverse(fft_result_, signal);
}

void spur_nullifier::find_max_and_relative_peaks()
{
	max_peak_position_ = 0;

	peak_positions_.clear();

	ipp_helper::check_status(ippsMagnitude_32fc(fft_result_.get(), magnitude_result_.get(), magnitude_result_.length()));

	for(int i = 0; i < magnitude_result_.length(); i++)
		*magnitude_result_.get(i) = 20 * log10(magnitude_result_.get_value(i));
	
	ipp_helper::check_status(ippsMaxIndx_32f(magnitude_result_.get(), magnitude_result_.length(), &max_peak_, &max_peak_position_));

	for(int i = 1; i < magnitude_result_.length() - 1; ++i)
	{
		Ipp32f power = magnitude_result_.get_value(i);
		if(power - max_peak_ > -10 /*&&
			power > magnitude_result_.get_value(i - 1) &&
			power > magnitude_result_.get_value(i + 1)*/)
		{
			peak_positions_.push_back(i);
		}
	}
}

void spur_nullifier::reduce_peaks_if_necessary()
{
	if(peak_positions_.size() > max_num_peaks_)
	{
		sort_peaks();

		int num_to_remove = peak_positions_.size() - max_num_peaks_;
		
		for(int i = 0; i < num_to_remove; i++)
			peak_positions_.erase(peak_positions_.begin());
	}
}

void spur_nullifier::sort_peaks()
{
	sort_peaks_descending sort_descending(magnitude_result_);
		
	peak_positions_.sort(sort_descending);
}

void spur_nullifier::null_relative_peaks_within_threshold()
{
	uint32_t counter = 0;
	for(auto it = peak_positions_.begin(); it != peak_positions_.end(); it++)
	{
		fft_result_.get(*it)->re = 0;
		fft_result_.get(*it)->im = 0;

		if(++counter > max_num_peaks_)
			break;
	}
}

}