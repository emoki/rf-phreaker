/*
 * OriginGPSDevice.cpp
 *
 *  Created on: Jul 26, 2014
 *      Author: me
 */

#include "OriginGPSDevice.h"
#include <thread>
#include <typeinfo>
#include <chrono>
#include <iostream>

using namespace std;

namespace rf_phreaker { namespace gps_comm {


const uint8_t OriginGPSDevice::gps_idle[] = { 0xA7, 0xB4 };
const std::string OriginGPSDevice::gps_boot_ok = "OK_TO_SEND";

OriginGPSDevice::OriginGPSDevice(FrontEndBoard& fb) : frontend(fb) {

	service.fix.scanningDeviceSerial = frontend.getBlade().getSerial();


	setInterface( DataInterface::UART);
	spiWriteCached = false;
	idleindex = 1;

	frontend.getBlade().setXBGPIODir( FrontEndBoard::ControlPin::GPS_WAKEUP, BladeDevice::GPIODirection::GPIO_IN );	//0 is input
	frontend.getBlade().setXBGPIODir( FrontEndBoard::ControlPin::GPS_ON_OFF, BladeDevice::GPIODirection::GPIO_OUT );	//1 is output
	frontend.getBlade().setXBGPIODir( FrontEndBoard::ControlPin::GPS_RESET, BladeDevice::GPIODirection::GPIO_OUT );	//1 is output
	frontend.getBlade().setXBGPIODir( FrontEndBoard::ControlPin::GPS_TX, BladeDevice::GPIODirection::GPIO_OUT );	//1 is output
	frontend.getBlade().setXBGPIODir( FrontEndBoard::ControlPin::GPS_RX, BladeDevice::GPIODirection::GPIO_IN );	//0 is input

	frontend.getBlade().setXBGPIODir( FrontEndBoard::ControlPin::SPI_CS, BladeDevice::GPIODirection::GPIO_OUT );
	frontend.getBlade().setXBGPIODir( FrontEndBoard::ControlPin::GPS_PPS, BladeDevice::GPIODirection::GPIO_IN );	//0 is input
}
OriginGPSDevice::~OriginGPSDevice(){

}
void OriginGPSDevice::setInterface(DataInterface inter){
	dataInterface = inter;
}
// should probably add state variable, or read to see if GPS is on first...
// because this toggle operation may put it in the wrong state...
// depends on quality of wakeup signal... will see
void OriginGPSDevice::setPower(bool is_on){

	// Origin module responds to 100ms on/off pulse (like a button press) to
	// toggle it on, and then off again sometime later.

	frontend.setPin( FrontEndBoard::ControlPin::GPS_ON_OFF, false );
	std::this_thread::sleep_for(std::chrono::milliseconds(100));	
	frontend.setPin( FrontEndBoard::ControlPin::GPS_ON_OFF, true );
	std::this_thread::sleep_for(std::chrono::milliseconds(100));	
	frontend.setPin( FrontEndBoard::ControlPin::GPS_ON_OFF, false );

}
bool OriginGPSDevice::getWakeup()
{
	return frontend.getPin( FrontEndBoard::ControlPin::GPS_WAKEUP );
}
GPSFix OriginGPSDevice::getFix(){

	return service.fix;
}

void OriginGPSDevice::sendCommand(std::string cmd){
	if(dataInterface == DataInterface::SPI){
		for(size_t i=0; i < cmd.size(); i++)
		{
			spiWrite(cmd[i]);
		}
	}
	else if(dataInterface == DataInterface::UART){
		for(size_t i=0; i < cmd.size(); i++)
		{
			uartWrite(cmd[i]);
		}
	}
	else {}

}

//decides how to interpret each new incoming byte, regardless of interface
void OriginGPSDevice::interpretOriginBytes( uint8_t byte){
	service.parser.parseByte( byte );
}

//handles bytes from uart interface to uart buffer
void OriginGPSDevice::handleUARTByte(uint8_t b){
	if(dataInterface == DataInterface::UART)
	{
		interpretOriginBytes( b );
	}
}
//handles bytes from spi interface to spi buffer
void OriginGPSDevice::handleSPIByte(uint8_t b){
	if(dataInterface == DataInterface::SPI)
	{
		//gps will return 0xA7, 0xB4 bytes when there is no data....
		if( !(b == gps_idle[0] || b == gps_idle[1])){
			interpretOriginBytes( b );
		}
	}
}



uint32_t OriginGPSDevice::update(){
	//throw std::runtime_error("Not finished.");

	uint32_t bytesread = 0;
	if(dataInterface == DataInterface::SPI)
	{
		cout << "SPI update..." << endl;

		uint8_t b = spiRead();
		bytesread++;
		while( !(b == gps_idle[0] || b == gps_idle[1]) )
		{
			b = spiRead();		//automatically passes to parser
			bytesread++;
		}

		return bytesread;
	}
	else if(dataInterface == DataInterface::UART)
	{
		cout << "UART update..." << endl;
		uint32_t amt = 0;
		uint32_t data = 0;						// uartRead() automatically sends each byte into
												// the gps parser if it's enabled for uart.
		while( amt = uartRead(&data) ){			//amt is 0-4 bytes
			//cout << "has data";
			bytesread += amt;

			//debug output  -- will just show the individual reveived bytes

			cout << "  DATA buffered: " << uartHasData() << endl;
			cout << "(" << amt << ") ";
			for(size_t i = 0; i < amt; i++){
				char b = (data >> (i*8)) & 0xff;
				if(b != 0)
					cout << b;
				else
					cout << '.';
			}

		}
		cout << endl;

		return bytesread;
	}
	else
	{	}

	return bytesread;
}

//idle byte rotation is only used for spi interface
uint8_t OriginGPSDevice::getIdleByte(){
	idleindex++;
	idleindex = idleindex % sizeof(gps_idle);
	//cout << "gps idle: " << (int)(gps_idle[idleindex+1]) << "   -->index:" << idleindex << endl;

	return OriginGPSDevice::gps_idle[idleindex];
}
uint8_t OriginGPSDevice::spiWrite(uint8_t data)
{
	frontend.getBlade().xboardSPIWrite(data);
	return frontend.getBlade().xboardSPIRead();
}
uint8_t OriginGPSDevice::spiRead()
{
	uint8_t b = 0;
	frontend.getBlade().xboardSPIWrite( getIdleByte() );
	b = frontend.getBlade().xboardSPIRead();

	handleSPIByte(b);	//will send to parser if spi is on
	return b;
}

uint32_t OriginGPSDevice::uartHasData(){
	uint32_t amt = frontend.getBlade().xboardUARTHasData();
	return amt;
}
void OriginGPSDevice::uartWrite(uint8_t data){
	frontend.getBlade().xboardUARTWrite(data);
}
uint32_t OriginGPSDevice::uartRead(uint32_t* data){

	uint32_t amt = uartHasData();
	uint32_t b = frontend.getBlade().xboardUARTRead();
	uint32_t num = 0;

	if(data != 0){
		*data = b;
	}

	//only process up to 4 bytes, cause amt returns the total number of bytes in buffer on nios,
	//but a single read only returns up to 4 bytes.
	if(amt < 4){
		for(size_t i = 0; i < amt; i++){
			handleUARTByte(   ( b >> (i*8) ) & 0xff    );		//will send to parser if uart is on.
		}
		num = amt;
	}
	else
	{
		for(int i = 0; i < 4; i++){
			handleUARTByte(  ( b >> (i*8) ) & 0xff );		//will send to parser if uart is on.
		}
		num = 4;
	}
	return num;

}


}} 
