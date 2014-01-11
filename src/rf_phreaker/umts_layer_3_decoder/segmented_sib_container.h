#pragma once

#include "rf_phreaker/umts_layer_3_decoder/segmented_sib.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include "rf_phreaker/layer_3_decoder_common/asn1_types.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_decoder_common/asn1_config.h"
#include <map>

using namespace layer_3_information;

class unique_sector_sib
{
public:
	unique_sector_sib(sib_type sib, unique_sector_key_type key) : sib_(sib), unique_sector_key_(key), age_(0) {}
	sib_type sib_;
	unique_sector_key_type unique_sector_key_;
	
	bool operator < (const unique_sector_sib &a) const
	{
		if(sib_ == a.sib_)
			return unique_sector_key_ < a.unique_sector_key_;
		else
			return sib_ < a.sib_;
	}

	uint64_t age_;
};

class segmented_sib_container
{
public:
	segmented_sib_container(void);
	~segmented_sib_container(void);

	void add_first_segment(const unique_sector_sib &sib, segment_count_type seg_count, bit_stream_container bit_stream);
	void add_subsequent_segment(const unique_sector_sib &sib, segment_index_type seg_index, bit_stream_container bit_stream);
	void add_last_segment(const unique_sector_sib &sib, segment_index_type seg_index, bit_stream_container bit_stream);
	
	bool is_sib_complete(const unique_sector_sib &sib);

	bit_stream_container get_completed_sib(const unique_sector_sib &sib);

	void clear_segments(const unique_sector_sib &key);

private:
	std::map<unique_sector_sib, segmented_sib>::iterator find_segment_iterator(unique_sector_sib sib);

	void open_debug_segment_file(); 
	
	void output_segment_to_file_if_specified(const unique_sector_sib &sib, segment_count_type seg_count, segment_index_type seg_index, bit_stream_container bit_stream);

	void remove_segmented_sibs_if_necessary();

	std::map<unique_sector_sib, segmented_sib> segmented_sibs_;

	size_t max_segmented_sibs_size_;

	uint64_t age_counter_;

	asn1_config config_;
};

