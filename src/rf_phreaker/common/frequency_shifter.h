#pragma once

#include <stdint.h>

#include "rf_phreaker/common/ipp_array.h"

namespace rf_phreaker
{

class frequency_shifter
{
public:
	frequency_shifter(double sample_rate = 4.875e6)
		: sample_rate_(sample_rate)
		, magnitude_(1)
		, phase_(0)
	{}
	
	~frequency_shifter()
	{}

	void shift_frequency(ipp_32fc_array &signal, int32_t length, double frequency_hz_to_shift)
	{
		assert(length <= signal.length());

		if(tone_.length() < signal.length())
			tone_.reset(signal.length());

		generate_tone(tone_, length, frequency_hz_to_shift);

		ipp_helper::check_status(ippsMul_32fc(signal.get(), tone_.get(), signal.get(), length));
	}

	void generate_tone(ipp_32fc_array &tone, int32_t length, double frequency_hz_to_shift)
	{
		assert(length <= tone.length());

		phase_ = 0;

		float normalized_freq = static_cast<float>(frequency_hz_to_shift / sample_rate_);

		if(abs(normalized_freq) > .5)
			throw misc_error("Error generating tone for frequency shift.");

		if(normalized_freq < 0)
			normalized_freq = 1 + normalized_freq;

		ipp_helper::check_status(ippsTone_Direct_32fc(tone.get(), tone.length(), magnitude_,
			normalized_freq, &phase_, ippAlgHintAccurate));
	}

private:

	ipp_32fc_array tone_;

	float magnitude_;

	float phase_;

	double sample_rate_;

	ipp_32fc_array *signal_;
};

}