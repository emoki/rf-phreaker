#include "rf_phreaker/cappeen_console_app/cappeen_dispatcher.h"
#include "rf_phreaker/cappeen_console_app/cappeen_utilities.h"
#include "rf_phreaker/cappeen_console_app/helper_structs.h"
#include "rf_phreaker/cappeen_console_app/beagle_io.h"
#include "rf_phreaker/cappeen_console_app/cappeen_utilities.h"
#include "rf_phreaker/cappeen_console_app/simple_logger.h"

#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

namespace cappeen_scanner {


void cappeen_dispatcher::dispatcher_thread() {
	try {
		cappeen_utilities::set_thread_name("cappeen_dispatcher");

		while(!is_shutting_down()) {
			cappeen_delegate_->timed_wait_for_data(dispatcher_thread_);
			dispatch_data();
		}
	}
	catch(const boost::thread_interrupted &) {
	}
	catch(const std::exception& ex) {
		std::string s("Exception: ");
		s += ex.what();
		simple_logger::instance().log(s);
		fatal_error_has_occurred_ = true;
	}
	catch(...) {
		simple_logger::instance().log("Unhandled exception.");
		fatal_error_has_occurred_ = true;
	}
}



cappeen_dispatcher::cappeen_dispatcher(boost::shared_ptr<cappeen_delegate> cappeen_delegate, const std::string &base_filename, bool log_to_stdout)
	: cappeen_delegate_(cappeen_delegate) {
	shutting_down_ = (false);
	fatal_error_has_occurred_ = (false);
	is_calibrated_ = (false);
	cappeen_io_.configure_output_filename(base_filename);
	cappeen_io_.log_to_stdout(log_to_stdout);
	dispatcher_thread_.reset(new boost::thread(boost::bind(&cappeen_dispatcher::dispatcher_thread, this)));
}

cappeen_dispatcher::~cappeen_dispatcher(void) {
	shut_down();
}

void cappeen_dispatcher::shut_down() {
	shutting_down_ = true;

	dispatcher_thread_->interrupt();

	dispatcher_thread_->join();
}

bool cappeen_dispatcher::is_shutting_down() {
	return shutting_down_;
}

void cappeen_dispatcher::dispatch_data() {
	auto beagle_info_list = cappeen_delegate_->retrieve_beagle_list();
	auto gps_info_list = cappeen_delegate_->retrieve_gps_list();
	auto gsm_sector_list = cappeen_delegate_->retrieve_gsm_sector_list();
	auto gsm_sweep_list = cappeen_delegate_->retrieve_gsm_sweep_list();
	auto umts_sector_list = cappeen_delegate_->retrieve_umts_sector_list();
	auto umts_sweep_list = cappeen_delegate_->retrieve_umts_sweep_list();
	auto lte_sector_list = cappeen_delegate_->retrieve_lte_sector_list();
	auto lte_sweep_list = cappeen_delegate_->retrieve_lte_sweep_list();
	auto error_list = cappeen_delegate_->retrieve_error_list();
	auto message_list = cappeen_delegate_->retrieve_message_list();

	cappeen_io_.output_to_file_and_stdio(beagle_info_list);
	cappeen_io_.output_to_file_and_stdio(gps_info_list);
	cappeen_io_.output_to_file_and_stdio(gsm_sector_list);
	cappeen_io_.output_to_file_and_stdio(gsm_sweep_list);
	cappeen_io_.output_to_file_and_stdio(umts_sector_list);
	cappeen_io_.output_to_file_and_stdio(umts_sweep_list);
	cappeen_io_.output_to_file_and_stdio(lte_sector_list);
	cappeen_io_.output_to_file_and_stdio(lte_sweep_list);
	cappeen_io_.output_to_file_and_stdio(error_list);
	cappeen_io_.output_to_file_and_stdio(message_list);

	for(auto &i : gps_info_list) {
		gps_stats_.add(gps_stats(i));
	}

	for(auto &i : gsm_sector_list) {
		gsm_stats_.add(gsm_stats(i));
	}

	for(auto &i : umts_sector_list) {
		umts_stats_.add(umts_stats(i));
	}

	for(auto &i : lte_sector_list) {
		lte_stats_.add(lte_stats(i));
	}

	for(auto it = error_list.begin(); it != error_list.end(); ++it) {
		++error_count_;
		if(it->number_ < 0 && it->number_ > -100) {
			fatal_error_has_occurred_ = true;
		}
	}

	// Look at the most recent beagle info to see if the unit is ready for collection.
	if(beagle_info_list.size()) {
		beagle_info_ = *beagle_info_list.rbegin();
		is_calibrated_ = beagle_info_.state_ == beagle_api::BEAGLE_READY;
		is_collecting_ = beagle_info_.state_ == beagle_api::BEAGLE_COLLECTING;
	}
}

}