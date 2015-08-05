#include "gtest/gtest.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "rf_phreaker/scanner/eeprom.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

TEST(EepromAddressingTest, GeneralTest) {
	eeprom_addressing add1;
	add1.set_byte_address(0xDEAD0000);
	add1.set_byte_length(0xDEAD);

	{
		std::ofstream f("test_eeprom_addressing.txt");
		boost::archive::text_oarchive oa(f);
		oa & add1;
	}
	eeprom_addressing add2;
	{
		std::ifstream f("test_eeprom_addressing.txt");
		boost::archive::text_iarchive ia(f);
		ia & add2;
	}

	EXPECT_EQ(add1.byte_address(), add2.byte_address());
	EXPECT_EQ(add1.byte_length(), add2.byte_length());
	EXPECT_TRUE(add1 == add2);

	{
		std::ofstream f("test_eeprom_addressing.bin");
		boost::archive::binary_oarchive oa(f);
		oa & add1;
	}
	eeprom_addressing add3;
	{
		std::ifstream f("test_eeprom_addressing.bin");
		boost::archive::binary_iarchive ia(f);
		ia & add2;
	}

	eeprom_addressing add4;
	add4 = add1;
	EXPECT_TRUE(add1 == add4);
}

TEST(MetaEepromTest, GeneralTest)
{
	eeprom ee1, ee2;
	eeprom_meta_data meta1;

	ee2.license_.bytes_.resize(RF_PHREAKER_FLASH_BYTE_LEN);
	meta1.calculate_eeprom_addresses(ee2);
	EXPECT_FALSE(meta1.is_valid());

	meta1.calculate_eeprom_addresses(ee1);
	EXPECT_TRUE(meta1.is_valid());
	
	EXPECT_EQ(meta1.freq_correction_addressing().byte_address(), RF_PHREAKER_FLASH_ADDR + RF_PHREAKER_FLASH_EB_SIZE);
	EXPECT_EQ(meta1.license_addressing().byte_address(), RF_PHREAKER_FLASH_ADDR + 2 * RF_PHREAKER_FLASH_EB_SIZE);
	EXPECT_EQ(meta1.calibration_addressing().byte_address(), RF_PHREAKER_FLASH_ADDR + 3 * RF_PHREAKER_FLASH_EB_SIZE);

	EXPECT_FALSE(meta1.is_frequency_correction_boundary_exceeded(RF_PHREAKER_FLASH_EB_SIZE));
	EXPECT_FALSE(meta1.is_license_boundary_exceeded(RF_PHREAKER_FLASH_EB_SIZE));
	EXPECT_FALSE(meta1.is_calibration_boundary_exceeded(RF_PHREAKER_FLASH_EB_SIZE));
	EXPECT_FALSE(meta1.is_trimmed_eeprom_boundary_exceeded(RF_PHREAKER_FLASH_BYTE_LEN - RF_PHREAKER_FLASH_EB_SIZE));

	EXPECT_TRUE(meta1.is_frequency_correction_boundary_exceeded(RF_PHREAKER_FLASH_EB_SIZE + 1));
	EXPECT_TRUE(meta1.is_license_boundary_exceeded(RF_PHREAKER_FLASH_EB_SIZE + 1));
	EXPECT_TRUE(meta1.is_calibration_boundary_exceeded(RF_PHREAKER_FLASH_EB_SIZE + 1));
	EXPECT_TRUE(meta1.is_trimmed_eeprom_boundary_exceeded(RF_PHREAKER_FLASH_BYTE_LEN - RF_PHREAKER_FLASH_EB_SIZE + 1));

	EXPECT_NO_THROW(meta1.update_frequency_correction_length(RF_PHREAKER_FLASH_EB_SIZE));
	EXPECT_NO_THROW(meta1.update_license_length(RF_PHREAKER_FLASH_EB_SIZE));
	EXPECT_NO_THROW(meta1.update_calibration_length(RF_PHREAKER_FLASH_EB_SIZE));

	EXPECT_THROW(meta1.update_frequency_correction_length(RF_PHREAKER_FLASH_EB_SIZE + 1), hardware_info_error);
	EXPECT_THROW(meta1.update_license_length(RF_PHREAKER_FLASH_EB_SIZE + 1), hardware_info_error);
	EXPECT_THROW(meta1.update_calibration_length(RF_PHREAKER_FLASH_EB_SIZE + 1), hardware_info_error);


	{
		std::ofstream f("test_eeprom_meta.txt");
		boost::archive::text_oarchive oa(f);
		oa & meta1;
	}
	eeprom_meta_data meta2;
	{
		std::ifstream f("test_eeprom_meta.txt");
		boost::archive::text_iarchive ia(f);
		ia & meta2;
	}

	EXPECT_TRUE(meta2 == meta1);

	{
		std::ofstream f("test_eeprom_meta.bin");
		boost::archive::binary_oarchive oa(f);
		oa & meta1;
	}
	eeprom_meta_data meta3;
	{
		std::ifstream f("test_eeprom_meta.bin");
		boost::archive::binary_iarchive ia(f);
		ia & meta3;
	}

	EXPECT_TRUE(meta3 == meta1);

	auto bytes = meta1.serialize_to_bytes();
	
	eeprom_meta_data meta4;
	EXPECT_TRUE(meta4.init(bytes));
}

TEST(EepromTest, GeneralTest) {
	
	eeprom ee1;

	eeprom_meta_data meta;
	meta.calculate_eeprom_addresses(ee1);

	{
		std::ofstream f("test_eeprom.txt");
		boost::archive::text_oarchive oa(f);
		oa & ee1;
	}
	eeprom ee2;
	{
		std::ifstream f("test_eeprom.txt");
		boost::archive::text_iarchive ia(f);
		ia & ee2;
	}

	EXPECT_TRUE(ee1 == ee2);

	{
		std::ofstream f("test_eeprom.bin");
		boost::archive::binary_oarchive oa(f);
		oa & ee1;
	}
	eeprom ee3;
	{
		std::ifstream f("test_eeprom.bin");
		boost::archive::binary_iarchive ia(f);
		ia & ee3;
	}

	EXPECT_TRUE(ee1 == ee3);

	auto bytes = ee1.serialize_to_bytes();

	eeprom ee4;
	EXPECT_TRUE(ee4.init(bytes, meta));


}


