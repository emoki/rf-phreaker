#pragma once

#pragma warning (disable: 4503) //Included to fix tbb_flow warnings.

#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/processing/collection_manager_body.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/common/settings.h"
#include "tbb/flow_graph.h"
#include <memory>

namespace rf_phreaker { namespace processing {


class frequency_correction_graph
{
public:
	frequency_correction_graph(void);

	~frequency_correction_graph(void);

	void start(rf_phreaker::scanner::scanner_controller_interface *sc, data_output_async *out, const collection_info_containers &collection_info, const settings &config);

	void cancel_and_wait();

private:
	void wait();

	void cancel();

	std::shared_ptr<tbb::flow::graph> graph_;

	std::vector<std::shared_ptr<tbb::flow::graph_node>> nodes_;

	std::shared_ptr<start_node> start_node_;

	std::shared_ptr<collection_manager_node> collection_manager_node_;

	std::unique_ptr<std::thread> thread_;

	std::recursive_mutex mutex_;
};


}}
