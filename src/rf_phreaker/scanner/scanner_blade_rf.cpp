#include "rf_phreaker/scanner/scanner_blade_rf.h"
#include "rf_phreaker/scanner/scanner_blade_rf_impl.h"

namespace rf_phreaker { namespace scanner {

scanner_blade_rf::scanner_blade_rf(const scanner_blade_rf_impl *impl)
	: impl_(impl)
{}

scanner_blade_rf& scanner_blade_rf::operator=(const scanner_blade_rf_impl *s)
{
	impl_ = impl_;
	return *this;
}

scanner_blade_rf& scanner_blade_rf::operator=(const scanner_blade_rf &s)
{
	impl_ = s.impl_;
	return *this;
}

hardware scanner_blade_rf::get_hardware() const { return impl_->get_hardware(); }

std::string scanner_blade_rf::scanner_id() const { return impl_->serial(); }
std::string scanner_blade_rf::serial() const { return impl_->serial(); }
int scanner_blade_rf::back_end() const { return impl_->back_end(); }
uint8_t scanner_blade_rf::usb_bus() const { return impl_->usb_bus(); }
uint8_t scanner_blade_rf::usb_address() const { return impl_->usb_address(); }
unsigned int scanner_blade_rf::instance() const { return impl_->instance(); }
//uint64_t scanner_blade_rf::rx_overruns() const { return impl_->rx_overruns(); }
//uint64_t scanner_blade_rf::rx_throughput() const { return impl_->rx_throughput(); } // samples/second
//uint64_t scanner_blade_rf::tx_underruns() const { return impl_->tx_underruns(); }
//uint64_t scanner_blade_rf::tx_throughput() const { return impl_->tx_throughput(); } // samples/second
uint16_t scanner_blade_rf::vctcxo_trim() const { return impl_->vctcxo_trim(); }
int scanner_blade_rf::usb_speed() const { return impl_->usb_speed(); }

uint16_t scanner_blade_rf::blade_rf_version_major() const { return impl_->blade_rf_version_major(); }
uint16_t scanner_blade_rf::blade_rf_version_minor() const { return impl_->blade_rf_version_minor(); }
uint16_t scanner_blade_rf::blade_rf_version_patch() const { return impl_->blade_rf_version_patch(); }
std::string scanner_blade_rf::blade_rf_version_description() const { return impl_->blade_rf_version_description(); }
		
uint16_t scanner_blade_rf::fpga_version_major() const { return impl_->fpga_version_major(); }
uint16_t scanner_blade_rf::fpga_version_minor() const { return impl_->fpga_version_minor(); }
uint16_t scanner_blade_rf::fpga_version_patch() const { return impl_->fpga_version_patch(); }
std::string scanner_blade_rf::fpga_version_description() const { return impl_->fpga_version_description(); }
		
uint16_t scanner_blade_rf::firmware_version_major() const { return impl_->firmware_version_major(); }
uint16_t scanner_blade_rf::firmware_version_minor() const { return impl_->firmware_version_minor(); }
uint16_t scanner_blade_rf::firmware_version_patch() const { return impl_->firmware_version_patch(); }
std::string scanner_blade_rf::firmware_version_description() const { return impl_->firmware_version_description(); }

}}