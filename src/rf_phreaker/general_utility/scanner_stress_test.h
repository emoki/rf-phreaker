#pragma once

#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/measurement_io.h"

namespace rf_phreaker {

class snapshot_setting {
public:
	frequency_type start_freq_;
	frequency_type end_freq_;
	frequency_type freq_increment_;
	frequency_type sampling_rate_;
	bandwidth_type bandwidth_;
	time_type time_;
};
class stress_test_settings
{
public:
	int duration_mins_;
	std::vector<snapshot_setting> snapshots_;
	int update_vctcx_trim_duration_s_;
	int write_vctcx_trim_duration_s_;
	int get_gps_message_duration_s_;
	int perform_1pps_calibration_s_;
	int read_eeprom_duration_s_;
	int log_level_;
};

class scanner_stress_test
{
public:
	static void run(const stress_test_settings &s) {
		auto start_time = std::chrono::system_clock::now();

		rf_phreaker::logger log("stress_test");
		log.change_logging_level(s.log_level_);
		log.enable_collection_log(true);
		log.enable_gps_general_log(true);
		log.enable_gps_parsing_log(false);


		scanner::blade_rf_controller blade;
		auto scanner_list = blade.list_available_scanners();
		if(scanner_list.empty()) {
			std::cout << "No scanners available." << std::endl;
			return;
		}

		blade.open_scanner_and_refresh_scanner_info((*scanner_list.begin())->id());
		blade.do_initial_scanner_config();

		uint16_t vctcxo;
		blade.read_vctcxo_trim(vctcxo);

		while(std::chrono::system_clock::now() - start_time < std::chrono::minutes(s.duration_mins_)) {
			
			for(auto &snapshot : s.snapshots_) {
				for(auto freq = snapshot.start_freq_; freq <= snapshot.end_freq_; freq += snapshot.freq_increment_) {
					auto tmp = blade.get_rf_data_use_auto_gain(freq, snapshot.time_, snapshot.bandwidth_, snapshot.sampling_rate_);

					static auto update_vctcx_trim = std::chrono::system_clock::now();
					if(std::chrono::system_clock::now() - update_vctcx_trim > std::chrono::seconds(s.update_vctcx_trim_duration_s_)) {
						std::cout << "Updating vctcxo.\n";
						blade.update_vctcxo_trim(vctcxo);
						update_vctcx_trim = std::chrono::system_clock::now();
					}

					tmp = blade.get_rf_data_use_auto_gain(freq, snapshot.time_, snapshot.bandwidth_, snapshot.sampling_rate_);

					static auto write_vctcx_trim = std::chrono::system_clock::now();
					if(std::chrono::system_clock::now() - write_vctcx_trim > std::chrono::seconds(s.write_vctcx_trim_duration_s_)) {
						std::cout << "Writing vctcxo.\n";
						blade.write_vctcxo_trim(vctcxo);
						write_vctcx_trim = std::chrono::system_clock::now();
					}

					tmp = blade.get_rf_data_use_auto_gain(freq, snapshot.time_, snapshot.bandwidth_, snapshot.sampling_rate_);

					static auto get_gps_message = std::chrono::system_clock::now();
					if(std::chrono::system_clock::now() - get_gps_message > std::chrono::seconds(s.get_gps_message_duration_s_)) {
						auto gps = blade.get_gps_data();
						std::cout << gps << std::endl;
						get_gps_message = std::chrono::system_clock::now();
					}

					 tmp = blade.get_rf_data_use_auto_gain(freq, snapshot.time_, snapshot.bandwidth_, snapshot.sampling_rate_);

					static auto perform_1pps = std::chrono::system_clock::now();
					if(std::chrono::system_clock::now() - perform_1pps > std::chrono::seconds(s.perform_1pps_calibration_s_)) {
						std::cout << "Attempting 1pps.\n";
						blade.attempt_gps_1pps_calibration();
						blade.start_gps_1pps_integration(std::min(s.perform_1pps_calibration_s_ - 1, 54));			
						perform_1pps = std::chrono::system_clock::now();
					}

					tmp = blade.get_rf_data_use_auto_gain(freq, snapshot.time_, snapshot.bandwidth_, snapshot.sampling_rate_);

					static auto read_eeprom = std::chrono::system_clock::now();
					if(std::chrono::system_clock::now() - read_eeprom > std::chrono::seconds(s.read_eeprom_duration_s_)) {
						std::cout << "Reading EEPROM.\n";
						blade.read_eeprom();
						read_eeprom = std::chrono::system_clock::now();
					}
				}
			}
		}
	}
};

}