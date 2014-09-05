/*
 * NMEAParser.h
 *
 *  Created on: Aug 12, 2014
 *      Author: me
 */

#ifndef NMEAPARSER_H_
#define NMEAPARSER_H_


#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace gps_comm {

class NMEAParseError : public gps_comm_error {
public:
	std::string message;

	NMEAParseError(std::string msg)
		: gps_comm_error(msg)
		, message(msg) {};
	virtual ~NMEAParseError(){};

};

//ok this should actually be called NMEASentence ... but I already wrote a bunch
class NMEACommand{
private:
	bool isvalid;
public:
	std::string text;			//whole plaintext of the received command
	std::string name;			//name of the command
	std::vector<std::string> parameters;	//list of parameters from the command
	std::string checksum;
public:
	NMEACommand();
	NMEACommand(std::string text);
	virtual ~NMEACommand();

	bool valid();
	bool parseText(std::string s);

};


class NMEAParser {
private:
	std::unordered_map<std::string, std::function<void(NMEACommand)>> eventTable;
	std::string buffer;

	NMEACommand analyzeCommandString(std::string);
public:
	//std::string newline;
	std::function<void(NMEACommand)> onCommand;

	NMEAParser();
	virtual ~NMEAParser();

	void handleTextCommand(std::string cmd);
	void parseByte(uint8_t b);
	void setCommandHandler(std::string cmdKey, std::function<void(NMEACommand)> handler);

	bool log;
};

}} 

#endif /* NMEAPARSER_H_ */
