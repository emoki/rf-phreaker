#pragma once

#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/umts_analysis/umts_config.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/umts_analysis/cpich_table_container.h"
#include "rf_phreaker/umts_analysis/umts_psch_with_brute_force.h"
#include "rf_phreaker/umts_analysis/umts_bch_decoder.h"
#include <atomic>
#include <mutex>

namespace rf_phreaker {

class umts_analysis_impl
{
public:
	umts_analysis_impl(const umts_config &config);

	~umts_analysis_impl();

	int cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, double sensitivity, umts_scan_type scan_type, double *rms);

	int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas);

	double get_rms_value();

	int set_num_coherent_slots_for_psch(int num_coherent_slots);

	void cancel_processing();

	umts_config get_umts_config() { return config_; }

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
};

}