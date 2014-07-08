#pragma once
#include <set>
#include <map>
#include <vector>
#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/scanner/scanner_types.h"
#include "rf_phreaker/common/license.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace cappeen_api {

typedef uint32_t license_element_type;

enum software_license
{
	network_coverage_license,
	cell_analysis_license,
	no_software_license
};

enum software_license_position
{
	gsm_850_license_position,
	gsm_900_license_position,
	gsm_1800_license_position,
	gsm_1900_license_position,
	wcdma_850_license_position,
	wcmda_900_license_position,
	wcdma_1800_license_position,
	wcdma_1900_license_position,
	wcdma_2100_license_position,
	lte_700_license_position, // 729 - 803 MHZ
	lte_850_license_position, // 791 - 894 MHZ
	lte_900_license_position, // 925 - 960 MHZ
	lte_1800_license_position, // 1805 - 1880 MHZ
	lte_1900_license_position, // 1930 - 1995 MHZ
	lte_2100_license_position, // 2100 - 2170 MHZ
	lte_2600_license_position, // 2620 - 2690 MHZ
	network_coverage_license_position,
	cell_analysis_license_position,

	last_license_position = 31,

	begin_gsm_license_position = gsm_850_license_position,
	end_gsm_license_position = gsm_1900_license_position,
	begin_wcdma_license_position = wcdma_850_license_position,
	end_wcdma_license_position = wcdma_2100_license_position,
	begin_lte_license_position = lte_700_license_position,
	end_lte_license_position = lte_2600_license_position,
	begin_application_license_position = network_coverage_license_position,
	end_application_license_position = cell_analysis_license_position

};

#define EEPROMDATASIZE 32 * sizeof(license_element_type);

static const int software_licenses_size = 2;

class encryption
{
public:
	encryption()
		: EncryptionConstant(27)
		, HwIdMultiplier(29)
		, FieldMultiplier(13)
		, HwIdMod(512)
		, FieldMod(32)
		, corrupt_(false) {}

	time_t decrypt(uint32_t data, uint32_t HwId, uint32_t FieldIdx) {
		double AdjHwId = fmod((HwId * HwIdMultiplier), HwIdMod) + 1;
		double AdjFieldIdx = fmod((FieldIdx * FieldMultiplier), FieldMod) + 1;

		double info = ((data - AdjFieldIdx - AdjHwId) / (EncryptionConstant * AdjFieldIdx * AdjHwId)) + 10000;

		if(info - floor(info) > .000001) {
			corrupt_ = true;
			return 0;
		}
		return static_cast<time_t>(floor(info)) * 60 * 60 * 24;
	}

	uint32_t encrypt(time_t TimeExpires, uint32_t HwId, uint32_t FieldIdx) {
		uint32_t AdjTimeExpires = static_cast<uint32_t>(TimeExpires / 60 / 60 / 24);

		double AdjHwId = fmod((HwId * HwIdMultiplier), HwIdMod) + 1;
		double AdjFieldIdx = fmod((FieldIdx * FieldMultiplier), FieldMod) + 1;

		return static_cast<uint32_t>((AdjTimeExpires - 10000) * (EncryptionConstant * AdjFieldIdx * AdjHwId) + AdjFieldIdx + AdjHwId);
	}

	void clear_corruption() { corrupt_ = false; }

	bool is_corrupt() { return corrupt_; }

private:
	bool corrupt_;
	const double EncryptionConstant;
	const double HwIdMultiplier;
	const double HwIdMod;
	const double FieldMultiplier;
	const double FieldMod;
};

class license_helper
{
public:
	static void add_license(std::vector<uint8_t> &license_container, uint32_t license_data);

	static const time_t invalid_license_ = 60 * 60 * 24 * 10000;

	static const time_t valid_license_ = 60 * 60 * 24 * 18307;

};

class license_map_v3
{
public:
	license_map_v3();

	const std::map<int, std::set<beagle_api::TECHNOLOGIES_AND_BANDS>>& get() { return map_; }

private:
	std::map<int, std::set<beagle_api::TECHNOLOGIES_AND_BANDS>> map_;
};

class cappeen_license
{
public:
	cappeen_license(software_license license = no_software_license);

	~cappeen_license();

	void initialize_license(const license &license, const rf_phreaker::scanner::scanner_id_type &serial);

	bool corrupt_license() { return encryption_.is_corrupt(); }

	const std::set<beagle_api::TECHNOLOGIES_AND_BANDS> & valid_licenses() const { return valid_licenses_; }

	const std::set<software_license> & software_licenses() const { return valid_software_licenses_; }

	static license create_new_license_from_file(const std::string &filename);

	static uint32_t serial_to_hwid(const rf_phreaker::scanner::scanner_id_type &serial);

protected:
	void validate_licenses();

	virtual void initialize_license_() = 0;

	time_t find_date(license_element_type position);

	bool initialized_;

	encryption encryption_;

	std::set<beagle_api::TECHNOLOGIES_AND_BANDS> valid_licenses_;

	std::set<software_license> valid_software_licenses_;

	software_license required_license_;

	license license_;

	rf_phreaker::scanner::scanner_id_type serial_;
};

class cappeen_license_version_1 : public cappeen_license
{
public:
	cappeen_license_version_1();

	~cappeen_license_version_1();

protected:
	void initialize_license_();

private:
	void create_us_license();

	void create_euro_license();

	static const license_element_type date_comparison_position_ = 29;
	static const license_element_type us_license_position_ = 16;
	static const license_element_type euro_license_position_ = 17;
};

class cappeen_license_version_2 : public cappeen_license
{
public:
	cappeen_license_version_2();

	static std::vector<uint8_t> generate_license(uint32_t hw_id, const std::set<beagle_api::TECHNOLOGIES_AND_BANDS> &licenses);

protected:
	void initialize_license_();
};

class cappeen_license_version_3 : public cappeen_license
{
public:
	cappeen_license_version_3(software_license lic);

	static std::vector<uint8_t> generate_license(uint32_t hw_id, const std::set<beagle_api::TECHNOLOGIES_AND_BANDS> &licenses, const std::set<software_license> &software_licenses);

protected:
	void initialize_license_();

	static license_map_v3 license_map_;
};


}}