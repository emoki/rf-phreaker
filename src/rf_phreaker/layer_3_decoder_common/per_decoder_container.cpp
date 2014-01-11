#include "rf_phreaker/layer_3_decoder_common/per_decoder_container.h"




per_decoder_container::per_decoder_container(void)
{
	upper_stack_limit_to_used_.max_stack_size = 0; // no stack limit.
}

per_decoder_container::~per_decoder_container(void)
{
}

decode_status per_decoder_container::decode(pdu_element_container& pdu_element_to_decode, const bit_stream_container &bit_stream, uint32_t &bits_consumed)
{
	asn_dec_rval_t rval = uper_decode(&upper_stack_limit_to_used_, pdu_element_to_decode.pdu_type(), pdu_element_to_decode.decoded_structure_ptr(),
		bit_stream.bit_stream(), bit_stream.num_of_bytes(), 0, bit_stream.unused_bits());
	
	bits_consumed = rval.consumed;

	decode_status status = decode_success;

	// TODO - If rval.code == RC_WMORE it means there is extra data that was not decoded.  We could actually try processing this as well...
	if(rval.code == RC_OK || rval.code == RC_WMORE)
	{
		char errbuf[128];
		size_t errlen = sizeof(errbuf);

		if(asn_check_constraints(pdu_element_to_decode.pdu_type(), pdu_element_to_decode.decoded_structure(), errbuf, &errlen))
			status = decode_constraint_failed;
	}
	else if(rval.code == RC_FAIL)
		status = decode_failed;

	return status;
}
