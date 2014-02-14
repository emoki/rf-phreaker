#include "gtest/gtest.h"

#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/scanner/blade_rf_controller_async.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/benchmark.h"
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


			collection_info_containers containers;
			containers.push_back(collection_info_container(umts_sweep, true));
			containers.push_back(collection_info_container(umts_layer_3_decode, false));

			auto &umts_sweep = containers[0];
			for(int i = mhz(869); i < mhz(894); i += khz(100))
				umts_sweep.adjust(add_collection_info(umts_sweep_collection_info(i)));

			processing_graph graph;


			graph.initialize(&blade, containers);

			boost::timer::auto_cpu_timer t;

			graph.start();

			//graph.wait();
			std::this_thread::sleep_for(std::chrono::minutes(5));

			graph.cancel();
		}
		else
			std::cout << "Unable to communicate to the scanner." << std::endl;
	}
	catch(const std::exception &err) {
		std::cout << err.what();
		EXPECT_TRUE(0);
	}
}
