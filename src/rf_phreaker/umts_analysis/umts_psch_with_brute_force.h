#pragma once

#include "rf_phreaker/common/cross_correlation_incoherent_and_coherent_addition.h"
#include "rf_phreaker/umts_analysis/spur_nullifier.h"
#include "rf_phreaker/umts_analysis/cpich_table_container.h"
#include "rf_phreaker/umts_analysis/umts_types.h"
#include "rf_phreaker/umts_analysis/umts_measurement_container.h"
#include "rf_phreaker/umts_analysis/umts_config.h"
#include "rf_phreaker/common/benchmark.h"
#include "rf_phreaker/common/ipp_array.h"
#include "stdafx.h"
#include "ipp.h"
#include <vector>
#include <list>
#include <atomic>

namespace rf_phreaker {

class umts_psch_with_brute_force 
{
public:
	umts_psch_with_brute_force(const umts_psch_with_brute_force& a);

	umts_psch_with_brute_force(const umts_config &config, const /*cpich_table_container &*/Ipp32fc* cpich_table, std::atomic_bool *is_cancelled = nullptr);
	
	umts_measurements process(const ipp_32fc_array &signal, const umts_measurements &tracking_measurements, uint32_t num_cpich_chips, umts_scan_type scanning_method = full_scan_type);

	void set_max_num_psch_peaks(size_t num_peaks) { max_num_psch_peaks_ = num_peaks; }

	size_t max_num_psch_peaks() { return max_num_psch_peaks_; }

	void set_max_num_candidates(size_t num_candidates) { max_num_candidates_ = num_candidates; }

	size_t max_num_candidates() { return max_num_candidates_; }

	double average_rms() { return average_rms_; }

	void set_pause(int32_t pause) { pause_ = pause; }

	void set_num_coherent_psch_slots_and_reset_iterations(int coherent_slots) { num_coherent_psch_slots_ = coherent_slots; psch_cross_correlator_.reset_num_iterations(); }

	void set_num_psch_iterations(int num_iterations) { psch_cross_correlator_.set_num_iterations(num_iterations); }

	int num_psch_iterations() const { return psch_cross_correlator_.num_iterations(); }

	int num_coherent_psch_slots() const { return num_coherent_psch_slots_; }

private:

	void set_resampled_cpich_table(const cpich_table_container &cpich_table) { resampled_cpich_table_ = cpich_table.cpich_table_ptr(); }

	void set_config(const umts_config &umts_config);

	void do_cpich_correlation_and_add_candidate(uint32_t cpich, uint32_t timeslot, uint32_t peak_position, umts_measurements &new_meas);

	void determine_cpich_and_timeslot(std::list<std::pair<uint32_t, uint32_t> > &cpich_timeslot_group, uint32_t peak_position, const umts_measurements &tracking_measurements);

	void calculate_peak_adjustment();

	void adjust_clock_error_rate();

	void pause_if_necessary() 
	{ 
		if(pause_ >= 0) 
			Sleep(pause_); 
	}

	cross_correlation_incoherent_and_coherent_addition psch_cross_correlator_;

	cross_correlation_incoherent_and_coherent_addition cpich_cross_correlator_;

	ipp_32fc_array psch_template_;

	ipp_32fc_array cpich_wrap_around_;

	const Ipp32fc* resampled_cpich_table_;

	//spur_nullifier spur_nullifier_;

	size_t max_num_psch_peaks_;

	size_t max_num_candidates_;

	int default_num_cpich_chips_;

	double average_rms_;

	//rf_phreaker::benchmark benchmark_;

	Ipp32f min_cpich_ecio_watts_;

	uint64_t time_of_packet_uframes_;

	int32_t pause_;

	int num_coherent_psch_slots_;

	int total_psch_correlation_length_;

	int psch_peak_adjustment_;

	double actual_num_chips_in_time_slot_;

	double actual_num_chips_in_frame_;

	int length_to_process_;

	std::atomic_bool *is_cancelled_;

	bool do_we_benchmark_;

	double sample_rate_;

	double clock_rate_;

	double over_sampling_rate_;

	double psch_confidence_threshold_;

	double cpich_confidence_threshold_;

	int num_samples_per_cpich_;

	int num_samples_per_time_slot_;

	int max_processing_length_;
};

}