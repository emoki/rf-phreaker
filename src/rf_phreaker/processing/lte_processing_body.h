#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/log.h"
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

		int status = analysis_.cell_search(*info, meas, calculate_num_half_frames(info->time_ns() > milli_to_nano(50) ? milli_to_nano(50) : info->time_ns()));
		if(status != 0)
			throw lte_analysis_error("Error processing lte.");

		double avg_rms = ipp_helper::calculate_average_rms(info->get_iq().get(), info->get_iq().length());

		LOG_IF(LCOLLECTION, (meas.size() != 0)) << "LTE processing - Found " << meas.size() << " possible LTE measurements.  Frequency: " << info->frequency() / 1e6
				<< "mhz | Bandwidth: " << info->bandwidth() / 1e6 << "mhz | Sampling rate: " << info->sampling_rate() / 1e6 << "mhz.";

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
			//output(info);
			
			//// Reduce the time (num half frames) that we process if we are less than the minimum collection round.  This will
			//// help speed up the process of removing the false detections.
			//auto time_ns = info.meas_->time_ns();
			//if(info.meas_->collection_round() < config_.layer_3_.minimum_collection_round_ && info.meas_->time_ns() > milli_to_nano(20))
			//	time_ns =  milli_to_nano(20);

			int status = analysis_.decode_layer_3(*info.meas_, info.processed_data_, calculate_num_half_frames(info.meas_->time_ns()));
			if(status != 0)
				throw lte_analysis_error("Error decoding lte layer 3.");

			for(auto &data : info.processed_data_) {
				if(is_valid_measurement(data) || tracker_.in_history(freq, data)) {
					if((!tracker_.is_fully_decoded(freq, data) && (data.sync_quality > config_.layer_3_.decode_threshold_ || tracker_.in_history(freq, data)))) {
						tracker_.update(freq, data);
					}
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
				} // Temp checks.
				if(meas.sync_quality > config_.layer_3_.decode_minimum_threshold_ && is_valid_measurement(meas))
					tracker_.update(freq, meas);
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

	bool constains_valid_measurement(lte_measurements &data)
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

	bool is_valid_measurement(lte_measurement &meas)
	{
		return meas.Bandwidth != LteBandwidth_Unknown && meas.Bandwidth != LteBandwidth_1_4MHZ && 
			meas.Bandwidth != LteBandwidth_3MHZ && meas.NumAntennaPorts != LteAntPorts_Unknown;
	}

private:
	void output(const lte_info &info)
	{
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
		if(info.meas_->bandwidth() == mhz(5) || info.meas_->bandwidth() == mhz(10) || info.meas_->bandwidth() == mhz(15) || info.meas_->bandwidth() == mhz(20)) {
			switch(bw) {
			case LteBandwidth_5MHZ:
			{
				static int c_5 = 0;
				std::ofstream file("lte_5mhz_" + timestamp + "_" + std::to_string(c_5++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file); 
					a & *info.meas_;
				}
				else
					file << *info.meas_;
			}
				break;
			case LteBandwidth_10MHZ:
			{
				static int c_10 = 0;
				std::ofstream file("lte_10mhz_" + timestamp + "_" + std::to_string(c_10++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file);
					a & *info.meas_;
				}
				else
					file << *info.meas_;
			}
				break;
			case LteBandwidth_15MHZ:
			{
				static int c_15 = 0;
				std::ofstream file("lte_15mhz_" + timestamp + "_" + std::to_string(c_15++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file);
					a & *info.meas_;
				}
				else
					file << *info.meas_;
			}
				break;
			case LteBandwidth_20MHZ:
			{
				static int c_20 = 0;
				std::ofstream file("lte_20mhz_" + timestamp + "_" + std::to_string(c_20++) + ".bin", use_boost_archive ? std::ios::binary : std::ios::out);
				if(use_boost_archive) {
					boost::archive::binary_oarchive a(file);
					a & *info.meas_;
				}
				else
					file << *info.meas_;
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
	int64_t current_collection_round_;
};


}}