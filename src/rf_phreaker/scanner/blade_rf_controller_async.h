#pragma once

#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/concurrent.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"

namespace rf_phreaker { namespace scanner {

class blade_rf_controller_async : public scanner_controller_interface
{
public:
	blade_rf_controller_async(comm_type comm = USB_BLADE_RF)
		: controller_(comm)
	{}

	virtual std::future<std::vector<comm_info_ptr>> list_available_scanners()
	{
		return controller_([=] (blade_rf_controller &c) {
			return c.list_available_scanners();
		});
	}

	virtual std::future<void> open_scanner(const scanner_serial_type &id)
	{
		return controller_([&](blade_rf_controller &c) {
			c.open_scanner(id);
		});
	}
	
	virtual std::future<void> close_scanner()
	{
		return controller_([=](blade_rf_controller &c) {
			c.close_scanner();
		});
	}

	virtual std::future<void> do_initial_scanner_config(const scanner_settings &settings = blade_settings()) {
		return controller_([&](blade_rf_controller &c) {
			c.do_initial_scanner_config(settings);
		});
	}

	virtual std::future<void> refresh_scanner_info() {
		return controller_([=](blade_rf_controller &c) {
			c.refresh_scanner_info();
		});
	}

	virtual std::future<const scanner*> get_scanner()
	{
		return controller_([=](blade_rf_controller &c) {
			return c.get_scanner();
		});
	}

	virtual std::future<void> write_vctcxo_trim_and_update_calibration(frequency_type carrier_freq, frequency_type freq_shift)
	{
		return controller_([=](blade_rf_controller &c) {
			return c.write_vctcxo_trim_and_update_calibration(carrier_freq, freq_shift);
		});
	}

	virtual std::future<void> update_vctcxo_trim(frequency_type carrier_freq, frequency_type freq_shift)
	{
		return controller_([=](blade_rf_controller &c) {
			return c.update_vctcxo_trim(carrier_freq, freq_shift);
		});
	}

	virtual std::future<rf_phreaker::gps> get_gps_data()
	{
		return controller_([=](blade_rf_controller &c) {
			return c.get_gps_data();
		});
	}

	virtual std::future<measurement_info> get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, frequency_type sampling_rate = 0)
	{
		return controller_([=] (blade_rf_controller &c) {
			return c.get_rf_data_use_auto_gain(freq, time_ns, bandwidth, sampling_rate);
		});
	}

	virtual std::future<void> write_license(const license &license)
	{
		return controller_([=](blade_rf_controller &c) {
			return c.write_license(license);
		});
	}

	virtual std::future<void> set_log_level(int level) {
		return controller_([=](blade_rf_controller &c) {
			return c.set_log_level(level);
		});
	}

private:
	rf_phreaker::concurrent<blade_rf_controller> controller_;
};





}}