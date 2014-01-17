// lte_layer_3_decoder.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_bcch_dl_sch_message.h"

#include <fstream>

using namespace layer_3_information;

lte_asn1_decoder::lte_asn1_decoder()
: lte_bcch_bch_message_(new lte_bcch_dl_sch_message)
{
}

lte_asn1_decoder::~lte_asn1_decoder()
{
	delete lte_bcch_bch_message_;
}

int lte_asn1_decoder::decode_bcch_bch_message(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits,  layer_3_information::lte_rrc_message_aggregate &message)
{
	int status = 0;
	try
	{
		message.clear();
		bit_stream_container bits(bit_stream, num_of_bytes, unused_bits);

		//std::ofstream debug("lte_bitstreams.txt", std::ios::app);
		//if(debug)
		//	debug << bits << "\n";

		lte_bcch_bch_message_->populate_data(bits, message);
	}
	catch(const std::exception &err)
	{
        std::cout << err.what();
		status = -1;
	}
	return status;
};


