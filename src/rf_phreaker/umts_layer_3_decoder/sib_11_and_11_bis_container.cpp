#include "sib_11_and_11_bis_container.h"
#include "SysInfoType11bis.h"
#include "SysInfoType11.h"


sib_11_and_11_bis_container::sib_11_and_11_bis_container()
	: system_information_container(SIB_Type_systemInformationBlockType11, umts_sib11)
	, last_decode_was_sib_11_bis_(false)
	, sib_11_pdu_(umts_sib11)
	, sib_11_bis_pdu_(umts_sib11_bis)
{
}


sib_11_and_11_bis_container::~sib_11_and_11_bis_container()
{
}

decode_status sib_11_and_11_bis_container::decode_data(const bit_stream_container &bit_stream, pdu_element_container &pdu_element)
{
	// 3GPP spec allows for the transmit of sib 11 or/(and?) sib 11 bis.  Both are specified using sib type 11 within the payload structure.  
	// To figure out which is being broadcast we must look at the MIB and scheduling block 1 and scheduling block 2.
	// Or we try to decode sib 11 and if it fails we decode sib 11 bis.  We currently ignore pdu_element and use internally sib_11 and sib_11_bis member variables
	// for decoding and parsing.

	bits_consumed_ = 0;

	last_decode_was_sib_11_bis_ = false;

	decode_status stat = per_decoder_container_.decode(sib_11_pdu_, bit_stream, bits_consumed_);

	if(stat != decode_success)
	{
		bits_consumed_ = 0;

		stat = per_decoder_container_.decode(sib_11_bis_pdu_, bit_stream, bits_consumed_);

		if(stat == decode_success)
			last_decode_was_sib_11_bis_ = true;
	}

	return stat;
}

void sib_11_and_11_bis_container::parse_data(umts_bcch_bch_message_aggregate &message)
{
	if(last_decode_was_sib_11_bis_)
		parse_sib_11_bis(message);
	else
		parse_sib_11(message);
}

void sib_11_and_11_bis_container::parse_sib_11_bis(umts_bcch_bch_message_aggregate &message)
{
	SysInfoType11bis_t *data = (SysInfoType11bis_t*)sib_11_bis_pdu_.decoded_structure();

	if(data->measurementControlSysInfo->use_of_HCS.present == MeasurementControlSysInfoExtension__use_of_HCS_PR_hcs_used)
	{
		if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.present == MeasurementControlSysInfoExtension__use_of_HCS__hcs_used__cellSelectQualityMeasure_PR_cpich_RSCP)
		{
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.newIntraFreqCellList;
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.newInterFreqCellList;
		}
		else if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.present == MeasurementControlSysInfoExtension__use_of_HCS__hcs_used__cellSelectQualityMeasure_PR_cpich_Ec_N0)
		{
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newIntraFreqCellList;
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newInterFreqCellList;
		}
	}
	else if(data->measurementControlSysInfo->use_of_HCS.present == MeasurementControlSysInfoExtension__use_of_HCS_PR_hcs_not_used)
	{
		if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.present == MeasurementControlSysInfoExtension__use_of_HCS__hcs_not_used__cellSelectQualityMeasure_PR_cpich_RSCP)
		{
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.newIntraFreqCellList;
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.newInterFreqCellList;
		}
		else if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.present == MeasurementControlSysInfoExtension__use_of_HCS__hcs_not_used__cellSelectQualityMeasure_PR_cpich_Ec_N0)
		{
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newIntraFreqCellList;
			data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newInterFreqCellList;
		}
	}

	//RAT_Type_t *dummy = 0;
	//if(data->measurementControlSysInfoExtensionAddon_r5)
	//{
	//	if(data->measurementControlSysInfoExtensionAddon_r5->newIntraFrequencyCellInfoListAddon_r5)
	//	{
	//		for(int i = 0; i < data->measurementControlSysInfoExtensionAddon_r5->newIntraFrequencyCellInfoListAddon_r5->list.count; i++)
	//		{
	//			CellSelectReselectInfo_v590ext *test = data->measurementControlSysInfoExtensionAddon_r5->newIntraFrequencyCellInfoListAddon_r5->list.array[i];
	//			DeltaRSCP_t tmp = *test->deltaQhcs;
	//		}
	//	}
	//	if(data->measurementControlSysInfoExtensionAddon_r5->newInterRATCellInfoListAddon_r5)
	//	{
	//		for(int i = 0; i < data->measurementControlSysInfoExtensionAddon_r5->newInterRATCellInfoListAddon_r5->list.count; i++)
	//		{
	//			CellSelectReselectInfo_v590ext *test = data->measurementControlSysInfoExtensionAddon_r5->newInterRATCellInfoListAddon_r5->list.array[i];
	//			DeltaRSCP_t tmp = *test->deltaQhcs;
	//		}
	//	}
	//	if(data->measurementControlSysInfoExtensionAddon_r5->newInterFrequencyCellInfoListAddon_r5)
	//	{
	//		for(int i = 0; i < data->measurementControlSysInfoExtensionAddon_r5->newInterFrequencyCellInfoListAddon_r5->list.count; i++)
	//		{
	//			CellSelectReselectInfo_v590ext *test = data->measurementControlSysInfoExtensionAddon_r5->newInterFrequencyCellInfoListAddon_r5->list.array[i];
	//			DeltaRSCP_t tmp = *test->deltaQhcs;
	//		}
	//	}
	//}
}

void sib_11_and_11_bis_container::parse_sib_11(umts_bcch_bch_message_aggregate &message)
{
	SysInfoType11_t *data = (SysInfoType11_t*)sib_11_pdu_.decoded_structure();

	//if(data->fach_MeasurementOccasionInfo)
	//{
	//	if(data->fach_MeasurementOccasionInfo->inter_freq_FDD_meas_ind)
	//	{
	//		data->fach_MeasurementOccasionInfo->
	//	}
	//	if(data->fach_MeasurementOccasionInfo->inter_freq_TDD_meas_ind)
	//	{
	//	}
	//	if(data->fach_MeasurementOccasionInfo->inter_RAT_meas_ind)
	//	{
	//		for(int i = 0; i < data->fach_MeasurementOccasionInfo->inter_RAT_meas_ind->list.count; i++)
	//		{
	//			RAT_Type_t *dummy = data->fach_MeasurementOccasionInfo->inter_RAT_meas_ind->list.array[i];
	//		}
	//	}
	//}
	//if(data->v4b0NonCriticalExtensions && data->v4b0NonCriticalExtensions->v590NonCriticalExtension)
	//{
	//	for(int i = 0; i < data->v4b0NonCriticalExtensions->v590NonCriticalExtension->sysInfoType11_v590ext.newIntraFrequencyCellInfoList_v590ext->list.count; i++)
	//	{
	//		CellSelectReselectInfo_v590ext *test = data->v4b0NonCriticalExtensions->v590NonCriticalExtension->sysInfoType11_v590ext.newIntraFrequencyCellInfoList_v590ext->list.array[i];
	//		DeltaRSCP_t tmp = *test->deltaQhcs;
	//	}
	//	for(int i = 0; i < data->v4b0NonCriticalExtensions->v590NonCriticalExtension->sysInfoType11_v590ext.newInterFrequencyCellInfoList_v590ext->list.count; i++)
	//	{
	//		CellSelectReselectInfo_v590ext *test = data->v4b0NonCriticalExtensions->v590NonCriticalExtension->sysInfoType11_v590ext.newInterFrequencyCellInfoList_v590ext->list.array[i];
	//		DeltaRSCP_t tmp = *test->deltaQhcs;
	//	}
	//	for(int i = 0; i < data->v4b0NonCriticalExtensions->v590NonCriticalExtension->sysInfoType11_v590ext.newInterRATCellInfoList_v590ext->list.count; i++)
	//	{
	//		CellSelectReselectInfo_v590ext *test = data->v4b0NonCriticalExtensions->v590NonCriticalExtension->sysInfoType11_v590ext.newInterRATCellInfoList_v590ext->list.array[i];
	//		DeltaRSCP_t tmp = *test->deltaQhcs;
	//	}
	//	//if(data->v4b0NonCriticalExtensions->v590NonCriticalExtension->v690NonCriticalExtensions->v6b0NonCriticalExtensions->v770NonCriticalExtensions->v7b0NonCriticalExtensions->sysInfoType11_v7b0ext.newInterFreqCellList->)

	//}
}
