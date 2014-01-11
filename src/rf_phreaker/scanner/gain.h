#pragma once

#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker { namespace scanner {

class gain
{
public:

	static packet_container get_default_gain(rf_phreaker::frequency_type freq);


};

}}