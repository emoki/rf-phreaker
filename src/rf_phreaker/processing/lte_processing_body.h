#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/processing/output_and_feedback_helper.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/log.h"
#include "tbb/flow_graph.h"

namespace rf_phreaker { namespace processing {

/* Allow for greater configuration in LTE.*/
class lte_processing_settings
{
public:
	lte_processing_settings(const collection_settings &s, const layer_3_settings &l, const lte_general_settings &g)
		: layer_3_(l)
		, general_(g)
	{
		lte_config_.sampling_rate((int)s.sampling_rate_);
		lte_config_.clock_rate((int)s.sampling_rate_);
		lte_config_.max_signal_length(rf_phreaker::convert_to_samples(s.collection_time_, s.sampling_rate_));
	}
	lte_general_settings general_;
	lte_config lte_config_;
	layer_3_settings layer_3_;
};

class lte_processing_body
{
public:
	lte_processing_body(const lte_processing_settings &config, std::atomic_bool *is_cancelled = nullptr)
		: config_(config)
		, tracker_(config.layer_3_.max_update_threshold_)
		, analysis_(config.lte_config_, is_cancelled) {
		// If empty, default to decoding all sibs.
		if(config.layer_3_.wanted_layer_3_.empty()) {
			LOG(LVERBOSE) << "Defaulting to decoding all LTE SIBs.";
			std::vector<layer_3_information::lte_sib_type> wanted;
			wanted.push_back(layer_3_information::SIB_1);
			wanted.push_back(layer_3_information::SIB_3);
			wanted.push_back(layer_3_information::SIB_4);
			wanted.push_back(layer_3_information::SIB_5);
			wanted.push_back(layer_3_information::SIB_6);
			wanted.push_back(layer_3_information::SIB_7);
			wanted.push_back(layer_3_information::SIB_8);
			tracker_.set_wanted_layer_3(wanted);
		}
		else
			tracker_.set_wanted_layer_3((std::vector<layer_3_information::lte_sib_type>&)config.layer_3_.wanted_layer_3_);
		
		config_.lte_config_.wanted_si(tracker_.wanted_layer_3());
		analysis_.set_config(config_.lte_config_);
	}

	lte_info operator()(measurement_package package) {
		auto meas = *package.measurement_info_.get();
		lte_measurements group;
		double avg_rms = 0;

		int status = analysis_.cell_search(meas, group, calculate_num_half_frames(meas.time_ns() > milli_to_nano(50) ? milli_to_nano(50) : meas.time_ns()));
		if(status != 0)
			throw lte_analysis_error("Error processing lte.");

		// Remove any measurements that are lower than are confidence threshold.  Note we should always keep measurements
		// that have a PBCH decoded.
		group.erase(std::remove_if(group.begin(), group.end(), [&](const lte_measurement& m) {
			return m.sync_quality < config_.general_.sync_quality_confidence_threshold_ && !this->is_valid_measurement(m);
		}), group.end());

		avg_rms = ipp_helper::calculate_average_rms(meas.get_iq().get(), meas.get_iq().length());

		LOG_IF(LCOLLECTION, (group.size() != 0)) << "LTE processing - Found " << group.size() << " possible LTE measurements.  Frequency: " << meas.frequency() / 1e6
			<< "mhz | Bandwidth: " << meas.bandwidth() / 1e6 << "mhz | Sampling rate: " << meas.sampling_rate() / 1e6 << "mhz.";

		return lte_info(std::move(package), std::move(group), power_info_group{{meas.frequency(), meas.bandwidth(), avg_rms}});
	}

	lte_info operator()(lte_info info)
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		// If the collection round is 0 it means we need to start decoding from scratch.
		if(helper_.has_layer_3_restarted(meas)) {
			tracker_.clear();
			analysis_.clear_all_tracking_si();
		}

		auto freq = meas.frequency();
		if(meas.collection_round() % config_.general_.full_scan_interval_ == 0) {
			analysis_.clear_tracking_si(freq);
		}

		if(info.processed_data_.size()) {
			if(0)
				output(info);

			int data_element = 0;
			for(auto &data : info.processed_data_) {
				if(is_valid_measurement(data)) {
					if((!tracker_.is_fully_decoded(freq, data) && (data.sync_quality > config_.layer_3_.decode_threshold_ || tracker_.in_history(freq, data)))) {
						int status = analysis_.decode_layer_3(meas, info.processed_data_, calculate_num_half_frames(meas.time_ns()), data_element);
						if(status != 0)
							throw lte_analysis_error("Error decoding lte layer 3.");
						tracker_.update(freq, data);
					}
				}
				++data_element;
			}

			// If no measurements were greater than the decode_threshold and we are not tracking any cells on this freq, add the cell with the greatest ecio if
			// it meets the min decode threshold.
			if(!tracker_.is_freq_in_history(freq)) {
				lte_measurement data;
				double tmp_sync_quality = -99;
				for(auto &tmp_data : info.processed_data_) {
					if(tmp_data.sync_quality > tmp_sync_quality)
						data = tmp_data;
				} // Temp checks.
				if(data.sync_quality > config_.layer_3_.decode_minimum_threshold_ && is_valid_measurement(data))
					tracker_.update(freq, data);
			}
		}

		tracker_.update_freq(freq);

		if((tracker_.has_freq_exceeded_max_updates(freq) || tracker_.is_all_decoded_on_freq(freq)) && meas.collection_round() > config_.layer_3_.minimum_collection_round_)
			info.remove_ = true;

		return info;
	}

	int calculate_num_half_frames(time_type nano_secs) const
	{
		return static_cast<int>(nano_secs / 1e6 / 5);
	}

	bool constains_valid_measurement(const lte_measurements &data) const
	{
		bool valid = false;
		for(auto &meas : data) {
			if(is_valid_measurement(meas)) {
				valid = true;
				break;
			}
		}
		return valid;
	}

	bool is_valid_measurement(const lte_measurement &data) const
	{
		return data.Bandwidth != LteBandwidth_Unknown && data.Bandwidth != LteBandwidth_1_4MHZ &&
			data.Bandwidth != LteBandwidth_3MHZ && data.NumAntennaPorts != LteAntPorts_Unknown;
	}

protected:
	void output(const lte_info &info) const
	{
		auto meas = *info.measurement_package_.measurement_info_.get();
		static std::string timestamp;
		if(timestamp.empty())
			timestamp = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

		LteChannelBandwidth bw = LteBandwidth_Unknown;
		for(auto &data : info.processed_data_) {
			if(data.Bandwidth != LteBandwidth_Unknown && data.NumAntennaPorts != LteAntPorts_Unknown) {
				if(data.Bandwidth > bw)
					bw = data.Bandwidth;
			}
		}
		bool use_boost_archive = true;
		if(meas.bandwidth() == mhz(5) || meas.bandwidth() == mhz(10) || meas.bandwidth() == mhz(15) || meas.bandwidth() == mhz(20)) {
			switch(bw) {
			case LteBandwidth_5MHZ:
			{
				static int c_5 = 0;
				std::ofstream file("lte_5mhz_" + timestamp + "_" + std::to_string(c_5++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file); 
					a & meas;
				}
				else
					file << meas;
			}
				break;
			case LteBandwidth_10MHZ:
			{
				static int c_10 = 0;
				std::ofstream file("lte_10mhz_" + timestamp + "_" + std::to_string(c_10++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file);
					a & meas;
				}
				else
					file << meas;
			}
				break;
			case LteBandwidth_15MHZ:
			{
				static int c_15 = 0;
				std::ofstream file("lte_15mhz_" + timestamp + "_" + std::to_string(c_15++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file);
					a & meas;
				}
				else
					file << meas;
			}
				break;
			case LteBandwidth_20MHZ:
			{
				static int c_20 = 0;
				std::ofstream file("lte_20mhz_" + timestamp + "_" + std::to_string(c_20++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file);
					a & meas;
				}
				else
					file << meas;
			}
				break;
			default:
				;
			}
		}
	}
	
	lte_processing_settings config_;
	lte_layer_3_tracker tracker_;
	lte_analysis analysis_;
	output_and_feedback_helper<void> helper_;
};


}}