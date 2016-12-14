#pragma once

#include <stdint.h>

#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker
{

class frequency_shifter
{
public:
	frequency_shifter()
		: magnitude_(1)
		, phase_(0)
	{}
	
	~frequency_shifter()
	{}

	void shift_frequency(ipp_32fc_array &signal, int32_t length, double frequency_hz_to_shift, frequency_type sample_rate)
	{
		if(frequency_hz_to_shift == 0)
			return;

		assert(length <= signal.length());

		if(tone_.length() < signal.length())
			tone_.reset(signal.length());

		generate_tone(tone_, length, frequency_hz_to_shift, sample_rate);

		ipp_helper::check_status(ippsMul_32fc(signal.get(), tone_.get(), signal.get(), length));
	}

	void generate_tone(ipp_32fc_array &tone, int32_t length, double frequency_hz_to_shift, frequency_type sample_rate)
	{
		assert(length <= tone.length());

		phase_ = 0;

		float normalized_freq = static_cast<float>(frequency_hz_to_shift / (double)sample_rate);

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
};

}