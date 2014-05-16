#pragma once

#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/lte_rrc_asn_library/SystemInformationBlockType7.h"
#include "rf_phreaker/lte_rrc_asn_library/CarrierFreqsGERAN.h"

class lte_sib_7_parser
{
public:
	lte_sib_7_parser(void);
	~lte_sib_7_parser(void);

	void parse_data(const SystemInformationBlockType7_t &data, layer_3_information::lte_rrc_message_aggregate &message);

private:
	std::vector<int> convert_explicit(const ExplicitListOfARFCNs_t &arfcns, int start);
	std::vector<int> convert_equally_spaced(long arfcn_Spacing, long numberOfFollowingARFCNs, int start);
	std::vector<int> convert_variable_bitmap(const OCTET_STRING_t &octets, int start);
};

