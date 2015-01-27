#pragma once
#include <boost/serialization/access.hpp>
#include "rf_phreaker/scanner/calibration.h"
#include "rf_phreaker/scanner/freq_correction_container.h"
#include "rf_phreaker/scanner/eeprom_defines.h"
#include "rf_phreaker/common/license.h"
#include "rf_phreaker/common/serialization_helper.h"
#include "rf_phreaker/common/log.h"

namespace rf_phreaker { namespace scanner {

class eeprom;

class eeprom_addressing {
public:
	eeprom_addressing()  
		: byte_address_(0)
		, byte_length_(0) {}
	eeprom_addressing(uint32_t byte_address, uint32_t byte_length)
		: byte_address_(byte_address)
		, byte_length_(byte_length) {}
	eeprom_addressing& operator=(const eeprom_addressing &a) {
		byte_address_ = a.byte_address_;
		byte_length_ = a.byte_length_;
		return *this;
	}
	bool operator==(const eeprom_addressing &a) {
		return byte_address_ == a.byte_address_ && byte_length_ == a.byte_length_;
	}
	// Relative from the end of the eeprom meta data, including any erase block padding.
	uint32_t byte_address() const { return byte_address_; }
	uint32_t page_address() const { return convert_to_page(byte_address_); }
	uint32_t erase_block_address() const { return convert_to_erase_block(byte_address_); }
	uint32_t byte_length() const { return byte_length_; }
	uint32_t byte_length_with_eb_padding() const { return add_eb_padding(byte_length_); }
	uint32_t page_length() const { return convert_to_page(byte_length_); }
	uint32_t erase_block_length() const { return convert_to_erase_block(byte_length_); }
	uint32_t end_byte_address() const { return byte_address_ + byte_length_; }
	uint32_t end_byte_address_with_eb_padding() const { return add_eb_padding(end_byte_address()); }
	uint32_t end_page_address() const { return convert_to_page(end_byte_address()); }
	uint32_t end_erase_block_address() const { return convert_to_erase_block(end_byte_address()); }

	void set_byte_address(uint32_t add) { byte_address_ = add; }
	void set_byte_length(uint32_t len) { byte_length_ = len; }
private:
	uint32_t byte_address_;
	uint32_t byte_length_;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & byte_address_;
		ar & byte_length_;
	}

};


class eeprom_meta_data
{
public:
	eeprom_meta_data() {
		set_to_default();
	}
	bool operator==(const eeprom_meta_data &a) {
		return freq_correction_addressing_ == a.freq_correction_addressing_ &&
			license_addressing_ == a.license_addressing_ &&
			calibration_addressing_ == a.calibration_addressing_ &&
			trimmed_eeprom_addressing_ == a.trimmed_eeprom_addressing_;
	}

	static const eeprom_addressing& addressing() { return meta_addressing_; }

	void clear();
	void set_to_default();
	void calculate_eeprom_addresses(const eeprom &ee);
	
	void update_frequency_correction_length(uint32_t frequency_correction_length);
	void update_license_length(uint32_t license_length);
	void update_calibration_length(uint32_t calibration_length);

	bool is_frequency_correction_boundary_exceeded(uint32_t length) const;
	bool is_license_boundary_exceeded(uint32_t length) const;
	bool is_calibration_boundary_exceeded(uint32_t length) const;
	bool is_trimmed_eeprom_boundary_exceeded(uint32_t length) const;

	bool is_valid() const;

	const eeprom_addressing& freq_correction_addressing() const { return freq_correction_addressing_; }
	const eeprom_addressing& license_addressing() const { return license_addressing_; }
	const eeprom_addressing& calibration_addressing() const { return calibration_addressing_; }
	const eeprom_addressing& trimmed_eeprom_addressing() const { return trimmed_eeprom_addressing_; }

	uint32_t freq_correction_relative_byte_address() const { return freq_correction_addressing_.byte_address() - trimmed_eeprom_addressing().byte_address(); }
	uint32_t license_relative_byte_address() const { return license_addressing_.byte_address() - trimmed_eeprom_addressing().byte_address(); }
	uint32_t calibration_relative_byte_address() const { return calibration_addressing_.byte_address() - trimmed_eeprom_addressing().byte_address(); }

	bool init(const std::vector<uint8_t> &bytes) {
		bool success = serialization_helper::init(bytes, *this, true);
		LOG_IF(LERROR, !success) << "EEPROM meta data failed verification.  It appears corrupt.";
		return success;
	}
	std::vector<uint8_t> serialize_to_bytes() const {
		return serialization_helper::serialize_to_bytes(*this, RF_PHREAKER_FLASH_PAGE_SIZE, true);
	}

private:
	static eeprom_addressing meta_addressing_;
	eeprom_addressing freq_correction_addressing_;
	eeprom_addressing license_addressing_;
	eeprom_addressing calibration_addressing_;
	eeprom_addressing trimmed_eeprom_addressing_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & freq_correction_addressing_;
		ar & license_addressing_;
		ar & calibration_addressing_;
		ar & trimmed_eeprom_addressing_;
	}
};

class eeprom
{
public:
	eeprom() {};

	static const eeprom_addressing& addressing() { return eeprom_addressing_; }

	bool operator==(const eeprom &a) {
		return freq_correction_ == a.freq_correction_ &&
			license_ == a.license_ &&
			cal_ == a.cal_;
	}

	bool init(const std::vector<uint8_t> &bytes, const eeprom_meta_data &meta) {
		assert(bytes.size());

		bool valid = true;

		std::vector<uint8_t> freq_bytes(&bytes.at(meta.freq_correction_relative_byte_address()), 
			&bytes.at(meta.freq_correction_relative_byte_address() + meta.freq_correction_addressing().byte_length()));
		valid &= freq_correction_.init(freq_bytes);

		std::vector<uint8_t> license_bytes(&bytes.at(meta.license_relative_byte_address()),
			&bytes.at(meta.license_relative_byte_address() + meta.license_addressing().byte_length()));
		valid &= license_.init(license_bytes);

		std::vector<uint8_t> cali_bytes(&bytes.at(meta.calibration_relative_byte_address()),
			&bytes.at(meta.calibration_relative_byte_address() + meta.calibration_addressing().byte_length()));
		valid &= cal_.init(cali_bytes);

		return valid;
	}
	std::vector<uint8_t> serialize_to_bytes() const {
		// Serialize all objects making sure that each object starts on a new erase block.
		auto freq_bytes = freq_correction_.serialize_to_bytes();
		freq_bytes.resize(add_mod(freq_bytes.size(), RF_PHREAKER_FLASH_EB_SIZE));
		
		auto license_bytes = license_.serialize_to_bytes(RF_PHREAKER_FLASH_PAGE_SIZE);
		license_bytes.resize(add_mod(license_bytes.size(), RF_PHREAKER_FLASH_EB_SIZE));
		
		auto cali_bytes = cal_.serialize_to_bytes();
		cali_bytes.resize(add_mod(cali_bytes.size(), RF_PHREAKER_FLASH_EB_SIZE));

		std::vector<uint8_t> eeprom_bytes(freq_bytes.size() + license_bytes.size() + cali_bytes.size());
		std::copy(freq_bytes.begin(), freq_bytes.end(), eeprom_bytes.begin());
		std::copy(license_bytes.begin(), license_bytes.end(), eeprom_bytes.begin() + freq_bytes.size());
		std::copy(cali_bytes.begin(), cali_bytes.end(), eeprom_bytes.begin() + freq_bytes.size() + license_bytes.size());

		return eeprom_bytes;
	}

	freq_correction_container freq_correction_;
	license license_;
	calibration cal_;

private:
	static eeprom_addressing eeprom_addressing_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & freq_correction_;
		ar & license_;
		ar & cal_;
	}
};


}}
