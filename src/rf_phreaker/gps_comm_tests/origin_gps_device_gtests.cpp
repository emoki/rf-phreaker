#include "gtest/gtest.h"
#include <memory>
#include <thread>
#include "libbladeRF.h"
#include "rf_phreaker/gps_comm/OriginGPSDevice.h"


using namespace rf_phreaker::gps_comm;

TEST(OriginGpsDevice, TestGeneral) {
	bladerf *device;
	
	// Open first available device.
	EXPECT_EQ(0, bladerf_open(&device, nullptr));

	// Make sure there is a GPS compatible fpga load within the working dir.
	EXPECT_EQ(0, bladerf_load_fpga(device, "fpga_load.rbf"));

	std::unique_ptr<BladeDevice> blade_device_;
	std::unique_ptr<FrontEndBoard> front_end_board_;
	std::unique_ptr<OriginGPSDevice> origin_gps_device_;

	blade_device_.reset(new BladeDevice(device));
	front_end_board_.reset(new FrontEndBoard(*blade_device_));
	origin_gps_device_.reset(new OriginGPSDevice(*front_end_board_));

	origin_gps_device_->setInterface(OriginGPSDevice::UART);

	origin_gps_device_->service.parser.log = true;

	std::cout << "Wakeup = " << std::boolalpha << origin_gps_device_->getWakeup() << std::endl;

	origin_gps_device_->setPower();
	
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "Wakeup = " << std::boolalpha << origin_gps_device_->getWakeup() << std::endl;

	for(int i = 0; i < 60 * 60; ++i) {
		origin_gps_device_->update();
		//std::cout << origin_gps_device_->getFix().toString() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

}