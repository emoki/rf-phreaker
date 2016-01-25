#pragma once 

#include <list>
#include <boost/thread.hpp>
#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen_console_app/api_string.h"
#include "rf_phreaker/cappeen_console_app/group.h"

namespace cappeen_scanner {

template<typename Wrapper>
class thead_safe_storage
{
public:
	template<typename Data>
	void push_back_all(const Data *data, int num_data) {
		boost::lock_guard<boost::timed_mutex> lock(mutex_);
		for(int i = 0; i < num_data; i++)
			list_.push_back(data[i]);
	}

	template<typename Data>
	void push_back(const Data &data) {
		boost::lock_guard<boost::timed_mutex> lock(mutex_);
		list_.push_back(data);
	}

	std::list<typename Wrapper> pop_all() {
		std::list<Wrapper> return_list;
		boost::timed_mutex::scoped_try_lock lock(mutex_);
		if(lock.owns_lock() && list_.size()) {
			return_list = list_;
			list_.clear();
		}
		return return_list;
	}
private:
	boost::timed_mutex mutex_;
	std::list<Wrapper> list_;
};

class plmn_wrapper;
class sib_wrapper;
class umts_sib_18_wrapper;
class gsm_neighbor_inter_rat_wrapper;
class lte_sib_1_wrapper;
class lte_sib_3_wrapper;
class lte_sib_4_wrapper;
class lte_sib_5_wrapper;
class lte_sib_6_wrapper;
class lte_sib_7_wrapper;
class lte_sib_8_wrapper;

typedef group<beagle_api::BANDS> band_group_type;
typedef group<beagle_api::TECHNOLOGIES_AND_BANDS> technologies_and_band_group_type;
typedef group<beagle_api::cpich_type> neighbor_intra_type;
typedef group<beagle_api::umts_neighbor_inter> neighbor_inter_type;
typedef group<gsm_neighbor_inter_rat_wrapper> gsm_neighbor_inter_rat_type;
typedef group<plmn_wrapper> plmns_type;
typedef umts_sib_18_wrapper umts_sib_18_type;
typedef lte_sib_1_wrapper lte_sib_1_type;
typedef lte_sib_3_wrapper lte_sib_3_type;
typedef lte_sib_4_wrapper lte_sib_4_type;
typedef lte_sib_5_wrapper lte_sib_5_type;
typedef lte_sib_6_wrapper lte_sib_6_type;
typedef lte_sib_7_wrapper lte_sib_7_type;
typedef lte_sib_8_wrapper lte_sib_8_type;
typedef beagle_api::gsm_sector_info gsm_sector_info_wrapper;
typedef beagle_api::gsm_sweep_info gsm_sweep_info_wrapper;
typedef beagle_api::umts_sweep_info umts_sweep_info_wrapper;
typedef beagle_api::gps_info gps_info_wrapper;
typedef beagle_api::lte_sweep_info lte_sweep_info_wrapper;

class gsm_neighbor_inter_rat_wrapper
{
public:
	gsm_neighbor_inter_rat_wrapper(const beagle_api::umts_neighbor_inter_rat_gsm &t)
		: channel_(t.channel_)
		, bsic_(t.bsic_)
		, band_indicator_(t.band_indicator_)
		, rssi_(t.rssi_) {}

	gsm_neighbor_inter_rat_wrapper() {}

	beagle_api::channel_type channel_;
	std::string bsic_;
	beagle_api::BAND_INDICATOR band_indicator_;
	beagle_api::rssi_type rssi_;

};

class plmn_wrapper
{
public:
	plmn_wrapper() {}
	plmn_wrapper(const beagle_api::plmn &t)
		: mcc_(t.mcc_)
		, mnc_(t.mnc_) {}
	plmn_wrapper& operator= (plmn_wrapper &t) {
		mcc_ = t.mcc_;
		mnc_ = t.mnc_;
		return *this;
	}
	std::string mcc_;
	std::string mnc_;
};

class sib_wrapper
{
public:
	sib_wrapper(bool decoded = false)
		: decoded_(decoded) {}
	bool decoded_;
};

class umts_sib_18_wrapper : public sib_wrapper
{
public:
	umts_sib_18_wrapper()
		: sib_wrapper(false) {}
	umts_sib_18_wrapper(const beagle_api::umts_sib_18 &t)
		: sib_wrapper(t.decoded_) {
		if(decoded_) {
			plmns_ = t.plmns_;
		}
	}
	plmns_type plmns_;
};

class lte_sib_1_wrapper : public sib_wrapper
{
public:
	lte_sib_1_wrapper()
		: tac_(-1)
		, cid_(-1) {}
	lte_sib_1_wrapper(const beagle_api::lte_sib_1 &t)
		: sib_wrapper(t.decoded_) {
		if(decoded_) {
			plmns_ = t.plmns_;
			tac_ = t.tac_;
			cid_ = t.cid_;
		}
	}
	plmns_type plmns_;
	int16_t tac_;
	int32_t cid_;
};

class lte_sib_3_wrapper : public sib_wrapper
{
public:
	lte_sib_3_wrapper() {}
	lte_sib_3_wrapper(const beagle_api::lte_sib_3 &t)
		: sib_wrapper(t.decoded_) {}
};

class lte_sib_4_wrapper : public sib_wrapper
{
public:
	lte_sib_4_wrapper() {}
	lte_sib_4_wrapper(const beagle_api::lte_sib_4 &t)
		: sib_wrapper(t.decoded_) {}
};

class lte_sib_5_wrapper : public sib_wrapper
{
public:
	lte_sib_5_wrapper() {}
	lte_sib_5_wrapper(const beagle_api::lte_sib_5 &t)
		: sib_wrapper(t.decoded_) {}
};

class lte_sib_6_wrapper : public sib_wrapper
{
public:
	lte_sib_6_wrapper() {}
	lte_sib_6_wrapper(const beagle_api::lte_sib_6 &t)
		: sib_wrapper(t.decoded_) {}
};

class lte_sib_7_wrapper : public sib_wrapper
{
public:
	lte_sib_7_wrapper() {}
	lte_sib_7_wrapper(const beagle_api::lte_sib_7 &t)
		: sib_wrapper(t.decoded_) {}
};

class lte_sib_8_wrapper : public sib_wrapper
{
public:
	lte_sib_8_wrapper() {}
	lte_sib_8_wrapper(const beagle_api::lte_sib_8 &t)
		: sib_wrapper(t.decoded_) {}
};

class beagle_info_wrapper
{
public:
	beagle_info_wrapper()
		: beagle_id_(0)
		, state_(beagle_api::BEAGLE_ERROR)
		, rf_calibration_date_(0)
		, dds_clock_correction_calibration_date_(0)
		, device_speed_(beagle_api::UNKOWN_SPEED) {}

	beagle_info_wrapper(const beagle_api::beagle_info &info)
		: beagle_id_(info.beagle_id_)
		, state_(info.state_)
		, beagle_serial_(info.beagle_serial_)
		, valid_licenses_(info.valid_licenses_)
		, available_bands_in_hardware_(info.available_bands_in_hardware_)
		, rf_calibration_date_(info.rf_calibration_date_)
		, dds_clock_correction_calibration_date_(info.dds_clock_correction_calibration_date_)
		, device_speed_(info.device_speed_) {}

	beagle_api::beagle_id_type beagle_id_;
	beagle_api::BEAGLESTATE state_;
	std::string beagle_serial_;
	technologies_and_band_group_type valid_licenses_;
	band_group_type available_bands_in_hardware_;
	int64_t rf_calibration_date_;
	int64_t dds_clock_correction_calibration_date_;
	beagle_api::DEVICESPEED device_speed_;
};

class umts_sector_info_wrapper
{
public:
	umts_sector_info_wrapper(const beagle_api::umts_sector_info &info)
		: collection_round_(info.collection_round_)
		, carrier_freq_(info.carrier_freq_)
		, carrier_sl_(info.carrier_sl_)
		, uarfcn_(info.uarfcn_)
		, mcc_(info.mcc_)
		, mnc_(info.mnc_)
		, lac_(info.lac_)
		, cell_id_(info.cell_id_)
		, cpich_(info.cpich_)
		, ecio_(info.ecio_)
		, rscp_(info.rscp_)
		, band_(info.band_)
		, mcc_three_digits_(info.mcc_three_digits_)
		, mnc_three_digits_(info.mnc_three_digits_)
		, neighbor_intra_group_(info.neighbor_intra_group_)
		, neighbor_inter_group_(info.neighbor_inter_group_)
		, gsm_neighbor_inter_rat_group_(info.neighbor_inter_rat_gsm_group_)
		, sib_18_group_(info.sib_18_group_) {}

	umts_sector_info_wrapper() {}

	unsigned __int32 collection_round_;
	beagle_api::frequency_type carrier_freq_;
	double carrier_sl_;
	unsigned __int16 uarfcn_;
	unsigned __int16 mcc_;
	unsigned __int16 mnc_;
	unsigned __int16 lac_;
	uint32_t cell_id_;
	unsigned __int16 cpich_;
	double ecio_;
	double rscp_;
	beagle_api::BANDS band_;
	bool mcc_three_digits_;
	bool mnc_three_digits_;
	neighbor_intra_type neighbor_intra_group_;
	neighbor_inter_type neighbor_inter_group_;
	gsm_neighbor_inter_rat_type gsm_neighbor_inter_rat_group_;
	umts_sib_18_type sib_18_group_;
};

class lte_sector_info_wrapper
{
public:
	lte_sector_info_wrapper(const beagle_api::lte_sector_info &info)
		: collection_round_(info.collection_round_)
		, carrier_freq_(info.carrier_freq_)
		, carrier_sl_(info.carrier_sl_)
		, earfcn_(info.earfcn_)
		, lte_operating_band_(info.lte_operating_band_)
		, physical_cell_id_(info.physical_cell_id_)
		, rsrp_(info.rsrp_)
		, rsrq_(info.rsrq_)
		, rssi_(info.rssi_)
		, primary_sync_id_(info.primary_sync_id_)
		, primary_sync_quality_(info.primary_sync_quality_)
		, secondary_sync_id_(info.secondary_sync_id_)
		, secondary_sync_quality_(info.secondary_sync_quality_)
		, carrier_bandwidth_(info.carrier_bandwidth_)
		, antenna_ports_(info.antenna_ports_)
		, cyclic_prefix_length_(info.cyclic_prefix_length_)
		, system_frame_number_(info.system_frame_number_)
		, sib_1_(info.sib_1_)
		, sib_3_(info.sib_3_)
		, sib_4_(info.sib_4_)
		, sib_5_(info.sib_5_)
		, sib_6_(info.sib_6_)
		, sib_7_(info.sib_7_)
		, sib_8_(info.sib_8_)

	{}

	uint32_t collection_round_;
	beagle_api::frequency_type carrier_freq_;
	double carrier_sl_;
	uint16_t earfcn_;
	int32_t physical_cell_id_;
	beagle_api::TECHNOLOGIES_AND_BANDS lte_operating_band_;
	double rsrp_;
	double rsrq_;
	double rssi_;
	int16_t primary_sync_id_;
	double primary_sync_quality_;
	int16_t secondary_sync_id_;
	double secondary_sync_quality_;
	beagle_api::frequency_type carrier_bandwidth_;
	int8_t antenna_ports_;
	int8_t cyclic_prefix_length_;
	int32_t system_frame_number_;
	lte_sib_1_type sib_1_;
	lte_sib_3_type sib_3_;
	lte_sib_4_type sib_4_;
	lte_sib_5_type sib_5_;
	lte_sib_6_type sib_6_;
	lte_sib_7_type sib_7_;
	lte_sib_8_type sib_8_;
};


}