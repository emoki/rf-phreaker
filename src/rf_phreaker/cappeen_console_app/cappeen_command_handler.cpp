#include "rf_phreaker/cappeen_console_app/cappeen_command_handler.h"
#include "rf_phreaker/cappeen_console_app/cappeen_utilities.h"
#include "rf_phreaker/cappeen_console_app/simple_logger.h"

#include <boost/lexical_cast.hpp>

namespace cappeen_scanner {


cappeen_command_handler::cappeen_command_handler(boost::shared_ptr<cappeen_interface> beagle)
	: beagle_(beagle)
	, scanner_connection_open_(false)
	, scanner_collecting_(false)
{}

cappeen_command_handler::~cappeen_command_handler(void)
{
}

void cappeen_command_handler::start_collection(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &bands)
{
	simple_logger::instance().log("Starting collection.");

	beagle_api::collection_info info;

	// Filename is only used during beagle api debug.
	info.collection_filename_ = "debug_beagle_api_collection";

	if(bands.empty())
		throw std::runtime_error("No technologies_and_bands to sweep.");

	info.tech_and_bands_to_sweep_.elements_ = &bands[0];
	info.tech_and_bands_to_sweep_.num_elements_ = bands.size();

	long error = beagle_->start_collection(info);

	if(error)
		throw std::runtime_error("Error starting collection.  Error code: " + boost::lexical_cast<std::string>(error));
	else
		simple_logger::instance().log("Collection started successfully.");

	scanner_collecting_ = true;
}

void cappeen_command_handler::stop_collection()
{
	simple_logger::instance().log("Stopping collection");

	long error = beagle_->stop_collection();

	if(error)
		throw std::runtime_error("Unable to stop collection.  Error code: " + boost::lexical_cast<std::string>(error));
	else
	{
		simple_logger::instance().log("Collection stopped successfully.");
		scanner_collecting_ = false;
	}
}

void cappeen_command_handler::upload_license(const std::string &license_filename, const std::string hw_serial)
{
	auto serial = hw_serial;

	if(serial.empty())
		serial = get_serial_id();

	simple_logger::instance().log("Uploading license to beagle unit " + serial + ".  Filename = " + license_filename);
	
	long error = beagle_->input_new_license(serial.c_str(), serial.size() + 1, license_filename.c_str(), license_filename.size() + 1);

	if(error)
		throw std::runtime_error("Unable to upload license. Error code:" + boost::lexical_cast<std::string>(error));
	else
		simple_logger::instance().log("License uploaded successfully.");
}

bool cappeen_command_handler::connect_to_scanner()
{
	// If connection was previously open try to close connection and reopen.  
	// If connection doesn't close properly a physical USB connector removal 
	// and reinsertion is needed.
	if(scanner_connection_open_)
	{
		simple_logger::instance().log("Connection to scanner previously open.  Closing connection before new attempt.");	
		beagle_->close_beagle_unit(scanner_id_.c_str(), scanner_id_.size() + 1);
		scanner_connection_open_ = false;
	}

	if(list_scanners() && open_scanner())
	{
		simple_logger::instance().log("Connection to beagle unit " + scanner_id_  + " established.");	
		scanner_connection_open_  = true;
		scanner_collecting_ = false;
	}

	return scanner_connection_open_;
}

bool cappeen_command_handler::list_scanners()
{
	simple_logger::instance().log("Listing beagle units.");

	memset(scanner_buf_, 0, string_buf_size_);

	long error = beagle_->list_available_beagle_units(scanner_buf_, string_buf_size_);

	if(error)
		throw std::runtime_error("Error listing beagle units.  Error code:" + boost::lexical_cast<std::string>(error));

	return error == 0;
}

bool cappeen_command_handler::open_scanner()
{
	bool connection_opened = false;

	scanner_id_.clear();

	scanner_id_ = parse_first_serial(scanner_buf_);

	if(scanner_id_.empty())
		simple_logger::instance().log("No beagle units connected.");	

	else	
	{
		simple_logger::instance().log("Opening beagle unit " + scanner_id_ + ".");

		long error = beagle_->open_beagle_unit(scanner_id_.c_str(), scanner_id_.size());

		if(error)
			throw std::runtime_error("Error opening beagle unit.   code:" + boost::lexical_cast<std::string>(error));
		else
		{
			connection_opened = true;
			simple_logger::instance().log("Opened beagle unit successfully.");
		}
	}

	return connection_opened;
}

std::string cappeen_command_handler::parse_first_serial(std::string serials)
{
	if (serials.find(';') != std::string::npos)
		return serials.substr(0, serials.find(';'));
	else
		return serials;
}

void cappeen_command_handler::close_scanner()
{
	simple_logger::instance().log("Closing connection to beagle unit.");	

	long error = beagle_->close_beagle_unit(scanner_id_.c_str(), scanner_id_.size());
	if(error)
		throw std::runtime_error("Error closing beagle unit.   code:" + boost::lexical_cast<std::string>(error));
	else
	{
		simple_logger::instance().log("Closed beagle unit successfully.");
		scanner_connection_open_ = false;
		scanner_collecting_ = false;
	}
}

std::string cappeen_command_handler::get_serial_id()
{
	if (scanner_connection_open_)
		return scanner_id_;
	else if (list_scanners())
	{
		return parse_first_serial(scanner_buf_);
	}
	else
		return std::string();
}


}