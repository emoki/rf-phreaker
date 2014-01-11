#pragma once

#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"
#include <vector>

namespace layer_3_information
{

// Get from Rajesh any changes he has done to this aggregate class.
// For now placeholders are put in to compile the code.

// placeholder
enum bcch_message_t
{
	msg_type_si_2,
	msg_type_si_2bis,
	msg_type_si_2ter,
	msg_type_si_2quarter,
	msg_type_si_3
};

class gsm_layer_3_message_aggregate : public bcch_bch_message_aggregate
{
public:
	gsm_layer_3_message_aggregate();

	// placeholder
	std::vector<uint32_t> neighbour_list_;
};


};

