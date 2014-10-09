#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_impl.h"

using namespace rf_phreaker::api;

RP_LIBEXPORT(rp_status) rp_initialize(rp_callbacks *callbacks) {
	return rf_phreaker_impl::instance().initialize(callbacks);
}

RP_LIBEXPORT(rp_status) rp_clean_up() { 
	return rf_phreaker_impl::instance().clean_up();
}

RP_LIBEXPORT(rp_status) rp_list_devices(rp_serial_type *serials, int *num_serials) {
	return rf_phreaker_impl::instance().list_devices(serials, num_serials);
}

RP_LIBEXPORT(rp_status) rp_connect_device(const rp_serial_type *serial, rp_device **device) {
	return rf_phreaker_impl::instance().connect_device(serial, device);
}

RP_LIBEXPORT(rp_status) rp_disconnect_device(rp_device *device) {
	return rf_phreaker_impl::instance().disconnect_device(device);
}

RP_LIBEXPORT(rp_status) rp_is_device_open(rp_device *device) {
	return rf_phreaker_impl::instance().is_device_open(device);
}

RP_LIBEXPORT(rp_status) rp_get_device_info(rp_device *device, rp_device_info *device_info) {
	return rf_phreaker_impl::instance().get_device_info(device, device_info);
}

RP_LIBEXPORT(rp_status) rp_add_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band) {
	return rf_phreaker_impl::instance().add_collection_frequency(device, data, freq, band);
}

RP_LIBEXPORT(rp_status) rp_add_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel) {
	return rf_phreaker_impl::instance().add_collection_channel(device, data, channel);
}

RP_LIBEXPORT(rp_status) rp_remove_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band) {
	return rf_phreaker_impl::instance().remove_collection_frequency(device, data, freq, band);
}

RP_LIBEXPORT(rp_status) rp_remove_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel) {
	return rf_phreaker_impl::instance().remove_collection_channel(device, data, channel);
}

RP_LIBEXPORT(rp_status) rp_add_sweep_operating_band(rp_device *device, rp_operating_band band) {
	return rf_phreaker_impl::instance().add_sweep_operating_band(device, band);
}

RP_LIBEXPORT(rp_status) rp_remove_sweep_operating_band(rp_device *device, rp_operating_band band) {
	return rf_phreaker_impl::instance().remove_sweep_operating_band(device, band);
}

RP_LIBEXPORT(rp_status) rp_get_gps_data(rp_device *device, rp_gps gps) {
	return rf_phreaker_impl::instance().get_gps_data(device, gps);
}

RP_LIBEXPORT(rp_status) rp_get_iq_data_using_auto_gain(rp_device *device, rp_frequency_type freq, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, int32_t gain_db) {
	return rf_phreaker_impl::instance().get_iq_data_using_auto_gain(device, freq, time_ns, bandwidth, sampling_rate, gain_db);
}

RP_LIBEXPORT(rp_status) rp_get_iq_data(rp_device *device, rp_frequency_type freq, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate) {
	return rf_phreaker_impl::instance().get_iq_data(device, freq, time_ns, bandwidth, sampling_rate);
}

RP_LIBEXPORT(rp_status) rp_update_license(rp_device *device, const char *filename) {
	return rf_phreaker_impl::instance().update_license(device, filename);
}

RP_LIBEXPORT(const char*) rp_status_message(rp_status status) {
	return rf_phreaker_impl::status_message(status);
}

RP_LIBEXPORT(const char*) rp_build_version() {
	return rf_phreaker_impl::build_version();
}