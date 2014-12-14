/*
 * GPSDevice.h
 *
 *  Created on: Jul 26, 2014
 *      Author: ck
 */

#ifndef GPSDevice_H_
#define GPSDevice_H_


#include <string>
#include <functional>
#include "BladeDevice.h"
#include "GPSService.h"
#include "NMEACommand.h"
#include "FrontEndBoard.h"
#include "rf_phreaker/common/exception_types.h"


#define SPI_MAX_UPDATE_BYTES 1000


namespace rf_phreaker { namespace gps_comm {


	class GPSDeviceError : public gps_comm_error {
	public:
		std::string message;
		GPSDeviceError(std::string msg) 
			: gps_comm_error(msg), message(msg)
		{};
	};

	class GPSDevice {
	public:
		enum DataInterface
		{
			OTHER,
			SPI,
			UART
		};

	private:
		static const uint8_t gps_idle[];

		void setupParsedCommandEventHandlers();		// initialization function


		uint32_t idleindex;				//handles the spi idle bytes
		uint8_t getIdleByte();


		void handleUARTByte(uint8_t);		// byte received over uart interface
		void handleSPIByte(uint8_t);		// byte received over spi interface
		void interpretOriginBytes(uint8_t byte);		// decides where to send new received byte

		void togglePower();				// sends a power toggle pulse over the gpsOnOff pin



		DataInterface dataInterface;		//which interface to r/w
		FrontEndBoard& frontend;
	public:
		bool log;
		uint32_t maxSPIUpdateBytes;
		GPSService service;					//contains the gps state


		GPSDevice(FrontEndBoard& fb);
		virtual ~GPSDevice();

		bool awake();								// is the GPS chip on
		void setPower(bool set_on);					//tries to put the GPS chip into the state requested, 5sec timeout
		void reset();								//resets gps settings with RESET pin
		GPSFix getFix();							//gets the current fix information from all data received
		void sendCommand(std::string cmd);			//send custom string to the GPS chip.
		void sendCommand(NMEACommand& cmd);			//sends a standard command to the GPS chip

		void disableAllNMEAOutput();				// stops all messages from the GPS chip
		void sendQuery(std::vector<NMEASentence::MessageID> types);		//will query the gps chip for a single update
		// to each of the messages listed
		// -- Query Usage --
		//  sendQuery( /*NMEASentence::MessageID vector list*/ );		//  Will request the information...
		//    
		//  update();		//  Will read all the requested information, putting it into the fix.
		//	  

		// Sets which interface (SPI/UART) the parser uses as input, or where to send commands.
		void setInterface(DataInterface inter);
		DataInterface getInterface();


		// call every so often (1-2 sec - depending on baud rate) to read the new data and update the internal states.
		uint32_t update();			//returns number of bytes read
		uint32_t fast_update();			//returns number of bytes read


		void uartBaud(uint16_t b);

		uint32_t synchronizeUart();			//called to make sure the baud rates are correct on NIOS and gps chip.

		void requestNewCalibrationCount(uint8_t samples);		//call to initiate a calibration count using 'samples' gps pps pulses
		uint32_t checkCalibrationCount();					//call periodically to check if the measurement is available. >0 if measurment is complete.

		std::string formatCommand(std::string cmd);
	private:
		// ----- Low Level Data Transfer Functions -------

		// SPI
		uint8_t spiWrite(uint8_t data);	//writes byte to gps and returns the response, without parsing it
		uint8_t spiRead();				//gets the latest data from the gps

		// UART
		void uartWrite(uint8_t data);
		uint32_t uartHasData();						//returns number of bytes buffered inside of NIOS
		uint32_t uartRead(uint32_t* data = 0);		//returns the num bytes read, also

	};

}} 

#endif /* GPSDevice_H_ */
