#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/umts_analysis/umts_analysis_impl.h"

umts_analysis::umts_analysis()
: impl_(new umts_analysis_impl())
{}

umts_analysis::~umts_analysis()
{
	delete impl_;
}

int umts_analysis::cell_search(rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, uint32_t num_cpich_chips, umts_scan_type scan_type)
{
	return impl_->cell_search(raw_signal, umts_meas, num_umts_meas, num_cpich_chips, scan_type);
}

void umts_analysis::set_config(const umts_config &config)
{
	return impl_->set_config(config);
}



