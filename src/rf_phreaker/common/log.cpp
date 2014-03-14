#include "rf_phreaker/common/log.h"

using namespace rf_phreaker;



logger& logger::rf_phreaker_log()
{
	static logger log;
	return log;
}

