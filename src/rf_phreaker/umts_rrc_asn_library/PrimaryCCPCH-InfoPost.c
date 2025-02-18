/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/PrimaryCCPCH-InfoPost.h"

static asn_per_constraints_t asn_PER_type_syncCase_constr_2 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_syncCase1_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PrimaryCCPCH_InfoPost__syncCase__syncCase1, timeslot),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeslotNumber,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timeslot"
		},
};
static ber_tlv_tag_t asn_DEF_syncCase1_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_syncCase1_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* timeslot at 19947 */
};
static asn_SEQUENCE_specifics_t asn_SPC_syncCase1_specs_3 = {
	sizeof(struct PrimaryCCPCH_InfoPost__syncCase__syncCase1),
	offsetof(struct PrimaryCCPCH_InfoPost__syncCase__syncCase1, _asn_ctx),
	asn_MAP_syncCase1_tag2el_3,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_syncCase1_3 = {
	"syncCase1",
	"syncCase1",
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
	asn_DEF_syncCase1_tags_3,
	sizeof(asn_DEF_syncCase1_tags_3)
		/sizeof(asn_DEF_syncCase1_tags_3[0]) - 1, /* 1 */
	asn_DEF_syncCase1_tags_3,	/* Same as above */
	sizeof(asn_DEF_syncCase1_tags_3)
		/sizeof(asn_DEF_syncCase1_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_syncCase1_3,
	1,	/* Elements count */
	&asn_SPC_syncCase1_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_syncCase2_5[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PrimaryCCPCH_InfoPost__syncCase__syncCase2, timeslotSync2),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeslotSync2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timeslotSync2"
		},
};
static ber_tlv_tag_t asn_DEF_syncCase2_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_syncCase2_tag2el_5[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* timeslotSync2 at 19950 */
};
static asn_SEQUENCE_specifics_t asn_SPC_syncCase2_specs_5 = {
	sizeof(struct PrimaryCCPCH_InfoPost__syncCase__syncCase2),
	offsetof(struct PrimaryCCPCH_InfoPost__syncCase__syncCase2, _asn_ctx),
	asn_MAP_syncCase2_tag2el_5,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_syncCase2_5 = {
	"syncCase2",
	"syncCase2",
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
	asn_DEF_syncCase2_tags_5,
	sizeof(asn_DEF_syncCase2_tags_5)
		/sizeof(asn_DEF_syncCase2_tags_5[0]) - 1, /* 1 */
	asn_DEF_syncCase2_tags_5,	/* Same as above */
	sizeof(asn_DEF_syncCase2_tags_5)
		/sizeof(asn_DEF_syncCase2_tags_5[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_syncCase2_5,
	1,	/* Elements count */
	&asn_SPC_syncCase2_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_syncCase_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PrimaryCCPCH_InfoPost__syncCase, choice.syncCase1),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_syncCase1_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"syncCase1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PrimaryCCPCH_InfoPost__syncCase, choice.syncCase2),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_syncCase2_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"syncCase2"
		},
};
static asn_TYPE_tag2member_t asn_MAP_syncCase_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* syncCase1 at 19947 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* syncCase2 at 19950 */
};
static asn_CHOICE_specifics_t asn_SPC_syncCase_specs_2 = {
	sizeof(struct PrimaryCCPCH_InfoPost__syncCase),
	offsetof(struct PrimaryCCPCH_InfoPost__syncCase, _asn_ctx),
	offsetof(struct PrimaryCCPCH_InfoPost__syncCase, present),
	sizeof(((struct PrimaryCCPCH_InfoPost__syncCase *)0)->present),
	asn_MAP_syncCase_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_syncCase_2 = {
	"syncCase",
	"syncCase",
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
	&asn_PER_type_syncCase_constr_2,
	asn_MBR_syncCase_2,
	2,	/* Elements count */
	&asn_SPC_syncCase_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_PrimaryCCPCH_InfoPost_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PrimaryCCPCH_InfoPost, syncCase),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_syncCase_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"syncCase"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PrimaryCCPCH_InfoPost, cellParametersID),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellParametersID,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellParametersID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PrimaryCCPCH_InfoPost, sctd_Indicator),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sctd-Indicator"
		},
};
static ber_tlv_tag_t asn_DEF_PrimaryCCPCH_InfoPost_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_PrimaryCCPCH_InfoPost_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* syncCase at 19947 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* cellParametersID at 19952 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* sctd-Indicator at 19953 */
};
static asn_SEQUENCE_specifics_t asn_SPC_PrimaryCCPCH_InfoPost_specs_1 = {
	sizeof(struct PrimaryCCPCH_InfoPost),
	offsetof(struct PrimaryCCPCH_InfoPost, _asn_ctx),
	asn_MAP_PrimaryCCPCH_InfoPost_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_PrimaryCCPCH_InfoPost = {
	"PrimaryCCPCH-InfoPost",
	"PrimaryCCPCH-InfoPost",
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
	asn_DEF_PrimaryCCPCH_InfoPost_tags_1,
	sizeof(asn_DEF_PrimaryCCPCH_InfoPost_tags_1)
		/sizeof(asn_DEF_PrimaryCCPCH_InfoPost_tags_1[0]), /* 1 */
	asn_DEF_PrimaryCCPCH_InfoPost_tags_1,	/* Same as above */
	sizeof(asn_DEF_PrimaryCCPCH_InfoPost_tags_1)
		/sizeof(asn_DEF_PrimaryCCPCH_InfoPost_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_PrimaryCCPCH_InfoPost_1,
	3,	/* Elements count */
	&asn_SPC_PrimaryCCPCH_InfoPost_specs_1	/* Additional specs */
};

