#pragma once

#include "rf_phreaker/common/concurrent.h"
#include <boost/signals2.hpp>

namespace rf_phreaker
{

typedef boost::signals2::signal<void(const std::string &, int)> sink_type;

class delegate_sink
{
public:
	delegate_sink()
		: error_sink_(std::make_shared<sink_type>())
		, message_sink_(std::make_shared<sink_type>())
	{}
	delegate_sink(delegate_sink &&sink)
	{
		std::swap(error_sink_, sink.error_sink_);
		std::swap(message_sink_, sink.message_sink_);
	}
	void log_error(const std::string &str, int code)
	{
		(*error_sink_)(str, code);
	}

	void log_message(const std::string &str, int code)
	{
		(*message_sink_)(str, code);
	}

	template<typename Func>
	void connect_error(Func &func)
	{
		error_sink_->connect(func);
	}

	template<typename Func>
	void connect_message(Func &func)
	{
		message_sink_->connect(func);
	}

private:
	std::shared_ptr<sink_type> error_sink_;
	std::shared_ptr<sink_type> message_sink_;
};

class delegate_sink_async 
{
public:
	static delegate_sink_async& instance()
	{
		static delegate_sink_async sink;
		return sink;
	}

	std::future<void> log_error(const std::string &str, int code)
	{
		return sink_([=](delegate_sink sink) {
			sink.log_error(str, code);
		});
	}

	std::future<void> log_message(const std::string &str, int code)
	{
		return sink_([=](delegate_sink sink) {
			sink.log_message(str, code);
		});
	}

	template<typename Func>
	std::future<void> connect_error(Func &func)
	{
		return sink_([=](delegate_sink sink) {
			sink.connect_error(func);
		});
	}
	template<typename Func>
	std::future<void> connect_message(Func &func)
	{
		return sink_([=](delegate_sink sink) {
			sink.connect_message(func);
		});
	}

private:
	delegate_sink_async() {}

	concurrent<delegate_sink> sink_;
};
	
}