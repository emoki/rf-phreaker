#pragma once

#include <stdint.h>
#include <vector>
#include "rf_phreaker/layer_3_common/uint16_string.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"


namespace layer_3_information
{

enum umts_sib_type
{
	MIB,
	SIB1,
	SIB3_SIB4,
	SIB11,
};
	
typedef uint16_t system_frame_number_type;
typedef uint16_t cpich_type;
typedef uint16_t channel_type;
typedef uint16_string bsic_type;
typedef int16_t qrx_lev_min_type;
typedef int16_t band_indicator_type;

struct neighbor_inter
{
	neighbor_inter() 
		: uarfcn_(not_decoded_16)
		, cpich_(not_decoded_16) 
	{}

	channel_type uarfcn_;
	cpich_type cpich_;
};

// 3GPP TS 25.331 version 10.3.1 Release 10
// 10.3.7.47a Measurement control system information extension
// Currently we only decode the RAT if it's GSM.  IS-2000 we ignore.
struct neighbor_inter_rat
{
	neighbor_inter_rat() 
		: bsic_(not_decoded_16)
		, band_indicator_(unknown_band_was_used)
		, arfcn_(not_decoded_16)
		, qrx_lev_min_(not_decoded_16) 
	{}

	bsic_type bsic_;
	band_indicator band_indicator_;
	channel_type arfcn_;
	qrx_lev_min_type qrx_lev_min_;
};

struct sib_18
{
	sib_18() 
		: inter_rat_mcc_(not_decoded_16)
		, inter_rat_mnc_(not_decoded_16)
	{}

	mcc_type inter_rat_mcc_;
	mnc_type inter_rat_mnc_;
};

class umts_bcch_bch_message_aggregate : public bcch_bch_message_aggregate
{
public:

	umts_bcch_bch_message_aggregate();

	umts_bcch_bch_message_aggregate(umts_bcch_bch_message_aggregate &&a)
		//: umts_bcch_bch_message_aggregate()
	{
		this->swap(a);
	}

	void swap(umts_bcch_bch_message_aggregate &a)
	{
		bcch_bch_message_aggregate::swap(a);
		std::swap(system_frame_number_, a.system_frame_number_);
		neighbor_intra_group_.swap(a.neighbor_intra_group_);
		neighbor_inter_group_.swap(a.neighbor_inter_group_);
		neighbor_inter_rat_group_.swap(a.neighbor_inter_rat_group_);
	}

	bool is_system_frame_number_decoded() const { return system_frame_number_ != not_decoded_16; }

	umts_bcch_bch_message_aggregate & operator = (umts_bcch_bch_message_aggregate a)
	{
		a.swap(*this);
		return *this;
	}

	void clear() 
	{ 
		bcch_bch_message_aggregate::clear();
		system_frame_number_ = not_decoded_16;
		neighbor_intra_group_.clear();
		neighbor_inter_group_.clear();
		neighbor_inter_rat_group_.clear();
	}

	virtual void update_info(const umts_bcch_bch_message_aggregate &a)
	{
		bcch_bch_message_aggregate::update_info(a);

		if(a.is_system_frame_number_decoded())
			system_frame_number_ = a.system_frame_number_;
		if(!a.neighbor_intra_group_.empty())
			neighbor_intra_group_ = a.neighbor_intra_group_;
		if(!a.neighbor_inter_group_.empty())
			neighbor_inter_group_ = a.neighbor_inter_group_;
		if(!a.neighbor_inter_rat_group_.empty())
			neighbor_inter_rat_group_ = a.neighbor_inter_rat_group_;
		if(!a.sib_18_group_.empty())
			sib_18_group_ = a.sib_18_group_;
	}

	friend std::ostream& operator<<(std::ostream &os, const umts_bcch_bch_message_aggregate &t);

	system_frame_number_type system_frame_number_;

	std::vector<cpich_type> neighbor_intra_group_;

	std::vector<neighbor_inter> neighbor_inter_group_;

	std::vector<neighbor_inter_rat> neighbor_inter_rat_group_;

	std::vector<sib_18> sib_18_group_;
};


}