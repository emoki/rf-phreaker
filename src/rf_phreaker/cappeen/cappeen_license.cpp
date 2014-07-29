#include "rf_phreaker/cappeen/cappeen_license.h"
#include "rf_phreaker/cappeen/beagle_defines.h"
#include "hash_utility/sha256.h"
#include <fstream>

using namespace beagle_api;
//using namespace rf_phreaker::cappeen_api;
namespace rf_phreaker { namespace cappeen_api {
//{{

void license_helper::add_license(std::vector<uint8_t> &license_container, uint32_t license_data) {
	license_container.push_back((uint8_t)(license_data >> 0));
	license_container.push_back((uint8_t)(license_data >> 8));
	license_container.push_back((uint8_t)(license_data >> 16));
	license_container.push_back((uint8_t)(license_data >> 24));
}

license_map_v3::license_map_v3() {
	std::set<TECHNOLOGIES_AND_BANDS> tmp;
	tmp.clear();
	tmp.insert(GSM_BAND_850);
	map_.insert(std::make_pair(gsm_850_license_position, tmp));
	tmp.clear();
	tmp.insert(GSM_BAND_900);
	map_.insert(std::make_pair(gsm_900_license_position, tmp));
	tmp.clear();
	tmp.insert(GSM_BAND_1800);
	map_.insert(std::make_pair(gsm_1800_license_position, tmp));
	tmp.clear();
	tmp.insert(GSM_BAND_1900);
	map_.insert(std::make_pair(gsm_1900_license_position, tmp));
	tmp.clear();
	tmp.insert(WCDMA_BAND_850);
	map_.insert(std::make_pair(wcdma_850_license_position, tmp));
	tmp.clear();
	tmp.insert(WCDMA_BAND_900);
	map_.insert(std::make_pair(wcmda_900_license_position, tmp));
	tmp.clear();
	tmp.insert(WCDMA_BAND_1800);
	map_.insert(std::make_pair(wcdma_1800_license_position, tmp));
	tmp.clear();
	tmp.insert(WCDMA_BAND_1900);
	map_.insert(std::make_pair(wcdma_1900_license_position, tmp));
	tmp.clear();
	tmp.insert(WCDMA_BAND_2100);
	map_.insert(std::make_pair(wcdma_2100_license_position, tmp));

	tmp.clear();
	tmp.insert(LTE_BAND_12);// operating band  [729 - 746 MHZ]
	tmp.insert(LTE_BAND_13);// operating band  [746 - 756 MHZ]
	tmp.insert(LTE_BAND_14);// operating band  [758 - 768 MHZ]
	tmp.insert(LTE_BAND_17);// operating band  [734 - 746 MHZ]
	tmp.insert(LTE_BAND_28);// operating band  [758 - 803 MHZ]
	tmp.insert(LTE_BAND_29);// operating band  [716 - 728 MHZ]
	map_.insert(std::make_pair(lte_700_license_position, tmp));

	tmp.clear();
	tmp.insert(LTE_BAND_5);// operating band 5 [869 - 894 MHZ]
	tmp.insert(LTE_BAND_6);// operating band 6 [875 - 885 MHZ]
	tmp.insert(LTE_BAND_18);// operating band  [860 - 875 MHZ]
	tmp.insert(LTE_BAND_19);// operating band  [875 - 890 MHZ]
	tmp.insert(LTE_BAND_20);// operating band 20 [791 - 821 MHZ]
	tmp.insert(LTE_BAND_26);// operating band  [859 - 894 MHZ]
	tmp.insert(LTE_BAND_27);// operating band  [852 - 869 MHZ]
	map_.insert(std::make_pair(lte_850_license_position, tmp));

	tmp.clear();
	tmp.insert(LTE_BAND_8);// operating band 8 [925 - 960 MHZ]
	map_.insert(std::make_pair(lte_900_license_position, tmp));

	tmp.clear();
	tmp.insert(LTE_BAND_3);// operating band 3 [1805 - 1880 MHZ]
	tmp.insert(LTE_BAND_9);// operating band 9 [1844.9 - 1879.9 MHZ]
	map_.insert(std::make_pair(lte_1800_license_position, tmp));

	tmp.clear();
	tmp.insert(LTE_BAND_2);// operating band 2 [1930 - 1990 MHZ]
	tmp.insert(LTE_BAND_25);// operating band  [1930 - 1995 MHZ]
	map_.insert(std::make_pair(lte_1900_license_position, tmp));

	tmp.clear();
	tmp.insert(LTE_BAND_1);// operating band 1 [2110 - 2170 MHZ]
	tmp.insert(LTE_BAND_4);// operating band 4 [2110 - 2155 MHZ]
	tmp.insert(LTE_BAND_10);// operating band  [2110 - 2170 MHZ]
	// Removed band 23.  It's not needed by Cobham according to Arne - see email Mar 5, 2014 [bands needed for NST+].
	//tmp.insert(LTE_BAND_23);// operating band  [2180 - 2200 MHZ]
	map_.insert(std::make_pair(lte_2100_license_position, tmp));

	tmp.clear();
	tmp.insert(LTE_BAND_7); // operating band 7 [2620 - 2690 MHZ]
	map_.insert(std::make_pair(lte_2600_license_position, tmp));
}

license_map_v3 cappeen_license_version_3::license_map_;

cappeen_license::cappeen_license(software_license license)
	: initialized_(false)
	, required_license_(license) 
{}

cappeen_license::~cappeen_license() {}

void cappeen_license::initialize_license(const license &license, const rf_phreaker::scanner::scanner_id_type &serial) {
	encryption_.clear_corruption();

	license_ = license;

	serial_ = serial;

	initialize_license_();

	initialized_ = true;
}

license cappeen_license::create_new_license_from_file(const std::string &filename) {

	std::ifstream f(filename, std::ios::binary);
	if(!f)
		throw cappeen_api_error("Unable to open license file: " + filename + ".", GENERAL_ERROR);

	license new_license;

	std::vector<uint8_t> buf(256);

	f.read((char*)&buf[0], buf.size());

	new_license.version_ = buf[0];

	// Erase the license version and license position from buffer.
	buf.erase(buf.begin(), buf.begin() + 2);

	new_license.bytes_ = buf;

	return new_license;
}

time_t cappeen_license::find_date(license_element_type position) {
	license_element_type encrypted;

	memcpy(&encrypted, &(license_.bytes_[position * sizeof(license_element_type)]), sizeof(license_element_type));

	time_t date = encryption_.decrypt(encrypted, serial_to_hwid(serial_), position);

	if(encryption_.is_corrupt())
		throw cappeen_api_error("License appears corrupt.", CORRUPTLICENSE);

	return date;
}

void cappeen_license::validate_licenses() {
	if(valid_software_licenses_.find(required_license_) == valid_software_licenses_.end()) {
		valid_licenses_.clear();
	}
}

uint32_t cappeen_license::serial_to_hwid(const rf_phreaker::scanner::scanner_id_type &serial) {
	if(serial.size() != 32)
		throw cappeen_api_error("The following serial (" + serial + ") is not valid.  "
			"It should be a 32-character hex string.", GENERAL_ERROR);

	std::string serial_16_char(serial.substr(16, 16));

	SHA256 sha;
	auto hash = sha(serial_16_char);

	uint32_t hw_id = 0;
	char t1[9];
	std::copy(hash.begin(), hash.begin() + 8, t1);
	t1[8] = 0;
	auto t2 = &t1[8];
	hw_id = std::strtoul(t1, &t2, 16);
	return hw_id;
}


cappeen_license_version_1::cappeen_license_version_1()
	: cappeen_license(network_coverage_license) {}

cappeen_license_version_1::~cappeen_license_version_1() {}

void cappeen_license_version_1::initialize_license_() {
	valid_licenses_.clear();

	// date_comparsion can be the date the hardware was calibrated or a specified date that signifies no license available.  
	// We compare this date to first the US date.  If US date is greater we populate valid_licenses_ with gsm and wcdma techs on US bands.
	// If it is not greater than we compare the European date.  If European date is greater we populate valid_licenses_ with gsm and wcdma techs on European bands.
	// If neither is greater there are no valid licenses and we leave valid_licenses_ empty.

	time_t date_comparison = find_date(date_comparison_position_);

	time_t us_license_date = find_date(us_license_position_);

	time_t euro_license_date = find_date(euro_license_position_);

	if(us_license_date > date_comparison)
		create_us_license();

	else if(euro_license_date > date_comparison)
		create_euro_license();

	valid_software_licenses_.clear();
	valid_software_licenses_.insert(network_coverage_license);

	validate_licenses();
}

void cappeen_license_version_1::create_us_license() {
	valid_licenses_.insert(GSM_BAND_850);
	valid_licenses_.insert(GSM_BAND_1900);
	valid_licenses_.insert(WCDMA_BAND_850);
	valid_licenses_.insert(WCDMA_BAND_1900);
	valid_licenses_.insert(WCDMA_BAND_2100);
}

void cappeen_license_version_1::create_euro_license() {
	valid_licenses_.insert(GSM_BAND_900);
	valid_licenses_.insert(GSM_BAND_1800);
	valid_licenses_.insert(WCDMA_BAND_900);
	valid_licenses_.insert(WCDMA_BAND_1800);
	valid_licenses_.insert(WCDMA_BAND_2100);
}


cappeen_license_version_2::cappeen_license_version_2() 
	: cappeen_license(network_coverage_license)
{}

void cappeen_license_version_2::initialize_license_() {
	valid_licenses_.clear();

	for(license_element_type i = GSM_BAND_850; i <= WCDMA_BAND_2100; i++) {
		time_t date = find_date(i);
		if(date > license_helper::invalid_license_)
			valid_licenses_.insert((TECHNOLOGIES_AND_BANDS)i);
	}

	valid_software_licenses_.clear();
	valid_software_licenses_.insert(network_coverage_license);

	validate_licenses();
}

std::vector<uint8_t> cappeen_license_version_2::generate_license(uint32_t hw_id, const std::set<beagle_api::TECHNOLOGIES_AND_BANDS> &licenses) {
	encryption encryption;

	std::vector<uint8_t> output_data;

	// License version
	output_data.push_back((uint8_t)0x02);

	// Position of license in EEPROM
	output_data.push_back((uint8_t)0x11);

	// Bands and technologies info
	// We output the entire license portion of the EEPROM.  A total of 32 entries..
	for(license_element_type i = gsm_850_license_position; i <= end_wcdma_license_position; i++) {
		auto it = licenses.find((TECHNOLOGIES_AND_BANDS)i);

		uint32_t value;

		if(it == licenses.end())
			value = encryption.encrypt(license_helper::invalid_license_, hw_id, (uint32_t)i);
		else
			value = encryption.encrypt(license_helper::valid_license_, hw_id, (uint32_t)i);

		license_helper::add_license(output_data, value);
	}

	for(license_element_type i = end_wcdma_license_position + 1; i <= last_license_position; i++) {
		uint32_t  value = encryption.encrypt(license_helper::invalid_license_, hw_id, (uint32_t)i);
		license_helper::add_license(output_data, value);
	}

	return output_data;
}


cappeen_license_version_3::cappeen_license_version_3(software_license lic)
	: cappeen_license(lic) 
{}

void cappeen_license_version_3::initialize_license_() {
	valid_licenses_.clear();
	valid_software_licenses_.clear();

	for(license_element_type i = 0; i <= last_license_position; i++) {
		time_t date = find_date(i);
		if(date > license_helper::invalid_license_) {
			// handle special cases (software licenses)
			if(i == network_coverage_license_position)
				valid_software_licenses_.insert(network_coverage_license);

			else if(i == cell_analysis_license_position)
				valid_software_licenses_.insert(cell_analysis_license);

			else {
				auto tmp_licenses = license_map_.get().find(i);
				if(tmp_licenses != license_map_.get().end()) {
					for(auto it = tmp_licenses->second.begin(); it != tmp_licenses->second.end(); ++it)
						valid_licenses_.insert(*it);
				}
			}
		}
	}

	validate_licenses();
}

std::vector<uint8_t> cappeen_license_version_3::generate_license(uint32_t hw_id, const std::set<beagle_api::TECHNOLOGIES_AND_BANDS> &licenses, const std::set<software_license> &software_licenses) {
	encryption encryption;

	std::vector<uint8_t> output_data;

	// License version
	output_data.push_back((uint8_t)0x03);

	// Position of license in EEPROM
	output_data.push_back((uint8_t)0x11);

	uint32_t value;

	for(license_element_type i = 0; i <= last_license_position; i++) {
		bool found_valid_license = false;

		// handle special cases (software licenses)
		if(i == network_coverage_license_position && software_licenses.find(network_coverage_license) != software_licenses.end())
			found_valid_license = true;

		else if(i == cell_analysis_license_position && software_licenses.find(cell_analysis_license) != software_licenses.end())
			found_valid_license = true;
		else {
			auto tmp_licenses = license_map_.get().find(i);
			if(tmp_licenses != license_map_.get().end()) {
				for(auto it = tmp_licenses->second.begin(); it != tmp_licenses->second.end(); ++it) {
					if(licenses.find(*it) != licenses.end()) {
						found_valid_license = true;
						break;
					}
				}
			}
		}

		if(found_valid_license)
			value = encryption.encrypt(license_helper::valid_license_, hw_id, (uint32_t)i);
		else
			value = encryption.encrypt(license_helper::invalid_license_, hw_id, (uint32_t)i);

		license_helper::add_license(output_data, value);
	}

	return output_data;
}


}}


