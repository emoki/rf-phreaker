#include "rf_phreaker/umts_layer_3_decoder/umts_sib_4_container.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType4.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"

using namespace layer_3_information;

umts_sib_4_container::umts_sib_4_container(void)
	: umts_system_information_container(SIB_Type_systemInformationBlockType4, umts_sib4)
{
}


umts_sib_4_container::~umts_sib_4_container(void)
{
}

void umts_sib_4_container::parse_data(umts_bcch_bch_message_aggregate &message)
{
	SysInfoType4_t *data = (SysInfoType4_t*)decoded_structure();
	message.sib4_.is_decoded_ = true;
	message.sib4_.cid_ = create_num_from_bit_stream(data->cellIdentity);
	message.cid_ = message.sib4_.cid_;
}

