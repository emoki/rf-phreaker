#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/processing/lte_data_container.h"
#include "rf_phreaker/lte_analysis/lte_analysis.h"


namespace rf_phreaker { namespace processing {


typedef std::tuple<rf_phreaker::scanner::measurement_info, lte_data_container> lte_package;

class basic_processing_lte
{
public:
	basic_processing_lte()
		: wind_lte_data_(lte_measurements_, num_measurements)
	{}

	lte_package operator()(rf_phreaker::scanner::measurement_info meas_info)
	{
		//auto status = lte_cell_search(meas_info.get_iq().get(), meas_info.get_iq().length(), meas_info.time_ms() / 5, 
		//	data_sampling_rate_3840, wind_lte_data_);

		lte_data_container container;

		for(unsigned int i = 0; i < wind_lte_data_.NumMeasurements; ++i)
			container.add(wind_lte_data_.Measurements[i], meas_info);

        return std::make_tuple(std::move(meas_info), std::move(container));
	}
	
private:
	static const int num_measurements = 200;
	LteMeasurement lte_measurements_[num_measurements];
	WindLteData wind_lte_data_;
};

}}
