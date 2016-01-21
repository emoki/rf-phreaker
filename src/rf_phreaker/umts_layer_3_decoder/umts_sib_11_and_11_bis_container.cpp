#include "rf_phreaker/umts_layer_3_decoder/umts_sib_11_and_11_bis_container.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType11bis.h"
#include "rf_phreaker/umts_rrc_asn_library/SysInfoType11.h"
#include <boost/lexical_cast.hpp>

using namespace layer_3_information;

enum cell_info_mode_specific_info
{
	mode_specific_nothing,
	mode_specific_fdd,
	mode_specific_tdd
};

enum rat_mode_specific_info
{
	rat_mode_specific_nothing,
	rat_mode_specific_gsm,
	rat_mode_specific_is_2000,
	rat_mode_specific_absent,
	rat_mode_specific_spare1
};


umts_sib_11_and_11_bis_container::umts_sib_11_and_11_bis_container()
	: umts_system_information_container(SIB_Type_systemInformationBlockType11, umts_sib11)
	, last_decode_was_sib_11_bis_(false)
{
}


umts_sib_11_and_11_bis_container::~umts_sib_11_and_11_bis_container()
{
}

decode_status umts_sib_11_and_11_bis_container::decode_data(const bit_stream_container &bit_stream, pdu_element_container &pdu_element)
{
	// 3GPP spec allows for the transmit of sib 11 or/(and?) sib 11 bis.  Both are specified using sib type 11 within the payload structure.  
	// To figure out which is being broadcast we must look at the MIB and scheduling block 1 and scheduling block 2.
	// Or we try to decode sib 11 and if it fails we decode sib 11 bis.  We currently ignore pdu_element and use internally sib_11 and sib_11_bis member variables
	// for decoding and parsing.

	bits_consumed_ = 0;

	last_decode_was_sib_11_bis_ = false;

	current_pdu_.reset(new pdu_element_container(umts_sib11));

	decode_status stat = per_decoder_container_.decode(*current_pdu_, bit_stream, bits_consumed_);

	if(stat != decode_success)
	{
		bits_consumed_ = 0;

		current_pdu_.reset(new pdu_element_container(umts_sib11_bis));

		stat = per_decoder_container_.decode(*current_pdu_, bit_stream, bits_consumed_);

		if(stat == decode_success)
			last_decode_was_sib_11_bis_ = true;
	}

	return stat;
}

void umts_sib_11_and_11_bis_container::parse_data(umts_bcch_bch_message_aggregate &message)
{
	current_message_ = (umts_bcch_bch_message_aggregate*)&message;

	if(last_decode_was_sib_11_bis_)
		parse_sib_11_bis();
	else
		parse_sib_11();

	remove_decoded_pdu_element();
}

void umts_sib_11_and_11_bis_container::parse_sib_11_bis()
{
	SysInfoType11bis_t *data = (SysInfoType11bis_t*)current_pdu_->decoded_structure();
	
	current_message_->sib11_bis_.is_decoded_ = true;

	if(data->measurementControlSysInfo)
	{
		switch(data->measurementControlSysInfo->use_of_HCS.present)
		{
		case MeasurementControlSysInfoExtension__use_of_HCS_PR_hcs_not_used:
			// inter rat neighbor
			if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.newInterRATCellList)
				parse_inter_rat_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.newInterRATCellList);


			switch(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.present)
			{
			case MeasurementControlSysInfoExtension__use_of_HCS__hcs_not_used__cellSelectQualityMeasure_PR_cpich_RSCP:
				// intra neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.newIntraFreqCellList)
					parse_intra_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.newIntraFreqCellList);

				// inter neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.newInterFreqCellList)
					parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.newInterFreqCellList);

				break;


			case MeasurementControlSysInfoExtension__use_of_HCS__hcs_not_used__cellSelectQualityMeasure_PR_cpich_Ec_N0:
				// intra neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newIntraFreqCellList)
					parse_intra_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newIntraFreqCellList);
			
				// inter neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newInterFreqCellList)
					parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newInterFreqCellList);

				break;


            case MeasurementControlSysInfoExtension__use_of_HCS_PR_NOTHING:
            default:;
			}
 		break;


		case MeasurementControlSysInfoExtension__use_of_HCS_PR_hcs_used:

			// inter rat neighbor
			if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.newInterRATCellList)
				parse_inter_rat_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.newInterRATCellList);
		

			switch(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.present)
			{
			case MeasurementControlSysInfoExtension__use_of_HCS__hcs_used__cellSelectQualityMeasure_PR_cpich_RSCP:
				// intra neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.newIntraFreqCellList)
					parse_intra_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.newIntraFreqCellList);

				// inter neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.newInterFreqCellList)
					parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.newInterFreqCellList);

				break;


			case MeasurementControlSysInfoExtension__use_of_HCS__hcs_used__cellSelectQualityMeasure_PR_cpich_Ec_N0:
				// intra neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newIntraFreqCellList)
					parse_intra_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newIntraFreqCellList);
			
				// inter neighbor
				if(data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newInterFreqCellList)
					parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo->use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.newInterFreqCellList);

				break;


			case MeasurementControlSysInfoExtension__use_of_HCS_PR_NOTHING:
			default:;
			}
        case MeasurementControlSysInfoExtension__use_of_HCS_PR_NOTHING:
        default:;
        }
	}

	current_message_->sib11_bis_.neighbor_intra_group_ = current_message_->neighbor_intra_group_;
	current_message_->sib11_bis_.neighbor_inter_group_ = current_message_->neighbor_inter_group_;
	current_message_->sib11_bis_.neighbor_inter_rat_group_ = current_message_->neighbor_inter_rat_group_;
}

void umts_sib_11_and_11_bis_container::parse_sib_11()
{
	SysInfoType11_t *data = (SysInfoType11_t*)current_pdu_->decoded_structure();

	current_message_->sib11_.is_decoded_ = true;

	switch(data->measurementControlSysInfo.use_of_HCS.present)
	{
	case MeasurementControlSysInfo__use_of_HCS_PR_hcs_not_used:

		// inter rat neighbor
		if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.interRATMeasurementSysInfo &&
				data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.interRATMeasurementSysInfo->interRATCellInfoList)
			parse_inter_rat_measurement_sys_info<>(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.interRATMeasurementSysInfo->interRATCellInfoList->newInterRATCellList);


		switch(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.present)
		{
		case MeasurementControlSysInfo__use_of_HCS__hcs_not_used__cellSelectQualityMeasure_PR_cpich_RSCP:
			// intra neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.intraFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List)
				parse_intra_measurement_sys_info<>(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List->newIntraFreqCellList);

			// inter neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo->interFreqCellInfoSI_List &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList)
				parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList);

			break;


		case MeasurementControlSysInfo__use_of_HCS__hcs_not_used__cellSelectQualityMeasure_PR_cpich_Ec_N0:
			// intra neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.intraFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List)
				parse_intra_measurement_sys_info<>(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List->newIntraFreqCellList);
			
			// inter neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo->interFreqCellInfoSI_List &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList)
				parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo.use_of_HCS.choice.hcs_not_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList);

			break;


		default:;
		}
 		break;


	case MeasurementControlSysInfo__use_of_HCS_PR_hcs_used:

		// inter rat neighbor
		if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.interRATMeasurementSysInfo &&
				data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.interRATMeasurementSysInfo->interRATCellInfoList)
			parse_inter_rat_measurement_sys_info<>(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.interRATMeasurementSysInfo->interRATCellInfoList->newInterRATCellList);
		

		switch(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.present)
		{
		case MeasurementControlSysInfo__use_of_HCS__hcs_used__cellSelectQualityMeasure_PR_cpich_RSCP:
			// intra neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.intraFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List)
				parse_intra_measurement_sys_info<>(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List->newIntraFreqCellList);

			// inter neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo->interFreqCellInfoSI_List &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList)
				parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_RSCP.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList);

			break;


		case MeasurementControlSysInfo__use_of_HCS__hcs_used__cellSelectQualityMeasure_PR_cpich_Ec_N0:
						// intra neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.intraFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List)
				parse_intra_measurement_sys_info<>(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.intraFreqMeasurementSysInfo->intraFreqCellInfoSI_List->newIntraFreqCellList);
			
			// inter neighbor
			if(data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo->interFreqCellInfoSI_List &&
					data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList)
				parse_inter_measurement_sys_info<>(*data->measurementControlSysInfo.use_of_HCS.choice.hcs_used.cellSelectQualityMeasure.choice.cpich_Ec_N0.interFreqMeasurementSysInfo->interFreqCellInfoSI_List->newInterFreqCellList);

			break;


		case MeasurementControlSysInfo__use_of_HCS_PR_NOTHING:
		default:;
		}
		break;
	default:;
	}

	current_message_->sib11_.neighbor_intra_group_ = current_message_->neighbor_intra_group_;
	current_message_->sib11_.neighbor_inter_group_ = current_message_->neighbor_inter_group_;
	current_message_->sib11_.neighbor_inter_rat_group_ = current_message_->neighbor_inter_rat_group_;
}

void umts_sib_11_and_11_bis_container::remove_decoded_pdu_element()
{
	current_pdu_.reset();
}

template<typename Data>
void umts_sib_11_and_11_bis_container::parse_intra_measurement_sys_info(const Data &data)
{
	for(int i = 0; i < data.list.count; i++)
	{
		// We present to cell_info_mode_specific because each numeration ultimately has the same choices.
		// nothing, fdd, and tdd - each enum in the same order..
		switch((cell_info_mode_specific_info)data.list.array[i]->cellInfo.modeSpecificInfo.present)
		{
		case mode_specific_fdd:
			if(data.list.array[i]->cellInfo.modeSpecificInfo.choice.fdd.primaryCPICH_Info)
				((umts_bcch_bch_message_aggregate*)current_message_)->neighbor_intra_group_.push_back((cpich_type)data.list.array[i]->cellInfo.modeSpecificInfo.choice.fdd.primaryCPICH_Info->primaryScramblingCode);
			else
				continue;
			break;
		case mode_specific_tdd:
			// see 10.3.6.57 Primary CCPCH info
			// scrambling code not present.
			break;
		default:;
		}
	}
}

template<typename Data>
void umts_sib_11_and_11_bis_container::parse_inter_measurement_sys_info(const Data &data)
{
	// 10.3.7.47a Measurement control system information extension
	// Default frequencyInfo value is the value of the previous "frequency info" in the list.  
	// NOTE: The first occurrence is then MP.
	// Therefore we leave neighbor instantiated and use the previous value for uarfcn if necessary.
	neighbor_inter neighbor;
	
	for(int i = 0; i < data.list.count; i++)
	{
		// We present to cell_info_mode_specific because each numeration ultimately has the same choices.
		// nothing, fdd, and tdd - each enum in the same order..

		if(data.list.array[i]->frequencyInfo)
		{
			switch((cell_info_mode_specific_info)data.list.array[i]->frequencyInfo->modeSpecificInfo.present)
			{
			case mode_specific_fdd:
				neighbor.uarfcn_ = (channel_type)data.list.array[i]->frequencyInfo->modeSpecificInfo.choice.fdd.uarfcn_DL;
				break;
			case mode_specific_tdd:
				neighbor.uarfcn_ = (channel_type)data.list.array[i]->frequencyInfo->modeSpecificInfo.choice.tdd.uarfcn_Nt;
				break;
			default:;
			}
		}

		switch((cell_info_mode_specific_info)data.list.array[i]->cellInfo.modeSpecificInfo.present)
		{
			case mode_specific_fdd:
				if(data.list.array[i]->cellInfo.modeSpecificInfo.choice.fdd.primaryCPICH_Info)
					neighbor.cpich_ = (cpich_type)data.list.array[i]->cellInfo.modeSpecificInfo.choice.fdd.primaryCPICH_Info->primaryScramblingCode;
				else
					neighbor.cpich_ = not_decoded_16;
				break;
			case mode_specific_tdd:
				// see 10.3.6.57 Primary CCPCH info
				// scrambling code not present.
				neighbor.cpich_ = not_decoded_16;
				break;
			default:;
		}

		((umts_bcch_bch_message_aggregate*)current_message_)->neighbor_inter_group_.push_back(neighbor);
	}
}

template<typename Data>
void umts_sib_11_and_11_bis_container::parse_inter_rat_measurement_sys_info(const Data &data)
{
	for(int i = 0; i < data.list.count; i++)
	{
		neighbor_inter_rat neighbor;

		switch(data.list.array[i]->technologySpecificInfo.present)
		{
		case rat_mode_specific_gsm:
			neighbor.arfcn_ = (channel_type)data.list.array[i]->technologySpecificInfo.choice.gsm.bcch_ARFCN;
			
			neighbor.bsic_ = std::string(boost::lexical_cast<std::string>(data.list.array[i]->technologySpecificInfo.choice.gsm.bsic.ncc)) +
				(std::string(boost::lexical_cast<std::string>(data.list.array[i]->technologySpecificInfo.choice.gsm.bsic.bcc)));
			
			neighbor.band_indicator_ = (band_indicator_type)data.list.array[i]->technologySpecificInfo.choice.gsm.frequency_band;

			// 10.3.2.4 Cell selection and re-selection info for SIB11/12
			// If the technology is not gsm skip this neighbor. 
			// Mandatory default for gsm rxlev is serving cell which appears to be in sib3/4 cellreselection.
			// Currently we leave the qrx_lev_min as not_decoded.
			if(data.list.array[i]->technologySpecificInfo.choice.gsm.cellSelectionReselectionInfo &&
					data.list.array[i]->technologySpecificInfo.choice.gsm.cellSelectionReselectionInfo->modeSpecificInfo.present == CellSelectReselectInfoSIB_11_12__modeSpecificInfo_PR_gsm &&
					data.list.array[i]->technologySpecificInfo.choice.gsm.cellSelectionReselectionInfo->modeSpecificInfo.choice.gsm.q_RxlevMin)
				neighbor.qrx_lev_min_ = (qrx_lev_min_type)*data.list.array[i]->technologySpecificInfo.choice.gsm.cellSelectionReselectionInfo->modeSpecificInfo.choice.gsm.q_RxlevMin;
			else
				neighbor.qrx_lev_min_ = not_decoded_16;
			break;

		case rat_mode_specific_is_2000:
			// Does not contain any information we're interested in.
		case rat_mode_specific_absent:
		case rat_mode_specific_spare1:
		case rat_mode_specific_nothing:
			break;
		default:;
		}

		((umts_bcch_bch_message_aggregate*)current_message_)->neighbor_inter_rat_group_.push_back(neighbor);
	}
}
