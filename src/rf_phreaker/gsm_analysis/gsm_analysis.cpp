#include "rf_phreaker/gsm_analysis/gsm_analysis.h"
#include "rf_phreaker/gsm_analysis/gsm_analysis_impl.h"

namespace rf_phreaker {

gsm_analysis::gsm_analysis(const gsm_config &config, std::atomic_bool *is_cancelled)
: impl_(new gsm_analysis_impl(config, is_cancelled)) {}

gsm_analysis::~gsm_analysis() {
	delete impl_;
}

int gsm_analysis::cell_search(const rf_phreaker::raw_signal &raw_signal, gsm_measurements &gsm_meas) {
	return impl_->cell_search(raw_signal, gsm_meas);
}

int gsm_analysis::decode_bsic(const rf_phreaker::raw_signal &raw_signal, gsm_measurement &gsm_meas) {
	return impl_->decode_bsic(raw_signal, gsm_meas);
}

int gsm_analysis::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, gsm_measurement &gsm_meas) {
	int status = impl_->decode_bcch_bursts(raw_signal, gsm_meas);
	if(status == 0) {
		if(gsm_meas.bcch_burst_decoded_ || gsm_meas.extended_bcch_burst_decoded_)
			status = impl_->decode_layer_3(gsm_meas);
	}
	return status;
}

}
