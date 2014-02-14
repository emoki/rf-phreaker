#pragma once

#include <stdint.h>

#include "rf_phreaker/common/common_types.h"

namespace rf_phreaker {

	struct gps
	{
		scanner_serial_type scanner_id_;
		bool lock_;
		int64_t coordinated_universal_time_;  
		int32_t visible_satelites_;
		int32_t tracking_satelites_;
		double latitude_;
		double longitude_;
		int32_t speed_;
		int64_t raw_status_;
	};


	struct basic_data
	{
		//scanner_serial_type scanner_id_;
		int64_t collection_round_;
		frequency_type carrier_frequency_;
		bandwidth_type carrier_bandwidth_;
		double carrier_signal_level_;
		int64_t time_;
		int32_t status_flags_;
	};

	/**
	Encapsulates a PLMN.
	*/
	struct plmn
	{
		char mcc_[4];
		char mnc_[4];
	};

	/**
	Contains multiple PLMN.
	*/
	struct plmn_group
	{
		int32_t size_; 
		plmn *elements_;
	};

	struct sys_info_base
	{
		bool decoded_;
	};

	struct umts_mib : public sys_info_base
	{
		plmn_group plmns_;
	};
	
	struct umts_sib_1 : public sys_info_base
	{
		int32_t lac_;
	};
	
	struct umts_sib_3 : public sys_info_base
	{
		int32_t cid_;
	};
	
	struct umts_sib_4 : public sys_info_base
	{
		int32_t cid_;
	};
	
	/**
	Used within GSM Inter Frequency RAT structure.  Helps determine band when UARFCN is ambiguous.
	*/
	enum band_indicator
	{
		dcs_1800_was_used = 0,
		pcs_1900_was_used = 1,
	};

	struct neighbor_intra_group
	{
		int32_t size_;
		int32_t *elements_;  ///CPICH
	};
	
	/**
	Encapsulates inter frequency neighbor decoded from SIB 11/SIB 11bis.
	*/
	struct neighbor_inter
	{
		// UARFCN
		int32_t channel_;
		// Scrambling code
		int32_t cpich_;
	};

	struct neighbor_inter_group
	{
		int32_t size_;
		neighbor_inter *elements_;
	};

	/**
	Encapsulates inter RAT frequency neighbor.
	*/
	struct gsm_neighbor_inter_rat
	{
		int32_t channel_;
		char bsic_[3];
		band_indicator band_indicator_;
		int32_t rssi_;
	};
	
	struct gsm_neighbor_inter_rat_group
	{
		int32_t size_;
		gsm_neighbor_inter_rat *elements_;
	};

	struct umts_sib_11 : public sys_info_base
	{
		neighbor_intra_group intra_neighbors_;
		neighbor_inter_group inter_neighbors_;
		gsm_neighbor_inter_rat_group gsm_neighbors_;
	};

	struct umts_data : public basic_data
	{
		int32_t uarfcn_;
		operating_band operating_band_;
		int32_t cpich_;
		double ecio_;
		double rscp_;
		umts_mib mib_;
		umts_sib_1 sib_1_;
		umts_sib_3 sib_3_;
		umts_sib_4 sib_4_;
		umts_sib_11 sib_11_;
	};

	struct lte_sib_1 : public sys_info_base
	{ 
		/// The list of PLMNS decoded within SIB1.
		plmn_group plmns_;

		/// Tracking Area Code.
		int32_t tac_;

		/// Cell ID
		int32_t cid_;
	};

	struct lte_data : public basic_data
	{
		int32_t earfcn_;
		operating_band operating_band_;
		int32_t physical_cell_id_;
		double rsrp_;
		double rsrq_;
		double rssi_;
		int32_t psch_id_;
		double psch_quality_;
		int32_t ssch_id_;
		double ssch_quality_;
		double rs_quality_;
		int cyclic_prefix_;
		int num_antenna_ports_;
		int32_t frame_number_;
		lte_sib_1 sib_1_;
	};

}