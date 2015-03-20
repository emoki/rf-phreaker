/*
 * BladeError.h
 *
 *  Created on: Mar 28, 2014
 *      Author: ck
 */

#ifndef BladeError_H_
#define BladeError_H_

#include <string>
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace gps_comm {
    
class BladeError : public gps_comm_error {
public:
	int code;
	std::string message;

public:
	BladeError(std::string msg, int code);
	virtual ~BladeError();
	std::string toString();

	static bool check(int code, const std::string &file = "", int line = 0);
	static bool check(int code, std::string &msg);
};

}}

#endif /* BladeError_H_ */
