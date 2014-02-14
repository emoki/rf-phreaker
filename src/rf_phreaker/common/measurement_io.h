#pragma once
#include "rf_phreaker/common/measurements.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

namespace rf_phreaker
{
static std::string delimiter = "\t";
static std::string spacer = " | ";

inline std::ostream& operator<<(std::ostream &os, const gps &t);
inline std::ostream& operator<<(std::ostream &os, const basic_data &t);
inline std::ostream& operator<<(std::ostream &os, const lte_data &t);



inline std::ostream& operator<<(std::ostream &os, const gps &t){
	os << t.scanner_id_ << delimiter
		<< (t.lock_ ? "TRUE" : "FALSE") << delimiter
		<< t.coordinated_universal_time_ << delimiter
		<< t.visible_satelites_ << delimiter
		<< t.tracking_satelites_ << delimiter
		<< t.latitude_ << delimiter
		<< t.longitude_ << delimiter
		<< t.speed_ << delimiter
		<< std::setw(4) << std::setfill('0') << std::hex << t.raw_status_;
	return os;
}
	
inline std::ostream& operator<<(std::ostream &os, const basic_data &t) {
	os << t.collection_round_ << delimiter
		<< t.carrier_frequency_ << delimiter
		<< t.carrier_bandwidth_ << delimiter
		<< t.carrier_signal_level_ << delimiter
		<< t.time_ << delimiter
		<< t.status_flags_;
	return os;
}
	
inline std::ostream& operator<<(std::ostream &os, const plmn &t)
{
	os << t.mcc_ << spacer
		<< t.mnc_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const plmn_group &t)
{
	for(uint32_t i = 0, end = t.size_; i < end; ++i) {
		if(t.size_ - i == 1)
			os << t;
		else
			os << t << delimiter;
	}
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const sys_info_base &t)
{
	os << t.decoded_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_mib &t)
{
	os << static_cast<sys_info_base>(t);
	if(t.decoded_) 
		os << delimiter << t.plmns_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_sib_1 &t)
{
	os << static_cast<sys_info_base>(t);
	if(t.decoded_) 
		os << delimiter << t.lac_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_sib_3 &t)
{
	os << static_cast<sys_info_base>(t);
	if(t.decoded_) 
		os << delimiter	<< t.cid_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_sib_4 &t)
{
	os << static_cast<sys_info_base>(t);
	if(t.decoded_)
		os << delimiter << t.cid_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const neighbor_inter &t)
{
	os << t.channel_ << delimiter
		<< t.cpich_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const gsm_neighbor_inter_rat &t)
{
	os << t.channel_ << spacer
		<< t.bsic_ << spacer
		<< (t.band_indicator_ == dcs_1800_was_used ? "DCS_1800" : "PCS_1900") << spacer
		<< t.rssi_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_sib_11 &t)
{
	os << static_cast<sys_info_base>(t);
	if(t.decoded_) {
		for(int i = 0, end = t.intra_neighbors_.size_; i < end; ++i) {
			if(end - i == 1) os << t.intra_neighbors_.elements_[i];
			else os << t.intra_neighbors_.elements_[i] << delimiter;
		}
		for(int i = 0, end = t.inter_neighbors_.size_; i < end; ++i) {
			os << delimiter << t.inter_neighbors_.elements_[i];
		}
		for(int i = 0, end = t.gsm_neighbors_.size_; i < end; ++i) {
			os << delimiter << t.gsm_neighbors_.elements_[i];
		}
	}
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const umts_data &t)
{
	os << static_cast<basic_data>(t) << delimiter
		<< t.uarfcn_ << delimiter
		<< t.operating_band_ << delimiter
		<< t.cpich_ << delimiter
		<< t.ecio_ << delimiter
		<< t.rscp_ << delimiter
		<< t.mib_ << delimiter
		<< t.sib_1_ << delimiter
		<< t.sib_3_ << delimiter
		<< t.sib_4_ << delimiter
		<< t.sib_11_;
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const lte_sib_1 &t)
{
	os << static_cast<sys_info_base>(t);
	if(t.decoded_) {
		os << delimiter
			<< t.plmns_ << delimiter
			<< t.tac_ << delimiter
			<< t.cid_;
	}
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const lte_data &t)
{
	os << static_cast<basic_data>(t) << delimiter
		<< t.physical_cell_id_ << delimiter
		<< t.rsrp_ << delimiter
		<< t.rsrq_ << delimiter
		<< t.rssi_ << delimiter
		<< t.psch_id_ << delimiter
		<< t.psch_quality_ << delimiter
		<< t.ssch_id_ << delimiter
		<< t.ssch_quality_ << delimiter
		<< t.rs_quality_ << delimiter
		<< t.cyclic_prefix_ << delimiter
		<< t.num_antenna_ports_ << delimiter
		<< t.frame_number_ << delimiter
		<< t.sib_1_;
	return os;
}

}
