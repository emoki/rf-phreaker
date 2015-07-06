#pragma once

#include "rf_phreaker/fir_filter/fir_filter.h"


// Class which down-converts a modulated signal to baseband,
// resamples to the native sampling rate (optional),
// applies a zero-delay low-pass filter (required),
// and correlates against a template.
class modulated_signal_correlator
{
public:
	modulated_signal_correlator(
		const Ipp32fc* template_samples, unsigned int template_length,
		unsigned int max_signal_length=0,
		unsigned int upsample_factor=1, unsigned int downsample_factor=1,
		double normalized_cutoff_freq=0.5f, unsigned int filter_length=0
	);
	~modulated_signal_correlator();
	const Ipp32fc* Correlate(const Ipp32fc *in_data, unsigned int data_len,
		float freq_shift, int lo_lag, unsigned int corr_len);
	const Ipp32fc* Correlation_Data() const { return xcorr_data_; }
	const Ipp32fc* Resampled_Data() const { return resampled_data_; }
	const int Upsample_Factor() const { return upsample_factor_; }
	const int Downsample_Factor() const { return downsample_factor_; }
protected:
	const Ipp32fc *template_sequence_;
	unsigned int template_length_;
	Ipp32fc *dcvt_data_;
	unsigned int max_dcvt_data_length_;
	Ipp32fc *resampled_data_;
	unsigned int max_resampled_data_length_;
	Ipp32fc *xcorr_data_;
	unsigned int max_xcorr_data_length_;
	rf_phreaker::fir_filter *resampler_;
	unsigned int upsample_factor_;
	unsigned int downsample_factor_;
};
