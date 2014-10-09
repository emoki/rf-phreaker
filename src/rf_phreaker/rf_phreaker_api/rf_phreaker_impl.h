#pragma once

#include "rf_phreaker\rf_phreaker_api\rf_phreaker_api.h"
#include "rf_phreaker/scanner/blade_rf_controller_async.h"
#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/processing/frequency_correction_graph.h"
#include "rf_phreaker/processing/gps_graph.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/operating_band_range_specifier.h"
#include <memory>
#include <string>
#include <mutex>

namespace rf_phreaker { namespace api { 

class rf_phreaker_impl {
public:
	static rf_phreaker_impl& instance();

	static const char* status_message(rp_status status);

	static const char* build_version();

	rf_phreaker_impl();

	~rf_phreaker_impl();
	
	rp_status initialize(rp_callbacks *callbacks);

	rp_status clean_up();

	rp_status list_devices(rp_serial_type *serials, int *num_serials);

	rp_status connect_device(const rp_serial_type *serial, rp_device **device);

	rp_status disconnect_device(rp_device *device);

	rp_status is_device_open(rp_device *device);

	rp_status get_device_info(rp_device *device, rp_device_info *device_info);

	rp_status add_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band);

	rp_status add_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel);

	rp_status remove_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band);

	rp_status remove_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel);

	rp_status add_sweep_operating_band(rp_device *device, rp_operating_band band);

	rp_status remove_sweep_operating_band(rp_device *device, rp_operating_band band);

	rp_status get_gps_data(rp_device *device, rp_gps gps);

	rp_status get_iq_data_using_auto_gain(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, int32_t gain_db);

	rp_status get_iq_data(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate);

	rp_status update_license(rp_device *device, const char *filename);

private:
	void read_settings();

	bool is_initialized_;

	rf_phreaker::settings config_;

	std::unique_ptr<rf_phreaker::scanner::blade_rf_controller_async> scanner_;

	std::unique_ptr<rf_phreaker::processing::data_output_async> data_output_;

	std::unique_ptr<rf_phreaker::processing::processing_graph> processing_graph_;

	std::unique_ptr<rf_phreaker::processing::gps_graph> gps_graph_;

	std::unique_ptr<rf_phreaker::processing::frequency_correction_graph> frequency_correction_graph_;

	operating_band_range_specifier operating_bands_;

	//std::unique_ptr<rf_phreaker_delegate> delegate_;

	std::unique_ptr<init_log> logger_;

	std::recursive_mutex mutex_;
};

}}