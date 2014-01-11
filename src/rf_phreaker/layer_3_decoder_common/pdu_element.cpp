#include "rf_phreaker/layer_3_decoder_common/pdu_element.h"
#include "asn_type_descriptor.h" // This header file dependent on the type of the decoder.

using namespace layer_3_information;


pdu_definitions::pdu_definitions()
{
	available_pdus_.resize(number_pdu_elements);
	
	available_pdus_[umts_bcch_bch]   = &asn_DEF_BCCH_BCH_Message;
	available_pdus_[umts_mib]        = &asn_DEF_MasterInformationBlock; 
	available_pdus_[umts_sib1]       = &asn_DEF_SysInfoType1;
	available_pdus_[umts_sib2]       = &asn_DEF_SysInfoType2;
	available_pdus_[umts_sib3]       = &asn_DEF_SysInfoType3;
	available_pdus_[umts_sib4]       = &asn_DEF_SysInfoType4;
	available_pdus_[umts_sib11]      = &asn_DEF_SysInfoType11;
	available_pdus_[umts_sib11_bis]  = &asn_DEF_SysInfoType11bis;
	available_pdus_[umts_sib18]      = &asn_DEF_SysInfoType18;

	available_pdus_[lte_bcch_sch]    = &asn_DEF_BCCH_DL_SCH_Message;
	available_pdus_[lte_sib1]        = &asn_DEF_SystemInformationBlockType1;
	available_pdus_[lte_sib2]        = &asn_DEF_SystemInformationBlockType2;
	available_pdus_[lte_sib3]        = &asn_DEF_SystemInformationBlockType3;
	available_pdus_[lte_sib4]        = &asn_DEF_SystemInformationBlockType4;
	available_pdus_[lte_sib5]        = &asn_DEF_SystemInformationBlockType5;
	available_pdus_[lte_sib6]        = &asn_DEF_SystemInformationBlockType6;
	available_pdus_[lte_sib7]        = &asn_DEF_SystemInformationBlockType7;
	available_pdus_[lte_sib8]        = &asn_DEF_SystemInformationBlockType8;
	available_pdus_[lte_sib9]        = &asn_DEF_SystemInformationBlockType9;
	available_pdus_[lte_sib10]       = &asn_DEF_SystemInformationBlockType10;
	available_pdus_[lte_sib11]       = &asn_DEF_SystemInformationBlockType11;
	

};


pdu_definitions pdu_element_container::pdu_definitions_;

pdu_element_container::pdu_element_container(pdu_element_type pdu_element)
	: decoded_structure_(0)
{
	specified_pdu_ = pdu_definitions_.available_pdus_[pdu_element];
}

pdu_element_container::~pdu_element_container(void)
{
	if(decoded_structure_)
		ASN_STRUCT_FREE(*specified_pdu_, decoded_structure_);
}

void *pdu_element_container::decoded_structure()
{
	return decoded_structure_;
}

void **pdu_element_container::decoded_structure_ptr()
{
	return &decoded_structure_;
}

pdu_definitions::pdu_definition_type *pdu_element_container::pdu_type()
{
	return specified_pdu_;
}

