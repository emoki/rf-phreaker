#include "rf_phreaker/gsm_layer_3_library/generic_information_element.h"
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include <cmath>

generic_information_element::generic_information_element(format_of_information_elements format, int32_t type_bit_size, int32_t value_bit_size, int32_t length_bit_size) 
	: format_(format)
	, value_bit_size_(value_bit_size)
	, length_bit_size_(length_bit_size)
    , type_bit_size_(type_bit_size)
{
	determine_bits_to_consume(); 
	resize_raw_bit_stream();
}

generic_information_element::~generic_information_element()
{
}

void generic_information_element::determine_bits_to_consume()
{
	switch(format_)
	{
	case type_only_format:
		bits_to_consume_ = type_bit_size_;
		BOOST_ASSERT(value_bit_size_ == 0);
		BOOST_ASSERT(length_bit_size_ == 0);
		break;
	case value_only_format:
		bits_to_consume_ = value_bit_size_;
		BOOST_ASSERT(type_bit_size_ == 0);
		BOOST_ASSERT(length_bit_size_ == 0);
		break;
	case type_and_value_format:
		bits_to_consume_ = type_bit_size_ + value_bit_size_;
		BOOST_ASSERT(length_bit_size_ == 0);
		break;
	case length_and_value_format:
		bits_to_consume_ = length_bit_size_ + value_bit_size_;
		BOOST_ASSERT(type_bit_size_ == 0);
		break;
	case type_length_and_value_format:
		bits_to_consume_ = type_bit_size_ + length_bit_size_ + value_bit_size_;
		break;
	case length_and_value_eps_format:
	case type_length_and_value_eps_format:
		throw std::runtime_error("EPS Mobility Management and EPS Session Management format of information elements not supported.");
		break;
	default:
		throw std::runtime_error("Format of information elements unknown.");
	}
}

void generic_information_element::resize_raw_bit_stream()
{
	raw_bit_stream_.resize((uint32_t)std::ceil(bits_to_consume_ / 8.0));
}

void generic_information_element::decode(gsm_bit_stream &bs)
{
	bs.verify_bit_stream(bits_to_consume_);
	
	parse_bit_stream(bs);

	info_element_specific_decode();
}

void generic_information_element::parse_bit_stream(gsm_bit_stream &bs)
{
	bs.verify_bit_stream(bits_to_consume_);
		
	calculate_skip_bits(bs);

	copy_to_raw_bit_stream(bs);

	bs.consume_more_bits(bits_to_consume_);
}

void generic_information_element::copy_to_raw_bit_stream(const gsm_bit_stream &bs)
{
	uint32_t pos = 0;
	for(int32_t i = 0; i < bits_to_consume_; i += 8)
    {
        // ecs - I believe this is the behavior Rajesh wanted.
        //raw_bit_stream_[pos] = bs.current_position_in_bit_stream()[pos];
        raw_bit_stream_[pos] = bs.current_position_in_bit_stream()[pos];
        pos++;
    }
}

void generic_information_element::calculate_skip_bits(const gsm_bit_stream &bs)
{
	skip_bits_ = bs.bits_consumed_thus_far() - bs.bytes_consumed_thus_far();
}


