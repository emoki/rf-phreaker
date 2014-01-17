#include "rf_phreaker/umts_layer_3_decoder/umts_sib_11_container.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType11.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"

using namespace layer_3_information;

umts_sib_11_container::umts_sib_11_container(void)
	: umts_system_information_container(SIB_Type_systemInformationBlockType11, umts_sib11)
{
}


umts_sib_11_container::~umts_sib_11_container(void)
{
}

void umts_sib_11_container::parse_data(umts_bcch_bch_message_aggregate &/*message*/)
{
//	SysInfoType11_t *data = (SysInfoType11_t*)decoded_structure();
}
