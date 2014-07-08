#pragma once

#include <string>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "rf_phreaker/scanner/blade_rf_controller.h"

class calibration_utility
{
public:
	static void read_calibration_and_output(const std::string &nuand_calibration_filename, const std::string &rf_board_calibration_filename,
		const std::string &switch_setting_filename) {
		using namespace rf_phreaker::scanner;

		try {
			calibration cal;
			cal.read_nuand_calibration_file(nuand_calibration_filename);
			cal.read_rf_board_calibration_file(rf_board_calibration_filename);
			cal.read_rf_switch_file(switch_setting_filename);

			{
				std::string cali_filename = cal.nuand_serial_ + "_cali.bin";
				std::ofstream f(cali_filename, std::ios::binary);
				if(!f)
					throw rf_phreaker::rf_phreaker_error("Unable to open calibration file (" + cali_filename + ").");
				boost::archive::binary_oarchive ia(f);
				ia & cal;
			}
		}
		catch(rf_phreaker::rf_phreaker_error &err) {
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch(std::exception &err) {
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch(...) {
			std::cout << "Unknown error has occurred." << std::endl;
		}
	}

	static void load_calibrations(const std::vector<rf_phreaker::scanner::scanner_id_type> &list) {
		using namespace rf_phreaker::scanner;


		try {
			std::cout << "Searching for the following scanner(s):\n";
			for(auto serial : list)
				std::cout << "   " << serial << "\n";

			std::vector<comm_info_ptr> scanners;
			{
				blade_rf_controller controller;
				scanners = controller.list_available_scanners();
				if(scanners.size() == 0)
					throw rf_phreaker::rf_phreaker_error("No scanners detected.");
				else
					std::cout << "\nFound " << scanners.size() << " scanner(s) connected.\n";
			}

			bool found_serial = false;
			for(auto serial : list) {
				auto scanner = std::find_if(scanners.begin(), scanners.end(), [&](comm_info_ptr &comm) {
					return comm->id() == serial;
				});

				if(scanner == scanners.end())
					continue;
				else {
					std::cout << "\nFound scanner " << serial << "\n";
					found_serial = true;
					load_calibration(serial, serial + "_cali.bin");
				}
			}

			if(!found_serial)
				std::cout << "\nNo specified scanner(s) detected.\n";
		}
		catch(rf_phreaker::rf_phreaker_error &err) {
			std::cout << "\nError: " << err.what() << std::endl;
		}
		catch(std::exception &err) {
			std::cout << "\nError: " << err.what() << std::endl;
		}
		catch(...) {
			std::cout << "\nUnknown error has occurred." << std::endl;
		}

	}

	static void load_calibration(const rf_phreaker::scanner::scanner_id_type &serial, const std::string &cali_filename) {
		using namespace rf_phreaker::scanner;

		try {
			std::cout << "\nLoading calibration...\n";

			calibration cal = read_calibration_from_file(cali_filename);

			blade_rf_controller controller;

			auto scanners = controller.list_available_scanners();

			auto scanner = std::find_if(scanners.begin(), scanners.end(), [&](comm_info_ptr &comm) {
				return comm->id() == serial;
			});

			if(scanner == scanners.end())
				throw rf_phreaker::rf_phreaker_error("Scanner " + serial + " was not detected.");
			else
				std::cout << "\nOpening scanner " << serial << ".\n";

			controller.open_scanner(serial);

			try{
				auto meta_data = controller.read_eeprom_meta_data();
				if(!meta_data.is_valid()) {
					std::cout << "\nInitializing EEPROM.\n";
					controller.initialize_eeprom();
				}
			}
			catch(const std::exception &err) {
				std::cout << "\nError while reading EEPROM meta data: " << err.what() << "\nInitializing EEPROM.\n" ;
				controller.initialize_eeprom();
			}

			// If the EEPROM is valid then we use the freq correction value and date. 
			auto tmp_cal = controller.read_calibration();
			if(tmp_cal.nuand_freq_correction_value_ > 0 && tmp_cal.nuand_freq_correction_date_ > 0) {
				cal.nuand_freq_correction_value_ = tmp_cal.nuand_freq_correction_value_;
				cal.nuand_freq_correction_date_ = tmp_cal.nuand_freq_correction_date_;
			}

			std::cout << "\nWriting calibration to EEPROM.\n";
			controller.write_calibration(cal);

			std::cout << "\nCalibration loaded successfully!\n";
			return;
		}
		catch(rf_phreaker::rf_phreaker_error &err) {
			std::cout << "\nError: " << err.what() << std::endl;
		}
		catch(std::exception &err) {
			std::cout << "\nError: " << err.what() << std::endl;
		}
		catch(...) {
			std::cout << "\nUnknown error has occurred." << std::endl;
		}

		std::cout << "\nLoading calibration failed!" << std::endl;
	}

	static rf_phreaker::scanner::calibration read_calibration_from_file(const std::string &filename)
	{
		using namespace rf_phreaker::scanner;

		std::cout << "\nReading calibration from file.\n";

		calibration cal;
		std::ifstream f(filename, std::ios::binary);
		if(!f)
			throw rf_phreaker::rf_phreaker_error("Unable to open calibration file (" + filename + ").");
		boost::archive::binary_iarchive ia(f);
		ia & cal;
		
		return cal;
	}
};