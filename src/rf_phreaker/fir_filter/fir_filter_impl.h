#pragma once

#include <stdexcept>
#include <rf_phreaker/ipp_custom/ipp.h>
#include "rf_phreaker/common/common_types.h"

#define _WIF_NO_ERROR			0
#define _WIF_MEMORY_ALLOCATION	-1
#define _WIF_INVALID_POINTER	-2
#define _WIF_LENGTH_ERROR		-3
#define _WIF_FILTERING_ERROR	-4
#define _WIF_INIT_STATE_ERROR	-5


namespace rf_phreaker {


// Provides for channel filtering of a signal.
class fir_filter_impl
{
public:
	fir_filter_impl();

	//fir_filter_impl(int upFactor, int downFactor);

	fir_filter_impl(frequency_type original_sampling_rate, frequency_type new_sampling_rate);

	virtual ~fir_filter_impl();

	int length() const { return m_Length; };

	int num_samples_delay() const { return m_InputDelay; };

	void set_up_down_factor_based_on_sampling_rates(frequency_type original_sampling_rate, frequency_type new_sampling_rate);

	void set_up_down_factor(int up_factor, int down_factor);

	void set_zero_delay(bool zero_delay);

	int set_taps(int length, double norm_factor, double norm_cutoff_freq);

	int set_taps(const Ipp32fc *taps, int length);

	int set_taps(const double *taps, int length);

	int filter(Ipp32fc *in, int numIters) const;

	int filter(const Ipp32fc *in, Ipp32fc *out, int num_iters) const;

	virtual int filter(const Ipp32fc *in, int num_input_samples_to_filter,
		Ipp32fc *out, int num_samples_output_buffer_capacity,
		int& num_output_filtered_samples) const;

	virtual int num_input_samples_required(int num_output_samples_desired) const;

	virtual int num_output_samples_required(int num_input_samples_desired) const;

	virtual int ensure_output_samples_large_enough(int num_output_samples_desired) const;

	virtual int num_iterations_required(int num_input_samples_desired) const;

	int up_factor() const { return m_UpFactor; }

	int down_factor() const { return m_DownFactor; }

protected:
	virtual int init_state(const Ipp32fc *taps);

	IppsFIRState_32fc* m_State;
	Ipp32fc *m_DelayLine;
	int m_Length;
	int m_DelayLen;
	bool m_ZeroDelay;
	int m_InputDelay;

	bool is_multi_rate;
	int m_UpFactor;
	int m_DownFactor;
	int m_UpPhase;
	int m_DownPhase;

};


}