#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/common/settings.h"
#include "tbb/flow_graph.h"

namespace rf_phreaker { namespace processing {

/* Allow for greater configuration in LTE.*/
class lte_processing_settings
{
public:
	lte_processing_settings(/*const collection_settings &s, */const layer_3_settings &l/*, const umts_general_settings &g*/)
		: layer_3_(l)/*, umts_general_(g)*/
	{
		//lte_config_.sampling_rate((int)s.sampling_rate_);
		//lte_config_.clock_rate((int)s.sampling_rate_);
		//lte_config_.max_signal_length((int)(s.sampling_rate_ * (s.collection_time_ / 1e9) + 1));
	}

	//lte_config lte_config_;
	layer_3_settings layer_3_;
};

class lte_processing_body
{
	lte_processing_body(const lte_processing_settings &config)
		: tracker_(config.layer_3_.max_update_threshold_)
		, config_(config)
	{}

	lte_info operator()(measurement_package info)
	{
		int num_meas = 100;
		lte_measurements meas(num_meas);

		int status = analysis_.cell_search(*info, &meas[0], num_meas, calculate_num_half_frames(info->time_ns()));
		if(status != 0)
			throw lte_analysis_error("Error processing lte.");

		meas.resize(num_meas);

		double avg_rms = ipp_helper::calculate_average_rms(info->get_iq().get(), info->get_iq().length());

		return lte_info(info, std::move(meas), avg_rms);
	
	}

	lte_info operator()(lte_info info)
	{
		// If the collection round is 0 it means we need to start decoding from scratch.
		if(info.meas_->collection_round() == 0) {
			tracker_.clear();
		}

		auto freq = info.meas_->frequency();
		int status = analysis_.decode_layer_3(*info.meas_, &info.processed_data_[0], info.processed_data_.size(), calculate_num_half_frames(info.meas_->time_ns()));
		if(status != 0)
			throw umts_analysis_error("Error decoding umts layer 3.");

		for(auto &data : info.processed_data_) {
			if(!tracker_.is_fully_decoded(freq, data) && (data.sync_quality > config_.layer_3_.decode_threshold_ || tracker_.in_history(freq, data))) {
				tracker_.update(freq, data);
			}
		}

		// If no measurements were greater than the decode_threshold and we are not tracking any cells on this freq, add the cell with the greatest ecio if
		// it meets the min decode threshold.
		if(!tracker_.is_freq_in_history(freq)) {
			lte_measurement meas;
			double tmp_sync_quality = -99;
			for(auto &data : info.processed_data_) {
				if(data.sync_quality > tmp_sync_quality)
					meas = data;
			}
			if(meas.sync_quality > config_.layer_3_.decode_minimum_threshold_)
				tracker_.update(freq, meas);
		}

		if(tracker_.is_all_decoded_on_freq(freq))
			info.remove_ = true;

		return info;
	}

	int calculate_num_half_frames(time_type nano_secs)
	{
		return static_cast<int>(nano_secs / 1e6 / 5);
	}

private:
	lte_analysis analysis_;
	lte_layer_3_tracker tracker_;
	lte_processing_settings config_;
};


}}