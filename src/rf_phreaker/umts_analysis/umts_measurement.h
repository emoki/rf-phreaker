#pragma once

#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include <vector>
#include <stdint.h>

namespace rf_phreaker {

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

	umts_measurement() 
		: cpich_(-1)
		, norm_corr_(-DBL_MAX)
		, rms_signal_(-DBL_MAX)
		, ecio_(-DBL_MAX)
		, sample_num_(-1)
		, time_(-1) {}

	umts_measurement(umts_measurement&& meas)
		//: umts_measurement()
	{
		this->swap(meas);
	}

	umts_measurement& operator=(umts_measurement meas)
	{
		meas.swap(*this);
		return *this;
	}

	void swap(umts_measurement &meas)
	{
		std::swap(meas.cpich_, cpich_);
		std::swap(meas.norm_corr_, norm_corr_);
		std::swap(meas.rms_signal_, rms_signal_);
		std::swap(meas.ecio_, ecio_);
		std::swap(meas.sample_num_, sample_num_);
		std::swap(meas.time_, time_);
		meas.layer_3_.swap(layer_3_);
	}
};

}