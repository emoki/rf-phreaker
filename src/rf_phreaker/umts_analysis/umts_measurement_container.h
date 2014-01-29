#pragma once

#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/common/common_types.h"
#include <map>
#include <vector>

typedef std::map<rf_phreaker::frequency_type, umts_measurements> measurement_map;

class umts_measurement_container
{
public:
	umts_measurement_container() {};
	
	~umts_measurement_container() {};

	const umts_measurements& get_meas(rf_phreaker::frequency_type freq)
	{
		auto it = meas_map_.find(freq);
		if(it == meas_map_.end()) {
			auto insertion = meas_map_.insert(std::make_pair(freq, umts_measurements()));
			return insertion.first->second;
		}
		else
			return it->second;
	}

private:
	measurement_map meas_map_;
};