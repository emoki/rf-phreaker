// lte_layer_3_decoder.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_bcch_dl_sch_message.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/log.h"
#include <fstream>

using namespace layer_3_information;

lte_asn1_decoder::lte_asn1_decoder(bool output_streams)
: lte_bcch_bch_message_(new lte_bcch_dl_sch_message)
, debug_(output_streams) {}


lte_asn1_decoder::~lte_asn1_decoder()
{
	delete lte_bcch_bch_message_;
}

int lte_asn1_decoder::decode_bcch_bch_message(const uint8_t* raw_bits, uint32_t num_of_bytes, uint32_t unused_bits, layer_3_information::lte_rrc_message_aggregate &message)
{
	int status = 0;
	try {
		message.clear();

		bit_stream_container bits(raw_bits, num_of_bytes, unused_bits);

		if(debug_) {
			static std::ofstream f("lte_bitstreams_" + rf_phreaker::static_timestamp::to_string() + ".txt", std::ios::app);
			f << bits << std::endl;
		}

		lte_bcch_bch_message_->populate_data(bits, message);

		auto unused_bits = lte_bcch_bch_message_->bits_consumed() ? lte_bcch_bch_message_->bits_consumed() % 8 : 0;
		message.update_raw_layer_3(bit_stream(raw_bits, lte_bcch_bch_message_->bytes_consumed(), unused_bits));
	}
	catch(const std::exception &err)
	{
		LOG(LERROR) << err.what();
		status = -2;
	}
	return status;
}

std::vector<std::string> lte_asn1_decoder::get_text_description() {
	return lte_bcch_bch_message_->get_text_description();
}

void lte_asn1_decoder::store_descriptions(bool store_text) {
	lte_bcch_bch_message_->store_descriptions(store_text);
}


std::vector<std::string> lte_asn1_decoder::get_sib_description() {
	return lte_bcch_bch_message_->get_sib_description();
}
