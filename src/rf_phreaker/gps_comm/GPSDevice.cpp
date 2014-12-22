/*
 * GPSDevice.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: me
 */

#include "GPSDevice.h"
#include "NMEAParser.h"
#include <thread>
#include <typeinfo>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "boost/algorithm/string.hpp"
#include "rf_phreaker/common/log.h"

using namespace std;

namespace rf_phreaker { namespace gps_comm {



	const uint8_t GPSDevice::gps_idle[] = { 0xA7, 0xB4 };

	GPSDevice::GPSDevice(FrontEndBoard& fb) : frontend(fb), maxSPIUpdateBytes(SPI_MAX_UPDATE_BYTES) {
		log = false;

		service.fix.scanningDeviceSerial = frontend.getBlade().getSerial();


		setInterface(DataInterface::UART);
		idleindex = 1;

		BladeDevice& blade = frontend.getBlade();
		blade.setXBGPIODir(FrontEndBoard::ControlPin::GPS_WAKEUP,	BladeDevice::GPIODirection::IN);
		blade.setXBGPIODir(FrontEndBoard::ControlPin::GPS_ON_OFF,	BladeDevice::GPIODirection::OUT);
		blade.setXBGPIODir(FrontEndBoard::ControlPin::GPS_RESET,	BladeDevice::GPIODirection::OUT);
		blade.setXBGPIODir(FrontEndBoard::ControlPin::GPS_TX,		BladeDevice::GPIODirection::OUT);
		blade.setXBGPIODir(FrontEndBoard::ControlPin::GPS_RX,		BladeDevice::GPIODirection::IN);

		blade.setXBGPIODir(FrontEndBoard::ControlPin::SPI_CS,		BladeDevice::GPIODirection::OUT);
		blade.setXBGPIODir(FrontEndBoard::ControlPin::GPS_PPS,		BladeDevice::GPIODirection::IN);


		frontend.setPin(FrontEndBoard::ControlPin::GPS_ON_OFF, false);
		frontend.setPin(FrontEndBoard::ControlPin::GPS_RESET, true);
	}


	GPSDevice::~GPSDevice(){

	}


	void GPSDevice::setInterface(DataInterface inter){
		LOG(LGPS) << "Setting gps interface to " << (inter == SPI ? "SPI." : (inter == UART ? "UART." : "unknown."));
		dataInterface = inter;
	}

	GPSDevice::DataInterface GPSDevice::getInterface(){
		return dataInterface;
	}

	void GPSDevice::togglePower(){
		frontend.setPin(FrontEndBoard::ControlPin::GPS_ON_OFF, true);
		this_thread::sleep_for(chrono::milliseconds(25));
		frontend.setPin(FrontEndBoard::ControlPin::GPS_ON_OFF, false);
	}


	// wakeup signal is reliable, so this checks to make sure it is in right state.
	// if wakeup is unreliable (like if board disconnected), a timeout will occur, and exception is thrown.
	void GPSDevice::setPower(bool set_on){

		// Origin module responds to 100ms on/off pulse (like a button press) to
		// toggle it on, and then off again sometime later.
		uint32_t timeout_ms = 1000;
		uint32_t checktime_ms = 10;

		LOG(LGPS) << "Current gps power is " << std::boolalpha << awake() << ".";
		if (log){
			cout << "Current GPS Power: " << boolalpha << awake() << endl;
		}

		if (set_on)
		{ 			// TURN ON
			if (log){
				cout << "GPS turning power ON..." << endl;
			}

			LOG(LGPS) << "Turning gps power on.";

			for(int i = 0; i < 5; ++i) {
				uint32_t counter_ms = 0;
				if(!awake()) {
					togglePower();
				}

				// spin till gps is on...
				while(!awake() && counter_ms < timeout_ms) {
					this_thread::sleep_for(chrono::milliseconds(checktime_ms));
					counter_ms += checktime_ms;
				}

				if(awake())
					break;
			}
			// if couldn't turn off in timeout...
			if(!awake()) 
				throw GPSDeviceError("Unable to power off gps device.  Timed out while waiting for wakeup signal.");
		}
		else
		{			// TURN OFF
			if (log){
				cout << "GPS turning power OFF..." << endl;
			}

			LOG(LGPS) << "Turning gps power off.";

			for(int i = 0; i < 5; ++i) {
				uint32_t counter_ms = 0;
				if(awake()) {
					togglePower();
				}

				// spin till gps is off...
				while(awake() && counter_ms < timeout_ms) {
					this_thread::sleep_for(chrono::milliseconds(checktime_ms));
					counter_ms += checktime_ms;
				}
			
				if(!awake())
					break;
			}
			// if couldn't turn off in timeout...
			if (awake())
				throw GPSDeviceError("Unable to power down GPS device.  Timed out while waiting for wakeup signal.");
		}

		if (log){
			cout << "GPS Awake: " << awake() << endl;
		}

		LOG(LGPS) << "gps awake status: " << boolalpha << awake() << ".";

	}
	void GPSDevice::reset(){
		LOG(LGPS) << "Resetting gps device.";
		frontend.setPin(FrontEndBoard::ControlPin::GPS_RESET, false);
		this_thread::sleep_for(chrono::milliseconds(500));
		frontend.setPin(FrontEndBoard::ControlPin::GPS_RESET, true);

	}


	bool GPSDevice::awake()
	{
		return frontend.getPin(FrontEndBoard::ControlPin::GPS_WAKEUP);
	}


	GPSFix GPSDevice::getFix(){

		return service.fix;
	}

	void GPSDevice::requestNewCalibrationCount(uint8_t samples){
		frontend.getBlade().niosRPC(BladeDevice::NiosRPC::GPS_CALIBRATION_START, samples);
	}
	uint32_t GPSDevice::checkCalibrationCount(){
		return frontend.getBlade().niosRPC(BladeDevice::NiosRPC::GPS_CALIBRATION_READ, 0);
	}


	void GPSDevice::disableAllNMEAOutput(){

		LOG(LGPS) << "Disabling all NMEA output on gps device.";
		//configure the gps settings

		NMEACommandSerialConfiguration cfg;
		//cfg.baud = 9600;		//4800, 9600
		//sendCommand(cfg);
		//uartBaud((uint16_t)cfg.baud);		//set the actual controller baud right after changing gps


		//turn off all messages
		NMEACommandQueryRate query;


		query.messageID = NMEASentence::GGA;	//gpgga
		query.rate = 0;			//disable
		sendCommand(query);

		query.messageID = NMEASentence::GSA;	//gpgsa
		query.rate = 0;			//disable
		sendCommand(query);

		query.messageID = NMEASentence::RMC;	//gprmc
		query.rate = 0;			//disable
		sendCommand(query);

		query.messageID = NMEASentence::GSV;	//gpgsv
		query.rate = 0;			//disable
		sendCommand(query);
	}


	void GPSDevice::sendQuery(vector<NMEASentence::MessageID> types){

		NMEACommandQueryRate query;
		// --- query these ONCE --

		for (size_t i = 0; i < types.size(); i++){
			query.messageID = types[i];
			query.mode = NMEACommandQueryRate::QUERY;		//single query
			sendCommand(query);
		}
	}


	void GPSDevice::sendCommand(NMEACommand& cmd){
		string scmd = cmd.toString();
		if (log){
			cout << "Sending command to gps: " << scmd << endl;
		}

		LOG(LGPS) << "Sending " << formatCommand(scmd) << " command to gps device.";

		sendCommand(scmd);
	};

	std::string GPSDevice::formatCommand(std::string cmd) {
		boost::algorithm::replace_all(cmd, "\r", "\\r");
		boost::algorithm::replace_all(cmd, "\n", "\\n");
		return cmd;
	}


	void GPSDevice::sendCommand(std::string cmd){
		if (dataInterface == DataInterface::SPI){
			
			uint32_t send = 0;
			for (size_t i = 0; i < cmd.size(); i += sizeof(uint32_t))
			{
				send = 0;
				for (size_t j = 0; j < sizeof(uint32_t) && (i + j) < cmd.size(); j++){
					send |= cmd[i + j] << (j * 8);
				}
				spiWrite(send);
			}

		}
		else if (dataInterface == DataInterface::UART){
			for (size_t i = 0; i < cmd.size(); i++)
			{
				uartWrite(cmd[i]);
			}
		}
		else {}

	}


	//decides how to interpret each new incoming byte, regardless of interface
	void GPSDevice::interpretOriginBytes(uint8_t byte){
		if (log){
			
			std::cout << " [" << std::hex << std::showbase << std::setw(2) << (int)byte << std::dec << std::noshowbase << "] ";
			if (byte >= 9)
			{
				if (byte == '\r')
				{
					cout << "\\r";
				}
				else if (byte == '\n'){
					cout << "\\n";
				}
				else {
					cout << byte;
				}
			}
			else {
				cout << '.';
			}
		}

		if (byte != 0){
			service.parser.parseByte(byte);
		}
	}


	//handles bytes from uart interface to uart buffer
	void GPSDevice::handleUARTByte(uint8_t b){
		if (dataInterface == DataInterface::UART)
		{
			interpretOriginBytes(b);
		}
	}


	//handles bytes from spi interface to spi buffer
	void GPSDevice::handleSPIByte(uint8_t b){
		if (dataInterface == DataInterface::SPI)
		{
			// gps will return 0xA7, 0xB4 bytes when there is no data....
			// Nios returns 0 on that byte if a zero was given to send. 
			if ( !(b == gps_idle[0] || b == gps_idle[1]) ){
				interpretOriginBytes(b);
			}
		}
	}



	uint32_t GPSDevice::update(){

		uint32_t bytesread = 0;
		if (dataInterface == DataInterface::SPI)
		{
			if (log){
				cout << "SPI update..." << endl;
			}
			uint8_t b = spiRead();
			while ( bytesread < maxSPIUpdateBytes && b != 0)
			{
				if (b == ((uint8_t)-1)){
					//All spi input is high - board has disconnected...
					throw GPSDeviceError("gps device SPI interface unavailable!"); // Possibly the board is removed or hw/fpga is configured wrong.
				}

				if (log){
					cout << "[" << bytesread << "]  ";
				}

				b = spiRead();

				//if an idle byte shows up... we're done.
				if ( (b == gps_idle[0] || b == gps_idle[1]) )
				{
					goto StopUpdate;
				}
					
				bytesread++;

				if (log){
					cout << endl;
				}
			}
	StopUpdate:
			if (log){
				cout << endl;
			}

			return bytesread;
		}
		else if (dataInterface == DataInterface::UART)
		{
			if (log){
				cout << "UART update..." << endl;
			}

			//uint32_t initial_hasdata = uartHasData();		//don't really need this now.

			uint32_t amt = 0;
			uint32_t data = 0;						// uartRead() automatically sends each byte into
													// the gps parser if it's enabled for uart.
			
			while (amt = uartRead(&data)){			//amt is 0-4 bytes
				bytesread += amt;

				// if incoming uart data is zero - which should not happen from GPS because NMEA only sends ascii - then no more data
				// if incoming uart data is 0xff, then the uart is disconnected or faulty in some way.
				if (data == ((uint32_t)-1)  ){
					throw GPSDeviceError("gps device UART interface unavailable!"); // Possibly the board is removed or hw/fpga is configured wrong.
				}

				if (bytesread > 1024){	//1024 is internal buffer size of nios
					//stop for now..?
					if (log){
						cout << " Read initial UART bytes (" << 1024 << ")... more left but skipping." << endl;
					}
					break;
				}

				

				if (log)
				{
					cout << endl;
				}

			}

			if (log){
				cout << " -- total read: " << bytesread << endl;
			}
			return bytesread;
		}
		else
		{
		}

		return bytesread;
	}

	// DO NOT CALL
	uint32_t GPSDevice::fast_update(){
		// The idea is to send 14 bytes of data per  USB transaction to the NIOS instead of the 1 byte as it stands now.
		// The libbladerf functions are ready, but the NIOS code is not implemented. It requires setting up a new handler
		// for a different "magic." Did not finish because current speeds are acceptable.

		throw GPSDeviceError("fast_update is not implemented. The shell is ready in libbladerf but it's not ready on Nios.");

		uint32_t bytesread = 0;
		if (dataInterface == DataInterface::SPI)
		{
			LOG(LGPS) << "fast_update not enabled for SPI.";
			if (log){
				cout << "No fast_update() for SPI..." << endl;
			}
			
			return bytesread;
		}
		else if (dataInterface == DataInterface::UART)
		{
			if (log){
				cout << "UART update..." << endl;
			}

			uint8_t read_buffer[14];		// must be exactly 14 or larger

			uint32_t amt = 0;
			uint32_t data = 0;						// uartRead() automatically sends each byte into
			// the gps parser if it's enabled for uart.
			while ( amt = frontend.getBlade().xboardExpressRead(0, read_buffer) ){			//amt is 0-14 bytes
				bytesread += amt;

				//debug output  -- will just show the individual received bytes
				if (log)
				{
					cout << "(" << amt << ") ";
					for (uint32_t i = 0; i < amt; i++){
						char b = read_buffer[i];
						if (b != 0)
						{
							if (b == '\r')
							{
								cout << "\\r";
							}
							else if (b == '\n'){
								cout << "\\n";
							}
							else {
								cout << b << "[" << (int)b << "]";
							}
						}
						else {
							cout << '.';
						}
					}
					cout << endl;
				}

			}

			if (log){
				cout << "   total read: " << bytesread << endl;
			}
			return bytesread;
		}
		else
		{
		}

		return bytesread;
	}



	//idle byte rotation is only used for spi interface
	uint8_t GPSDevice::getIdleByte(){
		idleindex++;
		idleindex = idleindex % sizeof(gps_idle);
		//cout << "gps idle: " << (int)(gps_idle[idleindex+1]) << "   -->index:" << idleindex << endl;

		return GPSDevice::gps_idle[idleindex];
	}


	uint8_t GPSDevice::spiWrite(uint8_t data)
	{
		return frontend.getBlade().xboardSPI(data);			//returns 0 for all
	}

	// Reads a 4 byte sequence, handles the idle bytes.
	uint8_t GPSDevice::spiRead()
	{
		// Reading is sending a 0. 
		//uint8_t b = frontend.getBlade().xboardSPI(getIdleByte());	//write idle for test
		uint8_t b = frontend.getBlade().xboardSPI(0);	//read response
		//uint8_t b = frontend.getBlade().xboardSPI(0);	//read response

		handleSPIByte(b);	//will send to parser if spi is on
		
		return b;
	}


	uint32_t GPSDevice::uartHasData(){
		uint32_t amt = frontend.getBlade().xboardUARTHasData();
		return amt;
	}


	void GPSDevice::uartWrite(uint8_t data){
		frontend.getBlade().xboardUARTWrite(data);
	}


	uint32_t GPSDevice::uartRead(uint32_t* data){

		uint32_t d = frontend.getBlade().xboardUARTRead();
		uint32_t num = 0;

		if (data != 0){
			*data = d;
		}

		//only process up to 4 bytes, cause amt returns the total number of bytes in buffer on nios,
		//but a single read only returns up to 4 bytes.
		for (int i = 0; i < 4; i++){
			char b = (d >> (i * 8)) & 0xff;
			if (b != 0){
				handleUARTByte(b);		//will send to parser if uart is on.
				num++;
			}
		}
		
		return num;

	}


	void GPSDevice::uartBaud(uint16_t b){
		LOG(LGPS) << "Setting baud rate to " << b << ".";
		frontend.getBlade().xboardUARTBaud(b);
	}

	// This collects more bytes before concluding what baud the gps is on. Also cycles through all the bauds
	// so we don't have to be given default_baud. This might not have been the right place to implement because now I have a parser in
	// the GPS device... but it's just so much better.
	uint32_t GPSDevice::synchronizeUart(){
		// ----------------------------------------
		// This is muuuuuuuuuuuuuuuuuuch better!
		// ----------------------------------------

		// It's a bit long, but it's not so complicated.
		// - For every baud...
		//     - Get a byte
		//			- if we start and keep getting nonzero bytes - clearing the buffer - continue until byte > 1024, or we get a zero byte.
		//			- if we get a zero byte - buffer is empty - now parsing next bytes as possible good input.
		//			- if it takes too long to get a nonzero byte (about 2 sec)... then go to next baud rate
		//		- sample for 3 seconds of activity... break if success.
		//		- Check for > 0 successful parses - if yes, keep controller at that correct baud rate.
		//	- If no baud found - revert to NMEA standard (4800) - could throw an error if you want.
				
		LOG(LGPS) << "Attempting to synchronize baud rate...";

		if (dataInterface != DataInterface::UART){
			return 0;
		}

		//max time to spend on each baud. Usually if it's the right one, the parser will catch on and
		// get a success within 1 sec.
		float baudcheck_timeout_s = 5;		

		bool oldlog = log;
		//log = true;

		NMEAParser parser;
		//parser.log = true;
		NMEAParser old = service.parser;

		int successes = 0;
		uint32_t finalBaud = 0;
		vector<uint16_t> bauds = {4800, 9600, 19200, 38400};
							//4800 (default), 9600, 19200, 38400, 115200, [These need nios interrupts ->] 230400, 460800, 921600

		parser.onCommand += [&successes](NMEASentence nmea){
			if (nmea.checksumOK()){
				successes++;
			}
		};


		service.parser = parser;
		for (size_t i = 0; i < bauds.size(); i++){
			int bytesread = 0;
			uint32_t data = 0;
			uint16_t baud = bauds[i];
			int sleeps = 0;
			bool buffer_cleared = false;
			time_t checkstart = clock();
			float elapsed = 0.0;

			if (log){
				cout << "Checking " << baud << " baud..." << endl;
			}
			uartBaud(baud);

			int skipped_bytes_num = 0, new_data = 0;

			do {
				if ( bytesread < 1024 && sleeps == 0 && !buffer_cleared){				//if sleeps == 0, the nios buffer has initial data. else we are getting new.
					if(dataInterface != DataInterface::OTHER)
						setInterface(DataInterface::OTHER);		//skip these bytes... they might be old from a different baud
					//cout << "skip." << endl;

					skipped_bytes_num++;
				}
				else {
					if (log && dataInterface == DataInterface::OTHER){
						cout << "Buffer cleared... reading fresh data." << endl;
					}
					new_data++;
					//cout << "read." << endl;
					if(dataInterface != DataInterface::UART)
						setInterface(DataInterface::UART);		//keep these bytes... they are definitely from the selected baud
				}

				bool reading = true;
				int reads = 0;
				while (reading){
					try {
						reads++;
						bytesread += uartRead(&data);			//reads from gps and sends data through parser if interface is UART
						reading = false;
					}
					catch (BladeError& e){
						if (e.code == BLADERF_ERR_TIMEOUT){
							LOG(LGPS) << "Timeout while receiving gps data. Retrying...";
							if (reads > 10){
								e.message += " - Unable to communicate to FPGA!";
								throw e;
							}
							continue;
						}
						throw e;
					}
				}

				//if (data != 0){
				//	cout << "[" << bytesread << "]  " << (char)(0xff & data) << (char)((0xff00 & data)>>8) << (char)((0xff0000 & data)>>16) << (char)((0xff000000 & data)>>24) << endl;
				//}
				//else {
				//	cout << "." << endl;
				//}



				if (data != 0){
					sleeps = 0;
				}
				else {
					buffer_cleared = true;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					sleeps++;
					if (sleeps > 20){		//2 sec of possible silence (0's)
						LOG(LGPS) << "Timeout while waiting for next byte.";
						if (log){
							cout << " > Too long to read a byte... skipping." << endl;
						}
						break;
					}
				}

				if (data == ((uint32_t)-1)){
					throw GPSDeviceError("gps device UART interface unavailable");
				}

				elapsed = (clock() - checkstart) / (float)CLOCKS_PER_SEC;
				if (elapsed > baudcheck_timeout_s){
					LOG(LGPS) << "Sampling timeout - skipping baud rate.";
					if (log){
						cout << " > Sampling timeout... skipping." << endl;
					}
					break;
				}
				
				
			} while ( successes == 0 && bytesread < 1024 + 500);			// enough to flush the buffer and start reading with the new baud

			LOG(LGPS) << "Skipped data " << skipped_bytes_num << " times.  Read data " << new_data << " times.  Total bytes read: " << bytesread;

			if (successes > 0){
				finalBaud = baud;
				LOG(LGPS) << "Found " << successes << " possible baud rate matches.  Synchronizing to a baud rate of " << finalBaud << ".";
				if (log){
					cout << " > CORRECT!" << endl;
				}
				break;
			}
			
		}// for

		if(successes == 0) {
			// last ditch effort... Set baud to NMEA standard 4800
			LOG(LGPS) << "Unable to detect baud rate.  Reverting to default 4800.";
			if (log){
				cout << " <!> No baud rate detected with NMEA data. Reverting to standard 4800." << endl;
			}
			finalBaud = 4800;
			uartBaud(4800);
		}

		if (log){

			cout << " Synchronized at " << finalBaud << " baud. Continue;" << endl;
		}

		service.parser = old;
		log = oldlog;


		return finalBaud;
	}


}} 
