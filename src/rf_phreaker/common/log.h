#ifndef __LOG_H__
#define __LOG_H__


#include "rf_phreaker/../../third_party/g3log/src/g2log.hpp"
#include "rf_phreaker/../../third_party/g3log/src/g2loglevels.hpp"
#include "rf_phreaker/../../third_party/g3log/src/g2logworker.hpp"

namespace rf_phreaker {

class logger
{
public:
	logger(const std::string& filename, const std::string& dir = "")
		: handler_(g2::LogWorker::createWithDefaultLogger(filename, dir)) {
		g2::initializeLogging(handler_.worker.get());
	}

	~logger() {
		shutdown();
	}

	void shutdown() {
		g2::internal::shutDownLoggingForActiveOnly(handler_.worker.get());
	}

	void change_logging_level(int level) {
		g2::setLogLevel(LVERBOSE, level <= LVERBOSE.value);
		g2::setLogLevel(LDEBUG, level <= LDEBUG.value);
		g2::setLogLevel(LINFO, level <= LINFO.value);
		g2::setLogLevel(LWARNING, level <= LWARNING.value);
		g2::setLogLevel(LERROR, level <= LERROR.value);
		g2::setLogLevel(LFATAL, level <= LFATAL.value);
	}

	g2::DefaultFileLogger handler_;
};

}

#endif // __LOG_H__
