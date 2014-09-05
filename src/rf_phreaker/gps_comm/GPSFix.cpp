/*
 * WNGPSFix.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: me
 */

#include "GPSFix.h"
#include <cmath>
#include <string>
#include <sstream>

using namespace std;
using namespace std::chrono;

namespace rf_phreaker { namespace gps_comm {

string GPSSatellite::toString(){
	stringstream ss;

	ss << " > [Satellite  PRN:" << prn
			<< "  SNR:" << snr
			<< "  azimuth:" << azimuth
			<< "  elivation:" << elevation
			<< "]";

	return ss.str();
}
GPSSatellite::operator std::string(){
	return toString();
}



GPSFix::GPSFix() {

	scanningDeviceSerial = "";

	fixQuality = 0; //void

	haslock 		= 0;
	timestamp 		= 0;

	latitude 		= 0;
	longitude		= 0;
	speed			= 0;
	altitude = 0;
	trackingSatellites = 0;
	visibleSatellites = 0;


}

GPSFix::~GPSFix() {
	// TODO Auto-generated destructor stub
}

milliseconds GPSFix::timeSinceLastFix(){
	return duration_cast<milliseconds>(clock.now() - hostTimeAtFix);
}

std::string GPSFix::toString(){
	stringstream ss;
	ss << "=== GPS FIX ===" << endl
			<< " Status: " << ((haslock)?"LOCK!":"SEARCHING...") << endl
			<< " Scanning Device: " << scanningDeviceSerial << endl
			<< " Satellites: " << visibleSatellites << "(visible); " << trackingSatellites << "(tracking);" << endl
			<< " < Fix Details >" << endl
			<< "   Age: " << timeSinceLastFix().count() << " ms" << endl
			<< "   Fix Quality: " << (int)fixQuality << endl
			<< "   Timestamp: " << timestamp << endl
			<< "   Lat/Lon: " << latitude << " deg, " << longitude << " deg" << endl
			<< "   Altitude: " << altitude << " m"<< endl
			<< "   Speed: " << speed << " m/s" << endl;
	ss << " < Satellites >" << endl;
	if(satellites.size() == 0){
		ss << " > No satellites.";
	}
	for(size_t i = 0; i < satellites.size(); i++){
		ss << " > [" << i << "]" << satellites[i].toString();
	}

	return ss.str();
}
GPSFix::operator std::string(){
	return toString();
}

GPSFix::operator gps(){
	gps raw;

	raw.lock_ 		= haslock;
	raw.coordinated_universal_time_ = timestamp;
	raw.scanner_id_ = (scanner_serial_type)scanningDeviceSerial;		//blade serial number...
	raw.raw_status_ = 0;		// ?? not sure what that is

	raw.latitude_ 	= latitude;
	raw.longitude_ 	= longitude;
	raw.speed_		= (int32_t)speed;
	raw.tracking_satellites_	= trackingSatellites;
	raw.visible_satellites_		= visibleSatellites;

	return raw;
}

}} 
