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
		, is_simultaneous_collection_(false)
		, do_multiple_scans_(true)
		, processing_(processing)
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
					meas->collection_round(c.collection_round());
					meas->set_operating_band(ci.operating_band_);
					switch(c.get_technology()) {
					case UMTS_SWEEP:
						std::get<UMTS_SWEEP_PORT>(out).try_put(meas);
						break;
					case UMTS_LAYER_3_DECODE:
						std::get<UMTS_LAYER3_PORT>(out).try_put(meas);
						break;
					case LTE_SWEEP:
						std::get<LTE_SWEEP_PORT>(out).try_put(meas);
						break;
					case LTE_LAYER_3_DECODE:
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

		if(scanning_finished_for_all_containers && do_multiple_scans_) {
			for(auto &c : containers_)
				c.reset();
		}
	}

private:
	scanner_io scanner_io_;

	collection_info_containers containers_;

	bool is_simultaneous_collection_;

	bool do_multiple_scans_;

	std::atomic<bool> &processing_;
};


}}
