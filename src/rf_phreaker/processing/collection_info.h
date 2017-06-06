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

collection_info create_tech_collection_info(rf_phreaker::specifier tech, frequency_type freq, operating_band band, bool can_remove = false);

collection_info create_sweep_collection_info(rf_phreaker::specifiers specs, rf_phreaker::frequency_type freq, operating_bands bands, bool can_remove = false);

class collection_info
{
public:
	collection_info()
		: freq_(0)
		, time_ns_(0)
		, overlap_time_ns_(0)
		, bandwidth_(0)
		, sampling_rate_(0)
		, operating_bands_({OPERATING_BAND_UNKNOWN})
		, can_remove_(false)
		, params_(power_spectrum_spec{}) {}

	collection_info(frequency_type freq, time_type time_ns, time_type overlap_time_ns, bandwidth_type bw, frequency_type sampling_rate = 0, specifiers spec = {UNKOWN_SPECIFIER},
		operating_bands bands = {OPERATING_BAND_UNKNOWN}, bool can_remove = false, const power_spectrum_spec &params = {})
		: freq_(freq)
		, time_ns_(time_ns)
		, overlap_time_ns_(overlap_time_ns)
		, bandwidth_(bw)
		, sampling_rate_(sampling_rate)
		, operating_bands_(bands)
		, can_remove_(can_remove)
		, specs_(spec)
		, params_(params) {}

	collection_info(const collection_info &a)
		: freq_(a.freq_)
		, time_ns_(a.time_ns_)
		, overlap_time_ns_(a.overlap_time_ns_)
		, bandwidth_(a.bandwidth_)
		, sampling_rate_(a.sampling_rate_)
		, operating_bands_(a.operating_bands_)
		, can_remove_(a.can_remove_)
		, specs_(a.specs_)
		, params_(a.params_) {}

	collection_info(collection_info &&a)
		: freq_(a.freq_)
		, time_ns_(a.time_ns_)
		, overlap_time_ns_(a.overlap_time_ns_)
		, bandwidth_(a.bandwidth_)
		, sampling_rate_(a.sampling_rate_)
		, operating_bands_(std::move(a.operating_bands_))
		, can_remove_(a.can_remove_)
		, specs_(std::move(a.specs_))
		, params_(std::move(a.params_)) {}

	collection_info& operator=(collection_info a) {
		this->swap(a);
		return *this;
	}

	void swap(collection_info &a) {
		std::swap(freq_, a.freq_);
		std::swap(time_ns_, a.time_ns_);
		std::swap(overlap_time_ns_, a.overlap_time_ns_);
		std::swap(bandwidth_, a.bandwidth_);
		std::swap(sampling_rate_, a.sampling_rate_);
		operating_bands_.swap(a.operating_bands_);
		std::swap(can_remove_, a.can_remove_);
		specs_.swap(a.specs_);
		std::swap(params_, a.params_);
	}

	bool operator==(const collection_info &a) const {
		return freq_ == a.freq_ && time_ns_ == a.time_ns_ && overlap_time_ns_ == a.overlap_time_ns_ 
			&& bandwidth_ == a.bandwidth_ && sampling_rate_ == a.sampling_rate_&& operating_bands_ == a.operating_bands_ 
			&& can_remove_ == a.can_remove_ && specs_ == a.specs_;
	}

	bool partial_equal(const collection_info &a) const {
		return freq_ == a.freq_ && time_ns_ == a.time_ns_ && overlap_time_ns_ == a.overlap_time_ns_
			&& bandwidth_ == a.bandwidth_ && sampling_rate_ == a.sampling_rate_
			&& can_remove_ == a.can_remove_;
	}

	bool partial_equal_specs_overlap(const collection_info &a) const {
		return partial_equal(a) && specs_.does_overlap(a.specs_);
	}

	operating_band get_band() const { return operating_bands_.get_first_band(); }

	frequency_type freq_;
	time_type time_ns_;
	time_type overlap_time_ns_;
	bandwidth_type bandwidth_;
	frequency_type sampling_rate_;
	operating_bands operating_bands_;
	bool can_remove_;
	specifiers specs_;
	power_spectrum_spec params_;
};

class sweep_collection_info : public collection_info
{
public:
	sweep_collection_info(frequency_type freq, specifiers specs = {}, operating_bands bands = OPERATING_BAND_UNKNOWN, bool can_remove = false)
		: collection_info(freq, time_ns__, overlap_time_ns__, bandwidth__, sampling_rate__, specs, bands, can_remove) {}
	static time_type time_ns__;
	static time_type overlap_time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class gsm_sweep_collection_info : public collection_info
{
public:
	gsm_sweep_collection_info(frequency_type freq, operating_bands bands = OPERATING_BAND_UNKNOWN, bool can_remove = false)
		: collection_info(freq, time_ns__, overlap_time_ns__, bandwidth__, sampling_rate__, GSM_SWEEP, bands, can_remove) {}
	static time_type time_ns__;
	static time_type overlap_time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class gsm_layer_3_collection_info : public collection_info
{
public:
	gsm_layer_3_collection_info(frequency_type freq, operating_bands bands = OPERATING_BAND_UNKNOWN, bool can_remove = false)
		: collection_info(freq, time_ns__, overlap_time_ns__, bandwidth__, sampling_rate__, GSM_LAYER_3_DECODE, bands, can_remove) {}
	static time_type time_ns__;
	static time_type overlap_time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class umts_sweep_collection_info : public collection_info
{
public:
	umts_sweep_collection_info(frequency_type freq, operating_bands bands = OPERATING_BAND_UNKNOWN, bool can_remove = false)
		: collection_info(freq, time_ns__, overlap_time_ns__, bandwidth__, sampling_rate__, UMTS_SWEEP, bands, can_remove) {}
	static time_type time_ns__;
	static time_type overlap_time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class umts_layer_3_collection_info : public collection_info
{
public:
	umts_layer_3_collection_info(frequency_type freq, operating_bands bands = OPERATING_BAND_UNKNOWN, bool can_remove = false)
		: collection_info(freq, time_ns__, overlap_time_ns__, bandwidth__, sampling_rate__, UMTS_LAYER_3_DECODE, bands, can_remove) {}
	static time_type time_ns__;
	static time_type overlap_time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class lte_sweep_collection_info : public collection_info
{
public:
	lte_sweep_collection_info(frequency_type freq, bandwidth_type bw = bandwidth__, operating_bands bands = OPERATING_BAND_UNKNOWN, bool can_remove = false)
		: collection_info(freq, time_ns__, overlap_time_ns__, bw, sampling_rate__, LTE_SWEEP, bands, can_remove) {}
	static time_type time_ns__;
	static time_type overlap_time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class lte_layer_3_collection_info : public collection_info
{
public:
	lte_layer_3_collection_info(frequency_type freq, frequency_type sampling_rate = sampling_rate__, bandwidth_type bw = bandwidth__,
		operating_bands bands = OPERATING_BAND_UNKNOWN, bool can_remove = false)
		: collection_info(freq, time_ns__, overlap_time_ns__, bw, sampling_rate, LTE_LAYER_3_DECODE, bands, can_remove) {}
	static time_type time_ns__;
	static time_type overlap_time_ns__;
	static bandwidth_type bandwidth__;
	static frequency_type sampling_rate__;
};

class power_spectrum_collection_info : public collection_info
{
public:
	power_spectrum_collection_info(frequency_type freq, time_type time_ns, time_type overlap_time_ns, bandwidth_type bw, frequency_type sampling_rate, const power_spectrum_spec &spec)
		: collection_info(freq, time_ns, overlap_time_ns, bw, sampling_rate, POWER_SPECTRUM, OPERATING_BAND_UNKNOWN, false, spec) {}
};



}}