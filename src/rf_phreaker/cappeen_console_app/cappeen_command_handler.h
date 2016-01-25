#pragma once

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

#include "rf_phreaker/cappeen_console_app/cappeen_interface.h"

namespace cappeen_scanner {



class cappeen_command_handler
{
public:
	cappeen_command_handler(boost::shared_ptr<cappeen_interface> beagle);

	~cappeen_command_handler(void);

	bool connect_to_scanner();

	std::string get_serial_id();

	void start_collection(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &bands);

	void stop_collection();

	void upload_license(const std::string &license_filename, const std::string hw_serial = "");

	void close_scanner();

	bool is_scanner_open() { return scanner_connection_open_; }

	bool is_scanner_collecting() { return scanner_collecting_; }

private:

	std::string parse_first_serial(std::string serials);

	bool list_scanners();

	bool open_scanner();

	boost::shared_ptr<cappeen_interface> beagle_;

	bool scanner_connection_open_;

	bool scanner_collecting_;

	static const std::size_t string_buf_size_ = 1024;

	char scanner_buf_[string_buf_size_];

	std::string scanner_id_;

	std::vector<char> base_filename_;

};

}