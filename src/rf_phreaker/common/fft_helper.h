#pragma once

#include <vector>
#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/moving_window_calculator.h"

namespace rf_phreaker {

class fft_helper
{
public:
	fft_helper();

	fft_helper(int fft_order, int flag = IPP_FFT_DIV_BY_SQRTN);

	~fft_helper();

	void reset_based_on_signal_length(int signal_length);

	void reset(int fft_order, int flag);

	void fft_forward(const Ipp32fc *src, Ipp32fc *dst);

	void fft_inverse(const Ipp32fc *src, Ipp32fc *dst);

	void fft_forward(const ipp_32fc_array &src, ipp_32fc_array &dst);

	void fft_inverse(const ipp_32fc_array &src, ipp_32fc_array &dst);

	void fft_shift(ipp_32fc_array &src_dst);
	
	void inverse_fft_shift(ipp_32fc_array &src_dst);

private:
	int fft_order_;

	int flag_;

	IppsFFTSpec_C_32fc *fft_spec_; 

	ipp_array<Ipp8u> internal_buffer_; 

	ipp_32fc_array fft_shift_buffer_;
};

}