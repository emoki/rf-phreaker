#pragma once
#include <sstream>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "rf_phreaker/scanner/calibration.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/license.h"

namespace rf_phreaker { namespace scanner {

#define RF_PHREAKER_FLAGE_PAGE_SIZE 256
#define RF_PHREAKER_FLASH_ADDR 0x00040000
#define RF_PHREAKER_FLASH_PAGE (RF_PHREAKER_FLASH_ADDR / RF_PHREAKER_FLAGE_PAGE_SIZE)
#define RF_PHREAKER_FLASH_EB (RF_PHREAKER_FLASH_ADDR / (64 * 1024))
#define RF_PHREAKER_FLASH_BYTE_LEN 0x00370000
#define RF_PHREAKER_FLASH_METADATA_BYTE_LEN 256

inline uint32_t convert_to_page(uint32_t num) {
	return add_mod(num, RF_PHREAKER_FLAGE_PAGE_SIZE) / RF_PHREAKER_FLAGE_PAGE_SIZE;
}

class eeprom
{
public:
	eeprom() {};

	static uint32_t absolute_byte_address() { return RF_PHREAKER_FLASH_ADDR; }
	static uint32_t absolute_page_address() { return RF_PHREAKER_FLASH_PAGE; }
	static uint32_t absolute_erase_block_address() { return RF_PHREAKER_FLASH_EB; }
	static uint32_t absolute_total_byte_length() { return RF_PHREAKER_FLASH_BYTE_LEN; }
	static uint32_t absolute_total_page_length() { return convert_to_page(RF_PHREAKER_FLASH_BYTE_LEN); }
	static uint32_t absolute_erase_block_length() { return RF_PHREAKER_FLASH_BYTE_LEN / (64 * 1024); }

	void init(const std::vector<uint8_t> &bytes) {
		std::stringstream ss;
		std::string str(bytes.begin(), bytes.end());
		ss << str;
		boost::archive::text_iarchive ia(ss);
		ia & *this;
	}

	std::vector<uint8_t> serialize_to_bytes() const
	{
		// Be sure to include any buffer length that may be needed at the end because 
		// we have to write in pages (256 bytes at a time).
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa & *this;
		std::vector<uint8_t> bytes(add_mod(ss.str().size(), RF_PHREAKER_FLAGE_PAGE_SIZE));
		std::string tmp(ss.str());
		std::copy(tmp.begin(), tmp.end(), bytes.begin());
		return bytes;
	}
	calibration cal_;
	license license_;


private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & cal_;
		ar & license_;
	}
};

class eeprom_meta_data
{
public:
	eeprom_meta_data() : eeprom_length_(0), eeprom_address_(0) {}

	static uint32_t absolute_byte_address() { return RF_PHREAKER_FLASH_ADDR; }
	static uint32_t absolute_page_address() { return RF_PHREAKER_FLASH_PAGE; }
	static uint32_t absolute_total_byte_length() { return RF_PHREAKER_FLASH_METADATA_BYTE_LEN; }
	static uint32_t absolute_total_page_length() { return convert_to_page(RF_PHREAKER_FLASH_METADATA_BYTE_LEN); }

	bool is_valid()
	{
		return eeprom_address_ > absolute_byte_address() && eeprom_address_ + eeprom_length_ < eeprom::absolute_byte_address() + eeprom::absolute_total_byte_length();
	}

	void set_eeprom_byte_length_and_calculate_address(uint32_t length) { 
		eeprom_length_ = length; 
		calculate_eeprom_byte_address();
	}

	void calculate_eeprom_byte_address()
	{
		// Include a flash page for padding
		auto meta_bytes = serialize_to_bytes();
		eeprom_address_ = eeprom::absolute_byte_address() + meta_bytes.size() + RF_PHREAKER_FLAGE_PAGE_SIZE;
		assert(eeprom_address_ == add_mod(eeprom_address_, RF_PHREAKER_FLAGE_PAGE_SIZE)); 
	}

	uint32_t eeprom_byte_length() const {
		return eeprom_length_;
	}

	uint32_t eeprom_page_length() const	{
		return convert_to_page(eeprom_length_);
	}

	uint32_t eeprom_byte_address() const {
		assert(eeprom_address_ == add_mod(eeprom_address_, RF_PHREAKER_FLAGE_PAGE_SIZE));
		return eeprom_address_;
	}

	uint32_t eeprom_page_address() const {
		return convert_to_page(eeprom_address_);
	}

	void init(const std::vector<uint8_t> &bytes)
	{
		std::stringstream ss;
		std::string str(bytes.begin(), bytes.end());
		ss << str;
		boost::archive::text_iarchive ia(ss);
		ia & *this;
	}

	std::vector<uint8_t> serialize_to_bytes() const
	{
		// Be sure to include any buffer length that may be needed at the end because 
		// we have to write in pages (256 bytes at a time).
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa & *this;
		std::vector<uint8_t> bytes(add_mod(ss.str().size(), RF_PHREAKER_FLAGE_PAGE_SIZE));
		std::string tmp(ss.str());
		std::copy(tmp.begin(), tmp.end(), bytes.begin());
		return bytes;
	}
private:
	uint32_t eeprom_length_;
	uint32_t eeprom_address_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & eeprom_length_;
		ar & eeprom_address_;
	}
};


}}
