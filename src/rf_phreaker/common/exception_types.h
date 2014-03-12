#pragma once

#include <stdexcept>
#include <stdint.h>

namespace rf_phreaker {

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

typedef specific_error<1> comm_error;
typedef specific_error<2> scanner_init_error;
typedef specific_error<3> hardware_error;
typedef specific_error<4> misc_error;
typedef specific_error<5> file_error;
typedef specific_error<6> blade_rf_error;
typedef specific_error<7> ipp_error;
typedef specific_error<8> filter_error;
typedef specific_error<9> gsm_analysis_error;
typedef specific_error<10> umts_analysis_error;
typedef specific_error<11> lte_analysis_error;
typedef specific_error<12> processing_error;
typedef specific_error<13> matlab_interface_error;
typedef specific_error<14> cappeen_api_error;

}