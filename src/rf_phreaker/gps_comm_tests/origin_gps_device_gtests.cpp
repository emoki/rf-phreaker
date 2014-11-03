#include "gtest/gtest.h"
#include <memory>
#include <thread>
#include "libbladeRF.h"
#include "rf_phreaker/gps_comm/OriginGPSDevice.h"

#include <chrono>


using namespace rf_phreaker::gps_comm;

TEST(OriginGpsDevice, TestGeneral) {

	bladerf *device;

	bool USE_SPI = false;			// Change for UART(false) / SPI(true) boards
	bool RUN_RX = false;			// Set to run a dummy rx scan on each update.


#define GPS_PREFERRED_BAUD 19200


	// -- Pick UART Bauds		 -- Default depends on the chip... NMEA standard is 4800
	// #define GPS_DEFAULT_BAUD 4800
	// #define GPS_PREFERRED_BAUD 9600


	int sts;

	// Open first available device.
	bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
	sts = bladerf_open(&device, nullptr);
	if (sts != 0){
		std::cout << "==== DEVICE FAILED! ====  :  " << bladerf_strerror(sts) << std::endl;
		std::cin.ignore();
	}
	EXPECT_EQ(0, sts);


	//Beginning:   

	
	std::cout << " Loading FPGA... " << std::endl;
	
	sts = bladerf_load_fpga(device, "fpga_load-fw-v2.rbf");

	if (sts != 0){
		std::cout << "==== FPGA LOAD FAILED! ====  " << bladerf_strerror(sts) << std::endl;
		std::cin.ignore();
	}

	EXPECT_EQ(0, sts);

	std::cout << " FPGA OK " << std::endl;


	std::unique_ptr<BladeDevice> blade_device_;
	std::unique_ptr<FrontEndBoard> front_end_board_;
	std::unique_ptr<OriginGPSDevice> origin_gps_device_;

	blade_device_.reset(new BladeDevice(device));
	front_end_board_.reset(new FrontEndBoard(*blade_device_));
	origin_gps_device_.reset(new OriginGPSDevice(*front_end_board_));

	origin_gps_device_->reset();

	if (USE_SPI){
		origin_gps_device_->setInterface(OriginGPSDevice::SPI);
	}
	else {
		origin_gps_device_->setInterface(OriginGPSDevice::UART);
	}


	// -- DEBUG LOG TO COUT
	//origin_gps_device_->service.parser.log = true;
	//origin_gps_device_->log = true;


	// set power will now try it's best to put device in the state requested in 5 sec timeout, otherwise error
	std::cout << "Starting GPS..." << std::endl;
	try
	{
		origin_gps_device_->setPower(true);
	}
	catch (OriginGPSDeviceError& e){
		std::cout << "OriginGPSDevice Error: " << e.message << std::endl;
	}
	std::cout << "GPS Awake: " << std::boolalpha << origin_gps_device_->awake() << std::endl;		//confirmation



	// If GPS is still tricked with timing issues, can still try to restart it, this ensures it is definitely on.
	// - ...except I don't know how to capture the gps unique_ptr to call set power from inside the lambda, so... that's up to you.
	origin_gps_device_->service.parser.setCommandHandler("PSRF150", [](NMEASentence nmea){
		if (!nmea.checksum.compare("3E")){
			std::cout << "GPS POWERED ON!" << std::endl;
		}
		// Origin sends an invalid checksum when it turns off, checksumOK() will be false.
		else if (!nmea.checksum.compare("3F")){
			std::cout << "GPS POWERED OFF ?!?! " << std::endl;
			//std::cout << "Restarting..." << std::endl;
			//origin_gps_device_->setPower(true);
			//origin_gps_device_->setDefaultNMEASettings();
		}
		else
		{
			std::cout << "PSRF150 unknown checksum" << std::endl;
		}
	});


	if (origin_gps_device_->getInterface() == OriginGPSDevice::DataInterface::SPI){
		// can set message rates here too, but SPI is so much less problematic, we can do fine with the defaults.
	}
	else if (origin_gps_device_->getInterface() == OriginGPSDevice::DataInterface::UART){

		//make sure we are communicating and synched with gps at the right startup baud in order to change settings.
		
		std::cout << "Auto-detecting current GPS baud rate... ";
		uint32_t detected = origin_gps_device_->synchronizeUart();
		std::cout << " detected " << detected << " baud." << std::endl;


		// Disable all messages from the GPS
		origin_gps_device_->disableAllNMEAOutput();

		// Enable only certain messages from GPS at certain rate
		// - Comment out these if you want to use single updates
		NMEACommandQueryRate updates;

		// [!] -- CHANGE MESSAGE RATES HERE -- [!]
		std::cout << "Setting GPGGA as output." << std::endl;
		updates.messageID = NMEASentence::GGA;
		updates.rate = 1;			// seconds per msg
		origin_gps_device_->sendCommand(updates);

		std::cout << "Setting GPRMC as output." << std::endl;
		updates.messageID = NMEASentence::RMC;
		updates.rate = 1;			// seconds per msg
		origin_gps_device_->sendCommand(updates);

		std::cout << "Setting GPGSV as outputting almanac." << std::endl;
		updates.messageID = NMEASentence::GSV;
		updates.rate = 4;			// seconds per msg
		origin_gps_device_->sendCommand(updates);


		// change gps baud rate
		NMEACommandSerialConfiguration cfg;
		cfg.baud = GPS_PREFERRED_BAUD;		//4800 (default), 9600, 19200, 38400, 115200, [These need nios interrupts ->] 230400, 460800, 921600
		std::cout << "Setting baud rate to " << cfg.baud << std::endl;
		origin_gps_device_->sendCommand(cfg);
		origin_gps_device_->sendCommand(cfg);
		//set the actual controller baud right after changing gps
		origin_gps_device_->uartBaud( (uint16_t)cfg.baud );
	}
	else {
		// nothing.
	}







	// show sentence received
	origin_gps_device_->service.parser.onCommand += [](NMEASentence nmea){
		std::cout << " >> GPS Received. checksum: " << (nmea.checksumOK() ? "good" : "bad") << ". Tag: [$" << nmea.name << "] Text: " << nmea.text << std::endl;
	};


	if (RUN_RX){
		blade_device_->initializeForCollection();
	}

	std::cout << "Begin" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	//std::cin.ignore();

	clock_t runTime = clock();
	uint32_t timeouts = 0;
	uint32_t timeouts_read = 0;
	uint32_t timeouts_write = 0;
	uint32_t total_updates = 0;
	uint32_t total_bytes_read = 0;
	bool inread = false;
	bool inwrite = false;
	std::vector<NMEASentence::MessageID> queryTypes;
	queryTypes.push_back(NMEASentence::GGA);
	queryTypes.push_back(NMEASentence::RMC);


	for (int i = 0; i < 60; ++i) {
		try {
			inread = false;
			inwrite = false;

			system("cls");

			uint32_t hd = origin_gps_device_->uartHasData();
			clock_t startTime = clock();

			inwrite = true;
			//std::cout << std::endl << " -- sending queries..." << std::endl;
			//origin_gps_device_->sendQuery(queryTypes);			//uncomment for single updates  -- Send commands for next update
			inwrite = false;

			inread = true;
			uint32_t bytes = origin_gps_device_->update();
			total_bytes_read += bytes;
			inread = false;

			if (RUN_RX){
				blade_device_->collectDummySnapshot();
			}

			double txtime = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			if (txtime == 0){ txtime = 0.001; }

			std::cout << std::endl;
			std::cout << "Transmission: \t\tBytes: " << bytes << " \tTime: " << txtime << " s \t\tRate: " << bytes / txtime << " b/s" << std::endl;
			std::cout << "Timeouts:   \t\tREAD: " << timeouts_read << " \tWRITE: " << timeouts_write << " \t\tTOTAL: " << timeouts << std::endl;
			std::cout << "Total Updates: \t\t" << total_updates << std::endl;
			double elaptime = (clock() - runTime) / (double)CLOCKS_PER_SEC;
			std::cout << "Elapsed Run Time: \t" << elaptime / 60.0 << " min  (" << elaptime << " s)" << std::endl;
			std::cout << "Uart FIFO Data:   \t" << hd << std::endl;


			std::cout << std::endl << std::endl << origin_gps_device_->getFix().toString() << std::endl;



			std::cout << std::endl << " -- Waiting for next update..." << std::endl;
			total_updates++;
		}
		catch (BladeError& e){
			if (e.code == BLADERF_ERR_TIMEOUT){
				std::cout << " <!> ############ Blade TIMEOUT Error, trying again... ############ <!>" << std::endl;
				std::cout << "     - Out of sync with nios, trying again will let it catch up." << std::endl;
				std::cout << "     - libusb timeout is about 250 ms per access, maybe the host is slow?" << std::endl;

				if (inread){
					timeouts_read++;
				}
				if (inwrite){
					timeouts_write++;
				}
				timeouts++;
				
				if (RUN_RX){
					blade_device_->disableRXModule();
					blade_device_->enableRXModule();
				}

				continue;
			}
			else
			{
				throw e;
			}
		}
		catch (OriginGPSDeviceError& e){
			std::cout << "GPS ERROR: " << e.message << std::endl;
		}

		// polling interval
		for (int i = 1; i > 0; i--){
			std::cout << "Update in " << i << "..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}


	// -- Run entire test again if necessary
	//try{
	//	origin_gps_device_->setPower(false);
	//}
	//catch (...){}
	//std::cout << "GPS OFF - RUNNING AGAIN..." << std::endl;
	//
	//goto Beginning;


	EXPECT_EQ(0, timeouts);
	EXPECT_TRUE( total_bytes_read > 0 );
	std::cout << "DONE" << std::endl;
	//std::cin.ignore();
}