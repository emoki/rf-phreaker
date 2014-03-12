#pragma once

//#include "rf_phreaker/common/common_types.h"
//#include "rf_phreaker/processing/node_defs.h"
//#include "tbb/flow_graph.h"
//#include <map>
//#include <algorithm>

//namespace rf_phreaker { namespace processing {
//
//
//typedef std::pair<specifier, start_node::successor_type*> node_tech_type;
//
//class switch_body
//{
//public:
//	switch_body(const std::vector<node_tech_type> &nodes, start_node *start) : nodes_(nodes), start_node_(start) {}
//
//	void operator()(specifier tech)
//	{
//		auto it = std::find_if(nodes_.begin(), nodes_.end(), [&](const node_tech_type &a) {
//			return a.first == tech;
//		});
//	
//		if(it != nodes_.end())
//		{
//			auto next = it;
//			if(++next == nodes_.end())
//				next == nodes_.begin();
//
//			//start_node_->remove_successor(*it->second);
//			//start_node_->register_successor(*next->second);
//		}
//	}
//
//private:
//	std::vector<node_tech_type> nodes_;
//
//	start_node *start_node_;
//};

//}}