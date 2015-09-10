#pragma once
#include "tbb/flow_graph.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/processing/scanner_error_tracker.h"
#include "rf_phreaker/processing/frequency_correction_calculator.h"
#include "rf_phreaker/processing/processing_and_feedback_helper.h"
#include "rf_phreaker/gsm_analysis/gsm_analysis.h"
#include "rf_phreaker/gsm_analysis/gsm_config.h"
#include "rf_phreaker/gsm_analysis/gsm_defs.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/frequency_bin_calculator.h"

namespace rf_phreaker { namespace processing {

class gsm_cell_search_settings
{
public:
	gsm_cell_search_settings(const collection_settings &s, const gsm_general_settings &g, const layer_3_settings &l)
		: general_(g)
		, gsm_config_(g.perform_sync_correlations_, (int)s.sampling_rate_, (int)s.sampling_rate_, 
		rf_phreaker::convert_to_samples_and_mod_1024(s.collection_time_, s.sampling_rate_),
			(int)g.side_power_threshold_, (int)g.band_power_threshold_, (int)s.bandwidth_) 
		, layer_3_(l) {}

	gsm_config gsm_config_;
	gsm_general_settings general_;
	layer_3_settings layer_3_;
};

class gsm_processing_body
{
public:
	gsm_processing_body(const gsm_cell_search_settings &config, std::atomic_bool *is_cancelled = nullptr)
		: analysis_(config.gsm_config_, is_cancelled)
		, tracker_(config.layer_3_.max_update_threshold_, config.layer_3_.minimum_collection_round_, config.layer_3_.minimum_decode_count_)
		, config_(config) {
		if(config.layer_3_.wanted_layer_3_.empty()) {
			LOG(LVERBOSE) << "Defaulting to decoding all GSM SIBs.";
			std::vector<layer_3_information::gsm_bcch_si_type> wanted;
			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_1);
			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_2);
			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_2BIS);
			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_2TER);
			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_2QUATER);
			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_3);
			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_4);
			//wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_7);
			//wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_8);
//			wanted.push_back(layer_3_information::gsm_bcch_si_type::SI_23);
			tracker_.set_wanted_layer_3(wanted);
		}
		else
			tracker_.set_wanted_layer_3((std::vector<layer_3_information::gsm_bcch_si_type>&)config.layer_3_.wanted_layer_3_);
	}

	gsm_processing_body(const gsm_processing_body &body)
		: analysis_(body.config_.gsm_config_)
		, tracker_(body.tracker_.max_update_, body.tracker_.min_collection_round_, body.tracker_.min_decode_count_, body.tracker_.wanted_layer_3())
		, config_(body.config_) {}

	//gsm_processing_body(gsm_processing_body &&body)
	//	: gsm_analysis_(std::move(body.gsm_analysis_))
	//{}

	gsm_info operator()(measurement_package package) {
		auto meas = *package.measurement_info_.get();
		gsm_measurements gsm_group;

		int status = analysis_.cell_search(meas, gsm_group);
		if(status != 0)
			throw gsm_analysis_error("Error performing gsm cell search.");

		//if(config_.gsm_config_.preform_sync_correlations()) {
		//	for(auto &i : gsm_group) {
		//		if(i.norm_sync_corr_ > config_.general_.sync_corr_confidence_threshold_) {
		//			status = analysis_.decode_bsic(meas, i);
		//			if(status != 0)
		//				throw gsm_analysis_error("Error decoding gsm bsic.");
		//		}
		//	}
		//}

		// Remove any measurements that are lower than are confidence threshold.  Note we should always keep measurements
		// that have a BSIC decoded.
		gsm_group.erase(std::remove_if(gsm_group.begin(), gsm_group.end(), [&](const gsm_measurement& m) {
			return m.norm_sync_corr_ < config_.general_.sync_corr_confidence_threshold_ && m.bsic_ == -1;
		}), gsm_group.end());

		auto pow_2_length = 1 << 17;
		for(int i = 0; i < 16; ++i) {
			if(pow_2_length < meas.get_iq().length())
				break;
			pow_2_length = pow_2_length >> 1;
		}
		
		freq_bin_calculator_.calculate_power_in_bins(meas.get_iq(), meas.sampling_rate(), gsm_channel_bandwidth_, pow_2_length);

		auto center_freq = meas.frequency() + GSM_PROCESSING_IF;
		if(center_freq % khz(200) != 0)
			throw processing_error("GSM center freq is incorrectly centered on a GSM channel.");

		power_info_group p_info_group;
		for(frequency_type freq = -GSM_LOW_BANDWIDTH_HZ; freq <= GSM_HIGH_BANDWIDTH_HZ; freq += gsm_channel_bandwidth_) {
			p_info_group.push_back(power_info(center_freq + freq, gsm_channel_bandwidth_, freq_bin_calculator_.get_power_in_bin(freq)));
		}

		LOG_IF(LCOLLECTION, (gsm_group.size() != 0)) << "GSM processing - Found " << gsm_group.size() << " GSM measurements using a center frequency of "
			<< meas.frequency() / 1e6 << "mhz and a bandwidth of " << meas.bandwidth() / 1e6 << "mhz";

		return gsm_info(std::move(package), std::move(gsm_group), std::move(p_info_group));
	}

	gsm_info operator()(gsm_info info) {
		auto meas = *info.measurement_package_.measurement_info_.get();
		// If the collection round is 0 it means we need to start decoding from scratch.
		if(helper_.has_layer_3_restarted(meas)) {
			tracker_.clear();
		}

		for(auto &data : info.processed_data_) {
			if(!tracker_.is_fully_decoded(data.center_frequency_, data) && (data.c_i_ratio_ > config_.layer_3_.decode_threshold_ || tracker_.in_history(data.center_frequency_, data))) {
				if(data.bsic_ == -1) {
					int status = analysis_.decode_bsic(meas, data);
					if(status != 0)
						throw gsm_analysis_error("Error decoding gsm bsic.");
				}
				int status = analysis_.decode_layer_3(meas, data);
				if(status != 0)
					throw gsm_analysis_error("Error decoding gsm layer 3.");
				tracker_.update(data.center_frequency_, data);
			}
		}

		// No minimum decode threshold because each base station is on a different freq.
		auto freq = meas.frequency();
		if(info.measurement_package_.can_remove_) {
			tracker_.update_decodes(freq, !info.processed_data_.empty());
			if(config_.layer_3_.should_prioritize_layer_3_) {
				tracker_.update_freq(freq);
				if(tracker_.has_freq_exceeded_max_updates(freq) || (meas.collection_round() > config_.layer_3_.minimum_collection_round_ && tracker_.is_all_decoded()))
					info.remove_ = true;
			}
			else {
				if(tracker_.has_freq_exceeded_max_no_decodes(freq)) {
					info.remove_ = true;
					tracker_.clear_decodes(freq);
				}
			}
		}
		return info;
	}

private:
	static const int gsm_channel_bandwidth_ = khz(200);
	gsm_analysis analysis_;
	gsm_layer_3_tracker tracker_;
	gsm_cell_search_settings config_;
	processing_and_feedback_helper helper_;
	frequency_bin_calculator freq_bin_calculator_;
};

}}
