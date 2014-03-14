#ifndef __LOG_H__
#define __LOG_H__


//#include "rf_phreaker/../../third_party/g2log/g2log/src/g2log.h"
//#include "rf_phreaker/../../third_party/g2log/g2log/src/g2logworker.h"
#include <boost/signals2.hpp>

namespace rf_phreaker {

typedef boost::signals2::signal<void(const std::string &, int)> sink_type;

class logger
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

	static logger& rf_phreaker_log();
};


}

#endif // __LOG_H__
