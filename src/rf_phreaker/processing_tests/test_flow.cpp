//#include "gtest/gtest.h"
//
//
// #pragma warning (disable: 4503)
//
//#include "ttb/flow_graph.h"
//
//#include <map>
//#include <vector>
//#include <ostream>
//#include <Windows.h>
//#include <algorithm>
//#include <boost/timer/timer.hpp>
//
//#include "scanner_api_types.h"
//#include "concurrent.h"
//#include "scanner_controller.h"
//#include "collection_manager_lte.h"
//
//concurrent<std::ostream&> async_cout(std::cout);
//
//struct collection_parameters_tmp
//{
//	rf_phreaker::frequency_type freq_;
//	int num_samples_;
//	rf_phreaker::bandwidth_type bandwidth_;
//	rf_phreaker::frequency_type sampling_rate_;
//};
//
//typedef std::tuple<std::map<rf_phreaker::frequency_type, collection_parameters_tmp>, std::map<rf_phreaker::frequency_type, collection_parameters_tmp>> add_remove_parameters_tmp;
//
//struct collection_parameter_manager_tmp
//{
//	collection_parameter_manager_tmp(tbb::flow::graph &g) : g_(g) {}
//
//	collection_parameters_tmp operator()(add_remove_parameters_tmp param)
//	{		
//		manager_.erase(std::remove_if(std::begin(manager_), std::end(manager_), [&](const collection_parameters_tmp &p) { 
//			return std::get<1>(param).find(p.freq_) != std::get<1>(param).end(); 
//		}), std::end(manager_));
//
//		std::for_each(std::begin(std::get<0>(param)), std::end(std::get<0>(param)), [&](const std::pair<rf_phreaker::frequency_type, collection_parameters_tmp> &p) {
//			manager_.push_back(p.second);
//		});
//
//		std::sort(std::begin(manager_), std::end(manager_), [=](const collection_parameters_tmp &a, const collection_parameters_tmp &b) {
//			return a.freq_ < b.freq_;
//		});
//
//		auto it = std::find_if(std::begin(manager_), std::end(manager_), [&](const collection_parameters_tmp &a) {
//			return current_parameters_.freq_ == a.freq_;
//		});
//		
//		if(manager_.empty())
//			g_.root_task()->cancel_group_execution();
//
//		else if(it == manager_.end())
//			current_parameters_ = *manager_.begin();
//		else
//			current_parameters_ = *it;
//	
//		return current_parameters_;
//	}
//
//	typedef std::vector<collection_parameters_tmp> internal_manager;
//	internal_manager manager_;
//	collection_parameters_tmp current_parameters_;
//
//	tbb::flow::graph &g_;
//
//};
//

//TEST(FlowTest, experiment)
//{
//		try
//		{
//	
//	tbb::flow::graph g;
//		
//	scanner_controller controller;
//
//			auto scanner_list = controller.list_available_scanners().get();
//
//			if(scanner_list.size())
//			{
//				auto scanner_id = (*scanner_list.begin())->id();
//
//				controller.open_scanner(scanner_id);
//
//				controller.do_initial_scanner_config();
//
//
//
//
//	tbb::flow::function_node<add_remove_parameters_tmp, collection_parameters_tmp> collection_parameter_manager_node(g,1, collection_parameter_manager_tmp(g));
//
//	tbb::flow::function_node<collection_parameters_tmp, collection_parameters_tmp> output_node(g, 1, [&](collection_parameters_tmp p) {
//		//async_cout([=](std::ostream &cout){
//		//	cout << p.freq_ << "\t" << p.num_samples_ << std::endl;
//		//});
//			std::cout << p.freq_ << "\t" << p.num_samples_ << std::endl;
//			boost::timer::auto_cpu_timer t;
//			auto snapshot = controller.get_rf_data(p.freq_, 50, p.bandwidth_, 0).get();
//
//			if(snapshot.get_iq().length())
//				std::cout << "SUCCESS!!" << std::endl;
//
//
//		return p;
//	});
//
//	tbb::flow::function_node<collection_parameters_tmp, add_remove_parameters_tmp> remove_node(g, 1, [](collection_parameters_tmp p) { 
//		std::map<rf_phreaker::frequency_type, collection_parameters_tmp> add;
//		std::map<rf_phreaker::frequency_type, collection_parameters_tmp> remove;
//		remove.insert(std::make_pair(p.freq_, p));
//		return std::make_tuple(add, remove); 
//	});
//
//
//	tbb::flow::make_edge(collection_parameter_manager_node, output_node);
//	tbb::flow::make_edge(output_node, remove_node);
//	tbb::flow::make_edge(remove_node, collection_parameter_manager_node);
//
//	collection_parameters_tmp p;
//	p.freq_ = mhz(1850);
//	p.num_samples_ = 1;
//	p.sampling_rate_ = mhz(30);
//	p.bandwidth_ = mhz(10);
//
//	std::map<rf_phreaker::frequency_type, collection_parameters_tmp> add;
//	for(int i = 1; i < 10; i++)
//	{
//		add.insert(std::make_pair(p.freq_, p));
//		p.freq_ += mhz(1);
//	}
//
//	std::map<rf_phreaker::frequency_type, collection_parameters_tmp> remove;
//
//	auto tup = std::make_tuple(add, remove);
//	collection_parameter_manager_node.try_put(tup);
//
//
//	//Sleep(10000);
//
//	//g.root_task()->cancel_group_execution();
//	g.wait_for_all();
//
//			}
//		}
//		catch(std::exception &err)
//		{
//			std::cerr << err.what() << std::endl;
//		}
//
//}