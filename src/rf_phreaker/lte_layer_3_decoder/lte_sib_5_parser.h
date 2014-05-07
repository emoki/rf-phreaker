#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/lte_rrc_asn_library/SystemInformationBlockType5.h"

class lte_sib_5_parser
{
public:
	lte_sib_5_parser(void);
	~lte_sib_5_parser(void);

	void parse_data(const SystemInformationBlockType5_t &data, layer_3_information::lte_rrc_message_aggregate &message);

};

