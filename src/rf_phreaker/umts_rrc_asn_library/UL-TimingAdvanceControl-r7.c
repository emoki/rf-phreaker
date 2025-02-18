/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UL-TimingAdvanceControl-r7.h"

static asn_per_constraints_t asn_PER_type_tddOption_constr_4 = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_UL_TimingAdvanceControl_r7_constr_1 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_tdd384_5[] = {
	{ ATF_POINTER, 3, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd384, ul_TimingAdvance),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UL_TimingAdvance,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-TimingAdvance"
		},
	{ ATF_POINTER, 2, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd384, ext_UL_TimingAdvance),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EXT_UL_TimingAdvance,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ext-UL-TimingAdvance"
		},
	{ ATF_POINTER, 1, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd384, activationTime),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ActivationTime,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"activationTime"
		},
};
static int asn_MAP_tdd384_oms_5[] = { 0, 1, 2 };
static ber_tlv_tag_t asn_DEF_tdd384_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd384_tag2el_5[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ul-TimingAdvance at 21942 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ext-UL-TimingAdvance at 21943 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* activationTime at 21944 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd384_specs_5 = {
	sizeof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd384),
	offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd384, _asn_ctx),
	asn_MAP_tdd384_tag2el_5,
	3,	/* Count of tags in the map */
	asn_MAP_tdd384_oms_5,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd384_5 = {
	"tdd384",
	"tdd384",
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
	asn_DEF_tdd384_tags_5,
	sizeof(asn_DEF_tdd384_tags_5)
		/sizeof(asn_DEF_tdd384_tags_5[0]) - 1, /* 1 */
	asn_DEF_tdd384_tags_5,	/* Same as above */
	sizeof(asn_DEF_tdd384_tags_5)
		/sizeof(asn_DEF_tdd384_tags_5[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd384_5,
	3,	/* Elements count */
	&asn_SPC_tdd384_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd768_9[] = {
	{ ATF_POINTER, 2, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd768, ext_UL_TimingAdvance),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EXT_UL_TimingAdvance,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ext-UL-TimingAdvance"
		},
	{ ATF_POINTER, 1, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd768, activationTime),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ActivationTime,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"activationTime"
		},
};
static int asn_MAP_tdd768_oms_9[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_tdd768_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd768_tag2el_9[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ext-UL-TimingAdvance at 21947 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* activationTime at 21948 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd768_specs_9 = {
	sizeof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd768),
	offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd768, _asn_ctx),
	asn_MAP_tdd768_tag2el_9,
	2,	/* Count of tags in the map */
	asn_MAP_tdd768_oms_9,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd768_9 = {
	"tdd768",
	"tdd768",
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
	asn_DEF_tdd768_tags_9,
	sizeof(asn_DEF_tdd768_tags_9)
		/sizeof(asn_DEF_tdd768_tags_9[0]) - 1, /* 1 */
	asn_DEF_tdd768_tags_9,	/* Same as above */
	sizeof(asn_DEF_tdd768_tags_9)
		/sizeof(asn_DEF_tdd768_tags_9[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd768_9,
	2,	/* Elements count */
	&asn_SPC_tdd768_specs_9	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd128_12[] = {
	{ ATF_POINTER, 2, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd128, ul_SynchronisationParameters),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UL_SynchronisationParameters_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-SynchronisationParameters"
		},
	{ ATF_POINTER, 1, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd128, synchronisationParameters),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SynchronisationParameters_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"synchronisationParameters"
		},
};
static int asn_MAP_tdd128_oms_12[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_tdd128_tags_12[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd128_tag2el_12[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ul-SynchronisationParameters at 21951 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* synchronisationParameters at 21952 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd128_specs_12 = {
	sizeof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd128),
	offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption__tdd128, _asn_ctx),
	asn_MAP_tdd128_tag2el_12,
	2,	/* Count of tags in the map */
	asn_MAP_tdd128_oms_12,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd128_12 = {
	"tdd128",
	"tdd128",
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
	asn_DEF_tdd128_tags_12,
	sizeof(asn_DEF_tdd128_tags_12)
		/sizeof(asn_DEF_tdd128_tags_12[0]) - 1, /* 1 */
	asn_DEF_tdd128_tags_12,	/* Same as above */
	sizeof(asn_DEF_tdd128_tags_12)
		/sizeof(asn_DEF_tdd128_tags_12[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd128_12,
	2,	/* Elements count */
	&asn_SPC_tdd128_specs_12	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tddOption_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption, choice.tdd384),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_tdd384_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd384"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption, choice.tdd768),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd768_9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd768"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption, choice.tdd128),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_tdd128_12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd128"
		},
};
static asn_TYPE_tag2member_t asn_MAP_tddOption_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tdd384 at 21942 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* tdd768 at 21947 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* tdd128 at 21951 */
};
static asn_CHOICE_specifics_t asn_SPC_tddOption_specs_4 = {
	sizeof(struct UL_TimingAdvanceControl_r7__enabled__tddOption),
	offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption, _asn_ctx),
	offsetof(struct UL_TimingAdvanceControl_r7__enabled__tddOption, present),
	sizeof(((struct UL_TimingAdvanceControl_r7__enabled__tddOption *)0)->present),
	asn_MAP_tddOption_tag2el_4,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tddOption_4 = {
	"tddOption",
	"tddOption",
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
	&asn_PER_type_tddOption_constr_4,
	asn_MBR_tddOption_4,
	3,	/* Elements count */
	&asn_SPC_tddOption_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_enabled_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TimingAdvanceControl_r7__enabled, tddOption),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_tddOption_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tddOption"
		},
};
static ber_tlv_tag_t asn_DEF_enabled_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_enabled_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* tddOption at 21945 */
};
static asn_SEQUENCE_specifics_t asn_SPC_enabled_specs_3 = {
	sizeof(struct UL_TimingAdvanceControl_r7__enabled),
	offsetof(struct UL_TimingAdvanceControl_r7__enabled, _asn_ctx),
	asn_MAP_enabled_tag2el_3,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_enabled_3 = {
	"enabled",
	"enabled",
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
	asn_DEF_enabled_tags_3,
	sizeof(asn_DEF_enabled_tags_3)
		/sizeof(asn_DEF_enabled_tags_3[0]) - 1, /* 1 */
	asn_DEF_enabled_tags_3,	/* Same as above */
	sizeof(asn_DEF_enabled_tags_3)
		/sizeof(asn_DEF_enabled_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_enabled_3,
	1,	/* Elements count */
	&asn_SPC_enabled_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UL_TimingAdvanceControl_r7_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TimingAdvanceControl_r7, choice.disabled),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"disabled"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TimingAdvanceControl_r7, choice.enabled),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_enabled_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"enabled"
		},
};
static asn_TYPE_tag2member_t asn_MAP_UL_TimingAdvanceControl_r7_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* disabled at 21938 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* enabled at 21955 */
};
static asn_CHOICE_specifics_t asn_SPC_UL_TimingAdvanceControl_r7_specs_1 = {
	sizeof(struct UL_TimingAdvanceControl_r7),
	offsetof(struct UL_TimingAdvanceControl_r7, _asn_ctx),
	offsetof(struct UL_TimingAdvanceControl_r7, present),
	sizeof(((struct UL_TimingAdvanceControl_r7 *)0)->present),
	asn_MAP_UL_TimingAdvanceControl_r7_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_UL_TimingAdvanceControl_r7 = {
	"UL-TimingAdvanceControl-r7",
	"UL-TimingAdvanceControl-r7",
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
	&asn_PER_type_UL_TimingAdvanceControl_r7_constr_1,
	asn_MBR_UL_TimingAdvanceControl_r7_1,
	2,	/* Elements count */
	&asn_SPC_UL_TimingAdvanceControl_r7_specs_1	/* Additional specs */
};

