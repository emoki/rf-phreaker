#include "gtest/gtest.h"

#include "rf_phreaker/cappeen/cappeen.h"
#include "rf_phreaker/cappeen/beagle_defines.h"
#include <array>
#include <thread>
#include <atomic>
#include <fstream>

using namespace beagle_api;

class output : public beagle_delegate
{
public:
	output() { error_occurred_ = false; new_hw_info_ = false; }

	virtual void __stdcall available_beagle_info(long beagle_id, const beagle_info &info){
		std::cout << info.beagle_serial_ << "\t" 
			<< (info.device_speed_ == beagle_api::USB_SUPER_SPEED ? "USB_SUPER_SPEED" : "USB_HI_SPEED") 
			<< "\t" << info.state_ << "\n";
		new_hw_info_ = true;
	}
	virtual void __stdcall available_gps_info(long beagle_id, const gps_info &info){
		//std::cout << info.utc_time_ << "\t" << info.raw_gps_status_ << "\n";
	}
	virtual void __stdcall available_gsm_sector_info(long beagle_id, const gsm_sector_info *info, long num_records){}
	virtual void __stdcall available_umts_sector_info(long beagle_id, const umts_sector_info *info, long num_records){
		for(int i = 0; i < num_records; ++i) {
			std::cout << info[i].carrier_freq_ << "\t" << info[i].carrier_sl_ << "\t" << info[i].cpich_ << "\t" << info[i].ecio_
				<< "\t" << info[i].mcc_
				<< "\t" << info[i].mnc_
				<< "\t" << info[i].lac_
				<< "\t" << info[i].cell_id_;
			if(info[i].neighbor_intra_group_.num_elements_ || info[i].neighbor_inter_group_.num_elements_ || info[i].neighbor_inter_rat_gsm_group_.num_elements_)
				std::cout << "\t" << info[i].neighbor_intra_group_.num_elements_
				<< "\t" << info[i].neighbor_inter_group_.num_elements_
				<< "\t" << info[i].neighbor_inter_rat_gsm_group_.num_elements_
				<< "------------------------------------------------------------------------------------------\n";
			else
				std::cout << "\n";
			tmp.insert(info[i].carrier_freq_);
		}
	}
	std::set<double> tmp;
	virtual void __stdcall available_umts_sweep_info(long beagle_id, const umts_sweep_info *info, long num_records){
		for(int i = 0; i < num_records; ++i)
			std::cout << info[i].frequency_ << "\t" << info[i].rssi_ << "\t" << "umts" << "\n";
	}
	virtual void __stdcall available_lte_sector_info(long beagle_id, const lte_sector_info *info, long num_records)
	{
		static std::ofstream lte_output("lte_sector_info.txt");
		for(int i = 0; i < num_records; ++i) {
			std::string t;
			t += std::to_string(info[i].collection_round_) + "\t";
			t += std::to_string(info[i].carrier_freq_ / 1e6) + "\t";
			t += std::to_string(info[i].carrier_bandwidth_ / 1e6) + "\t";
			t += std::to_string(info[i].earfcn_) + "\t";
			t += std::to_string(info[i].lte_operating_band_) + "\t";
			t += std::to_string(info[i].antenna_ports_) + "\t";
			t += std::to_string(info[i].system_frame_number_) + "\t";
			t += std::to_string(info[i].physical_cell_id_) + "\t";
			t += std::to_string(info[i].rssi_) + "\t";
			t += std::to_string(info[i].rsrp_) + "\t";
			t += std::to_string(info[i].rsrq_) + "\t";
			t += std::to_string(info[i].cyclic_prefix_length_) + "\t";
			t += std::to_string(info[i].primary_sync_id_) + "\t";
			t += std::to_string(info[i].primary_sync_quality_) + "\t";
			t += std::to_string(info[i].secondary_sync_id_) + "\t";
			t += std::to_string(info[i].secondary_sync_quality_) + "\t";
			if(info[i].sib_1_.decoded_) {
				t += "sib1 | ";
				t += std::to_string(info[i].sib_1_.tac_) + " | ";
				t += std::to_string(info[i].sib_1_.cid_) + " | ";
				for(int j = 0; j < info[i].sib_1_.plmns_.num_elements_; ++j) {
					auto &k = info[i].sib_1_.plmns_.elements_;
					t += "[" + std::string(k[j].mcc_) + " " + std::string(k[j].mnc_) + "] ";
				}
				t += " | ";
				for(int j = 0; j < info[i].sib_1_.scheduled_sibs_.num_elements_; ++j) {
					auto &k = info[i].sib_1_.scheduled_sibs_.elements_;
					t += "[" + std::to_string(k[j].sib + 3) + " " + std::to_string(k[j].periodicity_in_frames_) + "f] ";
				}
			}
			t += "\t";
			if(info[i].sib_4_.decoded_) {
				t += "sib4 | ";
				t += std::to_string(info[i].sib_4_.csg_physical_cellid_range_.start_) + " " + std::to_string(info[i].sib_4_.csg_physical_cellid_range_.range_) + " | ";
				t += "[";
				for(int j = 0; j < info[i].sib_4_.intra_freq_neighbor_cell_list_.num_elements_; ++j) {
					auto &k = info[i].sib_4_.intra_freq_neighbor_cell_list_.elements_;
					t += std::to_string(k[j].physical_cell_id_) + " | ";
				}
				t += "] | [";
				for(int j = 0; j < info[i].sib_4_.intra_freq_black_cell_list_.num_elements_; ++j) {
					auto &k = info[i].sib_4_.intra_freq_black_cell_list_.elements_;
					t += std::to_string(k[j].start_) + " " + std::to_string(k[j].range_) + " | ";
				}
				t += "]";
			}
			t += "\t";
			if(info[i].sib_5_.decoded_) {
				t += "sib5 | ";
				for(int j = 0; j < info[i].sib_5_.inter_freq_carrier_info_list_.num_elements_; ++j) {
					auto &k = info[i].sib_5_.inter_freq_carrier_info_list_.elements_;
					t += std::to_string(k[j].downlink_arfcn_value_eutra_) + " | ";
					t += std::to_string(k[j].allowed_measurement_bandwidth_) + " | ";
					t += (k[j].presence_antenna_port_1_ ? "TRUE | " : "FALSE | ");
					t += "[";
					for(int jj = 0; jj < k[j].inter_freq_neighbor_cell_list_.num_elements_; ++jj) {
						auto &kk = k[j].inter_freq_neighbor_cell_list_.elements_;
						t += std::to_string(kk[jj].physical_cell_id_) + " ";
					}
					t += "] | [";
					for(int jj = 0; jj < k[j].inter_freq_black_cell_list_.num_elements_; ++jj) {
						auto &kk = k[j].inter_freq_black_cell_list_.elements_;
						t += std::to_string(kk[jj].start_) + " " + std::to_string(kk[jj].range_) + " | ";
					}
					t += "] | ";
				}
			}
			t += "\t";
			if(info[i].sib_6_.decoded_) {
				t += "sib6 | [";
				for(int j = 0; j < info[i].sib_6_.carrier_freq_list_utra_fdd_.num_elements_; ++j) {
					auto &k = info[i].sib_6_.carrier_freq_list_utra_fdd_.elements_;
					t += std::to_string(k[j]) + " ";
				}
				t += "] | [";
				for(int j = 0; j < info[i].sib_6_.carrier_freq_list_utra_tdd_.num_elements_; ++j) {
					auto &k = info[i].sib_6_.carrier_freq_list_utra_tdd_.elements_;
					t += std::to_string(k[j]) + " ";
				}
				t += "] ";
			}
			t += "\t";
			if(info[i].sib_7_.decoded_) {
				t += "sib7 | ";
				for(int j = 0; j < info[i].sib_7_.carrier_freqs_.num_elements_; ++j) {
					auto &k = info[i].sib_7_.carrier_freqs_.elements_;

					t += std::to_string(k[j].band_indicator_) + " | [";

					for(int jj = 0; jj < k[j].arfcns_.num_elements_; ++jj) {
						auto &kk = k[j].arfcns_.elements_;
						t += kk[jj] + " ";
					}
					t += "] | ";
				}
			}
			t += "\t";
			if(info[i].sib_8_.decoded_) {
				t += "sib8 | ";
				for(int j = 0; j < info[i].sib_8_.parameters_hrpd_.num_elements_; ++j) {
					auto &k = info[i].sib_8_.parameters_hrpd_.elements_;
					t += std::to_string(k[j].arfcn_value_cmda_2000_) + " | ";
					t += std::to_string(k[j].band_) + " | [";
					for(int jj = 0; jj < k[j].physical_cell_ids_.num_elements_; ++jj) {
						auto &kk = k[j].physical_cell_ids_.elements_;
						t += kk[jj] + " ";
					}
					t += "] | ";
				}

				for(int j = 0; j < info[i].sib_8_.parameters_1xrtt_.num_elements_; ++j) {
					auto &k = info[i].sib_8_.parameters_1xrtt_.elements_;
					t += std::to_string(k[j].arfcn_value_cmda_2000_) + " | ";
					t += std::to_string(k[j].band_) + " | [";
					for(int jj = 0; jj < k[j].physical_cell_ids_.num_elements_; ++jj) {
						auto &kk = k[j].physical_cell_ids_.elements_;
						t += kk[jj] + " ";
					}
					t += "] | ";
				}
			}

			std::cout << t << std::endl;
			lte_output << t << std::endl;
		}
	}
	virtual void __stdcall available_lte_sweep_info(long beagle_id, const lte_sweep_info *info, long num_records)
	{
		for(int i = 0; i < num_records; ++i)
			std::cout << info[i].frequency_ << "\t" << info[i].rssi_ << "\t" << "lte" << "\n";
	}
	virtual void __stdcall available_error(long beagle_id, long error, const char *str, long buf_size) 
	{ 
		std::cout << str << "\n"; 
		error_occurred_ = true; 
	}
	virtual void __stdcall available_message(long beagle_id, long possible_message_number, const char *str, long buf_size) 
	{ 
		std::cout << str << "\n";
	}

	std::atomic_bool error_occurred_;
	std::atomic_bool new_hw_info_;
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
		tech_bands.push_back(WCDMA_BAND_850);
		tech_bands.push_back(WCDMA_BAND_1900);
		tech_bands.push_back(WCDMA_BAND_2100);
		//tech_bands.push_back(WCDMA_BAND_900);
		//tech_bands.push_back(WCDMA_BAND_1800);
		tech_bands.push_back(LTE_BAND_12);
		tech_bands.push_back(LTE_BAND_5);
		tech_bands.push_back(LTE_BAND_2);
		tech_bands.push_back(LTE_BAND_1);
		info.tech_and_bands_to_sweep_.elements_ = &tech_bands[0];
		info.tech_and_bands_to_sweep_.num_elements_ = tech_bands.size();

		for(int i = 0; i < 5000000; ++i) {
			out.new_hw_info_ = false;
			out.error_occurred_ = false;
			EXPECT_EQ(0, cappeen_open_unit(&serial[0], serial.size()));

			//std::cout << "Starting frequency correction.\n";
			//std::vector<uint32_t> freqs; freqs.push_back(871600000); freqs.push_back(2142500000); freqs.push_back(1977500000);
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