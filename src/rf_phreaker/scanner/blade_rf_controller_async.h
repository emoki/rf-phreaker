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

	virtual void open_scanner(const scanner_id_type &id) 
	{
		controller_([&](blade_rf_controller &c) {
			c.open_scanner(id);
		});
	}
	
	virtual void close_scanner()
	{
		controller_([=](blade_rf_controller &c) {
			c.close_scanner();
		});
	}

	virtual void do_initial_scanner_config()
	{
		controller_([=](blade_rf_controller &c) {
			c.do_initial_scanner_config();
		});
	}


	//virtual void config_scanner_for_collection(std::vector<rf_phreaker::frequency_type> &freqs) = 0;

	virtual void update_dds()
	{
		controller_([=](blade_rf_controller &c) {
			c.update_dds();
		});
	}

	virtual std::future<const scanner*> get_scanner()
	{
		return controller_([=](blade_rf_controller &c) {
			return c.get_scanner();
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


private:
	rf_phreaker::concurrent<blade_rf_controller> controller_;
};





}}