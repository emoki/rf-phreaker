#pragma once

#include <cstdlib>
#include "rf_phreaker/scanner/scanner_types.h"


namespace rf_phreaker { namespace scanner {

class hex_conversion
{
public:
	template<size_t Size>
	static long convert_hex(const buf_type::iterator &it)
	{
		char tmp[Size];
		char *endptr;
		std::copy(it, it + Size, tmp);
		return strtol(tmp, &endptr, 16);
	}
	template<size_t Size>
	static long convert_hex(const char* ptr)
	{
		char tmp[Size];
		char *endptr;
		std::copy(ptr, ptr + Size, tmp);
		return strtol(tmp, &endptr, 16);
	}

	template<size_t Size>
	static std::string convert_hex(int value)
	{
		return std::move(str(boost::format("%x") % boost::io::group(std::setw(Size), std::setfill('0'), value)));
	}
};

}}