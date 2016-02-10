#pragma once

#include <memory>
#include <string>
#include <mutex>
#include "tbb/task_scheduler_init.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_handler.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_handler_protobuf.h"
#include "rf_phreaker/scanner/blade_rf_controller_async.h"
#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/processing/frequency_correction_graph.h"
#include "rf_phreaker/processing/gps_graph.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/operating_band_range_specifier.h"


typedef struct rp_device
{
	rp_device(rf_phreaker::scanner::comm_type comm = rf_phreaker::scanner::USB_BLADE_RF)
		: async_(comm) {}
	rf_phreaker::scanner::blade_rf_controller_async async_;
} rp_device;

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

	rp_status list_devices(rp_serial *serials, int *num_serials);

	rp_status connect_device(rp_serial serial, rp_device **device);

	rp_status disconnect_device(rp_device *device);

	bool is_device_open(rp_device *device);

	rp_status get_device_info(rp_device *device, rp_device_info *device_info);

	rp_status add_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band);

	//rp_status add_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel);

	rp_status remove_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band);

	rp_status add_sweep_operating_band(rp_device *device, rp_operating_band band);

	rp_status remove_sweep_operating_band(rp_device *device, rp_operating_band band);

	rp_status remove_collection_frequencies_and_bands(rp_device *device);

	rp_status start_collection(rp_device *device, const rp_collection_info *info);

	rp_status stop_collection(rp_device *device);

	rp_status get_gps_data(rp_device *device, rp_gps gps);

	rp_status get_iq_data_using_auto_gain(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, 
		rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, rp_raw_data *raw_data);

	rp_status get_iq_data(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, 
		rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, int32_t gain_db, rp_raw_data *raw_data);

	rp_status update_license(rp_device *device, const char *filename);

private:
	void general_checks(rp_device *device);

	void check_calibration(hardware hw, frequency_type freq);

	processing::collection_info_containers::iterator add_sweep(specifier sweep, specifier decode);

	void rf_phreaker_impl::remove_sweep(operating_band band, specifier sweep);

	bool is_within_freq_paths(frequency_type f);

	void read_settings();

	bool check_rp_device(rp_device* d) {
		for(auto i : scanners_) {
			if(i.get() == d)
				return true;
		};
		return false;
	}

	void message_handling(const std::string &str, int type, int code);

	void error_handling(const std::string &str, int type, int code);

	bool is_initialized_;

	rf_phreaker::settings config_;

	// Order of components is important when destructing.
	std::unique_ptr<rf_phreaker_handler> handler_;
	std::unique_ptr<rf_phreaker_handler_protobuf> handler_pb_;

	std::unique_ptr<processing::processing_graph> processing_graph_;

	std::unique_ptr<processing::gps_graph> gps_graph_;

	std::unique_ptr<processing::frequency_correction_graph> frequency_correction_graph_;

	std::unique_ptr<processing::data_output_async> data_output_;

	typedef std::vector<std::shared_ptr<rp_device>> scanners_type;
	scanners_type scanners_;

	operating_band_range_specifier operating_bands_;

	processing::collection_info_containers containers_;

	std::unique_ptr<logger> logger_;

	std::recursive_mutex mutex_;

	tbb::task_scheduler_init tbb_task_scheduler_;

	rp_callbacks *callbacks_;

	protobuf::update_pb update_;
	
	std::mutex update_mutex_;
};

}}