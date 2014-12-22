#ifndef __LOG_H__
#define __LOG_H__


#include "rf_phreaker/../../third_party/g3log/src/g2log.hpp"
#include "rf_phreaker/../../third_party/g3log/src/g2loglevels.hpp"
#include "rf_phreaker/../../third_party/g3log/src/g2logworker.hpp"

namespace rf_phreaker {
	
class logger
{
private:
public:

	logger() {}

	logger(const std::string& filename, const std::string& dir = "")
		: handler_(new g2::DefaultFileLogger{g2::LogWorker::createWithDefaultLogger(filename, dir)}) {
		g2::initializeLogging(handler_->worker.get());
	}

	~logger() {
		g2::internal::shutDownLogging();
	}

	void init(const std::string& filename, const std::string& dir = "") {
		handler_.reset(new g2::DefaultFileLogger{g2::LogWorker::createWithDefaultLogger(filename, dir)});
		g2::initializeLogging(handler_->worker.get());
	}

	void change_logging_level(int level) {
		// Verbose corresponds to 0 in the ini file therefore
		// we need to adjust it before comparing levels.
		int adjusted_level = level + LVERBOSE.value;
		g2::setLogLevel(LVERBOSE, adjusted_level <= LVERBOSE.value);
		g2::setLogLevel(LDEBUG, adjusted_level <= LDEBUG.value);
		g2::setLogLevel(LINFO, adjusted_level <= LINFO.value);
		g2::setLogLevel(LWARNING, adjusted_level <= LWARNING.value);
		g2::setLogLevel(LERROR, adjusted_level <= LERROR.value);
		g2::setLogLevel(LFATAL, adjusted_level <= LFATAL.value);
	}
	
	void enable_gps_general_log(bool enable) {
		g2::setLogLevel(LGPS, enable);
	}

	void enable_gps_parsing_log(bool enable) {
		g2::setLogLevel(LGPSPARSE, enable);
	}

	void enable_collection_log(bool enable) {
		g2::setLogLevel(LCOLLECTION, enable);
	}

	std::unique_ptr<g2::DefaultFileLogger> handler_;
};


}

#endif // __LOG_H__
