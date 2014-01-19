// gsm_layer_3_decoder.cpp : Defines the exported functions for the DLL application.
//

#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_decoder.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_container.h"

gsm_layer_3_decoder::gsm_layer_3_decoder()
{
	gsm_layer_3_container_ = new gsm_layer_3_container();
}

gsm_layer_3_decoder::~gsm_layer_3_decoder()
{
	delete gsm_layer_3_container_;
}


int32_t gsm_layer_3_decoder::decode_bcch_message(const uint8_t *bit_stream, uint32_t num_of_bytes, uint32_t unused_bits, layer_3_information::gsm_layer_3_message_aggregate &message)
{
	int32_t status = 0;
	try
	{
		message.clear();
		gsm_bit_stream bits(bit_stream, num_of_bytes, unused_bits);
		gsm_layer_3_container_->populate_data(bits, message);
	}
	catch(const std::exception &err)
	{
        std::cout << err.what();
		status = -1;
	}
	return status;

}

void gsm_layer_3_decoder::update_message_decode_list(layer_3_information::bcch_message_t message_t)
{
	gsm_layer_3_container_->update_message_container_list(message_t);
}



