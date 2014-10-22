#pragma once

#include "rf_phreaker/umts_rrc_asn_library/MasterInformationBlock.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_system_information_container.h"

class umts_mib_container : public umts_system_information_container
{
public:
	umts_mib_container(void);

	~umts_mib_container(void);

	void parse_data(layer_3_information::umts_bcch_bch_message_aggregate &message);

private:
	void look_for_plmn(layer_3_information::umts_bcch_bch_message_aggregate &message);

	void look_for_sib_11(layer_3_information::umts_bcch_bch_message_aggregate &message);

	void look_for_sib_11_bis(layer_3_information::umts_bcch_bch_message_aggregate &message);

	void look_in_extended_sib_list();

	MasterInformationBlock_t *mib_data_;
};

