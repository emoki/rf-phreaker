#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/scanner/scanner_comm.h"
#include "rf_phreaker/scanner/scanner.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include <future>
#include <vector>

namespace rf_phreaker { namespace scanner {


class scanner_controller_interface
{
public:
	virtual ~scanner_controller_interface(void) {};

	virtual std::future<std::vector<comm_info_ptr>> list_available_scanners() = 0;

	virtual std::future<void> open_scanner_and_refresh_scanner_info(const scanner_serial_type &id) = 0;

	virtual std::future<void> close_scanner() = 0;

	virtual std::future<void> do_initial_scanner_config(const scanner_settings &settings) = 0;

	virtual std::future<void> refresh_scanner_info() = 0;

	virtual std::future<const scanner*> get_scanner() = 0;

	virtual std::future<void> calculate_vctcxo_trim_and_update_calibration(double error_hz) = 0;

	virtual std::future<void> calculate_and_update_vctcxo_trim(double error_hz) = 0;

	virtual std::future<void> write_license(const license &license) = 0;

	virtual std::future<rf_phreaker::gps> get_gps_data() = 0;

	virtual std::future<void> start_gps_1pps_integration(int seconds) = 0;

	virtual std::future<bool> attempt_gps_1pps_calibration() = 0;

	virtual std::future<gps_1pps_integration> get_last_valid_gps_1pps_integration() = 0;

	virtual std::future<measurement_info> get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, frequency_type sampling_rate = 0) = 0;

	virtual std::future<measurement_info> get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, gain_type &gain, frequency_type sampling_rate = 0) = 0;
};


}}