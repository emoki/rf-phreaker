#include "gtest/gtest.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "rf_phreaker/scanner/eeprom.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

TEST(EepromTest, GeneralTest)
{
	eeprom_meta_data meta_ee;
	meta_ee;

	meta_ee.set_eeprom_byte_length_and_calculate_address(256*2);

	{
		std::ofstream f("test_eeprom_meta.txt");
		boost::archive::text_oarchive oa(f);
		oa & meta_ee;
	}
	eeprom_meta_data meta_ee2;
	{
		std::ifstream f("test_eeprom_meta.txt");
		boost::archive::text_iarchive ia(f);
		ia & meta_ee2;
	}

	auto bytes = meta_ee.serialize_to_bytes();
	
	eeprom_meta_data meta_ee_1;
	meta_ee_1.init(bytes);
}