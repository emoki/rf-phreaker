#pragma once

#include <stdint.h>
#include <cmath>
#include <boost/lexical_cast.hpp>

class gsm_bit_stream
{
public:
	gsm_bit_stream(const uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused, uint32_t bits_consumed_thus_far = 0)
		: bit_stream_(bit_stream)
		, num_bytes_(num_bytes)
		, bits_unused_(bits_unused)
		, bits_consumed_thus_far_(bits_consumed_thus_far)
	{}

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

protected:

	const uint8_t *bit_stream_;

	const uint32_t num_bytes_;

	const uint32_t bits_unused_;

	uint32_t bits_consumed_thus_far_;
};
