#include "gtest/gtest.h"
#include <memory>
#include <thread>
#include "libbladeRF.h"
#include "rf_phreaker/gps_comm/GPSDevice.h"

#include <chrono>


using namespace rf_phreaker::gps_comm;


//--------------------------------------------------------------------------------------------
//----------------------- Calibration Utility Functions --------------------------------------
//--------------------------------------------------------------------------------------------

//return number of cycles (frequency) the vcxto is off by
double clockerror_cycles(uint32_t measure, int samples, uint32_t ref_clock){
	return  (double)measure / (double)samples - (double)ref_clock;
}
//return the percent error the vcxto is off by
double clockerror_percent(uint32_t measure, int samples, uint32_t ref_clock){
	double meas = (double)clockerror_cycles(measure, samples, ref_clock) / (double)ref_clock;
	return meas;
}

// hz per dac lsb
double dac_trim_hz_per_lsb_coefficient(){
	double vref = 2.5;									// dac Vref
	double dac_v_lsb = vref / (double)(1 << 16);		// voltage per lsb = vref / 2^n		== 0.03814697265625 mV

	double vctcxo_frequency_tuning_range_ppm = 7.25*2.0;	// ASVTX-12 minimum +/- 5ppm and maximum +/- 9.5  avg would be 
	double vctcxo_voltage_tuning_range = 2.0;				// +0.4v - +2.4v
	double vctcxo_f_ppm = 38.4;								// 38.4 Mhz -> ppm -> 38.4 hz

	// 5ppm ~ 0.007 hz;  9ppm ~ 0.013 hz;
	double tune_hz_per_dac_lsb = vctcxo_frequency_tuning_range_ppm * vctcxo_f_ppm / vctcxo_voltage_tuning_range * dac_v_lsb;

	return tune_hz_per_dac_lsb;
}

//--------------------------------------------------------------------------------------------



TEST(GPSDevice, TestGeneral) {

	// The GPS output is large. Need more horizontal reading room.
	system("mode con:cols=120 lines=50");				//get fat!



	bladerf *device;

	bool USE_SPI = false;			// Change for UART(false) / SPI(true) boards
	bool RUN_RX = false;			// Set to run a dummy rx scan on each update.


#define GPS_PREFERRED_BAUD /*19200*/9600


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
	
	sts = bladerf_load_fpga(device, "fpga_load.rbf");

	if (sts != 0){
		std::cout << "==== FPGA LOAD FAILED! ====  " << bladerf_strerror(sts) << std::endl;
		std::cin.ignore();
	}

	EXPECT_EQ(0, sts);

	std::cout << " FPGA OK " << std::endl;


	std::unique_ptr<GpsComm> blade_device_;
	std::unique_ptr<FrontEndBoard> front_end_board_;
	std::unique_ptr<GPSDevice> origin_gps_device_;

	blade_device_.reset(new GpsComm(device));
	front_end_board_.reset(new FrontEndBoard(*blade_device_));
	origin_gps_device_.reset(new GPSDevice(*front_end_board_));

	origin_gps_device_->reset();

	if (USE_SPI){
		origin_gps_device_->setInterface(GPSDevice::SPI);
	}
	else {
		origin_gps_device_->setInterface(GPSDevice::UART);
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
	catch (GPSDeviceError& e){
		std::cout << "GPSDevice Error: " << e.message << std::endl;
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


	if (origin_gps_device_->getInterface() == GPSDevice::DataInterface::SPI){
		// can set message rates here too, but SPI is so much less problematic, we can do fine with the defaults.
	}
	else if (origin_gps_device_->getInterface() == GPSDevice::DataInterface::UART){

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
		std::cout << " >> GPS Received. checksum: " << (nmea.checksumOK() ? "good" : "bad") << ". Tag: [$" << nmea.name << "]" << std::endl;
		std::cout << "    Text: " << nmea.text << std::endl;
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

	// ------- Calibration Settings and States----------
	bool requestedCalibrationCount = false;
	bool hasCalibrationCount = false;
	bool measurementCollected = false;
	time_t request_start_time = 0;
	uint32_t calibrationCount = 0;
	std::vector<uint32_t> counts;
	std::vector<uint16_t> trims;
	std::vector<uint8_t> samplecounts;
	uint32_t refclock = 38400000;  //38.4 M
	uint8_t samplecount = 2;			// value is used for the first quick measurement
	uint8_t max_samplecount = 30;		// is used after the first iteration as the more precise measurement.

	//read starting dactrim
	uint16_t dactrim = 0;
	uint16_t dactrimpre = 0;
	bladerf_get_vctcxo_trim(blade_device_->getHandle(), &dactrim);
	dactrimpre = dactrim;
	//-------------------------------------------------


	//Main GPS update loop
	for (int i = 0; i < 60*60; ++i) {
		try {
			inread = false;
			inwrite = false;

			system("cls");

			//uint32_t hd = origin_gps_device_->uartHasData();
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
			//std::cout << "Uart FIFO Data:   \t" << hd << std::endl;


			std::cout << std::endl << std::endl << origin_gps_device_->getFix().toString() << std::endl;



			/*================================================================*/
			/*==================== PPS COUNT READ TEST =======================*/
			/*================================================================*/
			// Testing the full calibration procedure...

			// -- Request a new pps clock measurement if the GPS has a lock
			std::cout << std::endl;
			if (!requestedCalibrationCount && origin_gps_device_->getFix().locked() ){
				if (calibrationCount != 0){
					if (counts.size() > 0 ){
						samplecount = (uint8_t)max_samplecount;
					}
					origin_gps_device_->requestNewCalibrationCount( samplecount );
				}
				samplecounts.push_back(samplecount);
				origin_gps_device_->requestNewCalibrationCount(samplecount);
				request_start_time = clock();
				requestedCalibrationCount = true;
			}
			// -- Waiting for response
			if (!hasCalibrationCount && requestedCalibrationCount){
				calibrationCount = origin_gps_device_->checkCalibrationCount();
				double elapsed_s = (clock() - request_start_time) / (double)CLOCKS_PER_SEC;
				std::cout << "Calibration Counter: Requested...  (status: " << calibrationCount << ") elapsed: " << elapsed_s  << " s  >> " << min(1.0, elapsed_s / (double)samplecount) * 100.0 << " %" << std::endl;

				if (calibrationCount > 0){
					hasCalibrationCount = true;
				}
			}
			// -- Calibrate 38.4 Mhz clock with the new measurement
			if (hasCalibrationCount){
				std::cout << "Calibration Counter: " << calibrationCount << std::endl;
				counts.push_back(calibrationCount);
				trims.push_back(dactrim);

				double time = (double)calibrationCount / refclock;

				// If the measurement is correct - ie. the sample corresponds to the correct amount of time
				if ((uint32_t)round(time) == samplecount){
					// calibrate the system clock - calculate new dactrim
					int32_t delta = (int32_t)round(clockerror_cycles(calibrationCount, samplecount, refclock) * -1.0 / dac_trim_hz_per_lsb_coefficient() * 0.9);		// x 0.9 to dampen convergence and wobble
					uint16_t newdactrim = (uint16_t)((int32_t)dactrim + delta);
					std::cout << " DAC TRIM CHANGED by: " << delta << "  to " << newdactrim << std::endl;
					bladerf_dac_write(blade_device_->getHandle(), newdactrim);
					dactrim = newdactrim;
				} else {
					// Time mismatch, invalid sample.
					// This would happen if the GPS loses a lock during sampling or if there is a spurious extra pulse on the line.
				}

				// count has been logged, request another measurement
				requestedCalibrationCount = false;
				hasCalibrationCount = false;
			}


			// display samples / dactrim information
			std::cout << "dactrim-pre:  " << dactrimpre << std::endl;
			std::cout << "dactrim-last: " << dactrim << std::endl;

			std::cout << "{SAMPLE SIZE: " << (int)samplecount << "; REF CLOCK: " << std::fixed << std::setprecision(3) << (float)refclock / 1000000 << " Mhz}" << std::endl;
			std::cout << "[Measurements]\tRaw\t\t\tError (Hz)\t+/- ppm\t\tTime\t\tfrom dac trim" << std::endl;
			if (counts.size() == 0){
				std::cout << "\tWaiting..." << std::endl;
			}
			for (size_t i = 0; i < counts.size(); i++){
				uint32_t raw_count   = counts[i];
				double   error_hz    = clockerror_cycles(counts[i], samplecounts[i], refclock);
				double   error_ppm   = clockerror_percent(counts[i], samplecounts[i], refclock) * 1000000.0;
				double   sample_time = (double)counts[i] / refclock;

				std::cout << "\t[" << i << "]:  \t" << std::fixed << std::setprecision(3) << raw_count << "\t\t" << error_hz << "\t\t" << error_ppm << "\t\t" << sample_time << "\t\t" << trims[i] <<  std::endl;
			}

			/*================================================================*/
			/*================================================================*/


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
		catch (GPSDeviceError& e){
			std::cout << "GPS ERROR: " << e.message << std::endl;
		}

		// polling interval
		for (int i = 3; i > 0; i--){
			std::cout << "Update in " << i << "..." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
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