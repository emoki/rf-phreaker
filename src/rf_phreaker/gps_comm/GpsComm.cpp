//
//  GpsComm.cpp
//  bladeXcode
//
//  Created by Cameron on 3/30/14.
//  Copyright (c) 2014 Cameron. All rights reserved.
//

#include "GpsComm.h"
#include "BladeError.h"
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace rf_phreaker::gps_comm;


GpsComm::GpsComm()
	: handle(0), devinfo(), isOpen(false), null(true), activeModule(BLADERF_MODULE_RX), isIndirect(false)
{
	serial = "";
}
GpsComm::GpsComm(bladerf* open_device)
	: handle(open_device), devinfo(), isOpen(true), null(false), activeModule(BLADERF_MODULE_RX), isIndirect(true)
{
	bladerf_devinfo devinfo;
	BladeError::check(bladerf_get_devinfo(open_device, &devinfo), __FILE__, __LINE__);

	this->devinfo = devinfo;

	stringstream ss;
	ss << devinfo.serial;
	serial = ss.str();
}
// will add proper copy and assignment later.
GpsComm::GpsComm(const GpsComm& ref)
	: handle(0), devinfo(), isOpen(false), null(true), activeModule(BLADERF_MODULE_RX), isIndirect(false)
{
	throw BladeError("Can NOT copy GpsComm object. yet...", -1);
}
void GpsComm::load(bladerf_devinfo& devinfo)
{
	if (isOpen)
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
void GpsComm::setActiveModule(bladerf_module module)
{
	activeModule = module;
}


GpsComm::~GpsComm()
{
	if (isOpen && !isIndirect)
	{
		close();
	}
}

string GpsComm::getSerial(){
	return serial;
}
bladerf_devinfo GpsComm::getInfo(){
	return devinfo;
}

bladerf* GpsComm::getHandle()
{
	if (!isOpen || !handle)
	{
		BladeError::check(-1, "GpsComm not opened, no handle available.");
		return 0;
	}
	return handle;
}
bool GpsComm::open()
{
	cout << " >> Opening Device... [" << serial << "]" << endl;
	if (!isOpen)
	{
		int e = bladerf_open_with_devinfo(&handle, &devinfo);
		if (handle)
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
bool GpsComm::close()
{
	cout << " >> Closing Device...[" << serial << "]" << endl;
	if (isOpen && handle)
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

void GpsComm::loadFPGAImage(std::string fpgapath)
{
	// cout << " (!) Loading FPGA [" << fpgapath.c_str() << "]... ";
	BladeError::check(  bladerf_load_fpga(handle, fpgapath.c_str()), "Unable to load FPGA Image...");
}
void GpsComm::setModuleState(bladerf_module mod, bool state)
{
	BladeError::check(bladerf_enable_module(handle, mod, state), __FILE__, __LINE__);
}


uint32_t GpsComm::getConfigGPIO()
{
	uint32_t value = 0;
	BladeError::check(bladerf_config_gpio_read(getHandle(), &value), __FILE__, __LINE__);
	return value;
}
bool GpsComm::getConfigGPIO(uint32_t index)
{
	return getbit(getConfigGPIO(), index);
}
void GpsComm::setConfigGPIO(uint32_t val)
{
	BladeError::check(bladerf_config_gpio_write(getHandle(), val), __FILE__, __LINE__);
}
void GpsComm::setConfigGPIO(uint32_t index, bool val)
{
	uint32_t reg = getConfigGPIO();	//save old
	reg = setbit(reg, index, val);
	setConfigGPIO(reg);		//write new
}








//----------- Cleaner NIOS IO ---------------
uint32_t GpsComm::niosRPC(NiosRPC addr, uint32_t send){
	uint32_t resp = 0;
	BladeError::check(bladerf_nios_rpc(handle, addr, send, &resp), __FILE__, __LINE__);
	return resp;
}





uint32_t GpsComm::xboardExpressRead(uint8_t addr, uint8_t* data){
	uint32_t count = 0;
	BladeError::check(bladerf_xb_express_read(handle, addr, data, &count), __FILE__, __LINE__);
	return count;
}

// ----------- [ XB SPI link  ] -------
// Sends 'send' and returns the 8bit reply.
uint8_t GpsComm::xboardSPI(uint8_t send)
{
	uint8_t resp = 0;
	BladeError::check(bladerf_xb_gps_spi(handle, send, &resp), __FILE__, __LINE__);
	//cout << "SPI RESPONSE: " << resp  << endl;
	return resp;
}

uint32_t GpsComm::xboardUARTRead()
{
	uint32_t b = 0;
	BladeError::check(bladerf_xb_uart_read(handle, &b), __FILE__, __LINE__);
	return b;
}
void GpsComm::xboardUARTWrite(char val)
{
	BladeError::check(bladerf_xb_uart_write(handle, val), __FILE__, __LINE__);
}
void GpsComm::xboardUARTBaud(uint16_t baud)
{
	BladeError::check(bladerf_xb_uart_baud_write(handle, baud), __FILE__, __LINE__);
}
uint32_t GpsComm::xboardUARTHasData()
{
	uint32_t hasdata = 0;
	BladeError::check(bladerf_xb_uart_hasdata(handle, &hasdata), __FILE__, __LINE__);
	return hasdata;
}


// ---------------- [ XB GPIO manip ] --------------
uint32_t GpsComm::getXBGPIO()
{
	uint32_t value = 0;
	BladeError::check(bladerf_expansion_gpio_read(getHandle(), &value), __FILE__, __LINE__);
	return value;
}
bool GpsComm::getXBGPIO(uint32_t index)
{
	return getbit(getXBGPIO(), index);
}
void GpsComm::setXBGPIO(uint32_t value)
{
	BladeError::check(bladerf_expansion_gpio_write(getHandle(), value), __FILE__, __LINE__);
}
void GpsComm::setXBGPIO(uint32_t index, bool val)
{
	uint32_t reg = getXBGPIO();	//save current
	reg = setbit(reg, index, val);
	setXBGPIO(reg);		//write new
}

// 1 = OUTPUT, 0 = INPUT
uint32_t GpsComm::getXBGPIODir()
{
	uint32_t value = 0;
	BladeError::check(bladerf_expansion_gpio_dir_read(getHandle(), &value), __FILE__, __LINE__);
	return value;
}
bool GpsComm::getXBGPIODir(uint32_t index)
{
	return getbit(getXBGPIODir(), index);
}
void GpsComm::setXBGPIODir(uint32_t value)
{
	BladeError::check(bladerf_expansion_gpio_dir_write(getHandle(), value), __FILE__, __LINE__);
}
void GpsComm::setXBGPIODir(uint32_t index, bool val)
{
	uint32_t reg = getXBGPIODir();	//save old
	reg = setbit(reg, index, val);
	setXBGPIODir(reg);		//write new
}


bool GpsComm::getbit(uint32_t field, int i) //from 1
{
	field = (field & (1 << (i - 1))) >> (i - 1);
	return field != 0;
}
uint32_t GpsComm::setbit(uint32_t field, int i, bool val) // from 1
{
	field = field & (~(1 << (i - 1)));		//zeros the index
	field = field | (val << (i - 1));			//sets it t/f
	return field;
}
// --------------------------------------------------

uint32_t GpsComm::getSampleRate()
{
	unsigned int sr = 0;
	BladeError::check(bladerf_get_sample_rate(getHandle(), activeModule, &sr), __FILE__, __LINE__);
	return sr;
}
void GpsComm::setFrequency(uint32_t f)
{
	BladeError::check(bladerf_set_frequency(getHandle(), activeModule, f), __FILE__, __LINE__);
}
uint32_t GpsComm::setBandwidth(uint32_t bw)
{
	uint32_t actualbw;
	BladeError::check(bladerf_set_bandwidth(getHandle(), activeModule, bw, &actualbw), __FILE__, __LINE__);
	return actualbw;
}

uint32_t GpsComm::getFrequency()
{
	uint32_t actual;
	BladeError::check(bladerf_get_frequency(getHandle(), activeModule, &actual), __FILE__, __LINE__);
	return actual;
}
uint32_t GpsComm::getBandwidth()
{
	uint32_t actual;
	BladeError::check(bladerf_get_bandwidth(getHandle(), activeModule, &actual), __FILE__, __LINE__);
	return actual;
}

void GpsComm::initializeForCollection()
{
	uint32_t sampling_rate = 30720000;
	uint32_t blade_sampling_rate = 0;
	uint32_t frequency = 1960000000;
	uint32_t bandwidth = 10000000;
	uint32_t blade_bandwidth = 0;

	BladeError::check(bladerf_set_sample_rate(handle, BLADERF_MODULE_RX, sampling_rate, &blade_sampling_rate), __FILE__, __LINE__);
	BladeError::check(bladerf_set_bandwidth(handle, BLADERF_MODULE_RX, bandwidth, &blade_bandwidth), __FILE__, __LINE__);
	BladeError::check(bladerf_set_frequency(handle, BLADERF_MODULE_RX, frequency), __FILE__, __LINE__);
	BladeError::check(bladerf_set_lna_gain(handle, BLADERF_LNA_GAIN_MAX)), __FILE__, __LINE__;
	BladeError::check(bladerf_set_rxvga1(handle, 30), __FILE__, __LINE__);
	BladeError::check(bladerf_set_rxvga2(handle, 15), __FILE__, __LINE__);

	enableRXModule();
}

void GpsComm::collectDummySnapshot() {
	struct sample
	{
		int16_t i;
		int16_t q;
	};
	static std::vector<sample> buffer(1024000 * 3);
	bladerf_metadata metadata;
	uint32_t sampling_rate = (rand() % 2) ? 30720000 : 15360000;
	uint32_t blade_sampling_rate = 0;
	uint32_t frequency = 1960000000 + (100000 * (rand() % 10));
	uint32_t bandwidth = 10000000;
	uint32_t blade_bandwidth = 0;
	static uint32_t lna_gain = 0;
	static uint32_t vga1 = 0;
	static uint32_t vga2 = 0;
	uint32_t gpio = 0;

	// Change collection parameters to simulate sweeping freqs.
	BladeError::check(bladerf_set_sample_rate(handle, BLADERF_MODULE_RX, sampling_rate, &blade_sampling_rate), __FILE__, __LINE__);
	BladeError::check(bladerf_set_bandwidth(handle, BLADERF_MODULE_RX, bandwidth, &blade_bandwidth), __FILE__, __LINE__);
	BladeError::check(bladerf_set_frequency(handle, BLADERF_MODULE_RX, frequency), __FILE__, __LINE__);
	BladeError::check(bladerf_set_lna_gain(handle, static_cast<bladerf_lna_gain>(lna_gain++ % 2 + 1)), __FILE__, __LINE__);
	BladeError::check(bladerf_set_rxvga1(handle, vga1++ % 25 + 5), __FILE__, __LINE__);
	BladeError::check(bladerf_set_rxvga2(handle, vga2++ % 30), __FILE__, __LINE__);
	BladeError::check(bladerf_expansion_gpio_read(handle, &gpio), __FILE__, __LINE__);
	// 0x070007f0 is our mask.  It corresponds to the pins that we use to control the switches for the filter paths.
	gpio &= ~0x070007f0;
	gpio |= (rand() & 0x070007f0);
	BladeError::check(bladerf_expansion_gpio_write(handle, gpio), __FILE__, __LINE__);

	BladeError::check(bladerf_sync_rx(handle, &buffer.at(0), buffer.size(), &metadata, 1500), __FILE__, __LINE__);

	// Confirm the gpio pins were correctly set and kept their values.
	uint32_t new_gpio = 0;
	BladeError::check(bladerf_expansion_gpio_read(handle, &new_gpio), __FILE__, __LINE__);
	if((new_gpio & 0x070007f0) != (gpio & 0x070007f0))
		throw std::runtime_error("GPIO XB pins did not hold their value.");
}

void GpsComm::enableRXModule()
{
	int rx_sync_num_transfers_ = 5;
	int rx_sync_num_buffers_ = 6;
	int rx_sync_buffer_size_ = 4096;
	int rx_sync_timeout_ = 5000;
	BladeError::check(bladerf_sync_config(handle, BLADERF_MODULE_RX, BLADERF_FORMAT_SC16_Q11,
		rx_sync_num_buffers_, rx_sync_buffer_size_, rx_sync_num_transfers_, rx_sync_timeout_), __FILE__, __LINE__);
	BladeError::check(bladerf_enable_module(handle, BLADERF_MODULE_RX, true), __FILE__, __LINE__);
}

void GpsComm::disableRXModule()
{
	BladeError::check(bladerf_enable_module(handle, BLADERF_MODULE_RX, false), __FILE__, __LINE__);
}
