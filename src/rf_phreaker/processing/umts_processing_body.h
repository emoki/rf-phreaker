#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/processing/scanner_error_tracker.h"
#include "rf_phreaker/processing/frequency_correction_calculator.h"
#include "rf_phreaker/processing/processing_and_feedback_helper.h"
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
		, umts_config_((int)s.sampling_rate_, (int)38400000, 
		rf_phreaker::convert_to_samples_and_mod_1024(s.collection_time_, s.sampling_rate_), g.num_coherent_slots_, max_candidates)
	{}
	
	umts_config umts_config_;
	layer_3_settings layer_3_;
	umts_general_settings umts_general_;
};

class umts_processing_body
{
public:
	umts_processing_body(const umts_cell_search_settings &config, scanner::scanner_controller_interface *sc, std::atomic_bool *is_cancelled = nullptr)
		: analysis_(config.umts_config_, is_cancelled)
		, tracker_(config.layer_3_.max_update_threshold_, config.layer_3_.minimum_collection_round_, config.layer_3_.minimum_decode_count_)
		, config_(config)
		, sc_(sc) {
		if(config.layer_3_.wanted_layer_3_.empty()) {
			LOG(LVERBOSE) << "Defaulting to decoding all UMTS SIBs.";
			std::vector<layer_3_information::umts_sib_type> wanted;
			wanted.push_back(layer_3_information::umts_sib_type::SIB1);
			wanted.push_back(layer_3_information::umts_sib_type::SIB3_SIB4);
			wanted.push_back(layer_3_information::umts_sib_type::SIB11);
			tracker_.set_wanted_layer_3(wanted);
		}
		else
			tracker_.set_wanted_layer_3((std::vector<layer_3_information::umts_sib_type>&)config.layer_3_.wanted_layer_3_);
	}
	
	umts_processing_body(const umts_processing_body &body)
		: analysis_(body.config_.umts_config_)
		, tracker_(body.tracker_.max_update_, body.tracker_.min_collection_round_, body.tracker_.min_decode_count_, body.tracker_.wanted_layer_3())
		, config_(body.config_)
		, sc_(body.sc_) 
	{}

	//umts_processing_body(umts_processing_body &&body)
	//	: umts_analysis_(std::move(body.umts_analysis_))
	//{}

	virtual umts_info operator()(measurement_package package)
	{
		auto meas = *package.measurement_info_.get();
		umts_measurements group;
		double rms = 0;
		
		// Change scan_type to candidate_one_timeslot_scan_type once we have tracking.
		auto scan_type = candidate_all_timeslots_scan_type;
		if(meas.collection_round() % config_.umts_general_.full_scan_interval_ == 0) {
			scan_type = full_scan_type;
		}

		int status = analysis_.cell_search(meas, group, config_.umts_general_.sensitivity_, scan_type,
			g_scanner_error_tracker::instance().current_error(), &rms);
		if(status != 0)
			throw umts_analysis_error("Error processing umts.");

		LOG_IF(LCOLLECTION, (group.size() != 0)) << "UMTS processing - Found " << group.size() << " UMTS measurements.  Frequency: " << meas.frequency() / 1e6
			<< "mhz. | Scan type: " << (scan_type == full_scan_type ? "full scan" : scan_type == candidate_one_timeslot_scan_type 
			? "one timeslot scan" : "all timeslots scan");

		if(group.size() && do_we_need_new_correction()) {
			auto error = g_scanner_error_tracker::instance().current_error();
			freq_correction_param param;
			param.scan_type_ = candidate_all_timeslots_scan_type;
			param.sensitivity_ = -28;
			param.num_coherent_slots_ = 10;
			param.start_freq_ = (int)(-error * meas.frequency() * 1.5);
			param.end_freq_ = (int)(error * meas.frequency() * 1.5);
			param.increment_ = (int)(10 * meas.frequency() / mhz(2600));

			auto correction = calculator_.determine_freq_correction(meas, analysis_, param);
			if(correction.has_insertions()) {
				auto best_shift = correction.find_best_freq_shift();

				if(do_we_need_new_correction())
					update_frequency_correction(calculator_.calculate_error(best_shift, meas.frequency()));
			}
		}
		
		return umts_info(std::move(package), std::move(group), power_info_group{{meas.frequency(), meas.bandwidth(), rms}});
	}

	bool do_we_need_new_correction() {
		return !g_scanner_error_tracker::instance().has_started_1pps_calibration() && g_scanner_error_tracker::instance().do_we_need_new_correction();
	}

	void update_frequency_correction(double error_hz) {
		LOG(LDEBUG) << "Error based on UMTS cells: " << error_hz << " Hz.";
		sc_->calculate_and_update_vctcxo_trim(error_hz);
		g_scanner_error_tracker::instance().new_freq_correction();
	}

	umts_info operator()(umts_info info)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		// If the collection round is 0 it means we need to start decoding from scratch.
		if(helper_.has_layer_3_restarted(meas)) {
			tracker_.clear();
		}

		auto freq = meas.frequency();

		if(!config_.layer_3_.should_prioritize_layer_3_ && meas.collection_round() % config_.layer_3_.complete_decode_interval_ == 0) {
			tracker_.clear_history(freq);
		}

		for(auto &data : info.processed_data_) {
			if(!tracker_.is_fully_decoded(freq, data) && (data.ecio_ > config_.layer_3_.decode_threshold_ || tracker_.in_history(freq, data))) {
				int status = analysis_.decode_layer_3(meas, data);
				if(status != 0)
					throw umts_analysis_error("Error decoding umts layer 3.");
				tracker_.update(freq, data);
			}
		}

		// If no measurements were greater than the decode_threshold and we are not tracking any cells on this freq, add the cell with the greatest ecio if
		// it meets the min decode threshold.
		helper_.update_tracker_if_necessary(tracker_, freq, info.processed_data_, config_.layer_3_.decode_minimum_threshold_);

		tracker_.update_freq(freq);

		// With UMTS processing false detections are removed within the umts processing dll therefore we only want to remove frequencies when we are prioritizing layer 3.
		// When layer 3 is not prioritized we are constantly scanning of all detected freqs.
		if(info.measurement_package_.can_remove_ && config_.layer_3_.should_prioritize_layer_3_) {
			if((tracker_.has_freq_exceeded_max_updates(freq) || tracker_.is_all_decoded_on_freq(freq)) && meas.collection_round() > config_.layer_3_.minimum_collection_round_)
				info.remove_ = true;
		}

		return info;
	}

protected:
	umts_analysis analysis_;
	umts_layer_3_tracker tracker_;
	umts_cell_search_settings config_;
	frequency_correction_calculator calculator_;
	scanner::scanner_controller_interface *sc_;
	processing_and_feedback_helper helper_;
};

class umts_sweep_processing_body : public umts_processing_body {
public:
	umts_sweep_processing_body(const umts_cell_search_settings &config, scanner::scanner_controller_interface *sc, frequency_type low_if, frequency_type high_if, std::atomic_bool *is_cancelled = nullptr)
		: umts_processing_body(config, sc, is_cancelled)
		, low_intermediate_freq_(low_if)
		, high_intermediate_freq_(high_if) {
		if(low_intermediate_freq_ <= -mhz(2) || low_intermediate_freq_ >= mhz(2))
			throw processing_error("UMTS low intermediate frequency (" + std::to_string(low_intermediate_freq_) + ") is out of range.");
		if(high_intermediate_freq_ <= -mhz(2) || high_intermediate_freq_ >= mhz(2))
			throw processing_error("UMTS high intermediate frequency (" + std::to_string(high_intermediate_freq_) + ") is out of range.");
		if(low_intermediate_freq_ > high_intermediate_freq_)
			throw processing_error("UMTS intermediate frequencies are invalid.");
	}
	umts_info operator()(measurement_package package) {
		auto meas = *package.measurement_info_.get();
		umts_measurements group;
		power_info_group rms_group;

		int status = analysis_.cell_search_sweep(meas, group, config_.umts_general_.sensitivity_,
			g_scanner_error_tracker::instance().current_error(), low_intermediate_freq_, high_intermediate_freq_, &rms_group);
		if(status != 0)
			throw umts_analysis_error("Error processing umts.");

		if(group.size()) {
			std::string log("UMTS sweep processing on center freq (");
			log += std::to_string(meas.frequency()/1e6) + "mhz) - Found ";
			log += std::to_string(group.size()) + " UMTS measurements on frequencies: ";
			std::set<frequency_type> freqs;
			for(const auto &i : group)
				freqs.insert(i.intermediate_frequency_ + meas.frequency());
			for(const auto &i : freqs)
				log += std::to_string(i / 1e6) + "mhz ";
			LOG(LCOLLECTION) << log;
		}

		return umts_info(std::move(package), std::move(group), std::move(rms_group));
	}

private:
	frequency_type low_intermediate_freq_;
	frequency_type high_intermediate_freq_;
};

}}
