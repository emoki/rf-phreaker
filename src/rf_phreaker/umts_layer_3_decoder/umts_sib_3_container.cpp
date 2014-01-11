#include "rf_phreaker/umts_layer_3_decoder/umts_sib_3_container.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType3.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"

using namespace layer_3_information;

umts_sib_3_container::umts_sib_3_container(void)
	: umts_system_information_container(SIB_Type_systemInformationBlockType3, umts_sib3)
{
}


umts_sib_3_container::~umts_sib_3_container(void)
{
}

void umts_sib_3_container::parse_data(umts_bcch_bch_message_aggregate &message)
{
	SysInfoType3_t *data = (SysInfoType3_t*)decoded_structure();
	message.cid_ = create_num_from_bit_stream(data->cellIdentity);
}

