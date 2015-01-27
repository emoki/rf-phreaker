#include "rf_phreaker/scanner/eeprom.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace scanner {

eeprom_addressing eeprom_meta_data::meta_addressing_(RF_PHREAKER_FLASH_ADDR, RF_PHREAKER_FLASH_METADATA_BYTE_LEN);
eeprom_addressing eeprom::eeprom_addressing_(RF_PHREAKER_FLASH_ADDR, RF_PHREAKER_FLASH_BYTE_LEN);

void eeprom_meta_data::clear() {
	freq_correction_addressing_.set_byte_length(0);
	freq_correction_addressing_.set_byte_address(0);
	license_addressing_.set_byte_length(0);
	license_addressing_.set_byte_address(0);
	calibration_addressing_.set_byte_length(0);
	calibration_addressing_.set_byte_address(0);
	trimmed_eeprom_addressing_.set_byte_length(0);
	trimmed_eeprom_addressing_.set_byte_address(0);
}

void eeprom_meta_data::set_to_default() {
	freq_correction_addressing_.set_byte_length(RF_PHREAKER_FLASH_EB_SIZE);
	freq_correction_addressing_.set_byte_address(eeprom_meta_data::addressing().end_byte_address_with_eb_padding());

	license_addressing_.set_byte_length(RF_PHREAKER_FLASH_EB_SIZE);
	license_addressing_.set_byte_address(freq_correction_addressing_.end_byte_address_with_eb_padding());

	calibration_addressing_.set_byte_length(RF_PHREAKER_FLASH_EB_SIZE * 5);
	calibration_addressing_.set_byte_address(license_addressing_.end_byte_address_with_eb_padding());

	trimmed_eeprom_addressing_.set_byte_length(freq_correction_addressing_.byte_length_with_eb_padding() +
		license_addressing_.byte_length_with_eb_padding() +
		calibration_addressing_.byte_length_with_eb_padding());
	trimmed_eeprom_addressing_.set_byte_address(eeprom_meta_data::addressing().end_byte_address_with_eb_padding());
}

void eeprom_meta_data::calculate_eeprom_addresses(const eeprom &ee) {
	freq_correction_addressing_.set_byte_length(ee.freq_correction_.serialize_to_bytes().size());
	freq_correction_addressing_.set_byte_address(eeprom_meta_data::addressing().end_byte_address_with_eb_padding());

	license_addressing_.set_byte_length(ee.license_.serialize_to_bytes(RF_PHREAKER_FLASH_PAGE_SIZE).size());
	license_addressing_.set_byte_address(freq_correction_addressing_.end_byte_address_with_eb_padding());

	calibration_addressing_.set_byte_length(ee.cal_.serialize_to_bytes().size());
	calibration_addressing_.set_byte_address(license_addressing_.end_byte_address_with_eb_padding());

	trimmed_eeprom_addressing_.set_byte_length(freq_correction_addressing_.byte_length_with_eb_padding() +
		license_addressing_.byte_length_with_eb_padding() +
		calibration_addressing_.byte_length_with_eb_padding());
	trimmed_eeprom_addressing_.set_byte_address(eeprom_meta_data::addressing().end_byte_address_with_eb_padding());
}

void eeprom_meta_data::update_frequency_correction_length(uint32_t length) {
	if(is_frequency_correction_boundary_exceeded(length))
		throw rf_phreaker_error("Frequency correction size exceeds it's boundary.");
	freq_correction_addressing_.set_byte_length(length);
}

void eeprom_meta_data::update_license_length(uint32_t length) {
	if(is_license_boundary_exceeded(length))
		throw rf_phreaker_error("License size exceeds it's boundary.");
	license_addressing_.set_byte_length(length);
}

void eeprom_meta_data::update_calibration_length(uint32_t length) {
	if(is_calibration_boundary_exceeded(length))
		throw rf_phreaker_error("Calibration size exceeds it's boundary.");
	calibration_addressing_.set_byte_length(length);
	
	// For trimmed eeprom we need the padded freq corr and license but cali can be unpadded since 
	// it is the last item.
	trimmed_eeprom_addressing_.set_byte_length(freq_correction_addressing_.byte_length_with_eb_padding() +
		license_addressing_.byte_length_with_eb_padding() +
		calibration_addressing_.byte_length());
}

bool eeprom_meta_data::is_frequency_correction_boundary_exceeded(uint32_t length) const {
	return freq_correction_addressing_.byte_address() + add_eb_padding(length) > license_addressing_.byte_address();
}

bool eeprom_meta_data::is_license_boundary_exceeded(uint32_t length) const {
	return license_addressing_.byte_address() + add_eb_padding(length) > calibration_addressing_.byte_address();
}

bool eeprom_meta_data::is_calibration_boundary_exceeded(uint32_t length) const {
	return calibration_addressing_.byte_address() + add_eb_padding(length) > trimmed_eeprom_addressing_.end_byte_address_with_eb_padding();
}

bool eeprom_meta_data::is_trimmed_eeprom_boundary_exceeded(uint32_t length) const {
	return trimmed_eeprom_addressing_.byte_address() + add_eb_padding(length) > eeprom::addressing().end_byte_address_with_eb_padding();
}

bool eeprom_meta_data::is_valid() const {
	return !is_frequency_correction_boundary_exceeded(freq_correction_addressing_.byte_length()) &&
		!is_license_boundary_exceeded(license_addressing_.byte_length()) &&
		!is_calibration_boundary_exceeded(calibration_addressing_.byte_length()) &&
		!is_trimmed_eeprom_boundary_exceeded(trimmed_eeprom_addressing_.byte_length());
}


}}