#include "rf_phreaker/cappeen_console_app/simple_logger.h"

using namespace cappeen_scanner;

boost::scoped_ptr<simple_logger> simple_logger::logger_;
boost::mutex simple_logger::m1_;
