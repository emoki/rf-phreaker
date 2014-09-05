/*
 * WNGPSFix.h
 *
 *  Created on: Jul 23, 2014
 *      Author: me
 */

#ifndef WNGPSFIX_H_
#define WNGPSFIX_H_

#include <cstdint>
#include <string>
#include <chrono>
#include <vector>
#include "rf_phreaker/common/measurements.h"

namespace rf_phreaker { namespace gps_comm {

class GPSSatellite {
public:
	//satellite data
	double snr;
	double prn;
	double elevation;
	double azimuth;
	// tracking?, inview?
	std::string toString();
	operator std::string();
};

class GPSService;
class GPSFix {
	friend GPSService;

private:
	std::chrono::high_resolution_clock clock;
public:
	GPSFix();
	virtual ~GPSFix();


	std::chrono::high_resolution_clock::time_point hostTimeAtFix;
	std::string scanningDeviceSerial;

	std::vector<GPSSatellite> satellites;

	char fixQuality;
	double altitude;

	bool haslock;
	int64_t timestamp;

	double latitude;
	double longitude;
	double speed;
	int32_t trackingSatellites;
	int32_t visibleSatellites;


	std::chrono::milliseconds timeSinceLastFix();

	std::string toString();
	operator std::string();

	operator struct gps();		//convert to gps struct implicitly, easier to use.
};

}} 

#endif /* WNGPSFIX_H_ */
