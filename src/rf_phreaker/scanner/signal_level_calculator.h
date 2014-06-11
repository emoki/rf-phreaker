#pragma once

#include "rf_phreaker/scanner/measurement_info.h"

namespace rf_phreaker { namespace scanner {

class signal_level_calculator
{
public:
	static double calculate_sl(double avg_rms, const measurement_info &info, bool use_rf_board_adj = true)
	{
		if(avg_rms < .0001)
			return -999;
		// Assuming the LNA is maxed.
		return 20.0 * log10(avg_rms) - info.gain().rxvga1_ - (0.96 * info.gain().rxvga2_) + info.blade_adjustment() - (use_rf_board_adj ? info.rf_board_adjustment() : 0);
	}

	static double calculate_sl(double digital_value, int rxvga1, int rxvga2, double blade_adj, double rf_board_adj)
	{
		if(digital_value < .0001)
			return -999;
		// Assuming the LNA is maxed.
		return 20.0 * log10(digital_value) - rxvga1 - (0.96 * rxvga2) + blade_adj - rf_board_adj;
	}
};


}}