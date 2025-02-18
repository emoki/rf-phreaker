/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/MobilityFromEUTRACommand-r8-IEs.h"

static asn_per_constraints_t asn_PER_type_purpose_constr_3 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_purpose_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MobilityFromEUTRACommand_r8_IEs__purpose, choice.handover),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Handover,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"handover"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MobilityFromEUTRACommand_r8_IEs__purpose, choice.cellChangeOrder),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellChangeOrder,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellChangeOrder"
		},
};
static asn_TYPE_tag2member_t asn_MAP_purpose_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* handover */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* cellChangeOrder */
};
static asn_CHOICE_specifics_t asn_SPC_purpose_specs_3 = {
	sizeof(struct MobilityFromEUTRACommand_r8_IEs__purpose),
	offsetof(struct MobilityFromEUTRACommand_r8_IEs__purpose, _asn_ctx),
	offsetof(struct MobilityFromEUTRACommand_r8_IEs__purpose, present),
	sizeof(((struct MobilityFromEUTRACommand_r8_IEs__purpose *)0)->present),
	asn_MAP_purpose_tag2el_3,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_purpose_3 = {
	"purpose",
	"purpose",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_purpose_constr_3,
	asn_MBR_purpose_3,
	2,	/* Elements count */
	&asn_SPC_purpose_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_MobilityFromEUTRACommand_r8_IEs_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MobilityFromEUTRACommand_r8_IEs, cs_FallbackIndicator),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cs-FallbackIndicator"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MobilityFromEUTRACommand_r8_IEs, purpose),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_purpose_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"purpose"
		},
	{ ATF_POINTER, 1, offsetof(struct MobilityFromEUTRACommand_r8_IEs, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MobilityFromEUTRACommand_v8a0_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtension"
		},
};
static int asn_MAP_MobilityFromEUTRACommand_r8_IEs_oms_1[] = { 2 };
static ber_tlv_tag_t asn_DEF_MobilityFromEUTRACommand_r8_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_MobilityFromEUTRACommand_r8_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* cs-FallbackIndicator */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* purpose */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* nonCriticalExtension */
};
static asn_SEQUENCE_specifics_t asn_SPC_MobilityFromEUTRACommand_r8_IEs_specs_1 = {
	sizeof(struct MobilityFromEUTRACommand_r8_IEs),
	offsetof(struct MobilityFromEUTRACommand_r8_IEs, _asn_ctx),
	asn_MAP_MobilityFromEUTRACommand_r8_IEs_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_MobilityFromEUTRACommand_r8_IEs_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_MobilityFromEUTRACommand_r8_IEs = {
	"MobilityFromEUTRACommand-r8-IEs",
	"MobilityFromEUTRACommand-r8-IEs",
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
	asn_DEF_MobilityFromEUTRACommand_r8_IEs_tags_1,
	sizeof(asn_DEF_MobilityFromEUTRACommand_r8_IEs_tags_1)
		/sizeof(asn_DEF_MobilityFromEUTRACommand_r8_IEs_tags_1[0]), /* 1 */
	asn_DEF_MobilityFromEUTRACommand_r8_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_MobilityFromEUTRACommand_r8_IEs_tags_1)
		/sizeof(asn_DEF_MobilityFromEUTRACommand_r8_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_MobilityFromEUTRACommand_r8_IEs_1,
	3,	/* Elements count */
	&asn_SPC_MobilityFromEUTRACommand_r8_IEs_specs_1	/* Additional specs */
};

