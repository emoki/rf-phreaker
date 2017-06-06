#pragma once

#include "rf_phreaker/common/concurrent.h"
#include "rf_phreaker/common/singleton.h"
#include <boost/signals2.hpp>

namespace rf_phreaker {

typedef boost::signals2::signal<void(const std::string &, int, int)> sink_type;

class delegate_sink_async;
typedef singleton<delegate_sink_async> delegate_sink;

class delegate_sink_impl
{
public:
	delegate_sink_impl()
		: error_sink_(std::make_shared<sink_type>())
		, message_sink_(std::make_shared<sink_type>()) {}
	delegate_sink_impl(delegate_sink_impl &&sink) {
		std::swap(error_sink_, sink.error_sink_);
		std::swap(message_sink_, sink.message_sink_);
	}
	void log_error(const rf_phreaker_error &err) {
		(*error_sink_)(err.what(), err.error_type_, err.error_code_);
	}

	void log_error(const std::string &str, int type, int code) {
		(*error_sink_)(str, type, code);
	}

	void log_message(const rf_phreaker_error &err) {
		(*message_sink_)(err.what(), err.error_type_, err.error_code_);
	}

	void log_message(const std::string &str, int type, int code) {
		(*message_sink_)(str, type, code);
	}

	template<typename Func>
	void connect_error(Func &func) {
		error_sink_->connect(func);
	}

	template<typename Func>
	void connect_message(Func &func) {
		message_sink_->connect(func);
	}

private:
	std::shared_ptr<sink_type> error_sink_;

	std::shared_ptr<sink_type> message_sink_;
};

class delegate_sink_async
{
public:
	//static delegate_sink_async& instance()
	//{
	//	static delegate_sink_async sink;
	//	return sink;
	//}

	std::future<void> log_error(const rf_phreaker_error &err) {
		return sink_.lambda([=](delegate_sink_impl &sink) {
			sink.log_error(err);
		});
	}

	std::future<void> log_error(const std::string &str, int type, int code) {
		return sink_.lambda([=](delegate_sink_impl &sink) {
			sink.log_error(str, type, code);
		});
	}

	std::future<void> log_message(const rf_phreaker_error &err) {
		return sink_.lambda([=](delegate_sink_impl &sink) {
			sink.log_error(err);
		});
	}
	std::future<void> log_message(const std::string &str, int type, int code) {
		return sink_.lambda([=](delegate_sink_impl &sink) {
			sink.log_message(str, type, code);
		});
	}

	template<typename Func>
	std::future<void> connect_error(Func &func) {
		return sink_.lambda([=](delegate_sink_impl &sink) {
			sink.connect_error(func);
		});
	}
	template<typename Func>
	std::future<void> connect_message(Func &func) {
		return sink_.lambda([=](delegate_sink_impl &sink) {
			sink.connect_message(func);
		});
	}

private:
	//	delegate_sink_async() {}

	concurrent<delegate_sink_impl> sink_;
};

}