#pragma once

#include "rf_phreaker/layer_3_decoder_common/per_decoder_container.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"

class per_decoder_interface 
{
public:
	per_decoder_interface(layer_3_information::pdu_element_type type);
	~per_decoder_interface(void);

	template<typename Message> void populate_data(const bit_stream_container &bit_stream, Message &message);

protected:
	virtual decode_status decode_data(const bit_stream_container &bit_stream, pdu_element_container &pdu_element);

	virtual void parse_data(layer_3_information::umts_bcch_bch_message_aggregate &message);
	virtual void parse_data(layer_3_information::lte_rrc_message_aggregate &message);

	void* decoded_structure();

	uint32_t bits_consumed();

	decode_status current_decode_status();

	per_decoder_container per_decoder_container_;

	uint32_t bits_consumed_;
	
private:
	void *decoded_structure_;

	layer_3_information::pdu_element_type pdu_element_type_;

	decode_status current_decode_status_;
};

template<typename Message> 
void per_decoder_interface::populate_data(const bit_stream_container &bit_stream, Message &message)
{
	pdu_element_container pdu_element(pdu_element_type_);

	current_decode_status_ = decode_data(bit_stream, pdu_element);

	if(current_decode_status() != decode_success)
		return;

	decoded_structure_ = pdu_element.decoded_structure();

	parse_data(message);

	decoded_structure_ = 0;
}
