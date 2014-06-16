#include "rf_phreaker/lte_layer_3_decoder/lte_sib_5_parser.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"
#include <iostream>

using namespace layer_3_information;

lte_sib_5_parser::lte_sib_5_parser(void)
{}


lte_sib_5_parser::~lte_sib_5_parser(void)
{}

void lte_sib_5_parser::parse_data(const SystemInformationBlockType5_t &data, lte_rrc_message_aggregate &message)
{
//	std::cout << "lte_sib5!";

	message.sib5_.decoded_ = true;

	auto &inter_list = data.interFreqCarrierFreqList.list;

	for(int i = 0; i < inter_list.count; ++i) {
		inter_freq_carrier_freq_info inter_freq;
		inter_freq.downlink_arfcn_value_eutra_ = inter_list.array[i]->dl_CarrierFreq;

		inter_freq.q_rx_lev_min_ = inter_list.array[i]->q_RxLevMin;

		inter_freq.q_offset_cell_ = inter_list.array[i]->q_OffsetFreq ? *inter_list.array[i]->q_OffsetFreq : 0;

		switch(inter_list.array[i]->allowedMeasBandwidth) {
		case AllowedMeasBandwidth_mbw6:
			inter_freq.allowed_measurement_bandwidth_ = 6;
			break;
		case AllowedMeasBandwidth_mbw15:
			inter_freq.allowed_measurement_bandwidth_ = 15;
			break;
		case AllowedMeasBandwidth_mbw25:
			inter_freq.allowed_measurement_bandwidth_ = 25;
			break;
		case AllowedMeasBandwidth_mbw50:
			inter_freq.allowed_measurement_bandwidth_ = 50;
			break;
		case AllowedMeasBandwidth_mbw75:
			inter_freq.allowed_measurement_bandwidth_ = 75;
			break;
		case AllowedMeasBandwidth_mbw100:
			inter_freq.allowed_measurement_bandwidth_ = 100;
			break;
		default:
			inter_freq.allowed_measurement_bandwidth_ = -1;		
		}
		
		inter_freq.presence_antenna_port_1_ = inter_list.array[i]->presenceAntennaPort1 != 0;

		if(inter_list.array[i]->interFreqNeighCellList) {
			auto inter_cell = inter_list.array[i]->interFreqNeighCellList->list;
			for(int i = 0; i < inter_cell.count; ++i) {
				neighbor_cell cell;
				cell.physical_cell_id_ = inter_cell.array[i]->physCellId;
				cell.q_offset_cell_ = inter_cell.array[i]->q_OffsetCell;
				inter_freq.inter_freq_neighbor_cell_list_.push_back(cell);
			}
		}

		if(inter_list.array[i]->interFreqBlackCellList) {
			auto inter_black = inter_list.array[i]->interFreqBlackCellList->list;
			for(int i = 0; i < inter_black.count; ++i) {
				physical_cellid_range range;
				range.start_ = inter_black.array[i]->start;
				range.range_ = inter_black.array[i]->range ? *inter_black.array[i]->range : 1;
				inter_freq.inter_freq_black_cell_list_.push_back(range);
			}
		}

		message.sib5_.inter_freq_carrier_info_list_.push_back(inter_freq);
	}
}

