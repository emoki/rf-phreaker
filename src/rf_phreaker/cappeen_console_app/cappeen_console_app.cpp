// beagle_console_app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <chrono>
#include <thread>
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/cappeen/operating_band_conversion.h"
#include "rf_phreaker/cappeen_console_app/cappeen_wrapper.h"
#include "rf_phreaker/cappeen_console_app/cappeen_delegate.h"
#include "rf_phreaker/cappeen_console_app/cappeen_dispatcher.h"
#include "rf_phreaker/cappeen_console_app/cappeen_command_handler.h"
#include "rf_phreaker/cappeen_console_app/cappeen_utilities.h"
#include "rf_phreaker/cappeen_console_app/simple_logger.h"

#include <boost/program_options.hpp>

void generate_report(const boost::program_options::variables_map &vars, const std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const cappeen_scanner::cappeen_dispatcher &dispatcher);

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace cappeen_scanner;
	using namespace beagle_api;
	namespace po = boost::program_options;

	// Option variables.
	std::vector<int> gsm_bands;
	std::vector<int> umts_bands;
	std::vector<int> lte_bands;
	std::string base_filename;
	std::string report_filename;
	std::string collection_priority;
	int time_min;
	int iterations;
	bool should_report;
	bool perform_quick_scan;

	try {
		po::options_description desc("Allowed options");

		desc.add_options()
			("help,h", "Produce help message.")
			("log_filename,f", po::value<std::string>(&base_filename)->default_value("cappeen_data"), "Set base filename for output.")
			("generate_report", po::value<bool>(&should_report)->default_value(false), "Generate report.")
			("report_filename,r", po::value<std::string>(&report_filename)->default_value("cappeen_report.txt"), "Set filename for report.")
			("time,t", po::value<int>(&time_min)->default_value(15), "Time duration (minutes) for collection.")
			("log,l", "Log output to screen.")
			("priority,p", po::value<std::string>(&collection_priority)->default_value("gsm"), "Set technology priority for collection.")
			("sweep_gsm,g", po::value<std::vector<int>>(&gsm_bands)->multitoken(),
			"Set GSM bands to sweep.\n"
			"Example usage: 'sweep_gsm = 850'.\n"
			"Possible bands are:\n"
			"  850  [{869 - 894}]\n"
			"  900  [{925 - 960}]\n"
			"  1800 [{1805 - 1880}]\n"
			"  1900 [{1930 - 1990}]\n"
			)
			("sweep_wcdma,w", po::value<std::vector<int>>(&umts_bands)->multitoken(),
			"Set WCDMA bands to sweep.\n"
			"Example usage: 'sweep_wcdma = 850'.\n"
			"Possible bands are:\n"
			"  850  [Band 5 {869 - 894}]\n"
			"  900  [Band 8 {925 - 960}]\n"
			"  1800 [Band 3 {1805 - 1880}]\n"
			"  1900 [Band 2 {1930 - 1990}]\n"
			"  2100 [Band 1 & 4 {2110 - 2170}]\n"
			)
			("sweep_lte,l", po::value<std::vector<int>>(&lte_bands)->multitoken(),
			"Set LTE bands to sweep.\n"
			"Example usage: 'sweep_lte = 20'.\n"
			"Possible bands are:\n"
			"  20  [Band 20 {869 - 894}]\n"
			"  5  [Band 5 {869 - 894}]\n"
			"  8  [Band 8 {925 - 960}]\n"
			"  3 [Band 3 {1805 - 1880}]\n"
			"  2 [Band 2 {1930 - 1990}]\n"
			"  4 [Band 4 {2110 - 2155}]\n"
			"  1 [Band 1 {2110 - 2170}]\n"
			"  7 [Band 7 {2620 - 2690}]\n"
			)
			("upload_license,u", po::value<std::string>(), "Upload new license to scanner.  Include full path and filename.")
			("upload_license_hardware_id,s", po::value<std::string>(), "Hardware ID used when uploading a license.  Only necessary when overwriting a corrupt license.")
			("iterations,i", po::value<int>(&iterations)->default_value(1))
			("perform_quick_scan,q", po::value<bool>(&perform_quick_scan)->default_value(false), "Perfrom quick scan.")
			;

		// Read command line.
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		if(vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}
		vm.notify();

		// Read config file.  
		std::ifstream config_file("console.config");
		if(!config_file)
			std::cout << "Unable to open config file named \"console.config\"" << std::endl;
		else {
			po::store(po::parse_config_file(config_file, desc), vm);
			vm.notify();
		}

		// Begin Cappeen initialization.

		// The cappeen_delegate has to be created before initializing the beagle class.
		// It derives from the beagle_delegate class which allows the API to communicate
		// asynchronously, passing over info such as errors, warnings, and power measurements thru
		// callback functions.  The least amount of work possible should be done within the callback 
		// functions because the internal API processing threads are calling them directly.
		boost::shared_ptr<cappeen_delegate> c_delegate(new cappeen_delegate);

		// The api_interface wraps the beagle class and performs beagle's initialize and clean_up using RAII.  
		boost::shared_ptr<cappeen_interface> api_interface(new cappeen_wrapper(c_delegate.get()));

		// The cappeen_dispatcher runs a boost thread which monitors output from the cappeen_delegate.
		cappeen_dispatcher c_dispatcher(c_delegate, base_filename, vm.count("log") != 0);

		// Output beagle_api_version.  This function can be used without initializing the API.
		simple_logger::instance().log(std::string("Running cappeen api version: ") + api_interface->api_version());

		// The cappeen_command_handler mainly handles the additional logic that comes with opening/closing a beagle unit, 
		// starting/stopping collection and the additional beagle functions.
		cappeen_command_handler c_command_handler(api_interface);

		std::vector<beagle_api::TECHNOLOGIES_AND_BANDS>  tech_bands;

		// Upload license before we connect to a unit.  Necessary if the hardware unit has a corrupt license.
		if(vm.count("upload_license") && vm.count("upload_license_hardware_id"))
			c_command_handler.upload_license(vm["upload_license"].as<std::string>(), vm["upload_license_hardware_id"].as<std::string>());
		else {
			// Connect to beagle unit.  This lists possibly connected devices and opens the first in the list.
			if(c_command_handler.connect_to_scanner()) {
				// Upload license to connected unit if specified.
				if(vm.count("upload_license") && !vm.count("upload_license_hardware_id"))
					c_command_handler.upload_license(vm["upload_license"].as<std::string>());
				else {
					// The API prioritizes the technology located in location 0 of the technologies_and_band_group.
					// It will sweep all bands associated with that technology before moving to the other technology.
					cappeen_scanner::cappeen_utilities::convert_and_add_gsm_bands(tech_bands, gsm_bands);
					cappeen_scanner::cappeen_utilities::convert_and_add_umts_bands(tech_bands, umts_bands);
					cappeen_scanner::cappeen_utilities::convert_and_add_lte_bands(tech_bands, lte_bands);

					
					for(int i = 0; i < iterations; ++i) {
						// Wait for time_ms then stop collection and exit.
						auto start = std::chrono::high_resolution_clock::now();
						while(std::chrono::high_resolution_clock::now() - start < std::chrono::minutes(time_min)) {
							if(!c_dispatcher.is_collecting()) {
								c_command_handler.start_collection(tech_bands, perform_quick_scan);
							}
							std::this_thread::sleep_for(std::chrono::milliseconds(500));
							if(c_dispatcher.has_fatal_error_occurred()) {
								c_dispatcher.reset_error();
								std::cout << "Error has occurred.  Attempting to recover..." << std::endl;
								std::this_thread::sleep_for(std::chrono::seconds(2));
								c_command_handler.connect_to_scanner();
								continue;
							}
						}

						if(c_dispatcher.is_collecting())
							c_command_handler.stop_collection();
					}
				}
			}

			if(!c_dispatcher.has_fatal_error_occurred() && c_command_handler.is_scanner_open())
				c_command_handler.close_scanner();
		}

		// Stop dispatching thread.
		c_dispatcher.shut_down();

		if(should_report) {
			generate_report(vm, tech_bands, c_dispatcher);
		}
	}
	catch(std::exception &error) {
		std::cout << error.what() << std::endl;
	}
	catch(...) {
		std::cout << "Unknown error." << std::endl;
	}

	//do {
	//	std::cout << '\n' << "Press the Enter key to continue.";
	//}
	//while(std::cin.get() != '\n');

	return 0;
}

template<typename Data>
std::vector<typename Data> find_max_sls(const std::vector<typename Data> &v) {
	using namespace rf_phreaker;
	auto t = v;
	if(t.empty()) return t;
	std::sort(t.begin(), t.end(), [&](meas_stats &a, meas_stats&b) {
		if(a.freq_ == b.freq_)
			return a.max_sl_ > b.max_sl_;
		else
			return a.freq_ < b.freq_;
	});
	frequency_type current_freq = -1;
	t.erase(std::remove_if(t.begin(), t.end(), [&](meas_stats &a) {
		if(current_freq == a.freq_)
			return true;
		else {
			current_freq = a.freq_;
			return false;
		}
	}), t.end());
	return t;
}

void generate_report(const boost::program_options::variables_map &vars, const std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const cappeen_scanner::cappeen_dispatcher &dispatcher) {
	using namespace rf_phreaker;
	using namespace cappeen_scanner;

	auto filename = vars["report_filename"].as<std::string>() + "_" + std::to_string(dispatcher.id()) + "_" + rf_phreaker::current_date_time_string() + ".txt";
	std::ofstream f(filename);
	if(f) {
		f << "scanner id\t" << dispatcher.id() << std::endl;
		f << "scanner serial\t" << dispatcher.serial() << std::endl;
		f << "runtime (min)\t" << vars["time"].as<int>() << std::endl;
		f << "iterations\t" << vars["iterations"].as<int>() << std::endl;
		f << "error count\t" << dispatcher.error_count() << std::endl;
		f << "bands collected\t";
		for(auto &i : tech_bands)
			f << cappeen_api::tech_band_to_string(i) << "   ";
		f << "\n\n";

		auto sats = dispatcher.gps_stats_.get_stats();
		if(!sats.empty()) {
			{
				std::sort(sats.begin(), sats.end(), [&](rf_phreaker::gps_stats &a, rf_phreaker::gps_stats&b) {
					return a.sats_tracking_ > b.sats_tracking_;
				});
				f << "max_satelites_tracked\t" << sats.begin()->sats_tracking_ << std::endl;
				auto k = sats.begin()->sats_tracking_;
				auto seconds_seen = 0;
				for(auto &i : sats) {

					if(k != i.sats_tracking_)
						break;
					seconds_seen += i.seconds_seen_;
				}
				f << "max_satelites_tracked_time(min)\t" << sats.begin()->seconds_seen_ / 3600.0 << std::endl;
			}
			{
				std::sort(sats.begin(), sats.end(), [&](rf_phreaker::gps_stats &a, rf_phreaker::gps_stats&b) {
					return a.sats_visible_ > b.sats_visible_;
				});
				f << "max_satelites_visible\t" << sats.begin()->sats_visible_ << std::endl;
				auto k = sats.begin()->sats_visible_;
				auto seconds_seen = 0;
				for(auto &i : sats) {
					if(k != i.sats_visible_)
						break;
					seconds_seen += i.seconds_seen_;
				}
				f << "max_satelites_visible_time(min)\t" << seconds_seen / 3600.0 << std::endl;
			}
			{
				std::sort(sats.begin(), sats.end(), [&](rf_phreaker::gps_stats &a, rf_phreaker::gps_stats&b) {
					return a.sats_tracking_ < b.sats_tracking_;
				});
				f << "min_satelites_tracked\t" << sats.begin()->sats_tracking_ << std::endl;
				auto k = sats.begin()->sats_tracking_;
				auto seconds_seen = 0;
				for(auto &i : sats) {
					if(k != i.sats_tracking_)
						break;
					seconds_seen += i.seconds_seen_;
				}
				f << "min_satelites_tracked_time(min)\t" << sats.begin()->seconds_seen_ / 3600.0 << std::endl;
			}
			{
				std::sort(sats.begin(), sats.end(), [&](rf_phreaker::gps_stats &a, rf_phreaker::gps_stats&b) {
					return a.sats_visible_ < b.sats_visible_;
				});
				f << "min_satelites_visible\t" << sats.begin()->sats_visible_ << std::endl;
				auto k = sats.begin()->sats_visible_;
				auto seconds_seen = 0;
				for(auto &i : sats) {
					if(k != i.sats_visible_)
						break;
					seconds_seen += i.seconds_seen_;
				}
				f << "min_satelites_visible_time(min)\t" << seconds_seen / 3600.0 << std::endl;
			}
		}

		f << "\n\n\ntech\t";
		meas_stats::output_header(f);

		auto umts_max_stats = find_max_sls(dispatcher.umts_stats_.get_stats());
		for(auto &i : umts_max_stats) {
			f << "UMTS\t";
			rf_phreaker::operator<<(f, i) << std::endl;
		}
		auto lte_max_stats = find_max_sls(dispatcher.lte_stats_.get_stats());
		for(auto &i : lte_max_stats) {
			f << "LTE\t";
			rf_phreaker::operator<<(f, i) << std::endl;
		}
		auto gsm_max_stats = find_max_sls(dispatcher.gsm_stats_.get_stats());
		for(auto &i : gsm_max_stats) {
			if(i.identifier_ == -1)
				continue;
			f << "GSM\t";
			rf_phreaker::operator<<(f, i) << std::endl;
		}
	}
	else
		std::cout << "Unable to create report!";

}