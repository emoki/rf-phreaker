#pragma once
#include "boost/multi_index_container.hpp"
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include "boost/multi_index/key_extractors.hpp"
#include <rf_phreaker/rf_phreaker_gui/Base.h>
#include "rf_phreaker/common/measurements.h"

namespace mi = boost::multi_index;

//namespace rf_phreaker { namespace gui {

struct unique_lookup{};
struct random_access{};
struct freq{};

struct index_frequency {
	typedef rf_phreaker::frequency_type result_type;
	result_type operator()(const Base *b) const {
		return b->base().carrier_frequency_;
	}
	result_type operator()(const rf_phreaker::basic_data &b) const {
		return b.carrier_frequency_;
	}
};

struct index_tech {
	typedef ApiTypes::Tech result_type;
	result_type operator()(const Base *b) const {
		return b->cellTech();
	}
	result_type operator()(const rf_phreaker::gsm_data &) const {
		return ApiTypes::GSM_FULL_SCAN;
	}
	result_type operator()(const rf_phreaker::umts_data &) const {
		return ApiTypes::WCDMA_FULL_SCAN;
	}
	result_type operator()(const rf_phreaker::lte_data &) const {
		return ApiTypes::LTE_FULL_SCAN;
	}
};

struct index_id {
	typedef int32_t result_type;
	result_type operator()(const Base *b) const {
		return b->cellId();
	}
	result_type operator()(const rf_phreaker::gsm_data &b) const {
		return b.bsic_;
	}
	result_type operator()(const rf_phreaker::umts_data &b) const {
		return b.cpich_;
	}
	result_type operator()(const rf_phreaker::lte_data &b) const {
		return b.physical_cell_id_;
	}
};

struct index_cell_sl {
	typedef int32_t result_type;
	result_type operator()(const rf_phreaker::gsm_data &b) const {
		return b.cell_signal_level_;
	}
	result_type operator()(const rf_phreaker::umts_data &b) const {
		return b.rscp_;
	}
	result_type operator()(const rf_phreaker::lte_data &b) const {
		return b.carrier_signal_level_ + b.sync_quality_;
	}
};

template<typename Data>
struct index_update {
	index_update(const Data &data) : data_(data) {}
	void operator()(Base *b) {
		b->update(data_);
	}
	const Data &data_;
};

struct less_than_cell_sl {
	template<typename Data>
	bool operator()(const Base *b, const Data &a) const {
		static index_cell_sl sl;
		return b->cellSignalLevel() < sl(a);
	}
	template<typename Data>
	bool operator()(const Data &a, const Base *b) const {
		static index_cell_sl sl;
		return sl(a) < b->cellSignalLevel();
	}
	template<typename Data>
	bool operator()(const Data &a, const Data &b) const {
		static index_cell_sl sl;
		return sl(a) < sl(b);
	}
	template<typename Data>
	bool operator()(double cell_sl, const Data &b) const {
		index_cell_sl sl;
		return cell_sl < sl(b);
	}
};

typedef boost::multi_index_container<
	Base*,
	mi::indexed_by<
		mi::ordered_unique<
			mi::tag<unique_lookup>,
			mi::composite_key<
				Base*,
				index_tech,
				index_frequency,
				index_id
			>
		>,
		mi::random_access<
			mi::tag<random_access>
		>/*,
		mi::ordered_non_unique<
			mi::tag<freq>,
			index_frequency
		>*/
	>
> data_index;

typedef data_index::index<unique_lookup> by_unique_lookup;
typedef data_index::index<random_access> by_random_access;
typedef data_index::index<freq> by_freq;

template<typename IndexIterator>
data_index::size_type index_position(const data_index &di, IndexIterator it) {
	return mi::project<random_access>(di, it) - di.get<random_access>().begin();
}

//}}
