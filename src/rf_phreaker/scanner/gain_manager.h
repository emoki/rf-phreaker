#pragma once

#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/gain.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/common/common_types.h"
#include "ipp.h"



namespace rf_phreaker { namespace scanner {

class gain_manager
{
public:
	class gain_history
	{
	public:
		gain_history(const measurement_info &meas)
			: freq_(meas.frequency())
			, bw_(meas.bandwidth())
			, gain_(meas.gain())
			, max_adc_(0)
		{}

		rf_phreaker::frequency_type freq_;
		rf_phreaker::bandwidth_type bw_;
		gain_type gain_;
		Ipp32f max_adc_;
	};

	gain_type calculate_gain(const measurement_info &meas)
	{
		gain_history history(meas);
		gain_type gain;
		return gain;
	}
};

}}