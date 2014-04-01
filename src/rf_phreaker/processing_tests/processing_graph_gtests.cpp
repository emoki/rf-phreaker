#include "gtest/gtest.h"

#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/scanner/blade_rf_controller_async.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/benchmark.h"
#include "rf_phreaker/qt_specific/settings_io.h"
#include "stdafx.h"

TEST(ProcessingGraph, TestGeneral)
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

			initialize_collection_info_defaults(config);

			collection_info_containers containers;
			//containers.push_back(collection_info_container(UMTS_SWEEP, true));
			containers.push_back(collection_info_container(UMTS_LAYER_3_DECODE, false));
			auto it = containers.begin();
			//auto &umts_sweep = (*it++);
			auto &umts_layer_3 = (*it++);
			//for(rf_phreaker::frequency_type i = mhz(869); i < mhz(893); i += khz(100))
			for(rf_phreaker::frequency_type i = mhz(2110); i < mhz(2170); i += khz(100))
				//umts_sweep.adjust(add_collection_info(umts_sweep_collection_info(i, UMTS_OPERATING_BAND_4)));
				//umts_sweep.adjust(add_collection_info(umts_sweep_collection_info(i, UMTS_OPERATING_BAND_5)));
			//umts_sweep.adjust(add_collection_info(umts_sweep_collection_info(876800000)));
			umts_layer_3.adjust(add_collection_info(umts_layer_3_collection_info(khz(2147500), UMTS_OPERATING_BAND_5)));

			data_output_async output;
			output.set_standard_output(true);

			processing_graph graph;
			
			graph.start(&blade, &output, containers, config);

			//graph.wait();

			std::this_thread::sleep_for(std::chrono::minutes(45));
			//std::this_thread::sleep_for(std::chrono::seconds(45));

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
