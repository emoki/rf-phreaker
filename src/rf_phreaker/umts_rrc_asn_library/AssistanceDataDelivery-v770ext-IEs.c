/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-v770ext-IEs.h"

static asn_TYPE_member_t asn_MBR_AssistanceDataDelivery_v770ext_IEs_1[] = {
	{ ATF_POINTER, 3, offsetof(struct AssistanceDataDelivery_v770ext_IEs, ue_Positioning_OTDOA_AssistanceData_UEB_ext),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_OTDOA_AssistanceData_UEB_ext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-Positioning-OTDOA-AssistanceData-UEB-ext"
		},
	{ ATF_POINTER, 2, offsetof(struct AssistanceDataDelivery_v770ext_IEs, ue_Positioning_GPS_AssistanceData),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_AssistanceData_v770ext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-Positioning-GPS-AssistanceData"
		},
	{ ATF_POINTER, 1, offsetof(struct AssistanceDataDelivery_v770ext_IEs, ue_positioning_GANSS_AssistanceData),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GANSS_AssistanceData,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GANSS-AssistanceData"
		},
};
static int asn_MAP_AssistanceDataDelivery_v770ext_IEs_oms_1[] = { 0, 1, 2 };
static ber_tlv_tag_t asn_DEF_AssistanceDataDelivery_v770ext_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_AssistanceDataDelivery_v770ext_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ue-Positioning-OTDOA-AssistanceData-UEB-ext at 1324 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ue-Positioning-GPS-AssistanceData at 1325 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* ue-positioning-GANSS-AssistanceData at 1326 */
};
static asn_SEQUENCE_specifics_t asn_SPC_AssistanceDataDelivery_v770ext_IEs_specs_1 = {
	sizeof(struct AssistanceDataDelivery_v770ext_IEs),
	offsetof(struct AssistanceDataDelivery_v770ext_IEs, _asn_ctx),
	asn_MAP_AssistanceDataDelivery_v770ext_IEs_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_AssistanceDataDelivery_v770ext_IEs_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_AssistanceDataDelivery_v770ext_IEs = {
	"AssistanceDataDelivery-v770ext-IEs",
	"AssistanceDataDelivery-v770ext-IEs",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_AssistanceDataDelivery_v770ext_IEs_tags_1,
	sizeof(asn_DEF_AssistanceDataDelivery_v770ext_IEs_tags_1)
		/sizeof(asn_DEF_AssistanceDataDelivery_v770ext_IEs_tags_1[0]), /* 1 */
	asn_DEF_AssistanceDataDelivery_v770ext_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_AssistanceDataDelivery_v770ext_IEs_tags_1)
		/sizeof(asn_DEF_AssistanceDataDelivery_v770ext_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_AssistanceDataDelivery_v770ext_IEs_1,
	3,	/* Elements count */
	&asn_SPC_AssistanceDataDelivery_v770ext_IEs_specs_1	/* Additional specs */
};

