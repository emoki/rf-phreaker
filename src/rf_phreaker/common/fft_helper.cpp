#include "rf_phreaker/common/fft_helper.h"

namespace rf_phreaker {

fft_helper::fft_helper()
	: fft_spec_(nullptr)
	, fft_order_(0)
	, flag_(0) {}

fft_helper::fft_helper(int fft_order, int flag)
	: fft_spec_(nullptr) {
	reset(fft_order, flag);
}

fft_helper::~fft_helper(void) {
	if(fft_spec_)
		ipp_helper::check_status(ippsFFTFree_C_32fc(fft_spec_));
}

void fft_helper::reset_based_on_signal_length(int signal_length) {
	if(signal_length <= 0) 
		throw ipp_error("Unable to determine order for FFT.  Signal length is invalid.");

	int order = static_cast<int>(log10(signal_length) / log10(2.0));
	
	if(abs(pow(2, order) - signal_length) > .0001)
		throw ipp_error("Zero padding the fft is not currently supported.  Signal length must be changed to match order.");

	reset(order, IPP_FFT_DIV_FWD_BY_N);
}

void fft_helper::reset(int fft_order, int flag) {
	if(fft_order_ == fft_order && flag == flag_ && fft_spec_ != nullptr)
		return;

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

void fft_helper::fft_forward(const ipp_32fc_array &src, ipp_32fc_array &dst) {
	ipp_helper::check_status(ippsFFTFwd_CToC_32fc(src.get(), dst.get(), fft_spec_, internal_buffer_.get()));
}

void fft_helper::fft_inverse(const ipp_32fc_array &src, ipp_32fc_array &dst) {
	ipp_helper::check_status(ippsFFTInv_CToC_32fc(src.get(), dst.get(), fft_spec_, internal_buffer_.get()));
}

void fft_helper::fft_shift(ipp_32fc_array &src_dst) {
	int tmp_length = (int)(src_dst.length() / 2.0);

	// Account for odd array sizes.
	int odd_component = 0;
	if(tmp_length - src_dst.length() / 2.0 > .5)
		odd_component = 1;

	if(tmp_length + 1 > fft_shift_buffer_.length())
		fft_shift_buffer_.reset(tmp_length + 1);

	ipp_helper::check_status(ippsCopy_32fc(src_dst.get(), fft_shift_buffer_.get(), tmp_length + odd_component));
	ipp_helper::check_status(ippsCopy_32fc((src_dst.get() + tmp_length + odd_component), src_dst.get(), tmp_length));
	ipp_helper::check_status(ippsCopy_32fc(fft_shift_buffer_.get(), src_dst.get() + tmp_length + odd_component, tmp_length + odd_component));
}

void fft_helper::inverse_fft_shift(ipp_32fc_array &src_dst) {
	int tmp_length = (int)(src_dst.length() / 2.0);

	// Account for odd array sizes.
	int odd_component = 0;
	if(tmp_length - src_dst.length() / 2.0 > .5)
		odd_component = 1;

	if(tmp_length + 1 > fft_shift_buffer_.length())
		fft_shift_buffer_.reset(tmp_length + 1);

	ipp_helper::check_status(ippsCopy_32fc(src_dst.get(), fft_shift_buffer_.get(), tmp_length));
	ipp_helper::check_status(ippsCopy_32fc((src_dst.get() + tmp_length), src_dst.get(), tmp_length + odd_component));
	ipp_helper::check_status(ippsCopy_32fc(fft_shift_buffer_.get(), src_dst.get() + tmp_length, tmp_length));
}

}