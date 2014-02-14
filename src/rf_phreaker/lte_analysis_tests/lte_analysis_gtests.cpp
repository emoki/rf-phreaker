#include "gtest/gtest.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/lte_analysis/lte_io.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include <boost/lexical_cast.hpp>
#include <iostream>

TEST(LteAnalysisTests, TestGeneral)
{
	try {
		const int num_iterations = 25;
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_lte_4875_";
		std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_lte_2_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_4875_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/signal_lte_4875_";

		//lte_config config;
		//config.sample_rate(3840000);
		//config.clock_rate(3840000);
		//config.up_factor(1);
		//config.down_factor(1);
		//config.max_signal_length(231424);
		rf_phreaker::scanner::measurement_info info;

		// new hardware - 4875 samplerate
		//config.sample_rate(4875000);
		//config.clock_rate(9750000);
		//config.up_factor(325);
		//config.down_factor(256);
		//config.max_signal_length(292864);
		//rf_phreaker::scanner::measurement_info info;

		// old hardware
		//config.sample_rate(4875000);
		//config.clock_rate(9750000);
		//config.up_factor(325);
		//config.down_factor(256);
		//config.max_signal_length(655345);
		//rf_phreaker::raw_signal info;

		lte_analysis analysis;
		//analysis.set_config(config);

		for(int i = 0; i < num_iterations; ++i) {
			std::ifstream file(base_filename + boost::lexical_cast<std::string>(i) + ".txt");
			if(file) {
				file >> info;

				lte_measurements lte_meas(100);
				int num_meas = lte_meas.size();
				
				int status = analysis.cell_search(info, &lte_meas.at(0), num_meas, int(info.time_ns() / 1e6 / 5));
				EXPECT_EQ(0, status);


				
				for(int j = 0; j < num_meas; ++j) {
					status = analysis.decode_layer_3(info, &lte_meas.at(0), lte_meas.size(), int(info.time_ns() / 1e6 / 5));
					EXPECT_EQ(0, status);

					std::cout <<
						i << "\t" <<
						info.frequency() / 1e6 << "\t" <<
						lte_meas[j] << "\n";
				}
			}
		}
	}
	catch(const std::exception &err)
	{
		std::cout << "lte_analysis_gtests exception:  " << err.what() << std::endl;
	}
}