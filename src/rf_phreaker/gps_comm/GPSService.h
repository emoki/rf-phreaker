/*
 * GPSService.h
 *
 *  Created on: Aug 14, 2014
 *      Author: ck
 */

#ifndef GPSSERVICE_H_
#define GPSSERVICE_H_

#include <string>
#include <chrono>
#include <functional>
#include "GPSFix.h"
#include "NMEAParser.h"
#include "Event.h"

namespace rf_phreaker { namespace gps_comm {

class GPSService {
private:
	std::chrono::high_resolution_clock hostClock;
public:
	NMEAParser parser;
	GPSFix fix;

	GPSService();
	virtual ~GPSService();


	void readbyte(uint8_t b);		//must include  \r\n
	void readline(std::string s);	//without '\r\n'

	Event<void(bool)> onLockStateChanged;	// user assignable handler, called whenever lock changes

	void initSentenceHandlers();			// sets default handlers for all the parser messages
};


}} 

#endif /* GPSSERVICE_H_ */
