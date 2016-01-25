#pragma once

#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen_console_app/beagle_io.h"
#include "rf_phreaker/cappeen_console_app/helper_structs.h"

#include <map>
#include <list>
#include <boost/shared_ptr.hpp>

namespace cappeen_scanner {


enum beagle_output_type
{
	BEAGLE_OUTPUT,
	GPS_OUTPUT,
	GSM_SECTOR_OUTPUT,
	GSM_SWEEP_OUTPUT,
	UMTS_SECTOR_OUTPUT,
	UMTS_SWEEP_OUTPUT,
	LTE_SECTOR_OUTPUT,
	LTE_SWEEP_OUTPUT,
	API_STRING_OUTPUT
};

class cappeen_io
{
public:
	cappeen_io(void);
	
	~cappeen_io(void);

	void configure_output_filename(const std::string &base_filename);

	void log_to_stdout(bool log);

	template<typename Data>
	void output_to_file_and_stdio(const std::list<Data> &list);

	template<typename Data>
	void output(const Data &data);

private:
	template<typename Data>
	beagle_output_type find_beagle_output_type();

	template<typename Data>
	void open_file_and_output_header(std::ofstream &file, const std::string &suffix_filename);

	template<typename Data>
	//boost::shared_ptr<std::ofstream> get_file();
	std::ofstream* get_file();

	std::string output_common_header();

	std::string create_common_string();

	std::map<beagle_output_type, boost::shared_ptr<std::ofstream>> files_;

	std::map<beagle_output_type, std::string> file_suffixes_;

	std::string base_filename_;

	bool log_to_stdout_;
};

template<typename Data>	
void cappeen_io::output_to_file_and_stdio(const std::list<Data> &list)
{
	if(list.empty())
		return;

	auto file = get_file<Data>();

	std::string time_stamp = cappeen_utilities::create_time_stamp();
	
	for(auto it = list.begin(); it != list.end(); it++)
	{
		*file << time_stamp << beagle_delimiter << *it << std::endl;
		if(log_to_stdout_)
			simple_logger::instance().log(*it);
	}
}

template<typename Data>
std::ofstream* cappeen_io::get_file()
{
	auto type = find_beagle_output_type<Data>();

	if(files_.find(type) == files_.end())
	{
		files_[type] = boost::shared_ptr<std::ofstream>(new std::ofstream);
		open_file_and_output_header<Data>(*files_[type], file_suffixes_[find_beagle_output_type<Data>()]);
	}

	return files_[type].get();
}

template<typename Data>	
void cappeen_io::output(const Data &info)
{
	auto file = get_file<Data>();
	
	*file << cappeen_utilities::create_time_stamp() << beagle_delimiter << *it << std::endl;
}

template<typename Data>
void cappeen_io::open_file_and_output_header(std::ofstream &file, const std::string &suffix_filename)
{
	std::string full_filename(base_filename_);

	full_filename.append(suffix_filename);

	file.open(full_filename);

	if(!file.is_open())
		throw std::runtime_error(std::string("Unable to open file ").append(full_filename)); 

	file << output_common_header();

	output_beagle_api_header<Data>(file);
}

}
