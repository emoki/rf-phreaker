/*
 * BladeError.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: ck
 */

#include "BladeError.h"
#include <libbladeRF.h>
#include <sstream>
#include "rf_phreaker/common/common_utility.h"

using namespace std;
using namespace rf_phreaker::gps_comm;

BladeError::BladeError(string msg, int code) 
	: gps_comm_error(msg, code)
	, code(code)
	, message(msg)
{}

bool BladeError::check(int code, string &msg)
{
	if(code != 0)
	{
		BladeError e(msg,code);
        throw e;
	}
	return code != 0;
}
bool BladeError::check(int code, const std::string &file, int line)
{
	if(code != 0) {
		std::string tmp = "[" + split_file_name(file) + " L: " + std::to_string(line) + "] Device error: " + bladerf_strerror(code);
		return BladeError::check(code, tmp);
	}
	else return false;
}
string BladeError::toString()
{
	stringstream ss;
	ss << "DeviceError(" << this->code << "): " << this->message;
	return ss.str();
}
BladeError::~BladeError() {
	// TODO Auto-generated destructor stub
}

