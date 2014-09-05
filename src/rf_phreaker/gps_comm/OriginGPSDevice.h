/*
 * OriginGPSDevice.h
 *
 *  Created on: Jul 26, 2014
 *      Author: me
 */

#ifndef ORIGINGPSDEVICE_H_
#define ORIGINGPSDEVICE_H_


#include <string>
#include <functional>
#include "BladeDevice.h"
#include "GPSService.h"
#include "FrontEndBoard.h"

namespace rf_phreaker { namespace gps_comm {

class OriginGPSDevice {
public:
	enum DataInterface
	{
		OTHER,
		SPI,
		UART
	};

private:
	static const std::string gps_boot_ok;
	static const uint8_t gps_idle[];

									// -- SPI notes --
	bool spiWriteCached;			//- the nios caches the return byte from a spi write
									// the first nios read will return that byte, then
									// it will send 0 and receive the next byte on
									// subsequent reads.
									//- because the gps requires an idle code to get info
									// there needs to be a toggler to get the cached byte,
									// or write the new idle code.
									//-in retrospect, uart was easier to implement.

	uint32_t idleindex;
	uint8_t getIdleByte();


	void handleUARTByte(uint8_t);
	void handleSPIByte(uint8_t);
	void interpretOriginBytes( uint8_t byte );
	void setupParsedCommandEventHandlers();



	FrontEndBoard& frontend;
public:
	DataInterface dataInterface;		//which interface to r/w
	GPSService service;					//contains the gps state


	OriginGPSDevice(FrontEndBoard& fb);
	virtual ~OriginGPSDevice();

	bool getWakeup();
	void setPower(bool b=true);
	GPSFix getFix();
	void sendCommand(std::string cmd);
	std::function<void(NMEACommand)> onCommandReceived;

	void setInterface(DataInterface inter);	// sets all data transactions and
										// parsing activity to the given interface
	// call every so often (1-10 ms - depending on baud rate) to read the new data and update the internal states.
	uint32_t update();			//returns number of bytes read

	uint8_t spiWrite(uint8_t data);	//writes byte to gps and returns the response, without parsing it
	uint8_t spiRead();				//gets the latest data from the gps

	void uartWrite(uint8_t data);
	uint32_t uartHasData();
	uint32_t uartRead(uint32_t* data = 0);		//returns the num bytes read, also
													//can return data
};

}} 

#endif /* ORIGINGPSDEVICE_H_ */
