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
		, graph_(graph)
		, containers_(info)
		, is_simultaneous_collection_(false)
		, do_multiple_scans_(true)
		, packet_output_settings_(p_output)
		, settings_(s_settings)
		, umts_sweep_(0)
		, umts_layer_3_(0)
		, lte_sweep_(0)
		, lte_layer_3_(0)

	{}

	void operator()(add_remove_collection_info info, collection_manager_node::output_ports_type &out)
	{
		auto it = std::find_if(containers_.begin(), containers_.end(), [&](collection_info_container &c) {
			return c.get_technology() == info.tech_; });

		if(it != containers_.end())
			it->adjust(info);

		bool scanning_finished_for_all_containers = true;

		for(auto &c : containers_) {
			if(!c.is_finished()) {
				auto ci = c.try_get_next_info();
				if(c.is_finished()){
					//processing_.store(false);
					//return;
					continue;
				}
				else {
					scanning_finished_for_all_containers = false;

					auto meas = std::make_shared<scanner::measurement_info>(scanner_io_(ci));
					
					// Make necessary changes to the packet.
					meas->collection_round(c.collection_round());
					meas->set_operating_band(ci.operating_band_);
					if(!settings_.use_rf_board_adjustment_)
						meas->rf_board_adjustment(0);

					switch(c.get_technology()) {
					case UMTS_SWEEP:
						if(packet_output_settings_.umts_sweep_) { output(meas.get(), "umts_sweep_", umts_sweep_++); }
						std::get<UMTS_SWEEP_PORT>(out).try_put(meas);
						break;
					case UMTS_LAYER_3_DECODE:
						if(packet_output_settings_.umts_layer_3_) { output(meas.get(), "umts_layer_3_", umts_layer_3_++); }
						std::get<UMTS_LAYER3_PORT>(out).try_put(meas);
						break;
					case LTE_SWEEP:
						if(packet_output_settings_.lte_sweep_) { output(meas.get(), "lte_sweep_", lte_sweep_++); }
						std::get<LTE_SWEEP_PORT>(out).try_put(meas);
						break;
					case LTE_LAYER_3_DECODE:
						if(packet_output_settings_.lte_layer_3_) { output(meas.get(), "lte_layer_3_", lte_layer_3_++); }
						std::get<LTE_LAYER3_PORT>(out).try_put(meas);
						break;
					default:
						throw processing_error("Unknown specifier while trying to put meas in output port."); // Do nothing.
					}
				}
				if(!is_simultaneous_collection_)
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
			timestamp = timestamp_string();

		//std::ofstream file(name + timestamp + "_" + std::to_string(count) + ".bin", std::ios::binary);
		//file << *meas;
		std::ofstream file(name + timestamp + "_" + std::to_string(count) + ".bin", std::ios::binary);
		if(file) {
			boost::archive::binary_oarchive oa(file);
			oa & *static_cast<raw_signal*>(meas);
		}
	}

	virtual void finished_scanning() { throw processing_error("Finished scanning not supported."); }

	scanner_io scanner_io_;

	tbb::flow::graph *graph_;

	collection_info_containers containers_;

	bool is_simultaneous_collection_;

	bool do_multiple_scans_;

	output_settings packet_output_settings_;
	settings settings_;
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
		delegate_sink_async::instance().log_error("Frequency correction failed.", FREQUENCY_CORRECTION_FAILED);
		graph_->root_task()->cancel_group_execution();
	}
};

}}
