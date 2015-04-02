#ifndef __UMTS_UTILITIES_H__
#define __UMTS_UTILITIES_H__

#include <cmath>
#include <stdint.h>

namespace rf_phreaker {

class umts_utilities
{
public:
	static double calculate_correlation_ecio_threshold(double margin, double num_slots_coherently_combined, double num_slots_incoherently_combined, double number_chips_in_slot) {
		// Margin is usually somewhere between 11 and 12.
		double log_tmp1 = log10((double)num_slots_coherently_combined) / log10(2.0);
		double log_tmp2 = log10((double)num_slots_incoherently_combined) / log10(2.0);
		double threshold = margin - 3 * log_tmp1 - 1.5 * log_tmp2 - 10 * log10(number_chips_in_slot);
		return threshold;
	}

	static double calculate_correlation_ecio_watts_threshold(double margin, double num_slots_coherently_combined, double num_slots_incoherently_combined, double number_chips_in_slot) {
		// Margin is usually somewhere between 11 and 12.
		double threshold = calculate_correlation_ecio_threshold(margin, num_slots_coherently_combined, num_slots_incoherently_combined, number_chips_in_slot);

		return std::pow(10.0, threshold / 20.0);
	}

	static int32_t calculate_num_chips_from_ecio_threshold(double ecio) {
		double margin = 13;
		double num_slots_coherently_combined = 1;
		double num_slots_incoherently_combined = 1;

		double log_tmp1 = log10((double)num_slots_coherently_combined) / log10(2.0);
		double log_tmp2 = log10((double)num_slots_incoherently_combined) / log10(2.0);

		double num_chips = std::pow(10.0, ((ecio - margin + 3 * log_tmp1 + 1.5 * log_tmp2) / -10));


		return static_cast<int32_t>(std::floor(num_chips / 256.0)) * 256 + 256;

	}

	static double calculate_max_cpich_correlation_size(frequency_type freq, double error) {
		double chips_per_second = (38400.0 * 100);
		return calculate_max_coherent_correlation_seconds(freq, error) * chips_per_second; // num chips in 1 second
	}

	static double calculate_max_psch_coherent_slots(frequency_type freq, double error) {
		double slots_per_second = 100.0 * 15;
		return calculate_max_coherent_correlation_seconds(freq, error) * slots_per_second + 1;
	}

	static double calculate_max_psch_incoherent_iterations(double error, int coherent_slots) {
		double slots_per_second = 100.0 * 15;
		return .75 / (error * UMTS_CHIP_RATE_HZ) * slots_per_second; // .75 corresponds to how much of a chip off do we allow
	}

	static double calculate_max_coherent_correlation_seconds(frequency_type freq, double error) {
		return 1.0 / calculate_error_hz(freq, error) / 4; // 4 means at most we allow 90 degrees of phase shift
	}
	
	static double calculate_error_hz(frequency_type freq, double error) {
		return freq * error;
	}
};

}

#endif