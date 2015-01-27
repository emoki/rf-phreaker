#pragma once

#include <stdint.h>
#include "rf_phreaker/common/serialization_helper.h"
#include "rf_phreaker/scanner/eeprom_defines.h"

namespace rf_phreaker { namespace scanner {

class freq_correction_container
{
public:
	freq_correction_container() 
		: nuand_freq_correction_value_(0)
		, nuand_freq_correction_date_(0) 
	{}

	bool operator==(const freq_correction_container &a) {
		return nuand_freq_correction_value_ == a.nuand_freq_correction_value_ &&
			nuand_freq_correction_date_ == a.nuand_freq_correction_date_;
	}

	uint32_t nuand_freq_correction_value_;

	time_t nuand_freq_correction_date_;

	void clear() {
		nuand_freq_correction_value_ = 0;
		nuand_freq_correction_date_ = 0;
	}

	bool init(const std::vector<uint8_t> &bytes) {
		auto success = serialization_helper::init(bytes, *this, true);
		LOG_IF(LWARNING, !success) << "Frequency correction data failed verification.  It appears corrupt.";
		return success;
	}

	std::vector<uint8_t> serialize_to_bytes() const {
		return serialization_helper::serialize_to_bytes(*this, RF_PHREAKER_FLASH_PAGE_SIZE, true);
	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & nuand_freq_correction_value_;
		ar & nuand_freq_correction_date_;
	}
};

}}