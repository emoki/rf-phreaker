#pragma once

#include <vector>
#include <stdint.h>
#include "boost/serialization/access.hpp"
#include "boost/serialization/vector.hpp"
#include "rf_phreaker/common/serialization_helper.h"
#include "rf_phreaker/common/log.h"

namespace rf_phreaker {

class license
{
public:
	license(bool is_dummy) : version_(is_dummy ? dummy_version_ : -1) {}
	license() : version_(-1) {}
	int32_t version_;
	std::vector<uint8_t> bytes_;
	
	license& operator =(const license &lic)
	{
		version_ = lic.version_;
		bytes_ = lic.bytes_;
		return *this;
	}

	bool operator==(const license &a) {
		return version_ == a.version_ && bytes_ == a.bytes_;
	}

	bool is_dummy_version() const { return version_ == dummy_version_; }

	void clear() { version_ = -1; bytes_.clear(); }

	bool init(const std::vector<uint8_t> &bytes) {
		auto success = serialization_helper::init(bytes, *this, true);
		LOG_IF(LWARNING, !success) << "License failed verification.  It appears corrupt.";
		return success;
	}
	
	std::vector<uint8_t> serialize_to_bytes(int byte_align) const {
		return serialization_helper::serialize_to_bytes(*this, byte_align, true);
	}
private:
	static const int32_t dummy_version_ = -100;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & version_;
		ar & bytes_;
	}
};

}