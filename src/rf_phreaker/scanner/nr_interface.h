#pragma once
#include <string>
#include "libbladeRF.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker { namespace scanner {

void log_if(int status, const std::string &file, int line) {
	LOG_IF(LDEBUG, (status != 0)) << "[" << split_file_name(file) << " L: " << std::to_string(line) << "] NR interface error: "
		<< ::bladerf_strerror(status) << ".";
}

const char * nr_strerror(int error) {
	return ::bladerf_strerror(error);
}

int nr_get_device_list(struct bladerf_devinfo **devices, const std::string &file = __FILE__, int line = __LINE__) {
	return ::bladerf_get_device_list(devices);
}

void nr_free_device_list(struct bladerf_devinfo *devices, const std::string &file = __FILE__, int line = __LINE__) {	::bladerf_free_device_list(devices);
}

int nr_open_with_devinfo(struct bladerf **device, struct bladerf_devinfo *devinfo, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_open_with_devinfo(device, devinfo);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_open(struct bladerf **device, const char *device_identifier, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_open(device, device_identifier);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

void nr_close(struct bladerf *device, const std::string &file = __FILE__, int line = __LINE__) {	::bladerf_close(device);
}

void nr_init_devinfo(struct bladerf_devinfo *info, const std::string &file = __FILE__, int line = __LINE__) {	bladerf_init_devinfo(info);
}

int nr_get_devinfo(struct bladerf *dev, struct bladerf_devinfo *info, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_devinfo(dev, info);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_devinfo_from_str(const char *devstr, struct bladerf_devinfo *info, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_devinfo_from_str(devstr, info);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

bool nr_devinfo_matches(const struct bladerf_devinfo *a, const struct bladerf_devinfo *b, const std::string &file = __FILE__, int line = __LINE__) {	return ::bladerf_devinfo_matches(a, b);
}

bool nr_devstr_matches(const char *dev_str, struct bladerf_devinfo *info, const std::string &file = __FILE__, int line = __LINE__) {	return ::bladerf_devstr_matches(dev_str, info);
}

const char * nr_backend_str(bladerf_backend backend, const std::string &file = __FILE__, int line = __LINE__) {	return ::bladerf_backend_str(backend);
}

int nr_enable_module(struct bladerf *dev, bladerf_module m, bool enable, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_enable_module(dev, m, enable);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_loopback(struct bladerf *dev, bladerf_loopback l, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_loopback(dev, l);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_loopback(struct bladerf *dev, bladerf_loopback *l, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_loopback(dev, l);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_sample_rate(struct bladerf *dev, bladerf_module module, unsigned int rate, unsigned int *actual, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_sample_rate(dev, module, rate, actual);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_rational_sample_rate(struct bladerf *dev, bladerf_module module, struct bladerf_rational_rate *rate, struct bladerf_rational_rate *actual, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_rational_sample_rate(dev, module, rate, actual);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_sampling(struct bladerf *dev, bladerf_sampling sampling, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_sampling(dev, sampling);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_sampling(struct bladerf *dev, bladerf_sampling *sampling, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_sampling(dev, sampling);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_sample_rate(struct bladerf *dev, bladerf_module module, unsigned int *rate, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_sample_rate(dev, module, rate);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_rational_sample_rate(struct bladerf *dev, bladerf_module module, struct bladerf_rational_rate *rate, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_rational_sample_rate(dev, module, rate);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_correction(struct bladerf *dev, bladerf_module module, bladerf_correction corr, int16_t value, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_correction(dev, module, corr, value);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_correction(struct bladerf *dev, bladerf_module module, bladerf_correction corr, int16_t *value, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_correction(dev, module, corr, value);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

//int nr_set_txvga2(struct bladerf *dev, int gain, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_set_txvga2(dev, gain);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}
//
//int nr_get_txvga2(struct bladerf *dev, int *gain, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_get_txvga2(dev, gain);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}
//
//int nr_set_txvga1(struct bladerf *dev, int gain, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_set_txvga1(dev, gain);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}
//
//int nr_get_txvga1(struct bladerf *dev, int *gain, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_get_txvga1(dev, gain);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}
//
//int nr_set_tx_gain(struct bladerf *dev, int gain, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_set_tx_gain(dev, gain);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}

int nr_set_lna_gain(struct bladerf *dev, bladerf_lna_gain gain, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_lna_gain(dev, gain);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_lna_gain(struct bladerf *dev, bladerf_lna_gain *gain, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_lna_gain(dev, gain);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_rxvga1(struct bladerf *dev, int gain, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_rxvga1(dev, gain);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_rxvga1(struct bladerf *dev, int *gain, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_rxvga1(dev, gain);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_rxvga2(struct bladerf *dev, int gain, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_rxvga2(dev, gain);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_rxvga2(struct bladerf *dev, int *gain, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_rxvga2(dev, gain);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_gain(struct bladerf *dev, bladerf_module mod, int gain, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_gain(dev, mod, gain);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_bandwidth(struct bladerf *dev, bladerf_module module, unsigned int bandwidth, unsigned int *actual, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_bandwidth(dev, module, bandwidth, actual);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_bandwidth(struct bladerf *dev, bladerf_module module, unsigned int *bandwidth, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_bandwidth(dev, module, bandwidth);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_lpf_mode(struct bladerf *dev, bladerf_module module, bladerf_lpf_mode mode, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_lpf_mode(dev, module, mode);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_lpf_mode(struct bladerf *dev, bladerf_module module, bladerf_lpf_mode *mode, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_lpf_mode(dev, module, mode);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_select_band(struct bladerf *dev, bladerf_module module, unsigned int frequency, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_select_band(dev, module, frequency);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_set_frequency(struct bladerf *dev, bladerf_module module, unsigned int frequency, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_frequency(dev, module, frequency);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_frequency(struct bladerf *dev, bladerf_module module, unsigned int *frequency, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_frequency(dev, module, frequency);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_expansion_attach(struct bladerf *dev, bladerf_xb xb, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_expansion_attach(dev, xb);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_expansion_get_attached(struct bladerf *dev, bladerf_xb *xb, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_expansion_get_attached(dev, xb);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb200_set_filterbank(struct bladerf *dev, bladerf_module mod, bladerf_xb200_filter filter, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb200_set_filterbank(dev, mod, filter);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb200_get_filterbank(struct bladerf *dev, bladerf_module module, bladerf_xb200_filter *filter, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb200_get_filterbank(dev, module, filter);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb200_set_path(struct bladerf *dev, bladerf_module module, bladerf_xb200_path path, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb200_set_path(dev, module, path);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb200_get_path(struct bladerf *dev, bladerf_module module, bladerf_xb200_path *path, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb200_get_path(dev, module, path);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

//typedef void *(*bladerf_stream_cb)(struct bladerf *dev, struct bladerf_stream *stream, struct bladerf_metadata *meta, void *samples, size_t num_samples, void *user_data);

int nr_init_stream(struct bladerf_stream **stream, struct bladerf *dev, bladerf_stream_cb callback, void ***buffers, size_t num_buffers, bladerf_format format, size_t samples_per_buffer, size_t num_transfers, void *user_data, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_init_stream(stream, dev, callback, buffers, num_buffers, format, samples_per_buffer, num_transfers, user_data);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_stream(struct bladerf_stream *stream, bladerf_module module, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_stream(stream, module);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_submit_stream_buffer(struct bladerf_stream *stream, void *buffer, unsigned int timeout_ms, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_submit_stream_buffer(stream, buffer, timeout_ms);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

void nr_deinit_stream(struct bladerf_stream *stream, const std::string &file = __FILE__, int line = __LINE__) {	::bladerf_deinit_stream(stream);
}

int nr_set_stream_timeout(struct bladerf *dev, bladerf_module module, unsigned int timeout, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_set_stream_timeout(dev, module, timeout);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_stream_timeout(struct bladerf *dev, bladerf_module module, unsigned int *timeout, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_stream_timeout(dev, module, timeout);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_sync_config(struct bladerf *dev, bladerf_module module, bladerf_format format, unsigned int num_buffers, unsigned int buffer_size, unsigned int num_transfers, unsigned int stream_timeout, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_sync_config(dev, module, format, num_buffers, buffer_size, num_transfers, stream_timeout);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_sync_tx(struct bladerf *dev, void *samples, unsigned int num_samples, struct bladerf_metadata *metadata, unsigned int timeout_ms, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_sync_tx(dev, samples, num_samples, metadata, timeout_ms);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_sync_rx(struct bladerf *dev, void *samples, unsigned int num_samples, struct bladerf_metadata *metadata, unsigned int timeout_ms, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_sync_rx(dev, samples, num_samples, metadata, timeout_ms);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_serial(struct bladerf *dev, char *serial, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_serial(dev, serial);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_vctcxo_trim(struct bladerf *dev, uint16_t *trim, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_vctcxo_trim(dev, trim);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_fpga_size(struct bladerf *dev, bladerf_fpga_size *size, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_fpga_size(dev, size);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_fw_version(struct bladerf *dev, struct bladerf_version *version, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_fw_version(dev, version);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_is_fpga_configured(struct bladerf *dev, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_is_fpga_configured(dev);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_fpga_version(struct bladerf *dev, struct bladerf_version *version, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_fpga_version(dev, version);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

bladerf_dev_speed nr_device_speed(struct bladerf *dev, const std::string &file = __FILE__, int line = __LINE__) {	return ::bladerf_device_speed(dev);
}

int nr_flash_firmware(struct bladerf *dev, const char *firmware, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_flash_firmware(dev, firmware);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_load_fpga(struct bladerf *dev, const char *fpga, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_load_fpga(dev, fpga);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_flash_fpga(struct bladerf *dev, const char *fpga_image, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_flash_fpga(dev, fpga_image);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_erase_stored_fpga(struct bladerf *dev, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_erase_stored_fpga(dev);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_device_reset(struct bladerf *dev, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_device_reset(dev);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_jump_to_bootloader(struct bladerf *dev, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_jump_to_bootloader(dev);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

void nr_version(struct bladerf_version *version, const std::string &file = __FILE__, int line = __LINE__) {	::bladerf_version(version);
}

void nr_log_set_verbosity(bladerf_log_level level, const std::string &file = __FILE__, int line = __LINE__) {	::bladerf_log_set_verbosity(level);
}

struct bladerf_image * nr_alloc_image(bladerf_image_type type, uint32_t address, uint32_t length, const std::string &file = __FILE__, int line = __LINE__) {
	return ::bladerf_alloc_image(type, address, length);
}

struct bladerf_image * nr_alloc_cal_image(bladerf_fpga_size fpga_size, uint16_t vctcxo_trim, const std::string &file = __FILE__, int line = __LINE__) {
	return ::bladerf_alloc_cal_image(fpga_size, vctcxo_trim);
}

void nr_free_image(struct bladerf_image *image, const std::string &file = __FILE__, int line = __LINE__) {
	::bladerf_free_image(image);
}

int nr_image_write(struct bladerf_image *image, const char *filename, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_image_write(image, filename);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_image_read(struct bladerf_image *image, const char *filename, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_image_read(image, filename);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

//int nr_si5338_read(struct bladerf *dev, uint8_t address, uint8_t *val, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_si5338_read(dev, address, val);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}
//
//int nr_si5338_write(struct bladerf *dev, uint8_t address, uint8_t val, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_si5338_write(dev, address, val);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}
//
//int nr_si5338_set_tx_freq(struct bladerf *dev, unsigned freq, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_si5338_set_tx_freq(dev, freq);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}
//
//int nr_si5338_set_rx_freq(struct bladerf *dev, unsigned freq, const std::string &file = __FILE__, int line = __LINE__) {//	int status = 0, i = 0;
//	do {
//		status = ::bladerf_si5338_set_rx_freq(dev, freq);
//		log_if(status, file, line);
//	}
//	while(status != 0 && ++i < 3);
//	return status;
//}

int nr_lms_read(struct bladerf *dev, uint8_t address, uint8_t *val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_lms_read(dev, address, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_lms_write(struct bladerf *dev, uint8_t address, uint8_t val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_lms_write(dev, address, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_lms_set_dc_cals(struct bladerf *dev, const struct bladerf_lms_dc_cals *dc_cals, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_lms_set_dc_cals(dev, dc_cals);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_lms_get_dc_cals(struct bladerf *dev, struct bladerf_lms_dc_cals *dc_cals, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_lms_get_dc_cals(dev, dc_cals);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_config_gpio_read(struct bladerf *dev, uint32_t *val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_config_gpio_read(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_config_gpio_write(struct bladerf *dev, uint32_t val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_config_gpio_write(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_expansion_gpio_read(struct bladerf *dev, uint32_t *val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_expansion_gpio_read(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_expansion_gpio_write(struct bladerf *dev, uint32_t val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_expansion_gpio_write(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_expansion_gpio_dir_read(struct bladerf *dev, uint32_t *val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_expansion_gpio_dir_read(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_expansion_gpio_dir_write(struct bladerf *dev, uint32_t val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_expansion_gpio_dir_write(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_get_timestamp(struct bladerf *dev, bladerf_module mod, uint64_t *value, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_get_timestamp(dev, mod, value);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_dac_write(struct bladerf *dev, uint16_t val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_dac_write(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb_spi_write(struct bladerf *dev, uint32_t send, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb_spi_write(dev, send);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_nios_rpc(struct bladerf *dev, uint8_t addr, uint32_t send, uint32_t *receive, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_nios_rpc(dev, addr, send, receive);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb_gps_spi(struct bladerf *dev, uint8_t send, uint8_t *receive, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb_gps_spi(dev, send, receive);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb_uart_read(struct bladerf *dev, uint32_t *val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb_uart_read(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb_uart_write(struct bladerf *dev, uint8_t val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb_uart_write(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb_uart_baud_write(struct bladerf *dev, uint16_t val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb_uart_baud_write(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb_uart_hasdata(struct bladerf *dev, uint32_t* val, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb_uart_hasdata(dev, val);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_xb_express_read(struct bladerf* dev, uint8_t custom_addr, uint8_t* data, uint32_t* count, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_xb_express_read(dev, custom_addr, data, count);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_calibrate_dc(struct bladerf *dev, bladerf_cal_module module, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_calibrate_dc(dev, module);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_erase_flash(struct bladerf *dev, uint32_t erase_block, uint32_t count, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_erase_flash(dev, erase_block, count);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_read_flash(struct bladerf *dev, uint8_t *buf, uint32_t page, uint32_t count, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_read_flash(dev, buf, page, count);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}

int nr_write_flash(struct bladerf *dev, const uint8_t *buf, uint32_t page, uint32_t count, const std::string &file = __FILE__, int line = __LINE__) {	int status = 0, i = 0;
	do {
		status = ::bladerf_write_flash(dev, buf, page, count);
		log_if(status, file, line);
	}
	while(status != 0 && ++i < 3);
	return status;
}


}}



