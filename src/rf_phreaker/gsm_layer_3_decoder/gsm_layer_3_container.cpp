#include "stdafx.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_container.h"
#include "rf_phreaker/gsm_layer_3_decoder/si_2_container.h"
#include "rf_phreaker/gsm_layer_3_decoder/si_2bis_container.h"
#include "rf_phreaker/gsm_layer_3_decoder/si_2ter_container.h"
#include "rf_phreaker/gsm_layer_3_decoder/si_2quarter_container.h"
#include "rf_phreaker/gsm_layer_3_decoder/si_3_container.h"
#include <boost/shared_ptr.hpp>

gsm_layer_3_container::gsm_layer_3_container(void)
	                  :si_2_added(false),
					   si_3_added(false),
					   si_2bis_added(false),
					   si_2ter_added(false),
					   si_2quarter_added(false)
{
	//messages_to_decode_.insert(std::make_pair<message_type_code, boost::shared_ptr<populate_data_interface>>
	//	(system_information_type_3, boost::shared_ptr<populate_data_interface>(new si_3_container)));
}


gsm_layer_3_container::~gsm_layer_3_container(void)
{
}

void gsm_layer_3_container::populate_data(gsm_bit_stream &bit_stream, layer_3_information::gsm_layer_3_message_aggregate &message)
{
	auto it = messages_to_decode_.find(determine_message_type(bit_stream));
	if(it != messages_to_decode_.end())
		it->second->populate_data(bit_stream, message);
}

message_type_code gsm_layer_3_container::determine_message_type(gsm_bit_stream bs)
{
	if(is_standard_message(bs))
		throw std::runtime_error("Unable to decode gsm standard layer 3 message.");
	else
	{
		nonstandard_message_.decode(bs);
		return nonstandard_message_.message_type_.message_type_;
	}
}

bool gsm_layer_3_container::is_standard_message(gsm_bit_stream &bs)	
{
	return false;
}

void gsm_layer_3_container::update_message_container_list(layer_3_information::bcch_message_t message_t)
{
	switch(message_t) 
	{
	case layer_3_information::msg_type_si_2:
						{
							if(!si_2_added)
							{
							messages_to_decode_.insert(std::make_pair<message_type_code, boost::shared_ptr<populate_data_interface>>
							(system_information_type_2, boost::shared_ptr<populate_data_interface>(new si_2_container)));

							si_2_added = true;
							}

							break;
						}

	case layer_3_information::msg_type_si_2bis:
						{
							if(!si_2bis_added)
							{
							messages_to_decode_.insert(std::make_pair<message_type_code, boost::shared_ptr<populate_data_interface>>
							(system_information_type_2_bis, boost::shared_ptr<populate_data_interface>(new si_2bis_container)));

							si_2bis_added = true;
							}

							break;
						}

	
	case layer_3_information::msg_type_si_2ter:
						{
							if(!si_2ter_added)
							{
							messages_to_decode_.insert(std::make_pair<message_type_code, boost::shared_ptr<populate_data_interface>>
							(system_information_type_2_ter, boost::shared_ptr<populate_data_interface>(new si_2ter_container)));

							si_2ter_added = true;
							}

							break;
						}

	case layer_3_information::msg_type_si_2quarter:
					{
						if(!si_2quarter_added)
						{
						messages_to_decode_.insert(std::make_pair<message_type_code, boost::shared_ptr<populate_data_interface>>
						(system_information_type_2_quater, boost::shared_ptr<populate_data_interface>(new si_2quarter_container)));

						si_2quarter_added = true;
						}

						break;
					}


	

	case layer_3_information::msg_type_si_3:
						{
							if(!si_3_added)
							{
							messages_to_decode_.insert(std::make_pair<message_type_code, boost::shared_ptr<populate_data_interface>>
							(system_information_type_3, boost::shared_ptr<populate_data_interface>(new si_3_container)));

							si_3_added = true;
							}

							break;
						}					
	
	
	
	}//switch




}


