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
								sib_descriptons_.push_back("Nothing");
								break;/* No components present */
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib2:
								message.sib2_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType2");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib3:
								lte_sib_3_parser_.parse_data(sib_list.array[i]->choice.sib3, message);
								sib_descriptons_.push_back("SystemInformationBlockType3");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib4:
								lte_sib_4_parser_.parse_data(sib_list.array[i]->choice.sib4, message);
								sib_descriptons_.push_back("SystemInformationBlockType4");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib5:
								lte_sib_5_parser_.parse_data(sib_list.array[i]->choice.sib5, message);
								sib_descriptons_.push_back("SystemInformationBlockType5");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib6:
								lte_sib_6_parser_.parse_data(sib_list.array[i]->choice.sib6, message);
								sib_descriptons_.push_back("SystemInformationBlockType6");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib7:
								lte_sib_7_parser_.parse_data(sib_list.array[i]->choice.sib7, message);
								sib_descriptons_.push_back("SystemInformationBlockType7");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib8:
								lte_sib_8_parser_.parse_data(sib_list.array[i]->choice.sib8, message);
								sib_descriptons_.push_back("SystemInformationBlockType8");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib9:
								message.sib9_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType9");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib10:
								message.sib10_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType10");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib11:
								message.sib11_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType11");
								break;
							/* Extensions may appear below */
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib12_v920:
								message.sib12_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType12_v920");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib13_v920:
								message.sib13_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType13_v920");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib14_v1130:
								message.sib14_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType14_v1130");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib15_v1130:
								message.sib15_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType15_v1130");
								break;
							case SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib16_v1130:
								message.sib16_.is_decoded_ = true;
								sib_descriptons_.push_back("SystemInformationBlockType16_v1130");
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
					sib_descriptons_.push_back("SystemInformationBlockType1");
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