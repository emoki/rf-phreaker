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