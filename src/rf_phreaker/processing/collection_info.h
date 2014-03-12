#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/settings.h"
#include <vector>

namespace rf_phreaker { namespace processing {

class collection_info;
class umts_sweep_collection_info;
class umts_layer_collection_info;
class lte_sweep_collection_info;
class lte_layer_3_collection_info;

typedef std::vector<collection_info> collection_info_group_type;

void initialize_collection_info_defaults(const rf_phreaker::settings &config);

class collection_info
{
public:
	collection_info()
		: freq_(0)
		, time_ns_(0)
		, bandwidth_(0)
		, sampling_rate_(0)
	{}

	collection_info(rf_phreaker::frequency_type freq, rf_phreaker::time_type time_ns, rf_phreaker::bandwidth_type bw, rf_phreaker::frequency_type sampling_rate = 0)
		: freq_(freq)
		, time_ns_(time_ns)
		, bandwidth_(bw)
		, sampling_rate_(sampling_rate)
	{}

	bool operator==(const collection_info &a)
	{
		return freq_ == a.freq_ && time_ns_ == a.time_ns_ && bandwidth_ == a.bandwidth_ && sampling_rate_ == a.sampling_rate_;
	}

	rf_phreaker::frequency_type freq_;
	rf_phreaker::time_type time_ns_;
	rf_phreaker::bandwidth_type bandwidth_;
	rf_phreaker::frequency_type sampling_rate_;
};

class umts_sweep_collection_info : public collection_info
{
public:
	umts_sweep_collection_info(rf_phreaker::frequency_type freq) : collection_info(freq, time_ns__, bandwidth__, sampling_rate__) {}
	static rf_phreaker::time_type time_ns__;
	static rf_phreaker::bandwidth_type bandwidth__;
	static rf_phreaker::frequency_type sampling_rate__;
};

class umts_layer_3_collection_info : public collection_info
{
public:
	umts_layer_3_collection_info(rf_phreaker::frequency_type freq) : collection_info(freq, time_ns__, bandwidth__, sampling_rate__) {}
	static rf_phreaker::time_type time_ns__;
	static rf_phreaker::bandwidth_type bandwidth__;
	static rf_phreaker::frequency_type sampling_rate__;
};

class lte_sweep_collection_info : public collection_info
{
public:
	lte_sweep_collection_info(rf_phreaker::frequency_type freq, rf_phreaker::bandwidth_type bw = bandwidth__) : collection_info(freq, time_ns__, bw, sampling_rate__) {}
	static rf_phreaker::time_type time_ns__;
	static rf_phreaker::bandwidth_type bandwidth__;
	static rf_phreaker::frequency_type sampling_rate__;
};

class lte_layer_3_collection_info : public collection_info
{
public:
	lte_layer_3_collection_info(rf_phreaker::frequency_type freq, rf_phreaker::frequency_type sampling_rate = sampling_rate__, rf_phreaker::bandwidth_type bw = bandwidth__) : collection_info(freq, time_ns__, bw, sampling_rate) {}
	static rf_phreaker::time_type time_ns__;
	static rf_phreaker::bandwidth_type bandwidth__;
	static rf_phreaker::frequency_type sampling_rate__;
};



}}