#include "gtest\gtest.h"

#include "processing_graph.h"
#include "processing_lte.h"
#include "scanner_controller.h"

#include <windows.h>

TEST(ProcessingGraph, TestGeneral)
{
		try
		{
			processing_graph graph;

			basic_processing_lte test;
			basic_processing_lte test_copy_lte(test);
			lte_package package;
			lte_package test_copy(package);
		
			tbb::flow::graph g;
			auto lte = std::make_shared<tbb::flow::function_node<measurement_info, lte_package>>(g, 1, basic_processing_lte());		
			
			scanner_controller controller;
	
			auto scanner_list = controller.list_available_scanners().get();

			if(scanner_list.size())
			{
				auto scanner_id = (*scanner_list.begin())->id();

				controller.open_scanner(scanner_id);

				controller.do_initial_scanner_config();

				graph.initialize(controller);

					
				// 2137.5 mhz - nyc lte signal.
				//collection_parameters cp(2137500000, 50, khz(1920), khz(1920));
				
				// das signal
				collection_parameters cp(1875000000, 70, mhz(4), khz(7680));
				
				graph.start(cp);

				//Sleep(100000);

				//graph.cancel();

				graph.wait();

				controller.close_scanner();
			} 
		}
		catch(const std::exception &err)
		{
			std::cout << err.what();
		}
}
