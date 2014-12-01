#include "gtest/gtest.h"
#include <vector>
#include <thread>
#include <memory>
#include <fstream>
#include "boost/serialization/vector.hpp"
#include "boost/archive/basic_text_oarchive.hpp"
#include "boost/archive/basic_text_iarchive.hpp"
#include "libbladeRF.h"
#include "rf_phreaker/gps_comm/BladeDevice.h"
#include "rf_phreaker/gps_comm_tests/eeprom.h"
#include "rf_phreaker/gps_comm/gps_comm.h"


using namespace rf_phreaker::gps_comm;

inline std::ostream& operator<<(std::ostream &os, const rf_phreaker::gps &t) {
	os << t.serial_ << "\t"
		<< (t.lock_ ? "TRUE" : "FALSE") << "\t"
		<< t.coordinated_universal_time_ << "\t"
		<< t.visible_satellites_ << "\t"
		<< t.tracking_satellites_ << "\t"
		<< t.latitude_ << "\t"
		<< t.longitude_ << "\t"
		<< t.speed_ << "\t"
		<< std::setw(4) << std::setfill('0') << std::hex << t.raw_status_ << std::dec;
	return os;
}

TEST(ReadWriteEEPROM, DISABLED_TestGeneral) {

	bladerf *device;
	std::unique_ptr<BladeDevice> blade_device_;
	int sts;


	// Open first available device.
	bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
	sts = bladerf_open(&device, nullptr);
	if(sts != 0) {
		std::cout << "==== DEVICE FAILED! ====  :  " << bladerf_strerror(sts) << std::endl;
	}
	EXPECT_EQ(0, sts);
	ASSERT_TRUE(device != 0);

	blade_device_.reset(new BladeDevice(device));

	std::cout << " Loading FPGA... " << std::endl;
	sts = bladerf_load_fpga(device, "fpga_load.rbf");

	if(sts != 0) {
		std::cout << "==== FPGA LOAD FAILED! ====  " << bladerf_strerror(sts) << std::endl;
	}
	EXPECT_EQ(0, sts);

	int retry = 0;
	for(int i = 0; i < 5; ++i) {
		try {
			int status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (bladerf_calibrate_dc(device,
					BLADERF_DC_CAL_LPF_TUNING));
				if(status == 0) break;
			}
			if(status)
				throw std::runtime_error("Calibration failed: LPF Tuning Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (bladerf_calibrate_dc(device,
					BLADERF_DC_CAL_RX_LPF));
				if(status == 0) break;
			}
			if(status)
				throw std::runtime_error("Calibration failed: DC RX LPT Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (bladerf_calibrate_dc(device,
					BLADERF_DC_CAL_RXVGA2));
				if(status == 0) break;
			}
			if(status)
				throw std::runtime_error("Calibration failed: DC RXVGA2 Module.");

			status = (bladerf_set_lpf_mode(device, BLADERF_MODULE_RX,
				BLADERF_LPF_NORMAL), __FILE__, __LINE__);

			break;
		}
		catch(std::exception &err) {
			std::cout << err.what() << "  Attempting to recover...";

			bladerf_close(device);

			for(int i = 0; i < 3; ++i) {
				std::this_thread::sleep_for(std::chrono::seconds(3));
				sts = bladerf_open(&device, nullptr);
				std::this_thread::sleep_for(std::chrono::seconds(1));
				if(sts == 0) break;
			}
		}
	}

	bool use_spi = false;
	gps_comm tmp_gps;
	tmp_gps.init(device, use_spi);

	std::cout << "Saving existing EEPROM data." << std::endl;
	auto eeprom_bytes = read_raw_eeprom(device);
	{
		std::ofstream cali_file(blade_device_->getSerial() + "_eeprom_" +
			std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + ".dat");
		if(!cali_file) {
			std::cout << "Aborting EEPROM read/write test.  Unable to save exisiting EEPROM.\n";
			return;
		}

		boost::archive::text_oarchive oa(cali_file);
		oa & eeprom_bytes;
	}
	std::cout << "Initializing EEPROM with dummy data." << std::endl;
	initialize_eeprom(device);

	for(int i = 0; i < 20; ++i) {
		// Simulate reading and writing our calibration and license (dummy vectors).
		try {
			std::cout << tmp_gps.get_latest_gps() << std::endl;

			blade_device_->enableRXModule();
			blade_device_->collectDummySnapshot();
			blade_device_->disableRXModule();

			std::cout << tmp_gps.get_latest_gps() << std::endl;

			std::cout << i << " Reading EEPROM." << std::endl;
			auto tmp_ee = read_eeprom(device);

			eeprom verify_ee;
			EXPECT_TRUE(verify_ee.cal_ == tmp_ee.cal_);
			EXPECT_TRUE(verify_ee.license_ == tmp_ee.license_);

			std::cout << tmp_gps.get_latest_gps() << std::endl;

			blade_device_->enableRXModule();
			blade_device_->collectDummySnapshot();
			blade_device_->disableRXModule();

			std::cout << tmp_gps.get_latest_gps() << std::endl;

			std::cout << i << " Writing EEPROM." << std::endl;
			write_eeprom(device, verify_ee);
		}
		catch(BladeError &e) {
			std::cout << "error: " << e.message << " | " << e.error_code_ << std::endl;
		}
		catch(std::exception &e) {
			std::cout << "std error: " << e.what() << std::endl;
		}
	}

	std::cout << "Writing original EEPROM." << std::endl;
	write_raw_eeprom(device, eeprom_bytes);
	
	system("pause");
}