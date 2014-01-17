#include "rf_phreaker/umts_layer_3_decoder/umts_sib_18_container.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType18.h"

using namespace layer_3_information;

umts_sib_18_container::umts_sib_18_container(void)
	: umts_system_information_container(SIB_Type_systemInformationBlockType18, umts_sib18)
{
}


umts_sib_18_container::~umts_sib_18_container(void)
{
}

void umts_sib_18_container::parse_data(umts_bcch_bch_message_aggregate &/*message*/)
{
    //SysInfoType18_t *data = (SysInfoType18_t*)decoded_structure();
}
