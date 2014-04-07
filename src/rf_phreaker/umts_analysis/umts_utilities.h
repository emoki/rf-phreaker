#ifndef __UMTS_UTILITIES_H__
#define __UMTS_UTILITIES_H__

#include <cmath>
#include <stdint.h>

namespace rf_phreaker {

class umts_utilities
{
public:
	static double calculate_correlation_ecio_threshold(double margin, double num_slots_coherently_combined, double num_slots_incoherently_combined, double number_chips_in_slot)
	{
		// Margin is usually somewhere between 11 and 12.
		double log_tmp1 = log10((double)num_slots_coherently_combined) / log10(2.0);
		double log_tmp2 = log10((double)num_slots_incoherently_combined) / log10(2.0);
		double threshold = margin - 3 * log_tmp1 - 1.5 * log_tmp2 - 10 * log10(number_chips_in_slot);
		return threshold;
	}

	static double calculate_correlation_ecio_watts_threshold(double margin, double num_slots_coherently_combined, double num_slots_incoherently_combined, double number_chips_in_slot)
	{
		// Margin is usually somewhere between 11 and 12.
		double threshold = calculate_correlation_ecio_threshold(margin, num_slots_coherently_combined, num_slots_incoherently_combined, number_chips_in_slot);

		return std::pow(10.0, threshold/20.0);
	}

	static uint32_t calculate_num_chips_from_ecio_threshold(double ecio)
	{
		double margin = 13;
		double num_slots_coherently_combined = 1;
		double num_slots_incoherently_combined = 1;

		double log_tmp1 = log10((double)num_slots_coherently_combined) / log10(2.0);
		double log_tmp2 = log10((double)num_slots_incoherently_combined) / log10(2.0);

		double num_chips = std::pow(10.0, ((ecio - margin + 3 *log_tmp1 + 1.5 * log_tmp2) / -10));


		return static_cast<uint32_t>(std::floor(num_chips / 256.0)) * 256 + 256;

	}
};

}

#endif