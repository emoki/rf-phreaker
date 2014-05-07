#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/lte_rrc_asn_library/SystemInformationBlockType4.h"

class lte_sib_4_parser
{
public:
	lte_sib_4_parser(void);
	~lte_sib_4_parser(void);

	void parse_data(const SystemInformationBlockType4_t &data, layer_3_information::lte_rrc_message_aggregate &message);

};

