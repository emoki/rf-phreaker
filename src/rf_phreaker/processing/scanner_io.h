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
	rf_phreaker::scanner::measurement_info operator()(const collection_info &cp){
		if(cp.freq_ == 0)
			throw std::logic_error("Error, the requested frequency is 0.");

        auto future_data = sc_->get_rf_data(cp.freq_, cp.time_ns_, cp.bandwidth_,cp.sampling_rate_);

		//auto future_status = future_data.wait_for(std::chrono::seconds(2));

		//if(!future_data.valid())
		//	throw comm_error("Future is not valid within tbb flow graph.");

		//if(future_status == std::future_status::timeout) {
		//	throw comm_error("Time out occurred during scanner io within tbb flow graph.");
		//}

		return future_data.get();
	}
private:
    rf_phreaker::scanner::scanner_controller_interface *sc_;
};

}}
