#pragma once

#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/scanner/measurement_info.h"

namespace rf_phreaker { namespace processing {

class basic_data_wrap
{
public:
	basic_data_wrap(const scanner::measurement_info &info) 
	{		
		internal_.carrier_signal_level_ = 1000;
		internal_.carrier_bandwidth_ = info.bandwidth();
		internal_.carrier_frequency_ = info.frequency();
		internal_.collection_round_ = info.collection_round();
		internal_.status_flags_ = 0;
		internal_.time_ = info.time_ns();
	}

	basic_data internal_;
};


}}