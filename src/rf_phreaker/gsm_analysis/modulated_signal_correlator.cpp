#include "modulated_signal_correlator.h"


modulated_signal_correlator::modulated_signal_correlator(
	const Ipp32fc* template_samples, unsigned int template_length,
	unsigned int max_signal_length,
	unsigned int upsample_factor, unsigned int downsample_factor,
	double normalized_cutoff_freq, unsigned int filter_length) :
template_sequence_(template_samples),
template_length_(template_length),
dcvt_data_(NULL), resampled_data_(NULL),
xcorr_data_(NULL),
resampler_(NULL),
upsample_factor_(upsample_factor), downsample_factor_(downsample_factor),
max_dcvt_data_length_(0),
max_resampled_data_length_(0),
max_xcorr_data_length_(0)
{
	if ( !template_length || !template_samples )
		throw -1;
	if ( !upsample_factor_ || !downsample_factor_ )
		throw -2;

	if ( !max_signal_length )
		max_dcvt_data_length_ = template_length;
	else
		max_dcvt_data_length_ = max_signal_length;

	// allocate for down-converter and resampler
	if ( upsample_factor_ == downsample_factor_ )
	{
		upsample_factor_ = downsample_factor_ = 1;
		max_resampled_data_length_ = max_dcvt_data_length_;
		resampler_ = new rf_phreaker::fir_filter;
	}
	else
	{
		max_resampled_data_length_ = (max_dcvt_data_length_ * upsample_factor_) /
			downsample_factor_ + 1;
		resampler_ = new rf_phreaker::fir_filter;
		resampler_->set_up_down_factor(upsample_factor_, downsample_factor_);
	}
	resampled_data_ = ippsMalloc_32fc(max_resampled_data_length_);
	if ( !filter_length )
	{
		if ( upsample_factor_ > downsample_factor_ )
			filter_length = upsample_factor_;
		else
			filter_length = downsample_factor_;
		// Here we'll just assume transition BW = .05 if filter length is not given.
		// Using .05 will also ensure the filter length is an odd number,
		// however we should not expect a really sharp filter boundary.
		filter_length = 20 * filter_length + 1;
	}
	// ensure filter_length is odd so that the delay will be an integer num of samples.
	if ( (filter_length % 2) == 0 ) filter_length++;
	resampler_->set_taps(filter_length, upsample_factor_, normalized_cutoff_freq);
	resampler_->set_zero_delay(true);

	// Allocate dcvt_data with additional samples (set to zero) to aid
	// the zero-delay function of the resampler.
	dcvt_data_ = ippsMalloc_32fc(max_dcvt_data_length_ + filter_length);
	ippsZero_32fc(dcvt_data_, max_dcvt_data_length_ + filter_length);
}

modulated_signal_correlator::~modulated_signal_correlator()
{
	ippsFree(dcvt_data_);
	ippsFree(resampled_data_);
	ippsFree(xcorr_data_);
	delete resampler_;
}


const Ipp32fc* modulated_signal_correlator::Correlate(
	const Ipp32fc *in_data, unsigned int data_len,
	float norm_freq_shift, int lo_lag, unsigned int corr_len)
{
	if ( !in_data || !data_len || !corr_len )
		throw -1;

	if ( corr_len > max_xcorr_data_length_ )
	{
		// Re-allocate memory to accomodate the longer length
		ippsFree(xcorr_data_);
		xcorr_data_ = ippsMalloc_32fc(corr_len);
		max_xcorr_data_length_ = corr_len;
	}
	ippsZero_32fc(xcorr_data_, max_xcorr_data_length_);

	if ( data_len > max_dcvt_data_length_ )
	{
		// Re-allocate down-converter memory to accomodate the longer length,
		// and again allocate extra memory to aid the zero-delay filter
		ippsFree(dcvt_data_);
		unsigned int total_len = data_len + resampler_->length();
		dcvt_data_ = ippsMalloc_32fc(total_len);
		ippsZero_32fc(dcvt_data_, total_len);
		max_dcvt_data_length_ = data_len;

		unsigned int new_resamp_length = (max_dcvt_data_length_ * upsample_factor_) /
			downsample_factor_ + 1;
		// Note that it is possible for the dcvt data length to increase
		// without necessarily requiring the resampled length to increase.
		if ( new_resamp_length > max_resampled_data_length_ )
		{
			ippsFree(resampled_data_);
			max_resampled_data_length_ = new_resamp_length;
			resampled_data_ = ippsMalloc_32fc(max_resampled_data_length_);
		}
	}

	// Now that all the memory has been checked and re-allocated as needed,
	// we can proceed to the actual down-conversion and correlation!

	// freq shift to baseband
	float phase = 0.f;
	if ( norm_freq_shift < 0 )
		norm_freq_shift = 1 + norm_freq_shift;
	ippsTone_Direct_32fc(dcvt_data_, data_len, 1.f, norm_freq_shift, &phase, ippAlgHintAccurate);
	ippsMul_32fc_I(in_data, dcvt_data_, data_len);

	// filter / resample
	unsigned int num_iterations = data_len / downsample_factor_;
	//if ( data_len % downsample_factor_ )
	//	num_iterations++;
	resampler_->filter(dcvt_data_, resampled_data_, num_iterations);
	unsigned int resamp_len = num_iterations * upsample_factor_;

	// perform correlation
	// Note the template is assumed to be normalized to a sum of 1,
	// so no additional "length normalization" is needed
	ippsCrossCorr_32fc( template_sequence_, template_length_,
		resampled_data_, resamp_len,
		xcorr_data_, corr_len, lo_lag );

	//// calculate the normalization constant for the decimated data,
	//// i.e. the average RMS voltage
	//Ipp64f avg_rms_voltage;
	//ippsNorm_L2_32fc64f(resampled_data_, resamp_len, &avg_rms_voltage);

	//ippsMagnitude_32fc( xcorr_data_, xcorr_mag_normalized_, corr_len );
	//ippsDivC_32f_I((Ipp32f)avg_rms_voltage, xcorr_mag_normalized_, corr_len);

	return xcorr_data_;
}
