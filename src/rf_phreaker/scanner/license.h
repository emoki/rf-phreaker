#pragma once

#include <vector>
#include <stdint.h>

namespace rf_phreaker { namespace scanner {

class license
{
public:
	license() : version_(-1) {}
	int32_t version_;
	std::vector<uint8_t> bytes_;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & version_;
		ar & bytes_;
	}
};

}}