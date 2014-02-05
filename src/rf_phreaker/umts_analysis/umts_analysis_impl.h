#pragma once

#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/umts_analysis/umts_config.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/umts_analysis/cpich_table_container.h"
#include "rf_phreaker/umts_analysis/umts_psch_with_brute_force.h"
#include "rf_phreaker/umts_analysis/umts_bch_decoder.h"


class umts_analysis_impl
{
public:
	umts_analysis_impl();

	~umts_analysis_impl();

	int cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, uint32_t num_cpich_chips, umts_scan_type scan_type);

	int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas);

	void set_config(const umts_config &config);

	void cancel_processing();

private:
	void consolidate_measurements(umts_measurements &group);

	std::unique_ptr<cpich_table_container> cpich_table_;

	std::unique_ptr<cpich_table_container> tmp_cpich_table_;

	std::unique_ptr<umts_psch_with_brute_force> brute_force_;

	std::unique_ptr<umts_bch_decoder> decoder_;

	umts_config config_;

	umts_measurement_container umts_meas_container_;
};
