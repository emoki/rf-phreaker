#include "transaction_identifier.h"
#include "rf_phreaker/gsm_layer_3_library/gsm_layer_3_common.h"

transaction_identifier::transaction_identifier(void)
	: generic_information_element(transaction_identifier_value_bit_size)
{
}


transaction_identifier::~transaction_identifier(void)
{
}

void transaction_identifier::decode(uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused, uint32_t &bits_consumed_thus_far)
{
}
