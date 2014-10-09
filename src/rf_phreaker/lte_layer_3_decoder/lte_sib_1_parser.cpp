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
//	std::cout << "lte_sib1!";

	message.sib1_.decoded_ = true;

	auto &plmn_list = data.cellAccessRelatedInfo.plmn_IdentityList.list;
	for(int i = 0; i < plmn_list.count; ++i) {
		//plmn_list.array[i]->cellReservedForOperatorUse - Perhaps not pertinent for our purposes.

		// In the case of a malformed bit stream the mcc and perhaps other items can be NULL.  If it null
		if(plmn_list.array[i]->plmn_Identity.mcc == nullptr)
			continue;

		plmn p;
		p.mcc_ = create_mcc_type(plmn_list.array[i]->plmn_Identity.mcc->list.array, plmn_list.array[i]->plmn_Identity.mcc->list.count);
		p.mnc_ = create_mnc_type(plmn_list.array[i]->plmn_Identity.mnc.list.array, plmn_list.array[i]->plmn_Identity.mnc.list.count);
		message.sib1_.multiple_plmn_.push_back(p);
	}

	if(message.sib1_.multiple_plmn_.size())
	{
		message.mcc_ = message.sib1_.multiple_plmn_[0].mcc_;
		message.mnc_ = message.sib1_.multiple_plmn_[0].mnc_;
	}

	message.sib1_.tracking_area_code_ = create_num_from_bit_stream(data.cellAccessRelatedInfo.trackingAreaCode);
	message.lac_ = create_num_from_bit_stream(data.cellAccessRelatedInfo.trackingAreaCode);

	message.sib1_.cell_id_ = create_cid(data.cellAccessRelatedInfo.cellIdentity);
	message.cid_ = create_cid(data.cellAccessRelatedInfo.cellIdentity);

	auto &scheduling_list = data.schedulingInfoList.list;
	for(int i = 0; i < scheduling_list.count; ++i) {
		scheduling_info info;

		switch(scheduling_list.array[i]->si_Periodicity) {
		case SchedulingInfo__si_Periodicity_rf8:
			info.periodicity_in_frames_ = 8;
			break;
		case SchedulingInfo__si_Periodicity_rf16:
			info.periodicity_in_frames_ = 16;
			break;
		case SchedulingInfo__si_Periodicity_rf32:
			info.periodicity_in_frames_ = 32;
			break;
		case SchedulingInfo__si_Periodicity_rf64:
			info.periodicity_in_frames_ = 64;
			break;
		case SchedulingInfo__si_Periodicity_rf128:
			info.periodicity_in_frames_ = 128;
			break;
		case SchedulingInfo__si_Periodicity_rf256:
			info.periodicity_in_frames_ = 256;
			break;
		case SchedulingInfo__si_Periodicity_rf512:
			info.periodicity_in_frames_ = 512;
			break;
		default:
			info.periodicity_in_frames_ = -1;
		}
		
		auto &sibs = scheduling_list.array[i]->sib_MappingInfo.list;
		for(int i = 0; i < sibs.count; ++i) 
			info.sib_mapping_info_.push_back(convert(*sibs.array[i]));
		
		message.sib1_.scheduling_info_list_.push_back(info);
	}
	
	message.sib1_.si_window_length_ms_ = convert_si_window_length(data.si_WindowLength);
}
	
lte_sib_type lte_sib_1_parser::convert(SIB_Type_t sib)
{
	switch((SIB_Type)sib) {
	case SIB_Type_sibType3:
		return (sib_3);
		break;
	case SIB_Type_sibType4:
		return (sib_4);
		break;
	case SIB_Type_sibType5:
		return (sib_5);
		break;
	case SIB_Type_sibType6:
		return (sib_6);
		break;
	case SIB_Type_sibType7:
		return (sib_7);
		break;
	case SIB_Type_sibType8:
		return (sib_8);
		break;
	case SIB_Type_sibType9:
		return (sib_9);
		break;
	case SIB_Type_sibType10:
		return (sib_10);
		break;
	case SIB_Type_sibType11:
		return (sib_11);
		break;
	case SIB_Type_sibType12_v920:
		return (sib_12_v920);
		break;
	case SIB_Type_sibType13_v920:
		return (sib_13_v920);
		break;
	case SIB_Type_sibType14_v1130:
		return (sib_14_v1130);
		break;
	case SIB_Type_sibType15_v1130:
		return (sib_15_v1130);
		break;
	case SIB_Type_sibType16_v1130:
		return (sib_16_v1130);
		break;
	case SIB_Type_spare2:
		return (spare_2);
		break;
	case SIB_Type_spare1:
	default:
		return (spare_1);
	}
}

int lte_sib_1_parser::convert_si_window_length(long window_length) {
	long length = 0;
	switch(window_length) {
	case SystemInformationBlockType1__si_WindowLength_ms1:
		length = 1;
		break;
	case SystemInformationBlockType1__si_WindowLength_ms2:
		length = 2;
		break;
	case SystemInformationBlockType1__si_WindowLength_ms5:
		length = 5;
		break;
	case SystemInformationBlockType1__si_WindowLength_ms10:
		length = 10;
		break;
	case SystemInformationBlockType1__si_WindowLength_ms15:
		length = 15;
		break;
	case SystemInformationBlockType1__si_WindowLength_ms20:
		length = 20;
		break;
	case SystemInformationBlockType1__si_WindowLength_ms40:
		length = 40;
		break;
	}
	return length;
}
