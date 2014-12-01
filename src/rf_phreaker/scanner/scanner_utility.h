#pragma once

//#include <cstdlib>
//#include "rf_phreaker/scanner/scanner_types.h"
#include "libbladeRF.h"

namespace rf_phreaker { namespace scanner {

std::string to_string(int usb_speed)
{
	switch((bladerf_dev_speed)usb_speed) {
	case BLADERF_DEVICE_SPEED_HIGH:
		return "USB_HI_SPEED";
	case BLADERF_DEVICE_SPEED_SUPER:
		return "USB_SUPER_SPEED";
	case BLADERF_DEVICE_SPEED_UNKNOWN:
	default:
		return "UNKNOWN_SPEED";
	}
}

std::string usb_backend_to_string(int usb_backend) {
	switch((bladerf_backend)usb_backend) {
	case BLADERF_BACKEND_ANY: /**< "Don't Care" -- use any available backend */
		return "BLADERF_BACKEND_ANY";
	case BLADERF_BACKEND_LINUX:  /**< Linux kernel driver */
		return "BLADERF_BACKEND_LINUX";
	case BLADERF_BACKEND_LIBUSB: /**< libusb */
		return "BLADERF_BACKEND_LIBUSB";
	case BLADERF_BACKEND_CYPRESS: /**< CyAPI */
		return "BLADERF_BACKEND_CYPRESS";
	case BLADERF_BACKEND_DUMMY: /**< Dummy used for development purposes */
		return "BLADERF_BACKEND_DUMMY";
	default:
		return "UNKNOWN_USB_BACKEND";
	}
}

// hz per dac lsb
double dac_trim_hz_per_lsb_coefficient() {
	double vref = 2.5;									// dac Vref
	double dac_v_lsb = vref / (double)(1 << 16);		// voltage per lsb = vref / 2^n		== 0.03814697265625 mV

	double vctcxo_frequency_tuning_range_ppm = 7.25*2.0;	// ASVTX-12 minimum +/- 5ppm and maximum +/- 9.5  avg would be 
	double vctcxo_voltage_tuning_range = 2.0;				// +0.4v - +2.4v
	double vctcxo_f_ppm = 38.4;								// 38.4 Mhz -> ppm -> 38.4 hz

	// 5ppm ~ 0.007 hz;  9ppm ~ 0.013 hz;
	double tune_hz_per_dac_lsb = vctcxo_frequency_tuning_range_ppm * vctcxo_f_ppm / vctcxo_voltage_tuning_range * dac_v_lsb;

	return tune_hz_per_dac_lsb;
}

//class hex_conversion
//{
//public:
//	template<size_t Size>
//	static long convert_hex(const buf_type::iterator &it)
//	{
//		char tmp[Size];
//		char *endptr;
//		std::copy(it, it + Size, tmp);
//		return strtol(tmp, &endptr, 16);
//	}
//	template<size_t Size>
//	static long convert_hex(const char* ptr)
//	{
//		char tmp[Size];
//		char *endptr;
//		std::copy(ptr, ptr + Size, tmp);
//		return strtol(tmp, &endptr, 16);
//	}
//
//	template<size_t Size>
//	static std::string convert_hex(int value)
//	{
//		return std::move(str(boost::format("%x") % boost::io::group(std::setw(Size), std::setfill('0'), value)));
//	}
//};

}}