#pragma once

#include <stdexcept>
#include <stdint.h>

namespace rf_phreaker
{

enum error_type
{
	no_error_type,
	generic_error_type,
	comm_error_type,
	scanner_init_error_type,
	hardware_info_error_type,
	misc_error_type,
	file_io_error_type,
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

inline const char* error_to_str(error_type err) {
	switch(err) {
	case no_error_type:
		return "no error";
	case generic_error_type:
		return "generic error";
	case comm_error_type:
		return "comm error";
	case scanner_init_error_type:
		return "scanner initialization error";
	case hardware_info_error_type:
		return "hardware_info error";
	case misc_error_type:
		return "miscellaneous error";
	case file_io_error_type:
		return "file io error";
	case blade_rf_error_type:
		return "blade rf error";
	case ipp_error_type:
		return "ipp error";
	case filter_error_type:
		return "filter error";
	case gsm_analysis_error_type:
		return "gsm analysis error";
	case umts_analysis_error_type:
		return "umts analysis error";
	case lte_analysis_error_type:
		return "lte analysis error";
	case processing_error_type:
		return "processing error";
	case matlab_interface_error_type:
		return "matlab interface error";
	case cappeen_api_error_type:
		return "cappeen api error";
	case gps_comm_error_type:
		return "gps communciation error";
	case rf_phreaker_api_error_type:
		return "rf phreaker api error";
	default:
		return "unknown error type";
	}
}

class rf_phreaker_error : public std::runtime_error
{
public:
	rf_phreaker_error(const std::string &err, int error_code = -1, error_type etype = generic_error_type)
		: std::runtime_error(err)
		, error_code_(error_code)
		, error_type_(etype) {}

	const int error_code_;
	const error_type error_type_;
	const char* error_type_str() const { return error_to_str(error_type_); }
};

template<error_type T>
class specific_error : public rf_phreaker_error
{
public:
	specific_error(const std::string &err, int error_code = -1)
		: rf_phreaker_error(err, error_code, T) {}
};

typedef specific_error<comm_error_type> comm_error;
typedef specific_error<scanner_init_error_type> scanner_init_error;
typedef specific_error<hardware_info_error_type> hardware_info_error;
typedef specific_error<misc_error_type> misc_error;
typedef specific_error<file_io_error_type> file_io_error;
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