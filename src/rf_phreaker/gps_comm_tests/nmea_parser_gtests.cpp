#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include "rf_phreaker/gps_comm/GPSService.h"


using namespace rf_phreaker::gps_comm;

TEST(NmeaParserTests, DISABLED_TestGeneral) {
	// proves it works for most things... it's not a comprehensive test.
	// The trailing empty comma is also parsed correctly.  -- standard if no checksum
	// A single \n is also parsed correctly in addition to both \r\n.

	std::string s = "Broken Command, 1,2\n$GPS\r\n$\r\n\r\n$,3\r\n$,\r\n$G2,\r\n$G3,asd,33\r\n$G4,xyz,,4.245,\r\n$G5,xyz,\n$GCS,3,W*23\r\n$GCS2,q,w,*234\r\n$GCS3,q,w,W*\r\n$GCS4,q,w,*\r\n$GCSLAST,q,w,*,\r\n";
	NMEAParser p;
	p.log = true;	//show activity


	//setup parser output handler
	p.onCommand += [](NMEASentence nmea) {
		std::cout << "PARSED NMEA SENTENCE: \"" << nmea.name << "\"" << std::endl;
	};

	//setup specific message handler
	p.setCommandHandler("G4", [](NMEASentence nmea) {
		std::cout << " --> GPS EVENT RECEIVED: the G4 gps signal was received. " << std::endl;
	});

	//feed the parser the byte stream
	for(size_t i = 0; i < s.size(); i++) {
		p.parseByte(s[i]);
	}

}