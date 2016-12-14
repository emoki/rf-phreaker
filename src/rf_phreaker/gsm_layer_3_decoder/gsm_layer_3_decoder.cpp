#include <fstream>
#include <iostream>
#include <string>
#include "rf_phreaker/gsm_layer_3_library/ed_lib.h"
#include "rf_phreaker/gsm_layer_3_library/bitencode.h"
#include "rf_phreaker/gsm_layer_3_library/ed_c_recog_RR.h"
#include "rf_phreaker/gsm_layer_3_library/RRPLENDownlink_RR.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_decoder.h"
#include "rf_phreaker/gsm_layer_3_library/gsm_bit_stream.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_utility.h"
#include "rf_phreaker/common/common_utility.h"

using namespace layer_3_information;

gsm_layer_3_decoder::gsm_layer_3_decoder()
	: debug_(false) {}

gsm_layer_3_decoder::~gsm_layer_3_decoder() {}

int32_t gsm_layer_3_decoder::decode_bcch_message(const uint8_t *raw_bits, uint32_t num_of_bytes, uint32_t unused_bits, layer_3_information::gsm_layer_3_message_aggregate &message)
{
	// See 3GPP spec 44.018 section 3.2.2 (Network side - System Information Broadcasting) to see when different sibs are scheduled.
	int32_t status = 0;
	try
	{
		message.raw_layer_3_.emplace_back(bit_stream(raw_bits, num_of_bytes, unused_bits));

		gsm_bit_stream bits(raw_bits, num_of_bytes, unused_bits);

		if(debug_) {
			static std::ofstream debug("gsm_bit_streams_" + rf_phreaker::static_timestamp::to_string() + ".txt", std::ios::app);
			debug << bits << std::endl;
		}

		TRRPLENDownlink_Data data;
		INIT_TRRPLENDownlink_Data(&data);
		SetDecode_RRPLENDownlink((char*)bits.bit_stream(), &data, bits.num_bits_in_bit_stream());
		switch(data.Type) {
		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_1_DN: {
			message.si_1_.is_decoded_ = true;
			message.si_1_.band_indicator_ = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_1_DN->Si1RestOctets.BAND_INDICATOR == 0 ? dcs_1800_was_used : pcs_1900_was_used;
		} break;
		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2_DN: {
			message.si_2_.is_decoded_ = true;
			auto cell_des = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_2_DN->BcchFrequencyList;
			gsm_layer_3_utility::decode_bcch_cell_channels(cell_des.CellDescription, message.si_2_.bcch_neighbors_);
			message.si_2_.gsm_ba_ind_ = cell_des.BAInd;
			message.si_2_.bcch_neighbors_has_extension_ = cell_des.ExtInd == 1;
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2BIS_DN: {
			message.si_2bis_.is_decoded_ = true;
			auto cell_des = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_2BIS_DN->ExtendedBcchFrequencyList;
			gsm_layer_3_utility::decode_bcch_cell_channels(cell_des.CellDescription, message.si_2bis_.extended_bcch_neighbors_);
			message.si_2bis_.gsm_ba_ind_ = cell_des.BAInd;
			message.si_2bis_.bcch_neighbors_has_extension_ = cell_des.ExtInd == 1;
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2TER_DN: {
			message.si_2ter_.is_decoded_ = true;
			auto cell_des = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_2TER_DN->ExtendedBcchFrequencyList;
			gsm_layer_3_utility::decode_bcch_cell_channels(cell_des.CellDescription, message.si_2ter_.extended_bcch_neighbors_);
			message.si_2ter_.gsm_ba_ind_ = cell_des.BAInd;
			message.si_2ter_.bcch_neighbors_multiband_reporting_ = cell_des.MultibandReporting;
			auto octets = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_2TER_DN->Si2terRestOctets;
			if(octets.SI2ter_COUNT_Present)
				message.si_2ter_.rest_octet_count_ = octets.SI2ter_COUNT;
			if(octets.SI2ter_INDEX_Present)
				message.si_2ter_.rest_octet_index_ = octets.SI2ter_INDEX;
			if(octets.UTRAN_FDD_Description_Present)
				gsm_layer_3_utility::decode_utran_neighbors(*octets.UTRAN_FDD_Description, message.si_2ter_.utran_neighbors_);
			if(octets.UTRAN_TDD_Description_Present)
				gsm_layer_3_utility::decode_utran_neighbors(*octets.UTRAN_FDD_Description, message.si_2ter_.utran_neighbors_);
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2QUATER_DN: {
			message.si_2quater_.is_decoded_ = true;
			auto octets = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN->Si2QuaterRestOctets;
			message.si_2quater_.rest_octet_count_ = octets.SI2quater_COUNT;
			message.si_2quater_.rest_octet_index_ = octets.SI2quater_INDEX;
			message.si_2quater_.gsm_ba_ind_ = octets.BA_IND;
			message.si_2quater_.p3g_ba_ind_ = octets.p3G_BA_IND;

			if(octets.p3G_Neighbour_Cell_Description_Present) {
				message.si_2quater_.utran_neighbor_cell_index_start_3g_ = octets.p3G_Neighbour_Cell_Description->Index_Start_3G_Present ? octets.p3G_Neighbour_Cell_Description->Index_Start_3G : 0;
				message.si_2quater_.utran_neighbor_cell_absolute_index_start_emr_ = octets.p3G_Neighbour_Cell_Description->Absolute_Index_Start_EMR_Present ? octets.p3G_Neighbour_Cell_Description->Absolute_Index_Start_EMR : 0;
				if(octets.p3G_Neighbour_Cell_Description->UTRAN_FDD_Description_Present)
					gsm_layer_3_utility::decode_utran_neighbors(*octets.p3G_Neighbour_Cell_Description->UTRAN_FDD_Description, message.si_2quater_.utran_neighbors_);
				if(octets.p3G_Neighbour_Cell_Description->UTRAN_TDD_Description_Present)
					gsm_layer_3_utility::decode_utran_neighbors(*octets.p3G_Neighbour_Cell_Description->UTRAN_TDD_Description, message.si_2quater_.utran_neighbors_);
			}
			if(octets.Priority_and_E_UTRAN_Parameters_Description_Present) {
				if(octets.Priority_and_E_UTRAN_Parameters_Description->E_UTRAN_Parameters_Description_Present) {
					gsm_layer_3_utility::decode_eutran_neighbors(*octets.Priority_and_E_UTRAN_Parameters_Description->E_UTRAN_Parameters_Description, message.si_2quater_.eutran_neighbors_);
				}
			}
			if(octets.Extended_EARFCNs_Description_Present) {
				auto ext = octets.Extended_EARFCNs_Description->EARFCN_extended;
				for(int i = 0; i < ext.items; ++i) {
					message.si_2quater_.extended_eutran_neighbors_.push_back(ext.data[i]);
				}
			}
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_3_DN: {
			message.si_3_.is_decoded_ = true;
			auto si3 = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_3_DN;
			std::string tmp;
			tmp.append(std::to_string((int)si3->LocationAreaId.MCC1).c_str());
			tmp.append(std::to_string((int)si3->LocationAreaId.MCC2).c_str());
			tmp.append(std::to_string((int)si3->LocationAreaId.MCC3).c_str());
			message.si_3_.plmn_.mcc_ = tmp;
			tmp.clear();
			tmp.append(std::to_string((int)si3->LocationAreaId.MNC1).c_str());
			tmp.append(std::to_string((int)si3->LocationAreaId.MNC2).c_str());
			if(si3->LocationAreaId.MNC3 != 0xf) tmp.append(std::to_string((int)si3->LocationAreaId.MNC3).c_str());
			message.si_3_.plmn_.mnc_ = tmp;
			message.si_3_.location_area_code_ = si3->LocationAreaId.LAC;
			message.si_3_.cell_id_ = si3->CellId;
			message.si_3_.cell_reselect_hysteresis_db_ = si3->CellSelectionParameters.CellReseHyst * 2;

			message.si_3_.bs_ag_blks_res_ = si3->ControlChannelDescription.BsAgBlksRes;

			auto octet = si3->Si3RestOctets;
			if(octet.CELL_RESELECT_OFFSET_Present)
				message.si_3_.selection_parameters_.cell_reselect_offset_db_ = octet.CELL_RESELECT_OFFSET * 2;
			if(octet.PENALTY_TIME_Present) {
				if(octet.PENALTY_TIME != 31) {
					message.si_3_.selection_parameters_.penalty_time_seconds_ = octet.PENALTY_TIME * 20 + 20;
					message.si_3_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = false;
				}
				else {
					message.si_3_.selection_parameters_.penalty_time_seconds_ = -1;
					message.si_3_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = true;
				}
			}
			if(octet.CBQ_Present)
				message.si_3_.selection_parameters_.cbq_ = octet.CBQ;
			if(octet.TEMPORARY_OFFSET_Present) {
				if(octet.TEMPORARY_OFFSET != 7) {
					message.si_3_.selection_parameters_.temporary_offset_db_ = octet.TEMPORARY_OFFSET * 10;
					message.si_3_.selection_parameters_.apply_infinity_offset_ = false;
				}
				else {
						message.si_3_.selection_parameters_.temporary_offset_db_ = -1;
						message.si_3_.selection_parameters_.apply_infinity_offset_ = true;
				}
			}
			message.si_3_.is_2ter_present_ = octet.System_Information_2ter_Present == 1;
			
			message.si_3_.is_2quater_present_ = octet.SI2quater_Indicator_Present == 1;

			message.mcc_ = message.si_3_.plmn_.mcc_;
			message.mnc_ = message.si_3_.plmn_.mnc_;
			message.lac_ = message.si_3_.location_area_code_;
			message.cid_ = message.si_3_.cell_id_;
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_4_DN: {
			message.si_4_.is_decoded_ = true;
			auto si4 = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_4_DN;

			std::string tmp;
			tmp.append(std::to_string((int)si4->LocationAreaId.MCC1).c_str());
			tmp.append(std::to_string((int)si4->LocationAreaId.MCC2).c_str());
			tmp.append(std::to_string((int)si4->LocationAreaId.MCC3).c_str());
			message.si_4_.plmn_.mcc_ = tmp;
			tmp.clear();
			tmp.append(std::to_string((int)si4->LocationAreaId.MNC1).c_str());
			tmp.append(std::to_string((int)si4->LocationAreaId.MNC2).c_str());
			if(si4->LocationAreaId.MNC3 != 0xf) tmp.append(std::to_string((int)si4->LocationAreaId.MNC3).c_str());
			message.si_4_.plmn_.mnc_ = tmp;
			message.si_4_.location_area_code_ = si4->LocationAreaId.LAC;

			message.si_4_.is_cbch_present_ = si4->CbchChannelDescription_Present != 0;
			
			message.si_4_.cell_reselect_hysteresis_db_ = si4->CellSelectionParameters.CellReseHyst * 2;
			
			auto octet = si4->Si4RestOctets;
			if(octet.CELL_RESELECT_OFFSET_Present)
				message.si_4_.selection_parameters_.cell_reselect_offset_db_ = octet.CELL_RESELECT_OFFSET * 2;
			if(octet.PENALTY_TIME_Present) {
				if(octet.PENALTY_TIME != 31) {
					message.si_4_.selection_parameters_.penalty_time_seconds_ = octet.PENALTY_TIME * 20 + 20;
					message.si_4_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = false;
				}
				else {
					message.si_4_.selection_parameters_.penalty_time_seconds_ = -1;
					message.si_4_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = true;
				}
			}
			if(octet.CBQ_Present)
				message.si_4_.selection_parameters_.cbq_ = octet.CBQ;
			if(octet.TEMPORARY_OFFSET_Present) {
				if(octet.TEMPORARY_OFFSET != 7) {
					message.si_4_.selection_parameters_.temporary_offset_db_ = octet.TEMPORARY_OFFSET * 10;
					message.si_4_.selection_parameters_.apply_infinity_offset_ = false;
				}
				else {
					message.si_4_.selection_parameters_.temporary_offset_db_ = -1;
					message.si_4_.selection_parameters_.apply_infinity_offset_ = true;
				}
			}
			if(octet.Cell_Identity_Present)
				message.si_4_.cell_id_ = octet.Cell_Identity;

			// Override previous value if present
			if(octet.MCC_Present)
				message.si_4_.plmn_.mcc_ = octet.MCC;

			// Override previous value if present
			if(octet.MNC_Present)
				message.si_4_.plmn_.mnc_ = octet.MNC;

			message.si_4_.have_additional_param_in_si7_si8_ = octet.Break_Indicator_Present != 0;
	
			message.mcc_ = message.si_4_.plmn_.mcc_;
			message.mnc_ = message.si_4_.plmn_.mnc_;
			message.lac_ = message.si_4_.location_area_code_;
			message.cid_ = message.si_4_.cell_id_;
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_7_DN: {
			message.si_7_.is_decoded_ = true;
			auto octet = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_7_DN->Si7RestOctets;

			if(octet.CELL_RESELECT_OFFSET_Present)
				message.si_7_.selection_parameters_.cell_reselect_offset_db_ = octet.CELL_RESELECT_OFFSET * 2;
			if(octet.PENALTY_TIME_Present) {
				if(octet.PENALTY_TIME != 31) {
					message.si_7_.selection_parameters_.penalty_time_seconds_ = octet.PENALTY_TIME * 20 + 20;
					message.si_7_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = false;
				}
				else {
					message.si_7_.selection_parameters_.penalty_time_seconds_ = -1;
					message.si_7_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = true;
				}
			}
			if(octet.CBQ_Present)
				message.si_7_.selection_parameters_.cbq_ = octet.CBQ;
			if(octet.TEMPORARY_OFFSET_Present) {
				if(octet.TEMPORARY_OFFSET != 7) {
					message.si_7_.selection_parameters_.temporary_offset_db_ = octet.TEMPORARY_OFFSET * 10;
					message.si_7_.selection_parameters_.apply_infinity_offset_ = false;
				}
				else {
					message.si_7_.selection_parameters_.temporary_offset_db_ = -1;
					message.si_7_.selection_parameters_.apply_infinity_offset_ = true;
				}
			}
			if(octet.Cell_Identity_Present) {
				message.si_7_.cell_id_ = octet.Cell_Identity;
				message.cid_ = message.si_7_.cell_id_;
			}
			if(octet.MCC_Present) {
				message.si_7_.plmn_.mcc_ = octet.MCC;
				message.mcc_ = message.si_7_.plmn_.mcc_;
			}
			if(octet.MNC_Present) {
				message.si_7_.plmn_.mnc_ = octet.MNC;
				message.mnc_ = message.si_7_.plmn_.mnc_;
			}
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_8_DN: {
			message.si_8_.is_decoded_ = true;
			auto octet = data.Data.fld_c_SYSTEM_INFORMATION_TYPE_8_DN->Si8RestOctets;

			if(octet.CELL_RESELECT_OFFSET_Present)
				message.si_8_.selection_parameters_.cell_reselect_offset_db_ = octet.CELL_RESELECT_OFFSET * 2;
			if(octet.PENALTY_TIME_Present) {
				if(octet.PENALTY_TIME != 31) {
					message.si_8_.selection_parameters_.penalty_time_seconds_ = octet.PENALTY_TIME * 20 + 20;
					message.si_8_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = false;
				}
				else {
					message.si_8_.selection_parameters_.penalty_time_seconds_ = -1;
					message.si_8_.selection_parameters_.subtract_reselect_cell_offset_ignore_temp_offset_ = true;
				}
			}
			if(octet.CBQ_Present)
				message.si_8_.selection_parameters_.cbq_ = octet.CBQ;
			if(octet.TEMPORARY_OFFSET_Present) {
				if(octet.TEMPORARY_OFFSET != 7) {
					message.si_8_.selection_parameters_.temporary_offset_db_ = octet.TEMPORARY_OFFSET * 10;
					message.si_8_.selection_parameters_.apply_infinity_offset_ = false;
				}
				else {
					message.si_8_.selection_parameters_.temporary_offset_db_ = -1;
					message.si_8_.selection_parameters_.apply_infinity_offset_ = true;
				}
			}
			if(octet.Cell_Identity_Present) {
				message.si_8_.cell_id_ = octet.Cell_Identity;
				message.cid_ = message.si_8_.cell_id_;
			}
			if(octet.MCC_Present) {
				message.si_8_.plmn_.mcc_ = octet.MCC;
				message.mcc_ = message.si_8_.plmn_.mcc_;
			}
			if(octet.MNC_Present) {
				message.si_8_.plmn_.mnc_ = octet.MNC;
				message.mnc_ = message.si_8_.plmn_.mnc_;
			}
		} break;

		case ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_23_DN:
			message.si_23_.is_decoded_ = true;
		break;

		default:
			{ data.Type; };
		}	
		FREE_TRRPLENDownlink_Data(&data);
	}
	catch(const std::exception &err)
	{
        std::cout << err.what();
		status = -1;
	}
	return status;
}

void gsm_layer_3_decoder::update_message_decode_list(layer_3_information::gsm_bcch_si_type message_t)
{
//	gsm_layer_3_container_->update_message_container_list(message_t);
}



	