#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/umts_analysis/umts_analysis_impl.h"
#include <mutex>

namespace rf_phreaker {

std::mutex umts_analysis_mutex;

umts_analysis::umts_analysis(const umts_config &config, std::atomic_bool *is_cancelled)
	//: impl_(new umts_analysis_impl(config))
{
	std::lock_guard<std::mutex> lock(umts_analysis_mutex);
	impl_ = (new umts_analysis_impl(config, is_cancelled));

}

umts_analysis::umts_analysis(const umts_analysis &analysis)
	//: impl_(new umts_analysis_impl(analysis.impl_->get_umts_config()))
{
	std::lock_guard<std::mutex> lock(umts_analysis_mutex);
	impl_ = (new umts_analysis_impl(analysis.impl_->get_umts_config(), analysis.impl_->get_cancellation_bool()));
}


umts_analysis::~umts_analysis() {
	delete impl_;
}

int umts_analysis::cell_search_sweep(const rf_phreaker::raw_signal &raw_signal, umts_measurements &umts_meas, double sensitivity, double error,
	frequency_type low_intermediate_freq, frequency_type high_intermediate_freq, power_info_group *rms_group) {
	return impl_->cell_search_sweep(raw_signal, umts_meas, sensitivity, error, low_intermediate_freq, high_intermediate_freq, rms_group);
}


int umts_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurements &umts_meas, double sensitivity, umts_scan_type scan_type,
	double error, double *rms) {
	return impl_->cell_search(raw_signal, umts_meas, sensitivity, scan_type, error, rms);
}


int umts_analysis::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas) {
	return impl_->decode_layer_3(raw_signal, umts_meas);
}

int umts_analysis::set_num_coherent_slots_for_psch(int num_coherent_slots) {
	return impl_->set_num_coherent_slots_for_psch(num_coherent_slots);
}

//void umts_analysis::set_config(const umts_config &config)
//{
//	return impl_->set_config(config);
//}

const umts_measurements& umts_analysis::get_tracked_measurements(frequency_type freq) {
	return impl_->get_tracked_measurements(freq);
}

void umts_analysis::update_tracked_measurements(frequency_type freq, const umts_measurements &meas) {
	return impl_->update_tracked_measurements(freq, meas);
}

}