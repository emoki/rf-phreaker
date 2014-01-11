#pragma once

#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker { namespace scanner {

class rf_switch_conversion
{
public:
	rf_switch_conversion(void);

	~rf_switch_conversion(void);

	packet_container get_rf_switches(rf_phreaker::frequency_type freq);

};

}}