#pragma once

#include <future>
#include <string>



namespace rf_phreaker {

class delegate_sink_tmp
{
public:
	std::future<void> log_error(const std::string &str, int code);
	std::future<void> log_message(const std::string &str, int code);
	template<typename Func> std::future<void> connect_error(Func &func);
	template<typename Func> std::future<void> connect_message(Func &func);
};

}

extern rf_phreaker::delegate_sink_tmp g_delegate_sink;
