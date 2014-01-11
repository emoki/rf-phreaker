#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"


bit_stream_container::bit_stream_container(const bit_stream_type *stream)
	: bit_stream_(stream->buf)
	, num_of_bytes_(stream->size)
	, unused_bits_(stream->bits_unused)
{
}

bit_stream_container::bit_stream_container(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits)
	: bit_stream_(bit_stream)
	, num_of_bytes_(num_of_bytes)
	, unused_bits_(unused_bits)
{
}

bit_stream_container::~bit_stream_container()
{
}

void bit_stream_container::set_bit_stream(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits)
{
	bit_stream_ = bit_stream;
	num_of_bytes_ = num_of_bytes;
	unused_bits_ = unused_bits;
}

