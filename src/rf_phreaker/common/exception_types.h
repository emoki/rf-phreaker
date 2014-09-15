#pragma once

#include <stdexcept>
#include <stdint.h>

namespace rf_phreaker {

enum error_type {
	generic_error_type,
	comm_error_type,
	scanner_init_error_type,
	hardware_error_type,
	misc_error_type,
	file_error_type,
	blade_rf_error_type,
	ipp_error_type,
	filter_error_type,
	gsm_analysis_error_type,
	umts_analysis_error_type,
	lte_analysis_error_type,
	processing_error_type,
	matlab_interface_error_type,
	cappeen_api_error_type,
	gps_comm_error_type,
	rf_phreaker_api_error_type
};

class rf_phreaker_error : public std::runtime_error
{
public:
	rf_phreaker_error(const std::string &err, int error_code = -1, error_type etype = generic_error_type)
		: std::runtime_error(err)
		, error_code_(error_code)
		, error_type_(etype)
	{}

	int error_code_;
	error_type error_type_;
};

template<error_type T>
class specific_error : public rf_phreaker_error
{
public:
	specific_error(const std::string &err, int error_code = -1)
		: rf_phreaker_error(err, error_code, T)
	{}
};

typedef specific_error<comm_error_type> comm_error;
typedef specific_error<scanner_init_error_type> scanner_init_error;
typedef specific_error<hardware_error_type> hardware_error;
typedef specific_error<misc_error_type> misc_error;
typedef specific_error<file_error_type> file_error;
typedef specific_error<blade_rf_error_type> blade_rf_error;
typedef specific_error<ipp_error_type> ipp_error;
typedef specific_error<filter_error_type> filter_error;
typedef specific_error<gsm_analysis_error_type> gsm_analysis_error;
typedef specific_error<umts_analysis_error_type> umts_analysis_error;
typedef specific_error<lte_analysis_error_type> lte_analysis_error;
typedef specific_error<processing_error_type> processing_error;
typedef specific_error<matlab_interface_error_type> matlab_interface_error;
typedef specific_error<cappeen_api_error_type> cappeen_api_error;
typedef specific_error<gps_comm_error_type> gps_comm_error;
typedef specific_error<rf_phreaker_api_error_type> rf_phreaker_api_error;

}