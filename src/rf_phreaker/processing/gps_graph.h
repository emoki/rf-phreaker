#pragma once

#include "rf_phreaker/processing/gps_body.h"
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/common/settings.h"
#include <memory>


namespace rf_phreaker { namespace processing {

class gps_graph
{
public:
	gps_graph() {}

	~gps_graph() {}

	void initialize_comm(rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const settings &config)
	{
		auto g = std::make_shared<tbb::flow::graph>();

		graphs_.push_back(g);

		start_node_ = std::make_shared<gps_start_node> (*g, [=](tbb::flow::continue_msg&) { return true; }, false);

		auto gps = std::make_shared<gps_node>(*g, tbb::flow::serial, gps_body(sc, out, config));

		start_node_->register_successor(*gps);

		nodes_.push_back(gps);
	}

	void start()
	{
		start_node_->activate();
	}

	void wait()
	{
		for(auto &g : graphs_)
			g->wait_for_all();
	}

	void cancel()
	{
		for(auto &g : graphs_)
			g->root_task()->cancel_group_execution();

		wait();
	}

private:
	std::vector<std::shared_ptr<tbb::flow::graph>> graphs_;

	std::vector<std::shared_ptr<tbb::flow::graph_node>> nodes_;

	std::shared_ptr<gps_start_node> start_node_;
};


}}
