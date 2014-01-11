#include "rf_phreaker/umts_layer_3_decoder/umts_sib_1_container.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType1.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"

using namespace layer_3_information;


umts_sib_1_container::umts_sib_1_container(void)
	: umts_system_information_container(SIB_Type_systemInformationBlockType1, umts_sib1)

{
}


umts_sib_1_container::~umts_sib_1_container(void)
{
}

void umts_sib_1_container::parse_data(umts_bcch_bch_message_aggregate &message)
{
	SysInfoType1_t *data = (SysInfoType1_t*)decoded_structure();
	message.lac_ = create_lac(data->cn_CommonGSM_MAP_NAS_SysInfo);
}

