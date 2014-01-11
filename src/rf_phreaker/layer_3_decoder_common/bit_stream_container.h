#pragma once

#include "rf_phreaker/layer_3_decoder_common/asn1_types.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <boost/scoped_array.hpp>

class bit_stream_container;
inline std::ostream& operator<<(std::ostream &os, const bit_stream_container &t);

class bit_stream_container_mem;
inline std::istream& operator>>(std::istream &is, bit_stream_container_mem &t);

class bit_stream_container
{
public:
	bit_stream_container(const bit_stream_type *stream);
	
	bit_stream_container(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits = 0);

	bit_stream_container() {}

	~bit_stream_container();

	void set_bit_stream(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits = 0);

	const bit_container_type *bit_stream() const { return bit_stream_; }
	uint32_t num_of_bytes() const { return num_of_bytes_; }
	uint32_t unused_bits() const { return unused_bits_; }
	uint32_t total_number_bits() const { return num_of_bytes_ * bit_container_type_size - unused_bits_; }

protected:
	const bit_container_type* bit_stream_;
	uint32_t num_of_bytes_;
	uint32_t unused_bits_;
};

class bit_stream_container_mem : public bit_stream_container
{
public:
	bit_stream_container_mem(const bit_stream_type *stream)
	: bit_stream_container(stream)
	{}

	bit_stream_container_mem(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits = 0)
		: bit_stream_container(bit_stream, num_of_bytes, unused_bits)
	{}

	bit_stream_container_mem() 
	{}

	friend inline std::istream& operator>>(std::istream &is, bit_stream_container_mem &t);

protected:
	boost::scoped_array<bit_container_type> mem_;
};


inline std::ostream& operator<<(std::ostream &os, const bit_stream_container &t)
{
	os << t.num_of_bytes() << "\t" << t.unused_bits() << "\t";

	for(uint32_t i = 0, end = t.num_of_bytes(); i < end; ++i)
		os << std::hex << std::setw(2) << std::setfill('0') << (int)t.bit_stream()[i] << " ";

	return os;
}

inline std::istream& operator>>(std::istream &is, bit_stream_container_mem &t)
{
	uint32_t num_bytes = 0;
	uint32_t unused_bits = 0;
	is >> num_bytes;
	is >> unused_bits;

	t.mem_.reset(new bit_container_type[num_bytes]);

	std::string tmp;
	std::getline(is, tmp);
	
	char *ptr = &tmp[0];
	for(uint32_t i = 0; i < num_bytes; ++i) {
		t.mem_[i] = (bit_container_type)strtol(ptr, &ptr, 16);
	}

	t.set_bit_stream(t.mem_.get(), num_bytes, unused_bits);

	return is;
}

