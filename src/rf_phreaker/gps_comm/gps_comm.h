#pragma once

#include "rf_phreaker/common/measurements.h"

struct bladerf;

namespace rf_phreaker { namespace gps_comm {

class gps_comm_impl;

class gps_comm 
{
public:
	gps_comm();
	
	~gps_comm();

	void init(bladerf *comm, bool use_spi);

	void power_off();

	rf_phreaker::gps get_latest_gps();

private:
	gps_comm_impl *impl_;
};

}}