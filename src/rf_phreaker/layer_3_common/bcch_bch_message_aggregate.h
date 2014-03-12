#pragma once

#include <stdint.h>
#include "rf_phreaker/layer_3_common/uint16_string.h"

namespace layer_3_information
{


static uint32_t not_decoded_32 = 0xFFFFFFFF;

static uint16_t not_decoded_16 = 0xFFFF;

typedef uint16_string mcc_type;
typedef uint16_string mnc_type;
typedef uint16_t lac_type;
typedef uint32_t cid_type;
typedef uint32_t unique_sector_key_type;

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
	}

	friend std::ostream& operator<<(std::ostream &os, const bcch_bch_message_aggregate &t);

	mcc_type mcc_;
	mnc_type mnc_;
	lac_type lac_;
	cid_type cid_;

	unique_sector_key_type unique_sector_key_; // Key used when recombining segments.
};

static std::string delimiter = "\t";
static std::string spacer2 = " : ";
static std::string spacer = " | ";

inline std::ostream& operator << (std::ostream &os, const bcch_bch_message_aggregate &t)
{
	os << t.mcc_ << delimiter
		<< t.mnc_ << delimiter
		<< t.lac_ << delimiter
		<< t.cid_;
	return os;
}

};