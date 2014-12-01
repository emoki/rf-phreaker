#include "rf_phreaker/gps_comm/gps_comm.h"
#include "rf_phreaker/gps_comm/gps_comm_impl.h"
#include "libbladeRF.h"

namespace rf_phreaker { namespace gps_comm {

gps_comm::gps_comm() : impl_(new gps_comm_impl) {}

gps_comm::~gps_comm() { 
	delete impl_;
}

void gps_comm::init(bladerf *blade, bool use_spi) {
	impl_->init(blade, use_spi);
}

void gps_comm::power_off() {
	impl_->power_off();
}

rf_phreaker::gps gps_comm::get_latest_gps(){
	return impl_->get_latest_gps();
}

void gps_comm::initiate_pps_clock_counter(uint8_t samples){
	impl_->initiate_pps_clock_counter(samples);
}

uint32_t gps_comm::read_pps_clock_counter(){
	return impl_->read_pps_clock_counter();
}

}}