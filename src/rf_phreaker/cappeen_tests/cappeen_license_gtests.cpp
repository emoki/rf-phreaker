#include "gtest/gtest.h"
#include <fstream>
#include <memory>
#include "rf_phreaker/cappeen/cappeen_license.h"

TEST(CappeenLicense, TestMain) {
	using namespace beagle_api;
	using namespace rf_phreaker::cappeen_api;
	using namespace rf_phreaker::scanner;

	{
		std::shared_ptr<cappeen_license> v3 = std::make_shared<cappeen_license_version_3>(cell_analysis_license);
		auto scanner_license = v3->create_new_license_from_file("NST_e419f6fd676170d5.lic");
		v3->initialize_license(scanner_license, "77ecda454d25738ee419f6fd676170d5");
		auto v3_band_licenses = v3->valid_licenses();
		auto v3_software_licenses = v3->software_licenses();
	}

	std::set<TECHNOLOGIES_AND_BANDS> band_licenses;
	band_licenses.insert(GSM_BAND_1900);
	band_licenses.insert(GSM_BAND_1800);
	band_licenses.insert(WCDMA_BAND_1800);
	band_licenses.insert(WCDMA_BAND_1800);
	band_licenses.insert(WCDMA_BAND_2100);
	band_licenses.insert(LTE_BAND_19);
	band_licenses.insert(LTE_BAND_14);
	//band_licenses.insert(LTE_BAND_12);
	//band_licenses.insert(LTE_BAND_5);
	//band_licenses.insert(LTE_BAND_8);
	//band_licenses.insert(LTE_BAND_3);
	//band_licenses.insert(LTE_BAND_2);
	//band_licenses.insert(LTE_BAND_1);
	//band_licenses.insert(LTE_BAND_7);
	
	std::set<software_license> software_licenses;
	software_licenses.insert(network_coverage_license);
	software_licenses.insert(cell_analysis_license);

	auto raw_license_v2 = cappeen_license_version_2::generate_license(cappeen_license::serial_to_hwid("0123456789abcdef0123456789abcdef"), band_licenses);
	{
		std::ofstream f("test_license_v2", std::ios::binary);
		if(!f)
			GTEST_FATAL_FAILURE_("Failed to create v2 test license file.");
		f.write((char*)&raw_license_v2[0], raw_license_v2.size());
	}

	auto raw_license_v3 = cappeen_license_version_3::generate_license(cappeen_license::serial_to_hwid("0123456789abcdef0123456789abcdef"), band_licenses, software_licenses);
	{
		std::ofstream f("test_license_v3", std::ios::binary);
		if(!f)
			GTEST_FATAL_FAILURE_("Failed to create v3 test license file.");
		f.write((char*)&raw_license_v3[0], raw_license_v3.size());
	}

	{
		std::shared_ptr<cappeen_license> v2 = std::make_shared<cappeen_license_version_2>();
		auto scanner_license = v2->create_new_license_from_file("test_license_v2");
		v2->initialize_license(scanner_license, "0123456789abcdef0123456789abcdef");
		auto v2_band_licenses = v2->valid_licenses();
		auto v2_software_licenses = v2->software_licenses();
	}
	{
		std::shared_ptr<cappeen_license> v3 = std::make_shared<cappeen_license_version_3>(cell_analysis_license);
		auto scanner_license = v3->create_new_license_from_file("test_license_v3");
		v3->initialize_license(scanner_license, "0123456789abcdef0123456789abcdef");
		auto v3_band_licenses = v3->valid_licenses();
		auto v3_software_licenses = v3->software_licenses();
	}
}