#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/lte_analysis/lte_analysis_impl.h"

namespace rf_phreaker {

lte_analysis::lte_analysis(const lte_config &config, std::atomic_bool *is_cancelled)
	: impl_(new lte_analysis_impl(config, is_cancelled)) {}

lte_analysis::lte_analysis(const lte_analysis &analysis)
	: impl_(new lte_analysis_impl(analysis.impl_->get_lte_config())) {}

lte_analysis::~lte_analysis() {
	delete impl_;
}

int lte_analysis::cell_search_sweep(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames,
	frequency_type low_intermediate_freq, frequency_type high_intermediate_freq, frequency_type step_size, power_info_group *rms_group) {
	return impl_->cell_search_sweep(raw_signal, lte_meas, num_half_frames, low_intermediate_freq, high_intermediate_freq, step_size, rms_group);
}


int lte_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, double *avg_rms) {
	return impl_->cell_search(raw_signal, lte_meas, num_half_frames, avg_rms);
}

int lte_analysis::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, int meas_to_process) {
	return impl_->decode_layer_3(raw_signal, lte_meas, num_half_frames, meas_to_process);
}

void lte_analysis::clear_tracking_si(frequency_type freq) {
	impl_->clear_tracking_si(freq);
}

void lte_analysis::clear_all_tracking_si() {
	impl_->clear_all_tracking_si();
}

void lte_analysis::set_config(const lte_config &config) {
	impl_->set_config(config);
}


}