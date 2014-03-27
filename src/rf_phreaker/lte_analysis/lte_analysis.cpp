#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/lte_analysis/lte_analysis_impl.h"

lte_analysis::lte_analysis(const lte_config &config)
: impl_(new lte_analysis_impl(config))
{}

lte_analysis::lte_analysis(const lte_analysis &analysis)
: impl_(new lte_analysis_impl(analysis.impl_->get_lte_config()))
{}

lte_analysis::~lte_analysis()
{
	delete impl_;
}

int lte_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames)
{
	return impl_->cell_search(raw_signal, lte_meas, num_half_frames);
}

int lte_analysis::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames)
{
	return impl_->decode_layer_3(raw_signal, lte_meas, num_half_frames);
}
