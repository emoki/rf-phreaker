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

	void init(bladerf *comm);

	void set_to_spi_comm();

	void set_to_uart_comm();

	rf_phreaker::gps get_latest_gps();

private:
	gps_comm_impl *impl_;
};

}}