#pragma once

#include <boost/thread.hpp>

#include <list>

#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen_console_app/helper_structs.h"

namespace cappeen_scanner {


class cappeen_delegate : public beagle_api::beagle_delegate
{
public:
	cappeen_delegate();

	__stdcall ~cappeen_delegate(void);

	void timed_wait_for_data(boost::shared_ptr<boost::thread> waiting_thread);

	void wake_thread();

	std::list<beagle_info_wrapper> retrieve_beagle_list();

	std::list<gps_info_wrapper> retrieve_gps_list();

	std::list<gsm_sector_info_wrapper> retrieve_gsm_sector_list();

	std::list<gsm_sweep_info_wrapper> retrieve_gsm_sweep_list();

	std::list<umts_sector_info_wrapper> retrieve_umts_sector_list();

	std::list<umts_sweep_info_wrapper> retrieve_umts_sweep_list();

	std::list<lte_sector_info_wrapper> retrieve_lte_sector_list();

	std::list<lte_sweep_info_wrapper> retrieve_lte_sweep_list();

	std::list<api_string> retrieve_error_list();

	std::list<api_string> retrieve_message_list();

	void __stdcall available_beagle_info(beagle_api::beagle_id_type beagle_id, const beagle_api::beagle_info &info);
	
	void __stdcall available_gps_info(beagle_api::beagle_id_type beagle_id, const beagle_api::gps_info &info);
	
	void __stdcall available_gsm_sector_info(beagle_api::beagle_id_type beagle_id, const beagle_api::gsm_sector_info *info, long num_records);

	void __stdcall available_gsm_sweep_info(beagle_api::beagle_id_type beagle_id, const beagle_api::gsm_sweep_info *info, long num_records);

	void __stdcall available_umts_sector_info(beagle_api::beagle_id_type beagle_id, const beagle_api::umts_sector_info *info, long num_records);

	void __stdcall available_umts_sweep_info(beagle_api::beagle_id_type beagle_id, const beagle_api::umts_sweep_info *info, long num_records);
	
	void __stdcall available_lte_sector_info(beagle_api::beagle_id_type beagle_id, const beagle_api::lte_sector_info *info, long num_records);

	void __stdcall available_lte_sweep_info(beagle_api::beagle_id_type beagle_id, const beagle_api::lte_sweep_info *info, long num_records);
	
	void __stdcall available_error(beagle_api::beagle_id_type beagle_id, long error, const char *str, long buf_size);

	void __stdcall available_message(beagle_api::beagle_id_type beagle_id, long possible_message_number, const char *str, long buf_size);

private:
	thead_safe_storage<beagle_info_wrapper> beagle_info_list_;
	thead_safe_storage<gps_info_wrapper> gps_info_list_;
	thead_safe_storage<gsm_sector_info_wrapper> gsm_sector_list_;
	thead_safe_storage<gsm_sweep_info_wrapper> gsm_sweep_list_;
	thead_safe_storage<umts_sector_info_wrapper> umts_sector_list_;
	thead_safe_storage<umts_sweep_info_wrapper> umts_sweep_list_;
	thead_safe_storage<lte_sector_info_wrapper> lte_sector_list_;
	thead_safe_storage<lte_sweep_info_wrapper> lte_sweep_list_;
	thead_safe_storage<api_string> error_list_;
	thead_safe_storage<api_string> message_list_;

	boost::mutex wait_mutex_;
	boost::condition_variable condition_;
};


}