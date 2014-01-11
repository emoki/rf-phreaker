#include "rf_phreaker/lte_layer_3_decoder/lte_sib_1_parser.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"

using namespace layer_3_information;

lte_sib_1_parser::lte_sib_1_parser(void)
{
}


lte_sib_1_parser::~lte_sib_1_parser(void)
{
}

void lte_sib_1_parser::parse_data(const SystemInformationBlockType1_t &data, lte_rrc_message_aggregate &message)
{
	auto plmn_list = data.cellAccessRelatedInfo.plmn_IdentityList.list;
	for(int i = 0; i < plmn_list.count; ++i)
	{	
		//plmn_list.array[i]->cellReservedForOperatorUse - Perhaps not pertinent for our purposes.
		message.mcc_ = create_mcc_type(plmn_list.array[i]->plmn_Identity.mcc->list.array, plmn_list.array[i]->plmn_Identity.mcc->list.count);
		message.mnc_ = create_mnc_type(plmn_list.array[i]->plmn_Identity.mnc.list.array, plmn_list.array[i]->plmn_Identity.mnc.list.count);

		// TODO - implement multiple plmn instead of using this break statement to only capture first plmn.
		break;
	}

	message.lac_ = create_num_from_bit_stream(data.cellAccessRelatedInfo.trackingAreaCode);

	message.cid_ = create_cid(data.cellAccessRelatedInfo.cellIdentity);
}

