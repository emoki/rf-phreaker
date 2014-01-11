#pragma once

#include <stdint.h>
#include "rf_phreaker/umts_rrc_asn_library/SIB-Type.h"
#include "rf_phreaker/umts_rrc_asn_library/BIT_STRING.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include "rf_phreaker/layer_3_decoder_common/pdu_element.h"
#include "rf_phreaker/layer_3_decoder_common/per_decoder_interface.h"
#include "rf_phreaker/layer_3_decoder_common/asn1_types.h"

class umts_system_information_container abstract : public per_decoder_interface
{
public:
	umts_system_information_container(sib_type sib, layer_3_information::pdu_element_type pdu_element);

	virtual ~umts_system_information_container();

	bool does_sib_type_match(sib_type sib);

protected:
	sib_type sib_type_;	
};



