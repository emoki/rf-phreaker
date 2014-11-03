/*
 * BladeError.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: ck
 */

#include "BladeError.h"
#include <libbladeRF.h>
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
	stringstream ss;
	/*  ---------- libbladerf.h --------- 9/5/2014
	#define BLADERF_ERR_UNEXPECTED  (-1)  //< An unexpected failure occurred
	#define BLADERF_ERR_RANGE       (-2)  //< Provided parameter is out of range
	#define BLADERF_ERR_INVAL       (-3)  //< Invalid operation/parameter
	#define BLADERF_ERR_MEM         (-4)  //< Memory allocation error
	#define BLADERF_ERR_IO          (-5)  //< File/Device I/O error
	#define BLADERF_ERR_TIMEOUT     (-6)  //< Operation timed out
	#define BLADERF_ERR_NODEV       (-7)  //< No device(s) available
	#define BLADERF_ERR_UNSUPPORTED (-8)  //< Operation not supported
	#define BLADERF_ERR_MISALIGNED  (-9)  //< Misaligned flash access
	#define BLADERF_ERR_CHECKSUM    (-10) //< Invalid checksum
	#define BLADERF_ERR_NO_FILE     (-11) //< File not found
	#define BLADERF_ERR_UPDATE_FPGA (-12) //< An FPGA update is required
	#define BLADERF_ERR_UPDATE_FW   (-13) //< A firmware update is requied
	*/

	switch (code)
	{
	case 0: return string("SUCCESS!");
	case BLADERF_ERR_UNEXPECTED: 	return string("ERR_UNEXPECTED: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_RANGE: 		return string("ERR_RANGE: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_INVAL: 		return string("ERR_INVAL: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_MEM: 			return string("ERR_MEM: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_IO: 			return string("ERR_IO: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_TIMEOUT: 		return string("ERR_TIMEOUT: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_NODEV: 		return string("ERR_NODEV: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_UNSUPPORTED: 	return string("ERR_UNSUPPORTED: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_MISALIGNED: 	return string("ERR_MISALIGNED: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_CHECKSUM: 		return string("ERR_CHECKSUM: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_NO_FILE: 		return string("ERR_NO_FILE: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_UPDATE_FPGA: 	return string("ERR_UPDATE_FPGA: ") + string(bladerf_strerror(code));
	case BLADERF_ERR_UPDATE_FW: 	return string("ERR_UPDATE_FW: ") + string(bladerf_strerror(code));
	default:
		ss << "Unknown Error Code: (" << code << "). strerror() -> \"" << string(bladerf_strerror(code)) << "\"";
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

