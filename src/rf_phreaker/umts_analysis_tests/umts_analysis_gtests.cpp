#include "gtest/gtest.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include <boost/lexical_cast.hpp>
#include <iostream>

TEST(UmtsAnalysisTests, TestGeneral)
{
	try {
		const int num_iterations = 10;
		std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_4875_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/signal_";

		umts_config config;
		config.sample_rate(3840000);
		config.clock_rate(3840000);
		config.up_factor(1);
		config.down_factor(1);
		config.max_signal_length(231424);

		// old hardware
		//config.sample_rate(4875000);
		//config.clock_rate(9750000);
		//config.up_factor(325);
		//config.down_factor(256);
		//config.max_signal_length(655345);

		umts_analysis analysis;
		analysis.set_config(config);

		for(int i = 0; i < num_iterations; ++i) {
			std::ifstream file(base_filename + boost::lexical_cast<std::string>(i) + ".txt");
			if(file) {
				rf_phreaker::scanner::measurement_info info;
				//rf_phreaker::raw_signal info;
				file >> info;

				umts_measurements umts_meas(100);
				int num_meas = umts_meas.size();
				int status = analysis.cell_search(info, &umts_meas.at(0), num_meas, 14952, umts_scan_type::full_scan_type);
				EXPECT_EQ(0, status);
			}
		}
	}
	catch(const std::exception &err)
	{
		std::cout << "umts_analysis_gtests exception:  " << err.what() << std::endl;
	}
}