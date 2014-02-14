#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "tbb/flow_graph.h"

namespace rf_phreaker { namespace processing {

class umts_cell_search_body
{
public:
	umts_cell_search_body(const umts_config &config)
		: analysis_(config)
		, tracker_(100)
		, config_(config)
	{}
	umts_cell_search_body(const umts_cell_search_body &body)
		: analysis_(body.config_)
		, tracker_(body.tracker_.max_update_)
		, config_(body.config_)
	{}

	//umts_cell_search_body(umts_cell_search_body &&body)
	//	: umts_analysis_(std::move(body.umts_analysis_))
	//{}

	umts_info operator()(measurement_package info)
	{
		int num_meas = 50;
		umts_measurements meas(num_meas);
		double rms = 0;
		
		int status = analysis_.cell_search(*info, &meas[0], num_meas, 2560, full_scan_type, &rms);
		if(status != 0)
			throw umts_analysis_error("Error processing umts.");

		meas.resize(num_meas);
		
		return umts_info(info, std::move(meas), rms);
	}

	umts_info operator()(umts_info info)
	{
		auto freq = info.meas_->frequency();
		for(auto &data : info.processed_data_) {
			if(!tracker_.is_fully_decoded(freq, data) && (data.ecio_ > -15 || tracker_.in_history(freq, data))) {
				int status = analysis_.decode_layer_3(*info.meas_, data);
				if(status != 0)
					throw umts_analysis_error("Error decoding umts layer 3.");
				tracker_.update(freq, data);
			}
		}

		if(tracker_.is_all_decoded_on_freq(freq))
			info.remove_ = true;

		return info;
	}

private:
	umts_analysis analysis_;
	umts_layer_3_tracker tracker_;
	umts_config config_;
};

}}
