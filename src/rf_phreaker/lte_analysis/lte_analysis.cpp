#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/lte_analysis/lte_analysis_impl.h"
lte_analysis::lte_analysis()
: impl_(new lte_analysis_impl)
{}

lte_analysis::~lte_analysis()
{
	delete impl_;
}

int lte_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurement *lte_meas, int &num_lte_meas, int num_half_frames)
{
	return impl_->cell_search(raw_signal, lte_meas, num_lte_meas, num_half_frames);
}

int lte_analysis::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurement *lte_meas, int num_lte_meas, int num_half_frames)
{
	return impl_->decode_layer_3(raw_signal, lte_meas, num_lte_meas, num_half_frames);
}
