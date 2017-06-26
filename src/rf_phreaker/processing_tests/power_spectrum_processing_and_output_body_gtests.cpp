#include "gtest/gtest.h"
#include <iostream>
#include <algorithm>
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
#include "rf_phreaker/processing/processing_utility.h"
#include "rf_phreaker/processing/power_spectrum_processing_and_output_body.h"

using namespace rf_phreaker;
using namespace rf_phreaker::processing;

TEST(PowerSpectrumProcessingOutputTest, TestMain) {
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
//		"../../../../rf_phreaker/test_files/lte_may_2017/"
		"../../../../rf_phreaker/test_files/sig_gen_1945_-50db/"
		;

	std::string prefix =
		//	"lte_layer_3_1494274488_";
		"power_spectrum_1497993405_";
	std::string suffix = ".bin";


	auto meas_ptr = std::make_shared<scanner::measurement_info>();
	rf_phreaker::scanner::measurement_info &info = *meas_ptr.get();

	data_output_async async;
	async.connect_power_spectrum([&](const power_spectrum_data &d) {
		auto i = std::max_element(std::begin(d.power_), std::end(d.power_));
		std::cout << *i << std::endl;
		//static int i = 0;
		//std::ofstream f("power_spec_output_" + std::to_string(i) + ".txt");
		//if(f) {
		//	header(f, d) << std::endl;
		//	f << d << std::endl;
		//}
		//ipp_32f_array matlab_comp(d.power_.size());
		//int j = 0;
		//for(auto k : d.power_)
		//	matlab_comp[j++] = k;
		//matlab_comp.output_matlab_compatible_array("power_spectrum_sl_" + std::to_string(i) + ".txt");
		//i++;
	});
	power_spectrum_processing_and_output_body body(&async);

	for(int i = 20; i < num_iterations; ++i) {
		std::string full_path_and_filename = folder_path + prefix + boost::lexical_cast<std::string>(i) + suffix;

		std::ifstream file(full_path_and_filename, use_boost_archive ? std::ios_base::binary : std::ios_base::in);

		if(file) {
			if(use_boost_archive) {
				boost::archive::binary_iarchive ia(file);
				ia & info;
			}
			else
				file >> info;
			
			power_spectrum_approximator approx;
			//approx.determine_spectrum_parameters(info.frequency() - info.bandwidth() / 2, info.bandwidth(), khz(2), info.time_ns());
			approx.determine_spectrum_parameters(mhz(1941), mhz(10), khz(1), info.time_ns(), 1);

			power_spectrum_spec spec = std::get<power_spectrum_spec>(approx.power_specs().front());


				
			//power_spectrum_spec spec;
			//spec.dwell_time_ = info.time_ns();
			//spec.sampling_rate_ = info.sampling_rate();
			//spec.span_ = spec.sampling_rate_ / 3;
			////spec.span_ = std::min((frequency_type)info.bandwidth(), spec.sampling_rate_);
			//spec.start_frequency_ = info.frequency() - spec.span_ / 2;
			//spec.end_frequency_ = info.frequency() + spec.span_ / 2;
			//spec.window_length_ = pow(2, 12);
			//spec.bin_size_ = spec.sampling_rate_ / (double)spec.window_length_;
			//spec.step_size_ = spec.bin_size_;
			//spec.num_windows_ = info.get_iq().length() / spec.window_length_;

			power_spectrum_package pak(meas_ptr, spec);

			body.operator()(pak);

			//frequency_type sampling_rate = 4875000;
			//frequency_type window_length = (int)pow(2, 9);
			//ipp_32fc_array signal((int)pow(2, 18));
			//frequency_shifter shifter;
			//shifter.generate_tone(signal, signal.length(), khz(100), sampling_rate);
		}
	}
}
