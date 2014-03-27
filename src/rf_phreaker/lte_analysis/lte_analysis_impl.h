#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/lte_analysis/lte_config.h"
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/common_utility.h"
#include <map>
#include <mutex>

#define LTE_ANALYSIS_IF_STEPSIZE_KHZ			100
#define LTE_ANALYSIS_PSS_SEARCH_MAX_IF_KHZ		1500
#define LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF		(((2*LTE_ANALYSIS_PSS_SEARCH_MAX_IF_KHZ)/LTE_ANALYSIS_IF_STEPSIZE_KHZ) + 1)

int lte_cell_search(const Ipp32fc* SignalSamples,
					unsigned int NumSamples,
					unsigned int NumHalfFramesToProcess,
					lte_measurements &LteData, int &tmp_num_meas);

int lte_decode_data(const Ipp32fc* SignalSamples,
					unsigned int NumSamples,
					unsigned int NumHalfFramesToProcess,
					lte_measurements &LteData);

class lte_analysis_impl
{
public:
	lte_analysis_impl(const lte_config &config);

	~lte_analysis_impl();

	int cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames);

	int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas, int num_half_frames);

	//void set_config(const lte_config &config);

	lte_config get_lte_config() const { return config_; }

private:
	rf_phreaker::frequency_type determine_sampling_rate(const rf_phreaker::raw_signal &raw_signal, lte_measurements &lte_meas);

	rf_phreaker::fir_filter& get_filter_and_set_resampled_length(rf_phreaker::frequency_type input_sampling_rate, rf_phreaker::frequency_type output_sampling_rate, int num_input_samples);

	static const int num_measurements = 100;

	lte_measurements lte_measurements_;

	struct sampling_rates {
		sampling_rates() : input_sampling_rate_(0), output_sampling_rate_(0) {}
		sampling_rates(rf_phreaker::frequency_type i, rf_phreaker::frequency_type o) : input_sampling_rate_(i), output_sampling_rate_(o) {}
		sampling_rates(const sampling_rates &a) : input_sampling_rate_(a.input_sampling_rate_), output_sampling_rate_(a.output_sampling_rate_) {}
		rf_phreaker::frequency_type input_sampling_rate_;
		rf_phreaker::frequency_type output_sampling_rate_;
		bool operator()(const sampling_rates &a, const sampling_rates &b) {
			if(a.input_sampling_rate_ == b.input_sampling_rate_)
				return a.output_sampling_rate_ < b.output_sampling_rate_;
			else
				return a.input_sampling_rate_ < b.input_sampling_rate_;
		}
	};
	std::map<sampling_rates, std::shared_ptr<rf_phreaker::fir_filter>, sampling_rates> filters_;

	ipp_32fc_array resampled_signal_;

	int resampled_length_;

	lte_config config_;

	const static rf_phreaker::frequency_type cell_search_sampling_rate_ = khz(1920);

	// This is necessary until the lte cell search and decode are multithreaded.
	static std::mutex processing_mutex;
};

