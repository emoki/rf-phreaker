#include "rf_phreaker/gsm_layer_3_library/generic_message.h"


generic_message::generic_message(void)
{
}


generic_message::~generic_message(void)
{
}

void generic_message::decode(gsm_bit_stream &bs)
{
	for(auto it = information_elements_.begin(); it != information_elements_.end(); it++)
		(*it)->decode(bs);

	verify();
}

void generic_message::verify()
{
	for(auto it = information_elements_.begin(); it != information_elements_.end(); it++)
		(*it)->verify();
}
