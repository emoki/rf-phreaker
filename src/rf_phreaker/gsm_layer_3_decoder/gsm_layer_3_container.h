#pragma once

#include "rf_phreaker/gsm_layer_3_library/gsm_layer_3_common.h"
#include "rf_phreaker/gsm_layer_3_library/nonstandard_message.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include <map>

class gsm_layer_3_container
{
public:
	gsm_layer_3_container(void);
	
	~gsm_layer_3_container(void);

	void populate_data(gsm_bit_stream &bit_stream, layer_3_information::gsm_layer_3_message_aggregate &message);

	void update_message_container_list(layer_3_information::gsm_bcch_si_type message_t);

private:
	bool is_standard_message(gsm_bit_stream &bit_stream);

	bool si_2_added, si_2bis_added, si_2ter_added, si_2quarter_added, si_3_added;

	// Pass by value because we do not want to consume bits.
	message_type_code determine_message_type(gsm_bit_stream bit_stream);

	std::map<message_type_code, boost::shared_ptr<populate_data_interface>> messages_to_decode_;

	nonstandard_message nonstandard_message_;
};

