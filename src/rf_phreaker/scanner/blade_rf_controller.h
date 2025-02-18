#pragma once

#include "boost/circular_buffer.hpp"
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
#include "rf_phreaker/scanner/rf_switch_conversion.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/scanner_blade_rf.h"
#include "rf_phreaker/scanner/gain_manager.h"
#include "rf_phreaker/scanner/eeprom.h"
#include "rf_phreaker/scanner/freq_correction_container.h"
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

	void open_scanner_and_refresh_scanner_info(const scanner_serial_type &id);

	void close_scanner();

	void do_initial_scanner_config(const scanner_settings &settings = blade_settings());

	void update_settings(const scanner_settings &settings = blade_settings());

	void refresh_scanner_info();

	void write_vctcxo_trim(uint16_t trim);

	void calculate_vctcxo_trim_and_update_eeprom(double error_hz);
	
	void calculate_and_update_vctcxo_trim(double error_hz);

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

	measurement_info get_rf_data_use_auto_gain(frequency_type frequency, time_type time_ns, bandwidth_type bandwidth, frequency_type sampling_rate = 0);

	measurement_info get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, const gain_type &gain, frequency_type sampling_rate = 0,
		uint32_t switch_setting = 0, uint32_t switch_mask = 0);

	measurement_info get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, int total_gain_db, frequency_type sampling_rate = 0,
		uint32_t switch_setting = 0, uint32_t switch_mask = 0);

	void configure_rf_parameters_use_auto_gain(frequency_type frequency, bandwidth_type bandwidth, frequency_type sampling_rate = 0);

	void configure_rf_parameters(frequency_type frequency, bandwidth_type bandwidth, const gain_type &gain, frequency_type sampling_rate = 0,
		uint32_t switch_setting = 0, uint32_t switch_mask = 0);

	measurement_info stream_rf_data_use_auto_gain(frequency_type frequency, time_type time_ns, time_type time_ns_to_overlap, bandwidth_type bandwidth, frequency_type sampling_rate = 0);

	void stop_streaming_and_disable_blade_rx();

	gain_type get_auto_gain(frequency_type frequency, bandwidth_type bandwidth, time_type time_ns = 0, frequency_type sampling_rate = 0);

	void initialize_eeprom();

	void write_flash(const std::vector<uint8_t> &bytes, const eeprom_addressing &addressing);

	std::vector<uint8_t> read_flash(const eeprom_addressing &addressing);

	void write_eeprom_meta_data(const eeprom_meta_data &meta_ee);

	eeprom_meta_data read_eeprom_meta_data();

	void write_eeprom(const eeprom &ee);

	eeprom read_eeprom(bool quick_read = true);

	void write_calibration(calibration &cal);

	calibration read_calibration();

	void update_frequency_correction_value_and_date_in_calibration(uint16_t value, time_t date);

	void write_license(const license &license);

	license read_license();

	void write_frequency_correction(const freq_correction_container &freq_correction);

	freq_correction_container read_frequency_correction_container();

	void set_log_level(int level);

	const ipp_16sc_aligned_buffer& get_internal_iq_buffer() { return aligned_buffer_; }

	void set_blade_sync_rx_settings(const blade_rx_settings &settings);

	void set_blade_sync_rx_stream_settings(const blade_rx_settings &settings);

	void start_gps_1pps_integration(int seconds);

	bool attempt_gps_1pps_calibration();

	gps_1pps_integration get_last_valid_gps_1pps_integration();

	void power_on_gps();

	void power_off_gps();

	void enable_continuity_check();

	void output_continuity_packet(int num_transfer_samples);

	void flash_fx3_firmware(const std::string &filename);

	lna_gain_values get_lna_gains(frequency_type center_freq);

private:
	void enable_blade_rx(const blade_rx_settings &settings);
	void enable_full_streaming_rx();
	void enable_intermittent_streaming_rx();

	void stop_streaming();
	void disable_blade_rx();

	static int check_blade_status(int return_status, const std::string &file = "", int line = -1);

	void check_blade_comm();

	uint16_t calculate_vctcxo_trim_value(double error_in_hz);

	void update_vctcxo_based_on_eeprom();

	std::chrono::time_point<std::chrono::steady_clock> get_collection_start_time();

	measurement_info pop_measurement_buffer();

	void set_gain(const gain_type &gain);

	void update_gain(const measurement_info &info);

	measurement_info parameter_cache();

	void set_parameter_cache(measurement_info &info);

	void set_parameter_cache_gain(const gain_type &gain);

	ipp_16sc_aligned_buffer aligned_buffer_;

	gain_manager gain_manager_;

	std::unique_ptr<comm_blade_rf> comm_blade_rf_;

	std::shared_ptr<scanner_blade_rf_impl> scanner_blade_rf_;

	std::shared_ptr<scanner_blade_rf> scanner_;

	std::mutex parameter_cache_mutex_;
	measurement_info parameter_cache_;

	int64_t collection_count_;

	std::unique_ptr<gps_comm::gps_comm> gps_comm_;

	blade_rx_settings blade_settings_;

	blade_rx_settings blade_settings_stream_;

	gps_1pps_integration last_1pps_integration_;

	gps_1pps_integration current_1pps_integration_;

	ipp_32fc_array rf_stream_buffer_;
	enum streaming_type {
		NOT_STREAMING,
		INTERMITTENT_STREAMING,
		FULL_STREAMING
	};
	std::atomic<streaming_type> is_streaming_;
	std::atomic_bool should_update_streaming_parameters_;
	time_type streaming_time_ns_;
	time_type streaming_time_ns_to_overlap_;
	std::mutex meas_buffer_mutex_;
	std::unique_ptr<std::thread> streaming_thread_;
	boost::circular_buffer<measurement_info> meas_buffer_;

	std::recursive_mutex open_close_mutex_;
};

}}