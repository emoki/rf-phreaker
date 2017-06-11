// lte_layer_3_decoder.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_bcch_dl_sch_message.h"
#include "rf_phreaker/common/common_utility.h"

#include <fstream>

using namespace layer_3_information;

lte_asn1_decoder::lte_asn1_decoder()
: lte_bcch_bch_message_(new lte_bcch_dl_sch_message)
, debug_(false) {}


lte_asn1_decoder::~lte_asn1_decoder()
{
	delete lte_bcch_bch_message_;
}

int lte_asn1_decoder::decode_bcch_bch_message(const uint8_t* raw_bits, uint32_t num_of_bytes, uint32_t unused_bits, layer_3_information::lte_rrc_message_aggregate &message)
{
	int status = 0;
	try {
		message.clear();
		message.raw_layer_3_.emplace_back(bit_stream(raw_bits, num_of_bytes, unused_bits));
		bit_stream_container bits(raw_bits, num_of_bytes, unused_bits);

		if(debug_) {
			static std::ofstream f("lte_bitstreams_" + rf_phreaker::static_timestamp::to_string() + ".txt", std::ios::app);
			f << bits << std::endl;
		}

		lte_bcch_bch_message_->populate_data(bits, message);
	}
	catch(const std::exception &err)
	{
        std::cout << err.what();
		status = -1;
	}
	return status;
}

std::vector<std::string> lte_asn1_decoder::get_text_description() {
	return lte_bcch_bch_message_->get_text_description();
}

void lte_asn1_decoder::store_text_description(bool store_text) {
	lte_bcch_bch_message_->store_text_description(store_text);
}
