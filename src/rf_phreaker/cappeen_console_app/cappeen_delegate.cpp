#include "cappeen_delegate.h"

#include <boost/thread/locks.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <sstream>
#include <Windows.h>

using namespace beagle_api;

namespace cappeen_scanner {


cappeen_delegate::cappeen_delegate() {}

__stdcall cappeen_delegate::~cappeen_delegate(void) {}

void cappeen_delegate::timed_wait_for_data(boost::shared_ptr<boost::thread> waiting_thread) {
	boost::unique_lock<boost::mutex> lock(wait_mutex_);

	boost::system_time timeout = boost::get_system_time() + boost::posix_time::milliseconds(200);

	condition_.timed_wait(lock, timeout);
}

void cappeen_delegate::wake_thread() {
	condition_.notify_all();
}

void __stdcall cappeen_delegate::available_beagle_info(beagle_id_type beagle_id, const beagle_info &info) {
	beagle_info_list_.push_back(info);
}

void __stdcall cappeen_delegate::available_gps_info(beagle_id_type beagle_id, const gps_info &info) {
	gps_info_list_.push_back(info);
}

void __stdcall cappeen_delegate::available_gsm_sector_info(beagle_id_type beagle_id, const gsm_sector_info *info, long num_records) {
	gsm_sector_list_.push_back_all(info, num_records);
}

void __stdcall cappeen_delegate::available_gsm_sweep_info(beagle_api::beagle_id_type beagle_id, const beagle_api::gsm_sweep_info *info, long num_records) {
	gsm_sweep_list_.push_back_all(info, num_records);
}

void __stdcall cappeen_delegate::available_umts_sector_info(beagle_id_type beagle_id, const umts_sector_info *info, long num_records) {
	umts_sector_list_.push_back_all(info, num_records);
}

void __stdcall cappeen_delegate::available_umts_sweep_info(beagle_id_type beagle_id, const umts_sweep_info *info, long num_records) {
	umts_sweep_list_.push_back_all(info, num_records);
}

void __stdcall cappeen_delegate::available_lte_sector_info(beagle_id_type beagle_id, const lte_sector_info *info, long num_records) {
	lte_sector_list_.push_back_all(info, num_records);
}

void __stdcall cappeen_delegate::available_lte_sweep_info(beagle_id_type beagle_id, const lte_sweep_info *info, long num_records) {
	lte_sweep_list_.push_back_all(info, num_records);
}

void __stdcall cappeen_delegate::available_error(beagle_id_type beagle_id, long error, const char *str, long buf_size) {
	error_list_.push_back(api_string(error, str));
}

void __stdcall cappeen_delegate::available_message(beagle_id_type beagle_id, long possible_message_number, const char *str, long buf_size) {
	message_list_.push_back(api_string(possible_message_number, str));
}

std::list<beagle_info_wrapper>cappeen_delegate::retrieve_beagle_list() {
	return beagle_info_list_.pop_all();
}

std::list<gps_info>cappeen_delegate::retrieve_gps_list() {
	return gps_info_list_.pop_all();
}

std::list<gsm_sector_info_wrapper> cappeen_delegate::retrieve_gsm_sector_list() {
	return gsm_sector_list_.pop_all();
}

std::list<gsm_sweep_info_wrapper> cappeen_delegate::retrieve_gsm_sweep_list() {
	return gsm_sweep_list_.pop_all();
}

std::list<umts_sector_info_wrapper> cappeen_delegate::retrieve_umts_sector_list() {
	return umts_sector_list_.pop_all();
}

std::list<umts_sweep_info_wrapper> cappeen_delegate::retrieve_umts_sweep_list() {
	return umts_sweep_list_.pop_all();
}

std::list<lte_sector_info_wrapper> cappeen_delegate::retrieve_lte_sector_list() {
	return lte_sector_list_.pop_all();
}

std::list<lte_sweep_info_wrapper> cappeen_delegate::retrieve_lte_sweep_list() {
	return lte_sweep_list_.pop_all();
}

std::list<api_string> cappeen_delegate::retrieve_error_list() {
	return error_list_.pop_all();
}

std::list<api_string> cappeen_delegate::retrieve_message_list() {
	return message_list_.pop_all();
}

}