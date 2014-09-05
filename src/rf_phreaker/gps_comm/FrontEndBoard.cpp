/*
 * BladeGPS.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: me
 */

#include "FrontEndBoard.h"

namespace rf_phreaker { namespace gps_comm {


FrontEndBoard::FrontEndBoard(BladeDevice& blade) : blade(blade) {

	//blade.setXBGPIODir( FrontEndBoard::ControlPin::SW_CHx_V1, BladeDevice::GPIODirection::GPIO_OUT );	//1 is output
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::SW_CHx_V2, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::SW_CHx_V3, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::SW_CHx_V4, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::CSx_BAND_X1, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::CSx_BAND_X2, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::CSx_BAND_X3, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::SW_HIGH_X1, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::SW_HIGH_X2, BladeDevice::GPIODirection::GPIO_OUT );
	//blade.setXBGPIODir( FrontEndBoard::ControlPin::SW_HIGH_X3, BladeDevice::GPIODirection::GPIO_OUT );
}

FrontEndBoard::~FrontEndBoard() {
	// TODO Auto-generated destructor stub
}

BladeDevice& FrontEndBoard::getBlade()
{
	return blade;
}

void FrontEndBoard::setPin(ControlPin p, bool state){			// sets gpio pins by name
	setGPIO( (uint32_t)p, state);
}
void FrontEndBoard::setGPIO(uint32_t gpio_index, bool state){	// sets pins by index, start @ 1
	blade.setXBGPIO(gpio_index, state);
}
bool FrontEndBoard::getPin(ControlPin p){			// gets gpio pins by name
	return getGPIO( (uint32_t)p );
}
bool FrontEndBoard::getGPIO(uint32_t gpio_index){	// gets pins by index, start @ 1
	return blade.getXBGPIO(gpio_index);
}


void FrontEndBoard::setFilterChannel(uint32_t v, bool on){
	switch(v)
	{
		case 1:		setPin(ControlPin::SW_CHx_V1, on); break;
		case 2:		setPin(ControlPin::SW_CHx_V2, on); break;
		case 3:		setPin(ControlPin::SW_CHx_V3, on); break;
		case 4:		setPin(ControlPin::SW_CHx_V4, on); break;
		default: break;
	}
}
void FrontEndBoard::setFilterBand(uint32_t x, bool on){
	switch(x)
	{
		case 1:		setPin(ControlPin::CSx_BAND_X1, on); break;
		case 2:		setPin(ControlPin::CSx_BAND_X1, on); break;
		case 3:		setPin(ControlPin::CSx_BAND_X1, on); break;
		default: break;
	}
}
void FrontEndBoard::setFilterHigh(uint32_t x, bool on){
	switch(x)
	{
		case 1:		setPin(ControlPin::SW_HIGH_X1, on); break;
		case 2:		setPin(ControlPin::SW_HIGH_X2, on); break;
		case 3:		setPin(ControlPin::SW_HIGH_X3, on); break;
		default: break;
	}
}

}} 
