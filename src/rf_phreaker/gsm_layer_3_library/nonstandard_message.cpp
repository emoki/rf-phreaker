#include "rf_phreaker/gsm_layer_3_library/nonstandard_message.h"


nonstandard_message::nonstandard_message(void)
	: l2_pseudo_length_(value_only_format)
	, protocol_discriminator_(value_only_format, false)
	, skip_indicator_(value_only_format, true)
	, message_type_(value_only_format)
{
	information_elements_.push_back(&l2_pseudo_length_);
	information_elements_.push_back(&protocol_discriminator_);
	information_elements_.push_back(&skip_indicator_);
	information_elements_.push_back(&message_type_);
}


nonstandard_message::~nonstandard_message(void)
{
}

