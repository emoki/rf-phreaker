#pragma once

#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace processing {


class scanner_io
{
public:
    scanner_io(rf_phreaker::scanner::scanner_controller_interface *sc)
		: sc_(sc)
	{}
	rf_phreaker::scanner::measurement_info operator()(const collection_parameters &cp){
		
        auto future_data = sc_->get_rf_data(cp.freq_, cp.time_ms_, cp.bandwidth_,cp.sampling_rate_);

#if _DEBUG
		future_data.wait();
		auto future_status = std::future_status::ready;
#else
		auto future_status = future_data.wait_for(std::chrono::seconds(5));
#endif	
		if(!future_data.valid())
			throw comm_error("Future is not valid while waiting for snapshot to transfer.");

		if(future_status == std::future_status::timeout) {
			// TODO - fix scanner somehow.
			throw comm_error("Time out occurred while waiting for snapshot to transfer.");
		}

		return future_data.get();
	}
private:
    rf_phreaker::scanner::scanner_controller_interface *sc_;
};

}}
