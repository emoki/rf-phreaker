/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/ProtocolErrorInformation.h"

static asn_per_constraints_t asn_PER_type_diagnosticsType_constr_2 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_type1_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ProtocolErrorInformation__diagnosticsType__type1, protocolErrorCause),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ProtocolErrorCause,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"protocolErrorCause"
		},
};
static ber_tlv_tag_t asn_DEF_type1_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_type1_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* protocolErrorCause at 29090 */
};
static asn_SEQUENCE_specifics_t asn_SPC_type1_specs_3 = {
	sizeof(struct ProtocolErrorInformation__diagnosticsType__type1),
	offsetof(struct ProtocolErrorInformation__diagnosticsType__type1, _asn_ctx),
	asn_MAP_type1_tag2el_3,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_type1_3 = {
	"type1",
	"type1",
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
	asn_DEF_type1_tags_3,
	sizeof(asn_DEF_type1_tags_3)
		/sizeof(asn_DEF_type1_tags_3[0]) - 1, /* 1 */
	asn_DEF_type1_tags_3,	/* Same as above */
	sizeof(asn_DEF_type1_tags_3)
		/sizeof(asn_DEF_type1_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_type1_3,
	1,	/* Elements count */
	&asn_SPC_type1_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_diagnosticsType_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ProtocolErrorInformation__diagnosticsType, choice.type1),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_type1_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"type1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ProtocolErrorInformation__diagnosticsType, choice.spare),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare"
		},
};
static asn_TYPE_tag2member_t asn_MAP_diagnosticsType_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* type1 at 29090 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* spare at 29091 */
};
static asn_CHOICE_specifics_t asn_SPC_diagnosticsType_specs_2 = {
	sizeof(struct ProtocolErrorInformation__diagnosticsType),
	offsetof(struct ProtocolErrorInformation__diagnosticsType, _asn_ctx),
	offsetof(struct ProtocolErrorInformation__diagnosticsType, present),
	sizeof(((struct ProtocolErrorInformation__diagnosticsType *)0)->present),
	asn_MAP_diagnosticsType_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_diagnosticsType_2 = {
	"diagnosticsType",
	"diagnosticsType",
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
	&asn_PER_type_diagnosticsType_constr_2,
	asn_MBR_diagnosticsType_2,
	2,	/* Elements count */
	&asn_SPC_diagnosticsType_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ProtocolErrorInformation_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ProtocolErrorInformation, diagnosticsType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_diagnosticsType_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"diagnosticsType"
		},
};
static ber_tlv_tag_t asn_DEF_ProtocolErrorInformation_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_ProtocolErrorInformation_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* diagnosticsType at 29090 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ProtocolErrorInformation_specs_1 = {
	sizeof(struct ProtocolErrorInformation),
	offsetof(struct ProtocolErrorInformation, _asn_ctx),
	asn_MAP_ProtocolErrorInformation_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_ProtocolErrorInformation = {
	"ProtocolErrorInformation",
	"ProtocolErrorInformation",
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
	asn_DEF_ProtocolErrorInformation_tags_1,
	sizeof(asn_DEF_ProtocolErrorInformation_tags_1)
		/sizeof(asn_DEF_ProtocolErrorInformation_tags_1[0]), /* 1 */
	asn_DEF_ProtocolErrorInformation_tags_1,	/* Same as above */
	sizeof(asn_DEF_ProtocolErrorInformation_tags_1)
		/sizeof(asn_DEF_ProtocolErrorInformation_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_ProtocolErrorInformation_1,
	1,	/* Elements count */
	&asn_SPC_ProtocolErrorInformation_specs_1	/* Additional specs */
};

