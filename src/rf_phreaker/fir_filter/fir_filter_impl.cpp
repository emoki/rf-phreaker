#include "rf_phreaker/fir_filter/fir_filter_impl.h"
#include "rf_phreaker/ipp_custom/ipp.h"
#include "rf_phreaker/common/exception_types.h"
#include <boost/math/common_factor.hpp>
#include <cmath>
#include <algorithm>

using namespace rf_phreaker;


fir_filter_impl::fir_filter_impl() 
	: m_State(NULL)
	, m_DelayLine(NULL)
	, m_Length(0)
	, m_DelayLen(0)
	, m_ZeroDelay(false)
	, m_InputDelay(0)
	, is_multi_rate(false)
	, m_UpFactor(1)
	, m_DownFactor(1)
	, m_UpPhase(0)
	, m_DownPhase(0)
{}

//fir_filter_impl::fir_filter_impl(int upFactor, int downFactor) 
//	: m_State(NULL)
//	, m_DelayLine(NULL)
//	, m_Length(0)
//	, m_DelayLen(0)
//	, m_ZeroDelay(false)
//	, m_InputDelay(0)
//	, m_UpPhase(0)
//	, m_DownPhase(0)
//{
//	set_up_down_factor(upFactor, downFactor);
//}

fir_filter_impl::fir_filter_impl(frequency_type original_sampling_rate, frequency_type new_sampling_rate)
: m_State(NULL)
, m_DelayLine(NULL)
, m_Length(0)
, m_DelayLen(0)
, m_ZeroDelay(false)
, m_InputDelay(0)
, is_multi_rate(false)
, m_UpPhase(0)
, m_DownPhase(0)
{
	set_up_down_factor_based_on_sampling_rates(original_sampling_rate, new_sampling_rate);
}

fir_filter_impl::~fir_filter_impl()
{
	ippsFIRFree_32fc(m_State); ippsFree(m_DelayLine); 
}

void fir_filter_impl::set_up_down_factor_based_on_sampling_rates(frequency_type original_sampling_rate, frequency_type new_sampling_rate)
{
	if(original_sampling_rate % new_sampling_rate == 0) {
		set_up_down_factor(1, (int)(original_sampling_rate / new_sampling_rate));
	}
	else if(new_sampling_rate % original_sampling_rate == 0) {
		set_up_down_factor((int)(new_sampling_rate / original_sampling_rate), 1);
	}
	else {
		auto lcm = boost::math::lcm(original_sampling_rate, new_sampling_rate);
		set_up_down_factor(static_cast<int>(lcm / original_sampling_rate), static_cast<int>(lcm / new_sampling_rate));
	}
}

void fir_filter_impl::set_up_down_factor(int up_factor, int down_factor)
{
	m_UpFactor = up_factor;
	m_DownFactor = down_factor;

	if((m_UpFactor>0xFFFF) || (m_DownFactor>0xFFFF))
		throw std::invalid_argument("up/down factors must be < 0xFFFF");

	if(m_UpFactor == 1 && m_DownFactor == 1)
		is_multi_rate = false;
	else
		is_multi_rate = true;
}

void fir_filter_impl::set_zero_delay(bool zeroDelay)
{
	m_ZeroDelay = zeroDelay;
}

int fir_filter_impl::set_taps(int length, double normFactor, double norm_cutoff_freq)
{
	if(length < 0) {
		length = std::max(m_UpFactor, m_DownFactor) * 20;
		if(length % 2 == 0)
			length += 1;
	}
	if ( length < 5 ) throw std::invalid_argument("fir_filter_impl::SetTaps length < 5, not allowed when specifying cut-off frequency.");

	// Rule of thumb for norm cutoff freq is 1 / max(up, down).  We mulitple by .5 because IPP specifies the cutoff freq 
	// has to be 0 to 0.5.
	if(norm_cutoff_freq <= 0.0)
		norm_cutoff_freq = std::min(.49, (1.0 / std::max(m_UpFactor, m_DownFactor)) * .5);

	Ipp64f* pTmpTaps = ippsMalloc_64f(length);
	if ( pTmpTaps == NULL ) return _WIF_MEMORY_ALLOCATION;
	ippsFIRGenLowpass_64f((Ipp64f)norm_cutoff_freq, pTmpTaps, length, /*ippWinBlackman*/ippWinHamming, ippFalse);
	if ( normFactor != 1.0 )
	{
		ippsMulC_64f_I( (Ipp64f)normFactor, pTmpTaps, length );
	}
	int returnVal = set_taps(pTmpTaps, length);
	ippsFree(pTmpTaps);
	return returnVal;
}

int fir_filter_impl::set_taps(const Ipp32fc *taps, int length)
{
	if ( taps == NULL ) throw std::invalid_argument("fir_filter_impl::SetTaps null pointer input.");
	if ( length == 0 ) throw std::invalid_argument("fir_filter_impl::SetTaps length==0");

	if ( length == m_Length )
	{
		// just set the taps w/o re-allocating
		ippsFIRSetTaps_32fc(taps, m_State);
		return _WIF_NO_ERROR;
	}

	// else we are re-sizing the filter, so free it first, then re-allocate
	ippsFIRFree_32fc(m_State);

	m_Length = length;
	return this->init_state(taps);
}

int fir_filter_impl::set_taps(const double *taps, int length)
{
	if ( taps == NULL ) throw std::invalid_argument("fir_filter_impl::SetTaps null pointer input.");
	if ( length == 0 ) throw std::invalid_argument("fir_filter_impl::SetTaps length==0");

	Ipp32fc* pTmpTaps = ippsMalloc_32fc(length);
	if ( pTmpTaps == NULL ) return _WIF_MEMORY_ALLOCATION;

	for ( int i=0; i<length; i++ )
	{
		pTmpTaps[i].re = (Ipp32f)taps[i];
		pTmpTaps[i].im = 0;
	}

	int returnVal = set_taps(pTmpTaps, length);
	ippsFree(pTmpTaps);
	return returnVal;
}

int fir_filter_impl::init_state(const Ipp32fc* taps)
{
	m_DelayLen = ( m_Length + m_UpFactor - 1 ) / m_UpFactor;
	unsigned int filtDelay = m_Length / 2;
	m_InputDelay = static_cast<unsigned int>( ceil((double)filtDelay / (double)m_UpFactor) );
	m_UpPhase = m_InputDelay * m_UpFactor - filtDelay;
	m_DownPhase = 0;

	ippsFree(m_DelayLine);
	m_DelayLine = ippsMalloc_32fc(m_DelayLen);
	if ( m_DelayLine == NULL ) throw rf_phreaker::filter_error("fir_filter_impl::InitState null pointer result after allocating delay line.");

	if ( is_multi_rate )
	{
		if ( ippsFIRMRInitAlloc_32fc(&m_State, taps, m_Length,
			m_UpFactor, m_UpPhase, m_DownFactor, m_DownPhase, NULL) != ippStsNoErr )
		{
			throw rf_phreaker::filter_error("fir_filter_impl::InitState error in FIRMRInitAlloc.");
		}
	}
	else
	{
		if ( ippsFIRInitAlloc_32fc(&m_State, taps, m_Length, NULL) != ippStsNoErr )
		{
			throw rf_phreaker::filter_error("fir_filter_impl::InitState error in FIRInitAlloc.");
		}
	}

	return _WIF_NO_ERROR;
}


int fir_filter_impl::filter(Ipp32fc *in, int numIters) const
{
	// TODO: note that this doesn't work with ZeroDelay!!!!
	if ( m_ZeroDelay ) throw rf_phreaker::filter_error("fir_filter_impl::Filter in-place filtering not allowed with a zero-delay filter");
	if ( ippsFIR_32fc_I(in, numIters, m_State) != ippStsNoErr )
		throw rf_phreaker::filter_error("fir_filter_impl::Filter error in ippsFIR in-place filter operation");
	return _WIF_NO_ERROR;
}

int fir_filter_impl::filter(const Ipp32fc *in, Ipp32fc *out, int numIters) const
{
	ippsZero_32fc(m_DelayLine, m_DelayLen);
	if ( m_ZeroDelay )
	{
		ippsFlip_32fc(in, m_DelayLine, m_InputDelay);
		in = in + m_InputDelay;
	}
	ippsFIRSetDlyLine_32fc(m_State, m_DelayLine);

	if ( ippsFIR_32fc(in, out, numIters, m_State) != ippStsNoErr )
		throw rf_phreaker::filter_error("fir_filter_impl::Filter error in ippsFIR filter operation");
	return _WIF_NO_ERROR;
}

int fir_filter_impl::filter(const Ipp32fc *in, int num_input_samples_to_filter,
		Ipp32fc *out, int num_samples_output_buffer_capacity,
		int& num_output_filtered_samples) const
{
	num_output_filtered_samples = num_output_samples_required(num_input_samples_to_filter);
	if (num_output_filtered_samples == 0)
		return _WIF_LENGTH_ERROR;
	if (num_samples_output_buffer_capacity < num_output_filtered_samples)
	{
		num_output_filtered_samples = 0;
		throw rf_phreaker::filter_error("fir_filter_impl::Filter insufficient output buffer capacity.");
	}

	int numIters = num_iterations_required(num_input_samples_to_filter);
	return(filter(in, out, numIters));
}

int fir_filter_impl::num_input_samples_required(int num_output_samples_desired) const
{
	int num_iterations = (num_output_samples_desired / m_UpFactor);
	if ( (num_output_samples_desired % m_DownFactor) > 0 )
		num_iterations++;
	return (num_iterations * m_DownFactor) + (m_ZeroDelay ? m_InputDelay : 0);
}

int fir_filter_impl::num_output_samples_required(int num_input_samples_desired) const
{
	int num_useable_samples = num_input_samples_desired;
	if (m_ZeroDelay)
	{
		if (num_input_samples_desired <= m_InputDelay)
			return 0;
		else 
			num_useable_samples -= m_InputDelay;
	}

	int num_iterations = num_useable_samples / m_DownFactor;	
	return num_iterations * m_UpFactor;
}

int fir_filter_impl::num_iterations_required(int num_input_samples_desired) const
{
	return num_output_samples_required(num_input_samples_desired)/m_UpFactor;
}
