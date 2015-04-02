#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include "tbb/flow_graph.h"

namespace rf_phreaker { namespace processing {

class umts_cell_search_settings
{
public:
	umts_cell_search_settings(const collection_settings &s, const layer_3_settings &l, const umts_general_settings &g, int max_candidates)
		: layer_3_(l)
		, umts_general_(g)
		, umts_config_((int)s.sampling_rate_, (int)38400000, rf_phreaker::convert_to_samples(s.collection_time_, s.sampling_rate_), g.num_coherent_slots_, max_candidates)
	{}
	
	umts_config umts_config_;
	layer_3_settings layer_3_;
	umts_general_settings umts_general_;
};

class umts_processing_body
{
public:
	umts_processing_body(const umts_cell_search_settings &config)
		: analysis_(config.umts_config_)
		, tracker_(config.layer_3_.max_update_threshold_)
		, config_(config)
		, current_collection_round_(-1)
	{}
	
	umts_processing_body(const umts_processing_body &body)
		: analysis_(body.config_.umts_config_)
		, tracker_(body.tracker_.max_update_)
		, config_(body.config_)
		, current_collection_round_(body.current_collection_round_)
	{}

	//umts_processing_body(umts_processing_body &&body)
	//	: umts_analysis_(std::move(body.umts_analysis_))
	//{}

	umts_info operator()(measurement_package info)
	{
		int num_meas = 100;
		umts_measurements meas(num_meas);
		double rms = 0;
		
		// Change scan_type to candidate_one_timeslot_scan_type once we have tracking.
		auto scan_type = candidate_all_timeslots_scan_type;
		if(info->collection_round() % config_.umts_general_.full_scan_interval_ == 0) {
			scan_type = full_scan_type;
		}

		int status = analysis_.cell_search(*info, &meas[0], num_meas, config_.umts_general_.sensitivity_, scan_type, &rms);
		if(status != 0)
			throw umts_analysis_error("Error processing umts.");

		meas.resize(num_meas);

		LOG_IF(LCOLLECTION, (meas.size() != 0)) << "UMTS processing - Found " << meas.size() << " UMTS measurements.  Frequency: " << info->frequency() / 1e6 
			<< " mhz. | Scan type: " << (scan_type == full_scan_type ? "full scan" : scan_type == candidate_one_timeslot_scan_type 
			? "one timeslot scan" : "all timeslots scan");
		
		return umts_info(info, std::move(meas), rms);
	}

	umts_info operator()(umts_info info)
	{
		// If the collection round is 0 it means we need to start decoding from scratch.
		if(info.meas_->collection_round() == 0 && current_collection_round_ != 0) {
			tracker_.clear();
		}
		current_collection_round_ = info.meas_->collection_round();

		auto freq = info.meas_->frequency();
		for(auto &data : info.processed_data_) {
			if(!tracker_.is_fully_decoded(freq, data) && (data.ecio_ > config_.layer_3_.decode_threshold_ || tracker_.in_history(freq, data))) {
				int status = analysis_.decode_layer_3(*info.meas_, data);
				if(status != 0)
					throw umts_analysis_error("Error decoding umts layer 3.");
				tracker_.update(freq, data);
			}
		}

		// If no measurements were greater than the decode_threshold and we are not tracking any cells on this freq, add the cell with the greatest ecio if
		// it meets the min decode threshold.
		if(!tracker_.is_freq_in_history(freq)) {
			umts_measurement meas;
			meas.ecio_ = -99;
			for(auto &data : info.processed_data_) {
				if(data.ecio_ > meas.ecio_)
					meas = data;
			}
			if(meas.ecio_ > config_.layer_3_.decode_minimum_threshold_)
				tracker_.update(freq, meas);
		}

		if(tracker_.is_all_decoded_on_freq(freq) && info.meas_->collection_round() > config_.layer_3_.minimum_collection_round_)
			info.remove_ = true;

		return info;
	}

private:
	umts_analysis analysis_;
	umts_layer_3_tracker tracker_;
	umts_cell_search_settings config_;
	int64_t current_collection_round_;
};

}}
