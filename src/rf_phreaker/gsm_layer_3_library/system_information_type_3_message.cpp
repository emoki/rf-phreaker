#include "rf_phreaker/gsm_layer_3_library/system_information_type_3_message.h"
#include <boost/lexical_cast.hpp>

system_information_type_3_message::system_information_type_3_message(void)
	: cell_identity_(value_only_format)
	, location_area_identification_(value_only_format)
	, control_channel_desription_(value_only_format)
	, cell_options_(value_only_format)
	, cell_selection_parameters_(value_only_format)
	, rach_control_parameters_(value_only_format)
	, si_3_rest_octets_(value_only_format)
{
	information_elements_.push_back(&cell_identity_);
	information_elements_.push_back(&location_area_identification_);
	information_elements_.push_back(&control_channel_desription_);
	information_elements_.push_back(&cell_options_);
	information_elements_.push_back(&cell_selection_parameters_);
	information_elements_.push_back(&rach_control_parameters_);
	information_elements_.push_back(&si_3_rest_octets_);
}


system_information_type_3_message::~system_information_type_3_message(void)
{
}

void system_information_type_3_message::verify()
{
	generic_message::verify();

	if(l2_pseudo_length_.l2_pseudo_length_ != system_information_type_3_l2_pseduo_length)
		throw std::runtime_error(std::string("l2_pseudo_length not correct for system information type 3.  Decoded l2 pseduo length = ").append(boost::lexical_cast<std::string>(l2_pseudo_length_.l2_pseudo_length_)));

	if(protocol_discriminator_.protocol_discriminator_ != radio_resources_management_messages)
		throw std::runtime_error(std::string("protocol_discriminator not correct for system information type 3.  Decoded protocol discriminator = ").append(boost::lexical_cast<std::string>(protocol_discriminator_.protocol_discriminator_)));

	if(message_type_.message_type_ != system_information_type_3)
		throw std::runtime_error(std::string("message_type not correct for system information type 3.  Decoded message type = ").append(boost::lexical_cast<std::string>(message_type_.message_type_)));;
}
