#include "beagle_io.h"
#include <iomanip>

namespace cappeen_scanner {

template<> void output_beagle_api_header<beagle_info_wrapper>(std::ostream &os)
{
	os << "beagle_id" << beagle_delimiter
		<< "beagle_state" << beagle_delimiter
		<< "rf_calibration_date" << beagle_delimiter
		<< "dds_clock_calibration_date" << beagle_delimiter
		<< "serial" << beagle_delimiter
		<< "device_speed" << beagle_delimiter
		<< "licenses..." << beagle_delimiter
		<< "available_bands..." 
		<< std::endl;
}

template<> void output_beagle_api_header<gps_info_wrapper>(std::ostream &os)
{
	os	<< "hw_calibrated" << beagle_delimiter
				<< "gps_locked" << beagle_delimiter
				<< "utc_time" << beagle_delimiter
				<< "sat_visible" << beagle_delimiter
				<< "sat_tracking" << beagle_delimiter
				<< "lat" << beagle_delimiter
				<< "lon" << beagle_delimiter
				<< "raw_status" << beagle_delimiter
				<< std::endl;
}

template<> void output_beagle_api_header<gsm_sector_info_wrapper>(std::ostream &os)
{
	os	<< "collection_round" << beagle_delimiter
			<< "arfcn" << beagle_delimiter
			<< "bsic" << beagle_delimiter
			<< "mcc" << beagle_delimiter
			<< "mnc" << beagle_delimiter
			<< "lac" << beagle_delimiter
			<< "cid" << beagle_delimiter
			<< "signal_level" << beagle_delimiter
			<< "c/i" << beagle_delimiter
			<< "band" << beagle_delimiter
			<< std::endl;
}

template<> void output_beagle_api_header<gsm_sweep_info_wrapper>(std::ostream &os) {
	os << "freq" << beagle_delimiter
		<< "rssi";

	os << std::endl;
}

template<> void output_beagle_api_header<umts_sector_info_wrapper>(std::ostream &os)
{
	os	<< "collection_round" << beagle_delimiter
			<< "carrier_freq" << beagle_delimiter
			<< "carrier_sl" << beagle_delimiter
			<< "uarfcn" << beagle_delimiter
			<< "mcc" << beagle_delimiter
			<< "mnc" << beagle_delimiter
			<< "lac" << beagle_delimiter
			<< "cid" << beagle_delimiter
			<< "cpich" << beagle_delimiter
			<< "ecio" << beagle_delimiter
			<< "rscp" << beagle_delimiter
			<< "band" << beagle_delimiter
			<< "neighbor_intra : cpich...." << beagle_delimiter
			<< "neighbor_inter : uarfcn | cpich...." << beagle_delimiter
			<< "gsm_neighbor_inter_rat : arfcn | bsic | band_indicator | rssi..." << beagle_delimiter
			<< "sib_18 : inter_mcc | inter_mnc";

	os << std::endl;
}

template<> void output_beagle_api_header<umts_sweep_info_wrapper>(std::ostream &os)
{
	os	<< "freq" << beagle_delimiter
		<< "rssi";

	os << std::endl;
}

template<> void output_beagle_api_header<lte_sector_info_wrapper>(std::ostream &os)
{
	os << "collection_round" << beagle_delimiter
		<< "carrier_freq" << beagle_delimiter
		<< "carrier_sl" << beagle_delimiter
		<< "earfcn" << beagle_delimiter
		<< "lte_operating_band_" << beagle_delimiter
		<< "physical_cell_id" << beagle_delimiter
		<< "rsrp" << beagle_delimiter
		<< "rsrq" << beagle_delimiter
		<< "rssi" << beagle_delimiter
		<< "primary_sync_id" << beagle_delimiter
		<< "primary_sync_quality" << beagle_delimiter
		<< "secondary_sync_id" << beagle_delimiter
		<< "secondary_sync_quality" << beagle_delimiter
		<< "carrier_bandwidth" << beagle_delimiter
		<< "antenna_ports" << beagle_delimiter
		<< "system_frame_number" << beagle_delimiter
		<< "cyclic_prefix_length" << beagle_delimiter
		<< "plmns : mcc | mnc...." << beagle_delimiter
		<< "tracking_area_code" << beagle_delimiter
		<< "cell_id";

	os << std::endl;
}

template<> void output_beagle_api_header<lte_sweep_info_wrapper>(std::ostream &os)
{
	os	<< "freq" << beagle_delimiter
		<< "rssi";

	os << std::endl;
}

template<> void output_beagle_api_header<api_string>(std::ostream &os)
{
	os << "number" << beagle_delimiter
		<< "string";

	os << std::endl;
}


std::ostream& operator <<( std::ostream &os, const band_group_type &t)
{
	for(uint32_t i = 0; i < t.size(); i++)
	{
		os << "b_" << t.get_element(i);

		if(i != t.size() - 1)
			os << beagle_delimiter;
	}
	return os;
}

std::ostream& operator <<( std::ostream &os, const technologies_and_band_group_type &t)
{
	for(uint32_t i = 0; i < t.size(); i++)
	{
		os << "l_" << t.get_element(i);
	
		if(i != t.size() - 1)
			os << beagle_delimiter;
	}
	return os;
}

std::ostream& operator <<( std::ostream &os, const neighbor_intra_type &t)
{
	for(uint32_t i = 0; i < t.size(); i++)
	{
		os << t.get_element(i);
	
		if(i != t.size() - 1)
			os << beagle_delimiter;
	}
	return os;
}

std::ostream& operator <<( std::ostream &os, const neighbor_inter_type &t)
{
	for(uint32_t i = 0; i < t.size(); i++)
	{
		os << t.get_element(i).channel_ << beagle_spacer 
			<< t.get_element(i).cpich_;
	
		if(i != t.size() - 1)
			os << beagle_delimiter;
	}
	return os;
}

std::ostream& operator <<( std::ostream &os, const gsm_neighbor_inter_rat_type &t)
{
	for(uint32_t i = 0; i < t.size(); i++)
	{
		os << t.get_element(i).channel_ << beagle_spacer 
			<< t.get_element(i).bsic_ << beagle_spacer 
			<< t.get_element(i).band_indicator_ << beagle_spacer 
			<< (int32_t) t.get_element(i).rssi_;

		if(i != t.size() - 1)
			os << beagle_delimiter;
	}
	return os;
}

std::ostream& operator <<(std::ostream &os, const plmns_type &t)
{
	for(uint32_t i = 0; i < t.size(); i++)
	{
		os << t.get_element(i).mcc_ << beagle_spacer
			<< t.get_element(i).mnc_;
		
		if(i != t.size() - 1)
			os << beagle_delimiter;
	}
	return os;
}

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::umts_sib_18_type &t)
{
	if (t.decoded_)
	{
		os << t.plmns_;
	}
	return os;
}

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::lte_sib_1_type &t)
{
	if (t.decoded_)
	{
		os << t.plmns_ << beagle_delimiter
			<< t.tac_ << beagle_delimiter
			<< t.cid_;
	}
	return os;
}

std::ostream& operator <<( std::ostream &os, const beagle_info_wrapper &t)
{
	os	<< t.beagle_id_ << beagle_delimiter
		<< t.state_ << beagle_delimiter
		<< t.rf_calibration_date_ << beagle_delimiter
		<< t.dds_clock_correction_calibration_date_ << beagle_delimiter
		<< t.beagle_serial_<< beagle_delimiter
		<< (t.device_speed_ == beagle_api::USB_SUPER_SPEED ? "USB_SUPER_SPEED" : "USB_HI_SPEED")<< beagle_delimiter
		<< t.valid_licenses_ << beagle_delimiter
		<< t.available_bands_in_hardware_;	

	return os;
}

std::ostream& operator <<( std::ostream &os, const gps_info_wrapper &t)
{
	os	<< t.hw_calibrated_ << beagle_delimiter
		<< t.gps_locked_ << beagle_delimiter
		<< t.utc_time_ << beagle_delimiter
		<< t.num_visible_sat_ << beagle_delimiter
		<< t.num_track_sat_ << beagle_delimiter
		<< t.lat_ << beagle_delimiter
		<< t.lon_ << beagle_delimiter
		<< t.raw_gps_status_;

	return os;
}

std::ostream& operator <<( std::ostream &os, const gsm_sector_info_wrapper &t)
{
	os << t.collection_round_ << beagle_delimiter
		<< t.carrier_freq_ << beagle_delimiter
		<< t.rssi_ << beagle_delimiter
		<< t.arfcn_ << beagle_delimiter
		<< t.operating_band_ << beagle_delimiter
		<< std::setw(2) << std::setfill('0') << t.bsic_ << beagle_delimiter
		<< t.cell_sl_ << beagle_delimiter
		<< t.ctoi_;

	return os;
}

std::ostream& operator <<(std::ostream &os, const gsm_sweep_info_wrapper &t) {
	os << t.frequency_ << beagle_delimiter
		<< t.rssi_;

	return os;
}

std::ostream& operator <<( std::ostream &os, const umts_sector_info_wrapper &t)
{
	os << t.collection_round_ << beagle_delimiter
		<< t.carrier_freq_ << beagle_delimiter
		<< t.carrier_sl_ << beagle_delimiter
		<< t.uarfcn_ << beagle_delimiter;

	if(t.mcc_three_digits_)
		os << std::setw(3) << std::setfill('0') << t.mcc_ << beagle_delimiter;
	else
		os << std::setw(2) << std::setfill('0') << t.mcc_ << beagle_delimiter;

	if(t.mnc_three_digits_)
		os << std::setw(3) << std::setfill('0') << t.mnc_ << beagle_delimiter;
	else
		os << std::setw(2) << std::setfill('0') << t.mnc_ << beagle_delimiter;

	os << t.lac_ << beagle_delimiter
		<< t.cell_id_ << beagle_delimiter
		<< t.cpich_ << beagle_delimiter
		<< t.ecio_ << beagle_delimiter
		<< t.rscp_ << beagle_delimiter
		<< t.band_ << beagle_delimiter
		<< t.neighbor_intra_group_ << beagle_delimiter
		<< t.neighbor_inter_group_ << beagle_delimiter
		<< t.gsm_neighbor_inter_rat_group_ << beagle_delimiter
		<< t.sib_18_group_;

	return os;
}

std::ostream& operator <<( std::ostream &os, const umts_sweep_info_wrapper &t)
{
	os << t.frequency_ << beagle_delimiter
		<< t.rssi_;

	return os;
}

std::ostream& operator <<( std::ostream &os, const lte_sector_info_wrapper &t)
{
	os << t.collection_round_ << beagle_delimiter
		<< t.carrier_freq_ << beagle_delimiter
		<< t.carrier_sl_ << beagle_delimiter
		<< t.earfcn_ << beagle_delimiter
		<< t.lte_operating_band_ << beagle_delimiter
		<< t.physical_cell_id_ << beagle_delimiter
		<< t.rsrp_ << beagle_delimiter
		<< t.rsrq_ << beagle_delimiter
		<< t.rssi_ << beagle_delimiter
		<< t.primary_sync_id_ << beagle_delimiter
		<< t.primary_sync_quality_ << beagle_delimiter
		<< t.secondary_sync_id_ << beagle_delimiter
		<< t.secondary_sync_quality_ << beagle_delimiter
		<< t.carrier_bandwidth_ << beagle_delimiter
		<< (int16_t)t.antenna_ports_ << beagle_delimiter
		<< t.system_frame_number_ << beagle_delimiter
		<< (t.cyclic_prefix_length_ == 1 ? "Normal" : "Extended");
	if(t.sib_1_.decoded_)
		os << beagle_delimiter << "sib1 decoded!";
	if(t.sib_3_.decoded_)
		os << beagle_delimiter << "sib3 decoded!";
	if(t.sib_4_.decoded_)
		os << beagle_delimiter << "sib4 decoded!";
	if(t.sib_5_.decoded_)
		os << beagle_delimiter << "sib5 decoded!";
	if(t.sib_6_.decoded_)
		os << beagle_delimiter << "sib6 decoded!";
	if(t.sib_7_.decoded_)
		os << beagle_delimiter << "sib7 decoded!";
	if(t.sib_8_.decoded_)
		os << beagle_delimiter << "sib8 decoded!";

	return os;
}

std::ostream& operator <<( std::ostream &os, const lte_sweep_info_wrapper &t)
{
	os << t.frequency_ << beagle_delimiter
		<< t.rssi_;

	return os;
}

std::ostream& operator <<( std::ostream &os, const api_string &t)
{
	os << t.number_ << beagle_delimiter
		<< t.str_;

	return os;
}



}