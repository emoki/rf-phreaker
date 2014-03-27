#ifndef __LOG_H__
#define __LOG_H__


#include "rf_phreaker/../../third_party/g2log/g2log/src/g2log.h"
#include "rf_phreaker/../../third_party/g2log/g2log/src/g2logworker.h"
#include <boost/signals2.hpp>

namespace rf_phreaker {

typedef boost::signals2::signal<void(const std::string &, int)> sink_type;

class delegate_sink
{
public:
	void log_error(const std::string &str, int code)
	{
		error_sink_(str, code);
	}
	
	void log_message(const std::string &str, int code)
	{
		message_sink_(str, code);
	}

	sink_type error_sink_;
	sink_type message_sink_;

	static delegate_sink& rf_phreaker_log();
};

class init_log
{
public:
	init_log(const std::string& filename, const std::string& dir = "")
	{
		log_worker_.reset(new g2LogWorker(filename, dir));
		g2::initializeLogging(log_worker_.get());
	}
	void release()
	{
		g2::shutDownLoggingForActiveOnly(log_worker_.get());		
	}
	std::unique_ptr<g2LogWorker> log_worker_;
};

}

#endif // __LOG_H__
