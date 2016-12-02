#include "gtest/gtest.h"
#include <thread>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api_tests/output.h"

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
		std::vector<rp_frequency_type> raw_data;
		sweep.push_back(UMTS_OPERATING_BAND_4);
		sweep.push_back(UMTS_OPERATING_BAND_2);
		sweep.push_back(LTE_OPERATING_BAND_1);
		sweep.push_back(LTE_OPERATING_BAND_2);
		sweep.push_back(LTE_OPERATING_BAND_12);
		
		rp_collection_info info;
		info.sweep_.e_ = sweep.data();
		info.sweep_.size_ = sweep.size();
		info.gsm_.e_ = gsm.data();
		info.gsm_.size_ = gsm.size();
		info.wcdma_.e_ = umts.data();
		info.wcdma_.size_ = umts.size();
		info.lte_.e_ = lte.data();
		info.lte_.size_ = lte.size();
		info.raw_data_.e_ = raw_data.data();
		info.raw_data_.size_ = raw_data.size();

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