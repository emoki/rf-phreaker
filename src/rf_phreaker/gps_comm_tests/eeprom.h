#pragma once
#include <sstream>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "rf_phreaker/gps_comm/BladeError.h"

#define RF_PHREAKER_FLAGE_PAGE 256
#define RF_PHREAKER_FLASH_ADDR 0x00040000
#define RF_PHREAKER_FLASH_PAGE (RF_PHREAKER_FLASH_ADDR / RF_PHREAKER_FLAGE_PAGE)
#define RF_PHREAKER_FLASH_EB (RF_PHREAKER_FLASH_ADDR / (64 * 1024))
#define RF_PHREAKER_FLASH_BYTE_LEN 0x00370000
#define RF_PHREAKER_FLASH_METADATA_BYTE_LEN 256


template<typename Type>
typename Type add_mod(Type num, int mod) {
	if(num % mod)
		return num + (mod - (num % mod));
	else
		return num;
}

inline uint32_t convert_to_page(uint32_t num) {
	return add_mod(num, RF_PHREAKER_FLAGE_PAGE) / RF_PHREAKER_FLAGE_PAGE;
}

class eeprom
{
public:
	eeprom() : cal_(10000), license_(1000)
	{
		uint8_t i = 0;
		for(auto &v : cal_) 
			v = i++ % 58 + 65;
		
		i = 0;
		for(auto &v : license_)
			v = i++ % 58 + 65;
	};

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

	std::vector<uint8_t> serialize_to_bytes() const {
		// Be sure to include any buffer length that may be needed at the end because 
		// we have to write in pages (256 bytes at a time).
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa & *this;
		std::vector<uint8_t> bytes(add_mod(ss.str().size(), RF_PHREAKER_FLAGE_PAGE));
		std::string tmp(ss.str());
		std::copy(tmp.begin(), tmp.end(), bytes.begin());
		return bytes;
	}
	std::vector<uint8_t> cal_;
	std::vector<uint8_t> license_;

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

	bool is_valid() {
		return eeprom_address_ > absolute_byte_address() && eeprom_address_ + eeprom_length_ < eeprom::absolute_byte_address() + eeprom::absolute_total_byte_length();
	}

	void set_eeprom_byte_length_and_calculate_address(uint32_t length) {
		eeprom_length_ = length;
		calculate_eeprom_byte_address();
	}

	void calculate_eeprom_byte_address() {
		// Include a flash page for padding
		auto meta_bytes = serialize_to_bytes();
		eeprom_address_ = eeprom::absolute_byte_address() + meta_bytes.size() + RF_PHREAKER_FLAGE_PAGE;
		assert(eeprom_address_ == add_mod(eeprom_address_, RF_PHREAKER_FLAGE_PAGE));
	}

	uint32_t eeprom_byte_length() const {
		return eeprom_length_;
	}

	uint32_t eeprom_page_length() const {
		return convert_to_page(eeprom_length_);
	}

	uint32_t eeprom_byte_address() const {
		assert(eeprom_address_ == add_mod(eeprom_address_, RF_PHREAKER_FLAGE_PAGE));
		return eeprom_address_;
	}

	uint32_t eeprom_page_address() const {
		return convert_to_page(eeprom_address_);
	}

	void init(const std::vector<uint8_t> &bytes) {
		std::stringstream ss;
		std::string str(bytes.begin(), bytes.end());
		ss << str;
		boost::archive::text_iarchive ia(ss);
		ia & *this;
	}

	std::vector<uint8_t> serialize_to_bytes() const {
		// Be sure to include any buffer length that may be needed at the end because 
		// we have to write in pages (256 bytes at a time).
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa & *this;
		std::vector<uint8_t> bytes(add_mod(ss.str().size(), RF_PHREAKER_FLAGE_PAGE));
		std::string tmp(ss.str());
		std::copy(tmp.begin(), tmp.end(), bytes.begin());
		return bytes;
	}
private:
	uint32_t eeprom_length_;
	uint32_t eeprom_address_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & eeprom_length_;
		ar & eeprom_address_;
	}
};

inline std::vector<uint8_t> read_raw_eeprom(bladerf *device) {
	using namespace rf_phreaker::gps_comm;

	std::vector<uint8_t> bytes(eeprom::absolute_total_byte_length(), 0);

	BladeError::check(bladerf_read_flash(device, &bytes[0],
		eeprom::absolute_page_address(), eeprom::absolute_total_page_length()));

	return bytes;
}

inline void write_raw_eeprom(bladerf *device, const std::vector<uint8_t> &bytes) {
	using namespace rf_phreaker::gps_comm;

	if(bytes.size() < eeprom::absolute_total_byte_length())
		throw std::runtime_error("Cannot write to EEPROM - the buffer given is too small.");

	BladeError::check(bladerf_write_flash(device, &bytes[0],
		eeprom::absolute_page_address(), eeprom::absolute_total_page_length()));
}

inline eeprom_meta_data read_eeprom_meta_data(bladerf *device) {
	using namespace rf_phreaker::gps_comm;

	std::vector<uint8_t> md_bytes(eeprom_meta_data::absolute_total_byte_length(), 0);

	BladeError::check(bladerf_read_flash(device, &md_bytes[0],
		eeprom_meta_data::absolute_page_address(), eeprom_meta_data::absolute_total_page_length()));

	eeprom_meta_data md_eeprom;
	md_eeprom.init(md_bytes);

	return md_eeprom;
}

inline void write_eeprom(bladerf *device, const eeprom &ee) {
	using namespace rf_phreaker::gps_comm;

	auto new_eeprom_bytes = ee.serialize_to_bytes();

	eeprom_meta_data meta_ee;
	meta_ee.set_eeprom_byte_length_and_calculate_address(new_eeprom_bytes.size());
	auto meta_bytes = meta_ee.serialize_to_bytes();

	if(!meta_ee.is_valid())
		throw std::runtime_error("Cannot write to the EEPROM.  EEPROM meta data is not valid.");

	// Erase flash.
	BladeError::check(bladerf_erase_flash(device,
		eeprom::absolute_erase_block_address(), eeprom::absolute_erase_block_length()));

	// Perform writes.
	BladeError::check(bladerf_write_flash(device, &meta_bytes[0],
		eeprom_meta_data::absolute_page_address(), eeprom_meta_data::absolute_total_page_length()));

	BladeError::check(bladerf_write_flash(device, &new_eeprom_bytes[0],
		meta_ee.eeprom_page_address(), meta_ee.eeprom_page_length()));
}

inline eeprom read_eeprom(bladerf *device) {
	using namespace rf_phreaker::gps_comm;

	eeprom_meta_data meta_ee = read_eeprom_meta_data(device);

	if(!meta_ee.is_valid())
		throw std::runtime_error("Cannot read EEPROM.  EEPROM meta data is not valid.");

	std::vector<uint8_t> bytes(eeprom::absolute_total_byte_length(), 0);

	BladeError::check(bladerf_read_flash(device, &bytes[0],
		meta_ee.eeprom_page_address(), meta_ee.eeprom_page_length()));

	eeprom ee;
	ee.init(bytes);

	return ee;
}

inline void initialize_eeprom(bladerf *device) {
	eeprom ee;
	write_eeprom(device, ee);
}



