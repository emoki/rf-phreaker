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
	available_pdus_[umts_sib5] = &asn_DEF_SysInfoType5;
	available_pdus_[umts_sib5bis] = &asn_DEF_SysInfoType5bis;
	available_pdus_[umts_sib6] = &asn_DEF_SysInfoType6;
	available_pdus_[umts_sib7] = &asn_DEF_SysInfoType7;
	available_pdus_[umts_sib11]      = &asn_DEF_SysInfoType11;
	available_pdus_[umts_sib11_bis]  = &asn_DEF_SysInfoType11bis;
	available_pdus_[umts_sib12] = &asn_DEF_SysInfoType12;
	available_pdus_[umts_sib13] = &asn_DEF_SysInfoType13;
	available_pdus_[umts_sib13_1] = &asn_DEF_SysInfoType13_1;
	available_pdus_[umts_sib13_2] = &asn_DEF_SysInfoType13_2;
	available_pdus_[umts_sib13_3] = &asn_DEF_SysInfoType13_3;
	available_pdus_[umts_sib13_4] = &asn_DEF_SysInfoType13_4;
	available_pdus_[umts_sib14] = &asn_DEF_SysInfoType14;
	available_pdus_[umts_sib15] = &asn_DEF_SysInfoType15;
	available_pdus_[umts_sib15bis] = &asn_DEF_SysInfoType15bis;
	available_pdus_[umts_sib15_1bis] = &asn_DEF_SysInfoType15_1bis;
	available_pdus_[umts_sib15_2] = &asn_DEF_SysInfoType15_2;
	available_pdus_[umts_sib15_2bis] = &asn_DEF_SysInfoType15_2bis;
	available_pdus_[umts_sib15_2ter] = &asn_DEF_SysInfoType15_2ter;
	available_pdus_[umts_sib15_3] = &asn_DEF_SysInfoType15_3;
	available_pdus_[umts_sib15_3bis] = &asn_DEF_SysInfoType15_3bis;
	available_pdus_[umts_sib15_4] = &asn_DEF_SysInfoType15_4;
	available_pdus_[umts_sib15_5] = &asn_DEF_SysInfoType15_5;
	available_pdus_[umts_sib15_6] = &asn_DEF_SysInfoType15_6;
	available_pdus_[umts_sib15_7] = &asn_DEF_SysInfoType15_7;
	available_pdus_[umts_sib15_8] = &asn_DEF_SysInfoType15_8;
	available_pdus_[umts_sib16] = &asn_DEF_SysInfoType16;
	available_pdus_[umts_sib17] = &asn_DEF_SysInfoType17;
	available_pdus_[umts_sib18]      = &asn_DEF_SysInfoType18;
	available_pdus_[umts_sib19] = &asn_DEF_SysInfoType19;
	available_pdus_[umts_sib20] = &asn_DEF_SysInfoType20;
	available_pdus_[umts_scheduling_block1] = &asn_DEF_SysInfoTypeSB1;
	available_pdus_[umts_scheduling_block2] = &asn_DEF_SysInfoTypeSB2;

	available_pdus_[lte_bcch_sch]    = &asn_DEF_BCCH_DL_SCH_Message;
	//available_pdus_[lte_sib1]        = &asn_DEF_SystemInformationBlockType1;
	//available_pdus_[lte_sib2]        = &asn_DEF_SystemInformationBlockType2;
	//available_pdus_[lte_sib3]        = &asn_DEF_SystemInformationBlockType3;
	//available_pdus_[lte_sib4]        = &asn_DEF_SystemInformationBlockType4;
	//available_pdus_[lte_sib5]        = &asn_DEF_SystemInformationBlockType5;
	//available_pdus_[lte_sib6]        = &asn_DEF_SystemInformationBlockType6;
	//available_pdus_[lte_sib7]        = &asn_DEF_SystemInformationBlockType7;
	//available_pdus_[lte_sib8]        = &asn_DEF_SystemInformationBlockType8;
	//available_pdus_[lte_sib9]        = &asn_DEF_SystemInformationBlockType9;
	//available_pdus_[lte_sib10]       = &asn_DEF_SystemInformationBlockType10;
	//available_pdus_[lte_sib11]       = &asn_DEF_SystemInformationBlockType11;
	

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

