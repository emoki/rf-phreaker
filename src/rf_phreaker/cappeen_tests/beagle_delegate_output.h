#pragma once

#include <array>
#include <atomic>
#include <mutex>
#include <iomanip>
#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen/operating_band_conversion.h"

using namespace beagle_api;

class output : public beagle_delegate
{
public:
	output() { reinit(); }

	void reinit() { error_occurred_ = false; new_hw_info_ = false; }
	void wait(int s) {
		error_occurred_ = false;
		new_hw_info_ = false;

		for(int i = 0; i < s; ++i) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			if(error_occurred_ || new_hw_info_)
				break;
		}
	}

	virtual void __stdcall available_beagle_info(beagle_id_type beagle_id, const beagle_info &info) {
		{
			std::lock_guard<std::mutex> lock(hw_mutex_);
			hw_ = info;
		}
		std::lock_guard<std::mutex> lock(std_mutex_);
		std::cout << "serial: " << info.beagle_serial_ << "\n";
		std::cout << "hw_id: " << info.beagle_id_ << "\n";
		char mbstr[100];

		auto t1 = localtime(&info.dds_clock_correction_calibration_date_);
		std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&info.dds_clock_correction_calibration_date_));
		std::cout << "dds_clock_corr_date: " << mbstr << "\n"; //std::put_time(t1, "%Y-%m-%d %X") << "\n";

		auto t2 = localtime(&info.rf_calibration_date_);
		std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&info.rf_calibration_date_));
		std::cout << "rf_calibration_date: " << mbstr << "\n"; //std::put_time(t2, "%Y-%m-%d %X") << "\n";

		std::cout << (info.device_speed_ == beagle_api::USB_SUPER_SPEED ? "USB_SUPER_SPEED" : info.device_speed_ == beagle_api::USB_SUPER_SPEED ? "USB_HI_SPEED" : "UNKNOWN_SPEED") << "\n";

		switch(info.state_) {
		case BEAGLESTATE::BEAGLE_USBCLOSED:
			std::cout << "BEAGLE_USB_CLOSED" << "\n";
			break;
		case BEAGLESTATE::BEAGLE_USBOPENED:
			std::cout << "BEAGLE_USB_OPENED" << "\n";
			break;
		case BEAGLESTATE::BEAGLE_ERROR:
			std::cout << "BEAGLE_ERROR" << "\n";
			break;
		case BEAGLESTATE::BEAGLE_COLLECTING:
			std::cout << "BEAGLE_COLLECTING" << "\n";
			break;
		case BEAGLESTATE::BEAGLE_READY:
			std::cout << "BEAGLE_READY" << "\n";
			break;
		case BEAGLESTATE::BEAGLE_WARMINGUP:
			std::cout << "BEAGLE_WARMING_UP" << "\n";
			break;
		case BEAGLESTATE::BEAGLE_CALCULATING_FREQUENCY_CORRECTION:
			std::cout << "BEAGLE_CALCULATING_FREQUENCY_CORRECTION" << "\n";
			break;
		default:
			std::cout << "UNKNOWN_BEAGLE_STATE" << "\n";
		}

		std::cout << "Available bands:\n";
		for(uint32_t i = 0; i < info.available_bands_in_hardware_.num_elements_; ++i) {
			std::cout << "\t" << rf_phreaker::cappeen_api::hw_band_to_string(info.available_bands_in_hardware_.elements_[i]) << "\n";
		}

		std::cout << "Valid licenses:\n";
		for(uint32_t i = 0; i < info.valid_licenses_.num_elements_; ++i) {
			std::cout << "\t" << rf_phreaker::cappeen_api::tech_band_to_string(info.valid_licenses_.elements_[i]) << "\n";
		}

		new_hw_info_ = true;
	}
	virtual void __stdcall available_gps_info(beagle_id_type beagle_id, const gps_info &info) {
		{
			std::lock_guard<std::mutex> lock(gps_mutex_);
			gps_ = info;
		}

		if(info.gps_locked_)
			had_gps_lock_ = true;

		if(!output_) return;
		std::lock_guard<std::mutex> lock(std_mutex_);
		std::cout << beagle_id << "\t" << std::boolalpha << info.gps_locked_ << "\t" << info.utc_time_ << "\t" << info.raw_gps_status_ << "\n";
	}
	virtual void __stdcall available_gsm_sector_info(beagle_id_type beagle_id, const gsm_sector_info *info, long num_records) {
		if(!output_) return;
		std::lock_guard<std::mutex> lock(std_mutex_);
		for(int i = 0; i < num_records; ++i) {
			std::cout << beagle_id << "\t" << info[i].collection_round_ << "\t" << info[i].carrier_freq_ << "\t" << info[i].rssi_ << "\t" << info[i].arfcn_ << "\t" << info[i].bsic_
				<< "\t" << info[i].cell_sl_ << "\t" << info[i].ctoi_ << std::endl;
		}
	}
	virtual void __stdcall available_gsm_sweep_info(beagle_id_type beagle_id, const gsm_sweep_info *info, long num_records) {
		if(!output_) return;
		std::lock_guard<std::mutex> lock(std_mutex_);
		for(int i = 0; i < num_records; ++i)
			std::cout << beagle_id << "\t" << info[i].frequency_ << "\t" << info[i].rssi_ << "\t" << "gsm" << "\n";
	}
	virtual void __stdcall available_umts_sector_info(beagle_id_type beagle_id, const umts_sector_info *info, long num_records) {
		if(!output_) return;
		std::lock_guard<std::mutex> lock(std_mutex_);
		for(int i = 0; i < num_records; ++i) {
			std::cout << beagle_id << "\t" << info[i].carrier_freq_ << "\t" << info[i].carrier_sl_ << "\t" << info[i].cpich_ << "\t" << info[i].ecio_
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
	std::set<frequency_type> tmp;
	virtual void __stdcall available_umts_sweep_info(beagle_id_type beagle_id, const umts_sweep_info *info, long num_records) {
		if(!output_) return;
		std::lock_guard<std::mutex> lock(std_mutex_);
		for(int i = 0; i < num_records; ++i)
			std::cout << beagle_id << "\t" << info[i].frequency_ << "\t" << info[i].rssi_ << "\t" << "umts" << "\n";
	}
	virtual void __stdcall available_lte_sector_info(beagle_id_type beagle_id, const lte_sector_info *info, long num_records) {
		if(!output_) return;
		static std::ofstream lte_output("lte_sector_info.txt");
		for(int i = 0; i < num_records; ++i) {
			std::string t;
			t += std::to_string(beagle_id) + "\t";
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
				for(uint32_t j = 0; j < info[i].sib_1_.plmns_.num_elements_; ++j) {
					auto &k = info[i].sib_1_.plmns_.elements_;
					t += "[" + std::string(k[j].mcc_) + " " + std::string(k[j].mnc_) + "] ";
				}
				t += " | ";
				for(uint32_t j = 0; j < info[i].sib_1_.scheduled_sibs_.num_elements_; ++j) {
					auto &k = info[i].sib_1_.scheduled_sibs_.elements_;
					t += "[" + std::to_string(k[j].sib + 3) + " " + std::to_string(k[j].periodicity_in_frames_) + "f] ";
				}
			}
			t += "\t";
			if(info[i].sib_3_.decoded_) {
				t += "sib3 | ";
				t += std::to_string(info[i].sib_3_.cell_reselection_serving_freq_info_.cell_reselection_priority_) + " "
					+ std::to_string(info[i].sib_3_.cell_reselection_serving_freq_info_.s_non_intra_search_) + " "
					+ std::to_string(info[i].sib_3_.cell_reselection_serving_freq_info_.threshold_serving_low_);
			}
			t += "\t";
			if(info[i].sib_4_.decoded_) {
				t += "sib4 | ";
				t += std::to_string(info[i].sib_4_.csg_physical_cellid_range_.start_) + " " + std::to_string(info[i].sib_4_.csg_physical_cellid_range_.range_) + " | ";
				t += "[";
				for(uint32_t j = 0; j < info[i].sib_4_.intra_freq_neighbor_cell_list_.num_elements_; ++j) {
					auto &k = info[i].sib_4_.intra_freq_neighbor_cell_list_.elements_;
					t += std::to_string(k[j].physical_cell_id_) + " | ";
				}
				t += "] | [";
				for(uint32_t j = 0; j < info[i].sib_4_.intra_freq_black_cell_list_.num_elements_; ++j) {
					auto &k = info[i].sib_4_.intra_freq_black_cell_list_.elements_;
					t += std::to_string(k[j].start_) + " " + std::to_string(k[j].range_) + " | ";
				}
				t += "]";
			}
			t += "\t";
			if(info[i].sib_5_.decoded_) {
				t += "sib5 | ";
				for(uint32_t j = 0; j < info[i].sib_5_.inter_freq_carrier_info_list_.num_elements_; ++j) {
					auto &k = info[i].sib_5_.inter_freq_carrier_info_list_.elements_;
					t += std::to_string(k[j].downlink_arfcn_value_eutra_) + " | ";
					t += std::to_string(k[j].allowed_measurement_bandwidth_) + " | ";
					t += (k[j].presence_antenna_port_1_ ? "TRUE | " : "FALSE | ");
					t += "[";
					for(uint32_t jj = 0; jj < k[j].inter_freq_neighbor_cell_list_.num_elements_; ++jj) {
						auto &kk = k[j].inter_freq_neighbor_cell_list_.elements_;
						t += std::to_string(kk[jj].physical_cell_id_) + " ";
					}
					t += "] | [";
					for(uint32_t jj = 0; jj < k[j].inter_freq_black_cell_list_.num_elements_; ++jj) {
						auto &kk = k[j].inter_freq_black_cell_list_.elements_;
						t += std::to_string(kk[jj].start_) + " " + std::to_string(kk[jj].range_) + " | ";
					}
					t += "] | ";
				}
			}
			t += "\t";
			if(info[i].sib_6_.decoded_) {
				t += "sib6 | [";
				for(uint32_t j = 0; j < info[i].sib_6_.carrier_freq_list_utra_fdd_.num_elements_; ++j) {
					auto &k = info[i].sib_6_.carrier_freq_list_utra_fdd_.elements_;
					t += std::to_string(k[j].arfcn_value_utra_) + " ";
				}
				t += "] | [";
				for(uint32_t j = 0; j < info[i].sib_6_.carrier_freq_list_utra_tdd_.num_elements_; ++j) {
					auto &k = info[i].sib_6_.carrier_freq_list_utra_tdd_.elements_;
					t += std::to_string(k[j].arfcn_value_utra_) + " ";
				}
				t += "] ";
			}
			t += "\t";
			if(info[i].sib_7_.decoded_) {
				t += "sib7 | ";
				for(uint32_t j = 0; j < info[i].sib_7_.carrier_freqs_.num_elements_; ++j) {
					auto &k = info[i].sib_7_.carrier_freqs_.elements_;

					t += std::to_string(k[j].band_indicator_) + " | [";

					for(uint32_t jj = 0; jj < k[j].arfcns_.num_elements_; ++jj) {
						auto &kk = k[j].arfcns_.elements_;
						t += std::to_string(kk[jj]) + " ";
					}
					t += "] | ";
				}
			}
			t += "\t";
			if(info[i].sib_8_.decoded_) {
				t += "sib8 | ";
				for(uint32_t j = 0; j < info[i].sib_8_.parameters_hrpd_.num_elements_; ++j) {
					auto &k = info[i].sib_8_.parameters_hrpd_.elements_;
					t += std::to_string(k[j].arfcn_value_cmda_2000_) + " | ";
					t += std::to_string(k[j].band_) + " | [";
					for(uint32_t jj = 0; jj < k[j].physical_cell_ids_.num_elements_; ++jj) {
						auto &kk = k[j].physical_cell_ids_.elements_;
						t += std::to_string(kk[jj]) + " ";
					}
					t += "] | ";
				}

				for(uint32_t j = 0; j < info[i].sib_8_.parameters_1xrtt_.num_elements_; ++j) {
					auto &k = info[i].sib_8_.parameters_1xrtt_.elements_;
					t += std::to_string(k[j].arfcn_value_cmda_2000_) + " | ";
					t += std::to_string(k[j].band_) + " | [";
					for(uint32_t jj = 0; jj < k[j].physical_cell_ids_.num_elements_; ++jj) {
						auto &kk = k[j].physical_cell_ids_.elements_;
						t += std::to_string(kk[jj]) + " ";
					}
					t += "] | ";
				}
			}

			lte_output << t << std::endl;
			std::lock_guard<std::mutex> lock(std_mutex_);
			std::cout << t << std::endl;
		}
	}
	virtual void __stdcall available_lte_sweep_info(beagle_id_type beagle_id, const lte_sweep_info *info, long num_records) {
		if(!output_) return;
		std::lock_guard<std::mutex> lock(std_mutex_);
		for(int i = 0; i < num_records; ++i)
			std::cout << beagle_id << "\t" << info[i].frequency_ << "\t" << info[i].rssi_ << "\t" << "lte" << "\n";
	}
	virtual void __stdcall available_error(beagle_id_type beagle_id, long error, const char *str, long buf_size) {
		std::lock_guard<std::mutex> lock(std_mutex_);
		std::cout << "----------ERROR-------------  \nCODE: " << error << "\nSTR: " << str << "\nHWID: " << beagle_id << "\t" << "\n";
		error_occurred_ = true;
	}
	virtual void __stdcall available_message(beagle_id_type beagle_id, long possible_message_number, const char *str, long buf_size) {
		std::lock_guard<std::mutex> lock(std_mutex_);
		std::cout << "----------MESSAGE-------------  \nCODE: " << possible_message_number << "\nSTR : " << str << "\nHWID: " << beagle_id << "\t" << "\n";
	}

	beagle_info hw() {
		std::lock_guard<std::mutex> lock(hw_mutex_);
		return hw_;
	}

	gps_info gps() {
		std::lock_guard<std::mutex> lock(gps_mutex_);
		return gps_;
	}

	bool had_gps_lock() { return had_gps_lock_; }

	std::atomic_bool output_;
	std::atomic_bool error_occurred_;
	std::atomic_bool new_hw_info_;
	std::atomic_bool had_gps_lock_;
private:

	std::mutex hw_mutex_;
	std::mutex gps_mutex_;
	std::mutex std_mutex_;
	beagle_info hw_;
	gps_info gps_;
};

class bad_output : public beagle_delegate
{
	virtual void __stdcall available_beagle_info(beagle_id_type beagle_id, const beagle_info &info) {}
	virtual void __stdcall available_gps_info(beagle_id_type beagle_id, const gps_info &info) {}
	virtual void __stdcall available_gsm_sector_info(beagle_id_type beagle_id, const gsm_sector_info *info, long num_records) {}
	virtual void __stdcall available_umts_sector_info(beagle_id_type beagle_id, const umts_sector_info *info, long num_records) {}
	virtual void __stdcall available_umts_sweep_info(beagle_id_type beagle_id, const umts_sweep_info *info, long num_records) {}
	virtual void __stdcall available_lte_sector_info(beagle_id_type beagle_id, const lte_sector_info *info, long num_records) {}
	virtual void __stdcall available_lte_sweep_info(beagle_id_type beagle_id, const lte_sweep_info *info, long num_records) {}
	virtual void __stdcall available_error(beagle_id_type beagle_id, long error, const char *str, long buf_size) { std::cout << str << "\n"; }
	virtual void __stdcall available_message(beagle_id_type beagle_id, long possible_message_number, const char *str, long buf_size) { std::cout << str << "\n"; }
};
