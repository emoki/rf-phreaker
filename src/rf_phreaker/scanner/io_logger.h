#pragma once

#include <fstream>
#include <boost/date_time.hpp>

#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace scanner {

class io_logger
{
public:
	io_logger(bool log = false) : log_(log),  write_count_(0) {}

	void log_write(const char* bytes, size_t num_bytes)
	{
		if(log_)
		{
			if(!write_file_.is_open())
				open_file(write_file_, "write_file");
			
			write_file_ << "------- WRITE " << write_count_++ << " -------" << std::endl;

			write_file_.write(bytes, num_bytes);

			write_file_ << std::endl;
		}
	}	

	void log_read(const char* bytes,  size_t num_bytes)
	{
		if(log_)
		{
			if(!read_file_.is_open())
				open_file(read_file_, "read_file");
			
				read_file_ << "------- READ " << write_count_ << " -------" << std::endl;

				read_file_.write(bytes, num_bytes);

				read_file_ << std::endl;
		}
	}

	void log_sync(bool enabled)
	{
		if(log_)
		{
			if(!read_file_.is_open())
				open_file(read_file_, "read_file");
			if(!write_file_.is_open())
				open_file(write_file_, "write_file");
			if(enabled)
			{
				read_file_ << "Synchronous mode enabled!"<< std::endl;
				write_file_ << "Synchronous mode enabled!"<< std::endl;
			}
			else
			{
				read_file_ << "Synchronous mode reset!"<< std::endl;
				write_file_ << "Synchronous mode reset!"<< std::endl;
			}

		}
	}

private:
	void open_file(std::ofstream &file, const std::string &str, bool binary = true)
	{
		if(file_description_.empty())
		{
			boost::posix_time::time_facet* facet = new boost::posix_time::time_facet("_%Y_%b_%d__%H_%M_%S_.txt");
			std::stringstream date_stream;
			date_stream.imbue(std::locale(date_stream.getloc(), facet));
			date_stream << boost::posix_time::microsec_clock::universal_time();
			date_stream >> file_description_;
		}

		file.open(str + file_description_, binary ? std::ios::binary : std::ios::out);
		if(!file)
			throw file_error("Unable to open log file for io logging.");
	}


	std::ofstream write_file_;

	std::ofstream read_file_;

	std::string file_description_;

	size_t write_count_;

	bool log_;
};

}}