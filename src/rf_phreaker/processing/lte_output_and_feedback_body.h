#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/measurement_conversion.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/lte_analysis/lte_types.h"
#include "tbb/flow_graph.h"
#include <tuple>

namespace rf_phreaker { namespace processing {

inline frequency_type determine_sampling_rate(LteChannelBandwidth bw)
{
	switch(bw) {
	case LteBandwidth_5MHZ:
		return lte_bandwidth_5_mhz_sampling_rate;
	case LteBandwidth_10MHZ:
		return lte_bandwidth_10_mhz_sampling_rate;
	case LteBandwidth_15MHZ:
		return lte_bandwidth_15_mhz_sampling_rate;
	case LteBandwidth_20MHZ:
		return lte_bandwidth_20_mhz_sampling_rate;
	case LteBandwidth_3MHZ:
		return lte_bandwidth_3_mhz_sampling_rate;
	case LteBandwidth_1_4MHZ:
	default:
		return lte_bandwidth_1_4_mhz_sampling_rate;
	}
}

inline bandwidth_type determine_bandwidth(LteChannelBandwidth bw)
{
	// These should be valid bandwidths for bladeRF.  Alternatively we could ignore bandwidth when comparing collection_info for removal.
	switch(bw) {
	case LteBandwidth_5MHZ:
		return mhz(5);
	case LteBandwidth_10MHZ:
		return mhz(10);
	case LteBandwidth_15MHZ:
		return mhz(20);
	case LteBandwidth_20MHZ:
		return mhz(20);
	case LteBandwidth_3MHZ:
		return mhz(3);
	case LteBandwidth_1_4MHZ:
	default:
		return khz(1500);
	}
}

LteChannelBandwidth look_for_valid_bandwidth(const lte_measurements &measurements)
{
	auto bw = LteBandwidth_Unknown;
	for(auto &lte : measurements) {
		// Currently multiple bandwidths can be erroneously decoded for the same channel.  For now we take the largest bandwidth?
		// Fix LTE decoding!
		if(lte.Bandwidth != LteBandwidth_Unknown && lte.Bandwidth > bw) {
			bw = lte.Bandwidth;
			break;
		}
	}
	return bw;
}

class lte_sweep_output_and_feedback_body
{
public:
	lte_sweep_output_and_feedback_body(data_output_async *io)
		: io_(io)
	{}

	void operator()(lte_info info, lte_output_and_feedback_node::output_ports_type &out)
	{
		// Output basic tech.
		io_->output_lte_sweep(convert_to_basic_data(*info.meas_, info.avg_rms_))/*.get()*/;

		bool valid_lte = false;
		for(auto &lte : info.processed_data_) {
			if(/*lte.Bandwidth != LteBandwidth_Unknown ||*/ lte.sync_quality > -13) {
			//if((lte.NumAntennaPorts != LteAntPorts_Unknown
			//	&& lte.rsrp > .001 && (lte.rsrp <= DBL_MAX && lte.rsrp >= -DBL_MAX)
			//	&& (lte.rsrq <= DBL_MAX && lte.rsrq >= -DBL_MAX)
			//	&& lte.rssi > .001 && (lte.rssi <= DBL_MAX && lte.rssi >= -DBL_MAX)) || lte.sync_quality > -10) {
				valid_lte = true;
				break;
			}
		}
		if(valid_lte) {
			auto bw = look_for_valid_bandwidth(info.processed_data_);

			// Add the freq to the layer_3_decoder.
			std::get<0>(out).try_put(add_collection_info(lte_layer_3_collection_info(info.meas_->frequency(), determine_sampling_rate(bw), determine_bandwidth(bw), info.meas_->get_operating_band()), LTE_LAYER_3_DECODE));
		}

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	data_output_async *io_;
};

class lte_layer_3_output_and_feedback_body
{
public:
	lte_layer_3_output_and_feedback_body(data_output_async *io, int minimum_collection_round)
		: io_(io)
		, minimum_collection_round_(minimum_collection_round)
	{}

	void operator()(lte_info info, lte_output_and_feedback_node::output_ports_type &out)
	{

		// Remove freq if indicated.
		if(do_we_remove_collection_info(info)) {
			std::get<0>(out).try_put(remove_collection_info(lte_layer_3_collection_info(info.meas_->frequency(), info.meas_->sampling_rate(),
				info.meas_->bandwidth(), info.meas_->get_operating_band()), LTE_LAYER_3_DECODE));
		}
		
		if(!info.processed_data_.empty()) {
			////
			static std::ofstream file("debug_lte_layer_3.txt");
			static bool write_header = true;
			if(write_header) {
				write_header = false;
				file << "freq" << "\t";
				output_lte_meas_debug_header(file);
			}
			for(auto &lte : info.processed_data_) 
				file << info.meas_->frequency() << "\t" << lte << std::endl;
			////

			std::vector<lte_data> lte;

			// Until we get the LTE dll sorted out only output measurements with known bandwidths.
			for(auto &data : info.processed_data_) {
				if(data.NumAntennaPorts != LteAntPorts_Unknown  
					&& data.rsrp > .001 && (data.rsrp <= DBL_MAX && data.rsrp >= -DBL_MAX)
					&& (data.rsrq <= DBL_MAX && data.rsrq >= -DBL_MAX)
					&& data.rssi > .001 && (data.rssi <= DBL_MAX && data.rssi >= -DBL_MAX)) {
					
					auto tmp = convert_to_lte_data(*info.meas_, data, info.avg_rms_);
					auto is_valid = (tmp.rsrp_ <= DBL_MAX && tmp.rsrp_ >= -DBL_MAX)
						&& (tmp.rsrq_ <= DBL_MAX && tmp.rsrq_ >= -DBL_MAX)
						&& (tmp.rssi_ <= DBL_MAX && tmp.rssi_ >= -DBL_MAX);

					if(is_valid)
						lte.push_back(std::move(tmp));
				}
			}
			if(lte.size()) {
				update_measurement_watch(info.processed_data_, info.meas_->frequency());
			
				io_->output(lte)/*.get()*/;

				// Check to see if the sampling_rate is correct for the bandwidth.  If not, remove old collection_info and add new one with correct bandwidth and sampling_rate.
				auto bw = look_for_valid_bandwidth(info.processed_data_);

				if(bw != LteBandwidth_Unknown) {
					auto sampling_rate = determine_sampling_rate(bw);
					// LTE bandwidth can be erroneously decoded.  For now we want to keep the largest bandwidth decoded...
					if(sampling_rate /*!=*/> info.meas_->sampling_rate()) {
						add_remove_collection_info params;
						params.tech_ = LTE_LAYER_3_DECODE;

						params.remove_.push_back(lte_layer_3_collection_info(info.meas_->frequency(), info.meas_->sampling_rate(),
							info.meas_->bandwidth(), info.meas_->get_operating_band()));

						params.add_.push_back(lte_layer_3_collection_info(info.meas_->frequency(), sampling_rate, bw,
							info.meas_->get_operating_band()));

						std::get<0>(out).try_put(params);
					}
				}
			}
		}

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	bool do_we_remove_collection_info(lte_info info)
	{
		bool do_we_remove = false;
		if(info.remove_)
			do_we_remove = true;
		else if(info.meas_->collection_round() > minimum_collection_round_) {
			auto it = strongest_measurements_.find(info.meas_->frequency());
			if(it == strongest_measurements_.end())
				do_we_remove = true;
			else {
				for(auto &watch : strongest_measurements_) {
					if(it->first != watch.first) {
						if(it->second.sync_quality_ < watch.second.sync_quality_ && abs(it->first - watch.first) < watch.second.bw_ / 2)
							return true;
					}
				}
			}
		}
		return do_we_remove;
	}

	void update_measurement_watch(const lte_measurements &lte_group, frequency_type freq)
	{
		if(lte_group.size()) {
			auto bw = look_for_valid_bandwidth(lte_group);
			auto sync_quality = get_strongest_sync(lte_group);
			auto it = strongest_measurements_.find(freq);
			

			if(it == strongest_measurements_.end()) {
				it = strongest_measurements_.insert(std::make_pair(freq, lte_watch(bw, sync_quality))).first;
			}

			if(sync_quality > it->second.sync_quality_)
				it->second.sync_quality_ = sync_quality;
		}
	}

	double get_strongest_sync(const lte_measurements &lte_group)
	{
		double best_sync = -9999;
		for(auto &lte : lte_group) {
			if(best_sync < lte.sync_quality)
				best_sync = lte.sync_quality;
		}
		return best_sync;
	}

	bool has_decoded_layer_3(const lte_measurements &lte_group)
	{
		for(auto &lte : lte_group) {
			if(lte.layer_3_.sib1_.decoded_ || lte.layer_3_.sib4_.decoded_ || lte.layer_3_.sib5_.decoded_ || lte.layer_3_.sib6_.decoded_ 
				|| lte.layer_3_.sib7_.decoded_ || lte.layer_3_.sib8_.decoded_)
			return true;
		}
		return false;
	}

	data_output_async *io_;
	int minimum_collection_round_;

	struct lte_watch {
		lte_watch(frequency_type bw, double sync_quality)
			: bw_(bw)
			, sync_quality_(sync_quality)
		{}
		frequency_type bw_;
		double sync_quality_;
	};
	std::map<frequency_type, lte_watch> strongest_measurements_;
};

}}
