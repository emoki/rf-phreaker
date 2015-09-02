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
	gsm_measurement() 
		: channel_index_(-1)
		, intermediate_frequency_(-LLONG_MAX)
		, center_frequency_(-1)
		, channel_power_(-DBL_MAX)
		, fcch_freq_index_(-1)
		, fcch_peak_freq_(-1)
		, fcch_peak_power_(-DBL_MAX)
		, band_power_(-DBL_MAX)
		, side_power_(-DBL_MAX)
		, rms_corr_power_(-DBL_MAX)
		, norm_sync_corr_(-DBL_MAX)
		, c_i_ratio_(-DBL_MAX)
		, sync_sample_num_(-1)
		, bsic_(-1)
		, tdma_frame_number_(-1)
		, sync_burst_decoded_(false)
		, cgi_decoded_(false)
		, bcch_burst_decoded_(false) 
		, extended_bcch_burst_decoded_(false) {
		memset(bcch_octets_, 0, sizeof(bcch_octets_[0]) * bcch_octet_size_);
		memset(extended_bcch_octets_, 0, sizeof(extended_bcch_octets_[0]) * bcch_octet_size_);
	}

	gsm_measurement(const gsm_measurement &meas) 
		: channel_index_(meas.channel_index_)
		, intermediate_frequency_(meas.intermediate_frequency_)
		, center_frequency_(meas.center_frequency_)
		, channel_power_(meas.channel_power_)
		, fcch_freq_index_(meas.fcch_freq_index_)
		, fcch_peak_freq_(meas.fcch_peak_freq_)
		, fcch_peak_power_(meas.fcch_peak_power_)
		, band_power_(meas.band_power_)
		, side_power_(meas.side_power_)
		, rms_corr_power_(meas.rms_corr_power_)
		, norm_sync_corr_(meas.norm_sync_corr_)
		, c_i_ratio_(meas.c_i_ratio_)
		, sync_sample_num_(meas.sync_sample_num_)
		, bsic_(meas.bsic_)
		, tdma_frame_number_(meas.tdma_frame_number_)
		, sync_burst_decoded_(meas.sync_burst_decoded_)
		, cgi_decoded_(meas.cgi_decoded_)
		, bcch_burst_decoded_(meas.bcch_burst_decoded_)
		, extended_bcch_burst_decoded_(meas.extended_bcch_burst_decoded_)
		, layer_3_(meas.layer_3_) {
		memcpy(bcch_octets_, meas.bcch_octets_, sizeof(bcch_octets_[0]) * bcch_octet_size_);
		memcpy(extended_bcch_octets_, meas.extended_bcch_octets_, sizeof(extended_bcch_octets_[0]) * bcch_octet_size_);	
	}

	gsm_measurement(gsm_measurement &&meas) {
		swap(meas);
	}

	gsm_measurement& operator=(gsm_measurement meas) {
		meas.swap(*this);
		return *this;
	}

	void swap(gsm_measurement &meas) {
		std::swap(channel_index_, meas.channel_index_);
		std::swap(intermediate_frequency_, meas.intermediate_frequency_);
		std::swap(center_frequency_, meas.center_frequency_);
		std::swap(channel_power_, meas.channel_power_);
		std::swap(fcch_freq_index_, meas.fcch_freq_index_);
		std::swap(fcch_peak_freq_, meas.fcch_peak_freq_);
		std::swap(fcch_peak_power_, meas.fcch_peak_power_);
		std::swap(band_power_, meas.band_power_);
		std::swap(side_power_, meas.side_power_);
		std::swap(rms_corr_power_, meas.rms_corr_power_);
		std::swap(norm_sync_corr_, meas.norm_sync_corr_);
		std::swap(c_i_ratio_, meas.c_i_ratio_);
		std::swap(sync_sample_num_, meas.sync_sample_num_);
		std::swap(bsic_, meas.bsic_);
		std::swap(tdma_frame_number_, meas.tdma_frame_number_);
		std::swap(sync_burst_decoded_, meas.sync_burst_decoded_);
		std::swap(cgi_decoded_, meas.cgi_decoded_);
		std::swap(bcch_burst_decoded_, meas.bcch_burst_decoded_);
		std::swap(bcch_octets_, meas.bcch_octets_);
		std::swap(extended_bcch_burst_decoded_, meas.extended_bcch_burst_decoded_);
		std::swap(extended_bcch_octets_, meas.extended_bcch_octets_);
		layer_3_.swap(meas.layer_3_);
	}
	
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
	bool extended_bcch_burst_decoded_;
	unsigned char bcch_octets_[bcch_octet_size_];
	unsigned char extended_bcch_octets_[bcch_octet_size_];
	layer_3_information::gsm_layer_3_message_aggregate layer_3_;
};

}