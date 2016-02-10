#pragma once

#include <stdint.h>
#include <vector>
#include "rf_phreaker/layer_3_common/uint16_string.h"

namespace layer_3_information
{


static uint32_t not_decoded_32 = 0xFFFFFFFF;

static uint16_t not_decoded_16 = 0xFFFF;

typedef uint16_string mcc_type;
typedef uint16_string mnc_type;
typedef uint16_t lac_type;
typedef uint32_t cid_type;
typedef int64_t unique_sector_key_type;

enum band_indicator_type
{
	dcs_1800_was_used = 0,
	pcs_1900_was_used = 1,
	unknown_band_was_used = 2
};

struct plmn
{
	mcc_type mcc_;
	mnc_type mnc_;
};

typedef std::vector<plmn> multiple_plmn_type;

struct bit_stream {
	bit_stream() : unused_bits_(0) {}
	bit_stream(const uint8_t *stream, uint32_t num_bytes, uint32_t unused_bits = 0)
	: bytes_(num_bytes)
	, unused_bits_(unused_bits) {
		memcpy(bytes_.data(), stream, num_bytes);
	}
	
	std::vector<uint8_t> bytes_;
	uint32_t unused_bits_;
};

class bcch_bch_message_aggregate
{
public:
	bcch_bch_message_aggregate();

	void swap(bcch_bch_message_aggregate &a)
	{
		mcc_.swap(a.mcc_);
		mnc_.swap(a.mnc_);
		std::swap(lac_, a.lac_);
		std::swap(cid_, a.cid_);
		std::swap(unique_sector_key_, a.unique_sector_key_);
		std::swap(raw_layer_3_, a.raw_layer_3_);
	}

	bool is_mcc_decoded() const { return mcc_ != not_decoded_16; }
	bool is_mnc_decoded() const { return mnc_ != not_decoded_16; }
	bool is_lac_decoded() const { return lac_ != not_decoded_16; }
	bool is_cid_decoded() const { return cid_ != not_decoded_32; }

	virtual bcch_bch_message_aggregate & operator = (bcch_bch_message_aggregate a)
	{
		a.swap(*this);
		return *this;
	}

	virtual void clear() 
	{ 
		mcc_ = not_decoded_16;
		mnc_ = not_decoded_16;
		lac_ = not_decoded_16;
		cid_ = not_decoded_32;
	}

	virtual void update_info(const bcch_bch_message_aggregate &a)
	{
		if(a.is_mcc_decoded())
			mcc_ = a.mcc_;
		if(a.is_mnc_decoded())
			mnc_ = a.mnc_;
		if(a.is_lac_decoded())
			lac_ = a.lac_;
		if(a.is_cid_decoded())
			cid_ = a.cid_;
		for(auto &i : a.raw_layer_3_)
			raw_layer_3_.push_back(i);
	}

	friend std::ostream& operator<<(std::ostream &os, const bcch_bch_message_aggregate &t);

	mcc_type mcc_;
	mnc_type mnc_;
	lac_type lac_;
	cid_type cid_;

	unique_sector_key_type unique_sector_key_; // Key used when recombining segments.

	std::vector<bit_stream> raw_layer_3_;
};


}