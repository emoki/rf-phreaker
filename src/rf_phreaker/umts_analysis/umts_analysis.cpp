#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/umts_analysis/umts_analysis_impl.h"
#include <mutex>

std::mutex umts_analysis_mutex;

umts_analysis::umts_analysis(const umts_config &config)
//: impl_(new umts_analysis_impl(config))
{
	std::lock_guard<std::mutex> lock(umts_analysis_mutex);
	impl_ = (new umts_analysis_impl(config));

}

umts_analysis::umts_analysis(umts_analysis &analysis)
: impl_(new umts_analysis_impl(analysis.impl_->get_umts_config()))
{
	std::lock_guard<std::mutex> lock(umts_analysis_mutex);
	impl_ = (new umts_analysis_impl(analysis.impl_->get_umts_config()));
}


umts_analysis::~umts_analysis()
{
	delete impl_;
}

int umts_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, double sensitivity, umts_scan_type scan_type, double *rms)
{
	return impl_->cell_search(raw_signal, umts_meas, num_umts_meas, sensitivity, scan_type, rms);
}


int umts_analysis::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas)
{
	return impl_->decode_layer_3(raw_signal, umts_meas);
}

//void umts_analysis::set_config(const umts_config &config)
//{
//	return impl_->set_config(config);
//}

void umts_analysis::cancel_processing()
{
	return impl_->cancel_processing();
}



