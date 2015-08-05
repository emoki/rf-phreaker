#pragma once

#include <future>
#include <string>
#include "rf_phreaker/common/exception_types.h"


namespace rf_phreaker {

class delegate_sink_tmp
{
public:
	std::future<void> log_error(const rf_phreaker_error &err);
	std::future<void> log_error(const std::string &str, int type, int code);
	std::future<void> log_message(const rf_phreaker_error &err);
	std::future<void> log_message(const std::string &str, int type, int code);
	template<typename Func> std::future<void> connect_error(Func &func);
	template<typename Func> std::future<void> connect_message(Func &func);
};

}

extern rf_phreaker::delegate_sink_tmp g_delegate_sink;
