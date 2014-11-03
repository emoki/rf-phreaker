/*
 * NMEACommand.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: me
 */

#include "NMEACommand.h"
#include <iomanip>
#include <sstream>

using namespace std;
using namespace rf_phreaker::gps_comm;


NMEACommand::NMEACommand(){};
NMEACommand::~NMEACommand(){};
string NMEACommand::toString(){
	message = name + ",";
	return addChecksum(message);
}
string NMEACommand::addChecksum(std::string s){
	stringstream zz;
	zz << name << "," << s;
	checksum = NMEAParser::calculateChecksum(zz.str());

	stringstream ss;
	ss << "$" << zz.str() << "*" << hex << uppercase << internal << setfill('0') << setw(2) << (int)checksum << "\r\n";

	return ss.str();
};



		/*
		//$PSRF100,0,9600,8,1,0*0C
		Table 2-4 Set Serial Port Data Format
		Name Example Unit Description
		Message ID $PSRF100 PSRF100 protocol header
		Protocol 0 			0=SiRF binary, 1=NMEA
		Baud 	9600 		1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200
		DataBits 8 			8,71
		1. SiRF protocol is only valid for 8 data bits, 1stop bit, and no parity.
		StopBits 1 			0,1
		Parity 0 			0=None, 1=Odd, 2=Even
		Checksum *0C
		<CR> <LF> End of message termination
		*/
std::string NMEACommandSerialConfiguration::toString(){
	stringstream ss;

	ss << "1," << baud << "," << databits << "," << stopbits << "," << parity;
	message = ss.str();

	return NMEACommand::addChecksum(message);
}



//$PSRF103,00,01,00,01*25

	/*
	 * Table 2-9 Query/Rate Control Data Format
		Name Example Unit Description
		Message ID $PSRF103 PSRF103 protocol header
		Msg 00 		See Table 2-10
		Mode 01 		0=SetRate, 1=Query
		Rate 00 		sec Output—off=0, max=255
		CksumEnable 01 	0=Disable Checksum, 1=Enable Checksum
		Checksum *25
		<CR> <LF> End of message termination
	 */
	/*
	 * Table 2-10 Messages
			Value Description
			0 GGA
			1 GLL
			2 GSA
			3 GSV
			4 RMC
			5 VTG
			6 MSS (If internal beacon is supported)
			7 Not defined
			8 ZDA (if 1PPS output is supported)
			9 Not defined
	 */
//int messageID;
//int mode;
//int rate;
//int checksumEnable;
std::string NMEACommandQueryRate::toString(){
	stringstream ss;

	ss << setfill('0') << setw(2) << messageID << ","
		 << setfill('0') << setw(2) << mode << ","
		 << setfill('0') << setw(2) << rate << ","
		 << setfill('0') << setw(2) << checksumEnable;
	message = ss.str();

	return NMEACommand::addChecksum(message);
}

