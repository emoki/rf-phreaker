#pragma once

#include <vector>

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/lte_analysis/lte_measurement.h"

namespace rf_phreaker { namespace processing {


class lte_data_container
{
public:
	typedef std::vector<rf_phreaker::lte_data> group_type;

    lte_data_container() {}

    lte_data_container(const lte_data_container &a)
        : group_(a.group_)
    {}

	void add(const lte_measurement &lte, const rf_phreaker::scanner::measurement_info &meas_info)
	{
		rf_phreaker::lte_data data;

		//data.basic_.scanner_id_ = lte.;
		//data.basic_.collection_round_ = lte.;
		//data.basic_.carrier_signal_level_ = lte.;
		data.basic_.carrier_frequency_ = meas_info.frequency();
		data.basic_.carrier_bandwidth_ = lte.Bandwidth;
		//data.basic_.time_ = meas_info.;
		//data.basic_.status_flags_ = meas_info.;
		data.psch_norm_corr_ = lte.PschRecord.NormCorr;
		data.ssch_norm_corr_ = lte.SschRecord.NormCorr;
		data.rs_norm_corr_ = lte.RsRecord.NormCorr;
		data.cyclic_prefix_ = static_cast<int>(lte.CyclicPrefix);
		data.num_antenna_ports_ = lte.NumAntennaPorts;
		data.average_digital_voltage_ = lte.AvgDigitalVoltage;
		data.frame_number = lte.frame_number;
		data.rsrp_ = lte.rsrp;
		data.rssi_ = lte.rssi;
		data.rsrq_ = lte.rsrq;
		//data. cid_ = lte.cid;
		//data.lac_ = lte.lac;
		//memcpy(data.mcc_, lte.mcc, sizeof(data.mcc_));
		//memcpy(data.mnc_, lte.mnc, sizeof(data.mnc_));

		group_.push_back(data);
	}

	void clear() { group_.clear(); }

	group_type::iterator begin() { return group_.begin(); }

	group_type::iterator end() { return group_.end(); }
	
private:
	group_type group_;
};

}}
