#pragma once

#include <string>
#include <boost/archive/binary_iarchive.hpp>
#include "rf_phreaker/scanner/blade_rf_controller.h"

void load_calibration(const rf_phreaker::scanner::scanner_id_type &serial, const std::string &cali_filename) {
	using namespace rf_phreaker::scanner;

	try {
		std::cout << "Loading calibration...\n";

		calibration cal;
		{
			std::cout << "Reading calibration from file.\n";

			std::ifstream f(cali_filename, std::ios::binary);
			if(!f)
				throw rf_phreaker::rf_phreaker_error("Unable to open calibration file (" + cali_filename + ").");
			boost::archive::binary_iarchive ia(f);
			ia & cal;
		}

		blade_rf_controller controller;
		
		auto scanners = controller.list_available_scanners();
		if(scanners.size() == 0)
			throw rf_phreaker::rf_phreaker_error("No scanners detected.");
		else
			std::cout << "Found " << scanners.size() << " scanner(s) connected." << std::endl;

		auto scanner = std::find_if(scanners.begin(), scanners.end(), [&](comm_info_ptr &comm) {
			return comm->id() == serial;
		});

		if(scanner == scanners.end())
			throw rf_phreaker::rf_phreaker_error("Scanner " + serial + " was not detected.");
		else	
			std::cout << "Opening scanner " << serial << ".\n";
		
		controller.open_scanner(serial);

		std::cout << "Initializing EEPROM.\n";

		controller.initialize_eeprom();
		
		std::cout << "Writing calibration to EEPROM.\n";
		controller.write_calibration(cal);

		std::cout << "Calibration loaded successfully!\n";
		return;
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

	std::cout << "Loading calibration failed!" << std::endl;
}