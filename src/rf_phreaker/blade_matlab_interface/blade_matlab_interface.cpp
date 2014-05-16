#include "rf_phreaker/blade_matlab_interface/blade_matlab_interface.h"
#include "rf_phreaker/blade_matlab_interface/matlab_interface_helper.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/scanner/calibration.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;
using namespace rf_phreaker::matlab_interface;

float calculate_sl(measurement_info &meas)
{
	auto rms = ipp_helper::calculate_average_rms(meas.get_iq().get(), meas.get_iq().length());
	calibration cali;
	return (float)cali.calculate_sl(rms, meas.gain());
}

int start_logging(int log_level)
{
	try {
		static init_log logger("blade_matlab_interface", "");
		logger.log_worker_->changeLoggingLevel(log_level);

		return 0;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int num_blade_devices_connected(int *num_devices)
{
	try {
		check_null(num_devices);

		*num_devices = controller.num_available_scanners();

		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err)
	{
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int list_blade_devices(int8_t *device_list, int list_size)
{
	try {
		check_null(device_list);

		auto devices = controller.list_available_scanners();

		std::string device_str;
		for(auto const device : devices)
			device_str += device->description() + ";";

		device_str += ";";

		check_buf_size(list_size, device_str, "Device list");

		memset(device_list, 0, list_size);
		std::copy(device_str.begin(), device_str.end(), device_list);

		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int open_first_blade_device()
{
	try {
		auto devices = controller.list_available_scanners();
		if(devices.size() && (*devices.begin())->id() == "")
			devices = controller.list_available_scanners();

		if(devices.size() && (*devices.begin())->id().size())
		{
			controller.open_scanner((*devices.begin())->id());
			controller.do_initial_scanner_config();
			return matlab_interface_no_error;
		}

		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int open_blade_device(const char *serial)
{
	try {
		controller.open_scanner(serial);
		controller.do_initial_scanner_config();
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int close_blade_device()
{
	try {
		controller.close_scanner();
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int get_connected_device_info(int8_t *serial, int serial_size, int *usb_speed)
{
	try {
		check_null(serial);
		check_null(usb_speed);

		auto device = controller.get_scanner_blade_rf();

		check_buf_size(serial_size, device->serial(), "Serial");

		memset(serial, 0, serial_size);
		auto tmp_str = device->serial();
		std::copy(tmp_str.begin(), tmp_str.end(), serial);

		*usb_speed = device->usb_speed() + 1;

		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int get_rf_data(int64_t frequency_hz, int bandwidth_hz, int64_t sampling_rate_hz, int lna_gain, int rx_gain_vga1, int rx_gain_vga2, float *iq_data, int num_samples, float *sl)
{
	try {
		check_null(iq_data);

		lms::lna_gain_enum lna_gain_tmp;
		switch(lna_gain)
		{
		case 1:
			lna_gain_tmp = lms::LNA_BYPASS;
			break;
		case 2:
			lna_gain_tmp = lms::LNA_MID;
			break;
		case 3:
			lna_gain_tmp = lms::LNA_MAX;
			break;
		default:
			throw matlab_interface_error("Invalid parameter.  LNA gain not valid.  Valid values are 1 -> BYPASS, 2 -> MID, 3 -> MAX.", matlab_interface_error_invalid_parameter);
		}

		gain_type gain(lna_gain_tmp, rx_gain_vga1, rx_gain_vga2);

		auto meas = controller.get_rf_data(frequency_hz, rf_phreaker::convert_to_time(num_samples, sampling_rate_hz), bandwidth_hz, gain, sampling_rate_hz);

		memcpy(iq_data, &meas.get_iq()[0], num_samples * sizeof(ipp_32fc_array::data_type_));

		if(sl != nullptr) 
			*sl = calculate_sl(meas);

		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int only_get_rf_data(float *iq_data, int num_samples, float *sl)
{
	try {
		check_null(iq_data);

		auto meas = controller.get_rf_data(num_samples);

		memcpy(iq_data, &meas.get_iq()[0], num_samples * sizeof(ipp_32fc_array::data_type_));

		if(sl != nullptr) 
			*sl = calculate_sl(meas);

		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int set_vctcxo_trim(int trim)
{
	try {
		uint16_t tmp_trim = trim;
		controller.write_vctcxo_trim(tmp_trim);
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int read_vctcxo_trim(int *trim)
{
	try {
		check_null(trim);
		uint16_t tmp_trim = 0;
		controller.read_vctcxo_trim(tmp_trim);
		*trim = tmp_trim;
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int read_gpio(unsigned int *value)
{
	try {
		check_null(value);
		controller.read_gpio(*value);
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int set_gpio(unsigned int value)
{
	try {
		controller.write_gpio(value);
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int set_lms_reg(int address, int value)
{
	try {
		controller.set_lms_reg(address, value);
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int read_lms_reg(int address, int *value)
{
	try {
		uint8_t tmp;
		controller.read_lms_reg(address, tmp);
		*value = tmp;
		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;
}

int get_last_error(int8_t* description, int description_size)
{
	try {
		check_null(description);
		
		check_buf_size(description_size, last_error_, "Last error");

		memset(description, 0, description_size);

		std::copy(last_error_.begin(), last_error_.end(), description);

		return matlab_interface_no_error;
	}
	catch(rf_phreaker::rf_phreaker_error &err) {
		last_error_ = err.what();
		return (int)err.error_code_;
	}
	catch(std::exception &err) {
		last_error_ = err.what();
	}
	return matlab_interface_error_general;

}