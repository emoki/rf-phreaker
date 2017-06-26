#pragma once

#include <stdint.h>
#include "rf_phreaker/umts_rrc_asn_library/SIB-Type.h"
#include "rf_phreaker/umts_rrc_asn_library/SIB-TypeExt.h"
#include "rf_phreaker/umts_rrc_asn_library/SIB-TypeExt2.h"
#include "rf_phreaker/umts_rrc_asn_library/BIT_STRING.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include "rf_phreaker/layer_3_decoder_common/pdu_element.h"
#include "rf_phreaker/layer_3_decoder_common/per_decoder_interface.h"
#include "rf_phreaker/layer_3_decoder_common/asn1_types.h"
#include "rf_phreaker/umts_layer_3_decoder/asn_type_descriptor.h"

class umts_system_information_container  : public per_decoder_interface
{
public:
	umts_system_information_container(sib_type sib, layer_3_information::pdu_element_type pdu_element);

	virtual ~umts_system_information_container();

	bool does_sib_type_match(sib_type sib);

protected:
	virtual void parse_data(layer_3_information::umts_bcch_bch_message_aggregate &message);

	sib_type sib_type_;	
};

class umts_sib_2_container : public umts_system_information_container {
public:
	umts_sib_2_container() : umts_system_information_container(SIB_Type_systemInformationBlockType2, layer_3_information::umts_sib2) {}
};

class umts_sib_5_container : public umts_system_information_container {
public:
	umts_sib_5_container() : umts_system_information_container(SIB_Type_systemInformationBlockType5, layer_3_information::umts_sib5) {}
};

class umts_sib_5bis_container : public umts_system_information_container {
public:
	umts_sib_5bis_container() : umts_system_information_container(SIB_Type_systemInformationBlockType5bis, layer_3_information::umts_sib5bis) {}
};

class umts_sib_6_container : public umts_system_information_container {
public:
	umts_sib_6_container() : umts_system_information_container(SIB_Type_systemInformationBlockType6, layer_3_information::umts_sib6) {}
};

class umts_sib_7_container : public umts_system_information_container {
public:
	umts_sib_7_container() : umts_system_information_container(SIB_Type_systemInformationBlockType7, layer_3_information::umts_sib7) {}
};

class umts_sib_12_container : public umts_system_information_container {
public:
	umts_sib_12_container() : umts_system_information_container(SIB_Type_systemInformationBlockType12, layer_3_information::umts_sib12) {}
};

class umts_sib_13_container : public umts_system_information_container {
public:
	umts_sib_13_container() : umts_system_information_container(SIB_Type_systemInformationBlockType13, layer_3_information::umts_sib13) {}
};

class umts_sib_13_1_container : public umts_system_information_container {
public:
	umts_sib_13_1_container() : umts_system_information_container(SIB_Type_systemInformationBlockType13_1, layer_3_information::umts_sib13_1) {}
};

class umts_sib_13_2_container : public umts_system_information_container {
public:
	umts_sib_13_2_container() : umts_system_information_container(SIB_Type_systemInformationBlockType13_2, layer_3_information::umts_sib13_2) {}
};

class umts_sib_13_3_container : public umts_system_information_container {
public:
	umts_sib_13_3_container() : umts_system_information_container(SIB_Type_systemInformationBlockType13_3, layer_3_information::umts_sib13_3) {}
};

class umts_sib_13_4_container : public umts_system_information_container {
public:
	umts_sib_13_4_container() : umts_system_information_container(SIB_Type_systemInformationBlockType13_4, layer_3_information::umts_sib13_4) {}
};

class umts_sib_14_container : public umts_system_information_container {
public:
	umts_sib_14_container() : umts_system_information_container(SIB_Type_systemInformationBlockType14, layer_3_information::umts_sib14) {}
};

class umts_sib_15_3_container : public umts_system_information_container {
public:
	umts_sib_15_3_container() : umts_system_information_container(SIB_Type_systemInformationBlockType15_3, layer_3_information::umts_sib15_3) {}
};

class umts_sib_15_3bis_container : public umts_system_information_container {
public:
	umts_sib_15_3bis_container() : umts_system_information_container(SIB_TypeExt_PR_systemInfoType15_3bis, layer_3_information::umts_sib15_3bis) {}
};

class umts_sib_15_4_container : public umts_system_information_container {
public:
	umts_sib_15_4_container() : umts_system_information_container(SIB_Type_systemInformationBlockType15_4, layer_3_information::umts_sib15_4) {}
};

class umts_sib_15_5_container : public umts_system_information_container {
public:
	umts_sib_15_5_container() : umts_system_information_container(SIB_Type_systemInformationBlockType15_5, layer_3_information::umts_sib15_5) {}
};

class umts_sib_16_container : public umts_system_information_container {
public:
	umts_sib_16_container() : umts_system_information_container(SIB_Type_systemInformationBlockType16, layer_3_information::umts_sib16) {}
};

class umts_sib_17_container : public umts_system_information_container {
public:
	umts_sib_17_container() : umts_system_information_container(SIB_Type_systemInformationBlockType17, layer_3_information::umts_sib17) {}
};

class umts_scheduling_block_1_container : public umts_system_information_container {
public:
	umts_scheduling_block_1_container() : umts_system_information_container(SIB_Type_schedulingBlock1, layer_3_information::umts_scheduling_block1) {}
};

class umts_scheduling_block_2_container : public umts_system_information_container {
public:
	umts_scheduling_block_2_container() : umts_system_information_container(SIB_Type_schedulingBlock2, layer_3_information::umts_scheduling_block2) {}
};

class umts_multiple_container : public umts_system_information_container {
public:
	umts_multiple_container(sib_type sib, std::vector<layer_3_information::pdu_element_type> pdus) 
		: umts_system_information_container(sib, pdus.front()) {} // fail if no pdus

	virtual decode_status decode_data(const bit_stream_container &bit_stream, pdu_element_container &pdu_element) {
		decode_status stat = decode_failed;
		for(auto i : pdus_) {
			bits_consumed_ = 0;
			pdu_element_container pdu(i);
			stat = per_decoder_container_.decode(pdu, bit_stream, bits_consumed_);
			if(stat == decode_success)
				break;
		}
		return stat;
	}

	std::vector<layer_3_information::pdu_element_type> pdus_;
};

class umts_sib_15_container : public umts_multiple_container {
public:
	umts_sib_15_container() : umts_multiple_container(SIB_Type_systemInformationBlockType15, 
		std::vector<layer_3_information::pdu_element_type>{layer_3_information::umts_sib15, layer_3_information::umts_sib15bis}) {}
};

class umts_sib_15_1_container : public umts_multiple_container {
public:
	umts_sib_15_1_container() : umts_multiple_container(SIB_Type_systemInformationBlockType15_1, 
		std::vector<layer_3_information::pdu_element_type>{layer_3_information::umts_sib15_1, layer_3_information::umts_sib15_1bis}) {}
};

class umts_sib_15_2_container : public umts_multiple_container {
public:
	umts_sib_15_2_container() : umts_multiple_container(SIB_Type_systemInformationBlockType15_2, 
		std::vector<layer_3_information::pdu_element_type>{layer_3_information::umts_sib15_2, layer_3_information::umts_sib15_2bis, layer_3_information::umts_sib15_2ter}) {}
};




//////////////// Not currently used.  Have to figure how to decode these.  Perhaps the extension type?
class umts_sib_15_6_container : public umts_system_information_container {
public:
	umts_sib_15_6_container() : umts_system_information_container(SIB_TypeExt_PR_systemInfoType15_6, layer_3_information::umts_sib15_6) {}
};

class umts_sib_15_7_container : public umts_system_information_container {
public:
	umts_sib_15_7_container() : umts_system_information_container(SIB_TypeExt_PR_systemInfoType15_7, layer_3_information::umts_sib15_7) {}
};

class umts_sib_15_8_container : public umts_system_information_container {
public:
	umts_sib_15_8_container() : umts_system_information_container(SIB_TypeExt_PR_systemInfoType15_8, layer_3_information::umts_sib15_8) {}
};

class umts_sib_19_container : public umts_system_information_container {
public:
	umts_sib_19_container() : umts_system_information_container(SIB_TypeExt2_PR_systemInfoType19, layer_3_information::umts_sib19) {}
};

class umts_sib_20_container : public umts_system_information_container {
public:
	umts_sib_20_container() : umts_system_information_container(SIB_TypeExt2_PR_systemInfoType20, layer_3_information::umts_sib20) {}
};

