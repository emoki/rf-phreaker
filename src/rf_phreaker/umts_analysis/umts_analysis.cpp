#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/umts_analysis/umts_analysis_impl.h"

umts_analysis::umts_analysis()
: impl_(new umts_analysis_impl())
{}

umts_analysis::~umts_analysis()
{
	delete impl_;
}

int umts_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, uint32_t num_cpich_chips, umts_scan_type scan_type)
{
	return impl_->cell_search(raw_signal, umts_meas, num_umts_meas, num_cpich_chips, scan_type);
}


int umts_analysis::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas)
{
	return impl_->decode_layer_3(raw_signal, umts_meas);
}

void umts_analysis::set_config(const umts_config &config)
{
	return impl_->set_config(config);
}



