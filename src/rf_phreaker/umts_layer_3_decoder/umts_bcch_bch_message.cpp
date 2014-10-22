#include "rf_phreaker/umts_rrc_asn_library/BCCH-BCH-Message.h"
#include "rf_phreaker/umts_rrc_asn_library/SIB-Type.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_bcch_bch_message.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_mib_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_sib_1_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_sib_3_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_sib_4_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_sib_11_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_sib_11_bis_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_sib_11_and_11_bis_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_sib_18_container.h"

using namespace layer_3_information;


umts_bcch_bch_message::umts_bcch_bch_message(void)
	: per_decoder_interface(umts_bcch_bch)
{
}


umts_bcch_bch_message::~umts_bcch_bch_message(void)
{
}

void umts_bcch_bch_message::set_system_information_to_decode(const std::vector<pdu_element_type> &pdu_elements)
{
	system_information_to_decode_.clear();

	for(auto it = pdu_elements.begin(); it != pdu_elements.end(); it++)
	{
		switch(*it)
		{
		case umts_mib:
			system_information_to_decode_.push_back(boost::shared_ptr<umts_system_information_container>(new umts_mib_container));
			break;

		case umts_sib1:
			system_information_to_decode_.push_back(boost::shared_ptr<umts_system_information_container>(new umts_sib_1_container));
			break;

		case umts_sib3:
			system_information_to_decode_.push_back(boost::shared_ptr<umts_system_information_container>(new umts_sib_3_container));
			break;

		case umts_sib4:
			system_information_to_decode_.push_back(boost::shared_ptr<umts_system_information_container>(new umts_sib_4_container));
			break;

		case umts_sib11:
		case umts_sib11_bis:
			if(find_available_system_information(SIB_Type_systemInformationBlockType11) == nullptr)
				system_information_to_decode_.push_back(boost::shared_ptr<umts_system_information_container>(new umts_sib_11_and_11_bis_container));
			break;

		case umts_sib18:
			system_information_to_decode_.push_back(boost::shared_ptr<umts_system_information_container>(new umts_sib_18_container));
			break;

		default:
			throw(std::invalid_argument("Unknown or incompatible pdu element specified for decoding UMTS layer 3."));
		}
	}
}

void umts_bcch_bch_message::parse_data(umts_bcch_bch_message_aggregate &message)
{
	current_message_aggregate_ = &message;

	BCCH_BCH_Message_t *bcch_data = (BCCH_BCH_Message_t*)decoded_structure();
	
	message.system_frame_number_ = (system_frame_number_type)bcch_data->message.sfn_Prime;

	switch(bcch_data->message.payload.present)
	{
	case SystemInformation_BCH__payload_PR_NOTHING: 
	case SystemInformation_BCH__payload_PR_noSegment:
		break;
	case SystemInformation_BCH__payload_PR_firstSegment:
		handle_first_segment(bcch_data->message.payload.choice.firstSegment);
		break;
	case SystemInformation_BCH__payload_PR_subsequentSegment:
		handle_subsequent_segment(bcch_data->message.payload.choice.subsequentSegment);
		break;
	case SystemInformation_BCH__payload_PR_lastSegmentShort:
		handle_last_segment(bcch_data->message.payload.choice.lastSegmentShort);
		break;
	case SystemInformation_BCH__payload_PR_lastAndFirst:
		handle_last_segment(bcch_data->message.payload.choice.lastAndFirst.lastSegmentShort);
		handle_first_segment(bcch_data->message.payload.choice.lastAndFirst.firstSegment);
		break;
	case SystemInformation_BCH__payload_PR_lastAndComplete:
		handle_last_segment(bcch_data->message.payload.choice.lastAndComplete.lastSegmentShort);
		handle_complete_sib_list(bcch_data->message.payload.choice.lastAndComplete.completeSIB_List);
		break;
	case SystemInformation_BCH__payload_PR_lastAndCompleteAndFirst:
		handle_last_segment(bcch_data->message.payload.choice.lastAndCompleteAndFirst.lastSegmentShort);
		handle_complete_sib_list(bcch_data->message.payload.choice.lastAndCompleteAndFirst.completeSIB_List);
		handle_first_segment(bcch_data->message.payload.choice.lastAndCompleteAndFirst.firstSegment);
		break;
	case SystemInformation_BCH__payload_PR_completeSIB_List:
		handle_complete_sib_list(bcch_data->message.payload.choice.completeSIB_List);
		break;
	case SystemInformation_BCH__payload_PR_completeAndFirst:
		handle_complete_sib_list(bcch_data->message.payload.choice.completeAndFirst.completeSIB_List);
		handle_first_segment(bcch_data->message.payload.choice.completeAndFirst.firstSegment);
		break;
	case SystemInformation_BCH__payload_PR_completeSIB:
		handle_complete_sib(bcch_data->message.payload.choice.completeSIB);
		break;
	case SystemInformation_BCH__payload_PR_lastSegment:
		handle_last_segment(bcch_data->message.payload.choice.lastSegment);
		break;
	case SystemInformation_BCH__payload_PR_spare5:
	case SystemInformation_BCH__payload_PR_spare4:
	case SystemInformation_BCH__payload_PR_spare3:
	case SystemInformation_BCH__payload_PR_spare2:
	case SystemInformation_BCH__payload_PR_spare1:
		break;
	default:
		throw std::runtime_error("Error handling payload choice during umts bcch-bch message decoding");
	}

}

void umts_bcch_bch_message::handle_first_segment(const FirstSegmentShort_t &first_segment)
{
	umts_system_information_container *sys_info = find_available_system_information(first_segment.sib_Type);
	if(sys_info)
	{
		unique_sector_sib key(first_segment.sib_Type, current_message_aggregate_->unique_sector_key_);
		segmented_sibs_container_.add_first_segment(key, first_segment.seg_Count, bit_stream_container(&first_segment.sib_Data_variable));
		check_for_complete_sib_and_process(sys_info, key); 
	}
}

void umts_bcch_bch_message::handle_first_segment(const FirstSegment_t &first_segment)
{
	umts_system_information_container *sys_info = find_available_system_information(first_segment.sib_Type);
	if(sys_info)
	{
		unique_sector_sib key(first_segment.sib_Type, current_message_aggregate_->unique_sector_key_);
		segmented_sibs_container_.add_first_segment(key, first_segment.seg_Count, bit_stream_container(&first_segment.sib_Data_fixed));
		check_for_complete_sib_and_process(sys_info, key); 
	}
}

void umts_bcch_bch_message::handle_subsequent_segment(const SubsequentSegment_t &subsequent_segment)
{
	umts_system_information_container *sys_info = find_available_system_information(subsequent_segment.sib_Type);
	if(sys_info)
	{
		unique_sector_sib key(subsequent_segment.sib_Type, current_message_aggregate_->unique_sector_key_);
		segmented_sibs_container_.add_subsequent_segment(key, subsequent_segment.segmentIndex, bit_stream_container(&subsequent_segment.sib_Data_fixed));
		check_for_complete_sib_and_process(sys_info, key); 
	}
}

void umts_bcch_bch_message::handle_last_segment(const LastSegmentShort_t &last_segment)
{
	umts_system_information_container *sys_info = find_available_system_information(last_segment.sib_Type);
	if(sys_info)
	{
		unique_sector_sib key(last_segment.sib_Type, current_message_aggregate_->unique_sector_key_);
		segmented_sibs_container_.add_last_segment(key, last_segment.segmentIndex, bit_stream_container(&last_segment.sib_Data_variable));
		check_for_complete_sib_and_process(sys_info, key); 
	}
}

void umts_bcch_bch_message::handle_last_segment(const LastSegment_t &last_segment)
{
	umts_system_information_container *sys_info = find_available_system_information(last_segment.sib_Type);
	if(sys_info)
	{
		unique_sector_sib key(last_segment.sib_Type, current_message_aggregate_->unique_sector_key_);
		segmented_sibs_container_.add_last_segment(key, last_segment.segmentIndex, bit_stream_container(&last_segment.sib_Data_fixed));
		check_for_complete_sib_and_process(sys_info, key); 
	}
}

void umts_bcch_bch_message::handle_complete_sib(const CompleteSIBshort &complete_sib)
{
	umts_system_information_container *sys_info = find_available_system_information(complete_sib.sib_Type);
	if(sys_info)
		sys_info->populate_data(bit_stream_container(&complete_sib.sib_Data_variable), *current_message_aggregate_);
}

void umts_bcch_bch_message::handle_complete_sib(const CompleteSIB_t &complete_sib)
{
	umts_system_information_container *sys_info = find_available_system_information(complete_sib.sib_Type);
	if(sys_info)
		sys_info->populate_data(bit_stream_container(&complete_sib.sib_Data_fixed), *current_message_aggregate_);
}

void umts_bcch_bch_message::handle_complete_sib_list(const CompleteSIB_List_t &complete_sib_list)
{
	for(int i = 0; i < complete_sib_list.list.count; i++)
	{
		umts_system_information_container *sys_info = find_available_system_information(complete_sib_list.list.array[i]->sib_Type);
		if(sys_info)
			sys_info->populate_data(bit_stream_container(&complete_sib_list.list.array[i]->sib_Data_variable), *current_message_aggregate_);
	}
}

umts_system_information_container *umts_bcch_bch_message::find_available_system_information(sib_type sib)
{
	umts_system_information_container *sys_info = nullptr;
	for(auto it = system_information_to_decode_.begin(); it != system_information_to_decode_.end(); it++)
	{
		if((*it)->does_sib_type_match(sib))
			sys_info = it->get();
	}	
	return sys_info;
}

void umts_bcch_bch_message::check_for_complete_sib_and_process(umts_system_information_container *sys_info, const unique_sector_sib &key)
{
	if(segmented_sibs_container_.is_sib_complete(key))
	{
		bit_stream_container bit_stream(segmented_sibs_container_.get_completed_sib(key));
		sys_info->populate_data(bit_stream, *current_message_aggregate_);
		segmented_sibs_container_.clear_segments(key);
	}
}