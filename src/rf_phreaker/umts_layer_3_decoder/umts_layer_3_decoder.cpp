// asn1c_open_source_dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_layer_3_decoder.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_bcch_bch_message.h"

using namespace layer_3_information;

umts_asn1_decoder::umts_asn1_decoder()
	: umts_bcch_bch_message_(new umts_bcch_bch_message)
{
}

umts_asn1_decoder::~umts_asn1_decoder()
{
	delete umts_bcch_bch_message_;
}
	
int umts_asn1_decoder::specify_sibs_for_decoding(const pdu_element_type *elements, size_t num_elements)
{
	int status = 0;

	try
	{
		std::vector<pdu_element_type> pdus;
	
		for(size_t i = 0; i < num_elements; ++i)
		{
			pdus.push_back(elements[i]);
		}

		umts_bcch_bch_message_->set_system_information_to_decode(pdus);
	}
	catch(const std::exception &err)
	{
        std::cout << err.what();
		status = -1;
	}

	return status;
}

int umts_asn1_decoder::decode_bcch_bch_message(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits, umts_bcch_bch_message_aggregate &message)
{
	int status = 0;
	try
	{
		message.clear();
		bit_stream_container bits(bit_stream, num_of_bytes, unused_bits);
		umts_bcch_bch_message_->populate_data(bits, message);
	}
	catch(const std::exception &err)
	{
        std::cout << err.what();
		status = -1;
	}
	return status;
}




