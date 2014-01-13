#include "gtest/gtest.h"
 
#include "rf_phreaker/scanner/scanner_controller.h"
#include "rf_phreaker/common/benchmark.h"
#include "rf_phreaker/common/concurrent.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker::scanner;

TEST(ScannerControllerTest, TestScannerControllerSync)
{
	rf_phreaker::benchmark b("async_benchmark_1.txt", true);
	b.start_timer();
	{
		try
		{
			scanner_controller controller;
	
			auto scanner_list = controller.list_available_scanners().get();

			if(scanner_list.size())
			{
				auto scanner_id = (*scanner_list.begin())->id();

				controller.open_scanner(scanner_id);

				controller.do_initial_scanner_config();

				{
					const int num_iterations = 20;
					size_t time_ms = 100;
					rf_phreaker::benchmark b2("sync_benchmark_2.txt", true);
					
					auto data = controller.get_rf_data(mhz(886), time_ms, mhz(8), mhz(28)).get();
					
					b2.start_timer();
					for(int i = 0; i < num_iterations; ++i)
						data = controller.get_rf_data(mhz(886), time_ms, mhz(8), mhz(28)).get();
					b2.stop_timer();
					std::string str;
					str.append("release_mode\t")
						.append("no vtune\t")
						.append("fake_usb\t")
						.append("\taverage_transger_rate:\t")
						.append(boost::lexical_cast<std::string>((b.total_time_elapsed().wall/(double)data.get_iq().length())/num_iterations))
						.append("\tusb_transfer_size:\t")
						.append(boost::lexical_cast<std::string>(4096))
						.append("\tsnapshot_time:\t")
						.append(boost::lexical_cast<std::string>(time_ms));
					b2.output_time_elapsed(str);
				}

				//controller.close_scanner();
			}
		}
		catch(const std::exception &err)
		{
			std::cerr << err.what() << std::endl;
		}
		
	}
	b.stop_timer();
	b.output_time_elapsed();

	scanner_controller sc;
	auto list = sc.list_available_scanners().get();
	if(list.size())
	{
		auto scanner_id = (*list.begin())->id();

		sc.open_scanner(scanner_id);

		sc.do_initial_scanner_config();
	}
}
