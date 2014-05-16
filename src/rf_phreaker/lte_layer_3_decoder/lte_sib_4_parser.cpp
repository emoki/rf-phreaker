#include "rf_phreaker/lte_layer_3_decoder/lte_sib_4_parser.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"
#include <iostream>

using namespace layer_3_information;

lte_sib_4_parser::lte_sib_4_parser(void)
{}


lte_sib_4_parser::~lte_sib_4_parser(void)
{}

void lte_sib_4_parser::parse_data(const SystemInformationBlockType4_t &data, lte_rrc_message_aggregate &message)
{
//	std::cout << "lte_sib4!";

	message.sib4_.decoded_ = true;

	if(data.csg_PhysCellIdRange) {
		message.sib4_.csg_physical_cellid_range_.start_ = data.csg_PhysCellIdRange->start;
		message.sib4_.csg_physical_cellid_range_.range_ = data.csg_PhysCellIdRange->range ? *data.csg_PhysCellIdRange->range : 1;
	}
	else {
		message.sib4_.csg_physical_cellid_range_.start_ = -1;
		message.sib4_.csg_physical_cellid_range_.range_ = -1;
	}
	
	if(data.intraFreqNeighCellList) {
		for(int i = 0; i < data.intraFreqNeighCellList->list.count; ++i) {
			neighbor_cell n_cell;
			n_cell.physical_cell_id_ = data.intraFreqNeighCellList->list.array[i]->physCellId;
			n_cell.q_offset_cell_ = data.intraFreqNeighCellList->list.array[i]->q_OffsetCell;
			message.sib4_.intra_freq_neighbor_cell_list_.push_back(n_cell);
		}
	}
	
	if(data.intraFreqBlackCellList) {
		for(int i = 0; i < data.intraFreqBlackCellList->list.count; ++i) {
			physical_cellid_range range;
			range.start_ = data.intraFreqBlackCellList->list.array[i]->start;
			range.range_ = data.intraFreqBlackCellList->list.array[i]->range ? *data.intraFreqBlackCellList->list.array[i]->range : 1;
			message.sib4_.intra_freq_black_cell_list_.push_back(range);
		}
	}
}

