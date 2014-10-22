#pragma once

#include <vector>
#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include "asn_application.h"
#include "per_decoder.h"
#include "rf_phreaker/layer_3_decoder_common/pdu_element.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"

enum decode_status
{
	decode_success,
	decode_has_extra_data,
	decode_failed,
	decode_constraint_failed
};


class per_decoder_container
{
public:
	per_decoder_container(void);
	~per_decoder_container(void);

	decode_status decode(pdu_element_container &pdu_element_to_decode, const bit_stream_container &bit_stream, uint32_t &bits_consumed);

private:
	asn_codec_ctx_t upper_stack_limit_to_used_;
};

