#include <stdint.h>
#include <map>
#include <mutex>
#include <atomic>
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/common/frequency_bin_calculator.h"
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/filters.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/lte_analysis/lte_config.h"
#include "rf_phreaker/lte_analysis/lte_si_tracker.h"
#include "rf_phreaker/lte_analysis/lte_correlator.h"

namespace rf_phreaker {

int lte_cell_search(const Ipp32fc* SignalSamples,
					unsigned int NumSamples,
					unsigned int NumHalfFramesToProcess,
					lte_measurements &LteData, int &tmp_num_meas,
					double pbch_decoding_threshold,
					double min_relative_peak);

int lte_decode_data(const Ipp32fc* SignalSamples,
					unsigned int NumSamples,
					unsigned int NumHalfFramesToProcess,
					lte_measurements &LteData,
					int meas_to_process,
					lte_si_info_group *scheduling_info = nullptr,
					std::atomic_bool *is_cancelled = nullptr);

class lte_analysis_impl
{
public:
	lte_analysis_impl(const lte_config &config, std::atomic_bool *is_cancelled = nullptr);

	~lte_analysis_impl();

	int cell_search_sweep(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames,
		frequency_type low_intermediate_freq, frequency_type high_intermediate_freq, frequency_type step_size, power_info_group *rms_group = nullptr);

	int cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, double *avg_rms = nullptr);

	int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, int meas_to_process);

	void clear_tracking_si(frequency_type freq);

	void clear_all_tracking_si();

	void set_config(const lte_config &config);

	lte_config get_lte_config() const { return config_; }

private:
	int decode_layer_3_using_hint(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, int meas_to_process);

	rf_phreaker::frequency_type determine_sampling_rate(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas);

	rf_phreaker::fir_filter& get_filter_and_set_resampled_length(rf_phreaker::frequency_type input_sampling_rate, rf_phreaker::frequency_type output_sampling_rate, int num_samples_to_process);

	int calculate_required_num_samples_for_cell_search(int num_half_frames, frequency_type sampling_rate = cell_search_sampling_rate_);

	void clear_lte_measurements();

	static const int num_measurements = 100;

	lte_measurements lte_measurements_;

	filters filters_;

	ipp_32fc_array resampled_signal_;

	int resampled_length_;

	lte_config config_;

	const static rf_phreaker::frequency_type cell_search_sampling_rate_ = khz(1920);

	// This is necessary until the lte cell search and decode are multithreaded.
	static std::mutex processing_mutex;

	si_tracker si_tracker_;

	std::atomic_bool *is_cancelled_;

	std::vector<layer_3_information::lte_sib_type> wanted_si_;

	frequency_shifter shifter_;

	lte_correlator correlator_;
};

}