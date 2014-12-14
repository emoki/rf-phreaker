/*
 * NMEAParser.h
 *
 *  Created on: Aug 12, 2014
 *      Author: ck
 */

#ifndef NMEAPARSER_H_
#define NMEAPARSER_H_


#include "Event.h"
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include "rf_phreaker/common/exception_types.h"



//read class definition for info
#define NMEA_PARSER_MAX_BUFFER_SIZE 2000





namespace rf_phreaker { namespace gps_comm {

class NMEAParseError : public gps_comm_error {
public:
	std::string message;

	NMEAParseError(std::string msg)
		: gps_comm_error(msg)
		, message(msg) {};
	virtual ~NMEAParseError(){};

};




class NMEAParser;

class NMEASentence{
	friend NMEAParser;
private:
	bool isvalid;
public:
	std::string text;			//whole plaintext of the received command
	std::string name;			//name of the command
	std::vector<std::string> parameters;	//list of parameters from the command
	std::string checksum;
	uint8_t parsedChecksum;
	uint8_t calculatedChecksum;

	enum MessageID {
		GGA = 0,
		GLL = 1,
		GSA = 2,
		GSV = 3,
		RMC = 4,
		VTG = 5,
		ZDA = 8,
		Unknown = 9
	};
public:
	NMEASentence();
	NMEASentence(std::string text);
	virtual ~NMEASentence();

	bool checksumOK() const;
	bool valid();
	std::string paramsToString() {
		std::string str;
		size_t size = parameters.size();
		for(size_t i = 0; i < size; ++i) {
			str += parameters[i];
			if(i + 1 < size)
				str += ",";
		}
		return str;
	}
};


class NMEAParser {
private:
	std::unordered_map<std::string, std::function<void(NMEASentence)>> eventTable;
	std::string buffer;
	uint32_t maxbuffersize;		//limit the max size if no newline ever comes... Prevents huge buffer string internally

	void parseText(NMEASentence& nmea, std::string s);		//fills the given NMEA sentence with the results of parsing the string.
public:
	//std::string newline;

	NMEAParser();
	virtual ~NMEAParser();

	static uint8_t calculateChecksum(std::string);		// returns checksum of string -- XOR
	Event<void(NMEASentence)> onCommand;				// called every time parser receives any NMEA sentence
	void setCommandHandler(std::string cmdKey, std::function<void(NMEASentence)> handler);	//one handler called for any named sentence where name is the "cmdKey"
	void handleTextCommand(std::string cmd);			// called when parser receives a sentence from the byte stream. Can also be called by user to inject sentences.
	void parseByte(uint8_t b);							// handles bytes from the byte stream

	bool log;
};

}} 

#endif /* NMEAPARSER_H_ */
