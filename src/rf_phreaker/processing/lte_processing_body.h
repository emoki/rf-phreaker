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
	lte_processing_settings(const collection_settings &s, const layer_3_settings &l/*, const umts_general_settings &g*/)
		: layer_3_(l)/*, umts_general_(g)*/
	{
		lte_config_.sampling_rate((int)s.sampling_rate_);
		lte_config_.clock_rate((int)s.sampling_rate_);
		lte_config_.max_signal_length(rf_phreaker::convert_to_samples(s.collection_time_, s.sampling_rate_));
	}

	lte_config lte_config_;
	layer_3_settings layer_3_;
};

int count = 0;
class lte_processing_body
{
public:
	lte_processing_body(const lte_processing_settings &config)
		: config_(config)
		, tracker_(config.layer_3_.max_update_threshold_)
		, analysis_(config.lte_config_)
		, current_collection_round_(-1)
	{}

	lte_info operator()(measurement_package info)
	{
		lte_measurements meas;

		int status = analysis_.cell_search(*info, meas, calculate_num_half_frames(info->time_ns()));
		if(status != 0)
			throw lte_analysis_error("Error processing lte.");

		double avg_rms = ipp_helper::calculate_average_rms(info->get_iq().get(), info->get_iq().length());

		return lte_info(info, std::move(meas), avg_rms);
	
	}

	lte_info operator()(lte_info info)
	{
		// If the collection round is 0 it means we need to start decoding from scratch.
		if(info.meas_->collection_round() == 0 && current_collection_round_ != 0) {
			tracker_.clear();
		}
		current_collection_round_ = info.meas_->collection_round();

		auto freq = info.meas_->frequency();

		if(info.processed_data_.size()) {
			int status = analysis_.decode_layer_3(*info.meas_, info.processed_data_, calculate_num_half_frames(info.meas_->time_ns()));
			if(status != 0)
				throw lte_analysis_error("Error decoding lte layer 3.");


			for(auto &data : info.processed_data_) {
				if(data.Bandwidth == LteBandwidth_5MHZ && data.NumAntennaPorts != LteAntPorts_Unknown && data.rsrp > .001) {
					if((!tracker_.is_fully_decoded(freq, data) && (data.sync_quality > config_.layer_3_.decode_threshold_ || tracker_.in_history(freq, data)))) {
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
			}
		}

		if(tracker_.is_all_decoded_on_freq(freq) && info.meas_->collection_round() > config_.layer_3_.minimum_collection_round_)
			info.remove_ = true;

		return info;
	}

	int calculate_num_half_frames(time_type nano_secs)
	{
		return static_cast<int>(nano_secs / 1e6 / 5);
	}

private:
	lte_processing_settings config_;
	lte_layer_3_tracker tracker_;
	lte_analysis analysis_;
	int64_t current_collection_round_;
};


}}