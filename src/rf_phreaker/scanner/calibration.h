#pragma once

#include "rf_phreaker/scanner/gain.h"

namespace rf_phreaker { namespace scanner {

class calibration
{
public:
	double calculate_sl(double avg_rms, gain_type gain)
	{
		if(avg_rms < .0001)
			return -999;
		// TODO - Assuming the LNA is maxed.
		int offset = -30;
		return 20 * log10(avg_rms) - gain.rxvga1_ - gain.rxvga2_ + offset;
	}
};


}}