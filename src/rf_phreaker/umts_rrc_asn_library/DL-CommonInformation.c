/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/DL-CommonInformation.h"

static asn_per_constraints_t asn_PER_type_modeSpecificInfo_constr_3 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_fdd_4[] = {
	{ ATF_POINTER, 4, offsetof(struct DL_CommonInformation__modeSpecificInfo__fdd, defaultDPCH_OffsetValue),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DefaultDPCH_OffsetValueFDD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"defaultDPCH-OffsetValue"
		},
	{ ATF_POINTER, 3, offsetof(struct DL_CommonInformation__modeSpecificInfo__fdd, dpch_CompressedModeInfo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DPCH_CompressedModeInfo,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dpch-CompressedModeInfo"
		},
	{ ATF_POINTER, 2, offsetof(struct DL_CommonInformation__modeSpecificInfo__fdd, tx_DiversityMode),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TX_DiversityMode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tx-DiversityMode"
		},
	{ ATF_POINTER, 1, offsetof(struct DL_CommonInformation__modeSpecificInfo__fdd, dummy),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SSDT_Information,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dummy"
		},
};
static int asn_MAP_fdd_oms_4[] = { 0, 1, 2, 3 };
static ber_tlv_tag_t asn_DEF_fdd_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_fdd_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* defaultDPCH-OffsetValue at 16553 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* dpch-CompressedModeInfo at 16554 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* tx-DiversityMode at 16555 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* dummy at 16558 */
};
static asn_SEQUENCE_specifics_t asn_SPC_fdd_specs_4 = {
	sizeof(struct DL_CommonInformation__modeSpecificInfo__fdd),
	offsetof(struct DL_CommonInformation__modeSpecificInfo__fdd, _asn_ctx),
	asn_MAP_fdd_tag2el_4,
	4,	/* Count of tags in the map */
	asn_MAP_fdd_oms_4,	/* Optional members */
	4, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_fdd_4 = {
	"fdd",
	"fdd",
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
	asn_DEF_fdd_tags_4,
	sizeof(asn_DEF_fdd_tags_4)
		/sizeof(asn_DEF_fdd_tags_4[0]) - 1, /* 1 */
	asn_DEF_fdd_tags_4,	/* Same as above */
	sizeof(asn_DEF_fdd_tags_4)
		/sizeof(asn_DEF_fdd_tags_4[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_fdd_4,
	4,	/* Elements count */
	&asn_SPC_fdd_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd_9[] = {
	{ ATF_POINTER, 1, offsetof(struct DL_CommonInformation__modeSpecificInfo__tdd, defaultDPCH_OffsetValue),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DefaultDPCH_OffsetValueTDD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"defaultDPCH-OffsetValue"
		},
};
static int asn_MAP_tdd_oms_9[] = { 0 };
static ber_tlv_tag_t asn_DEF_tdd_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd_tag2el_9[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* defaultDPCH-OffsetValue at 16561 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd_specs_9 = {
	sizeof(struct DL_CommonInformation__modeSpecificInfo__tdd),
	offsetof(struct DL_CommonInformation__modeSpecificInfo__tdd, _asn_ctx),
	asn_MAP_tdd_tag2el_9,
	1,	/* Count of tags in the map */
	asn_MAP_tdd_oms_9,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd_9 = {
	"tdd",
	"tdd",
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
	asn_DEF_tdd_tags_9,
	sizeof(asn_DEF_tdd_tags_9)
		/sizeof(asn_DEF_tdd_tags_9[0]) - 1, /* 1 */
	asn_DEF_tdd_tags_9,	/* Same as above */
	sizeof(asn_DEF_tdd_tags_9)
		/sizeof(asn_DEF_tdd_tags_9[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd_9,
	1,	/* Elements count */
	&asn_SPC_tdd_specs_9	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_modeSpecificInfo_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation__modeSpecificInfo, choice.fdd),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_fdd_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"fdd"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation__modeSpecificInfo, choice.tdd),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd_9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd"
		},
};
static asn_TYPE_tag2member_t asn_MAP_modeSpecificInfo_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* fdd at 16553 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* tdd at 16561 */
};
static asn_CHOICE_specifics_t asn_SPC_modeSpecificInfo_specs_3 = {
	sizeof(struct DL_CommonInformation__modeSpecificInfo),
	offsetof(struct DL_CommonInformation__modeSpecificInfo, _asn_ctx),
	offsetof(struct DL_CommonInformation__modeSpecificInfo, present),
	sizeof(((struct DL_CommonInformation__modeSpecificInfo *)0)->present),
	asn_MAP_modeSpecificInfo_tag2el_3,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_modeSpecificInfo_3 = {
	"modeSpecificInfo",
	"modeSpecificInfo",
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
	&asn_PER_type_modeSpecificInfo_constr_3,
	asn_MBR_modeSpecificInfo_3,
	2,	/* Elements count */
	&asn_SPC_modeSpecificInfo_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_DL_CommonInformation_1[] = {
	{ ATF_POINTER, 1, offsetof(struct DL_CommonInformation, dl_DPCH_InfoCommon),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DL_DPCH_InfoCommon,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dl-DPCH-InfoCommon"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation, modeSpecificInfo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_modeSpecificInfo_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"modeSpecificInfo"
		},
};
static int asn_MAP_DL_CommonInformation_oms_1[] = { 0 };
static ber_tlv_tag_t asn_DEF_DL_CommonInformation_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_DL_CommonInformation_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* dl-DPCH-InfoCommon at 16550 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* modeSpecificInfo at 16559 */
};
static asn_SEQUENCE_specifics_t asn_SPC_DL_CommonInformation_specs_1 = {
	sizeof(struct DL_CommonInformation),
	offsetof(struct DL_CommonInformation, _asn_ctx),
	asn_MAP_DL_CommonInformation_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_DL_CommonInformation_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_DL_CommonInformation = {
	"DL-CommonInformation",
	"DL-CommonInformation",
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
	asn_DEF_DL_CommonInformation_tags_1,
	sizeof(asn_DEF_DL_CommonInformation_tags_1)
		/sizeof(asn_DEF_DL_CommonInformation_tags_1[0]), /* 1 */
	asn_DEF_DL_CommonInformation_tags_1,	/* Same as above */
	sizeof(asn_DEF_DL_CommonInformation_tags_1)
		/sizeof(asn_DEF_DL_CommonInformation_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_DL_CommonInformation_1,
	2,	/* Elements count */
	&asn_SPC_DL_CommonInformation_specs_1	/* Additional specs */
};

