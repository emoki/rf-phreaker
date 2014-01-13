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

		auto scanner_list = blade.list_available_scanners();

		if(scanner_list.size()) {
			auto scanner_id = (*scanner_list.begin())->id();

			blade.open_scanner(scanner_id);

			blade.do_initial_scanner_config();

			auto blade_info = blade.get_scanner_blade_rf();

			rf_phreaker::benchmark b("blade_benchmark_1.txt", true);

			b.start_timer();

			const int num_iterations = 100;
			std::string base_filename = "blade_samples_";
			rf_phreaker::frequency_type freq = mhz(886);
			size_t time_ms = 40;
			rf_phreaker::bandwidth_type bandwidth = mhz(1);
			int sampling_rate = mhz(1);
			int vga1 = 25;
			int vga2 = 25;
			auto lna_gain = lms::LNA_MAX;
			measurement_info data;

			for(int i = 0; i < num_iterations; ++i) {			
				data = blade.get_rf_data(freq, time_ms, sampling_rate, bandwidth, vga1, vga2, lna_gain);

				//std::string name = base_filename + boost::lexical_cast<std::string>(i) +".txt";
				//std::ofstream file(name.c_str());
				//file << data;
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
	}
}