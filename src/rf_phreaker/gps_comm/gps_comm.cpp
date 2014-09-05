#include "rf_phreaker/gps_comm/gps_comm.h"
#include "rf_phreaker/gps_comm/gps_comm_impl.h"
#include "libbladeRF.h"

namespace rf_phreaker { namespace gps_comm {

gps_comm::gps_comm() : impl_(new gps_comm_impl) {}

gps_comm::~gps_comm() { 
	delete impl_;
}

void gps_comm::init(bladerf *blade) {
	impl_->init(blade);
}

void gps_comm::set_to_spi_comm() {
	impl_->set_to_spi_comm();
}

void gps_comm::set_to_uart_comm() {
	impl_->set_to_uart_comm();
}

rf_phreaker::gps gps_comm::get_latest_gps(){
	return impl_->get_latest_gps();
}

}}