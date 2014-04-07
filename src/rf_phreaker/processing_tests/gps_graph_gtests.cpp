#include "gtest/gtest.h"

#include "rf_phreaker/processing/gps_graph.h"
#include "rf_phreaker/scanner/blade_rf_controller_async.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/qt_specific/settings_io.h"
#include "stdafx.h"

TEST(ProcessingGpsGraph, TestGeneral)
{
	using namespace rf_phreaker;
	using namespace rf_phreaker::scanner;
	using namespace rf_phreaker::processing;

	try {
		blade_rf_controller_async blade;

		// We ask twice because the first time we don't recieve a valid serial.  An error occurs inside libusb...
		auto scanner_list = blade.list_available_scanners().get();
		if(scanner_list.size() && (*scanner_list.begin())->id() == "")
			scanner_list = blade.list_available_scanners().get();

		if(scanner_list.size()) {
			auto scanner_id = (*scanner_list.begin())->id();

			blade.open_scanner(scanner_id);

			blade.do_initial_scanner_config();

			rf_phreaker::settings config;
			rf_phreaker::settings_io io("rf_phreaker_graph_test", "cappeen");
			io.read(config);


			data_output_async output;
			output.set_standard_output(true).get();
			gps_graph graph;

			graph.start(&blade, &output, config);

			//graph.wait();

			std::this_thread::sleep_for(std::chrono::seconds(1));

			//std::this_thread::sleep_for(std::chrono::seconds(10));

			graph.cancel_and_wait();
		}
		else
			std::cout << "Unable to communicate to the scanner." << std::endl;
	}
	catch(const rf_phreaker_error &err) {
		std::cout << err.what();
		EXPECT_TRUE(0);
	}
}
