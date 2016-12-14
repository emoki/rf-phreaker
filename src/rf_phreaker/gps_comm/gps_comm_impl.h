#include <memory>
#include <thread>
#include "libbladeRF.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/gps_comm/GpsComm.h"
#include "rf_phreaker/gps_comm/FrontEndBoard.h"
#include "rf_phreaker/gps_comm/GPSDevice.h"


namespace rf_phreaker { namespace gps_comm {

// Currently we're using this as a library so allow the exceptions to propagate up.
class gps_comm_impl
{
public:
	gps_comm_impl() {}

	void init(bladerf *blade, bool use_spi) {
		blade_device_.reset(new GpsComm(blade));
		front_end_board_.reset(new FrontEndBoard(*blade_device_));
		origin_gps_device_.reset(new GPSDevice(*front_end_board_));

		// -- Pulls the reset pin for 0.5 sec.
		origin_gps_device_->reset();

		// -- Pick UART Bauds		 -- Default depends on the chip... NMEA standard is 4800
#define GPS_PREFERRED_BAUD 9600


		// -- Pick Data Interface
		origin_gps_device_->setInterface(use_spi ? GPSDevice::DataInterface::SPI :
			GPSDevice::DataInterface::UART);

		// -- Enable Debug information
		//origin_gps_device_->service.parser.log = true;	//shows nmea success / fail info
		//origin_gps_device_->log = true;					//shows data xfer / gps state info



		// -- START GPS DEVICE     [throws GPSDevice:gps_comm_error]
		// set power now will try it's best to put device in the state requested within 5 sec timeout, otherwise error
		origin_gps_device_->setPower(true);

		// TODO DISABLE THIS - It is only to show/confirm activity while running "initialization_gtests"
		// -- Just remove these lines.
		//origin_gps_device_->service.parser.onCommand += [](NMEASentence nmea){
		//	if ( nmea.checksumOK() ){
		//		std::cout << "GPS ::> " << nmea.text << std::endl;
		//	}
		//};

		// -- Prevent improper shutdown if the power pulses are not timed right while dealing with blade gpio init pulses...
		// - overriding default parser handler of no action
		origin_gps_device_->service.parser.setCommandHandler("PSRF150", [&](NMEASentence nmea) {
			if(!nmea.checksum.compare("3E")) {
				//std::cout << "GPS POWER ON!" << std::endl;
				LOG(LGPS) << "Received gps power on message.";
			}
			// Gps sends an invalid checksum when it turns off, checksumOK() will be false.
			else if(!nmea.checksum.compare("3F")) {
				//std::cout << "GPS POWER OFF!" << std::endl;
				//std::cout << "Restarting..." << std::endl;

				LOG(LGPS) << "Received gps power off message.  Attempting to restart..";

				// could have another variable, like main_system_on, that decides to allow the restart or not...
				// - Not sure how to get reference to device from lambda, unique_ptr isn't captureable... that's up to you.
				origin_gps_device_->setPower(true);
			}
			else {
				LOG(LGPS) << "Unknown PSRF150 checksum.";
				//std::cout << "PSRF150 unknown checksum" << std::endl;
			}
		});


		if(origin_gps_device_->getInterface() == GPSDevice::DataInterface::SPI) {
			// can set message rates here too, but SPI is so much less problematic, we can do fine with the defaults.
		}
		else if(origin_gps_device_->getInterface() == GPSDevice::DataInterface::UART) {

			// -- Make sure we are communicating with the right startup baud in order to change settings.
			// -- This will check the data coming in and if it's unreadable, it will automatically adjust the baud rate.
			// -- Needed because ensuring the same baud on nios and gps is tricky when power/reload occurs.
			uint32_t detected = origin_gps_device_->synchronizeUart();

			// -- Sends message to gps to stop sending all sentences... will wait for host commands.
			origin_gps_device_->disableAllNMEAOutput();

			// ===== MESSAGE SELECTION ======
			// If you decide to use this method (periodic updates sent *from* gps) then make sure to COMMENT OUT the "sendQuery" line in "get_latest_gps()"
			// [BEGIN] This section will allow you to specify certain messages to update, as the others will be turned off.
			// - Comment out these if you want to use single updates
			NMEACommandQueryRate updates;

			//std::cout << "Setting GPGGA to output from GPS" << std::endl;
			updates.messageID = NMEASentence::GGA;
			updates.rate = 1;			// seconds per msg
			origin_gps_device_->sendCommand(updates);

			//std::cout << "Setting GPRMC to output from GPS" << std::endl;
			updates.messageID = NMEASentence::RMC;
			updates.rate = 1;			// seconds per msg
			origin_gps_device_->sendCommand(updates);

			//std::cout << "Setting GPGSV to output almanac." << std::endl;
			updates.messageID = NMEASentence::GSV;
			updates.rate = 5;			// seconds per msg
			origin_gps_device_->sendCommand(updates);

			//std::cout << "Setting GPGSA to output almanac." << std::endl;
			updates.messageID = NMEASentence::GSA;
			updates.rate = 1;			// seconds per msg
			origin_gps_device_->sendCommand(updates);
			// [END]


			// change gps baud rate
			NMEACommandSerialConfiguration cfg;
			cfg.baud = GPS_PREFERRED_BAUD;		//4800 (NMEA default), 9600, 19200, 38400, 115200, [These need nios interrupts ->] 230400, 460800, 921600
			//std::cout << "Setting baud rate to " << cfg.baud << std::endl;
			origin_gps_device_->sendCommand(cfg);
			origin_gps_device_->sendCommand(cfg);			// 2x just to be sure.
			//set the actual controller baud right after changing gps
			origin_gps_device_->uartBaud((uint16_t)cfg.baud);
		}
		else {
			// nothing.
		}
	}

	void power_off() {
		if(origin_gps_device_)
			origin_gps_device_->setPower(false);
	}
	
	rf_phreaker::gps get_latest_gps() {

		std::vector<NMEASentence::MessageID> types;
		types.push_back(NMEASentence::GGA);
		types.push_back(NMEASentence::RMC);

		// COMMENT THIS OUT IF YOU WANT PERIODIC UPDATES, NOT SINGLE UPDATES
		//origin_gps_device_->sendQuery(types);

		bool updating = true;
		int updates = 0;
		while (updating){
			try
			{
				updates++;

				// synchronous
				//origin_gps_device_->sendQuery(queryTypes);			//uncomment for single updates  -- Send commands for next update

				// synchronous
				origin_gps_device_->update();

				updating = false;

				return origin_gps_device_->getFix();
			}
			catch (BladeError& e)			// Not re-throwing timeout errors because of below explanation... just retry and we can pull the data.
			{
				if(e.code == BLADERF_ERR_TIMEOUT) {
					LOG(LGPS) << "Timeout while receiving gps data. Retrying...";
					//std::cout << " <!> ############ Blade TIMEOUT Error, trying again... ############ <!>" << std::endl;
					//std::cout << "     - Out of sync with nios, trying again will let it catch up." << std::endl;
					//std::cout << "     - libusb timeout is about 250 ms per access, maybe the host is slow?" << std::endl;

					//if there have been 10 timeouts in a row for a single update... something is severely broken...
					if(updates > 10) {
						throw BladeError("Unable to communicate to FPGA!", e.code);
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					continue;
				}
				else
					throw e;
			}
			catch(const std::exception &err) {
				throw rf_phreaker::gps_comm_error(err.what());
			}
		}
		return rf_phreaker::gps{0};
	}

	void initiate_pps_clock_counter(uint8_t samples){
		origin_gps_device_->requestNewCalibrationCount(samples);
	}

	uint32_t read_pps_clock_counter(){
		return origin_gps_device_->checkCalibrationCount();
	}

private:
	std::unique_ptr<GpsComm> blade_device_;
	std::unique_ptr<FrontEndBoard> front_end_board_;
	std::unique_ptr<GPSDevice> origin_gps_device_;
};

}}