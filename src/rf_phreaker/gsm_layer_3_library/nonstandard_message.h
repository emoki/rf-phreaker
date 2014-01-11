#pragma once

#include "rf_phreaker/gsm_layer_3_library/generic_message.h"
#include "rf_phreaker/gsm_layer_3_library/l2_pseudo_length_element.h"
#include "rf_phreaker/gsm_layer_3_library/skip_indicator.h"
#include "rf_phreaker/gsm_layer_3_library/protocol_discriminator.h"
#include "rf_phreaker/gsm_layer_3_library/message_type_info_element.h"

class nonstandard_message : public generic_message
{
public:
	nonstandard_message(void);
	~nonstandard_message(void);

	l2_pseudo_length_element l2_pseudo_length_;
	protocol_discriminator protocol_discriminator_;
	skip_indicator skip_indicator_;
	message_type_info_element message_type_;
};

