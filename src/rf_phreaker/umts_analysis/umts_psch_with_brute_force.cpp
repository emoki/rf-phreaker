#include "rf_phreaker/umts_analysis/umts_psch_with_brute_force.h"
#include "rf_phreaker/umts_analysis/umts_utilities.h"
#include "rf_phreaker/umts_analysis/sort_peaks.h"
#include "rf_phreaker/umts_analysis/psch_container.h"
#include "boost/math/special_functions.hpp"
#include <map>

//#include "frequency_correction.h"





umts_psch_with_brute_force::umts_psch_with_brute_force(const umts_config &config, const /*cpich_table_container&*/Ipp32fc* resampled_cpich_table)
: pause_(-1)
, num_coherent_psch_slots_(2)
, max_num_psch_peaks_(25)
, max_num_candidates_(1000)
, psch_confidence_threshold_(11)
, cpich_confidence_threshold_(13)
{
	cancel_processing_ = false;
	
	set_config(config);
		
	resampled_cpich_table_ = resampled_cpich_table;
}

void umts_psch_with_brute_force::set_config(const umts_config &config)
{
	psch_container psch;
	psch.generate_resampled_psch(config.sampling_rate());
	psch_template_ = psch.resampled_psch_array();

	do_we_benchmark_ = config.benchmark_umts_brute_force();

#ifdef USE_PSCH_BRUTE_FORCE_BENCHMARK 	
	if(do_we_benchmark_)
		benchmark_.open_benchmark(config.umts_brute_force_filename(), false);
#endif

	sample_rate_ = config.sampling_rate();
	clock_rate_ = config.clock_rate();
	over_sampling_rate_ = config.over_sampling_rate();
	num_samples_per_cpich_ = static_cast<int>(N_TOTAL_CHIPS_CPICH * over_sampling_rate_);
	num_samples_per_time_slot_ = static_cast<int>(N_CHIPS_PER_TIMESLOT * over_sampling_rate_);
	max_processing_length_ = num_samples_per_time_slot_ * num_coherent_psch_slots_ * 20; // somewhat arbitrary right now.. perhaps make it configurable?

}

umts_measurements umts_psch_with_brute_force::process(const ipp_32fc_array &signal, const umts_measurements &tracking_measurements, uint32_t num_cpich_chips, umts_scan_type scanning_method)
{
#ifdef USE_PSCH_BRUTE_FORCE_BENCHMARK 	
	if(do_we_benchmark_)
	{
		benchmark_.clear();
		benchmark_.start_timer();
	}
#endif
	length_to_process_ = signal.length() > max_processing_length_ ? max_processing_length_ : signal.length();


	adjust_clock_error_rate();

	double seconds = /*packet.getTimeSince1970()*/0 + (static_cast<double>(/*packet.getLongCounterLatched()*/0) / clock_rate_);

	time_of_packet_uframes_ = static_cast<uint64_t>(seconds * 100 * 1000000);
	
	average_rms_ = ipp_helper::calculate_average_rms(signal.get(), length_to_process_);

#ifdef USE_PSCH_BRUTE_FORCE_BENCHMARK 	
	if(do_we_benchmark_)
	{
		benchmark_.stop_timer();
		benchmark_.output_time_elapsed(std::string("calculate_sl\t"));
		benchmark_.start_timer();
	}
#endif

	//if(do_we_benchmark_)
	//{
	//	benchmark_.stop_timer();
	//	benchmark_.output_time_elapsed("nullify_spurs");
	//	benchmark_.start_timer();
	//}

	// Find primary syncs. ///////////////////
	psch_cross_correlator_.set_num_coherent_windows(num_coherent_psch_slots_);

	psch_cross_correlator_.set_iteration_length(num_samples_per_time_slot_);

	psch_cross_correlator_.set_input_signal_and_configure_parameters(
		signal, 
		length_to_process_,
		psch_template_.length());

	psch_cross_correlator_.calculate_average_power();

	psch_cross_correlator_.do_cross_correlation_and_additions(psch_template_.get());

	Ipp32f min_psch_ecio_watts = (Ipp32f)umts_utilities::calculate_correlation_ecio_watts_threshold(
		psch_confidence_threshold_, 
		(double)psch_cross_correlator_.num_coherent_windows(), 
		(double)psch_cross_correlator_.num_iterations(), 
		(double)psch_cross_correlator_.moving_window_length() / over_sampling_rate_);

	std::list<int> psch_peaks;

	ipp_32f_array &psch_correlation_result(psch_cross_correlator_.get_result());

	int length = psch_correlation_result.length() - 1;

	int size = 0;
	for(int i = 1; i < length; i++)
	{
		// Relative peak.
		Ipp32f possible_peak = psch_correlation_result.get_value(i);
		if(possible_peak > min_psch_ecio_watts && (
					possible_peak > psch_correlation_result.get_value(i - 1) &&
					possible_peak > psch_correlation_result.get_value(i + 1) ))
		{
			// If there are these many peaks there is probably something wrong.
			if(++size > 100)
				break;
			psch_peaks.push_back(i);
		}
	}

#ifdef USE_PSCH_BRUTE_FORCE_BENCHMARK 	
	if(do_we_benchmark_)
	{
		benchmark_.stop_timer();
		benchmark_.output_time_elapsed("psch_correlations");
		benchmark_.start_timer();
	}
#endif

	int total_num_peaks = psch_peaks.size();

	if(psch_peaks.size() > max_num_psch_peaks_)
	{
		sort_peaks_ascending sort_ascending(psch_correlation_result);

		psch_peaks.sort(sort_ascending);

		int num_to_remove = psch_peaks.size() - max_num_psch_peaks_;
		
		for(int i = 0; i < num_to_remove; i++)
			psch_peaks.erase(psch_peaks.begin());
	}

	calculate_peak_adjustment();

#ifdef USE_PSCH_BRUTE_FORCE_BENCHMARK 	
	if(do_we_benchmark_)
	{
		benchmark_.stop_timer();
		benchmark_.output_time_elapsed(std::string("remove_psch_peaks\ttotal_num_peaks\t").append(boost::lexical_cast<std::string>(total_num_peaks)));
		benchmark_.start_timer();
	}
#endif

	//  Find cpichs.

	int32_t samples_per_correlation_segment = (int32_t)boost::math::round(num_cpich_chips * over_sampling_rate_);
	int32_t pertinent_signal_length = samples_per_correlation_segment < num_samples_per_time_slot_ 
		? num_samples_per_time_slot_ * 2 + 1 
		: samples_per_correlation_segment * 2 + 1 ;
	pertinent_signal_length += psch_peak_adjustment_;

	cpich_cross_correlator_.set_num_coherent_windows(1);
	cpich_cross_correlator_.set_iteration_length(1);
	cpich_cross_correlator_.set_num_iterations(1);
	cpich_cross_correlator_.set_input_signal_and_configure_parameters(
		signal, 
		pertinent_signal_length, 
		samples_per_correlation_segment,
		psch_peak_adjustment_);

	cpich_cross_correlator_.calculate_average_power();

	min_cpich_ecio_watts_ = (Ipp32f)umts_utilities::calculate_correlation_ecio_watts_threshold(
		cpich_confidence_threshold_, 
		(double)cpich_cross_correlator_.num_coherent_windows(), 
		(double)cpich_cross_correlator_.num_iterations(), 
		(double)cpich_cross_correlator_.moving_window_length() / over_sampling_rate_);

	cpich_wrap_around_.reset(num_samples_per_cpich_);

#ifdef USE_PSCH_BRUTE_FORCE_BENCHMARK 	
	if(do_we_benchmark_)
	{
		benchmark_.stop_timer();
		benchmark_.output_time_elapsed(std::string("cpich_correlation_setup"));
		benchmark_.start_timer();
	}
#endif

	umts_measurements new_measurements;

	if(scanning_method == full_scan_type)
	{
		for(auto peak_position_it = psch_peaks.begin(); peak_position_it != psch_peaks.end(); peak_position_it++)
		{
			for(int i = 0; i < 512; i++)
			{	
				if(cancel_processing_ || new_measurements.size() >= max_num_candidates_)
					break;
	
				for(int j = 0; j < 15; j++)
					do_cpich_correlation_and_add_candidate(i, j, *peak_position_it, new_measurements);
			
				if(i % 15 == 0)
					pause_if_necessary();
			}
		}
	}
	else
	{
		for(auto peak_position_it = psch_peaks.begin(); peak_position_it != psch_peaks.end(); peak_position_it++)
		{
			std::list<std::pair<uint32_t, uint32_t> > cpich_timeslot_group;

			if(scanning_method == candidate_all_timeslots_scan_type)
			{
				for(auto it = tracking_measurements.begin(); it != tracking_measurements.end(); it++)
				{
					for(int j = 0; j < 15; j++)
						cpich_timeslot_group.push_back(std::make_pair(it->cpich_, j));
				}
			}	
			else
				determine_cpich_and_timeslot(cpich_timeslot_group, *peak_position_it, tracking_measurements);

			for(auto it = cpich_timeslot_group.begin(); it != cpich_timeslot_group.end(); it++)
				do_cpich_correlation_and_add_candidate(it->first, it->second, *peak_position_it, new_measurements);
		}
	}

#ifdef USE_PSCH_BRUTE_FORCE_BENCHMARK 	
	if(do_we_benchmark_)
	{
		benchmark_.stop_timer();
		benchmark_.output_time_elapsed(std::string("found_cells\t").append(boost::lexical_cast<std::string>(new_measurements.size())));
		benchmark_.output_total_time_elapsed(std::string("total_time_elapsed\t").append("----------------------------------------------"));
	}
#endif

	return new_measurements;
}

void umts_psch_with_brute_force::adjust_clock_error_rate()
{
	clock_rate_ /*= process_config_->clock_rate()*/;
	sample_rate_ /*= process_config_->sample_rate()*/;
	over_sampling_rate_ /*= process_config_->over_sampling_rate()*/;

	//if(frequency_correction::do_we_apply_frequency_correction(packet.getLastDeltaTime(), packet.getLongCounterLatched()))
	//{
	//	frequency_correction::adjust_for_error(clock_rate_);
	//	frequency_correction::adjust_for_error(sample_rate_);
	//}
}

void umts_psch_with_brute_force::calculate_peak_adjustment()
{
	total_psch_correlation_length_ = psch_cross_correlator_.iteration_length() * psch_cross_correlator_.num_coherent_windows() * psch_cross_correlator_.num_iterations();

	psch_peak_adjustment_ = total_psch_correlation_length_ / 2;
}

void umts_psch_with_brute_force::determine_cpich_and_timeslot(std::list<std::pair<uint32_t, uint32_t> > &cpich_timeslot_group, uint32_t peak_position, const umts_measurements &tracking_measurements)
{
	cpich_timeslot_group.clear();
					
	int64_t frame_starts_uframes = static_cast<int64_t>(((double)(peak_position + psch_peak_adjustment_) / sample_rate_) * 1e8);

	int64_t absolute_frame_starts_uframes = time_of_packet_uframes_ + frame_starts_uframes;
		
	for(auto it = tracking_measurements.begin(); it != tracking_measurements.end(); it++)
	{				
		int64_t uframes_diff = absolute_frame_starts_uframes - it->time_;
		
		double frames_diff = uframes_diff / 1e6;

		double num_chips_into_frame = (frames_diff - std::floor(frames_diff)) * N_TOTAL_CHIPS_CPICH;

		double num_chips_into_timeslot = std::fmod(num_chips_into_frame, N_CHIPS_PER_TIMESLOT);
		
		double num_chips_from_next_timeslot = N_CHIPS_PER_TIMESLOT - num_chips_into_timeslot;

		double chips_to_closest_timeslot;
		double timeslot;

 		if(num_chips_into_timeslot < num_chips_from_next_timeslot)
		{
			chips_to_closest_timeslot = num_chips_into_timeslot;
			timeslot = num_chips_into_frame / N_CHIPS_PER_TIMESLOT;
		}
		else
		{
			chips_to_closest_timeslot = num_chips_from_next_timeslot;
			timeslot = num_chips_into_frame / N_CHIPS_PER_TIMESLOT + 1;		
		}

		if(timeslot >= 15)
			timeslot = 0;

		if(chips_to_closest_timeslot < 10)
			cpich_timeslot_group.push_back(std::make_pair(it->cpich_, (uint32_t)boost::math::round(timeslot)));
	}
}

void umts_psch_with_brute_force::do_cpich_correlation_and_add_candidate(uint32_t cpich, uint32_t timeslot, uint32_t peak_position, umts_measurements &new_measurements)
{
	int32_t samples_per_correlation_segment = cpich_cross_correlator_.moving_window_length();

	int current_cpich_pos = cpich * num_samples_per_cpich_;
	int current_slot_pos = timeslot * num_samples_per_time_slot_;
	int abs_pos = current_cpich_pos + current_slot_pos;

	// This assumes our source template is bigger than our correlation length and
	// we would never have to wrap more than once.
	int samples_at_the_beginning = current_slot_pos - peak_position;

	int samples_at_the_end = num_samples_per_cpich_ - (current_slot_pos + peak_position);
				
	// align cpich template remember than it can be any timeslot does not have to be first time slot
	if(samples_at_the_beginning < 0)
	{
		int position_to_split = num_samples_per_cpich_ - peak_position;

		int copy_samples_1 = num_samples_per_cpich_ - position_to_split;
		if(copy_samples_1 > samples_per_correlation_segment)
			copy_samples_1 = samples_per_correlation_segment;

		memcpy(cpich_wrap_around_.get(), 
			&resampled_cpich_table_[current_cpich_pos + position_to_split], 
			copy_samples_1 * sizeof(Ipp32fc));

		int copy_samples_2 = samples_per_correlation_segment - copy_samples_1;

		memcpy(cpich_wrap_around_.get(num_samples_per_cpich_ - position_to_split), 
			&resampled_cpich_table_[current_cpich_pos], 
			copy_samples_2 * sizeof(Ipp32fc));

		cpich_cross_correlator_.do_cross_correlation_and_additions(cpich_wrap_around_.get());
	}
	else if(samples_at_the_end <  samples_per_correlation_segment)
	{
		int position_to_split = current_slot_pos - peak_position;

		int copy_samples_1 = num_samples_per_cpich_ - position_to_split;
		if(copy_samples_1 > samples_per_correlation_segment)
			copy_samples_1 = samples_per_correlation_segment;

		memcpy(cpich_wrap_around_.get(), 
			&resampled_cpich_table_[current_cpich_pos + position_to_split], 
			copy_samples_1 * sizeof(Ipp32fc));

		int copy_samples_2 = samples_per_correlation_segment - copy_samples_1;

		memcpy(cpich_wrap_around_.get(num_samples_per_cpich_ - position_to_split), 
			&resampled_cpich_table_[current_cpich_pos], 
			copy_samples_2 * sizeof(Ipp32fc));

		cpich_cross_correlator_.do_cross_correlation_and_additions(cpich_wrap_around_.get());
	}
	else
	{			
		cpich_cross_correlator_.do_cross_correlation_and_additions(&resampled_cpich_table_[abs_pos - peak_position]);
	}

	Ipp32f cpich_ecio_watts = *cpich_cross_correlator_.get_result().get();

	if(cpich_ecio_watts > min_cpich_ecio_watts_)
	{
 		int64_t frame_starts_samples = current_slot_pos == 0 ? (int64_t)peak_position - num_samples_per_cpich_ : ((int64_t)peak_position - current_slot_pos);

		frame_starts_samples += psch_peak_adjustment_;

		int64_t frame_starts_uframes = static_cast<int64_t>(((double)frame_starts_samples / sample_rate_) * 1e8);
					
		int64_t absolute_frame_starts_uframes = time_of_packet_uframes_ + frame_starts_uframes;
				
		int64_t frames_starts_relative_to_packet_start = frame_starts_samples < 0 ? frame_starts_samples + num_samples_per_cpich_ : frame_starts_samples;
					
		// Mod so we have frame that starts closest to the beginning of the packet.  This allows layer 3 decoder to use the entire packet for processing.
		frames_starts_relative_to_packet_start %= num_samples_per_cpich_;

		umts_measurement meas;
		meas.cpich_ = cpich;
		meas.sample_num_ = (int)frames_starts_relative_to_packet_start;
		meas.ecio_ = 20 * log10(cpich_ecio_watts);
		meas.norm_corr_ = cpich_ecio_watts;
		meas.rms_signal_ = cpich_cross_correlator_.get_rms(peak_position);
		new_measurements.push_back(meas);
	}
}
