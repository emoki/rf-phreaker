#include "rf_phreaker/gsm_analysis/gsm_analysis.h"
#include "rf_phreaker/gsm_analysis/gsm_analysis_impl.h"

namespace rf_phreaker {

gsm_analysis::gsm_analysis(const gsm_config &config, std::atomic_bool *is_cancelled)
: impl_(new gsm_analysis_impl(config, is_cancelled)) {}

gsm_analysis::~gsm_analysis() {
	delete impl_;
}

int gsm_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, gsm_measurements &gsm_meas, bool do_octet_decoding) {
	return impl_->cell_search(raw_signal, gsm_meas, do_octet_decoding);
}

}
