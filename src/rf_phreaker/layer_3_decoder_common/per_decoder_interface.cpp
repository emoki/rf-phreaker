#include "rf_phreaker/layer_3_decoder_common/per_decoder_interface.h"

using namespace layer_3_information;

per_decoder_interface::per_decoder_interface(pdu_element_type type)
     : bits_consumed_(0)
     , pdu_element_type_(type)
	 , decoded_structure_(0)
	 , current_decode_status_(decode_failed)
{
}


per_decoder_interface::~per_decoder_interface(void)
{
}

void per_decoder_interface::parse_data(umts_bcch_bch_message_aggregate &message)
{
	throw std::runtime_error("Parsing data with umts_bcch_bch_message_aggregate is not supported");
}

void per_decoder_interface::parse_data(lte_rrc_message_aggregate &message)
{
	throw std::runtime_error("Parsing data with umts_bcch_bch_message_aggregate is not supported");
}


decode_status per_decoder_interface::decode_data(const bit_stream_container &bit_stream, pdu_element_container &pdu_element)
{
	bits_consumed_ = 0;

	return per_decoder_container_.decode(pdu_element, bit_stream, bits_consumed_);
}

void* per_decoder_interface::decoded_structure() 
{ 
	BOOST_VERIFY(decoded_structure_);
	return decoded_structure_;
}

uint32_t per_decoder_interface::bits_consumed()
{
	return bits_consumed_;
}

decode_status per_decoder_interface::current_decode_status()
{
	return current_decode_status_;
}
