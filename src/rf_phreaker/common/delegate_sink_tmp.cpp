#include "rf_phreaker/common/delegate_sink_tmp.h"
#include "rf_phreaker/common/delegate_sink.h"

rf_phreaker::delegate_sink_tmp g_delegate_sink;

namespace rf_phreaker {

std::future<void> delegate_sink_tmp::log_error(const std::string &str, int code)
{
	return delegate_sink::instance().log_error(str, code);
}

std::future<void> delegate_sink_tmp::log_message(const std::string &str, int code)
{
	return delegate_sink::instance().log_message(str, code);
}

template<typename Func> 
std::future<void> delegate_sink_tmp::connect_error(Func &func)
{
	return delegate_sink:instance().connect_error(func);
}

template<typename Func> 
std::future<void> delegate_sink_tmp::connect_message(Func &func)
{
	return delegate_sink::instance().connect_message(func);
}

}