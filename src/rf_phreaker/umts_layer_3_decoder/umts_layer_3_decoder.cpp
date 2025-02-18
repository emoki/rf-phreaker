// asn1c_open_source_dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_layer_3_decoder.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_bcch_bch_message.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/log.h"

using namespace layer_3_information;

umts_asn1_decoder::umts_asn1_decoder(bool output_streams)
	: umts_bcch_bch_message_(new umts_bcch_bch_message)
	, debug_(output_streams) {}

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
		LOG(LERROR) << err.what();
		status = -1;
	}

	return status;
}

int umts_asn1_decoder::decode_bcch_bch_message(const uint8_t* raw_bits, uint32_t num_of_bytes, uint32_t unused_bits, umts_bcch_bch_message_aggregate &message)
{
	int status = 0;
	try
	{
		message.clear();
		bit_stream_container bits(raw_bits, num_of_bytes, unused_bits);

		if(debug_) {
			static std::ofstream f("umts_bitstreams_" + rf_phreaker::static_timestamp::to_string() + ".txt", std::ios::app);
			f << std::dec << message.unique_sector_key_ << "\t" << bits << std::endl;
		}

		umts_bcch_bch_message_->populate_data(bits, message);

		auto unused_bits = umts_bcch_bch_message_->bits_consumed() ? umts_bcch_bch_message_->bits_consumed() % 8 : 0;
		message.update_raw_layer_3(bit_stream(raw_bits, umts_bcch_bch_message_->bytes_consumed(), unused_bits));
	}
	catch(const std::exception &err)
	{
		LOG(LERROR) << err.what();
		status = -2;
	}
	return status;
}


std::vector<std::string> umts_asn1_decoder::get_text_description() {
	return umts_bcch_bch_message_->get_text_description();
}

void umts_asn1_decoder::store_descriptions(bool store_text) {
	umts_bcch_bch_message_->store_descriptions(store_text);
}

std::vector<std::string> umts_asn1_decoder::get_sib_description() {
	return std::vector<std::string>{};
}



