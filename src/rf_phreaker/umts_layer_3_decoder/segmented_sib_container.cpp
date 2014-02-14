#include "rf_phreaker/umts_layer_3_decoder/segmented_sib_container.h"
#include <boost/assert.hpp>
#include <fstream>
#include <iomanip>


segmented_sib_container::segmented_sib_container(void)
	: max_segmented_sibs_size_(32)
	, age_counter_(0)
{
	open_debug_segment_file();
}


segmented_sib_container::~segmented_sib_container(void)
{
}

void segmented_sib_container::add_first_segment(const unique_sector_sib &sib, segment_count_type seg_count, bit_stream_container bit_stream)
{
	output_segment_to_file_if_specified(sib, seg_count, 0, bit_stream);
	auto it = find_segment_iterator(sib);
	it->second.set_first_segment(bit_stream, seg_count);
}
	
void segmented_sib_container::add_subsequent_segment(const unique_sector_sib &sib, segment_index_type seg_index, bit_stream_container bit_stream)
{
	output_segment_to_file_if_specified(sib, 0, seg_index, bit_stream);
	auto it = find_segment_iterator(sib);
	it->second.set_subsequent_segment(bit_stream, seg_index);
}

void segmented_sib_container::add_last_segment(const unique_sector_sib &sib, segment_index_type seg_index, bit_stream_container bit_stream)
{
	output_segment_to_file_if_specified(sib, 0, seg_index, bit_stream);
	auto it = find_segment_iterator(sib);
	it->second.set_last_segment(bit_stream, seg_index);
}

bool segmented_sib_container::is_sib_complete(const unique_sector_sib &sib)
{
	auto it = find_segment_iterator(sib);
	return it->second.is_sib_complete();
}

std::map<unique_sector_sib, segmented_sib>::iterator segmented_sib_container::find_segment_iterator(unique_sector_sib sib)
{
	auto it = segmented_sibs_.find(sib);
	
	if(it == segmented_sibs_.end())
	{
		remove_segmented_sibs_if_necessary();
		sib.age_ = age_counter_++;
		auto p = segmented_sibs_.insert(std::make_pair(sib, segmented_sib()));
		it = p.first;
	}

	return it;
}

void segmented_sib_container::remove_segmented_sibs_if_necessary()
{
	BOOST_ASSERT(max_segmented_sibs_size_ > 0);
	if(segmented_sibs_.size() > max_segmented_sibs_size_)
	{
		uint64_t age = 0xffffffffffffffff;
		auto iterator_to_be_erased = segmented_sibs_.begin();
		for(auto it = segmented_sibs_.begin(); it != segmented_sibs_.end(); it++)
		{
			if(it->first.age_ < age)
			{
				age = it->first.age_;
				iterator_to_be_erased = it;
			}
		}
		segmented_sibs_.erase(iterator_to_be_erased);
	}
}

bit_stream_container segmented_sib_container::get_completed_sib(const unique_sector_sib &sib)
{
	auto it = find_segment_iterator(sib);

	return it->second.get_completed_sib();
}

void segmented_sib_container::clear_segments(const unique_sector_sib &key)
{
	auto it = find_segment_iterator(key);
	it->second.clear();
}

void segmented_sib_container::open_debug_segment_file()
{
	if(false/*config_.output_segments()*/)
	{
		std::ofstream file("debug_segments.txt");
		if(!file)
			throw std::runtime_error("Unable to open debug_segments.txt");
		file << "sib_type\tunique_sector\tage\tseg_count\tseg_index\tbit_stream_in_hex" << std::endl;
	}
}
void segmented_sib_container::output_segment_to_file_if_specified(const unique_sector_sib &sib, segment_count_type seg_count, segment_index_type seg_index, bit_stream_container bit_stream)
{
	if(false/*config_.output_segments()*/)
	{
		std::ofstream file("debug_segments.txt", std::ios_base::app);
	
		if(!file)
			throw std::runtime_error("Unable to open debug_segments.txt");
	
		file	<< sib.sib_ << "\t"
				<< sib.unique_sector_key_ << "\t"
				<< sib.age_ << "\t"
				<< seg_count << "\t"
				<< seg_index << "\t";
	
		for(uint32_t i = 0; i < bit_stream.num_of_bytes(); i++)
			file << std::setw(2) << std::setfill('0') << std::hex << (uint32_t)bit_stream.bit_stream()[i];

		file << std::dec << std::endl;
	}
}
