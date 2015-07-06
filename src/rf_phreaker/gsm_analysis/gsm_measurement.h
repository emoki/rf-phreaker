#pragma once

#include <vector>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"

namespace rf_phreaker {

class gsm_measurement;
typedef std::vector<gsm_measurement> gsm_measurements;

class gsm_measurement
{
public:
	static const int bcch_octet_size_ = 23;
	int32_t channel_index_;
	frequency_type intermediate_frequency_;
	frequency_type center_frequency_;
	double channel_power_;
	int32_t fcch_freq_index_;
	int32_t fcch_peak_freq_;
	double fcch_peak_power_;
	double band_power_;
	double side_power_;
	double rms_corr_power_;
	double norm_sync_corr_;
	double c_i_ratio_;
	int32_t sync_sample_num_;
	int32_t bsic_;
	int32_t tdma_frame_number_;
	bool sync_burst_decoded_;
	bool cgi_decoded_;
	bool bcch_burst_decoded_;
	char bcch_octets_[bcch_octet_size_];
	layer_3_information::gsm_layer_3_message_aggregate layer_3_;
};

}