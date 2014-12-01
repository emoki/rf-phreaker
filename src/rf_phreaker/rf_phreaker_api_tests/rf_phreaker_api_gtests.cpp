#include "gtest/gtest.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api_tests/output.h"

TEST(RfPhreakerApi, GeneralTest) {
	api_output output;

	auto status = rp_initialize(&output.cbs_);

	rp_serial serial[10];
	int num_serials = 10;
	status = rp_list_devices(serial, &num_serials);

	if(num_serials > 0) {
		rp_device *d1;
		rp_device *d2;
		status = rp_connect_device(serial[0], &d1);
		status = rp_connect_device(serial[0], &d2);

		status = rp_disconnect_device(d1);
		status = rp_disconnect_device(d2);

	}

	status = rp_clean_up();
}