/*
 * NumberConversion.h
 *
 *  Created on: Aug 14, 2014
 *      Author: me
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

double parseDouble(std::string s){
	char* p;
	double d = ::strtod(s.c_str(), &p);
	if( *p != 0){
		std::stringstream ss;
		ss << "NumberConversionError: parseDouble() error in argument \"" << s << "\", '"
			<< *p <<  "' is not a number.";
		throw NumberConversionError(ss.str());
	}
	return d;
}
uint64_t parseInt(std::string s, int radix=10){
	char* p;
#ifdef _WIN32
	uint64_t d = ::_strtoui64(s.c_str(), &p, radix);
#else
	uint64_t d = ::strtoll(s.c_str(), &p, radix);
#endif
	if(*p != 0) {
		std::stringstream ss;
		ss << "NumberConversionError: parseInt() error in argument \"" << s << "\", '"
			<< *p <<  "' is not a number.";
		throw NumberConversionError(ss.str());
	}
	return d;
}

}}
/*
 void NumberConversion_test(){
 	string s;
	try{

		s = "-1.345";
		float f = parseDouble(s);
		cout << s << ": " << f << endl;

		s = "-1.23e-2";
		f = parseDouble(s);
		cout << s << ": " << f << endl;

		// -- fails, ok
		//s = "asd";
		//f = parseDouble(s);
		//cout << s << ": " << f << endl;


		s = "-1234.123";
		long long k = parseInt(s);
		cout << s << ": " << k << endl;

		// -- fails, ok
		s = "asd";
		k = parseInt(s);
		cout << s << ": " << k << endl;
	}
	catch(NumberConversionError& ex){
		cout << ex.message << endl;
	}
 }
 */

#endif /* NUMBERCONVERSION_H_ */
