#pragma once

#include <stdint.h>
#include <vector>
#include <boost/assert.hpp>
#include <cmath>
#include "rf_phreaker/layer_3_decoder_common/asn1_types.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include "rf_phreaker/layer_3_decoder_common/asn1_config.h"
#include <fstream>
#include <iomanip>

#include "rf_phreaker/umts_rrc_asn_library/SegCount.h"
#include "rf_phreaker/umts_rrc_asn_library/SegmentIndex.h"
#include "rf_phreaker/umts_rrc_asn_library/Digit.h"

typedef SegCount_t segment_count_type;
typedef SegmentIndex_t segment_index_type;
typedef Digit_t digit_type;


#define segments_1_flag_mask 0x1
#define segments_2_flag_mask 0x3
#define segments_3_flag_mask 0x7
#define segments_4_flag_mask 0xF
#define segments_5_flag_mask 0x1F
#define segments_6_flag_mask 0x3F
#define segments_7_flag_mask 0x7F
#define segments_8_flag_mask 0xFF
#define segments_9_flag_mask 0x1FF
#define segments_10_flag_mask 0x3FF
#define segments_11_flag_mask 0x7FF
#define segments_12_flag_mask 0xFFF
#define segments_13_flag_mask 0x1FFF
#define segments_14_flag_mask 0x3FFF
#define segments_15_flag_mask 0x7FFF
#define segments_16_flag_mask 0xFFFF

#define segments_17_flag_mask 0x1FFFF
#define segments_18_flag_mask 0x3FFFF
#define segments_19_flag_mask 0x7FFFF
#define segments_20_flag_mask 0xFFFFF
#define segments_21_flag_mask 0x1FFFFF
#define segments_22_flag_mask 0x3FFFFF
#define segments_23_flag_mask 0x7FFFFF
#define segments_24_flag_mask 0xFFFFFF
#define segments_25_flag_mask 0x1FFFFFF
#define segments_26_flag_mask 0x3FFFFFF
#define segments_27_flag_mask 0x7FFFFFF
#define segments_28_flag_mask 0xFFFFFFF
#define segments_29_flag_mask 0x1FFFFFFF
#define segments_30_flag_mask 0x3FFFFFFF
#define segments_31_flag_mask 0x7FFFFFFF
#define segments_32_flag_mask 0xFFFFFFFF

class segment_type 
{
public:
	segment_type() : number_bytes_including_padding_(0), unused_bits_(0) {}


	void copy_bits(const bit_stream_container &bit_stream)
	{
		const uint8_t *bits = bit_stream.bit_stream();

		number_bytes_including_padding_ =  bit_stream.num_of_bytes();
		unused_bits_ = bit_stream.unused_bits();


		if(buffer_.size() < number_bytes_including_padding_)
			buffer_.resize(number_bytes_including_padding_);
		
		memcpy(&buffer_[0], bits, number_bytes_including_padding_);
	}

	const bit_container_type* get_bits() const
	{
		if(buffer_.empty())
			return 0;
		else
			return &buffer_[0];
	}

	uint32_t total_number_bits() const { return (number_bytes_including_padding_ * bit_container_type_size) - unused_bits_; }

	uint32_t number_bytes_including_padding() const { return number_bytes_including_padding_; }

	uint32_t unused_bits() const { return unused_bits_; }

	void clear()
	{
		for(std::size_t i = 0; i < buffer_.size(); i++)
			buffer_[i] = 0;
		number_bytes_including_padding_ = 0;
		unused_bits_ = 0;
	}

private:
	std::vector<bit_container_type> buffer_;

	uint32_t number_bytes_including_padding_;

	uint32_t unused_bits_;
};

class segmented_sib
{
public:
	segmented_sib() 
		: segments_set_flag_(0)
		, segment_expected_(0)
	{ 
		// We set the number of segments to the max.  This allows us to use any segments that come
		// in before we have decoded the actual number of segments.
		set_number_segments(32);
	}

	void set_first_segment(const bit_stream_container &bit_stream, segment_count_type segment_count)
	{
		set_number_segments(segment_count);
		segments_[0].copy_bits(bit_stream);
		segments_set_flag_ |= 1;
	}

	void set_subsequent_segment(const bit_stream_container &bit_stream, segment_index_type segment_index_offset_zero) 
	{ 
		// If the segment index is too large it means the segment count has changed.  In this case we clear all data taken so far and start over
		// looking for a first segment.
		if(segment_index_offset_zero >= total_number_of_segments_)
		{
			clear();
			return;
		}
		segments_[segment_index_offset_zero].copy_bits(bit_stream);

		segments_set_flag_ |= (1 << segment_index_offset_zero);

		segment_expected_ = segment_index_offset_zero + 1;
	}

	// TODO - is this needed?  If the last segment is not always one we can set_subsequent_segment above.  
	// For now we assume it does give the correct segment offset.
	void set_last_segment(const bit_stream_container &bit_stream, segment_index_type segment_index_offset_zero) 
	{
		set_subsequent_segment(bit_stream, segment_index_offset_zero);
	}
	
	bool is_sib_complete() const
	{
		return (segments_set_flag_ & set_flag_mask_) == set_flag_mask_;
	}

	bit_stream_container get_completed_sib()
	{
		calculate_completed_sib_total_number_bits();

		resize_completed_segment();

		copy_first_segment();

		copy_subsequent_segments();

		remove_unneeded_bytes_within_completed_sib();
		
		append_complete_segment_in_hex_format_to_file();

		append_complete_segment_in_binary_format_to_file();

		return bit_stream_container(&completed_sib_.at(0), completed_sib_.size(), (completed_sib_.size() * bit_container_type_size) - completed_sib_total_num_bits_);
	}

	segmented_sib& operator = (const segmented_sib &a)
	{
		total_number_of_segments_ = a.total_number_of_segments_;
		segments_ = a.segments_;
		segments_set_flag_ = a.segments_set_flag_;
		set_flag_mask_ = a.set_flag_mask_;
		segment_expected_ = a.segment_expected_;
		return *this;
	}

	void clear()
	{
		segments_set_flag_ = 0;
		for(std::size_t i = 0; i < segments_.size(); i++)
			segments_[i].clear();
		for(std::size_t i = 0; i < completed_sib_.size(); i++)
			completed_sib_[i] = 0;
	}

	segment_count_type get_number_segments(){ return total_number_of_segments_; }

	segment_index_type get_segment_expected(){ return segment_expected_; }

	void set_number_segments(segment_count_type num) 
	{ 
		if(total_number_of_segments_ != num)
		{
			switch(num)
			{
			case 1:
				set_flag_mask_ = segments_1_flag_mask;
				break;
			case 2:
				set_flag_mask_ = segments_2_flag_mask;
				break;
			case 3:
				set_flag_mask_ = segments_3_flag_mask;
				break;
			case 4:
				set_flag_mask_ = segments_4_flag_mask;
				break;
			case 5:
				set_flag_mask_ = segments_5_flag_mask;
				break;
			case 6:
				set_flag_mask_ = segments_6_flag_mask;
				break;
			case 7:
				set_flag_mask_ = segments_7_flag_mask;
				break;
			case 8:
				set_flag_mask_ = segments_8_flag_mask;
				break;
			case 9:
				set_flag_mask_ = segments_9_flag_mask;
				break;
			case 10:
				set_flag_mask_ = segments_10_flag_mask;
				break;
			case 11:
				set_flag_mask_ = segments_11_flag_mask;
				break;
			case 12:
				set_flag_mask_ = segments_12_flag_mask;
				break;
			case 13:
				set_flag_mask_ = segments_13_flag_mask;
				break;
			case 14:
				set_flag_mask_ = segments_14_flag_mask;
				break;
			case 15:
				set_flag_mask_ = segments_15_flag_mask;
				break;
			case 16:
				set_flag_mask_ = segments_16_flag_mask;
				break;

			case 17:
				set_flag_mask_ = segments_17_flag_mask;
				break;
			case 18:
				set_flag_mask_ = segments_18_flag_mask;
				break;
			case 19:
				set_flag_mask_ = segments_19_flag_mask;
				break;
			case 20:
				set_flag_mask_ = segments_20_flag_mask;
				break;
			case 21:
				set_flag_mask_ = segments_21_flag_mask;
				break;
			case 22:
				set_flag_mask_ = segments_22_flag_mask;
				break;
			case 23:
				set_flag_mask_ = segments_23_flag_mask;
				break;
			case 24:
				set_flag_mask_ = segments_24_flag_mask;
				break;
			case 25:
				set_flag_mask_ = segments_25_flag_mask;
				break;
			case 26:
				set_flag_mask_ = segments_26_flag_mask;
				break;
			case 27:
				set_flag_mask_ = segments_27_flag_mask;
				break;
			case 28:
				set_flag_mask_ = segments_28_flag_mask;
				break;
			case 29:
				set_flag_mask_ = segments_29_flag_mask;
				break;
			case 30:
				set_flag_mask_ = segments_30_flag_mask;
				break;
			case 31:
				set_flag_mask_ = segments_31_flag_mask;
				break;
			case 32:
				set_flag_mask_ = segments_32_flag_mask;
				break;
			default:
				throw std::runtime_error("Number of segments is too large.  Adjust code.");
			}
			total_number_of_segments_ = num; 

			segments_.resize(total_number_of_segments_); 

		}

	}

private:

	void calculate_completed_sib_total_number_bits()
	{
		completed_sib_total_num_bits_ = 0;

		for(auto it = segments_.begin(); it != segments_.end(); it++)
			completed_sib_total_num_bits_ += it->total_number_bits();

	}

	void resize_completed_segment()
	{
		uint32_t num_bytes = 0;
		for(auto it = segments_.begin(); it != segments_.end(); it++)
			num_bytes += it->number_bytes_including_padding();
		
		completed_sib_.resize(num_bytes);	
		memset(&completed_sib_[0], 0, num_bytes);
	}

	void remove_unneeded_bytes_within_completed_sib()
	{
		uint32_t num_bytes = completed_sib_total_num_bits_ / bit_container_type_size;
		if(completed_sib_total_num_bits_ % bit_container_type_size)		
			num_bytes += 1;

		completed_sib_.resize(num_bytes);	
	}

	void copy_first_segment()
	{
		memcpy(&completed_sib_.at(0), segments_[0].get_bits(), segments_[0].number_bytes_including_padding());
	}

	void copy_subsequent_segments()
	{
		uint32_t total_bits = segments_[0].total_number_bits();

		for(uint32_t i = 1; i < segments_.size(); i++)
		{
			uint32_t padding = (uint32_t)(std::ceil((double)total_bits / bit_container_type_size) * bit_container_type_size - total_bits);

			const bit_container_type *segment_to_transfer = segments_[i].get_bits();

			bit_container_type *completed_sib_position = &completed_sib_.at(total_bits / bit_container_type_size);

			if(padding == 0)
				memcpy(completed_sib_position, segment_to_transfer, segments_[i].number_bytes_including_padding()); 

			else
			{
				for(uint32_t j = 0; j < segments_[i].number_bytes_including_padding(); j++)
				{
					transfer_to_lower_bits(completed_sib_position, &segment_to_transfer[j], padding);
					transfer_to_upper_bits(++completed_sib_position, &segment_to_transfer[j], padding);
				}
			}

			total_bits += segments_[i].total_number_bits();
		}
	}

	uint32_t find_padding_used_by_previous_segment(uint32_t i)
	{
		return segments_[i - 1].unused_bits();
	}

	void transfer_all_bits(bit_container_type *comleted_sib_position, const bit_container_type *seg)
	{
			*comleted_sib_position = *seg;
	}

	void transfer_to_lower_bits(bit_container_type *comleted_sib_position, const bit_container_type *seg, uint32_t padding)
	{
		uint32_t right_shift_bits = bit_container_type_size - padding;
		clear_lower_bits(comleted_sib_position, padding);
		*comleted_sib_position |= *seg >> right_shift_bits;
	}

	void transfer_to_upper_bits(bit_container_type *comleted_sib_position, const bit_container_type *seg, uint32_t padding)
	{
		uint32_t right_shift_bits = bit_container_type_size - padding;
		clear_upper_bits(comleted_sib_position, right_shift_bits);
		*comleted_sib_position |= *seg << padding;
	}

	void clear_lower_bits(bit_container_type *bits, uint32_t num_bits_to_clear)
	{
		*bits = *bits >> num_bits_to_clear;
		*bits = *bits << num_bits_to_clear;
	}

	void clear_upper_bits(bit_container_type *bits, uint32_t num_bits_to_clear)
	{
		*bits = *bits << num_bits_to_clear;
		*bits = *bits >> num_bits_to_clear;
	}

	uint32_t completed_sib_total_num_bits_;

	std::vector<bit_container_type> completed_sib_;

	std::vector<segment_type> segments_;

	uint32_t segments_set_flag_; 

	uint32_t set_flag_mask_;

	segment_count_type total_number_of_segments_; 

	segment_index_type segment_expected_; 
	
	//asn1_config config_;

	void append_complete_segment_in_hex_format_to_file()
	{
		if(false/*config_.output_combined_segments()*/)
		{
			std::string filename("complete_segments_hex_format.txt");

			std::ofstream file(filename, std::ios::app);

			if(!file)	throw std::runtime_error(std::string("Unable to open file:  ").append(filename));

			for(uint32_t bit_stream_position = 0; bit_stream_position < completed_sib_.size(); bit_stream_position++)
				file << std::setw(2) << std::setfill('0') <<   std::hex << (uint32_t)completed_sib_[bit_stream_position]; // Cast to an uint32_t so it outputs properly in hex.

			file << std::endl;
		}
	}

	void append_complete_segment_in_binary_format_to_file()
	{
		if(false/*config_.output_combined_segments()*/)
		{
			std::string filename("complete_segments_binary_format.txt");

			std::ofstream file(filename, std::ios_base::binary);

			if(!file)	throw std::runtime_error(std::string("Unable to open file:  ").append(filename));
		
			uint32_t size = completed_sib_.size();
		
			file.write((char*)&size, sizeof(uint32_t));
		
			uint32_t unused_bits = (completed_sib_.size() * bit_container_type_size) - completed_sib_total_num_bits_;
		
			file.write((char*)&unused_bits, sizeof(uint32_t));
		
			for(uint32_t bit_stream_position = 0; bit_stream_position < completed_sib_.size(); bit_stream_position++)
				file.write((const char*)&completed_sib_[bit_stream_position], sizeof(uint8_t));
		}
	}
};


