#pragma once
#include "rf_phreaker/common/measurement_io.h"
#include "rf_phreaker/umts_analysis/umts_io.h"
#include "rf_phreaker/lte_analysis/lte_io.h"
#include <vector>
#include <boost/signals2.hpp>

namespace rf_phreaker { namespace processing {


	//boost::signals2::signal<void(gps*)> gps_signal_type;
	//boost::signals2::signal<void(umts_data*, int)> umts_signal_type;
	//boost::signals2::signal<void(lte_data*, int)> lte_signal_type;

class measurement_output
{
public:
	measurement_output()
	{}

	measurement_output(measurement_output &&meas)
	{}

	template<typename Data>
	void output(const std::vector<Data> &data);

	template<typename Data>
	void output(const Data &data);

private:

};

template<typename Data>
inline void measurement_output::output(const std::vector<Data> &data)
{
	for(auto &it : data)
		std::cout << it << "\n";
}

template<typename Data>
inline void measurement_output::output(const Data &data)
{
	std::cout << data << "\n";
}

//void output(const lte_measurements &data);
//void output(const basic_data &data);
//void output(const umts_data &data);
//void output(const lte_data &data);


}}
