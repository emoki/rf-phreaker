#include "rf_phreaker/umts_layer_3_decoder/umts_system_information_container.h"

using namespace layer_3_information;


umts_system_information_container::umts_system_information_container(sib_type sib, pdu_element_type pdu_element)
	: per_decoder_interface(pdu_element)
	, sib_type_(sib)
{
}


umts_system_information_container::~umts_system_information_container(void)
{
}

bool umts_system_information_container::does_sib_type_match(sib_type sib)
{
	return sib_type_ == sib;
}

void umts_system_information_container::parse_data(umts_bcch_bch_message_aggregate &message) {
	// Do nothing.  There are multiple sibs where we only dump their description and don't need
	// to parse anything.
}
