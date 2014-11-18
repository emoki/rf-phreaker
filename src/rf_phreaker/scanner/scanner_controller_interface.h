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

	virtual std::future<void> open_scanner(const scanner_serial_type &id) = 0;

	virtual std::future<void> close_scanner() = 0;

	virtual std::future<void> do_initial_scanner_config(const scanner_settings &settings) = 0;

	virtual std::future<void> refresh_scanner_info() = 0;

	virtual std::future<const scanner*> get_scanner() = 0;

	virtual std::future<void> write_vctcxo_trim_and_update_calibration(frequency_type carrier_freq, frequency_type freq_shift) = 0;

	virtual std::future<void> update_vctcxo_trim(frequency_type carrier_freq, frequency_type freq_shift) = 0;

	virtual std::future<void> write_license(const license &license) = 0;

	virtual std::future<rf_phreaker::gps> get_gps_data() = 0;

	virtual std::future<measurement_info> get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, frequency_type sampling_rate = 0) = 0;

	virtual std::future<measurement_info> get_rf_data(frequency_type freq, time_type time_ns, bandwidth_type bandwidth, gain_type &gain, frequency_type sampling_rate = 0) = 0;
};


}}