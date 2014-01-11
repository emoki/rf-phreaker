#include "measurement_info.h"
#include "das_format.h"
#include "recorder_to_das_converter.h"
#include "fir_filter.h"
#include <vector>
#include <memory>

typedef std::tuple<measurement_info, std::vector</*das::*/das1>> das_package;

class process_das
{
public:
	process_das() : resampling_filter_("resample_7.68_4.875.txt") {
		das_initialize();
	}

	~process_das() {
		das_cleanup();
	}

	long process_recorder(const /*das::*/recorder &recorder, const /*das::*/gps &gps, /*das::*/das1 *das_measurments, uint32_t &num_das_measurements) {
		return das_process_recorder(recorder, gps, das_measurments, num_das_measurements);
	}

	const char* get_last_error() {
		return das_get_last_error_description();
	}

	resampling_filter& get_resampling_filter() { return resampling_filter_; }

	static process_das& get() {
		if(process_das_.get() == nullptr)
		{
			process_das_.reset(new process_das);
		}

		return *process_das_;
	}

private:
	static std::unique_ptr<process_das> process_das_;

	resampling_filter resampling_filter_;
};

class basic_processing_das
{
public:
	das_package operator()(measurement_info meas_info)
	{
		ipp_32fc_array resampled_data(meas_info.get_iq().length() * 325 / 512);

		int num_output_filtered_samples = 0;
		
		//meas_info.get_iq().debug_output("orig_signal.txt");

		process_das::get().get_resampling_filter().filter(meas_info.get_iq().get(), meas_info.get_iq().length(), resampled_data.get(), resampled_data.length(), num_output_filtered_samples);

		//resampled_data.debug_output("signal_resamp.txt");

		// remove DC
		Ipp32fc mean;
		ippsMean_32fc(resampled_data.get(),resampled_data.length(), &mean, IppHintAlgorithm::ippAlgHintAccurate);
		ippsSubC_32fc_I(mean, resampled_data.get(), resampled_data.length());

		//resampled_data.debug_output("signal_resamp_dc_removed.txt");



		uint32_t return_das = 100;
		
		std::vector</*das::*/das1> das_meas(100);

		/*das::*/recorder recorder; 
		ipp_16sc_array tmp_array(num_output_filtered_samples);
		for(int i = 0; i < num_output_filtered_samples; ++i) {
			tmp_array[i].re = (Ipp16s)resampled_data[i].re;
			tmp_array[i].im = (Ipp16s)resampled_data[i].im;
		}			
		recorder.number_iq_samples_ = tmp_array.length();
		recorder.iq_samples_ = reinterpret_cast</*das::*/iq_sample*>(&tmp_array[0]);
		recorder.calibration_adjustment_ = 1;
		recorder.carrier_bandwidth_ = meas_info.bandwidth();
		recorder.carrier_frequency_ = (/*das::*/das_frequency_type)meas_info.frequency();
		recorder.sample_rate_ = 4875000;
		recorder.nanoseconds_since_start_of_day_ = 0;


		/*das::*/gps gps;
		gps.coordinated_universal_time_ = 100;

		auto status = process_das::get().process_recorder(recorder, gps, &das_meas[0], return_das);
			
		std::vector<das1> output;
		
		if(status)
			std::cout << process_das::get().get_last_error();
		else {	
			for(uint32_t i = 0; i < return_das; ++i)
				output.push_back(das_meas[i]);
		}

		return std::make_tuple(std::move(meas_info), std::move(output));
	}
};