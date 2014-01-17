#include "rf_phreaker/umts_layer_3_decoder/umts_sib_11_bis_container.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType11bis.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"

using namespace layer_3_information;

umts_sib_11_bis_container::umts_sib_11_bis_container(void)
	: umts_system_information_container(SIB_Type_systemInformationBlockType11, umts_sib11_bis)
{
}


umts_sib_11_bis_container::~umts_sib_11_bis_container(void)
{
}

void umts_sib_11_bis_container::parse_data(umts_bcch_bch_message_aggregate &/*message*/)
{
    //SysInfoType11bis_t *data = (SysInfoType11bis_t*)decoded_structure();
}
