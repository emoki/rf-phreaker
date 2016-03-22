#pragma once

#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "hash_utility/sha256.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/log.h"

namespace rf_phreaker {

const uint32_t sha256_byte_size = 64;
const char sha_spacer[] = "----";

class serialization_helper
{
public:
	template<typename T>
	static bool init(const std::vector<uint8_t> &bytes, T &t, bool use_sha256 = false) {
		try {
			t.clear();
			std::stringstream ss;
			std::string str(bytes.begin(), bytes.end());
			ss << str;
			boost::archive::text_iarchive ia(ss);
			ia & t;
			if(use_sha256) {
				size_t sha_start_position = str.rfind(sha_spacer);
				std::string sha_str = str.substr(sha_start_position + strlen(sha_spacer), sha256_byte_size);
				std::string original_str = str.substr(0, sha_start_position);
				SHA256 sha;
				if(sha_str != sha(original_str))
					return false;
			}
			return true;
		}
		catch(const std::exception &err) {
			LOG(LWARNING) << "Error while serializing object. " << err.what();
		}
		return false;
	}

	template<typename T>
	static std::vector<uint8_t> serialize_to_bytes(const T &t, uint32_t byte_mod = 1, bool use_sha256 = false) {
		// Be sure to include any buffer length that may be needed at the end because 
		// we have to write in pages (256 bytes at a time).
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa & t;
		std::string str(ss.str());
		auto byte_size = ss.str().size();
		// Add sha256 byte size if performing crc
		if(use_sha256) {
			byte_size += strlen(sha_spacer) + sha256_byte_size;
			SHA256 sha;
			str += sha_spacer + sha(str);
		}
		std::vector<uint8_t> bytes(add_mod(byte_size, byte_mod));
		std::copy(str.begin(), str.end(), bytes.begin());
		return bytes;
	}
};

}