#include "gtest/gtest.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/lte_analysis/lte_io.h"
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/common/common_serialization.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include <boost/lexical_cast.hpp>
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include <iostream>

using namespace rf_phreaker;

TEST(LteAnalysisTests, TestGeneral)
{
	try {
		const int num_iterations = 10000;

		// We can import measurements using a file handle directly (ascii io) or using boost::serialization. boost serialization allows 
		// more flexibility and when in binary mode, it is faster and smaller size.
		bool use_boost_archive = true;

		// We are using a relative path to load the test files.  It follows the convention of a out-of-source build using cmake.  
		// The build directory is located on the same level as the git root directory.  The git root directory's name is lte_phreaker
		// and the test_files are located within test_files. So the directory struct would look like:
		// ./cmake_build_directory			(cmake build directory)
		// ./lte_phreaker					(git root directory)
		// ./lte_phreaker/test_files		(directory containing test data)
		std::string folder_path =
			//"../../../../rf_phreaker/test_files/cobham3/"
			//"../../../../rf_phreaker/test_files/cobham8/"
			"../../../../rf_phreaker/test_files/cobham9/"
			;

		std::string prefix = 
			//"lte_layer_3_1413296677_"
			//"lte_layer_3_1437488969_"
			"lte_layer_3_1438857614_"
			;
		
		std::string suffix = ".bin";
		//std::string suffix = ".txt";


		lte_config config;
 		//rf_phreaker::raw_signal info;
		rf_phreaker::scanner::measurement_info info;

		std::vector<layer_3_information::lte_sib_type> wanted;
		wanted.push_back(layer_3_information::SIB_1);
		wanted.push_back(layer_3_information::SIB_3);
		wanted.push_back(layer_3_information::SIB_4);
		wanted.push_back(layer_3_information::SIB_5);
		wanted.push_back(layer_3_information::SIB_6);
		wanted.push_back(layer_3_information::SIB_7);
		wanted.push_back(layer_3_information::SIB_8);
		config.wanted_si(wanted);
		lte_analysis analysis(config);

		for(int i = 0; i < num_iterations; ++i) {
			std::string full_path_and_filename = folder_path + prefix + boost::lexical_cast<std::string>(i)+suffix;

			std::ifstream file(full_path_and_filename, use_boost_archive ? std::ios_base::binary : std::ios_base::in);

			if(file) {
				if(use_boost_archive) {
					boost::archive::binary_iarchive ia(file);
					ia & info;
				}
				else
					file >> info;

				{
					//std::ofstream t(folder_path + "old_format_" + prefix + boost::lexical_cast<std::string>(i)+suffix);
					//t << info;
					//continue;
					//std::ofstream t(folder_path + "new_format_" + prefix + boost::lexical_cast<std::string>(i)+suffix, std::ios::binary);
					//boost::archive::binary_oarchive oa(t);
					//oa & info;
					//continue;
				}

				lte_measurements lte_meas;
				
				int status = analysis.cell_search(info, lte_meas, int(info.time_ns() / 1e6 / 5));
				EXPECT_EQ(0, status);

				for(int j = 0; j < (int)lte_meas.size(); ++j) {
					if(lte_meas[j].NumAntennaPorts != LteNumAntennaPorts::LteAntPorts_Unknown) {
						status = analysis.decode_layer_3(info, lte_meas, int(info.time_ns() / 1e6 / 5), j);
						EXPECT_EQ(0, status);
					}
				}
				static std::ofstream output_file("lte_measurements.txt");
				static bool write_header = true;
				if(write_header) {
					output_file << "filename\tfile_num\tfreq\t";
					output_lte_meas_debug_header(output_file) << "\n";
					write_header = false;
				}

				for(auto &lte : lte_meas) {
					std::cout << full_path_and_filename << "\t" << i << "\t" << info.frequency() / 1e6 << "\t" << lte << std::endl;
					output_file << full_path_and_filename << "\t" << i << "\t" << info.frequency() / 1e6 << "\t" << lte << std::endl;
				}
			}
		}
	}
	catch(const std::exception &err)
	{
		std::cout << "lte_analysis_gtests exception:  " << err.what() << std::endl;
	}
}