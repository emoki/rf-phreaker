#include "gtest/gtest.h"
#include "rf_phreaker/common/frequency_bin_calculator.h"
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;

TEST(FftHelper, TestMain) {
	frequency_bin_calculator calc;

	frequency_type sampling_rate = 4875000;

	ipp_32fc_array signal((int)pow(2, 18));

	frequency_shifter shifter;

	shifter.generate_tone(signal, signal.length(), khz(100), sampling_rate);

	calc.calculate_power_in_bins(signal, sampling_rate, khz(200));

	calc.get_power_in_bin(khz(100));

	calc.get_bins().output_matlab_compatible_array("test_fft.txt");
}