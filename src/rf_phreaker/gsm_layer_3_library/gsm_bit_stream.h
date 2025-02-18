#pragma once

#include <stdint.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>

class gsm_bit_stream;
class gsm_bit_stream_mem;
inline std::ostream& operator<<(std::ostream &os, const gsm_bit_stream &t);
inline std::istream& operator>>(std::ostream &os, gsm_bit_stream_mem &t);

class gsm_bit_stream
{
public:
	gsm_bit_stream(const uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused, uint32_t bits_consumed_thus_far = 0)
		: bit_stream_(bit_stream)
		, num_bytes_(num_bytes)
		, bits_unused_(bits_unused)
		, bits_consumed_thus_far_(bits_consumed_thus_far)
	{}

	gsm_bit_stream() 
		: bit_stream_(0)
		, num_bytes_(0)
		, bits_unused_(0)
		, bits_consumed_thus_far_(0) {}

	const uint8_t* current_position_in_bit_stream() const { return &bit_stream_[bytes_consumed_thus_far()]; }

	uint32_t bytes_consumed_thus_far() const { return (uint32_t)std::floor(bits_consumed_thus_far_ / 8.0); }

	uint32_t bits_consumed_thus_far() const { return bits_consumed_thus_far_; }

	uint32_t num_bytes_in_bit_stream() const { return num_bytes_; }

	uint32_t num_bits_in_bit_stream() const { return num_bytes_ * 8; }

	uint32_t num_bits_unused_in_bit_stream() const { return bits_unused_; }

	void consume_more_bits(uint32_t additional_bits_consumed) { bits_consumed_thus_far_ += additional_bits_consumed; }

	void verify_bit_stream(uint32_t bits_to_consume) const 
	{ 
				
		int32_t bits_left = num_bits_in_bit_stream() - bits_unused_ - (bits_consumed_thus_far_ + bits_to_consume);
		if(bits_left < 0)
			throw std::runtime_error(std::string("Error decoding GSM bit stream.  ").append(boost::lexical_cast<std::string>(bits_left * -1)).append(" additional bit(s) are needed to continue current decode."));
	}

	const uint8_t *bit_stream() const { return bit_stream_; }

	void set_bit_stream(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits = 0) {
		bit_stream_ = bit_stream;
		num_bytes_ = num_of_bytes;
		bits_unused_ = unused_bits;
	}

protected:
	const uint8_t *bit_stream_;

	uint32_t num_bytes_;

	uint32_t bits_unused_;

	uint32_t bits_consumed_thus_far_;
};

class gsm_bit_stream_mem : public gsm_bit_stream {
public:
	gsm_bit_stream_mem(const uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused, uint32_t bits_consumed_thus_far = 0)
		: gsm_bit_stream(bit_stream, num_bytes, bits_unused, bits_consumed_thus_far) {}

	gsm_bit_stream_mem() {}

	friend std::istream& operator>>(std::istream &os, gsm_bit_stream_mem &t);

protected:
	std::vector<uint8_t> mem_;
};

inline std::ostream& operator<<(std::ostream &os, const gsm_bit_stream &t) {
	os << std::hex << t.num_bytes_in_bit_stream() << "\t" << t.num_bits_unused_in_bit_stream() << "\t";

	for(uint32_t i = 0, end = t.num_bytes_in_bit_stream(); i < end; ++i)
		os << std::setw(2) << std::setfill('0') << (int)t.bit_stream()[i] << " ";

	return os;
}

inline std::istream& operator>>(std::istream &is, gsm_bit_stream_mem &t) {
	uint32_t num_bytes = 0, num_bites_unused = 0;
	is >> std::hex >> num_bytes;
	is >> num_bites_unused;
	if(num_bytes) {
		t.mem_.resize(num_bytes);
		t.set_bit_stream(&t.mem_[0], num_bytes, num_bites_unused);

		for(uint32_t i = 0, end = t.num_bytes_in_bit_stream(); i < end; ++i) {
			int j = 0;
			is >> j;
			t.mem_[i] = j;
		}
	}
	return is;
}
