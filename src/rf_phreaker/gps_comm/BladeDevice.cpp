//
//  BladeDevice.cpp
//  bladeXcode
//
//  Created by Cameron on 3/30/14.
//  Copyright (c) 2014 Cameron. All rights reserved.
//

#include "BladeDevice.h"
#include "BladeError.h"
#include <iostream>
#include <sstream>


using namespace std;
using namespace rf_phreaker::gps_comm;


BladeDevice::BladeDevice()
: handle(0), devinfo(), isOpen(false), null(true), activeModule(BLADERF_MODULE_RX), isIndirect(false)
{
    serial = "";
}
BladeDevice::BladeDevice(bladerf* open_device)
: handle(open_device), devinfo(), isOpen(true), null(false), activeModule(BLADERF_MODULE_RX), isIndirect(true)
{
	bladerf_devinfo devinfo;
	BladeError::check( bladerf_get_devinfo(open_device, &devinfo) );

	this->devinfo = devinfo;

	stringstream ss;
	ss << devinfo.serial;
	serial = ss.str();
}
// will add proper copy and assignment later.
BladeDevice::BladeDevice(const BladeDevice& ref)
: handle(0), devinfo(), isOpen(false), null(true), activeModule(BLADERF_MODULE_RX), isIndirect(false)
{
	throw BladeError("Can NOT copy BladeDevice object. yet...", -1);
}
void BladeDevice::load(bladerf_devinfo& devinfo)
{
	if(isOpen)
	{
		close();
	}
	handle = 0;
	this->devinfo = devinfo;
	isOpen = false;
	null = false;
    // Copy device serial number
    stringstream ss;
    ss << devinfo.serial;
    serial = ss.str();
}
void BladeDevice::setActiveModule(bladerf_module module)
{
	activeModule = module;
}

// this moves the device, because it is a resource, only 1 can contain it.
// could use some shared pointer, but this should work atm.
BladeDevice::~BladeDevice()
{
    if(isOpen && !isIndirect)
    {
        close();
    }
}

string BladeDevice::getSerial(){
	return serial;
}
bladerf_devinfo BladeDevice::getInfo(){
	return devinfo;
}

bladerf* BladeDevice::getHandle()
{
    if(!isOpen || !handle)
    {
        BladeError::check(-1, "BladeDevice not opened, no handle available.");
        return 0;
    }
    return handle;
}
bool BladeDevice::open()
{
    cout << " >> Opening Device... [" << serial << "]" << endl;
    if(!isOpen)
    {
        int e = bladerf_open_with_devinfo(&handle, &devinfo);
        if(handle)
        {
            isOpen = true;
            cout << " >> Device opened!" << endl;
            return true;
        }
        else
        {
            isOpen = false;
            BladeError::check(e, "FAILED to open device!");
            cout << " >> FAILED to open device!" << endl;
        }
    }
    else
    {
        cout << " >> Device already open." << endl;
    }
    
    return false;
}
bool BladeDevice::close()
{
    cout << " >> Closing Device...[" << serial << "]" << endl;
    if(isOpen && handle)
    {
        bladerf_close(handle);
        handle = 0;
        isOpen = false;
        cout << " >> Device closed." << endl;
        return true;
    }
    else
    {
        cout << " >> Could NOT close device. Device not open." << endl;
    }
    return false;
}

void BladeDevice::loadFPGAImage(std::string fpgapath)
{
	// cout << " (!) Loading FPGA [" << fpgapath.c_str() << "]... ";
	BladeError::check( bladerf_load_fpga(handle, fpgapath.c_str()), "Unable to load FPGA Image...");
}
void BladeDevice::setModuleState(bladerf_module mod, bool state)
{
    BladeError::check(
                      bladerf_enable_module(handle, mod, state)
                      );
}


uint32_t BladeDevice::getConfigGPIO()
{
	uint32_t value = 0;
	BladeError::check( bladerf_config_gpio_read( getHandle(), &value) );
	return value;
}
bool BladeDevice::getConfigGPIO(uint32_t index)
{
	return getbit(getConfigGPIO(), index);
}
void BladeDevice::setConfigGPIO(uint32_t val)
{
	BladeError::check( bladerf_config_gpio_write( getHandle(), val ) );
}
void BladeDevice::setConfigGPIO(uint32_t index, bool val)
{
	uint32_t reg = getConfigGPIO();	//save old
	reg = setbit(reg, index, val);
	setConfigGPIO(reg);		//write new
}

// ----------- [ XB SPI link  ] -------
uint8_t BladeDevice::xboardSPIRead()
{
	uint32_t resp = 0;
	BladeError::check( bladerf_xb_spi_read(handle, &resp) );
	//cout << "SPI RESPONSE: " << (resp&0xff) << "," << (resp&0xff00) << "," << (resp&0xff0000) << "," << (resp&0xff000000) << endl;
	return resp;
}
void BladeDevice::xboardSPIWrite(uint8_t val)
{
	BladeError::check( bladerf_xb_spi_write(handle, val) );
}

uint32_t BladeDevice::xboardUARTRead()
{
	uint32_t b = 0;
	BladeError::check( bladerf_xb_uart_read(handle, &b ) );
	return b;
}
void BladeDevice::xboardUARTWrite(char val)
{
	BladeError::check( bladerf_xb_uart_write(handle, val) );
}
void BladeDevice::xboardUARTBaud(uint16_t baud)
{
	BladeError::check( bladerf_xb_uart_baud_write(handle, baud) );
}
uint32_t BladeDevice::xboardUARTHasData()
{
	uint32_t hasdata = 0;
	BladeError::check( bladerf_xb_uart_hasdata(handle, &hasdata) );
	return hasdata;
}


// ---------------- [ XB GPIO manip ] --------------
uint32_t BladeDevice::getXBGPIO()
{
	uint32_t value = 0;
	BladeError::check( bladerf_expansion_gpio_read( getHandle(), &value) );
	return value;
}
bool BladeDevice::getXBGPIO(uint32_t index)
{
	return getbit(getXBGPIO(), index);
}
void BladeDevice::setXBGPIO(uint32_t value)
{
	BladeError::check( bladerf_expansion_gpio_write( getHandle(), value) );
}
void BladeDevice::setXBGPIO(uint32_t index, bool val)
{
	uint32_t reg = getXBGPIO();	//save current
	reg = setbit(reg, index, val);
	setXBGPIO(reg);		//write new
}

// 1 = OUTPUT, 0 = INPUT
uint32_t BladeDevice::getXBGPIODir()
{
	uint32_t value = 0;
	BladeError::check( bladerf_expansion_gpio_dir_read( getHandle(), &value) );
	return value;
}
bool BladeDevice::getXBGPIODir(uint32_t index)
{
	return getbit(getXBGPIODir(), index);
}
void BladeDevice::setXBGPIODir(uint32_t value)
{
	BladeError::check( bladerf_expansion_gpio_dir_write( getHandle(), value) );
}
void BladeDevice::setXBGPIODir(uint32_t index, bool val)
{
	uint32_t reg = getXBGPIODir();	//save old
	reg = setbit(reg, index, val);
	setXBGPIODir(reg);		//write new
}


bool BladeDevice::getbit(uint32_t field, int i) //from 1
{
	field = (field & (1<<(i-1))) >> (i-1);
	return field ? true : false;
}
uint32_t BladeDevice::setbit(uint32_t field, int i, bool val) // from 1
{
	field = field & (~(1<<(i-1)));		//zeros the index
	field = field | (val<<(i-1));			//sets it t/f
	return field;
}
// --------------------------------------------------

uint32_t BladeDevice::getSampleRate()
{
	unsigned int sr = 0;
	BladeError::check( bladerf_get_sample_rate( getHandle(), activeModule, &sr) );
	return sr;
}
void BladeDevice::setFrequency( uint32_t f)
{
	BladeError::check( bladerf_set_frequency(getHandle(), activeModule, f) );
}
uint32_t BladeDevice::setBandwidth( uint32_t bw)
{
	uint32_t actualbw;
	BladeError::check( bladerf_set_bandwidth(getHandle(), activeModule, bw, &actualbw) );
	return actualbw;
}

uint32_t BladeDevice::getFrequency( )
{
	uint32_t actual;
	BladeError::check( bladerf_get_frequency(getHandle(), activeModule, &actual) );
	return actual;
}
uint32_t BladeDevice::getBandwidth( )
{
	uint32_t actual;
	BladeError::check( bladerf_get_bandwidth(getHandle(), activeModule, &actual) );
	return actual;
}
