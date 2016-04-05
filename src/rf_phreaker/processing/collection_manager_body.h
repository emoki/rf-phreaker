#pragma once
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/scanner_io.h"
#include "rf_phreaker/processing/collection_scheduler.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include "boost/archive/binary_oarchive.hpp"
#include "tbb/flow_graph.h"
#include <algorithm>
#include <atomic>

namespace rf_phreaker { namespace processing {

class exit_count {
public:
	exit_count(int num_tokens) : count_(num_tokens), is_counting_(false) {}
	exit_count(const exit_count &ex) : count_(ex.count_), is_counting_(ex.is_counting_) {}
	void start_counting() { is_counting_ = true; }
	void update() { if(is_counting_) --count_; }
	bool can_exit() const { return count_ <= 0; }
	int current_count() const { return count_; }
private:
	int count_;
	bool is_counting_;
};

class collection_manager_body
{
public:
	collection_manager_body(const collection_manager_body &a) 
		: scanner_interface_(a.scanner_interface_)
		, graph_(a.graph_)
		, containers_(a.containers_)
		, packet_output_settings_(a.packet_output_settings_)
		, settings_(a.settings_)
		, gsm_sweep_(a.gsm_sweep_)
		, gsm_layer_3_(a.gsm_layer_3_)
		, umts_sweep_(a.umts_sweep_)
		, umts_layer_3_(a.umts_layer_3_)
		, lte_sweep_(a.lte_sweep_)
		, lte_layer_3_(a.lte_layer_3_)
		, timestamp_(a.timestamp_)
		, scheduler_(&containers_, &settings_, a.scheduler_.has_multiple_scans())
		, token_count_(0)
		, exit_count_(a.exit_count_) {}


	collection_manager_body(tbb::flow::graph *graph, rf_phreaker::scanner::scanner_controller_interface *sc, const collection_info_containers &info, 
		const output_settings &p_output, const settings &s_settings, int num_items_in_flight, bool do_multiple_scans = true)
		: scanner_interface_(sc)
		, graph_(graph)
		, containers_(info)
		, packet_output_settings_(p_output)
		, settings_(s_settings)
		, scheduler_(&containers_, &settings_, do_multiple_scans)
		, gsm_sweep_(0)
		, gsm_layer_3_(0)
		, umts_sweep_(0)
		, umts_layer_3_(0)
		, lte_sweep_(0)
		, lte_layer_3_(0)
		, token_count_(0)
		, exit_count_(num_items_in_flight)
	{}

	void operator()(add_remove_collection_info info, collection_manager_node::output_ports_type &out)
	{
		if(!info.add_.empty() || !info.remove_.empty()) {
			for(auto &c : containers_)
				c.adjust(info);
		}

		// The flow graph controls processing by alloting x number of tokens to the system.  If the system is 
		// alloted 8 tokens then 8 tasks can be occurring simultaneously.  For this to work correctly a token 
		// cannot mutliply, meaning 1 token does not become 3 tokens.  This is what happens if we're using 
		// the generic sweep.  One token comes in and it's possible to send three out (gsm, umts, lte).  Therefore 
		// we keep a count of how many tokens we sent out and wait until we have received that number of tokens 
		// before collecting another packet.  Because this is the first node in the system we should be able to stay
		// under the number of tokens alloted.
		if(--token_count_ > 0) {
			return;
		}

		scheduler_.update();

		collection_info ci;
		if(scheduler_.get_next_collection_info(ci)) {
			std::shared_ptr<scanner::measurement_info> meas_ptr;
			if(scheduler_.get_current_container()->is_streaming_)
				meas_ptr = std::make_shared<scanner::measurement_info>(scanner_interface_->stream_rf_data(ci.freq_, ci.time_ns_, ci.overlap_time_ns_, ci.bandwidth_, ci.sampling_rate_).get());
			else
				meas_ptr = std::make_shared<scanner::measurement_info>(scanner_interface_->get_rf_data(ci.freq_, ci.time_ns_, ci.bandwidth_, ci.sampling_rate_).get());

			measurement_package package(meas_ptr, ci.can_remove_);

			auto &meas = package.measurement_info_;

			// Make necessary changes to the packet.
			meas->collection_round(scheduler_.current_container_collection_round());
			meas->set_operating_bands(ci.operating_bands_);
			if(!settings_.use_rf_board_adjustment_)
				meas->rf_board_adjustments(scanner::rf_adjustment{});

			std::string log("Sending to following processors: ");
			if(ci.specs_.has_spec(GSM_SWEEP)) {
				log += "gsm_sweep ";
				send_msg<GSM_SWEEP_PORT>(out, package);
				if(packet_output_settings_.gsm_sweep_) { output(meas.get(), "gsm_sweep_", gsm_sweep_++); }
			}
			if(ci.specs_.has_spec(GSM_LAYER_3_DECODE)) {
				log += "gsm_layer_3 ";
				send_msg<GSM_LAYER3_PORT>(out, package);
				if(packet_output_settings_.gsm_layer_3_) { output(meas.get(), "gsm_layer_3_", gsm_layer_3_++); }
			}
			if(ci.specs_.has_spec(UMTS_SWEEP)) {
				log += "umts_sweep ";
				send_msg<UMTS_SWEEP_PORT>(out, package);
				if(packet_output_settings_.umts_sweep_) { output(meas.get(), "umts_sweep_", umts_sweep_++); }
			}
			if(ci.specs_.has_spec(UMTS_LAYER_3_DECODE)) {
				log += "umts_layer_3" ;
				send_msg<UMTS_LAYER3_PORT>(out, package);
				if(packet_output_settings_.umts_layer_3_) { output(meas.get(), "umts_layer_3_", umts_layer_3_++); }
			}
			if(ci.specs_.has_spec(LTE_SWEEP)) {
				log += "lte_sweep ";
				send_msg<LTE_SWEEP_PORT>(out, package);
				if(packet_output_settings_.lte_sweep_) { output(meas.get(), "lte_sweep_", lte_sweep_++); }
			}
			if(ci.specs_.has_spec(LTE_LAYER_3_DECODE)) {
				log += "lte_layer_3 ";
				send_msg<LTE_LAYER3_PORT>(out, package);
				if(packet_output_settings_.lte_layer_3_) { output(meas.get(), "lte_layer_3_", lte_layer_3_++); }
			}
			LOG(LCOLLECTION) << log;
		}

		if(scheduler_.is_done())
			finished_scanning();
	}

protected:
	template<int Port, typename Msg>
	void send_msg(collection_manager_node::output_ports_type &out, Msg &msg) {
		if(std::get<Port>(out).try_put(msg))
			++token_count_;
	}
	
	void output(scanner::measurement_info *meas, std::string name, int count)
	{
		if(timestamp_.empty())
			timestamp_ = static_timestamp::to_string();
		std::string ext = settings_.output_in_binary_ ? ".bin" : ".txt";
		std::ofstream file(settings_.output_directory_ + "\\" + name + timestamp_ + "_" + std::to_string(count) + ext,
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

	virtual void finished_scanning() { 
		exit_count_.start_counting();
		exit_count_.update();
		if(exit_count_.can_exit()) {
			graph_->root_task()->cancel_group_execution();
			delegate_sink::instance().log_message("Collection finished.", processing_error_type, COLLECTION_FINISHED);
			LOG(LVERBOSE) << "Collection finished.  Stopping root task.";
		}
	}

	rf_phreaker::scanner::scanner_controller_interface *scanner_interface_;

	tbb::flow::graph *graph_;

	collection_info_containers containers_;

	output_settings packet_output_settings_;
	settings settings_;
	int gsm_sweep_;
	int gsm_layer_3_;
	int umts_sweep_;
	int umts_layer_3_;
	int lte_sweep_;
	int lte_layer_3_;

	std::string timestamp_;

	collection_scheduler scheduler_;

	int token_count_;

	exit_count exit_count_;
};

class freq_correction_collection_manager_body : public collection_manager_body
{
public:
	freq_correction_collection_manager_body(tbb::flow::graph *graph, rf_phreaker::scanner::scanner_controller_interface *sc, const collection_info_containers &info, 
		const output_settings &p_output, const settings &s_settings)
	: collection_manager_body(graph, sc, info, p_output, s_settings, false)
	{}

protected:
	void finished_scanning() 
	{
		delegate_sink::instance().log_error("Frequency correction failed.", processing_error_type, FREQUENCY_CORRECTION_FAILED);
		graph_->root_task()->cancel_group_execution();
	}
};


}}
