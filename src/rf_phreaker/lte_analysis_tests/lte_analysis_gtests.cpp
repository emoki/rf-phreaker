#include "gtest/gtest.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/lte_analysis/lte_io.h"
#include "rf_phreaker/common/benchmark.h"
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/common/common_serialization.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include "rf_phreaker/scanner/signal_level_calculator.h"
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
		bool apply_freq_shift = false;

		// We are using a relative path to load the test files.  It follows the convention of a out-of-source build using cmake.  
		// The build directory is located on the same level as the git root directory.  The git root directory's name is lte_phreaker
		// and the test_files are located within test_files. So the directory struct would look like:
		// ./cmake_build_directory			(cmake build directory)
		// ./lte_phreaker					(git root directory)
		// ./lte_phreaker/test_files		(directory containing test data)
		std::string folder_path =
			//"../../../../rf_phreaker/test_files/cobham3/"
			//"../../../../rf_phreaker/test_files/cobham8/"
			//"../../../../rf_phreaker/test_files/cobham9/"
			"../../../../rf_phreaker/test_files/lte_sweep/"
			;

		std::string prefix = 
			//"lte_layer_3_1413296677_"
			//"lte_layer_3_1437488969_"
			//"lte_layer_3_1438857614_"
			"lte_sweep_1458187885_"
			//"lte_sweep_1458829888_"
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
		config.pbch_decoding_threshold_db(-20);
		config.minimum_relative_peak_threshold(1 / 9.0);
		config.sampling_rate(khz(/*3840*/1920));
		lte_analysis analysis(config);

		static benchmark b;
		b.open_benchmark("lte_benchmark_.txt", false);

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

				if(apply_freq_shift) {
					static std::ofstream freq_shift_file1("freq_shift.txt");
					static bool write_header = true;
					if(write_header) {
						freq_shift_file1 << "filename\tfile_num\tfreq\tadj_freq\trms\t";
						output_lte_meas_debug_header(freq_shift_file1) << "\n";
						write_header = false;
					}
					if(info.frequency() % khz(100) == 0) {
						bool fs2 = false;
						power_info_group rms_group;

						b.start_timer();
						analysis.cell_search_sweep(info, lte_meas, int(info.time_ns() / 1e6 / 5), -khz(500), khz(500), khz(100), &rms_group);
						b.stop_timer();
						b.output_time_elapsed();


						for(auto &j : lte_meas) {
							fs2 = true;
							freq_shift_file1 <<
								full_path_and_filename << "\t" << i << "\t" << info.frequency() << "\t" <<
								(info.frequency() + j.intermediate_frequency_) << "\t" << 
								std::find_if(rms_group.begin(), rms_group.end(), [&](const power_info &p) {
								return info.frequency() + j.intermediate_frequency_ == p.freq_;
								})->avg_rms_ << "\t" << j << std::endl;
						}
						if(!fs2) {
							int k = 0;
							freq_shift_file1 <<
								i << "\t" << info.frequency()  << "\t" <<
								(info.frequency() + k) << "\t" << 
								std::find_if(rms_group.begin(), rms_group.end(), [&](const power_info &p) {
								return info.frequency() + k == p.freq_;
								})->avg_rms_ << "\t" << std::endl;
						}
						
						lte_measurement pss0, pss1, pss2;
						pss0.PschRecord.NormCorr = -99;
						pss1.PschRecord.NormCorr = -99;
						pss2.PschRecord.NormCorr = -99;
						for(const auto &k : lte_meas) {
							if(k.PschRecord.ID == 0 && k.PschRecord.NormCorr > pss0.PschRecord.NormCorr)
								pss0 = k;
							else if(k.PschRecord.ID == 1 && k.PschRecord.NormCorr > pss1.PschRecord.NormCorr)
								pss1 = k;
							else if(k.PschRecord.ID == 2 && k.PschRecord.NormCorr > pss2.PschRecord.NormCorr)
								pss2 = k;
						}

						lte_meas.clear();
						if(pss0.PschRecord.NormCorr > -99)
							lte_meas.push_back(pss0);
						if(pss1.PschRecord.NormCorr > -99)
							lte_meas.push_back(pss1);
						if(pss2.PschRecord.NormCorr > -99)
							lte_meas.push_back(pss2);

						static std::ofstream freq_shift_file2("freq_shift_2.txt");
						static bool write_header2 = true;
						if(write_header2) {
							freq_shift_file2 << "filename\tfile_num\tfreq\tadj_freq\trms\t";
							output_lte_meas_debug_header(freq_shift_file2) << "\n";
							write_header2 = false;
						}
						for(auto &j : lte_meas) {
							fs2 = true;
							freq_shift_file2 <<
								full_path_and_filename << "\t" << i << "\t" << info.frequency() << "\t" <<
								(info.frequency() + j.intermediate_frequency_) << "\t" << 
								std::find_if(rms_group.begin(), rms_group.end(), [&](const power_info &p) {
								return info.frequency() + j.intermediate_frequency_ == p.freq_;
								})->avg_rms_ << "\t" << j << std::endl;
						}
						if(!fs2) {
							int k = 0;
							freq_shift_file2 <<
								i << "\t" << info.frequency() << "\t" <<
								(info.frequency() + k) << "\t" << 
								std::find_if(rms_group.begin(), rms_group.end(), [&](const power_info &p) {
								return info.frequency() + k == p.freq_;
								})->avg_rms_ << "\t" << std::endl;
						}
					}
				}
				else {
					int status = analysis.cell_search(info, lte_meas, int(info.time_ns() / 1e6 / 5));
					EXPECT_EQ(0, status);
				}

				for(int j = 0; j < (int)lte_meas.size(); ++j) {
					if(lte_meas[j].NumAntennaPorts != LteNumAntennaPorts::LteAntPorts_Unknown) {
						int status = analysis.decode_layer_3(info, lte_meas, int(info.time_ns() / 1e6 / 5), j);
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
					lte.estimated_rsrp = scanner::signal_level_calculator::calculate_sl(lte.estimated_rsrp, info);
					lte.estimated_rssi = scanner::signal_level_calculator::calculate_sl(lte.estimated_rssi, info);
					std::cout << full_path_and_filename << "\t" << i << "\t" << info.frequency() / 1e6 << "\t" << lte << std::endl;
					output_file << full_path_and_filename << "\t" << i << "\t" << info.frequency() / 1e6 << "\t" << lte << std::endl;
				}
			}
		}
		b.output_total_time_elapsed();
	}
	catch(const std::exception &err)
	{
		std::cout << "lte_analysis_gtests exception:  " << err.what() << std::endl;
	}
}