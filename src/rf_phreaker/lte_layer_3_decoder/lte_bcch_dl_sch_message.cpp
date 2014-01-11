#include "rf_phreaker/lte_layer_3_decoder/lte_bcch_dl_sch_message.h"
#include "rf_phreaker/lte_rrc_asn_library/BCCH-DL-SCH-Message.h"
#include "rf_phreaker/lte_rrc_asn_library/BCCH-DL-SCH-MessageType.h"

using namespace layer_3_information;

lte_bcch_dl_sch_message::lte_bcch_dl_sch_message(void)
	: per_decoder_interface(lte_bcch_sch)
{
}


lte_bcch_dl_sch_message::~lte_bcch_dl_sch_message(void)
{
}

void lte_bcch_dl_sch_message::parse_data(lte_rrc_message_aggregate &message)
{
	auto dl_sch_data = (BCCH_DL_SCH_Message_t*)decoded_structure();

	switch(dl_sch_data->message.present)
	{
	case BCCH_DL_SCH_MessageType_PR_NOTHING:
		/* No components present */
		break;	
	case BCCH_DL_SCH_MessageType_PR_c1:
		{
			auto internal_data = dl_sch_data->message.choice.c1;
			switch(internal_data.present)
			{
				case BCCH_DL_SCH_MessageType__c1_PR_NOTHING:
				/* No components present */
					break;
				case BCCH_DL_SCH_MessageType__c1_PR_systemInformation:
					break;
				case BCCH_DL_SCH_MessageType__c1_PR_systemInformationBlockType1:
					lte_sib_1_parser_.parse_data(internal_data.choice.systemInformationBlockType1, message);
					break;
			}
		}
		break;
	case BCCH_DL_SCH_MessageType_PR_messageClassExtension:
		// do nothing
		break;
	default:;
	}

}
