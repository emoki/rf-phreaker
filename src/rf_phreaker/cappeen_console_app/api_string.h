#pragma once

#include <string>

namespace cappeen_scanner {


class api_string
{
public:
	api_string(long number, const char *str)
		: number_(number)
		, str_(str)
	{}

	long number_;
	std::string str_;
};


}