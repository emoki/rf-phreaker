#pragma once

#include <stdint.h>
#include <vector>
#include "rf_phreaker/layer_3_common/uint16_string.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"


namespace layer_3_information {

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

struct neighbor_inter
{
	neighbor_inter()
		: uarfcn_(not_decoded_16)
		, cpich_(not_decoded_16) {}

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
		, qrx_lev_min_(not_decoded_16) {}

	bsic_type bsic_;
	band_indicator_type band_indicator_;
	channel_type arfcn_;
	qrx_lev_min_type qrx_lev_min_;
};

struct umts_sib_base {
	umts_sib_base() : is_decoded_(false) {}
	virtual void clear() = 0;
	bool is_decoded() const { return is_decoded_; }
	bool is_decoded_;
};

struct umts_mib_type : public umts_sib_base {
	virtual void clear() {
		is_decoded_ = false;
		plmn_.mcc_ = {};
		plmn_.mnc_ = {};
		multiple_plmns_.clear();
	}
	void swap(umts_mib_type &a) {
		std::swap(is_decoded_, a.is_decoded_);
		plmn_.mcc_.swap(a.plmn_.mcc_);
		plmn_.mnc_.swap(a.plmn_.mnc_);
		multiple_plmns_.swap(a.multiple_plmns_);
	}
	plmn plmn_;
	std::vector<plmn> multiple_plmns_;
};

struct umts_sib1_type : public umts_sib_base {
	virtual void clear() {
		is_decoded_ = false;
		lac_ = -1;
	}
	void swap(umts_sib1_type &a) {
		std::swap(is_decoded_, a.is_decoded_);
		std::swap(lac_, a.lac_);
	}
	int32_t lac_;
};

struct umts_sib3_type : public umts_sib_base {
	virtual void clear() {
		is_decoded_ = false;
		cid_ = -1;
	}
	void swap(umts_sib3_type &a) {
		std::swap(is_decoded_, a.is_decoded_);
		std::swap(cid_, a.cid_);
	}
	int32_t cid_;
};

struct umts_sib4_type : public umts_sib_base {
	virtual void clear() {
		is_decoded_ = false;
		cid_ = -1;
	}
	void swap(umts_sib4_type &a) {
		std::swap(is_decoded_, a.is_decoded_);
		std::swap(cid_, a.cid_);
	}
	int32_t cid_;
};

struct umts_sib11_type : public umts_sib_base {
	virtual void clear() {
		is_decoded_ = false;
		neighbor_intra_group_.clear();
		neighbor_inter_group_.clear();
		neighbor_inter_rat_group_.clear();
	}
	void swap(umts_sib11_type &a) {
		std::swap(is_decoded_, a.is_decoded_);
		neighbor_intra_group_.swap(a.neighbor_intra_group_);
		neighbor_inter_group_.swap(a.neighbor_inter_group_);
		neighbor_inter_rat_group_.swap(a.neighbor_inter_rat_group_);
	}
	std::vector<cpich_type> neighbor_intra_group_;
	std::vector<neighbor_inter> neighbor_inter_group_;
	std::vector<neighbor_inter_rat> neighbor_inter_rat_group_;
};

struct umts_sib11_bis_type : public umts_sib_base {
	virtual void clear() {
		is_decoded_ = false;
		neighbor_intra_group_.clear();
		neighbor_inter_group_.clear();
		neighbor_inter_rat_group_.clear();
	}
	void swap(umts_sib11_bis_type &a) {
		std::swap(is_decoded_, a.is_decoded_);
		neighbor_intra_group_.swap(a.neighbor_intra_group_);
		neighbor_inter_group_.swap(a.neighbor_inter_group_);
		neighbor_inter_rat_group_.swap(a.neighbor_inter_rat_group_);
	}
	std::vector<cpich_type> neighbor_intra_group_;
	std::vector<neighbor_inter> neighbor_inter_group_;
	std::vector<neighbor_inter_rat> neighbor_inter_rat_group_;
};

class umts_bcch_bch_message_aggregate : public bcch_bch_message_aggregate
{
public:
	umts_bcch_bch_message_aggregate();

	umts_bcch_bch_message_aggregate(umts_bcch_bch_message_aggregate &&a) {
		this->swap(a);
	}

	void swap(umts_bcch_bch_message_aggregate &a) {
		bcch_bch_message_aggregate::swap(a);
		std::swap(system_frame_number_, a.system_frame_number_);
		neighbor_intra_group_.swap(a.neighbor_intra_group_);
		neighbor_inter_group_.swap(a.neighbor_inter_group_);
		neighbor_inter_rat_group_.swap(a.neighbor_inter_rat_group_);
		mib_.swap(a.mib_);
		sib1_.swap(a.sib1_);
		sib3_.swap(a.sib3_);
		sib4_.swap(a.sib4_);
		sib11_.swap(a.sib11_);
		sib11_bis_.swap(a.sib11_bis_);
	}

	bool is_system_frame_number_decoded() const { return system_frame_number_ != not_decoded_16; }

	umts_bcch_bch_message_aggregate & operator = (umts_bcch_bch_message_aggregate a) {
		a.swap(*this);
		return *this;
	}

	void clear() {
		bcch_bch_message_aggregate::clear();
		system_frame_number_ = not_decoded_16;
		neighbor_intra_group_.clear();
		neighbor_inter_group_.clear();
		neighbor_inter_rat_group_.clear();
		mib_.clear();
		sib1_.clear();
		sib3_.clear();
		sib4_.clear();
		sib11_.clear();
		sib11_bis_.clear();
	}

	virtual void update_info(const umts_bcch_bch_message_aggregate &a) {
		bcch_bch_message_aggregate::update_info(a);

		if(a.is_system_frame_number_decoded())
			system_frame_number_ = a.system_frame_number_;
		if(!a.neighbor_intra_group_.empty())
			neighbor_intra_group_ = a.neighbor_intra_group_;
		if(!a.neighbor_inter_group_.empty())
			neighbor_inter_group_ = a.neighbor_inter_group_;
		if(!a.neighbor_inter_rat_group_.empty())
			neighbor_inter_rat_group_ = a.neighbor_inter_rat_group_;

		if(a.mib_.is_decoded())
			mib_ = a.mib_;
		if(a.sib1_.is_decoded())
			sib1_ = a.sib1_;
		if(a.sib3_.is_decoded())
			sib3_ = a.sib3_;
		if(a.sib4_.is_decoded())
			sib4_ = a.sib4_;
		if(a.sib11_.is_decoded())
			sib11_ = a.sib11_;
		if(a.sib11_bis_.is_decoded())
			sib11_bis_ = a.sib11_bis_;
	}

	friend std::ostream& operator<<(std::ostream &os, const umts_bcch_bch_message_aggregate &t);

	system_frame_number_type system_frame_number_;
	std::vector<cpich_type> neighbor_intra_group_;
	std::vector<neighbor_inter> neighbor_inter_group_;
	std::vector<neighbor_inter_rat> neighbor_inter_rat_group_;
	umts_mib_type mib_;
	umts_sib1_type sib1_;
	umts_sib3_type sib3_;
	umts_sib4_type sib4_;
	umts_sib11_type sib11_;
	umts_sib11_bis_type sib11_bis_;
};


}