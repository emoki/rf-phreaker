#pragma once

#pragma warning (disable: 4503) //Included to fix tbb_flow warnings.

#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/processing/collection_manager_body.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/graph_observer.h"
#include "rf_phreaker/common/settings.h"
#include "tbb/flow_graph.h"
#include <memory>
#include <atomic>

namespace rf_phreaker { namespace processing {


class processing_graph
{
public:
	processing_graph(void);

	~processing_graph(void);

	void start(rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const collection_info_containers &collection_info, const settings &config);

	void cancel_and_wait();

private:
	void wait();

	void cancel();

	void add_lte_sweep();

	void add_gsm_sweep();

	std::shared_ptr<tbb::flow::graph> graph_;

	std::vector<std::shared_ptr<tbb::flow::graph_node>> nodes_;

	std::shared_ptr<start_node> start_node_;

	std::shared_ptr<collection_manager_node> collection_manager_node_;

	std::unique_ptr<std::thread> thread_;

	std::mutex mutex_;
};


}}
