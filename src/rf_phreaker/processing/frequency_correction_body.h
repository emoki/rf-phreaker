#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/common/log.h"
#include "tbb/flow_graph.h"
#include <tuple>
#include <set>
#include <map>

namespace rf_phreaker { namespace processing {

struct correction_lookup {
	correction_lookup() : has_insertions_(false) {}

	void insert(int cpich, double ecio, int freq_shift) {
		auto it = cpichs_.find(cpich);
		if(it == cpichs_.end()) {
			ecio_freq_shift_group_type tmp;
			it = cpichs_.insert(std::make_pair(cpich, tmp)).first;
		}
		it->second.insert(std::make_pair(ecio, freq_shift));
		has_insertions_ = true;
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

	bool has_insertions() { return has_insertions_; }

	typedef std::multimap<double, int, std::greater<double>> ecio_freq_shift_group_type;
	typedef std::map<int, ecio_freq_shift_group_type> cpich_group_type;
	cpich_group_type cpichs_;
	bool has_insertions_;
};

struct freq_correction_param 
{
	umts_scan_type scan_type_;
	double sensitivity_;
	int num_coherent_slots_;
	int start_freq_;
	int end_freq_;
	int increment_;
};

class frequency_correction_body
{
public:
	frequency_correction_body(tbb::flow::graph *graph, scanner::scanner_controller_interface *sc, data_output_async *out, const collection_settings &s, const frequency_correction_settings &freq_corr_settings, const umts_general_settings &layer_3_settings)
		: graph_(graph)
		, sc_(sc)
		, io_(out)
		, umts_settings_((int)s.sampling_rate_, (int)s.sampling_rate_, rf_phreaker::convert_to_samples(s.collection_time_, s.sampling_rate_), freq_corr_settings.general_settings_.num_coherent_slots_)
		, analysis_(umts_settings_)
		, frequency_correction_settings_(freq_corr_settings)
		, layer_3_settings_(layer_3_settings)
		, shifter_((double)s.sampling_rate_)
		, error_sum_(0)
		, num_shifts_(0)
		, has_corrected_freq_error_(false)
		, min_collection_round_(1)
	{
		if(frequency_correction_settings_.initial_frequency_correction_range_start_ >= frequency_correction_settings_.initial_frequency_correction_range_end_)
			throw processing_error("Frequency correction range is invalid.  Please choose start value lower than the end value.");
	}

	frequency_correction_body(const frequency_correction_body &b)
		: graph_(b.graph_)
		, sc_(b.sc_)
		, io_(b.io_)
		, umts_settings_(b.umts_settings_)
		, analysis_(b.umts_settings_)
		, frequency_correction_settings_(b.frequency_correction_settings_)
		, layer_3_settings_(b.layer_3_settings_)
		, shifter_(umts_settings_.sampling_rate())
		, error_sum_(b.error_sum_)
		, num_shifts_(b.num_shifts_)
		, has_corrected_freq_error_(false)
		, min_collection_round_(b.min_collection_round_)
	{}

	void operator()(measurement_package info, umts_output_and_feedback_node::output_ports_type &out)
	{
		if(info->collection_round() > min_collection_round_ && num_shifts_ > 10 || (info->collection_round() > 8)) {
			graph_->root_task()->cancel_group_execution();
			if(num_shifts_ > 0) {
				auto avg_error = error_sum_ / (double)num_shifts_;
				sc_->calculate_vctcxo_trim_and_update_calibration(avg_error).get();

				std::string message("Frequency correction successful.");

				delegate_sink_async::instance().log_message(message, FREQUENCY_CORRECTION_SUCCESSFUL);

				io_->output(sc_->get_scanner().get()->get_hardware());
			}
			else {
				delegate_sink_async::instance().log_error("Frequency correction failed.", FREQUENCY_CORRECTION_FAILED);
			}

			return;
		}

		// For the first collection round we reduce the sensitivity and perform a full scan.
		freq_correction_param param;
		param.scan_type_ = full_scan_type;
		param.sensitivity_ = frequency_correction_settings_.general_settings_.sensitivity_;
		param.num_coherent_slots_ = /*has_corrected_freq_error_ ? layer_3_settings_.num_coherent_slots_ :*/ 2;
		param.start_freq_ = (has_corrected_freq_error_ && frequency_correction_settings_.initial_frequency_correction_range_start_ < -250) ? -250 : frequency_correction_settings_.initial_frequency_correction_range_start_;
		param.end_freq_ = (has_corrected_freq_error_ && frequency_correction_settings_.initial_frequency_correction_range_end_ > 250) ? 250 : frequency_correction_settings_.initial_frequency_correction_range_end_;
		param.increment_ = (has_corrected_freq_error_) ? 10 : 50;
	
		if(has_corrected_freq_error_ && info->collection_round() > 0) {
			param.scan_type_ = candidate_all_timeslots_scan_type;
			param.sensitivity_ = layer_3_settings_.sensitivity_;
			param.start_freq_ = (frequency_correction_settings_.initial_frequency_correction_range_start_ < -70) ? -70 : frequency_correction_settings_.initial_frequency_correction_range_start_;
			param.end_freq_ = (frequency_correction_settings_.initial_frequency_correction_range_end_ > 70) ? 70 : frequency_correction_settings_.initial_frequency_correction_range_end_;
			param.num_coherent_slots_ = layer_3_settings_.num_coherent_slots_;
			param.increment_ = 2;
		}

		auto correction = determine_freq_correction(info, param);

		// If no insertions change parameters and try again.
		if(!correction.has_insertions()) {
			LOG(LDEBUG) << "Unable to find cells.  Increasing sensitivity...";
			param.scan_type_ = full_scan_type;
			param.sensitivity_ = layer_3_settings_.sensitivity_;
			param.num_coherent_slots_ = layer_3_settings_.num_coherent_slots_;
			param.increment_ = 20;

			correction = determine_freq_correction(info, param);
			if(!correction.has_insertions()) {
				LOG(LDEBUG) << "Unable to find cells.  Expanding frequency range...";
				param.start_freq_ = frequency_correction_settings_.initial_frequency_correction_range_start_;
				param.end_freq_ = frequency_correction_settings_.initial_frequency_correction_range_end_;
				correction = determine_freq_correction(info, param);
			}
		}

		if(correction.has_insertions()) {
			auto best_shift = correction.find_best_freq_shift();

			LOG(LDEBUG) << correction.cpichs_.size() << " cells found. Best shifts averaged = " << best_shift << "hz.";
			
			if(info->collection_round() > min_collection_round_) {
				++num_shifts_;
				error_sum_ += calculate_error(best_shift, info->frequency());
			}
			else {
				sc_->calculate_and_update_vctcxo_trim(calculate_error(best_shift, info->frequency()));
				has_corrected_freq_error_ = true;
			}
		}
		else {
			LOG(LDEBUG) << "No valid cells found.";
		}

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	double calculate_error(frequency_type shift, frequency_type carrier_freq) {
		return shift * (38.4e6 / carrier_freq);
	}
	
	correction_lookup determine_freq_correction(measurement_package &info, const freq_correction_param &param)
	{
		correction_lookup correction;

		int num_meas = 100;
		umts_measurements meas(num_meas);
	
		analysis_.set_num_coherent_slots_for_psch(param.num_coherent_slots_);

		LOG(LDEBUG) << "Starting frequency correction for " << info->frequency() / 1e6 << "mhz. Start offset = " << param.start_freq_ << "hz. End offset = " << param.end_freq_ << "hz. Increment = " << param.increment_ << "hz.";
		for(int i = param.start_freq_; i <= param.end_freq_; i += param.increment_) {
			num_meas = 100;
			raw_signal shifted_signal(*info);
			shifter_.shift_frequency(shifted_signal.get_iq(), shifted_signal.get_iq().length(), i);
			auto status = analysis_.cell_search(shifted_signal, &meas[0], num_meas, param.sensitivity_, param.scan_type_);
			if(status != 0)
				throw umts_analysis_error("Error processing umts.");

			for(int j = 0; j < num_meas; ++j) {
				correction.insert(meas[j].cpich_, meas[j].ecio_, i);
			}
		}

		return correction;
	}

	tbb::flow::graph *graph_;
	scanner::scanner_controller_interface *sc_;
	data_output_async *io_;
	umts_config umts_settings_;
	umts_analysis analysis_;
	frequency_correction_settings frequency_correction_settings_;
	umts_general_settings layer_3_settings_;
	frequency_shifter shifter_;

	double error_sum_;
	double num_shifts_;
	bool has_corrected_freq_error_;
	int min_collection_round_;
};


}}