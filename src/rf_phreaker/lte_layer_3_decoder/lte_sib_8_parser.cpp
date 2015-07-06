#include "rf_phreaker/lte_layer_3_decoder/lte_sib_8_parser.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"
#include <iostream>

using namespace layer_3_information;

lte_sib_8_parser::lte_sib_8_parser(void)
{}


lte_sib_8_parser::~lte_sib_8_parser(void)
{}

void lte_sib_8_parser::parse_data(const SystemInformationBlockType8_t &data, lte_rrc_message_aggregate &message)
{
//	std::cout << "lte_sib8!" << std::endl;

	message.sib8_.is_decoded_ = true;

	if(data.parametersHRPD) {
		if(data.parametersHRPD->cellReselectionParametersHRPD) {
			message.sib8_.parameters_hrpd_ = parse(data.parametersHRPD->cellReselectionParametersHRPD);
		}
	}

	if(data.cellReselectionParametersHRPD_v920) {
		add(message.sib8_.parameters_hrpd_.neighbor_cell_list_, data.cellReselectionParametersHRPD_v920->neighCellList_v920);
	}

	if(data.parameters1XRTT) {
		if(data.parameters1XRTT->cellReselectionParameters1XRTT) {
			message.sib8_.parameters_1xrtt_ = parse(data.parameters1XRTT->cellReselectionParameters1XRTT);
		}
	}

	if(data.cellReselectionParameters1XRTT_v920) {
		add(message.sib8_.parameters_1xrtt_.neighbor_cell_list_, data.cellReselectionParameters1XRTT_v920->neighCellList_v920);
		
	}
}

cell_reselection_parameters_cmda_2000 lte_sib_8_parser::parse(const CellReselectionParametersCDMA2000 *param)
{
	cell_reselection_parameters_cmda_2000 cell_reselection;

	auto &neigh_cell_list = param->neighCellList;
	for(int i = 0; i < neigh_cell_list.list.count; ++i) {
		neighbor_cell_cdma_2000 neigh_cell;
		neigh_cell.band_ = convert((BandclassCDMA2000)neigh_cell_list.list.array[i]->bandClass);

		auto &cells_per_freq_list = neigh_cell_list.list.array[i]->neighCellsPerFreqList.list;
		for(int i = 0; i < cells_per_freq_list.count; ++i) {
			neighbor_cells_per_band_class_cdma_2000 cells_per_band;
			cells_per_band.arfcn_value_cmda_2000_ = cells_per_freq_list.array[i]->arfcn;

			auto &cells = cells_per_freq_list.array[i]->physCellIdList.list;
			for(int i = 0; i < cells.count; ++i) {
				cells_per_band.physical_cell_ids_.push_back(*cells.array[i]);
			}

			neigh_cell.neighbor_cells_per_freq_list_.push_back(cells_per_band);
		}

		cell_reselection.neighbor_cell_list_.push_back(neigh_cell);
	}

	return cell_reselection;
}

band_class_cmda_2000 lte_sib_8_parser::convert(BandclassCDMA2000 bc)
{
	band_class_cmda_2000 tmp;

	switch(bc) {
	case BandclassCDMA2000_bc0:
		tmp = bc0;
		break;
	case BandclassCDMA2000_bc1:
		tmp = bc1;
		break;
	case BandclassCDMA2000_bc2:
		tmp = bc2;
		break;
	case BandclassCDMA2000_bc3:
		tmp = bc3;
		break;
	case BandclassCDMA2000_bc4:
		tmp = bc4;
		break;
	case BandclassCDMA2000_bc5:
		tmp = bc5;
		break;
	case BandclassCDMA2000_bc6:
		tmp = bc6;
		break;
	case BandclassCDMA2000_bc7:
		tmp = bc7;
		break;
	case BandclassCDMA2000_bc8:
		tmp = bc8;
		break;
	case BandclassCDMA2000_bc9:
		tmp = bc9;
		break;
	case BandclassCDMA2000_bc10:
		tmp = bc10;
		break;
	case BandclassCDMA2000_bc11:
		tmp = bc11;
		break;
	case BandclassCDMA2000_bc12:
		tmp = bc12;
		break;
	case BandclassCDMA2000_bc13:
		tmp = bc13;
		break;
	case BandclassCDMA2000_bc14:
		tmp = bc14;
		break;
	case BandclassCDMA2000_bc15:
		tmp = bc15;
		break;
	case BandclassCDMA2000_bc16:
		tmp = bc16;
		break;
	case BandclassCDMA2000_bc17:
		tmp = bc17;
		break;
	case BandclassCDMA2000_bc18_v9a0:
		tmp = bc18_v9a0;
		break;
	case BandclassCDMA2000_bc19_v9a0:
		tmp = bc19_v9a0;
		break;
	case BandclassCDMA2000_bc20_v9a0:
		tmp = bc20_v9a0;
		break;
	case BandclassCDMA2000_bc21_v9a0:
		tmp = bc21_v9a0;
		break;
	case BandclassCDMA2000_spare10:
		tmp = spare10;
		break;
	case BandclassCDMA2000_spare9:
		tmp = spare9;
		break;
	case BandclassCDMA2000_spare8:
		tmp = spare8;
		break;
	case BandclassCDMA2000_spare7:
		tmp = spare7;
		break;
	case BandclassCDMA2000_spare6:
		tmp = spare6;
		break;
	case BandclassCDMA2000_spare5:
		tmp = spare5;
		break;
	case BandclassCDMA2000_spare4:
		tmp = spare4;
		break;
	case BandclassCDMA2000_spare3:
		tmp = spare3;
		break;
	case BandclassCDMA2000_spare2:
		tmp = spare2;
		break;
	case BandclassCDMA2000_spare1:
	default:
		tmp = spare1;
		break;
	}

	return tmp;
}

void lte_sib_8_parser::add(std::vector<neighbor_cell_cdma_2000> &cell_list, const NeighCellListCDMA2000_v920 &new_cell_list)
{
	int i = 0;
	int j = 0;
	for(auto &neighbor_cell_cmda : cell_list) {
		for(auto &neighbor_cell_per_freq : neighbor_cell_cmda.neighbor_cells_per_freq_list_) {
			auto &phys_cell_list = new_cell_list.list.array[i]->neighCellsPerFreqList_v920.list.array[j]->physCellIdList_v920.list;
			for(int k = 0; k < phys_cell_list.count; ++k)
				neighbor_cell_per_freq.physical_cell_ids_.push_back(*phys_cell_list.array[k]);
			++j;
		}
		++i;
	}
}