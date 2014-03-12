#pragma once

#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/common/common_types.h"
#include "ipp.h"



namespace rf_phreaker { namespace scanner {

// lna gain (MAX, MID, BYPASS)
// vga1 (dB, min = 5, max = 30)
// vga2 (dB, min = 0, ~max = 30)
class gain_type
{
public:
	gain_type() : lna_gain_(lms::LNA_MAX), rxvga1_(30), rxvga2_(0)
	{}

	gain_type(lms::lna_gain_enum lna_gain, int rxvga1, int rxvga2)
		: lna_gain_(lna_gain)
		, rxvga1_(rxvga1)
		, rxvga2_(rxvga2)
	{}

	lms::lna_gain_enum lna_gain_;
	int rxvga1_;
	int rxvga2_;
};

}}