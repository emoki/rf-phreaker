#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/common/settings.h"
#include "tbb/flow_graph.h"

namespace rf_phreaker { namespace processing {

class umts_cell_search_settings
{
public:
	umts_config umts_config_;
	layer_3_settings layer_3_;
	umts_general_settings umts_general_;
};

class umts_cell_search_body
{
public:
	umts_cell_search_body(const umts_cell_search_settings &config)
		: analysis_(config.umts_config_)
		, tracker_(config.layer_3_.max_update_threshold_)
		, config_(config)
		, counter_(0)
	{}
	
	umts_cell_search_body(const umts_cell_search_body &body)
		: analysis_(body.config_.umts_config_)
		, tracker_(body.tracker_.max_update_)
		, config_(body.config_)
		, counter_(0)
	{}

	//umts_cell_search_body(umts_cell_search_body &&body)
	//	: umts_analysis_(std::move(body.umts_analysis_))
	//{}

	umts_info operator()(measurement_package info)
	{
		int num_meas = 50;
		umts_measurements meas(num_meas);
		double rms = 0;
		
		// Change scan_type to candidate_one_timeslot_scan_type once we have tracking.
		auto scan_type = candidate_all_timeslots_scan_type;
		if(++counter_ > config_.umts_general_.full_scan_interval_) {
			scan_type = full_scan_type;
			counter_ = 0;
		}

		int status = analysis_.cell_search(*info, &meas[0], num_meas, config_.umts_general_.sensitivity_, scan_type, &rms);
		if(status != 0)
			throw umts_analysis_error("Error processing umts.");

		meas.resize(num_meas);
		
		return umts_info(info, std::move(meas), rms);
	}

	umts_info operator()(umts_info info)
	{
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

		if(tracker_.is_all_decoded_on_freq(freq))
			info.remove_ = true;

		return info;
	}

private:
	umts_analysis analysis_;
	umts_layer_3_tracker tracker_;
	umts_cell_search_settings config_;
	int counter_;
};

}}
