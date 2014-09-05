/*
 * BladeError.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: me
 */

#include "BladeError.h"
#include <sstream>

using namespace std;
using namespace rf_phreaker::gps_comm;

BladeError::BladeError(string msg, int code) 
	: gps_comm_error(msg, code)
	, code(code)
{
	stringstream ss;

	ss << "ERROR: " << BladeError::getLibErrorMessage(code)
		<< endl << msg;

	this->message = ss.str();
}
string BladeError::getLibErrorMessage(int code) {
	// TODO Auto-generated constructor stub
	stringstream ss;


	switch(code)
	{
	case 0: return string("SUCCESS");
	case -1: return string("ERR_UNEXPECTED: Unexpected failure occured.");
	case -2: return string("ERR_RANGE: Provided parameter is out of range.");
	case -3: return string("ERR_INVAL: Invalid operation/parameter.");
	case -4: return string("ERR_MEM: Memory allocation Error.");
	case -5: return string("ERR_IO: File/Device IO Error.");
	case -6: return string("ERR_TIMEOUT: Operation timed out.");
	case -7: return string("ERR_NODEV: No device available.");
	case -8: return string("ERR_UNSUPPORTED: Operation not supported.");
	case -9: return string("ERR_MISALIGNED: Misaligned flash access.");
	case -10: return string("ERR_CHECKSUM: Invalid checksum.");
	default:
		ss << "Unknown Error Code: (" << code << ").";
		return ss.str();
	}
}

bool BladeError::check(int code, string msg)
{
	if(code != 0)
	{
		BladeError e(msg,code);
        throw e;
	}
	return code != 0;
}
bool BladeError::check(int code)
{
	return BladeError::check(code, "");
}
string BladeError::toString()
{
	stringstream ss;
	ss << "BladeError(" << this->code << "): " << this->message;
	return ss.str();
}
BladeError::~BladeError() {
	// TODO Auto-generated destructor stub
}

