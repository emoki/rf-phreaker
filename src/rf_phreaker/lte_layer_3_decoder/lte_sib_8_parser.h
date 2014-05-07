#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/lte_rrc_asn_library/SystemInformationBlockType8.h"

class lte_sib_8_parser
{
public:
	lte_sib_8_parser(void);
	~lte_sib_8_parser(void);

	void parse_data(const SystemInformationBlockType8_t &data, layer_3_information::lte_rrc_message_aggregate &message);

private:
	layer_3_information::band_class_cmda_2000 convert(BandclassCDMA2000 bc);

	layer_3_information::cell_reselection_parameters_cmda_2000 parse(const CellReselectionParametersCDMA2000 *param);

	void add(std::vector<layer_3_information::neighbor_cell_cdma_2000> &cell_list, const NeighCellListCDMA2000_v920 &new_cell_list);
};

