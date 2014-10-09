#pragma once

#include "rf_phreaker/common/ipp_array.h"

namespace rf_phreaker { namespace scanner {

template<typename DataType>
class byte_aligned_buffer;

typedef byte_aligned_buffer<Ipp16sc> ipp_16sc_aligned_buffer;

template<typename DataType>
class byte_aligned_buffer
{
public:

	void align_array(size_t return_bytes) {
		size_t byte_remainder = return_bytes % sizeof(DataType);

		if(byte_remainder)
		{
			byte_aligned_offset_ = sizeof(DataType) - byte_remainder;
			return_bytes += byte_aligned_offset_;
		}
		else
			byte_aligned_offset_ = 0;

		if(ipp_buffer_.length() * sizeof(DataType) < return_bytes)
			ipp_buffer_.reset(return_bytes / sizeof(DataType));
	}
	
	char* get_aligned_array() {
		return reinterpret_cast<char*>(ipp_buffer_.get()) + byte_aligned_offset_;
	}

	const char* get_aligned_array() const {
		return reinterpret_cast<const char*>(ipp_buffer_.get()) + byte_aligned_offset_;
	}

	const ipp_array<DataType>& get_unaligned_array() const {
		return ipp_buffer_;
	}

private:	
	ipp_array<DataType> ipp_buffer_;

	size_t byte_aligned_offset_;
};

}}