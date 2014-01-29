#include "rf_phreaker/common/fft_helper.h"


fft_helper::fft_helper(int fft_order, int flag)
: fft_spec_(0)
{
	reset(fft_order, flag);
}


fft_helper::~fft_helper(void)
{
		ipp_helper::check_status(ippsFFTFree_C_32fc(fft_spec_));
}

void fft_helper::reset(int fft_order, int flag)
{
	flag_ = flag;
	fft_order_ = fft_order;

	assert(fft_order_ >= 0 && fft_order_ <= 21);

	assert(flag == IPP_FFT_DIV_FWD_BY_N ||
		flag == IPP_FFT_DIV_INV_BY_N ||
		flag == IPP_FFT_DIV_BY_SQRTN ||
		flag == IPP_FFT_NODIV_BY_ANY);

	if(fft_spec_)
		ipp_helper::check_status(ippsFFTFree_C_32fc(fft_spec_));

	ipp_helper::check_status(ippsFFTInitAlloc_C_32fc(&fft_spec_, fft_order_, flag, ippAlgHintAccurate));

	int buf_size = 0;

	ipp_helper::check_status(ippsFFTGetBufSize_C_32fc(fft_spec_, &buf_size));

	internal_buffer_.reset(buf_size);
}

void fft_helper::fft_forward(ipp_32fc_array &src, ipp_32fc_array &dst)
{
	ipp_helper::check_status(ippsFFTFwd_CToC_32fc(src.get(), dst.get(), fft_spec_, internal_buffer_.get()));
}

void fft_helper::fft_inverse(ipp_32fc_array &src, ipp_32fc_array &dst)
{
	ipp_helper::check_status(ippsFFTInv_CToC_32fc(src.get(), dst.get(), fft_spec_, internal_buffer_.get()));
}

