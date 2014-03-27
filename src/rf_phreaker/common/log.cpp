#include "rf_phreaker/common/log.h"

using namespace rf_phreaker;



delegate_sink& delegate_sink::rf_phreaker_log()
{
	static delegate_sink log;
	return log;
}

