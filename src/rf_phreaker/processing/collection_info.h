#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/settings.h"
#include <vector>

namespace rf_phreaker { namespace processing {

class collection_info;
class gsm_sweep_collection_info;
class gsm_layer_collection_info;
class umts_sweep_collection_info;
class umts_layer_collection_info;
class lte_sweep_collection_info;
class lte_layer_3_collection_info;

typedef std::vector<collection_info> collection_info_group_type;

void initialize_collection_info_defaults(const settings &config);

collection_info create_tech_collection_info(rf_phreaker::specifier tech, frequency_type freq, operating_band band);

class collection_info
{
public:
	collection_info()
		: freq_(0)
		, time_ns_(0)
		, bandwidth_(0)
		, sampling_rate_(0)
		, operating_band_(OPERATING_BAND_UNKNOWN)
	{}

	collection_info(frequency_type freq, time_type time_ns, bandwidth_type bw, frequency_type sampling_rate = 0, operating_band band = OPERATING_BAND_UNKNOWN)
		: freq_(freq)
		, time_ns_(time_ns)
		, bandwidth_(bw)
		, sampling_rate_(sampling_rate)
		, operating_band_(band)
	{}

	bool operator==(const collection_info &a)
	{
		return freq_ == a.freq_ && time_ns_ == a.time_ns_ && bandwidth_ == a.bandwidth_ && sampling_rate_ == a.sampling_rate_;
	}

	frequency_type freq_;
	time_type time_ns_;
	bandwidth_type bandwidth_;
	frequency_type sampling_rate_;
	operating_band operating_band_;
};

class sweep_collection_info : public collection_info
{
public:
	sweep_collection_info(frequency_type freq, operating_band band = OPERATING_BAND_UNKNOWN)
		: collection_info(freq, time_ns__, bandwidth__, sampling_rate__, band) {}
	static time_type time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class gsm_sweep_collection_info : public collection_info
{
public:
	gsm_sweep_collection_info(frequency_type freq, operating_band band = OPERATING_BAND_UNKNOWN)
		: collection_info(freq, time_ns__, bandwidth__, sampling_rate__, band) {}
	static time_type time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class gsm_layer_3_collection_info : public collection_info
{
public:
	gsm_layer_3_collection_info(frequency_type freq, operating_band band = OPERATING_BAND_UNKNOWN)
		: collection_info(freq, time_ns__, bandwidth__, sampling_rate__, band) {}
	static time_type time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class umts_sweep_collection_info : public collection_info
{
public:
	umts_sweep_collection_info(frequency_type freq, operating_band band = OPERATING_BAND_UNKNOWN)
		: collection_info(freq, time_ns__, bandwidth__, sampling_rate__, band) {}
	static time_type time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class umts_layer_3_collection_info : public collection_info
{
public:
	umts_layer_3_collection_info(frequency_type freq, operating_band band = OPERATING_BAND_UNKNOWN)
		: collection_info(freq, time_ns__, bandwidth__, sampling_rate__, band) {}
	static time_type time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class lte_sweep_collection_info : public collection_info
{
public:
	lte_sweep_collection_info(frequency_type freq, bandwidth_type bw = bandwidth__, operating_band band = OPERATING_BAND_UNKNOWN) 
		: collection_info(freq, time_ns__, bw, sampling_rate__, band) {}
	static time_type time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class lte_layer_3_collection_info : public collection_info
{
public:
	lte_layer_3_collection_info(frequency_type freq, frequency_type sampling_rate = sampling_rate__, bandwidth_type bw = bandwidth__, operating_band band = OPERATING_BAND_UNKNOWN) 
		: collection_info(freq, time_ns__, bw, sampling_rate, band) {}
	static time_type time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};



}}