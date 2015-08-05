#pragma once
#include "rf_phreaker/processing/node_defs.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/processing/frequency_correction_calculator.h"
#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/common/log.h"
#include "tbb/flow_graph.h"
#include <tuple>

namespace rf_phreaker { namespace processing {

class frequency_correction_body
{
public:
	frequency_correction_body(tbb::flow::graph *graph, scanner::scanner_controller_interface *sc, data_output_async *out, const collection_settings &s, const frequency_correction_settings &freq_corr_settings, const umts_general_settings &layer_3_settings)
		: graph_(graph)
		, sc_(sc)
		, io_(out)
		, frequency_correction_settings_(freq_corr_settings)
		, layer_3_settings_(layer_3_settings)
		, umts_settings_((int)s.sampling_rate_, (int)s.sampling_rate_, rf_phreaker::convert_to_samples(s.collection_time_, s.sampling_rate_), freq_corr_settings.general_settings_.num_coherent_slots_)
		, analysis_(umts_settings_)
		, calculator_((double)s.sampling_rate_)
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
		, frequency_correction_settings_(b.frequency_correction_settings_)
		, umts_settings_(b.umts_settings_)
		, analysis_(b.umts_settings_)
		, calculator_(b.calculator_)
		, layer_3_settings_(b.layer_3_settings_)
		, error_sum_(b.error_sum_)
		, num_shifts_(b.num_shifts_)
		, has_corrected_freq_error_(false)
		, min_collection_round_(b.min_collection_round_)
	{}

	void operator()(measurement_package package, umts_output_and_feedback_node::output_ports_type &out)
	{
		auto meas = *package.measurement_info_.get();
		if(meas.collection_round() > min_collection_round_ && num_shifts_ > 10 || (meas.collection_round() > 8)) {
			graph_->root_task()->cancel_group_execution();
			if(num_shifts_ > 0) {
				auto avg_error = error_sum_ / (double)num_shifts_;
				update_frequency_correction(avg_error);

				std::string message("Frequency correction successful.");

				delegate_sink::instance().log_message(message, no_error_type, FREQUENCY_CORRECTION_SUCCESSFUL);

				io_->output(sc_->get_scanner().get()->get_hardware());
			}
			else {
				delegate_sink::instance().log_error("Frequency correction failed.", processing_error_type, FREQUENCY_CORRECTION_FAILED);
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
	
		if(has_corrected_freq_error_ && meas.collection_round() > 0) {
			param.scan_type_ = candidate_all_timeslots_scan_type;
			param.sensitivity_ = layer_3_settings_.sensitivity_;
			param.start_freq_ = (frequency_correction_settings_.initial_frequency_correction_range_start_ < -70) ? -70 : frequency_correction_settings_.initial_frequency_correction_range_start_;
			param.end_freq_ = (frequency_correction_settings_.initial_frequency_correction_range_end_ > 70) ? 70 : frequency_correction_settings_.initial_frequency_correction_range_end_;
			param.num_coherent_slots_ = layer_3_settings_.num_coherent_slots_;
			param.increment_ = 2;
		}

		auto correction = calculator_.determine_freq_correction(meas, analysis_, param);

		// If no insertions change parameters and try again.
		if(!correction.has_insertions()) {
			LOG(LDEBUG) << "Unable to find cells.  Increasing sensitivity...";
			param.scan_type_ = full_scan_type;
			param.sensitivity_ = layer_3_settings_.sensitivity_;
			param.num_coherent_slots_ = layer_3_settings_.num_coherent_slots_;
			param.increment_ = 20;

			correction = calculator_.determine_freq_correction(meas, analysis_, param);
			if(!correction.has_insertions()) {
				LOG(LDEBUG) << "Unable to find cells.  Expanding frequency range...";
				param.start_freq_ = frequency_correction_settings_.initial_frequency_correction_range_start_;
				param.end_freq_ = frequency_correction_settings_.initial_frequency_correction_range_end_;
				correction = calculator_.determine_freq_correction(meas, analysis_, param);
			}
		}

		if(correction.has_insertions()) {
			auto best_shift = correction.find_best_freq_shift();

			LOG(LDEBUG) << correction.cpichs_.size() << " cells found. Best shifts averaged = " << best_shift << "hz.";
			
			if(meas.collection_round() > min_collection_round_) {
				++num_shifts_;
				error_sum_ += calculator_.calculate_error(best_shift, meas.frequency());
			}
			else {
				update_frequency_correction(calculator_.calculate_error(best_shift, meas.frequency()));
			}
		}
		else {
			LOG(LDEBUG) << "No valid cells found.";
		}

		std::get<1>(out).try_put(tbb::flow::continue_msg());
	}

private:
	void update_frequency_correction(double error_hz) {
		sc_->calculate_and_update_vctcxo_trim(error_hz).get();
		g_scanner_error_tracker::instance().new_freq_correction();
		has_corrected_freq_error_ = true;
	}

	tbb::flow::graph *graph_;
	scanner::scanner_controller_interface *sc_;
	data_output_async *io_;
	frequency_correction_settings frequency_correction_settings_;
	umts_general_settings layer_3_settings_;
	umts_config umts_settings_;
	umts_analysis analysis_;
	frequency_correction_calculator calculator_;
	double error_sum_;
	double num_shifts_;
	bool has_corrected_freq_error_;
	int min_collection_round_;
};


}}