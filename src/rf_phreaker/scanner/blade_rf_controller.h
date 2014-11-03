#pragma once

#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/concurrent.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/scanner/comm_info.h"
#include "rf_phreaker/scanner/scanner_comm.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/byte_aligned_buffer.h"
#include "rf_phreaker/scanner/sampling_rate_conversion.h"
#include "rf_phreaker/scanner/rf_switch_conversion.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/scanner_blade_rf.h"
#include "rf_phreaker/scanner/gain_manager.h"
#include "rf_phreaker/scanner/eeprom.h"
#include "rf_phreaker/gps_comm/gps_comm.h"

namespace rf_phreaker { namespace scanner {

class comm_blade_rf;

class blade_rf_controller
{
public:
	blade_rf_controller(comm_type comm = USB_BLADE_RF);

	blade_rf_controller(blade_rf_controller &&c);

	~blade_rf_controller();
	
	int num_available_scanners();

	std::vector<comm_info_ptr> list_available_scanners();

	void open_scanner(const scanner_serial_type &id);

	void close_scanner();

	void do_initial_scanner_config(const scanner_settings &settings = blade_settings());

	void refresh_scanner_info();

	void write_vctcxo_trim(uint16_t trim);
	void write_vctcxo_trim_and_update_calibration(frequency_type carrier_freq, frequency_type freq_shift);
	
	void update_vctcxo_trim(frequency_type carrier_freq, frequency_type freq_shift);
	void update_vctcxo_trim(uint16_t trim);

	void read_vctcxo_trim(uint16_t &trim);

	void write_gpio(uint32_t value);

	void read_gpio(uint32_t &value);

	void write_config_gpio(uint32_t value);

	void read_config_gpio(uint32_t &value);

	void set_lms_reg(uint8_t reg, uint8_t value);

	void read_lms_reg(uint8_t reg, uint8_t &value);

	const scanner* get_scanner();

	const scanner_blade_rf* get_scanner_blade_rf();

	gps get_gps_data();

	measurement_info get_rf_data_use_auto_gain(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, frequency_type sampling_rate = 0);

	measurement_info get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, const gain_type &gain, frequency_type sampling_rate = 0,
		uint32_t switch_setting = 0, uint32_t switch_mask = 0);

	measurement_info get_rf_data(int num_samples);

	gain_type get_auto_gain(frequency_type freq, bandwidth_type bandwidth, time_type time_ns = 0, frequency_type sampling_rate = 0);

	void initialize_eeprom();

	eeprom_meta_data read_eeprom_meta_data();

	void write_eeprom(const eeprom &ee);

	eeprom read_eeprom();

	void write_calibration(calibration &cal);

	calibration read_calibration();

	void update_frequency_correction_value_and_date_in_calibration(uint16_t value, time_t date);

	void write_license(const license &license);

	void set_log_level(int level);

	const ipp_16sc_aligned_buffer& get_internal_iq_buffer() { return aligned_buffer_; }

	void set_blade_sync_rx_settings(const blade_settings &settings);

private:
	void enable_blade_rx();

	void disable_blade_rx();

	static int check_blade_status(int return_status, const std::string &file = "", int line = -1);

	void check_blade_comm();

	uint16_t calculate_vctcxo_trim_value(frequency_type carrier_freq, frequency_type freq_shift);

	ipp_16sc_aligned_buffer aligned_buffer_;

	gain_manager gain_manager_;

	std::unique_ptr<comm_blade_rf> comm_blade_rf_;

	std::shared_ptr<scanner_blade_rf_impl> scanner_blade_rf_;
	std::shared_ptr<scanner_blade_rf> scanner_;

	measurement_info parameter_cache_;

	int64_t collection_count_;

	std::unique_ptr<gps_comm::gps_comm> gps_comm_;

	blade_settings blade_settings_;
};

}}