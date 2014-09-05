#include <memory>
#include <thread>
#include "libbladeRF.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/gps_comm/BladeDevice.h"
#include "rf_phreaker/gps_comm/FrontEndBoard.h"
#include "rf_phreaker/gps_comm/OriginGPSDevice.h"


namespace rf_phreaker { namespace gps_comm {

// Currently we're using this as a library so allow the exceptions to propagate up.
class gps_comm_impl
{
public:
	gps_comm_impl() {}

	void init(bladerf *blade) {
		blade_device_.reset(new BladeDevice(blade));
		front_end_board_.reset(new FrontEndBoard(*blade_device_));
		origin_gps_device_.reset(new OriginGPSDevice(*front_end_board_));

		//origin_gps_device_->service.parser.log = true;

		// This should be reworked since we cannot rely on the WAKE_UP pin.
		int i = 0;
		while(!origin_gps_device_->getWakeup()) {
			origin_gps_device_->setPower();
			std::this_thread::sleep_for(std::chrono::seconds(1));
			if(++i > 10)
				throw gps_comm_error("Unable to wake GPS module.");
		}
	}

	void set_to_spi_comm() {
		origin_gps_device_->setInterface(OriginGPSDevice::SPI);
	}

	void set_to_uart_comm() {
		origin_gps_device_->setInterface(OriginGPSDevice::UART);
	}

	rf_phreaker::gps get_latest_gps() {
		origin_gps_device_->update();
		return origin_gps_device_->getFix();
	}

private:
	std::unique_ptr<BladeDevice> blade_device_;
	std::unique_ptr<FrontEndBoard> front_end_board_;
	std::unique_ptr<OriginGPSDevice> origin_gps_device_;
};

}}