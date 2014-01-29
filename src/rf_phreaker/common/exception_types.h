#pragma once

#include <stdexcept>
#include <stdint.h>

namespace rf_phreaker {

enum error_codes
{
	comm,
	scanner_init,
	hardware,
	misc,
	file,
	blade_rf,
	ipp,
	filter,
	gsm_analysis,
	umts_analysis,
	lte_analysis
};

class rf_phreaker_error : public std::runtime_error
{
public:
	rf_phreaker_error(const std::string &err, int64_t error_code = 0)
		: std::runtime_error(err)
		, error_code_(error_code)
	{}

	int64_t error_code_;
};

template<int T>
class specific_error : public rf_phreaker_error
{
public:
	specific_error(const std::string &err, int64_t error_code = 0)
		: rf_phreaker_error(err, error_code)
	{}
};

typedef specific_error<comm> comm_error;
typedef specific_error<scanner_init> scanner_init_error;
typedef specific_error<hardware> hardware_error;
typedef specific_error<misc> misc_error;
typedef specific_error<file> file_error;
typedef specific_error<blade_rf> blade_rf_error;
typedef specific_error<ipp> ipp_error;
typedef specific_error<filter> filter_error;
typedef specific_error<gsm_analysis> gsm_analysis_error;
typedef specific_error<umts_analysis> umts_analysis_error;
typedef specific_error<lte_analysis> lte_analysis_error;

}