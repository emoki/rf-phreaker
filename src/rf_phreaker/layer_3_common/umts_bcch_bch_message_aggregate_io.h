#pragma once 

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate_io.h"

namespace layer_3_information 
{

inline std::ostream& header(std::ostream &os, const umts_sib_base &t);
inline std::ostream& header(std::ostream &os, const umts_mib_type &t);
inline std::ostream& header(std::ostream &os, const umts_sib1_type &t);
inline std::ostream& header(std::ostream &os, const umts_sib3_type &t);
inline std::ostream& header(std::ostream &os, const umts_sib4_type &t);
inline std::ostream& header(std::ostream &os, const umts_sib11_type &t);
inline std::ostream& header(std::ostream &os, const umts_sib11_bis_type &t);

inline std::ostream& operator<<(std::ostream &os, const umts_sib_base &t);
inline std::ostream& operator<<(std::ostream &os, const umts_mib_type &t);
inline std::ostream& operator<<(std::ostream &os, const umts_sib1_type &t);
inline std::ostream& operator<<(std::ostream &os, const umts_sib3_type &t);
inline std::ostream& operator<<(std::ostream &os, const umts_sib4_type &t);
inline std::ostream& operator<<(std::ostream &os, const umts_sib11_type &t);
inline std::ostream& operator<<(std::ostream &os, const umts_sib11_bis_type &t);

inline std::ostream& header(std::ostream &os, const umts_sib_base &t) {
	os << "is_decoded";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const umts_sib_base &t) {
	os << (t.is_decoded() ? "YES" : "NO");
	return os;
}

inline std::ostream& output_empty_umts_mib(std::ostream &os) {
	for(int i = 0; i < 2; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const umts_mib_type &t) {
	os << "mib_mcc\tmib_mnc\tmib_multiple_plmns";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const umts_mib_type &t) {
	os << t.plmn_.mcc_.to_string() << main_delim
		<< t.plmn_.mnc_.to_string() << main_delim;
	os << begin_delim;
	for(auto &i : t.multiple_plmns_)
		os << i.mcc_.to_string() << spacer2 << i.mnc_.to_string() << spacer;
	os << end_delim;
	return os;
}


inline std::ostream& output_empty_umts_sib1(std::ostream &os) {
	return os;
}
inline std::ostream& header(std::ostream &os, const umts_sib1_type &t) {
	os << "sib1_lac";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const umts_sib1_type &t) {
	os << t.lac_;
	return os;
}

inline std::ostream& output_empty_umts_sib3(std::ostream &os) {
	return os;
}
inline std::ostream& header(std::ostream &os, const umts_sib3_type &t) {
	os << "sib3_cid";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const umts_sib3_type &t) {
	os << t.cid_;
	return os;
}

inline std::ostream& output_empty_umts_sib4(std::ostream &os) {
	return os;
}
inline std::ostream& header(std::ostream &os, const umts_sib4_type &t) {
	os << "sib4_cid";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const umts_sib4_type &t) {
	return os;
}


inline std::ostream& output_empty_umts_sib11(std::ostream &os) {
	for(int i = 0; i < 2; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const umts_sib11_type &t) {
	os << "sib11_neighbor_intra [cpich]\tsib11_nieghbor_inter[uarfcn cpich]\tsib11_nieghbor_inter_rat [arfcn bsic qrx_lev_min bai]";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const umts_sib11_type &t) {
	os << begin_delim;
	for(auto &i : t.neighbor_intra_group_)
		os << i << spacer;
	os << end_delim << main_delim;
	os << begin_delim;
	for(auto &i : t.neighbor_inter_group_)
		os << i.uarfcn_ << spacer2 << i.cpich_ << spacer;
	os << end_delim << main_delim;
	os << begin_delim;
	for(auto &i : t.neighbor_inter_rat_group_)
		os << i.arfcn_ << spacer2 << i.bsic_ << spacer2 << i.qrx_lev_min_ << spacer2 << 
		(i.band_indicator_ == layer_3_information::dcs_1800_was_used ? "DCS_1800" :
		(i.band_indicator_ == layer_3_information::pcs_1900_was_used ? "PCS_1900" : "UNKNOWN")) << spacer;
	os << end_delim;
	return os;
}

inline std::ostream& output_empty_umts_sib11_bis(std::ostream &os) {
	for(int i = 0; i < 2; ++i) os << main_delim;
	return os;
}
inline std::ostream& header(std::ostream &os, const umts_sib11_bis_type &t) {
	os << "sib11_bis_neighbor_intra [cpich]\tsib11_bis_nieghbor_inter[uarfcn cpich]\tsib11_bis_nieghbor_inter_rat [arfcn bsic qrx_lev_min bai]";
	return os;
}
inline std::ostream& operator<<(std::ostream &os, const umts_sib11_bis_type &t) {
	os << begin_delim;
	for(auto &i : t.neighbor_intra_group_)
		os << i << spacer;
	os << end_delim << main_delim;
	os << begin_delim;
	for(auto &i : t.neighbor_inter_group_)
		os << i.uarfcn_ << spacer2 << i.cpich_ << spacer;
	os << end_delim << main_delim;
	os << begin_delim;
	for(auto &i : t.neighbor_inter_rat_group_)
		os << i.arfcn_ << spacer2 << i.bsic_ << spacer2 << i.qrx_lev_min_ << spacer2 <<
		(i.band_indicator_ == layer_3_information::dcs_1800_was_used ? "DCS_1800" :
		(i.band_indicator_ == layer_3_information::pcs_1900_was_used ? "PCS_1900" : "UNKNOWN")) << spacer;
	os << end_delim;
	return os;
}



inline std::ostream& header(std::ostream &os, const umts_bcch_bch_message_aggregate &t) {
	header(os, t.mib_) << main_delim;
	header(os, t.sib1_) << main_delim;
	header(os, t.sib3_) << main_delim;
	header(os, t.sib4_) << main_delim;
	header(os, t.sib11_) << main_delim;
	header(os, t.sib11_bis_) << main_delim;
	os << "raw_layer_3";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_bcch_bch_message_aggregate &t)
{
	if(t.mib_.is_decoded())
		os << t.mib_ << main_delim;
	else
		output_empty_umts_mib(os) << main_delim;
	if(t.sib1_.is_decoded())
		os << t.sib1_ << main_delim;
	else
		output_empty_umts_sib1(os) << main_delim;
	if(t.sib3_.is_decoded())
		os << t.sib3_ << main_delim;
	else
		output_empty_umts_sib3(os) << main_delim;
	if(t.sib4_.is_decoded())
		os << t.sib4_ << main_delim;
	else
		output_empty_umts_sib4(os) << main_delim;
	if(t.sib11_.is_decoded())
		os << t.sib11_ << main_delim;
	else
		output_empty_umts_sib11(os) << main_delim;
	if(t.sib11_bis_.is_decoded())
		os << t.sib11_bis_ << main_delim;
	else
		output_empty_umts_sib11_bis(os) << main_delim;

	os << t.raw_layer_3_;

	return os;
}


}