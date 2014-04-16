#include "moving_window_calculator.h"
#include <stdexcept>
#include "tbb/parallel_for.h"
#include "tbb/tbb.h"

namespace rf_phreaker {

moving_window_calculator::moving_window_calculator()
: output_length_(0)
, moving_window_length_(0)
{
}

moving_window_calculator::~moving_window_calculator(void)
{
}

void moving_window_calculator::configure(int32_t max_signal_length, int32_t moving_window_length)
{
	if(power_spectrum_.length() != max_signal_length)
		power_spectrum_.reset(max_signal_length);

	if(moving_window_ones_.length() != moving_window_length) 
	{
		moving_window_ones_.reset(moving_window_length);
		ipp_helper::check_status(ippsSet_32f(1, moving_window_ones_.get(), moving_window_ones_.length()));
	}

	output_length_ = max_signal_length - moving_window_length;
	moving_window_length_ = moving_window_length;
}

void moving_window_calculator::calculate_moving_window_of_energy(const ipp_32fc_array &signal, int32_t moving_window_length)
{
	calculate_moving_window_of_energy(signal.get(), signal.length(), moving_window_length);
}

void moving_window_calculator::calculate_moving_window_of_rms(const ipp_32fc_array &signal, int32_t moving_window_length)
{
	calculate_moving_window_of_rms(signal.get(), signal.length(), moving_window_length);
}


void moving_window_calculator::calculate_moving_window_of_energy(const Ipp32fc *signal, int signal_length, int32_t moving_window_length)
{
	configure(signal_length, moving_window_length);

	if(total_energy_.length() < output_length_)
		total_energy_.reset(output_length_);

	IppStatus stat = ippStsNoErr;

	//// Calculate power spectrum 
	//tbb::parallel_for(tbb::blocked_range<int>(0, signal_length, 1), [&](const tbb::blocked_range<int> &r) {
	//	stat = ippsPowerSpectr_32fc(&signal[r.begin()], &power_spectrum_[r.begin()], r.size());
	//	if(stat != ippStsNoErr)
	//		throw std::runtime_error("Error calculating power spectrum.");
	//});
	stat = ippsPowerSpectr_32fc(&signal[0], &power_spectrum_[0], power_spectrum_.length());

	stat = ippsCrossCorr_32f(moving_window_ones_.get(), moving_window_length, power_spectrum_.get(), power_spectrum_.length(), total_energy_.get(), output_length_, 0);
	if(stat != ippStsNoErr)
		throw std::runtime_error("Error crosscorrelating moving window of energy.");
}

void moving_window_calculator::calculate_moving_window_of_rms(const Ipp32fc *signal, int signal_length, int32_t moving_window_length)
{
	calculate_moving_window_of_energy(signal, signal_length, moving_window_length);

	// calculate_moving_window_of_energy has configured all variables except...
	if(rms_.length() < output_length_)
		rms_.reset(output_length_);

	//tbb::parallel_for(tbb::blocked_range<int>(0, output_length_, 1), [&](const tbb::blocked_range<int> &r) {
	//	ipp_helper::check_status(ippsDivC_32f(&total_energy_[r.begin()], (Ipp32f)moving_window_length, &rms_[r.begin()], r.size()));
	//	ipp_helper::check_status(ippsSqrt_32f_I(&rms_[r.begin()], r.size()));
	//});
	ipp_helper::check_status(ippsDivC_32f(&total_energy_[0], (Ipp32f)moving_window_length, &rms_[0], rms_.length()));
	ipp_helper::check_status(ippsSqrt_32f_I(&rms_[0], rms_.length()));
}

}