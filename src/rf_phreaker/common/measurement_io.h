#pragma once
#include "rf_phreaker/common/measurements.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>

namespace rf_phreaker
{
static std::string delimiter = "\t";
static std::string spacer = " | ";

inline std::ostream& operator<<(std::ostream &os, const hardware &t);
inline std::ostream& operator<<(std::ostream &os, const gps &t);
inline std::ostream& operator<<(std::ostream &os, const basic_data &t);
inline std::ostream& operator<<(std::ostream &os, const umts_data &t);
inline std::ostream& operator<<(std::ostream &os, const lte_data &t);

inline std::ostream& operator<<(std::ostream &os, const hardware &t)
{
	os << t.scanner_id_ << delimiter;

	for(const auto &d : t.frequency_paths_)
		os << d.start_freq_ << "-" << d.end_freq_ << delimiter;

	switch(t.device_speed_)
	{
	case USB_HI_SPEED:
		os << "USB_HI_SPEED" << delimiter;
		break;
	case USB_SUPER_SPEED:
		os << "USB_SUPER_SPEED" << delimiter;
		break;
	case UNKNOWN_SPEED:
	default:
		os << "UNKNOWN_SPEED" << delimiter;
	}
	
	os << ctime(&t.rf_calibration_date_);

	return os;
}



inline std::ostream& operator<<(std::ostream &os, const gps &t){
	os << t.scanner_id_ << delimiter
		<< (t.lock_ ? "TRUE" : "FALSE") << delimiter
		<< t.coordinated_universal_time_ << delimiter
		<< t.visible_satellites_ << delimiter
		<< t.tracking_satellites_ << delimiter
		<< t.latitude_ << delimiter
		<< t.longitude_ << delimiter
		<< t.speed_ << delimiter
		<< std::setw(4) << std::setfill('0') << std::hex << t.raw_status_ << std::dec;
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

inline std::ostream& operator<<(std::ostream &os, const umts_data &t)
{
	os << static_cast<basic_data>(t) << delimiter
		<< t.uarfcn_ << delimiter
		<< t.operating_band_ << delimiter
		<< t.cpich_ << delimiter
		<< t.ecio_ << delimiter
		<< t.rscp_ << delimiter
		<< t.layer_3_;
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
		<< t.layer_3_;
	return os;
}

}
