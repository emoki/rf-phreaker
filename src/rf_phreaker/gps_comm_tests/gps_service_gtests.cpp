#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <thread>
#include "rf_phreaker/gps_comm/GPSService.h"


using namespace rf_phreaker::gps_comm;

TEST(GpsServiceTests, TestGeneral) {
	GPSService gps;
	gps.parser.onCommand = [](NMEACommand nmea) {
		std::cout << "NMEA: " << nmea.name << " >> " << nmea.text << std::endl;
	};
	std::vector<std::string> test;
	test.push_back("$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47");
	test.push_back("$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39");
	test.push_back("$GPGSV,2,1,08,01,40,083,46,02,17,308,41,12,07,344,39,14,22,228,45*75");
	test.push_back("$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A");
	test.push_back("$GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48");

	//bad data
	test.push_back("$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.5.4,M,46.9,M,,*47");	//missing a comma
	test.push_back("$GPGSA,A,3,04,05,,09,12,,,24,,,*39"); //missing a comma
	test.push_back("$GPGSV,2,1,08,308,41,12,07,344,39,14,22,228,45*75");
	test.push_back("$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A");
	test.push_back("$GPVTG,054.7,T,005.5,N,010.2,K*48");

	for(size_t i = 0; i < test.size(); i++) {
		gps.readline(test[i]);
	}
	GPSFix fix = gps.fix;

	std::this_thread::sleep_for(std::chrono::milliseconds(10));			//add delay to give fix an "age"
	std::cout << fix.toString() << std::endl;
}