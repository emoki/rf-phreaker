#pragma once

#include <vector>
#include "rf_phreaker/layer_3_common/pdu_element_types.h"
#include "asn_application.h"
#include "constr_TYPE.h"



class pdu_definitions
{
public:
	typedef asn_TYPE_descriptor_t pdu_definition_type;

	pdu_definitions();
	
	std::vector<pdu_definition_type*> available_pdus_;
};

class pdu_element_container
{
public:
	pdu_element_container(layer_3_information::pdu_element_type pdu_element);
	~pdu_element_container(void);

	void *decoded_structure();

	void **decoded_structure_ptr();
	
	pdu_definitions::pdu_definition_type *pdu_type(); 

private:
	pdu_definitions::pdu_definition_type* specified_pdu_;

	
	void *decoded_structure_;

	static pdu_definitions pdu_definitions_;
};

