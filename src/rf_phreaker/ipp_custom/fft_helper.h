#pragma once

#include "rf_phreaker/ipp_custom/ipp_array.h"

class fft_helper
{
public:
	fft_helper(int fft_order = 0, int flag = IPP_FFT_DIV_BY_SQRTN);

	~fft_helper();

	void reset(int fft_order, int flag);

	void fft_forward(ipp_32fc_array &src, ipp_32fc_array &dst);

	void fft_inverse(ipp_32fc_array &src, ipp_32fc_array &dst);

private:
	int fft_order_;

	int flag_;

	IppsFFTSpec_C_32fc *fft_spec_; 

	ipp_array<Ipp8u> internal_buffer_; 
};

