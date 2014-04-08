#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/frequency_shifter.h"
#include "tbb/flow_graph.h"
#include <tuple>
#include <set>
#include <map>

namespace rf_phreaker { namespace processing {

struct correction_lookup {
	typedef std::multimap<double, int, std::greater<double>> ecio_freq_shift_group_type;
	typedef std::map<int, ecio_freq_shift_group_type> cpich_group_type;
	cpich_group_type cpichs_;

	void insert(int cpich, double ecio, int freq_shift) {
		auto it = cpichs_.find(cpich);
		if(it == cpichs_.end()) {
			ecio_freq_shift_group_type tmp;
			it = cpichs_.insert(std::make_pair(cpich, tmp)).first;
		}
		it->second.insert(std::make_pair(ecio, freq_shift));
	}

	int find_best_freq_shift() {
		int freq_shift = 0;
		if(cpichs_.size()) {
			for(auto &ecio_freq : cpichs_) {
				freq_shift += ecio_freq.second.begin()->second;
			}
			freq_shift /= (int)cpichs_.size();
		}
		return freq_shift;
	}
};

class frequency_correction_body
{
public:
	frequency_correction_body(tbb::flow::graph *graph, scanner::scanner_controller_interface *sc, const collection_settings &s, const umts_general_settings &g, int freq_corrections_required = 4)
		: graph_(graph)
		, sc_(sc)
		, umts_settings_((int)s.sampling_rate_, (int)s.sampling_rate_, rf_phreaker::convert_to_samples(s.collection_time_, s.sampling_rate_))
		, analysis_(umts_settings_)
		, freq_corrections_required_(freq_corrections_required)
		, general_settings_(g)
		, shifter_((double)s.sampling_rate_)
	{}

	frequency_correction_body(const frequency_correction_body &b)
		: graph_(b.graph_)
		, sc_(b.sc_)
		, umts_settings_(b.umts_settings_)
		, analysis_(b.umts_settings_)
		, freq_corrections_required_(b.freq_corrections_required_)
		, general_settings_(b.general_settings_)
		, shifter_(umts_settings_.sampling_rate())
	{}

	void operator()(measurement_package info, umts_output_and_feedback_node::output_ports_type &out)
	{
		//if(--freq_corrections_required_ < 0) {
		//	graph_->root_task()->cancel_group_execution();
		//}

		correction_lookup correction;

		int num_meas = 100;
		umts_measurements meas(num_meas);
		double rms = 0;

		// Change scan_type to candidate_one_timeslot_scan_type once we have tracking.
		auto scan_type = full_scan_type;// candidate_all_timeslots_scan_type;

		int status = analysis_.cell_search(*info, &meas[0], num_meas, general_settings_.sensitivity_, scan_type);
		if(status != 0)
			throw umts_analysis_error("Error processing umts.");
		
		for(int i = khz(-2); i <= khz(2); i += 5) {
			num_meas = 100;
			raw_signal shifted_signal(*info);
			shifter_.shift_frequency(shifted_signal.get_iq(), shifted_signal.get_iq().length(), i);
			status = analysis_.cell_search(shifted_signal, &meas[0], num_meas, general_settings_.sensitivity_, candidate_all_timeslots_scan_type);
			if(status != 0)
				throw umts_analysis_error("Error processing umts.");

			for(int j = 0; j < num_meas; ++j) {
				correction.insert(meas[j].cpich_, meas[j].ecio_, i);
			}
		}

		auto best_shift = correction.find_best_freq_shift();

		if(best_shift != 0)
			sc_->update_vctcxo_trim(info->frequency(), best_shift);

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	tbb::flow::graph *graph_;
	scanner::scanner_controller_interface *sc_;
	umts_config umts_settings_;
	umts_analysis analysis_;
	int freq_corrections_required_;
	umts_general_settings general_settings_;
	frequency_shifter shifter_;
};


}}