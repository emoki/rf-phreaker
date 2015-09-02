#pragma once
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/scanner_io.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include "boost/archive/binary_oarchive.hpp"
#include "tbb/flow_graph.h"
#include <algorithm>
#include <atomic>

namespace rf_phreaker { namespace processing {


class collection_manager_body
{
public:
	collection_manager_body(tbb::flow::graph *graph, rf_phreaker::scanner::scanner_controller_interface *sc, const collection_info_containers &info, 
		const output_settings &p_output, const settings &s_settings)
		: scanner_io_(sc)
		, scanner_interface_(sc)
		, graph_(graph)
		, containers_(info)
		, do_multiple_scans_(true)
		, packet_output_settings_(p_output)
		, settings_(s_settings)
		, gsm_sweep_(0)
		, gsm_layer_3_(0)
		, umts_sweep_(0)
		, umts_layer_3_(0)
		, lte_sweep_(0)
		, lte_layer_3_(0)

	{}

	void operator()(add_remove_collection_info info, collection_manager_node::output_ports_type &out)
	{
		auto it = std::find_if(containers_.begin(), containers_.end(), [&](collection_info_container &c) {
			return c.get_technology() == info.tech_; 
		});

		if(it != containers_.end())
			it->adjust(info);

		bool scanning_finished_for_all_containers = true;

		for(auto &c : containers_) {
			if(!c.is_finished()) {
				//auto ci = c.try_get_next_info();
				
				collection_info ci;
				if(c.get_technology() == GSM_LAYER_3_DECODE) 
					c.current_info_determine_collection_round(ci);
				else
					ci = c.try_get_next_info();

				if(c.is_finished()) {
					//processing_.store(false);
					//return;
					continue;
				}
				else {
					scanning_finished_for_all_containers = false;

					//measurement_package package(std::make_shared<scanner::measurement_info>(
					//	scanner_interface_->get_rf_data(ci.freq_, ci.time_ns_, ci.bandwidth_, ci.sampling_rate_).get()), ci.can_remove_);

					std::shared_ptr<scanner::measurement_info> meas_ptr;
					if(c.get_technology() == GSM_LAYER_3_DECODE) {
						//static std::ofstream f("debug_streaming.txt");
						//static auto start_time = std::chrono::high_resolution_clock::now();
						//f << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count() << std::endl;
						meas_ptr = std::make_shared<scanner::measurement_info>(scanner_interface_->stream_rf_data(ci.freq_, ci.time_ns_, 35000000, ci.bandwidth_, ci.sampling_rate_).get());
					}
					else
						meas_ptr = std::make_shared<scanner::measurement_info>(scanner_interface_->get_rf_data(ci.freq_, ci.time_ns_, ci.bandwidth_, ci.sampling_rate_).get());

					measurement_package package(meas_ptr, ci.can_remove_);

					auto &meas = package.measurement_info_;

					// Make necessary changes to the packet.
					meas->collection_round(c.collection_round());
					meas->set_operating_band(ci.operating_band_);
					if(!settings_.use_rf_board_adjustment_)
						meas->rf_board_adjustments(scanner::rf_adjustment{});

					switch(c.get_technology()) {
					case GSM_SWEEP:
						if(packet_output_settings_.gsm_sweep_) { output(meas.get(), "gsm_sweep_", gsm_sweep_++); }
						std::get<GSM_SWEEP_PORT>(out).try_put(package);
						break;
					case GSM_LAYER_3_DECODE:
						if(packet_output_settings_.gsm_layer_3_) { output(meas.get(), "gsm_layer_3_", gsm_layer_3_++); }
						std::get<GSM_LAYER3_PORT>(out).try_put(package);
						break;
					case UMTS_SWEEP:
						if(packet_output_settings_.umts_sweep_) { output(meas.get(), "umts_sweep_", umts_sweep_++); }
						std::get<UMTS_SWEEP_PORT>(out).try_put(package);
						break;
					case UMTS_LAYER_3_DECODE:
						if(packet_output_settings_.umts_layer_3_) { output(meas.get(), "umts_layer_3_", umts_layer_3_++); }
						std::get<UMTS_LAYER3_PORT>(out).try_put(package);
						break;
					case LTE_SWEEP:
						if(packet_output_settings_.lte_sweep_) { output(meas.get(), "lte_sweep_", lte_sweep_++); }
						std::get<LTE_SWEEP_PORT>(out).try_put(package);
						break;
					case LTE_LAYER_3_DECODE:
						if(packet_output_settings_.lte_layer_3_) { output(meas.get(), "lte_layer_3_", lte_layer_3_++); }
						std::get<LTE_LAYER3_PORT>(out).try_put(package);
						break;
					default:
						throw processing_error("Unknown specifier while trying to put meas in output port."); // Do nothing.
					}
				}
				if(!settings_.simultaneous_collection_)
					break;
			}
		}

		if(scanning_finished_for_all_containers) {
			if(do_multiple_scans_) {
				for(auto &c : containers_)
					c.reset();
			}
			else
				finished_scanning();

			// If scanning has finished for all containers then we will not process any packets this time thru which 
			// means we need to send a continue msg to the limiter node directly.
			std::get<LIMITER_PORT>(out).try_put(tbb::flow::continue_msg());
		}
	}

protected:
	void output(scanner::measurement_info *meas, std::string name, int count)
	{
		if(timestamp.empty())
			timestamp = static_timestamp::to_string();
		std::string ext = settings_.output_in_binary_ ? ".bin" : ".txt";
		std::ofstream file(settings_.output_directory_ + "\\" + name + timestamp + "_" + std::to_string(count) + ext,
			settings_.output_in_binary_ ? std::ios::binary : std::ios::app);
		if(file) {
			if(settings_.output_in_binary_) {
				boost::archive::binary_oarchive oa(file);
				//oa & *static_cast<raw_signal*>(meas);
				oa & *meas;
			}
			else {
				file << *meas;
			}
		}
	}

	virtual void finished_scanning() { throw processing_error("Finished scanning not supported."); }

	scanner_io scanner_io_;
	
	rf_phreaker::scanner::scanner_controller_interface *scanner_interface_;

	tbb::flow::graph *graph_;

	collection_info_containers containers_;

	bool do_multiple_scans_;

	output_settings packet_output_settings_;
	settings settings_;
	int gsm_sweep_;
	int gsm_layer_3_;
	int umts_sweep_;
	int umts_layer_3_;
	int lte_sweep_;
	int lte_layer_3_;

	std::string timestamp;
};

class freq_correction_collection_manager_body : public collection_manager_body
{
public:
	freq_correction_collection_manager_body(tbb::flow::graph *graph, rf_phreaker::scanner::scanner_controller_interface *sc, const collection_info_containers &info, 
		const output_settings &p_output, const settings &s_settings)
	: collection_manager_body(graph, sc, info, p_output, s_settings)
	{
		do_multiple_scans_ = false;
	}

protected:
	void finished_scanning() 
	{
		delegate_sink::instance().log_error("Frequency correction failed.", processing_error_type, FREQUENCY_CORRECTION_FAILED);
		graph_->root_task()->cancel_group_execution();
	}
};

}}
