#include "rf_phreaker/lte_layer_3_decoder/lte_sib_3_parser.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"
#include <iostream>

using namespace layer_3_information;

/*
ReselectionThreshold
The IE  ReselectionThreshold is used to indicate an Rx level threshold for cell reselection. Actual value of threshold =
IE value * 2 [dB].

The IE  ReselectionThresholdQ is used to indicate a quality level threshold for cell reselection. Actual value of threshold
= IE value [dB].

The IE  CellReselectionPriority concerns the absolute priority of the concerned carrier frequency / set of frequencies
(GERAN) / bandclass(CDMA2000), as used by the cell reselection procedure.Corresponds with parameter "priority" in
TS 36.304[4].Value 0 means: lowest priority.The UE behaviour for the case the field is absent, if applicable, is
specified in TS 36.304[4].
*/

lte_sib_3_parser::lte_sib_3_parser(void) {}


lte_sib_3_parser::~lte_sib_3_parser(void) {}
void lte_sib_3_parser::parse_data(const SystemInformationBlockType3_t &data, lte_rrc_message_aggregate &message) {
	//	std::cout << "lte_sib3!";

	message.sib3_.decoded_ = true;

	message.sib3_.cell_reselection_serving_freq_info_.s_non_intra_search_ = data.cellReselectionServingFreqInfo.s_NonIntraSearch != nullptr
		? *data.cellReselectionServingFreqInfo.s_NonIntraSearch : -1;
	message.sib3_.cell_reselection_serving_freq_info_.cell_reselection_priority_ = data.cellReselectionServingFreqInfo.cellReselectionPriority;
	message.sib3_.cell_reselection_serving_freq_info_.threshold_serving_low_ = data.cellReselectionServingFreqInfo.threshServingLow;

	if(data.intraFreqCellReselectionInfo.s_IntraSearch != nullptr)
		message.sib3_.intra_freq_cell_reselection_info_.s_intra_search_ = *data.intraFreqCellReselectionInfo.s_IntraSearch;
	else
		message.sib3_.intra_freq_cell_reselection_info_.s_intra_search_.clear();;
	
	if(data.s_IntraSearch_v920 != nullptr) {
		message.sib3_.s_intra_search_v920_.p_ = data.s_IntraSearch_v920->s_IntraSearchP_r9;
		message.sib3_.s_intra_search_v920_.q_ = data.s_IntraSearch_v920->s_IntraSearchQ_r9;
	}
	else {
		message.sib3_.s_intra_search_v920_.p_.clear();
		message.sib3_.s_intra_search_v920_.q_ = -1;
	}

	if(data.s_NonIntraSearch_v920 != nullptr) {
		message.sib3_.s_non_intra_search_v920_.p_ = data.s_NonIntraSearch_v920->s_NonIntraSearchP_r9;
		message.sib3_.s_non_intra_search_v920_.q_ = data.s_NonIntraSearch_v920->s_NonIntraSearchQ_r9;
	}
	else {
		message.sib3_.s_non_intra_search_v920_.p_.clear();
		message.sib3_.s_non_intra_search_v920_.q_ = -1;
	}
	
	if(data.threshServingLowQ_r9 != nullptr)
		message.sib3_.threshold_serving_low_q_ = *data.threshServingLowQ_r9;
	else
		message.sib3_.threshold_serving_low_q_ = -1;
}

