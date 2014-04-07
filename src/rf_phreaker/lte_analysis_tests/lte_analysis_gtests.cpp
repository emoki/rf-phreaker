#include "gtest/gtest.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/lte_analysis/lte_io.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/common/common_utility.h"
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace rf_phreaker;

TEST(LteAnalysisTests, TestGeneral)
{
	try {
		const int num_iterations = 60;
		//std::string base_filename = "../../../../rf_phreaker/test_files/blade_samples_lte_4875_";
		std::string base_filename = "../../../../rf_phreaker/test_files/blade_samples_lte_739_";
		//std::string base_filename = "../../../../rf_phreaker/test_files/blade_samples_4875_";
		//std::string base_filename = "../../../../rf_phreaker/test_files/signal_lte_4875_";

		lte_config config;
		config.sampling_rate(khz(4875));
		config.clock_rate(khz(4875));
		config.max_signal_length(204750);
		rf_phreaker::scanner::measurement_info info;

		lte_analysis analysis(config);

		for(int i = 5; i < num_iterations; ++i) {
			std::ifstream file(base_filename + boost::lexical_cast<std::string>(i) + ".txt");
			if(file) {
				file >> info;

				lte_measurements lte_meas;
				
				int status = analysis.cell_search(info, lte_meas, int(info.time_ns() / 1e6 / 5));
				EXPECT_EQ(0, status);

				status = analysis.decode_layer_3(info, lte_meas, int(info.time_ns() / 1e6 / 5));
				//EXPECT_EQ(0, status);
				
				for(auto &lte : lte_meas) {

					std::cout <<
						i << "\t" <<
						info.frequency() / 1e6 << "\t" <<
						lte << "\n";
				}
			}
		}
	}
	catch(const std::exception &err)
	{
		std::cout << "lte_analysis_gtests exception:  " << err.what() << std::endl;
	}
}