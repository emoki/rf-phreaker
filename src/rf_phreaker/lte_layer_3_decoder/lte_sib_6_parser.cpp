#include "rf_phreaker/lte_layer_3_decoder/lte_sib_6_parser.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"
#include <iostream>

using namespace layer_3_information;

lte_sib_6_parser::lte_sib_6_parser(void)
{}


lte_sib_6_parser::~lte_sib_6_parser(void)
{}

void lte_sib_6_parser::parse_data(const SystemInformationBlockType6_t &data, lte_rrc_message_aggregate &message)
{
//	std::cout << "lte_sib6!" << std::endl;

	message.sib6_.is_decoded_ = true;

	if(data.carrierFreqListUTRA_FDD) {
		auto &fdd = data.carrierFreqListUTRA_FDD->list;
		for(int i = 0; i < fdd.count; ++i) {
			carrier_freq_utra utra;
			utra.arfcn_value_utra_ = fdd.array[i]->carrierFreq;

			utra.cell_reselection_priority_ = fdd.array[i]->cellReselectionPriority != nullptr ? *fdd.array[i]->cellReselectionPriority : -1;
			utra.threshold_x_high_ = fdd.array[i]->threshX_High;
			utra.threshold_x_low_ = fdd.array[i]->threshX_Low;
			if(fdd.array[i]->threshX_Q_r9) {
				utra.threshold_x_high_q_r9_ = fdd.array[i]->threshX_Q_r9->threshX_HighQ_r9;
				utra.threshold_x_low_q_r9_ = fdd.array[i]->threshX_Q_r9->threshX_LowQ_r9;
			}
			else {
				utra.threshold_x_high_q_r9_ = -1;
				utra.threshold_x_low_q_r9_ = -1;
			}
			message.sib6_.carrier_freq_list_utra_fdd_.push_back(utra);
		}
	}

	if(data.carrierFreqListUTRA_TDD) {
		auto &tdd = data.carrierFreqListUTRA_TDD->list;
		for(int i = 0; i < tdd.count; ++i) {
			carrier_freq_utra utra;
			utra.arfcn_value_utra_ = tdd.array[i]->carrierFreq;
			utra.cell_reselection_priority_ = tdd.array[i]->cellReselectionPriority != nullptr ? *tdd.array[i]->cellReselectionPriority : -1;
			utra.threshold_x_high_ = tdd.array[i]->threshX_High;
			utra.threshold_x_low_ = tdd.array[i]->threshX_Low;
			utra.threshold_x_high_q_r9_ = -1;
			utra.threshold_x_low_q_r9_ = -1;
			message.sib6_.carrier_freq_list_utra_tdd_.push_back(utra);
		}
	}
}

