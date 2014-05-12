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
		const int end = 1000;
		std::string base_filename = "../../../../rf_phreaker/test_files/";
		//std::string prefix = "lte_layer_3_1398013472_";
		//std::string prefix = "lte_layer_3_1398017723_";
//		std::string prefix = "lte_layer_3_1398023767_";
		//std::string prefix = "lte_layer_3_1398048822_";
		std::string prefix = "lte_layer_3_1398066558_";
		std::string suffix = ".bin";
		//std::string suffix = ".txt";


		rf_phreaker::scanner::measurement_info info;
		std::shared_ptr<lte_config> config;
		std::shared_ptr<lte_analysis> analysis; 

		for(int i = 13; i <= end; ++i) {
			std::ifstream file(base_filename + prefix + boost::lexical_cast<std::string>(i) + suffix);
			
			if(!file)
				break;

			file >> info;

			if(!config.get()) {
				config.reset(new lte_config);
				config->sampling_rate((int)info.sampling_rate());
				config->clock_rate((int)info.sampling_rate());
				config->max_signal_length(info.get_iq().length());
				analysis.reset(new lte_analysis(*config));

			}
			lte_measurements lte_meas;
				
			int status = analysis->cell_search(info, lte_meas, int(info.time_ns() / 1e6 / 5));
			EXPECT_EQ(0, status);

			status = analysis->decode_layer_3(info, lte_meas, int(info.time_ns() / 1e6 / 5));
			EXPECT_EQ(0, status);
				
			static std::ofstream output_file("lte_measurements.txt");
			static bool write_header = true;
			if(write_header) {
				output_file << "file_num\tfreq\t";
				output_lte_meas_debug_header(output_file);
				write_header = false;
			}


			for(auto &lte : lte_meas) {
				std::cout << i << "\t" << info.frequency() / 1e6 << "\t" << lte << "\n";
				output_file << i << "\t" << info.frequency() / 1e6 << "\t" << lte << "\n";
			}
		}
	}
	catch(const std::exception &err)
	{
		std::cout << "lte_analysis_gtests exception:  " << err.what() << std::endl;
	}
}