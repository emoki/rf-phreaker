#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker {


std::string static_timestamp::timestamp_;

std::string static_timestamp::to_string() {
	if(timestamp_.empty())
		timestamp_ = timestamp_string();
	return timestamp_;
}
void static_timestamp::clear() {
	timestamp_.clear();
}


}