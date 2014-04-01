#include "gtest/gtest.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <thread>

TEST(UmtsAnalysisTests, TestGeneral)
{
	try {
		const int num_iterations = 19;
		std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_umts_876.8_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_umts_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/blade_samples_4875_";
		//std::string base_filename = "e:/werk/maharashtra/projects/rf_phreaker/rf_phreaker/test_files/signal_";

		umts_config config;
		//config.sampling_rate(3840000);
		//config.clock_rate(3840000);
		//config.max_signal_length(231424);
		rf_phreaker::scanner::measurement_info info;

		// new hardware - 4875 samplerate
		//config.sampling_rate(4875000);
		//config.clock_rate(4875000);
		//config.max_signal_length(292864);
		//rf_phreaker::scanner::measurement_info info;

		// old hardware
		//config.sampling_rate(4875000);
		//config.clock_rate(9750000);
		//config.max_signal_length(655345);
		//rf_phreaker::raw_signal info;


		for(int i = 0; i < num_iterations; ++i) {
			std::ifstream file(base_filename + boost::lexical_cast<std::string>(i) + ".txt");
			if(file) {
				file >> info;

				config.sampling_rate((int)info.sampling_rate());
				config.clock_rate((int)info.sampling_rate());
				config.max_signal_length(info.get_iq().length());
				umts_analysis analysis(config);

				umts_measurements umts_meas(100);
				int num_meas = umts_meas.size();
				
				int status = analysis.cell_search(info, &umts_meas.at(0), num_meas, /*14952*//*8000*/-25, umts_scan_type::full_scan_type);
				EXPECT_EQ(0, status);


				
				for(int j = 0; j < num_meas; ++j) {
					status = analysis.decode_layer_3(info, umts_meas[j]);
					EXPECT_EQ(0, status);

					std::cout <<
						i << "\t" <<
						info.frequency() / 1e6 << "\t" <<
						umts_meas[j].cpich_ << "\t" <<
						umts_meas[j].ecio_ << "\t" <<
						umts_meas[j].rms_signal_ << "\t" <<
						umts_meas[j].sample_num_ << "\t" <<
						umts_meas[j].layer_3_.mcc_.to_string() << "\t" <<
						umts_meas[j].layer_3_.mnc_.to_string() << "\t" <<
						umts_meas[j].layer_3_.lac_ << "\t" <<
						umts_meas[j].layer_3_.cid_ << "\n";
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

		auto p_it = packets.begin();
		for(auto &analysis : analyzers) {
			threads.push_back(std::thread([&](umts_analysis &anl, rf_phreaker::scanner::measurement_info &info) {
				for(int i = 0; i < num_iterations; ++i) {
					umts_measurements umts_meas(100);
					int num_meas = umts_meas.size();
					int status = anl.cell_search(info, &umts_meas.at(0), num_meas, /*14952*//*8000*/-25, umts_scan_type::full_scan_type);
					EXPECT_EQ(0, status);
				}
			}, analysis, *p_it++));
		}
		for(auto &thread : threads)
			thread.join();
	}
	catch(const std::exception &err) {
		std::cout << "umts_analysis_gtests exception:  " << err.what() << std::endl;
	}
}