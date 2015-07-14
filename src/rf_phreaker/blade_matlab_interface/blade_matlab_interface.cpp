#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "rf_phreaker/blade_matlab_interface/blade_matlab_interface.h"
#include "rf_phreaker/blade_matlab_interface/matlab_interface_helper.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/scanner/signal_level_calculator.h"
#include "rf_phreaker/scanner/eeprom.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;
using namespace rf_phreaker::matlab_interface;

std::unique_ptr<rf_phreaker::logger> loggerz;

float calculate_sl(measurement_info &meas) {
	auto rms = ipp_helper::calculate_average_rms(meas.get_iq().get(), meas.get_iq().length());
	return (float)signal_level_calculator::calculate_sl(rms, meas, 0, use_rf_board_adjustment);
}

int start_logging(int log_level) {
	try {
		loggerz.reset(new rf_phreaker::logger("blade_matlab_interface", ""));
		loggerz->change_logging_level(log_level);
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

int stop_logging() {
	try {
		loggerz.reset();
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

int num_blade_devices_connected(int *num_devices) {
	try {
		check_null(num_devices);

		*num_devices = controller.num_available_scanners();

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

int list_blade_devices(int8_t *device_list, int list_size) {
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

int open_first_blade_device() {
	try {
		cali.reset();
		auto devices = controller.list_available_scanners();
		if(devices.size() && (*devices.begin())->id() == "")
			devices = controller.list_available_scanners();

		if(devices.size() && (*devices.begin())->id().size()) {
			controller.open_scanner_and_refresh_scanner_info((*devices.begin())->id());
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

int open_blade_device(const char *serial) {
	try {
		cali.reset();
		controller.open_scanner_and_refresh_scanner_info(serial);
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

int close_blade_device() {
	try {
		cali.reset();
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

int get_connected_device_info(int8_t *serial, int serial_size, int *usb_speed) {
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

int get_rf_data(int64_t frequency_hz, int bandwidth_hz, int64_t sampling_rate_hz, int lna_gain, int rx_gain_vga1, int rx_gain_vga2, float *iq_data,
	int num_samples, float *sl, uint32_t switch_setting, uint32_t switch_mask) {
	try {
		check_null(iq_data);
		// sl is optional.

		lms::lna_gain_enum lna_gain_tmp = lms::to_lna_gain(lna_gain);
		if(lna_gain_tmp == lms::LNA_UNKNOWN)
			throw matlab_interface_error("Invalid parameter.  LNA gain not valid.  Valid values are 1 -> BYPASS, 2 -> MID, 3 -> MAX.",
			matlab_interface_error_invalid_parameter);

		gain_type gain(lna_gain_tmp, rx_gain_vga1, rx_gain_vga2);

		// Add additional millisecond to num samples to ensure we have enough data.
		auto meas = controller.get_rf_data(frequency_hz, rf_phreaker::convert_to_time(num_samples, sampling_rate_hz) + milli_to_nano(1), bandwidth_hz, gain,
			sampling_rate_hz, switch_setting, switch_mask);

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

int auto_get_rf_data(int64_t frequency_hz, int bandwidth_hz, int64_t sampling_rate_hz, float *iq_data, int num_samples, float *sl,
	int *lna_gain, int *rx_gain_vga1, int *rx_gain_vga2) {
	try {
		check_null(iq_data);
		// sl is optional.

		// Add additional millisecond to num samples to ensure we have enough data.
		auto meas = controller.get_rf_data_use_auto_gain(frequency_hz, rf_phreaker::convert_to_time(num_samples, sampling_rate_hz) + milli_to_nano(1), bandwidth_hz, sampling_rate_hz);

		memcpy(iq_data, &meas.get_iq()[0], num_samples * sizeof(ipp_32fc_array::data_type_));

		if(sl != nullptr)
			*sl = calculate_sl(meas);

		auto gain = meas.gain();
		if(lna_gain != nullptr) 
			*lna_gain = gain.lna_gain_ == lms::LNA_MAX ? 3 : (gain.lna_gain_ == lms::LNA_MID ? 2 : 1);
		if(rx_gain_vga1 != nullptr)
			*rx_gain_vga1 = gain.rxvga1_;
		if(rx_gain_vga2 != nullptr)
			*rx_gain_vga2 = gain.rxvga2_;

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

int set_vctcxo_trim(int trim) {
	try {
		uint16_t tmp_trim = trim;
		controller.update_vctcxo_trim(tmp_trim);
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

int read_vctcxo_trim(int *trim) {
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

int write_frequency_correction_value(int trim, int64_t seconds_since_1970) {
	try {
		uint16_t tmp_trim = trim;
		controller.update_vctcxo_trim(tmp_trim);
		controller.write_vctcxo_trim(tmp_trim);
		try {
			controller.update_frequency_correction_value_and_date_in_calibration(tmp_trim, seconds_since_1970);
		}
		catch(const rf_phreaker_error &err) {
			LOG(LDEBUG) << "Error writing calibration: " << err.what() << ".  Attempting to reinitialize EEPROM.";
			controller.initialize_eeprom();
			controller.update_frequency_correction_value_and_date_in_calibration(tmp_trim, seconds_since_1970);
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

int read_gpio(unsigned int *value) {
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

int set_gpio(unsigned int value) {
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

int set_lms_reg(int address, int value) {
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

int read_lms_reg(int address, int *value) {
	try {
		check_null(value);
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

int write_calibration(const int8_t *nuand_calibration_filename, const int8_t *rf_board_calibration_filename, const int8_t *switch_setting_filename, const int8_t *calibration_output_filename, int hw_id) {
	try {
		check_null(nuand_calibration_filename);
		check_null(rf_board_calibration_filename);
		check_null(switch_setting_filename);

		cali.reset();

		calibration cal;
		cal.hw_id_ = hw_id;
		cal.read_nuand_calibration_file(std::string((char*)nuand_calibration_filename));
		cal.read_rf_board_calibration_file(std::string((char*)rf_board_calibration_filename));
		cal.read_rf_switch_file(std::string((char*)switch_setting_filename));

		{
			auto filename = cal.nuand_serial_ + "_calibration__" + current_date_time_string() + ".bin";
			if(calibration_output_filename != 0) {
				filename = (char*)(calibration_output_filename);
			}
			std::ofstream f(filename, std::ios::binary);
			boost::archive::binary_oarchive oa(f);
			//std::ofstream f(cal.nuand_serial_ + "_calibration_" /*+ current_date_time_string()*/ + ".txt");
			//boost::archive::text_oarchive oa(f);
			oa & cal;
		}

		try {
			controller.write_calibration(cal);
		}
		catch(const rf_phreaker_error &err) {
			LOG(LDEBUG) << "Error writing calibration: " << err.what() << ".  Attempting to reinitialize EEPROM.";
			controller.initialize_eeprom();
			controller.write_calibration(cal);
		}
		catch(const boost::archive::archive_exception &err) {
			LOG(LDEBUG) << "Error writing calibration: " << err.what() << ".  Attempting to reinitialize EEPROM.";
			controller.initialize_eeprom();
			controller.write_calibration(cal);
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

int use_rf_board_adjustment_for_signal_level(bool use_adj) {
	use_rf_board_adjustment = use_adj;
	return matlab_interface_no_error;
}

int get_nuand_adjustment(int lna_gain, __int64 frequency_hz, float *adj) {
	try {
		check_null(adj);

		if(!cali)
			cali.reset(new calibration(controller.read_calibration()));

		*adj = (float)cali->get_nuand_adjustment(lms::to_lna_gain(lna_gain), frequency_hz);
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

int get_rf_board_adjustment(__int64 frequency_hz, int bandwidth_hz, float *adj) {
	try {
		check_null(adj);

		if(!cali)
			cali.reset(new calibration(controller.read_calibration()));

		*adj = (float)cali->get_rf_board_adjustment(frequency_hz, bandwidth_hz);
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

int calculate_signal_level(__int64 frequency_hz, int bandwidth_hz, int lna_gain, int gain_rxvga1, int gain_rxvga2, float digital_voltage, float *signal_level) {
	try {
		check_null(signal_level);

		if(!cali)
			cali.reset(new calibration(controller.read_calibration()));

		double nuand_adj = 0;
		double blade_adj = 0;

		nuand_adj = cali->get_nuand_adjustment(lms::to_lna_gain(lna_gain), frequency_hz);

		if(use_rf_board_adjustment)
			blade_adj = cali->get_rf_board_adjustment(frequency_hz, bandwidth_hz);

		*signal_level = (float)signal_level_calculator::calculate_sl(digital_voltage, gain_rxvga1, gain_rxvga2, nuand_adj, blade_adj);

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

int get_last_error(int8_t* description, int description_size) {
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

int save_eeprom(const int8_t *eeprom_filename) {
	try {
		check_null(eeprom_filename);


		//std::ofstream f((char*)eeprom_filename, std::ios::binary);
		//boost::archive::binary_oarchive oa(f);
		std::ofstream f((char*)eeprom_filename);
		boost::archive::text_oarchive oa(f);

		auto ee = controller.read_eeprom();
		oa & ee;

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

int load_eeprom(const int8_t *eeprom_filename) {
	try {
		check_null(eeprom_filename);

		//std::ifstream f((char*)eeprom_filename, std::ios::binary);
		//boost::archive::binary_iarchive ia(f);
		std::ifstream f((char*)eeprom_filename);
		boost::archive::text_iarchive ia(f);

		eeprom ee;
		ia & ee;

		controller.write_eeprom(ee);

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

int get_gps_data(float *latitude, float *longitude, int *tracking_satellties, int *visible_satellties, __int64 *utc_time) {
	try {
		check_null(latitude);
		check_null(longitude);
		check_null(tracking_satellties);
		check_null(visible_satellties);
		check_null(utc_time);

		auto gps = controller.get_gps_data();

		*latitude = (float)gps.latitude_;
		*longitude = (float)gps.latitude_;
		*tracking_satellties = gps.tracking_satellites_;
		*visible_satellties = gps.visible_satellites_;
		*utc_time = gps.coordinated_universal_time_;

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

int start_gps_1pps_calibration(int seconds_to_integrate) {
	try {
		controller.start_gps_1pps_integration(seconds_to_integrate);

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

int finish_gps_1pps_calibration(bool *success) {
	try {
		check_null(success);

		*success = controller.attempt_gps_1pps_calibration();

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

int get_last_valid_1pps_calibration(__int64 *clock_ticks, int *seconds_integrated, float *error_in_hz) {
	try {
		check_null(clock_ticks);
		check_null(seconds_integrated);
		check_null(error_in_hz);

		auto pps = controller.get_last_valid_gps_1pps_integration();

		*clock_ticks = pps.clock_ticks();
		*seconds_integrated = pps.seconds_integrated();
		*error_in_hz = (float)pps.error_in_hz();

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

int power_on_gps() {
	try {

		controller.power_on_gps();

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

int power_off_gps() {
	try {

		controller.power_off_gps();

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
