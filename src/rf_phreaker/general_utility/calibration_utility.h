#pragma once

#include <string>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "rf_phreaker/scanner/blade_rf_controller.h"

class calibration_utility
{
public:
	static void read_calibration_and_output(const std::string &nuand_calibration_filename, const std::string &rf_board_calibration_filename,
		const std::string &switch_setting_filename, uint32_t hw_id) {
		using namespace rf_phreaker::scanner;

		try {
			calibration cal;
			cal.read_nuand_calibration_file(nuand_calibration_filename);
			cal.read_rf_board_calibration_file(rf_board_calibration_filename);
			cal.read_rf_switch_file(switch_setting_filename);
			cal.hw_id_ = hw_id;

			{
				std::string cali_filename = cal.nuand_serial_ + "_cali.bin";
				std::ofstream f(cali_filename, std::ios::binary);
				if(!f)
					throw rf_phreaker::file_io_error("Unable to open calibration file (" + cali_filename + ").");
				boost::archive::binary_oarchive ia(f);
				ia & cal;

				std::cout << "Finished creating calibration file: " << cali_filename << ".\n" << std::endl;
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

	static void load_calibration(const std::string &filename) {
		using namespace rf_phreaker::scanner;

		try {

			std::string serial;
			{
				calibration cal = read_calibration_from_file(filename);
				serial = cal.nuand_serial_;
			}

			std::vector<rf_phreaker::scanner_serial_type> list{ serial };

			std::cout << "Searching for the following scanner:\n";
			for(auto serial : list)
				std::cout << "   " << serial << "\n";

			std::vector<rf_phreaker::scanner::comm_info_ptr> scanners;
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
				auto scanner = std::find_if(scanners.begin(), scanners.end(), [&](rf_phreaker::scanner::comm_info_ptr &comm) {
					return comm->id() == serial;
				});

				if(scanner == scanners.end())
					continue;
				else {
					std::cout << "\nFound scanner " << serial << "\n";
					found_serial = true;
					load_calibration(serial, filename);
				}
			}

			if(!found_serial)
				std::cout << "\nSpecified scanner not detected.\n";
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

	static void load_calibration(const rf_phreaker::scanner_serial_type &serial, const std::string &cali_filename) {
		using namespace rf_phreaker::scanner;

		try {
			calibration cal = read_calibration_from_file(cali_filename);

			blade_rf_controller controller;

			auto scanners = controller.list_available_scanners();

			auto scanner = std::find_if(scanners.begin(), scanners.end(), [&](rf_phreaker::scanner::comm_info_ptr &comm) {
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

	static void load_calibration_from_directory(const std::string &dir) {
		using namespace rf_phreaker::scanner;

		try {
			std::cout << "Using auto detection for calibration upload.\n";

			std::string separator;
			if(!dir.empty() && dir.back() != '\\')
				separator.push_back('\\');

			std::vector<rf_phreaker::scanner::comm_info_ptr> scanners;
			{
				blade_rf_controller controller;
				scanners = controller.list_available_scanners();
				if(scanners.size() == 0)
					throw rf_phreaker::rf_phreaker_error("No scanners detected.");
				else
					std::cout << "\nFound " << scanners.size() << " scanner(s) connected.\n";
			}

			for(auto &scanner : scanners) {
				std::cout << "\nFound scanner " << scanner->id() << "\n";
				load_calibration(scanner->id(), dir + separator + scanner->id() + "_cali.bin");
			}
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

	static void upload_fx3_firmware_if_necessary() {
		using namespace rf_phreaker::scanner;

		try {
			std::cout << "Checking FX3 firmware." << std::endl;

			blade_rf_controller controller;
			std::vector<rf_phreaker::scanner::comm_info_ptr> scanners;
			{
				scanners = controller.list_available_scanners();
				if(scanners.size() == 0)
					throw rf_phreaker::rf_phreaker_error("No scanners detected.");
				else
					std::cout << "\nFound " << scanners.size() << " scanner(s) connected.\n";
			}

			for(auto &scanner : scanners) {
				std::cout << "\nFound scanner " << scanner->id() << "\n";
				
				controller.open_scanner_and_refresh_scanner_info(scanner->id());

				std::string fx3_fw = controller.get_scanner_blade_rf()->firmware_version_description();
				if(fx3_fw.find("1.8.0") == std::string::npos) {
					std::cout << "FX3 firmware mismatch.  Current firmware is " << fx3_fw << "." << std::endl;
					std::cout << "Flashing FX3 firmware..." << std::endl;
					controller.flash_fx3_firmware("bladeRF_fw_v1.8.0.img");
					std::cout << "Flashing complete!\n\nPlease power cycle the scanner!\n\n" << std::endl;
				}
				else
					std::cout << "Correct FX3 firmware found." << std::endl;
					
			}
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
};