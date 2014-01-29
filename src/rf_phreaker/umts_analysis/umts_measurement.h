#pragma once

#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include <vector>
#include <stdint.h>

class umts_measurement;
typedef std::vector<umts_measurement> umts_measurements;

class umts_measurement
{
public:
	int32_t cpich_;
	double norm_corr_;
	double rms_signal_;
	double ecio_;
	int32_t sample_num_;
	int64_t time_;
	layer_3_information::umts_bcch_bch_message_aggregate layer_3_;
};
