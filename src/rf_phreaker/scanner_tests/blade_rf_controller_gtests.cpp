#include "gtest/gtest.h"

#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/benchmark.h"
#include "rf_phreaker/common/concurrent.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include <boost/lexical_cast.hpp>

using namespace rf_phreaker::scanner;

TEST(BladeControllerTest, TestBladeControllerGeneral)
{
	try {
		blade_rf_controller blade;

		// We ask twice because the first time we don't recieve a valid serial.  An error occurs inside libusb...
		auto scanner_list = blade.list_available_scanners();
		if(scanner_list.size() && (*scanner_list.begin())->id() == "")
			scanner_list = blade.list_available_scanners();

		if(scanner_list.size()) {
			auto scanner_id = (*scanner_list.begin())->id();

			blade.open_scanner(scanner_id);

			blade.do_initial_scanner_config();

			auto blade_info = blade.get_scanner_blade_rf();

			rf_phreaker::benchmark b("blade_benchmark_1.txt", true);

			b.start_timer();

			rf_phreaker::frequency_type nyc_umts_freq = 2152500000;
			rf_phreaker::frequency_type nyc_lte_freq = 2140000000; // 10 mhz

            const int num_iterations = 10;
			std::string base_filename = "blade_samples_";
			rf_phreaker::frequency_type freq = mhz(925);
			size_t time_ms = 50;
            rf_phreaker::bandwidth_type bandwidth = mhz(4);
			int sampling_rate = khz(7680);
			rf_phreaker::scanner::gain_type gain(lms::LNA_MAX, 30, 0);

			measurement_info data;

			for(int i = 0; i < num_iterations; ++i) {			
				//freq += mhz(1);
				
				gain.rxvga2_ < 20 ?	gain.rxvga2_ = 30 :	gain.rxvga2_ = 0;

				data = blade.get_rf_data(freq, time_ms, bandwidth, gain, sampling_rate);

                std::string name = base_filename + boost::lexical_cast<std::string>(i) +".txt";
                std::ofstream file(name.c_str());
                file << data;
			}
			b.stop_timer();

			blade_info = blade.get_scanner_blade_rf();

			std::string str;
			str.append("release_mode\t")
				.append("vtune\t")
				.append("blade_rf\t")
				.append("\taverage_transer_rate B/s:\t")
				.append(boost::lexical_cast<std::string>(b.total_time_elapsed().wall / ((double)data.get_iq().length() * sizeof(int16_t)* 2 * (num_iterations))))
				.append("\tsnapshot_time:\t")
				.append(boost::lexical_cast<std::string>(time_ms));
			b.output_time_elapsed(str);
		}
	}
	catch(const std::exception &err) {
		std::cout << err.what() << std::endl;
		ASSERT_TRUE(0)  << "Error while testing with the bladeRF.  Error = " << err.what();
	}
}
