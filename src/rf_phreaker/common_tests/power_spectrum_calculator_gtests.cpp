#include "gtest/gtest.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include "rf_phreaker/common/common_serialization.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/power_spectrum_calculator.h"
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/common/benchmark.h"

using namespace rf_phreaker;

TEST(PowerSpectrumMainTest, DISABLED_FileTest) {
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
		"../../../../rf_phreaker/test_files/cobham9/"
		//"../../../../rf_phreaker/test_files/lte_sweep/"
		;

	std::string prefix =
		//"lte_layer_3_1413296677_"
		//"lte_layer_3_1437488969_"
		"lte_layer_3_1438857614_"
		//"lte_sweep_1458187885_"
		//"lte_sweep_1458829888_"
		;

	std::string suffix = ".bin";
	//std::string suffix = ".txt";


	rf_phreaker::scanner::measurement_info info;
	//rf_phreaker::raw_signal info;

	for(int i = 0; i < num_iterations; ++i) {
		std::string full_path_and_filename = folder_path + prefix + boost::lexical_cast<std::string>(i) + suffix;

		std::ifstream file(full_path_and_filename, use_boost_archive ? std::ios_base::binary : std::ios_base::in);

		if(file) {
			if(use_boost_archive) {
				boost::archive::binary_iarchive ia(file);
				ia & info;
			}
			else
				file >> info;

			{
				//std::ofstream t(folder_path + "matlab_format_" + prefix + boost::lexical_cast<std::string>(i)+".txt");
				//t << info;
				//continue;
				//std::ofstream t(folder_path + "matlab_format" + prefix + boost::lexical_cast<std::string>(i)+suffix, std::ios::binary);
				//boost::archive::binary_oarchive oa(t);
				//oa & info;
				//continue;
				//info.get_iq().output_matlab_compatible_array(folder_path + "matlab_format_" + prefix + boost::lexical_cast<std::string>(i) + ".txt");
				//continue;
			}


			frequency_type sampling_rate = info.sampling_rate();
			int window_length = (int)pow(2, 12);
			auto &signal = info.get_iq();
			
			//frequency_type sampling_rate = 4875000;
			//frequency_type window_length = (int)pow(2, 9);
			//ipp_32fc_array signal((int)pow(2, 18));
			//frequency_shifter shifter;
			//shifter.generate_tone(signal, signal.length(), khz(100), sampling_rate);

			//VecDoub vec_doub(signal.length() * 2);
			//for(int i = 0; i < signal.length(); ++i) {
			//	vec_doub[i*2] = signal[i].re;
			//	vec_doub[i*2+1] = signal[i].im;
			//}


			power_spectrum_calculator calc;
			calc.calculate_power_spectrum(signal, window_length);
			//calc.power_spectra().output_matlab_compatible_array("c_code_2" + prefix);


			//Spectolap spec((Int)window_length);
			//spec.addlongdata(vec_doub, bartlett);
			//auto spectrum = spec.spectrum();
			//auto freqs = spec.frequencies();
			//ipp_32f_array spec_output(spectrum.size());
			//for(int i = 0; i < spec_output.length(); ++i) {
			//	spec_output[i] = spectrum[i];
			//}
			//spec_output.output_matlab_compatible_array("recipe_code_" + prefix);

		}
	}
}

TEST(PowerSpectrumMainTest, DISABLED_TestSignal) {
	const int num_iterations = 10000;

	rf_phreaker::scanner::measurement_info info;

	for(int i = 0; i < num_iterations; ++i) {

		frequency_type sampling_rate = 4875000;
		frequency_type window_length = (int)pow(2, 9);
		ipp_32fc_array signal((int)pow(2, 18));
		frequency_shifter shifter;
		shifter.generate_tone(signal, signal.length(), khz(100), sampling_rate);

		//VecDoub vec_doub(signal.length() * 2);
		//for(int i = 0; i < signal.length(); ++i) {
		//	vec_doub[i * 2] = signal[i].re;
		//	vec_doub[i * 2 + 1] = signal[i].im;
		//}


		power_spectrum_calculator calc;
		calc.calculate_power_spectrum(signal, window_length);
		//calc.power_spectra().output_matlab_compatible_array("cxx" + prefix);


		//Spectolap spec((Int)window_length);
		//spec.addlongdata(vec_doub, bartlett);
		//auto spectrum = spec.spectrum();
		//auto freqs = spec.frequencies();
		//ipp_32f_array spec_output(spectrum.size());
		//for(int i = 0; i < spec_output.length(); ++i) {
		//	spec_output[i] = spectrum[i];
		//}
		//spec_output.output_matlab_compatible_array("recipe_code_" + prefix);
	}
}

TEST(PowerSpectrumMainTest, Benchmark) {

	benchmark b("benchmark_power_spectrum.txt", false);
	std::ofstream file("power_spectrum_averages.txt");
	for(int n = 0; n < 5; ++n) {
		for(int k = 9; k < 17; ++k) {
			b.clear();

			int num_iterations = 1000;
			frequency_type bin_size = 500 + 500 * n;
			int window_length = (int)pow(2, k);
			frequency_type sampling_rate = bin_size * window_length;
			int num_windows = 30;

			std::vector<ipp_32fc_array> signals;
			frequency_shifter shifter;
			for(int i = 0; i < 20; ++i) {
				ipp_32fc_array signal(window_length * num_windows);
				shifter.generate_tone(signal, signal.length(), (int)khz(10 + i * 2), sampling_rate);
				signals.emplace_back(std::move(signal));
			}


			power_spectrum_calculator calc;
			std::string params = "bin_size:\t" + std::to_string(bin_size) + "\t fft_order:\t" + std::to_string(k)
				+ "\twindow_length:\t" + std::to_string(window_length) + "\tsampling_rate:\t" + std::to_string(sampling_rate)
				+ "\ttotal_samples:\t" + std::to_string(window_length * num_windows)
				+ "\ttotal_time:\t" + std::to_string((window_length * num_windows) / sampling_rate);
			for(int i = 0; i < num_iterations; ++i) {
				auto &signal = signals[i % 20];
				b.start_timer();
				calc.calculate_power_spectrum(signal, window_length);
				b.stop_timer();
				b.output_time_elapsed("details\t" + params);
			}

			b.output_total_time_elapsed("avg\t" + params);
			if(file)
				file << "avg" << params << "\t" << (b.total_time_elapsed().wall / 1e9) / num_iterations
				<< "\t" << (b.total_time_elapsed().user / 1e9) / num_iterations
				<< "\t" << (b.total_time_elapsed().system / 1e9) / num_iterations
				<< std::endl;
		}
	}
}
