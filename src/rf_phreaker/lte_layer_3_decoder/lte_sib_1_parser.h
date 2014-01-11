#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/lte_rrc_asn_library/SystemInformationBlockType1.h"

class lte_sib_1_parser
{
public:
	lte_sib_1_parser(void);
	~lte_sib_1_parser(void);

	void parse_data(const SystemInformationBlockType1_t &data, layer_3_information::lte_rrc_message_aggregate &message);

};

