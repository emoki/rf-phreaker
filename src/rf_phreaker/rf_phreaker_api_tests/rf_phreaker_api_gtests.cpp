#include "gtest/gtest.h"
#include <thread>
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api_tests/output.h"

using namespace rf_phreaker;

TEST(RfPhreakerApi, IqTest) {
	rp_clean_up();

	api_output output;

	auto status = rp_initialize(&output.cbs_);

	rp_serial serial[10];
	int num_serials = 10;
	status = rp_list_devices(serial, &num_serials);

	if(num_serials > 0) {
		rp_device *d1;
		status = rp_connect_device(serial[0], &d1);

		frequency_type sampling_rate = mhz(10);
		time_type dwell_time = milli_to_nano(60);
		std::vector<float> samples(convert_to_samples(dwell_time, sampling_rate) * 2);
		std::vector<double> power(10000);
		rp_iq_data iq;
		iq.samples_ = samples.data();
		iq.num_samples_ = samples.size();
		iq.power_adjustment_.power_ = power.data();
		iq.power_adjustment_.num_power_ = power.size();

		rp_get_iq_data(d1, mhz(1930), dwell_time, mhz(5), mhz(10), 65, &iq);
	}

	rp_clean_up();
}

TEST(RfPhreakerApi, GeneralTest) {

	rp_clean_up();

	api_output output;

	auto status = rp_initialize(&output.cbs_);

	rp_serial serial[10];
	int num_serials = 10;
	status = rp_list_devices(serial, &num_serials);

	if(num_serials > 0) {
		rp_device *d1;
		rp_device *d2;
		status = rp_connect_device(serial[0], &d1);
		//status = rp_connect_device(serial[0], &d2);

		std::vector<rp_operating_band> sweep;
		std::vector<rp_frequency_band> gsm;
		std::vector<rp_frequency_band> umts;
		std::vector<rp_frequency_band> lte;
		std::vector<rp_power_spectrum_spec> spec;
		std::vector<rp_iq_data_spec> iq;
		sweep.push_back(rp_operating_band::UMTS_OPERATING_BAND_4);
		sweep.push_back(rp_operating_band::UMTS_OPERATING_BAND_2);
		sweep.push_back(rp_operating_band::LTE_OPERATING_BAND_1);
		sweep.push_back(rp_operating_band::LTE_OPERATING_BAND_2);
		sweep.push_back(rp_operating_band::LTE_OPERATING_BAND_12);
		
		spec.push_back(rp_power_spectrum_spec{ mhz(1930), mhz(25), khz(2), milli_to_nano(30) });
		spec.push_back(rp_power_spectrum_spec{ mhz(2110), mhz(40), khz(2), milli_to_nano(30) });

		iq.push_back(rp_iq_data_spec{ mhz(875), mhz(5), mhz(10), milli_to_nano(20) });
		iq.push_back(rp_iq_data_spec{mhz(750), mhz(2), mhz(4), milli_to_nano(20)});

		rp_collection_info info;
		info.sweep_.e_ = sweep.data();
		info.sweep_.size_ = sweep.size();
		info.gsm_.e_ = gsm.data();
		info.gsm_.size_ = gsm.size();
		info.wcdma_.e_ = umts.data();
		info.wcdma_.size_ = umts.size();
		info.lte_.e_ = lte.data();
		info.lte_.size_ = lte.size();
		info.iq_data_.e_ = iq.data();
		info.iq_data_.size_ = iq.size();
		info.power_spectrum_spec_.e_ = spec.data();
		info.power_spectrum_spec_.size_ = spec.size();

		rp_start_collection(d1, &info);

		api_helper::instance().wait(std::chrono::minutes(60));

		if(api_helper::instance().error_has_occurred()) {
			auto status = rp_initialize(&output.cbs_);
			status = rp_connect_device(serial[0], &d1);
			rp_start_collection(d1, &info);
			api_helper::instance().wait(std::chrono::minutes(60));
		}


		rp_stop_collection(d1);

		status = rp_disconnect_device(d1);
		//status = rp_disconnect_device(d2);

	}

	status = rp_clean_up();
}

