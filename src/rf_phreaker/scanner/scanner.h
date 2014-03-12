#pragma once

#include "rf_phreaker/common/measurements.h"

namespace rf_phreaker { namespace scanner {


class scanner
{
public:
	virtual hardware get_hardware() const = 0;
};


}}