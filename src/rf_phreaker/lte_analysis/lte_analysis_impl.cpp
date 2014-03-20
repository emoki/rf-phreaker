#include "rf_phreaker/lte_analysis/lte_analysis_impl.h"

lte_analysis_impl::lte_analysis_impl()
: lte_measurements_(num_measurements)
{
	filter_.set_taps(6501);
}

lte_analysis_impl::~lte_analysis_impl()
{}

int lte_analysis_impl::cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurement *lte_meas, int &num_lte_meas, int num_half_frames)
{
	int status = 0;

	try {
		int tmp_num_meas = 0;

		filter_.set_up_down_factor_based_on_sampling_rates(raw_signal.sampling_rate(), 3840000);
		filter_.set_taps(6501);
		resampled_signal_.reset(filter_.num_output_samples_required(raw_signal.get_iq().length()));
		filter_.filter(raw_signal.get_iq().get(), resampled_signal_.get(), filter_.num_iterations_required(raw_signal.get_iq().length()));
		
		status = lte_cell_search(resampled_signal_.get(), resampled_signal_.length(), num_half_frames, lte_measurements_, tmp_num_meas);

		//status = lte_cell_search(raw_signal.get_iq().get(), raw_signal.get_iq().length(), num_half_frames, lte_measurements_, tmp_num_meas);

		for(int i = 0; i < tmp_num_meas; ++i) {
			if(i >= num_lte_meas) {
				status = -1;
				break;
			}
			lte_meas[i] = lte_measurements_[i];
		}
		
		num_lte_meas = tmp_num_meas;
	}
	catch(const std::exception &err) {
		// Log error.
		std::cout << err.what() << std::endl;
		status = -2;
	}

	return status;
}


int lte_analysis_impl::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurement *lte_meas, int num_lte_meas, int num_half_frames)
{
	int status = 0;

	try {
		status = lte_decode_data(raw_signal.get_iq().get(), raw_signal.get_iq().length(), num_half_frames, lte_measurements_);
	}
	catch(const std::exception &err) {
		// Log error.
		std::cout << err.what() << std::endl;
		status = -2;
	}

	return status;
}
