#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker { namespace api {

	inline void copy_serial(const std::string &str, rp_serial &serial) {
		::rf_phreaker::copy_serial(str, serial.serial_, RP_SERIAL_LENGTH);
	}
}}