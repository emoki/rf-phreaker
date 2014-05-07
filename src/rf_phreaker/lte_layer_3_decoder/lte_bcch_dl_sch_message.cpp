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
			auto &internal_data = dl_sch_data->message.choice.c1;
			switch(internal_data.present) {
				case BCCH_DL_SCH_MessageType__c1_PR_NOTHING:
					/* No components present */
					break;
				case BCCH_DL_SCH_MessageType__c1_PR_systemInformation:
				{
					auto &crit_ex = internal_data.choice.systemInformation.criticalExtensions;
					switch(crit_ex.present) {
					case SystemInformation__criticalExtensions_PR_NOTHING:
						break;
					case SystemInformation__criticalExtensions_PR_systemInformation_r8:
					{
						auto &sib_list = crit_ex.choice.systemInformation_r8.sib_TypeAndInfo.list;
						for(int i = 0; i < sib_list.count; ++i) {
							switch(sib_list.array[i]->present) {
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_NOTHING:
								break;/* No components present */
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib2:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib3:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib4:
								lte_sib_4_parser_.parse_data(sib_list.array[i]->choice.sib4, message);
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib5:
								lte_sib_5_parser_.parse_data(sib_list.array[i]->choice.sib5, message);
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib6:
								lte_sib_6_parser_.parse_data(sib_list.array[i]->choice.sib6, message);
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib7:
								lte_sib_7_parser_.parse_data(sib_list.array[i]->choice.sib7, message);
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib8:
								lte_sib_8_parser_.parse_data(sib_list.array[i]->choice.sib8, message);
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib9:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib10:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib11:
								break;
							/* Extensions may appear below */
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib12_v920:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib13_v920:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib14_v1130:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib15_v1130:
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib16_v1130:
								break;
							default:
								;
							}

						}
					}	
						break;
					case SystemInformation__criticalExtensions_PR_criticalExtensionsFuture:
						;// Not supported.
						break;
					default:
						;
					
					}
				}
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
