#pragma once

#include "gtest/gtest.h"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "rf_phreaker/gsm_analysis/gsm_analysis.h"
#include "rf_phreaker/gsm_analysis/gsm_measurement_io.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include "rf_phreaker/common/frequency_bin_calculator.h"

TEST(GsmAnalysisTests, TestGeneral) {
	using namespace rf_phreaker;

	const int num_iterations = 10000;

	// we can import measurements using a file handle directly (ascii io) or using boost::serialization. boost serialization allows 
	// more flexibility and when in binary mode, it is faster and smaller size.
	bool use_boost_archive = true;

	// we are using a relative path to load the test files.  it follows the convention of a out-of-source build using cmake.  
	// the build directory is located on the same level as the git root directory.  the git root directory's name is lte_phreaker
	// and the test_files are located within test_files. so the directory struct would look like:
	// ./cmake_build_directory			(cmake build directory)
	// ./lte_phreaker					(git root directory)
	// ./lte_phreaker/test_files		(directory containing test data)

	std::string folder_path =
		"../../../../rf_phreaker/test_files/gsm/";

	std::string prefix =
		//"gsm_layer_3_1432609567_";
		"umts_sweep_1435430575_";

	std::string suffix = ".bin";
	//std::string suffix = ".txt";

	rf_phreaker::scanner::measurement_info signal;

	gsm_config config;
	config.preform_sync_correlations(true);
	config.max_signal_length(292500);
	gsm_analysis analysis(config);

	for(int i = 0; i < num_iterations; ++i) {
		std::string full_path_and_filename = folder_path + prefix + boost::lexical_cast<std::string>(i) + suffix;

		std::ifstream file(full_path_and_filename, use_boost_archive ? std::ios_base::binary : std::ios_base::in);

		if(file) {
			if(use_boost_archive) {
				boost::archive::binary_iarchive ia(file);
				ia & signal;
			}
			else
				file >> signal;

			gsm_measurements meas_group;

			auto status = analysis.cell_search(signal, meas_group, true);

			EXPECT_EQ(0, status);

			static std::ofstream output_file("gsm_measurements.txt");
			static bool write_header = true;
			if(write_header) {
				output_file << "filename\tfile_num\tfreq\t";
				output_gsm_meas_debug_header(output_file) << "\n";
				write_header = false;
			}

			for(auto &gsm : meas_group) {
				std::cout << full_path_and_filename << "\t" << i << "\t" << signal.frequency() / 1e6 << "\t" << gsm << std::endl;
				output_file << full_path_and_filename << "\t" << i << "\t" << signal.frequency() / 1e6 << "\t" << gsm << std::endl;
			}

			frequency_bin_calculator calc;
			calc.calculate_power_in_bins(signal.get_iq(), signal.sampling_rate(), khz(200), 131072);

			int i = 1600000;
			double p = calc.get_power_in_bin(i);
			int j = 0;
		}
	}
}