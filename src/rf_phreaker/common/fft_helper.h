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
	void fft_shift(ipp_32f_array &src_dst);
	// Template doesn't currently work unless we export it across the DLL boundaries.
	//template<typename Data>
	//void fft_shift(Data &src_dst) {
		//int tmp_length = (int)(src_dst.length() / 2.0);

		//// Account for odd array sizes.
		//int odd_component = 0;
		//if(tmp_length - src_dst.length() / 2.0 > .5)
		//	odd_component = 1;

		//auto buffer = get_fft_shift_buffer<Data>();

		//if(tmp_length + 1 > buffer.length())
		//	buffer.reset(tmp_length + 1);

		//copy(src_dst.get(), buffer.get(), tmp_length + odd_component);
		//copy(src_dst.get() + tmp_length + odd_component, src_dst.get(), tmp_length);
		//copy(buffer.get(), src_dst.get() + tmp_length + odd_component, tmp_length + odd_component);
	//}
	
	void inverse_fft_shift(ipp_32fc_array &src_dst);

	void copy(Ipp32fc *src, Ipp32fc* dst, int length) {
		ipp_helper::check_status(ippsCopy_32fc(src, dst, length));
	}

	void copy(Ipp32f *src, Ipp32f* dst, int length) {
		ipp_helper::check_status(ippsCopy_32f(src, dst, length));
	}
private:
	template<typename Data>
	Data& get_fft_shift_buffer();

	int fft_order_;

	int flag_;

	IppsFFTSpec_C_32fc *fft_spec_; 

	ipp_array<Ipp8u> internal_buffer_; 

	ipp_32fc_array fft_shift_buffer_fc_;
	ipp_32f_array fft_shift_buffer_f_;
};

template<>
inline ipp_32fc_array& fft_helper::get_fft_shift_buffer<>() {
	return fft_shift_buffer_fc_;
}
template<>
inline ipp_32f_array& fft_helper::get_fft_shift_buffer<>() {
	return fft_shift_buffer_f_;
}

}