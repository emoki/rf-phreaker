#pragma once

#include <atomic>
#include <mutex>
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/common/frequency_bin_calculator.h"
#include "rf_phreaker/common/filters.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/umts_analysis/umts_config.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/umts_analysis/cpich_table_container.h"
#include "rf_phreaker/umts_analysis/umts_psch_with_brute_force.h"
#include "rf_phreaker/umts_analysis/umts_bch_decoder.h"


namespace rf_phreaker {

class umts_analysis_impl
{
public:
	umts_analysis_impl(const umts_config &config, std::atomic_bool *is_cancelled = nullptr);

	~umts_analysis_impl();

	int cell_search_sweep(const rf_phreaker::raw_signal &raw_signal, umts_measurements &umts_meas, double sensitivity, double error,
		frequency_type low_intermediate_freq, frequency_type high_intermediate_freq, power_info_group *rms_group);

	int cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurements &umts_meas, double sensitivity, umts_scan_type scan_type, double error, double *rms);

	int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas);

	double get_rms_value();

	int set_num_coherent_slots_for_psch(int num_coherent_slots);

	umts_config get_umts_config() { return config_; }

	std::atomic_bool* get_cancellation_bool() { return is_cancelled_; }

private:
	void consolidate_measurements(umts_measurements &group);

	const cpich_table_container* brute_force_cpich_table_ptr();

	const cpich_table_container* bch_decoder_cpich_table_ptr();

	std::unique_ptr<umts_psch_with_brute_force> brute_force_;

	std::unique_ptr<umts_bch_decoder> decoder_;

	umts_config config_;

	umts_measurement_container umts_meas_container_;

	static std::shared_ptr<cpich_table_container> brute_force_cpich_table_;

	static std::shared_ptr<cpich_table_container> bch_decoder_cpich_table_;

	static std::mutex mutex_;

	std::atomic_bool *is_cancelled_;

	frequency_shifter shifter_;

	frequency_bin_calculator freq_bin_calculator_;

	filters filters_;

	ipp_32fc_array resampled_signal_;

	const int umts_cell_search_sampling_rate = 4875000;
};

}