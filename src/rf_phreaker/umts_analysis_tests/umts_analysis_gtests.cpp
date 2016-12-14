#include "gtest/gtest.h"
#include <iostream>
#include <thread>
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/umts_analysis/umts_io.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include <boost/lexical_cast.hpp>
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

using namespace rf_phreaker;

TEST(UmtsAnalysisTests, TestGeneral)
{
	try {
		const int num_iterations = 10000;

		// We can import measurements using a file handle directly (ascii io) or using boost::serialization. boost serialization allows 
		// more flexibility and when in binary mode, it is faster and smaller size.
		bool use_boost_archive = true;
		bool apply_freq_shift = true;

		std::string folder_path = 
			//"../../../../rf_phreaker/test_files/"
			//"../../../../rf_phreaker/test_files/umts_shift/"
			//"../../../../rf_phreaker/test_files/umts_corr_analysis/has_freq_error/"
			"../../../../rf_phreaker/test_files/umts_975_sample_rate/"
			;
		
		std::string prefix =
			//"umts_sweep_1397750536_"
			//"umts_sweep_1458751660_"
			//"umts_layer_3_1426537582_"
			"umts_layer_3_1460661150_";
		;
		std::string suffix = ".bin";
		//std::string suffix = ".txt";

		rf_phreaker::scanner::measurement_info info;

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

				umts_config config;
				config.sampling_rate((int)info.sampling_rate());
				config.clock_rate((int)info.sampling_rate());
				config.max_signal_length(info.get_iq().length());
				config.max_num_candidates(1000);
				config.num_coherent_psch_slots(14);

				umts_analysis analysis(config);

				umts_measurements group;
				
				if(apply_freq_shift) {
					static std::ofstream freq_shift_file2("umts_measurements_freq_shift.txt");
					static bool write_header = true;
					if(write_header) {
						freq_shift_file2 << "file_num\tfreq\tadj_freq\tavg_rms\t";
						output_umts_meas_debug_header(freq_shift_file2) << "\n";
						write_header = false;
					}
					if(info.frequency() % khz(100) == 0) {
						bool fs2 = false;
						power_info_group rms_group;
						analysis.cell_search_sweep(info, group, -20, 0, -khz(500), khz(500), &rms_group);
						for(auto &j : group) {
							fs2 = true;
							freq_shift_file2 <<
								i << "\t" << info.frequency() / 1e6 << "\t" <<
								(info.frequency() + j.intermediate_frequency_) / 1e6 << "\t" << 
								std::find_if(rms_group.begin(), rms_group.end(), [&](const power_info &p) {
								return info.frequency() + j.intermediate_frequency_ == p.freq_;
								})->avg_rms_ << "\t" << j << std::endl;
						}
						if(!fs2) {
							int k = 0;
							freq_shift_file2 <<
								i << "\t" << info.frequency() / 1e6 << "\t" <<
								(info.frequency() + k) / 1e6 << "\t" << 
								std::find_if(rms_group.begin(), rms_group.end(), [&](const power_info &p) {
								return info.frequency() + k == p.freq_;
								})->avg_rms_ << "\t" << std::endl;
						}
					}
				}
				else {
					int status = analysis.cell_search(info, group, -20, umts_scan_type::full_scan_type);
					EXPECT_EQ(0, status);
				}

				static std::ofstream out("umts_measurements.txt");
				static bool write_header = true;
				if(write_header) {
					out << "file_num\tfreq\t";
					output_umts_meas_debug_header(out) << "\n";
					write_header = false;
				}

				for(auto &j : group) {
					int status = analysis.decode_layer_3(info, j);
					EXPECT_EQ(0, status);

					std::cout <<
						i << "\t" <<
						info.frequency() / 1e6 << "\t" <<
						j << "\n";
					out <<
						i << "\t" <<
						info.frequency() / 1e6 << "\t" <<
						j << "\n";
				}
			}
		}
	}
	catch(const std::exception &err)
	{
		std::cout << "umts_analysis_gtests exception:  " << err.what() << std::endl;
	}
}

TEST(UmtsAnalysisTests, TestMultithreaded)
{
	try {
		const int num_iterations = 50;
		std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_umts_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_4875_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/signal_";

		umts_config config;

		// new hardware - 4875 samplerate
		config.sampling_rate(4875000);
		config.clock_rate(9750000);
		config.max_signal_length(292864);

		std::vector<umts_analysis> analyzers;
		analyzers.push_back(umts_analysis(config));
		analyzers.push_back(umts_analysis(analyzers[0]));
		analyzers.push_back(umts_analysis(analyzers[0]));
		analyzers.push_back(umts_analysis(analyzers[0]));
		analyzers.push_back(umts_analysis(analyzers[0]));

		std::vector<rf_phreaker::scanner::measurement_info> packets;

		for(size_t i = 0; i < analyzers.size(); ++i) {
			std::ifstream file(base_filename + boost::lexical_cast<std::string>(0) + ".txt");
			if(file) {
				rf_phreaker::scanner::measurement_info p;
				file >> p;
				packets.push_back(p);
			}
		}

		std::vector<std::thread> threads;

		if(packets.size()) {
			auto p_it = packets.begin();
			for(auto &analysis : analyzers) {
				threads.push_back(std::thread([&](umts_analysis &anl, rf_phreaker::scanner::measurement_info &info) {
					for(int i = 0; i < num_iterations; ++i) {
						umts_measurements group;
						int status = anl.cell_search(info, group, /*14952*//*8000*/-25, umts_scan_type::full_scan_type);
						EXPECT_EQ(0, status);
					}
				}, analysis, *p_it++));
			}
			for(auto &thread : threads)
				thread.join();
		}
	}
	catch(const std::exception &err) {
		std::cout << "umts_analysis_gtests exception:  " << err.what() << std::endl;
	}
}