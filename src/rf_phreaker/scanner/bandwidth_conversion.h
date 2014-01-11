#pragma once

#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker { namespace scanner {

class bandwidth_conversion
{
public:
	static packet_container get_bandwidth_and_enable_lpf(rf_phreaker::bandwidth_type bw);

	static lms_value_type get_bandwidth_and_enable_lpf_value(rf_phreaker::bandwidth_type bw);

	static lms::bandwidth_enum find_lower_bound_bandwidth(rf_phreaker::bandwidth_type bw);

	static rf_phreaker::bandwidth_type convert_to_bandwidth_type(lms::bandwidth_enum bw);

private:
	static const rf_phreaker::bandwidth_type *uint_bandwidths_;
};

}}