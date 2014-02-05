#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "rf_phreaker/common/ipp_array.h"

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
	lte_analysis_impl();

	~lte_analysis_impl();

	int cell_search(const rf_phreaker::raw_signal &raw_signal, lte_measurement *lte_meas, int &num_lte_meas, int num_half_frames);

	int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, lte_measurement *lte_meas, int num_lte_meas, int num_half_frames);

	//void set_config(const lte_config &config);

private:
	static const int num_measurements = 200;

	lte_measurements lte_measurements_;

	rf_phreaker::fir_filter filter_;

	ipp_32fc_array resampled_signal_;
};

