#ifndef __LOG_H__
#define __LOG_H__


#include "rf_phreaker/../../third_party/g2log/g2log/src/g2log.h"
#include "rf_phreaker/../../third_party/g2log/g2log/src/g2logworker.h"

namespace rf_phreaker {

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
