#pragma once
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/scanner_io.h"
#include "rf_phreaker/common/common_types.h"
#include "tbb/flow_graph.h"
#include <algorithm>
#include <atomic>

namespace rf_phreaker { namespace processing {


class collection_manager_body
{
public:
	collection_manager_body(std::atomic<bool> &processing, rf_phreaker::scanner::scanner_controller_interface *sc, const collection_info_containers &info)
		: scanner_io_(sc)
		, containers_(info)
		, simultaneous_collection_(false)
		, processing_(processing)
	{}

	void operator()(add_remove_collection_info info, collection_manager_node::output_ports_type &out)
	{
		auto it = std::find_if(containers_.begin(), containers_.end(), [&](collection_info_container &c) {
			return c.get_technology() == info.tech_; });

		if(it != containers_.end())
			it->adjust(info);

		for(auto &c : containers_) {
			if(!c.is_finished()) {
				auto ci = c.try_get_next_info();
				if(c.is_finished()){
					processing_.store(false);
					return;
				}
				else {
					auto meas = std::make_shared<scanner::measurement_info>(scanner_io_(ci));
					meas->collection_round(c.collection_round());
					switch(c.get_technology()) {
					case umts_sweep:
						std::get<UMTS_SWEEP_PORT>(out).try_put(meas);
						break;
					case umts_layer_3_decode:
						std::get<UMTS_LAYER3_PORT>(out).try_put(meas);
						break;
					case lte_sweep:
						std::get<LTE_SWEEP_PORT>(out).try_put(meas);
						break;
					case lte_layer_3_decode:
						std::get<LTE_LAYER3_PORT>(out).try_put(meas);
						break;
					default:
						throw processing_error("Unknown technology while trying to put meas in output port."); // Do nothing.
					}
				}
				if(!simultaneous_collection_)
					break;
			}
		}
	}

private:
	scanner_io scanner_io_;

	collection_info_containers containers_;

	bool simultaneous_collection_;

	std::atomic<bool> &processing_;
};

	//class collection_manager_body
	//{
	//public:
	//	collection_manager_body(rf_phreaker::scanner::scanner_controller_interface *sc, technology tech, const add_remove_collection_info &info)
	//		: scanner_io_(sc)
	//		, tech_(tech)
	//	{
	//		container_.adjust(info);
	//	}

	//	void operator()(add_remove_collection_info info, collection_manager_node::output_ports_type &out)
	//	{
	//		container_.adjust(info);

	//		if(!container_.finished_) {
	//			auto cp = container_.try_get_next_info();

	//			if(container_.finished_)
	//				std::get<TUPLE_TO_SWITCHER>(out).try_put(tech_);
	//			else {
	//				auto meas = scanner_io_(cp);
	//				meas.collection_round(container_.collection_round());
	//				std::get<TUPLE_TO_PROCESSING>(out).try_put(meas);
	//			}
	//		}
	//	}

	//private:
	//	scanner_io scanner_io_;

	//	technology tech_;

	//	collection_info_container container_;
	//};

}}
