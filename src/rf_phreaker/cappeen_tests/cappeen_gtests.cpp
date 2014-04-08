#include "gtest/gtest.h"

#include "rf_phreaker/cappeen/cappeen.h"
#include "rf_phreaker/cappeen/beagle_defines.h"
#include <array>
#include <thread>
#include <atomic>

using namespace beagle_api;

class output : public beagle_delegate
{
public:
	output() { error_occurred_ = false; }

	virtual void __stdcall available_beagle_info(long beagle_id, const beagle_info &info){
		std::cout << info.beagle_serial_ << "\t" << info.state_ << "\n";
	}
	virtual void __stdcall available_gps_info(long beagle_id, const gps_info &info){
		std::cout << info.utc_time_ << "\t" << info.raw_gps_status_ << "\n";
	}
	virtual void __stdcall available_gsm_sector_info(long beagle_id, const gsm_sector_info *info, long num_records){}
	virtual void __stdcall available_umts_sector_info(long beagle_id, const umts_sector_info *info, long num_records){
		for(int i = 0; i < num_records; ++i)
			std::cout << info[i].carrier_freq_ << "\t" << info[i].carrier_sl_ << "\t" << info[i].cpich_ << "\t" << info[i].ecio_ 
				<< "\t" << info[i].mcc_
				<< "\t" << info[i].mnc_
				<< "\t" << info[i].lac_
				<< "\t" << info[i].cell_id_
				<< "\t" << info[i].neighbor_intra_group_.num_elements_
				<< "\t" << info[i].neighbor_inter_group_.num_elements_ 
				<< "\t" << info[i].gsm_neighbor_inter_rat_group_.num_elements_ 
				<< "------------------------------------------------------------------------------------------\n";
	}
	virtual void __stdcall available_umts_sweep_info(long beagle_id, const umts_sweep_info *info, long num_records){
		for(int i = 0; i < num_records; ++i)
			std::cout << info[i].frequency_ << "\t" << info[i].rssi_ << "\t" << "umts" << "\n";
	}
	virtual void __stdcall available_lte_sector_info(long beagle_id, const lte_sector_info *info, long num_records){
		for(int i = 0; i < num_records; ++i)
			std::cout << info[i].carrier_freq_ << "\t" << info[i].carrier_sl_ << "\t" << info[i].physical_cell_id_ << "\t" << info[i].rsrp_ << "\t" << info[i].secondary_sync_quality_
			<< "\t" << (info[i].sib_1_.decoded_ ? "true" : "false") 
			<< "------------------------------------------------------------------------------------------------\n";
	}

	virtual void __stdcall available_lte_sweep_info(long beagle_id, const lte_sweep_info *info, long num_records)
	{
		for(int i = 0; i < num_records; ++i)
			std::cout << info[i].frequency_ << "\t" << info[i].rssi_ << "\t" << "lte" << "\n";
	}
	virtual void __stdcall available_error(long beagle_id, long error, const char *str, long buf_size) { std::cout << str << "\n"; error_occurred_ = true; }
	virtual void __stdcall available_message(long beagle_id, long possible_message_number, const char *str, long buf_size) { std::cout << str << "\n"; }

	std::atomic_bool error_occurred_;
};

class bad_output : public beagle_delegate
{
	virtual void __stdcall available_beagle_info(long beagle_id, const beagle_info &info) {}
	virtual void __stdcall available_gps_info(long beagle_id, const gps_info &info) {}
	virtual void __stdcall available_gsm_sector_info(long beagle_id, const gsm_sector_info *info, long num_records) {}
	virtual void __stdcall available_umts_sector_info(long beagle_id, const umts_sector_info *info, long num_records) {}
	virtual void __stdcall available_umts_sweep_info(long beagle_id, const umts_sweep_info *info, long num_records) {}
	virtual void __stdcall available_lte_sector_info(long beagle_id, const lte_sector_info *info, long num_records) {}
	virtual void __stdcall available_lte_sweep_info(long beagle_id, const lte_sweep_info *info, long num_records) {}
	virtual void __stdcall available_error(long beagle_id, long error, const char *str, long buf_size) { std::cout << str << "\n"; }
	virtual void __stdcall available_message(long beagle_id, long possible_message_number, const char *str, long buf_size) { std::cout << str << "\n"; }
};

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
		//tech_bands.push_back(WCDMA_BAND_850);
		//tech_bands.push_back(WCDMA_BAND_900);
		//tech_bands.push_back(WCDMA_BAND_1900);
		//tech_bands.push_back(WCDMA_BAND_1800);
		tech_bands.push_back(WCDMA_BAND_2100);
		tech_bands.push_back(LTE_BAND_1);
		//tech_bands.push_back(LTE_BAND_12);
		//tech_bands.push_back(LTE_BAND_2);
		//tech_bands.push_back(LTE_BAND_5);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();

		for(int i = 0; i < 5000000; ++i) {
			EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));

			EXPECT_EQ(0, cappeen_start_frequency_correction(info));

			for(int i = 0; i < 10000; ++i) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				if(out.error_occurred_)
					break;
			}

			EXPECT_EQ(0, cappeen_start_collection(info));

			for(int i = 0; i < 1000; ++i) {
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

TEST(Cappeen, NoCleanup)
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

		std::this_thread::sleep_for(std::chrono::seconds(10));

		EXPECT_EQ(0, cappeen_stop_collection());
		EXPECT_EQ(0, cappeen_close_unit(&serial[0], serial.size()));
	}
}

TEST(Cappeen, NoCleanupNoClose)
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
}

TEST(Cappeen, NoCleanupNoCloseNoStop)
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

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}