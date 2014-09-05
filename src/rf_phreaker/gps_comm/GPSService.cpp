/*
 * GPSService.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: me
 */


#include "GPSService.h"
#include <iostream>
#include "NumberConversion.h"
#include <cmath>

using namespace std;
using namespace std::chrono;

namespace rf_phreaker { namespace gps_comm {

GPSService::GPSService() {
	initSentenceHandlers();

}

GPSService::~GPSService() {
	// TODO Auto-generated destructor stub
}


void GPSService::readbyte(uint8_t b){
	parser.parseByte(b);
}
void GPSService::readline(string line){
	parser.handleTextCommand(line);
}

void GPSService::initSentenceHandlers(){

	// http://www.gpsinformation.org/dale/nmea.htm
	/* used Origin supported sentences...
	 $GPGGA		- time,position,fix data
	 no $GPGLL		- --legacy. origin implements, but not used here
	 $GPGSA		- gps receiver operating mode, satellites used in position and DOP values
	 $GPGSV		- number of gps satellites in view, satellite ID, elevation,azimuth, and SNR
	 $GPRMC		- time,date, position,course, and speed data
	 $GPVTG		- course and speed information relative to the ground
	 $GPZDA		- 1pps timing message
	 $PSRF150	- (proprietary) gps module ok_to_send
	 */
	parser.setCommandHandler("PSRF150",[this](NMEACommand nmea){
		//gps module is ready to send data
	});
	parser.setCommandHandler("GPGGA",[this](NMEACommand nmea){
		/* -- EXAMPLE --
		 	 $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

			Where:
				 GGA          Global Positioning System Fix Data
				index:
				[0] 123519       Fix taken at 12:35:19 UTC
				[1-2] 4807.038,N   Latitude 48 deg 07.038' N
				[3-4] 1131.000,E  Longitude 11 deg 31.000' E
				[5] 1            Fix quality: 0 = invalid
										   1 = GPS fix (SPS)
										   2 = DGPS fix
										   3 = PPS fix
										   4 = Real Time Kinematic
										   5 = Float RTK
										   6 = estimated (dead reckoning) (2.3 feature)
										   7 = Manual input mode
										   8 = Simulation mode
				[6] 08           Number of satellites being tracked
				[7] 0.9          Horizontal dilution of position
				[8-9] 545.4,M      Altitude, Meters, above mean sea level
				[10-11] 46.9,M       Height of geoid (mean sea level) above WGS84
								  ellipsoid
				[12] (empty field) time in seconds since last DGPS update
				[13] (empty field) DGPS station ID number
				[14]  *47          the checksum data, always begins with *
		 */
		try
		{
			if(nmea.parameters.size() < 14){
				throw NumberConversionError("GPS data is missing parameters.");
			}

			this->fix.haslock = false;

			this->fix.timestamp = (int64_t)parseDouble(nmea.parameters[0]);

			// -- not sure what to do about lat/long with the degrees and such
			// LAT
			if(nmea.parameters[1].size() > 0){
				string ps = nmea.parameters[1];
				double pd = parseDouble(ps);

				double deg = floor(pd / 100);				//get ddd from dddmm.xxxx
				double mins = parseDouble(ps.substr(ps.find('.')-2));	//get mm.xxxxx

				deg = deg + mins / 60.0;
				this->fix.latitude = deg;

				this->fix.haslock = true;
			}
			else{
				this->fix.latitude = 0;
			}

			// LONG
			if(nmea.parameters[3].size() > 0){

				string ps = nmea.parameters[3];
				double pd = parseDouble(ps);

				double deg = floor(pd / 100);				//get ddd from dddmm.xxxx
				double mins = parseDouble(ps.substr(ps.find('.')-2));	//get mm.xxxxx

				deg = deg + mins / 60.0;
				this->fix.longitude = deg;

				this->fix.haslock = true;
			}else{
				this->fix.longitude = 0;
			}

			this->fix.fixQuality = (char)parseInt(nmea.parameters[5]);
			this->fix.trackingSatellites = (int32_t)parseInt(nmea.parameters[6]);
			this->fix.altitude = parseDouble(nmea.parameters[8]);

			//update host timestamp
			this->fix.hostTimeAtFix = this->hostClock.now();
		}
		catch(NumberConversionError& ex)
		{
			cout << "GPS Data Bad Format [$GPGGA] :: " + ex.message << endl;
		}

	});
	parser.setCommandHandler("GPGSA",[this](NMEACommand nmea){
		/*  -- EXAMPLE --
		  $GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39

			Where:
				 GSA      Satellite status
				 [0] A        Auto selection of 2D or 3D fix (M = manual)
				 [1] 3        3D fix - values include: 1 = no fix
												   2 = 2D fix
												   3 = 3D fix
				 [2-13] 04,05... PRNs of satellites used for fix (space for 12)
				 [14] 2.5      PDOP (dilution of precision)
				 [15] 1.3      Horizontal dilution of precision (HDOP)
				 [16] 2.1      Vertical dilution of precision (VDOP)
				 [16] *39      the checksum data, always begins with *
		 */


		try
		{
			if(nmea.parameters.size() < 17){
				throw NumberConversionError("GPS data is missing parameters.");
			}

			//parse data...

			//this->fix.haslock = true;
		}
		catch(NumberConversionError& ex)
		{
			cout << "GPS Data Bad Format [$GPGSA] :: " + ex.message << endl;
		}
	});
	parser.setCommandHandler("GPGSV",[this](NMEACommand nmea){
		/*  -- EXAMPLE --
		 $GPGSV,2,1,08,01,40,083,46,02,17,308,41,12,07,344,39,14,22,228,45*75

		Where:
			  GSV          Satellites in view
			  [0] 2            Number of sentences for full data
			  [1] 1            sentence 1 of 2
			  [2] 08           Number of satellites in view

			  [3] 01           Satellite PRN number
			  [4] 40           Elevation, degrees
			  [5] 083          Azimuth, degrees
			  [6] 46           SNR - higher is better
				[...]   for up to 4 satellites per sentence
			  [17] *75          the checksum data, always begins with *
		 */

		try
		{
			if(nmea.parameters.size() < 18){
				throw NumberConversionError("GPS data is missing parameters.");
			}

			this->fix.visibleSatellites = (int32_t)parseInt(nmea.parameters[2]);
			//this->fix.haslock = true;
		}
		catch(NumberConversionError& ex)
		{
			cout << "GPS Data Bad Format [$GPGSV] :: " + ex.message << endl;
		}
	});
	parser.setCommandHandler("GPRMC",[this](NMEACommand nmea){
		/*  -- EXAMPLE ---
		 $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A

		Where:
			 RMC          Recommended Minimum sentence C
			[0] 123519       Fix taken at 12:35:19 UTC
			[1] A            Status A=active or V=Void.
			[2-3] 4807.038,N   Latitude 48 deg 07.038' N
			[4-5] 01131.000,E  Longitude 11 deg 31.000' E
			[6] 022.4        Speed over the ground in knots
			[7] 084.4        Track angle in degrees True
			[8] 230394       Date - 23rd of March 1994
			[9-10] 003.1,W      Magnetic Variation
			[10] *6A          The checksum data, always begins with *
		// NMEA 2.3 includes another field after
		 */

		try
		{
			if(nmea.parameters.size() < 10){
				throw NumberConversionError("GPS data is missing parameters.");
			}

			this->fix.timestamp = parseInt(nmea.parameters[0]);

			// -- not sure what to do about lat/long with the degrees and such
			// this->fix.latitude = parseDouble(nmea.parameters[2]);
			// this->fix.longitude = parseDouble(nmea.parameters[4]);

			this->fix.haslock = true;

			//update host timestamp
			this->fix.hostTimeAtFix = this->hostClock.now();
		}
		catch(NumberConversionError& ex)
		{
			cout << "GPS Data Bad Format [$GPRMC] :: " + ex.message << endl;
		}
	});
	parser.setCommandHandler("GPVTG",[this](NMEACommand nmea){
		/*
		 $GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48

		where:
				VTG          Track made good and ground speed
			[0-1]	054.7,T      True track made good (degrees)
			[2-3]	034.4,M      Magnetic track made good
			[4-5]	005.5,N      Ground speed, knots
			[6-7]	010.2,K      Ground speed, Kilometers per hour
			[7]	*48          Checksum
		 */

		try
		{
			if(nmea.parameters.size() < 7){
				throw NumberConversionError("GPS data is missing parameters.");
			}

			this->fix.speed = parseDouble(nmea.parameters[6]);
			//this->fix.haslock = true;
		}
		catch(NumberConversionError& ex)
		{
			cout << "GPS Data Bad Format [$GPVTG] :: " + ex.message << endl;
		}
	});


}


}} 
