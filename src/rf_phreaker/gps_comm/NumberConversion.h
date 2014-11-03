/*
 * NumberConversion.h
 *
 *  Created on: Aug 14, 2014
 *      Author: ck
 */

#ifndef NUMBERCONVERSION_H_
#define NUMBERCONVERSION_H_

#include <string>
#include <sstream>
#include <stdlib.h>
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace gps_comm {

class NumberConversionError : public gps_comm_error {
public:
	std::string message;
	NumberConversionError(std::string msg)
		: gps_comm_error(msg)
		, message(msg){};
	virtual ~NumberConversionError(){};
};




double parseDouble(std::string s);
int64_t parseInt(std::string s, int radix = 10);

//void NumberConversion_test();

}}



#endif /* NUMBERCONVERSION_H_ */
