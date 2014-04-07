#pragma once

#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/common/common_types.h"
#include <map>
#include <vector>

namespace rf_phreaker {

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

	void update_meas(rf_phreaker::frequency_type freq, const umts_measurements &new_meas)
	{
		auto tracking = meas_map_.find(freq);
		
		if(tracking  == meas_map_.end())
			tracking = meas_map_.insert(std::make_pair(freq, umts_measurements())).first;
		
		// Assumes at most only one entry for a given cpich.
		for(auto &umts : new_meas) {
			auto it = std::find_if(tracking->second.begin(), tracking->second.end(), [&] (const umts_measurement &u) {
				return umts.cpich_ == u.cpich_;
			});
			if(it != tracking->second.end())
				*it = umts;
			else
				tracking->second.push_back(umts);
		}
	}

private:
	measurement_map meas_map_;
};

}