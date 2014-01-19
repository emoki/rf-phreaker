#pragma once

#pragma warning (disable: 4503) //Included to fix tbb_flow warnings.

#include <memory>
#include "tbb/flow_graph.h"

#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/processing/collection_manager.h"

namespace rf_phreaker { namespace processing {

class processing_graph
{
public:
	processing_graph(void);

	~processing_graph(void);

    void initialize(rf_phreaker::scanner::scanner_controller_interface *sc);

	void start(const collection_parameters &cp);

	void wait();

	void cancel();

private:

	void add_lte_sweep();

	void add_gsm_sweep();

	std::vector<std::shared_ptr<tbb::flow::graph>> graphs_;

	std::shared_ptr<tbb::flow::function_node<add_remove_parameters_, collection_parameters>> collection_node_lte_;
	//std::shared_ptr<tbb::flow::function_node<add_remove_parameters, collection_parameters>> collection_node_lte_;

	std::vector<std::shared_ptr<tbb::flow::graph_node>> nodes_;
};

}}
