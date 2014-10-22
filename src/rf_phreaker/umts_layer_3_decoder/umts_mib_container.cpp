#include "rf_phreaker/umts_layer_3_decoder/umts_mib_container.h"
#include "rf_phreaker/umts_rrc_asn_library/MasterInformationBlock.h"
#include "rf_phreaker/umts_rrc_asn_library/PLMN-Type.h"
#include "rf_phreaker/umts_rrc_asn_library/SIB-TypeExt.h"
#include "rf_phreaker/umts_rrc_asn_library/SIBSb-TypeAndTag.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"

using namespace layer_3_information;

umts_mib_container::umts_mib_container()
	: umts_system_information_container(SIB_Type_masterInformationBlock, umts_mib)
{
}


umts_mib_container::~umts_mib_container(void)
{
}

void umts_mib_container::parse_data(umts_bcch_bch_message_aggregate &message)
{
	mib_data_ = (MasterInformationBlock_t*)decoded_structure();

	look_for_plmn(message);

	look_for_sib_11(message);

	look_for_sib_11_bis(message);
}

void umts_mib_container::look_for_plmn(umts_bcch_bch_message_aggregate &message)
{
	// TODO - Where are multiple PLMNs?
	switch(mib_data_->plmn_Type.present)
	{
	case PLMN_Type_PR_gsm_MAP:
		message.mcc_ = create_mcc_type(mib_data_->plmn_Type.choice.gsm_MAP.plmn_Identity.mcc.list.array, mib_data_->plmn_Type.choice.gsm_MAP.plmn_Identity.mcc.list.count);
		message.mnc_ = create_mnc_type(mib_data_->plmn_Type.choice.gsm_MAP.plmn_Identity.mnc.list.array, mib_data_->plmn_Type.choice.gsm_MAP.plmn_Identity.mnc.list.count);
		break;

	case PLMN_Type_PR_ansi_41:
		//message.mcc_ = create_mcc_type(mib_data_->plmn_Type.choice.ansi_41., mib_data_->plmn_Type.choice.ansi_41);
		//message.mnc_ = create_mnc_type(mib_data_->plmn_Type.choice.ansi_41, mib_data_->plmn_Type.choice.ansi_41);
		break;

	case PLMN_Type_PR_gsm_MAP_and_ANSI_41:
		message.mcc_ = create_mcc_type(mib_data_->plmn_Type.choice.gsm_MAP_and_ANSI_41.plmn_Identity.mcc.list.array, mib_data_->plmn_Type.choice.gsm_MAP_and_ANSI_41.plmn_Identity.mcc.list.count);
		message.mnc_ = create_mnc_type(mib_data_->plmn_Type.choice.gsm_MAP_and_ANSI_41.plmn_Identity.mnc.list.array, mib_data_->plmn_Type.choice.gsm_MAP_and_ANSI_41.plmn_Identity.mnc.list.count);
	break;

	case PLMN_Type_PR_spare:
		break;

	case PLMN_Type_PR_NOTHING:	/* No components present */
		break;

	default:
		throw std::runtime_error("Hit default statement when decoding umts master information block.\n");
	};
}

void umts_mib_container::look_for_sib_11(umts_bcch_bch_message_aggregate &message)
{
	//SIBSb_ReferenceList_t *list = &mib_data_->sibSb_ReferenceList;

	//for(int i = 0; i < list->list.count; i++)
	//{
	//	if(list->list.array[0]->sibSb_Type.present == SIBSb_TypeAndTag_PR_sysInfoType11)
	//	{
	//		i = list->list.count;
	//	}
	//}

	//look_in_extended_sib_list();
}

void umts_mib_container::look_for_sib_11_bis(umts_bcch_bch_message_aggregate &message)
{
//	look_in_extended_sib_list();
}

void umts_mib_container::look_in_extended_sib_list()
{
	//if(mib_data_->v690NonCriticalExtensions && mib_data_->v690NonCriticalExtensions->v6b0NonCriticalExtensions)
	//{
	//	ExtSIBTypeInfoSchedulingInfo_List *list = mib_data_->v690NonCriticalExtensions->v6b0NonCriticalExtensions->masterInformationBlock_v6b0ext.extSIBTypeInfoSchedulingInfo_List;

	//	for(int i = 0; i < list->list.count; i++)
	//	{
	//		if(list->list.array[i]->extensionSIB_Type.present == SIB_TypeExt_PR_systemInfoType11bis)
	//		{
	//			i = list->list.count;
	//		}
	//	}
	//}
}

