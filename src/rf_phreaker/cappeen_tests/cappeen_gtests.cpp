#include "gtest/gtest.h"

#include <thread>
#include <fstream>
#include <ctime>
#include "rf_phreaker/cappeen_tests/beagle_delegate_output.h"
#include "rf_phreaker/cappeen/cappeen.h"
#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen/cappeen_license.h"

using namespace beagle_api;


TEST(Cappeen, TestMain)
{
	//system("pause");

	std::cout << cappeen_api_version() << std::endl;

	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;
		info.tech_and_bands_to_sweep_.elements_ = 0;
		info.tech_and_bands_to_sweep_.num_elements_ = 0;;
		tech_bands.push_back(WCDMA_BAND_850);
		tech_bands.push_back(WCDMA_BAND_1900);
		tech_bands.push_back(WCDMA_BAND_2100);
		//tech_bands.push_back(WCDMA_BAND_900);
		//tech_bands.push_back(WCDMA_BAND_1800);
		//tech_bands.push_back(LTE_BAND_12);
		tech_bands.push_back(LTE_BAND_5);
		tech_bands.push_back(LTE_BAND_2);
		tech_bands.push_back(LTE_BAND_1);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();

		for(int i = 0; i < 5000000; ++i) {
			EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			out.new_hw_info_ = false;
			out.error_occurred_ = false;

			//std::cout << "Starting frequency correction.\n";
			//std::vector<uint32_t> freqs; 
			//freqs.push_back(871800000); 
			//freqs.push_back(876800000); 
			//freqs.push_back(1942500000);
			//freqs.push_back(1937500000); 
			//freqs.push_back(2147500000);
			//freqs.push_back(2152500000);
			//EXPECT_EQ(0, cappeen_start_frequency_correction_using_frequencies(&freqs[0], freqs.size()));
			//EXPECT_EQ(0, cappeen_start_frequency_correction_using_sweep(info));
			//for(int i = 0; i < 10000; ++i) {
			//	std::this_thread::sleep_for(std::chrono::seconds(1));
			//	if(out.error_occurred_ || out.new_hw_info_)
			//		break;
			//}

			std::cout << "Starting collection.\n";
			EXPECT_EQ(0, cappeen_start_collection(info));

			for(int i = 0; i < 60*60; ++i) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				if(out.error_occurred_)
					break;
			}

			//bad_output bad_out;
			//EXPECT_EQ(0, cappeen_initialize(&bad_out));

			if(!out.error_occurred_) {
				EXPECT_EQ(0, cappeen_stop_collection());
				EXPECT_EQ(0, cappeen_close_unit(&serial[0], serial.size()));
			}
			else {
				do {
					EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));
					std::string serial(&serials[0]);
					serial = serial.substr(0, serial.find_first_of(';'));
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
				while(serial.empty());
				out.error_occurred_ = false;
			}
		}
	}

	EXPECT_EQ(0, cappeen_clean_up());
	//system("pause");
}

TEST(Cappeen, DISABLED_FreqNotInCalibration) {
	using namespace rf_phreaker::cappeen_api;
	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {
		EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));

		// We manually have to jump the code for now.
		cappeen_license_version_3 v3(cell_analysis_license);
		std::set<TECHNOLOGIES_AND_BANDS> band_licenses;
		band_licenses.insert(LTE_BAND_12);
		std::set<software_license> soft_licenses;
		soft_licenses.insert(network_coverage_license);
		soft_licenses.insert(cell_analysis_license);

		std::string license_filename = "v3_everything.bin";
		auto raw = v3.generate_license(cappeen_license::serial_to_hwid(serial), band_licenses, soft_licenses);
		{
			std::ofstream f(license_filename.c_str(), std::ios::binary);
			f.write((char*)&raw[0], raw.size());
		}
		EXPECT_EQ(0, cappeen_input_new_license(serial.c_str(), serial.size(), license_filename.c_str(), license_filename.size()));

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;		
		tech_bands.push_back(LTE_BAND_12); // operating band[1475.9 - 1495.9 MHZ]
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();
		std::cout << "Starting collection.\n";
		
		EXPECT_EQ(FREQNOTWITHINCALIBRATIONLIMITS, cappeen_start_collection(info));
		EXPECT_EQ(0, cappeen_close_unit(serial.c_str(), serial.size()));
		EXPECT_EQ(0, cappeen_clean_up());
	}
}

TEST(Cappeen, DISABLED_GeneralLicenseUpdate1) {
	using namespace rf_phreaker::cappeen_api;
	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {
		EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));

		cappeen_license_version_3 v3(cell_analysis_license);
		std::set<TECHNOLOGIES_AND_BANDS> band_licenses;
		band_licenses.insert(WCDMA_BAND_850);
		band_licenses.insert(WCDMA_BAND_900);
		band_licenses.insert(WCDMA_BAND_2100);
		band_licenses.insert(LTE_BAND_1);
		band_licenses.insert(LTE_BAND_2);
		band_licenses.insert(LTE_BAND_20);
		std::set<software_license> soft_licenses;
		soft_licenses.insert(cell_analysis_license);

		std::string license_filename = "v3_license.bin";
		auto raw = v3.generate_license(cappeen_license::serial_to_hwid(serial), band_licenses, soft_licenses);
		{
			std::ofstream f(license_filename.c_str(), std::ios::binary);
			f.write((char*)&raw[0], raw.size());
		}
		EXPECT_EQ(GENERAL_ERROR, cappeen_input_new_license("12345", 6, license_filename.c_str(), license_filename.size()));
		EXPECT_EQ(CORRUPTLICENSE, cappeen_input_new_license("47d54d57db30c9169c98c53e30c08d9a", 6, license_filename.c_str(), license_filename.size()));
		EXPECT_EQ(GENERAL_ERROR, cappeen_input_new_license(serial.c_str(), serial.size(), "bad_filename", sizeof("bad_filename")));
		EXPECT_EQ(0, cappeen_input_new_license(serial.c_str(), serial.size(), license_filename.c_str(), license_filename.size()));

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;
		info.tech_and_bands_to_sweep_.elements_ = 0;
		info.tech_and_bands_to_sweep_.num_elements_ = 0;;
		tech_bands.push_back(WCDMA_BAND_1900);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();
		std::cout << "Starting collection - FAILURE.\n";
		EXPECT_EQ(FREQNOTLICENSED, cappeen_start_collection(info));

		tech_bands.clear();
		tech_bands.push_back(WCDMA_BAND_850);
		tech_bands.push_back(WCDMA_BAND_2100);
		tech_bands.push_back(WCDMA_BAND_1900);
		tech_bands.push_back(LTE_BAND_27);
		tech_bands.push_back(LTE_BAND_26);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();
		std::cout << "Starting collection - FAILURE.\n";
		EXPECT_EQ(FREQNOTLICENSED, cappeen_start_collection(info));


		tech_bands.clear();
		tech_bands.push_back(WCDMA_BAND_2100);
		tech_bands.push_back(LTE_BAND_27);
		tech_bands.push_back(LTE_BAND_26);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();
		std::cout << "Starting collection.\n";
		EXPECT_EQ(0, cappeen_start_collection(info));
		EXPECT_EQ(WRONGBEAGLESTATE, cappeen_input_new_license(serial.c_str(), serial.size(), license_filename.c_str(), license_filename.size()));
		EXPECT_EQ(0, cappeen_stop_collection());
		EXPECT_EQ(0, cappeen_close_unit(serial.c_str(), serial.size()));
		EXPECT_EQ(0, cappeen_clean_up());
	}
}

TEST(Cappeen, DISABLED_GeneralLicenseUpdate2) {
	using namespace rf_phreaker::cappeen_api;
	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {
		EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));

		cappeen_license_version_3 v3(cell_analysis_license);
		std::set<TECHNOLOGIES_AND_BANDS> band_licenses;
		band_licenses.insert(WCDMA_BAND_1800);
		band_licenses.insert(WCDMA_BAND_1900);
		band_licenses.insert(LTE_BAND_3);
		band_licenses.insert(LTE_BAND_8);
		std::set<software_license> soft_licenses;
		soft_licenses.insert(cell_analysis_license);

		std::string license_filename = "v3_license.bin";
		auto raw = v3.generate_license(cappeen_license::serial_to_hwid(serial), band_licenses, soft_licenses);
		{
			std::ofstream f(license_filename.c_str(), std::ios::binary);
			f.write((char*)&raw[0], raw.size());
		}
		EXPECT_EQ(0, cappeen_input_new_license(serial.c_str(), serial.size(), license_filename.c_str(), license_filename.size()));

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;
		tech_bands.push_back(WCDMA_BAND_1800);
		tech_bands.push_back(WCDMA_BAND_1900);
		tech_bands.push_back(LTE_BAND_3);
		tech_bands.push_back(LTE_BAND_8);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();
		std::cout << "Starting collection.\n";
		EXPECT_EQ(0, cappeen_start_collection(info));
		EXPECT_EQ(0, cappeen_stop_collection());
		EXPECT_EQ(0, cappeen_close_unit(serial.c_str(), serial.size()));
		EXPECT_EQ(0, cappeen_clean_up());
	}
}

TEST(Cappeen, DISABLED_LicenseNetworkScanner) {
	using namespace rf_phreaker::cappeen_api;
	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {
		EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));

		cappeen_license_version_3 v3(cell_analysis_license);
		std::set<TECHNOLOGIES_AND_BANDS> band_licenses;
		band_licenses.insert(WCDMA_BAND_1800);
		band_licenses.insert(WCDMA_BAND_1900);
		band_licenses.insert(LTE_BAND_3);
		band_licenses.insert(LTE_BAND_8);
		band_licenses.insert(LTE_BAND_12);
		std::set<software_license> soft_licenses;
		soft_licenses.insert(network_coverage_license);

		std::string license_filename = "v3_license.bin";
		auto raw = v3.generate_license(cappeen_license::serial_to_hwid(serial), band_licenses, soft_licenses);
		{
			std::ofstream f(license_filename.c_str(), std::ios::binary);
			f.write((char*)&raw[0], raw.size());
		}
		EXPECT_EQ(0, cappeen_input_new_license(serial.c_str(), serial.size(), license_filename.c_str(), license_filename.size()));

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;
		tech_bands.push_back(WCDMA_BAND_1800);
		tech_bands.push_back(WCDMA_BAND_1900);
		tech_bands.push_back(LTE_BAND_3);
		tech_bands.push_back(LTE_BAND_8);
		tech_bands.push_back(LTE_BAND_12);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();
		std::cout << "Starting collection.\n";
		EXPECT_EQ(FREQNOTLICENSED, cappeen_start_collection(info));
		EXPECT_EQ(0, cappeen_close_unit(serial.c_str(), serial.size()));
		EXPECT_EQ(0, cappeen_clean_up());
	}
}

TEST(Cappeen, DISABLED_LicenseCellAnalysisEverything) {
	using namespace rf_phreaker::cappeen_api;
	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {
		EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));

		cappeen_license_version_3 v3(cell_analysis_license);
		std::set<TECHNOLOGIES_AND_BANDS> band_licenses;
		band_licenses.insert(WCDMA_BAND_850);
		band_licenses.insert(WCDMA_BAND_900);
		band_licenses.insert(WCDMA_BAND_1800);
		band_licenses.insert(WCDMA_BAND_1900);
		band_licenses.insert(WCDMA_BAND_2100);
		band_licenses.insert(LTE_BAND_5);
		band_licenses.insert(LTE_BAND_8);
		band_licenses.insert(LTE_BAND_3);
		band_licenses.insert(LTE_BAND_2);
		band_licenses.insert(LTE_BAND_1);
		band_licenses.insert(LTE_BAND_7);
		std::set<software_license> soft_licenses;
		soft_licenses.insert(network_coverage_license);
		soft_licenses.insert(cell_analysis_license);

		std::string license_filename = "v3_everything.bin";
		auto raw = v3.generate_license(cappeen_license::serial_to_hwid(serial), band_licenses, soft_licenses);
		{
			std::ofstream f(license_filename.c_str(), std::ios::binary);
			f.write((char*)&raw[0], raw.size());
		}
		EXPECT_EQ(0, cappeen_input_new_license(serial.c_str(), serial.size(), license_filename.c_str(), license_filename.size()));

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;
		tech_bands.push_back(WCDMA_BAND_850);
		tech_bands.push_back(WCDMA_BAND_900);
		tech_bands.push_back(WCDMA_BAND_1800);
		tech_bands.push_back(WCDMA_BAND_1900);
		tech_bands.push_back(WCDMA_BAND_2100);
		tech_bands.push_back(LTE_BAND_5);// operating band 5 [869 - 894 MHZ]
		tech_bands.push_back(LTE_BAND_6);// operating band 6 [875 - 885 MHZ]
		tech_bands.push_back(LTE_BAND_18);// operating band  [860 - 875 MHZ]
		tech_bands.push_back(LTE_BAND_19);// operating band  [875 - 890 MHZ]
		tech_bands.push_back(LTE_BAND_20);// operating band 20 [791 - 821 MHZ]
		tech_bands.push_back(LTE_BAND_26);// operating band  [859 - 894 MHZ]
		tech_bands.push_back(LTE_BAND_27);// operating band  [852 - 869 MHZ]
		tech_bands.push_back(LTE_BAND_8);// operating band 8 [925 - 960 MHZ]
		tech_bands.push_back(LTE_BAND_3);// operating band 3 [1805 - 1880 MHZ]
		tech_bands.push_back(LTE_BAND_9);// operating band 9 [1844.9 - 1879.9 MHZ]
		tech_bands.push_back(LTE_BAND_2);// operating band 2 [1930 - 1990 MHZ]
		tech_bands.push_back(LTE_BAND_25);// operating band  [1930 - 1995 MHZ]
		tech_bands.push_back(LTE_BAND_1);// operating band 1 [2110 - 2170 MHZ]
		tech_bands.push_back(LTE_BAND_4);// operating band 4 [2110 - 2155 MHZ]
		tech_bands.push_back(LTE_BAND_10);// operating band  [2110 - 2170 MHZ]
		tech_bands.push_back(LTE_BAND_7); // operating band 7 [2620 - 2690 MHZ]
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();
		std::cout << "Starting collection.\n";
		EXPECT_EQ(0, cappeen_start_collection(info));
		EXPECT_EQ(0, cappeen_close_unit(serial.c_str(), serial.size()));
		EXPECT_EQ(0, cappeen_clean_up());
	}
}

TEST(Cappeen, DISABLED_NoClose)
{
	//system("pause");

	std::cout << cappeen_api_version() << std::endl;

	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;
		tech_bands.push_back(LTE_BAND_1);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();

		EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));
		EXPECT_EQ(0, cappeen_start_collection(info));

		std::this_thread::sleep_for(std::chrono::seconds(1));

		EXPECT_EQ(0, cappeen_stop_collection());
	}
	EXPECT_EQ(0, cappeen_clean_up());
}

TEST(Cappeen, DISABLED_NoCloseNoStop)
{
	std::cout << cappeen_api_version() << std::endl;

	output out;
	EXPECT_EQ(0, cappeen_initialize(&out));

	std::array<char, 1024 * 10> serials;
	EXPECT_EQ(0, cappeen_list_available_units(&serials[0], serials.size()));

	std::string serial(&serials[0]);
	serial = serial.substr(0, serial.find_first_of(';'));

	if(!serial.empty()) {

		collection_info info;
		info.collection_filename_ = "test_file";
		std::vector<TECHNOLOGIES_AND_BANDS> tech_bands;
		tech_bands.push_back(LTE_BAND_1);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();

		EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));
		EXPECT_EQ(0, cappeen_start_collection(info));

		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	EXPECT_EQ(0, cappeen_clean_up());
}
