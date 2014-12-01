#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include "libbladeRF.h"
#include "rf_phreaker/gps_comm/GPSDevice.h"


using namespace rf_phreaker::gps_comm;

TEST(FPGAReliability, DISABLED_TestGeneral) {

	bladerf *device;
	std::unique_ptr<BladeDevice> blade_device_;
	std::unique_ptr<FrontEndBoard> front_end_board_;
	std::unique_ptr<GPSDevice> origin_gps_device_;
	int sts;


	// Open first available device.
	bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
	sts = bladerf_open(&device, nullptr);
	if (sts != 0){
		std::cout << "==== DEVICE FAILED! ====  :  " << bladerf_strerror(sts) << std::endl;
	}
	EXPECT_EQ(0, sts);



	std::cout << " Loading FPGA... " << std::endl;
	sts = bladerf_load_fpga(device, "fpga_load-fw.rbf");

	if (sts != 0){
		std::cout << "==== FPGA LOAD FAILED! ====  " << bladerf_strerror(sts) << std::endl;
	}
	EXPECT_EQ(0, sts);


	// Repeated FPGA Load - Note: The load issue is caused by the same issue that causes timeouts for the nios with UART. Should be fixed now...

	int loads = 10;
	int load_fails = 0;
	std::cout << "-------------------------------------------------------------" << std::endl;
	std::cout << " Loading FPGA " << loads << " times for reliability test... " << std::endl;
	for (int i = 0; i < loads; i++){
		// Make sure there is a GPS compatible fpga load within the working dir.

		sts = bladerf_load_fpga(device, "fpga_load-fw.rbf");

		if (sts != 0){
			std::cout << "==== FPGA LOAD FAILED! ====  : Try #" << i << " :: "  << bladerf_strerror(sts) << std::endl;
			load_fails++;
		}
	}
	
	EXPECT_EQ(0, load_fails);


	std::cout << " FPGA OK !" << std::endl;


	// -- LMS Speed Read Test
	std::cout << "-------------------------------------------------------------" << std::endl;
	std::cout << "LMS REGISTER SPEED READ TEST..." << std::endl;
	uint8_t addr = 0x9;
	uint8_t val = 0;
	clock_t begin = clock();
	for (int i = 0; i < 10000; i++){
	bladerf_lms_read(device, addr, &val);
	}
	double tt = (clock() - begin) / (float)(CLOCKS_PER_SEC);
	double rate = 10000 / tt;
	std::cout << "LMS Rate: " << rate << " b/s" << std::endl;

	EXPECT_TRUE( rate > 100 );






	blade_device_.reset(new BladeDevice(device));
	front_end_board_.reset(new FrontEndBoard(*blade_device_));
	origin_gps_device_.reset(new GPSDevice(*front_end_board_));

	origin_gps_device_->reset();



	// -- POWER CYCLE TEST - should be placed in seperate test later...

	std::cout << "-------------------------------------------------------------" << std::endl;
	std::cout << "GPS POWER CYCLE TEST..." << std::endl;
	int num_wrong_states = 0;
	for (int i = 0; i < 10; i++){
		try{
			bool state = (bool)(i % 2 == 0);
			std::cout << "  >> GPS POWER: " << (state ? "ON" : "OFF") << "  -> ";
			origin_gps_device_->setPower(state);
			std::cout << (origin_gps_device_->awake() == state ? "good" : "bad");
			if (origin_gps_device_->awake() != state){
				num_wrong_states++;
			}
		}
		catch (GPSDeviceError& e){
			std::cout << "[!] unresponsive";
		}
		std::cout << std::endl;
	}

	EXPECT_EQ(0, num_wrong_states);
	
}