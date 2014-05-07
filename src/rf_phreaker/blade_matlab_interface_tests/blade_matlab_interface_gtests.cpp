#include "gtest/gtest.h"

#include "rf_phreaker/blade_matlab_interface/blade_matlab_interface.h"
#include "rf_phreaker/blade_matlab_interface/matlab_interface_helper.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/ipp_array.h"
#include <string>

using namespace rf_phreaker;
using namespace rf_phreaker::matlab_interface;

TEST(BladeMatlabInterface, TestMain)
{
	const int buf_size = 33 * 10;
	char devices[buf_size];
	int num_devices;

	EXPECT_EQ(0, start_logging(0));

	EXPECT_EQ(0, num_blade_devices_connected(&num_devices));

	EXPECT_EQ(0, list_blade_devices((int8_t*)devices, buf_size));

	std::string serial(devices);
	serial = serial.substr(0, serial.find(';'));
	int status = open_blade_device(serial.c_str());

	EXPECT_EQ(0, status);

	if(status == 0) {

		EXPECT_EQ(0, close_blade_device());

		EXPECT_EQ(0, open_first_blade_device());

		char device[buf_size];
		int usb_speed;
		EXPECT_EQ(0, get_connected_device_info((int8_t*)device, buf_size, &usb_speed));

		int num_samples = 100000;
		ipp_32fc_array iq_data(num_samples);
		float sl = 0;

		for(int i = 0; i < 100; ++i) {
			EXPECT_EQ(0, get_rf_data(mhz(886), mhz(5), khz(30720), 3, 30, 0, (float*)iq_data.get(), iq_data.length(), &sl));

			EXPECT_EQ(0, only_get_rf_data((float*)iq_data.get(), iq_data.length(), &sl));

			EXPECT_EQ(0, get_rf_data(mhz(900), mhz(5), khz(30720), 3, 30, 0, (float*)iq_data.get(), iq_data.length(), 0));

			EXPECT_EQ(0, only_get_rf_data((float*)iq_data.get(), iq_data.length(), 0));
		}
		int lms_add = 0x23;
		int lms_value = 0;
		EXPECT_EQ(0, read_lms_reg(lms_add, &lms_value));
		EXPECT_EQ(0, set_lms_reg(lms_add, lms_value));


		int trim = 0;
		EXPECT_EQ(0, read_vctcxo_trim(&trim));

		//int tmp_trim = trim - 100;
		//EXPECT_EQ(0, set_vctcxo_trim(tmp_trim));

		//EXPECT_EQ(0, read_vctcxo_trim(&tmp_trim));
		//EXPECT_EQ(0, set_vctcxo_trim(trim));

		uint32_t gpio = 0;
		EXPECT_EQ(0, read_gpio(&gpio));

		EXPECT_EQ(0, set_gpio(gpio));

		EXPECT_EQ(matlab_interface_error_null_detected, read_gpio(0));

		char error[buf_size];
		EXPECT_EQ(0, get_last_error((int8_t*)error, buf_size));
		EXPECT_EQ(0, get_last_error((int8_t*)error, buf_size));

	}

}
