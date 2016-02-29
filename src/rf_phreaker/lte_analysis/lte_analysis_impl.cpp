#include "rf_phreaker/lte_analysis/lte_analysis_impl.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "boost/math/special_functions.hpp"

namespace rf_phreaker {

std::mutex lte_analysis_impl::processing_mutex;

lte_analysis_impl::lte_analysis_impl(const lte_config &config, std::atomic_bool *is_cancelled)
	: config_(config)
	, is_cancelled_(is_cancelled)
{
	si_tracker_.set_wanted_si(config.wanted_si());
}

lte_analysis_impl::~lte_analysis_impl()
{}

int lte_analysis_impl::cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, double *avg_rms)
{
	int status = 0;

	try {
		clear_lte_measurements();

		// LTE analysis oversteps the num_half_frames it is processing by NUM_ADDITIONAL_SLOTS_NEEDED_FOR_PROCESSING so we
		// make sure to pass in that much additional signal by reducing the num of half to process.  
		int reduced_num_half_frames = (num_half_frames * 5 - NUM_ADDITIONAL_SLOTS_NEEDED_FOR_PROCESSING) / 5;
		if(reduced_num_half_frames < 2)
			throw lte_analysis_error("Number of LTE half frames to process must be at least " + std::to_string(2 + NUM_ADDITIONAL_SLOTS_NEEDED_FOR_PROCESSING / 5.0) + " half frames long.");
		
		auto num_samples_to_process = calculate_required_num_samples_for_cell_search(num_half_frames);

		int tmp_num_meas = 0;		

		if(raw_signal.sampling_rate() != cell_search_sampling_rate_) {

			auto &filter = get_filter_and_set_resampled_length(raw_signal.sampling_rate(), cell_search_sampling_rate_, num_samples_to_process);
			
			auto required_signal_length = resampled_length_ * (filter.down_factor() / filter.up_factor());

			if(raw_signal.get_iq().length() < required_signal_length)
				throw lte_analysis_error("Number of LTE half frames to process requires a larger input signal.");

			filter.filter(raw_signal.get_iq().get(), resampled_signal_.get(), filter.num_iterations_required(required_signal_length));

			// NOT WORKING - Maybe a bug
			//if(avg_rms)
			//	*avg_rms = ipp_helper::calculate_average_rms(resampled_signal_.get(), resampled_length_ - 25);

			std::lock_guard<std::mutex> lock(processing_mutex);
			status = lte_cell_search(resampled_signal_.get(), resampled_length_ - 25, reduced_num_half_frames, lte_measurements_, tmp_num_meas);

			// Convert frame start sample num.  At this point they are based on the 1.92mhz. 
			// we need to change it to the sampling rate of the input signal.
			for(int i = 0; i < tmp_num_meas; ++i) {
				lte_measurements_[i].PschRecord.StartSampleNum = (int)boost::math::round((double)lte_measurements_[i].PschRecord.StartSampleNum / 
					cell_search_sampling_rate_ * raw_signal.sampling_rate());
				lte_measurements_[i].SschRecord.StartSampleNum = (int)boost::math::round((double)lte_measurements_[i].SschRecord.StartSampleNum / 
					cell_search_sampling_rate_ * raw_signal.sampling_rate());
				lte_measurements_[i].RsRecord.StartSampleNum = (int)boost::math::round((double)lte_measurements_[i].RsRecord.StartSampleNum / 
					cell_search_sampling_rate_ * raw_signal.sampling_rate());
			}
		}
		else {
			if(raw_signal.get_iq().length() < num_samples_to_process)
				throw lte_analysis_error("Number of LTE half frames to process requires a larger input signal.");

			// NOT WORKING - Maybe a bug
			//if(avg_rms)
			//	*avg_rms = ipp_helper::calculate_average_rms(raw_signal.get_iq().get(), raw_signal.get_iq().length());

			std::lock_guard<std::mutex> lock(processing_mutex);
			status = lte_cell_search(raw_signal.get_iq().get(), num_samples_to_process, reduced_num_half_frames, lte_measurements_, tmp_num_meas);
		}


		for(int i = 0; i < tmp_num_meas; ++i) {			
			// If measurement is valid transfer to output.
			if(lte_measurements_[i].SschRecord.NormCorr > 0 && lte_measurements_[i].SschRecord.NormCorr < DBL_MAX) {
				lte_meas.push_back(lte_measurements_[i]);
			}
		}
		// Convert values to dB.
		for(auto &i : lte_meas) {
			i.PschRecord.NormCorr = 20 * log10(i.PschRecord.NormCorr);
			i.SschRecord.NormCorr = 20 * log10(i.SschRecord.NormCorr);
			i.sync_quality = 20 * log10(i.sync_quality);
			i.estimated_rsrq = 20 * log10(i.estimated_rsrq);
		}
	}
	catch(const rf_phreaker_error &err) {
		rf_phreaker::delegate_sink::instance().log_error(err);
		std::cout << err.what() << std::endl;
		status = -1;
	}
	catch(const std::exception &err) {
		rf_phreaker::delegate_sink::instance().log_error(err.what(), generic_error_type, STD_EXCEPTION_ERROR);
		std::cout << err.what() << std::endl;
		status = -2;
	}

	return status;
}

rf_phreaker::fir_filter& lte_analysis_impl::get_filter_and_set_resampled_length(rf_phreaker::frequency_type input_sampling_rate, rf_phreaker::frequency_type output_sampling_rate, int num_resampled_samples)
{
	sampling_rates wanted(sampling_rates(input_sampling_rate, output_sampling_rate));
	auto it = filters_.find(wanted);
	if(it == filters_.end()) {
		auto filter = std::make_shared<rf_phreaker::fir_filter>();
		filter->set_zero_delay(true);
		filter->set_up_down_factor_based_on_sampling_rates(input_sampling_rate, output_sampling_rate);
		filter->set_taps();
		it = filters_.insert(std::make_pair(wanted, filter)).first;
	}

	auto &filter = *it->second;

	resampled_length_ = num_resampled_samples;
	// We reset length because the filter uses the array length when filtering.
	if(resampled_length_ != resampled_signal_.length())
		resampled_signal_.reset(resampled_length_);

	return filter;
}

int lte_analysis_impl::calculate_required_num_samples_for_cell_search(int num_half_frames)
{
	return rf_phreaker::convert_to_samples(milli_to_nano(5 * num_half_frames), cell_search_sampling_rate_);
}

void lte_analysis_impl::clear_lte_measurements()
{
	lte_measurements_.resize(num_measurements);
	for(auto &lte : lte_measurements_) {
		lte.clear();
	}
}

int lte_analysis_impl::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, int meas_to_process)
{
	int status = 0;

	try {
		if(meas_to_process >= (int)lte_meas.size())
			throw lte_analysis_error("LTE measurement is not within vector range.");

		if(num_half_frames < 2)
			throw lte_analysis_error("Number of LTE half frames to process must be at least 2 half frames long.");

		auto needed_sampling_rate = determine_sampling_rate(raw_signal, lte_meas);
		if(needed_sampling_rate == 0) {
			status = 0;
		}
		else if(needed_sampling_rate == raw_signal.sampling_rate()) {
			// If we have the scheduling_info use it immediately, otherwise pass in nullptr for hint so that we only try to decode sib1 and then decode using hint.
			if(si_tracker_.has_scheduling_info(raw_signal.frequency(), lte_meas[meas_to_process])) {
				status = decode_layer_3_using_hint(raw_signal, lte_meas, num_half_frames, meas_to_process);
			}
			else {
				std::lock_guard<std::mutex> lock(processing_mutex);
				status = lte_decode_data(raw_signal.get_iq().get(), raw_signal.get_iq().length(), num_half_frames, lte_meas, meas_to_process, nullptr, is_cancelled_);
				si_tracker_.update(raw_signal.frequency(), lte_meas[meas_to_process]);
				// Try again in case we were able to find scheduling info.
				status = decode_layer_3_using_hint(raw_signal, lte_meas, num_half_frames, meas_to_process);
			}
		}
		// Currently LTE will report the wrong bandwidth.  Because of this we never try resampling to a lower bandwidth.
		//else if(needed_sampling_rate < raw_signal.sampling_rate())
		//{
		//	auto &filter = get_filter_and_set_resampled_length(raw_signal.sampling_rate(), needed_sampling_rate,
		//													   rf_phreaker::convert_to_samples(milli_to_nano(5 * num_half_frames), raw_signal.sampling_rate()));

		//	filter.filter(raw_signal.get_iq().get(), resampled_signal_.get(), filter.num_iterations_required(raw_signal.get_iq().length()));

		//	std::lock_guard<std::mutex> lock(processing_mutex);
		//	status = lte_decode_data(resampled_signal_.get(), resampled_length_, num_half_frames, lte_meas);
		//}	
		else/* if(needed_sampling_rate > raw_signal.sampling_rate()) */{
			status = 0;
		}
		//else
		//	assert(0 && "Error when determining LTE sampling rate.  We reach an invalid branch!");
	}
	catch(const rf_phreaker_error &err) {
		rf_phreaker::delegate_sink::instance().log_error(err);
		std::cout << err.what() << std::endl;
		status = -1;
	}
	catch(const std::exception &err) {
		rf_phreaker::delegate_sink::instance().log_error(err.what(), generic_error_type, STD_EXCEPTION_ERROR);
		std::cout << err.what() << std::endl;
		status = -2;
	}

	return status;
}

rf_phreaker::frequency_type lte_analysis_impl::determine_sampling_rate(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas)
{
	rf_phreaker::frequency_type sampling_rate = 0;

	for(auto &lte : lte_meas) {
		switch(lte.Bandwidth) {
		case LteBandwidth_5MHZ:
			sampling_rate = lte_bandwidth_5_mhz_sampling_rate;
			break;
		case LteBandwidth_10MHZ:
			sampling_rate = lte_bandwidth_10_mhz_sampling_rate;
			break;
		case LteBandwidth_15MHZ:
			sampling_rate = lte_bandwidth_15_mhz_sampling_rate;
			break;
		case LteBandwidth_20MHZ:
			sampling_rate = lte_bandwidth_20_mhz_sampling_rate;
			break;
		case LteBandwidth_3MHZ:
			sampling_rate = lte_bandwidth_3_mhz_sampling_rate;
			break;
		case LteBandwidth_1_4MHZ:
			sampling_rate = lte_bandwidth_1_4_mhz_sampling_rate;
			break;
		default:;
		}
		if(sampling_rate != 0)
			break;
	}

	return sampling_rate;
}

int lte_analysis_impl::decode_layer_3_using_hint(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames, int meas_to_process) {
	int status = 0;
	auto hint = si_tracker_.get_needed_scheduling_info(raw_signal.frequency(), lte_meas[meas_to_process]);
	if(hint.g_.size()) {
		status = lte_decode_data(raw_signal.get_iq().get(), raw_signal.get_iq().length(), num_half_frames, lte_meas, meas_to_process, &hint, is_cancelled_);
		si_tracker_.update(raw_signal.frequency(), lte_meas[meas_to_process]);
	}
	return status;
}

void lte_analysis_impl::clear_tracking_si(frequency_type freq) {
	si_tracker_.clear(freq);
}

void lte_analysis_impl::clear_all_tracking_si() {
	si_tracker_.clear();
}

void lte_analysis_impl::set_config(const lte_config &config) {
	config_ = config;
}
}