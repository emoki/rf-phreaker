#include "rf_phreaker/gsm_layer_3_library/cell_identity.h"


cell_identity::cell_identity(format_of_information_elements format)
	: information_element_type_3(format, cell_identity_value_bit_size)
{
}


cell_identity::~cell_identity()
{
}

void cell_identity::info_element_specific_decode()
{
	cell_identity_ = raw_bit_stream_[value_byte_position()] << 8 | raw_bit_stream_[value_byte_position() + 1];
}

void cell_identity::verify()
{
	// Nothing to verify.
}
