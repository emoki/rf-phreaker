/*
 * GPSService.h
 *
 *  Created on: Aug 14, 2014
 *      Author: me
 */

#ifndef GPSSERVICE_H_
#define GPSSERVICE_H_

#include <string>
#include <chrono>
#include <functional>
#include "GPSFix.h"
#include "NMEAParser.h"

namespace rf_phreaker { namespace gps_comm {

class GPSService {
private:
	std::chrono::high_resolution_clock hostClock;
public:
	NMEAParser parser;

	GPSFix fix;

	GPSService();
	virtual ~GPSService();

	void readbyte(uint8_t b);
	void readline(std::string s);	//with or without '\r\n'

	void initSentenceHandlers();
};

void GPSService_test();

}} 

#endif /* GPSSERVICE_H_ */
