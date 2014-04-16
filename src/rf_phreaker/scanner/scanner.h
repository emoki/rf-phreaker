#pragma once

#include "rf_phreaker/common/measurements.h"

namespace rf_phreaker { namespace scanner {


class scanner
{
public:
	virtual hardware get_hardware() const = 0;
	virtual int get_frequency_correction_value() const = 0;
	virtual time_t get_frequency_correction_date() const = 0;
};


}}