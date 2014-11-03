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