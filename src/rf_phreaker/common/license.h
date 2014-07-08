#pragma once

#include <vector>
#include <stdint.h>
#include "boost/serialization/access.hpp"

namespace rf_phreaker {

class license
{
public:
	license() : version_(-1) {}
	int32_t version_;
	std::vector<uint8_t> bytes_;
	license& operator =(const license &lic)
	{
		version_ = lic.version_;
		bytes_ = lic.bytes_;
		return *this;
	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & version_;
		ar & bytes_;
	}
};

}