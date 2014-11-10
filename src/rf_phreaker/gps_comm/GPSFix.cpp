/*
 * WNGPSFix.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: ck
 */

#include "GPSFix.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include "boost/date_time.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

using namespace std;
using namespace std::chrono;

namespace rf_phreaker { namespace gps_comm {

	// ===========================================================
	// ======================== GPS SATELLITE ====================
	// ===========================================================

	string GPSSatellite::toString(){
		stringstream ss;

		ss << "[PRN: " << prn << " \t"
			<< "   SNR:   " << snr << " dB  \t"
			<< "   Azimuth: " << azimuth << " deg \t"
			<< "   Elevation: " << elevation << " deg \t"
			<< "]";

		return ss.str();
	}
	GPSSatellite::operator std::string(){
		return toString();
	}



	// =========================================================
	// ======================== GPS ALMANAC ====================
	// =========================================================

	void GPSAlmanac::clear(){
		lastPage = 0;
		totalPages = 0;
		processedPages = 0;
		visibleSize = 0;
		satellites.clear();
	}
	void GPSAlmanac::updateSatellite(GPSSatellite sat){
		if (satellites.size() > visibleSize)
		{	//we missed the new almanac start page, start over.
			clear();
		}

		//satellites.push_back(sat);
	}
	double GPSAlmanac::percentComplete(){
		if (totalPages == 0){
			return 0.0;
		}

		return ((double)processedPages) / ((double)totalPages) * 100.0;
	}
	double GPSAlmanac::averageSNR(){

		double avg = 0;
		double relevant = 0;
		for (size_t i = 0; i < satellites.size(); i++){
			if (satellites[i].snr > 0){
				relevant += 1.0;
			}
		}

		for (size_t i = 0; i < satellites.size(); i++){
			if (satellites[i].snr > 0){
				avg += satellites[i].snr / relevant;
			}
		}

		return avg;
	}
	double GPSAlmanac::minSNR(){
		double min = 9999999;
		if (satellites.size() == 0){
			return 0;
		}
		int32_t num_over_zero = 0;
		for (size_t i = 0; i < satellites.size(); i++){
			if (satellites[i].snr > 0){
				num_over_zero++;
				if (satellites[i].snr < min){
					min = satellites[i].snr;
				}
			}
		}
		if (num_over_zero == 0){
			return 0;
		}
		return min;
	}

	double GPSAlmanac::maxSNR(){
		double max = 0;
		for (size_t i = 0; i < satellites.size(); i++){
			if (satellites[i].snr > 0){
				if (satellites[i].snr > max){
					max = satellites[i].snr;
				}
			}
		}
		return max;
	}




	// ===========================================================
	// ======================== GPS TIMESTAMP ====================
	// ===========================================================


	GPSTimestamp::GPSTimestamp(){
		hour = 0;
		min = 0;
		sec = 0;

		month = 1;
		day = 1;
		year = 1970;

		rawtime = 0;
		rawdate = 0;
	};

	std::string GPSTimestamp::monthName(uint32_t index){
		if (index < 1 || index > 12){
			std::stringstream ss;
			ss << "[month:" << index << "]";
			return ss.str();
		}

		std::string names[] = {
			"January",
			"February",
			"March",
			"April",
			"May",
			"June",
			"July",
			"August",
			"September",
			"October",
			"November",
			"December"
		};
		return names[index - 1];
	};

	time_t GPSTimestamp::gettimet() {
		using namespace boost::posix_time;
		using namespace boost::gregorian;
		static ptime epoch(boost::gregorian::date(1970, 1, 1));
		try {
			ptime now(date(year, month, day), time_duration(hour, min, (int32_t)sec));
			time_duration::sec_type seconds = (now - epoch).total_seconds();
			return time_t(seconds);
		}
		catch(const std::exception &) {
			return 0;
		}
	}

	void GPSTimestamp::settime(double raw_ts){
		rawtime = raw_ts;

		hour = (int32_t)trunc(raw_ts / 10000.0);
		min = (int32_t)trunc((raw_ts - hour * 10000) / 100.0);
		sec = raw_ts - min * 100 - hour * 10000;
	}

	//ddmmyy
	void GPSTimestamp::setdate(int32_t raw_date){
		rawdate = raw_date;
		// If uninitialized, use posix time.
		if(rawdate == 0) {
			month = 1;
			day = 1;
			year = 1970;
		}
		else {
			day = (int32_t)trunc(raw_date / 10000.0);
			month = (int32_t)trunc((raw_date - 10000 * day) / 100.0);
			year = raw_date - 10000 * day - 100 * month + 2000;
		}
	}

	std::string GPSTimestamp::toString(){
		std::stringstream ss;
		ss << hour << "h " << min << "m " << sec << "s" << "  " << monthName(month) << " " << day << " " << year;
		return ss.str();
	};







	// =====================================================
	// ======================== GPS FIX ====================
	// =====================================================

	GPSFix::GPSFix() {

		scanningDeviceSerial = "";

		quality = 0; //searching...
		status = 'V';
		type = 1;	//1=none, 2=2d, 3=3d

		haslock = 0;

		dilution = 0;
		horizontalDilution = 0;	// best is 1, >20 is terrible, so 0 means uninitialized
		verticalDilution = 0;
		latitude = 0;
		longitude = 0;
		speed = 0;
		travelAngle = 0;
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
	bool GPSFix::hasEstimate(){
		return (latitude != 0 && longitude != 0) || (quality == 6);
	}
	bool GPSFix::setlock(bool locked){
		if (haslock != locked){
			haslock = locked;
			return true;
		}
		return false;
	}

	bool GPSFix::locked(){
		return haslock;
	}

	// returns meters
	double GPSFix::horizontalAccuracy(){
		// horizontal 2drms 95% = 4.0  -- from origin datasheet
		return 4.0 * horizontalDilution;
	}
	//returns meters
	double GPSFix::verticalAccuracy(){
		// Vertical 2drms 95% = 6.0  -- from origin datasheet
		return 6.0 * verticalDilution;
	}

	std::string GPSFix::travelAngleToCompassDirection(double deg){

		//normalize, just in case
		int32_t c = (int32_t)round(deg / 360.0 * 8.0);
		int32_t r = c % 8;
		if (r < 0){
			r = 8 + r;
		}

		std::string dirs[] = {
			"North",
			"North East",
			"East",
			"South East",
			"South",
			"South West",
			"West",
			"North West",
			"North"
		};

		return dirs[r];
	};

	std::string GPSFix::toString(){
		stringstream ss;
		ios_base::fmtflags oldflags = ss.flags();

		ss << "/======================== GPS FIX =============================" << endl
			<< "| Status: \t\t" << ((haslock) ? "LOCK!" : "SEARCHING...") << endl
			<< "| Scanning Device: \t" << scanningDeviceSerial << endl
			<< "| Satellites: \t\t" << trackingSatellites << " (tracking) of " << visibleSatellites << " (visible)" << endl
			<< "| < Fix Details >" << endl
			<< "|   Age:             " << timeSinceLastFix().count() << " ms" << endl
			<< "|   Timestamp:       " << timestamp.toString() << "   UTC    (raw: " << timestamp.rawtime << " time, " << timestamp.rawdate << " date)" << endl
			<< "|   Raw Status:      " << status << "  (V=Void, A=Active)" << endl
			<< "|   Type:            " << (int)type << "  (1=none, 2=2D, 3=3D)" << endl
			<< "|   Quality:         " << (int)quality << "  (0=invalid, 1=std fix, 6=estimate)" << endl
			<< "|   Lat/Lon (N,E):   " << setprecision(6) << fixed << latitude << ", " << longitude << endl;

		ss.flags(oldflags);  //reset

		ss << "|   DOP (P,H,V):     " << dilution << ",   " << horizontalDilution << ",   " << verticalDilution << endl
			<< "|   Accuracy(H,V):   " << horizontalAccuracy() << " m,   " << verticalAccuracy() << " m" << endl;

		ss << "|   Altitude:        " << altitude << " m" << endl
			<< "|   Speed:           " << speed << " km/h" << endl
			<< "|   Travel Dir:      " << travelAngle << " deg  [" << travelAngleToCompassDirection(travelAngle) << "]" << endl
			<< "|   SNR:             avg: " << almanac.averageSNR() << " dB   [min: " << almanac.minSNR() << " dB,  max:" << almanac.maxSNR() << " dB]" << endl;

		ss << "| < Almanac (" << almanac.percentComplete() << "%) >" << endl;
		if (almanac.satellites.size() == 0){
			ss << "| > No satellite info in almanac." << endl;
		}
		for (size_t i = 0; i < almanac.satellites.size(); i++){
			ss << "|   [" << (i + 1) << "] \t" << almanac.satellites[i].toString() << endl;
		}
		ss << "\\==============================================================";

		return ss.str();
	}
	GPSFix::operator std::string(){
		return toString();
	}

	GPSFix::operator gps(){
		gps raw;

		raw.lock_ = haslock;
		raw.coordinated_universal_time_ = timestamp.gettimet();		//will truncate the milliseconds...
		raw.scanner_id_ = scanningDeviceSerial;		//blade serial number...
		raw.raw_status_ = status;		// ?? not sure what that is, putting the Origin status 'A'/'V' here

		raw.latitude_ = latitude;
		raw.longitude_ = longitude;
		raw.speed_ = (int32_t)round(speed);
		raw.tracking_satellites_ = trackingSatellites;
		raw.visible_satellites_ = visibleSatellites;

		return raw;
	}

}} 
