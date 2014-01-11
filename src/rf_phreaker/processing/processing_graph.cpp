#include "stdafx.h"
#include "processing_graph.h"
#include "processing_lte.h"
//#include "processing_das.h"
#include "collection_manager.h"
#include "scanner_io.h"
#include <iostream>


using namespace rf_phreaker::scanner;
using namespace rf_phreaker::processing;

processing_graph::processing_graph(void)
{
}


processing_graph::~processing_graph(void)
{
}

void processing_graph::initialize(scanner_controller &sc)
{
	auto g = std::shared_ptr<tbb::flow::graph>(new tbb::flow::graph);

	graphs_.push_back(g);

	collection_node_lte_.reset(new tbb::flow::function_node<add_remove_parameters_, collection_parameters>(*g, 1, collection_parameter_manager(*g)));
	//collection_node_lte_.reset(new tbb::flow::function_node<add_remove_parameters, collection_parameters>(*g, 1, collection_parameter_manager(*g)));
	
	auto scanner_io_node = std::make_shared<tbb::flow::function_node<collection_parameters, measurement_info>>(*g, 1, scanner_io(sc));

	auto basic_processing_lte_node = std::make_shared<tbb::flow::function_node<measurement_info, lte_package>>(*g, 1, basic_processing_lte());
	//auto basic_processing_lte_node = std::make_shared<tbb::flow::function_node<measurement_info, das_package>>(*g, 1, basic_processing_das());

	//auto tmp_output = std::make_shared<tbb::flow::function_node<das_package, add_remove_parameters>>(*g, 1, [](das_package lte){
	//						std::cout << 
	//							"freq: " << std::get<0>(lte).frequency() << " hz\t" << 
	//							" orig_bandwidth: " << std::get<0>(lte).bandwidth() << " hz \t" << 
	//							"time: " << std::get<0>(lte).time_ms() << " ms\t" << 
	//							"orig_sample_rate: " << std::get<0>(lte).sampling_rate() << " hz\t" << 
	//							"num_samples: " << std::get<0>(lte).get_iq().length() << "\t" << 
	//							std::endl;

	//						for(const /*das::*/das1 &data : std::get<1>(lte))
	//							std::cout << 
	//								"freq: " << data.carrier_frequency_ << "\t" << 
	//								"avg_sig " << data.carrier_signal_level_ << "\t" << 
	//								"group_code: " << data.group_code_ << "\t" <<
	//								"ecio: " << data.ecio_ << "\t" << 
	//								"norm: " << data.norm_corr_ << "\t" << 
	//								"rms_corr: " << data.rms_corr_ << "\t" << 
	//								"rms_signal: " << data.rms_signal_ << "\t" << 
	//								std::endl;
	//			
	//						return add_remove_parameters();
	//					});

	auto tmp_output = std::make_shared<tbb::flow::function_node<lte_package, add_remove_parameters_>>(*g, 1, [](lte_package lte){
						std::cout << 
							"freq: " << std::get<0>(lte).frequency() << " hz\t" << 
							"bandwidth: " << std::get<0>(lte).bandwidth() << " hz \t" << 
							"time: " << std::get<0>(lte).time_ms() << " ms\t" << 
							"sample_rate: " << std::get<0>(lte).sampling_rate() << " hz\t" << 
							"num_samples: " << std::get<0>(lte).get_iq().length() << "\t" << 
							std::endl;

						for(const rf_phreaker::lte_data &data : std::get<1>(lte))
							std::cout << 
								"freq: " << data.basic_.carrier_frequency_ << "\t" << 
								"avg digital v: " << data.average_digital_voltage_ << "\t" << 
								"rssi: " << data.rssi_ << "\t" << 
								"rsrp: " << data.rsrp_ << "\t" << 
								"rsrq: " << data.rsrq_ << "\t" << 
								"frame number: " << data.frame_number << "\t" <<
								"mcc: " << data.mcc_ << "\t" << 
								"mnc: " << data.mnc_ << "\t" << 
								"lac: " << data.lac_ << "\t" << 
								"cid: " << data.cid_ << "\t" << 
								std::endl;
				
						return add_remove_parameters_();
					});

	nodes_.push_back(collection_node_lte_);
	
	nodes_.push_back(scanner_io_node);

	nodes_.push_back(basic_processing_lte_node);

	nodes_.push_back(tmp_output);


	tbb::flow::make_edge(*collection_node_lte_, *scanner_io_node);

	tbb::flow::make_edge(*scanner_io_node, *basic_processing_lte_node);

	tbb::flow::make_edge(*basic_processing_lte_node, *tmp_output);

	tbb::flow::make_edge(*tmp_output, *collection_node_lte_);


}

void processing_graph::start(const collection_parameters &cp)
{
	std::map<rf_phreaker::frequency_type, collection_parameters> add;
	add.insert(std::make_pair(cp.freq_, cp)); 
				
	std::map<rf_phreaker::frequency_type, collection_parameters> remove;

	auto t = std::make_tuple(add, remove);

	//collection_node_lte_->try_put(t);
}

void processing_graph::wait()
{
	for(auto &g : graphs_)
		g->wait_for_all();
}

void processing_graph::cancel()
{
	for(auto &g : graphs_)
		g->root_task()->cancel_group_execution();

	for(auto &g : graphs_)
		g->wait_for_all();
}
