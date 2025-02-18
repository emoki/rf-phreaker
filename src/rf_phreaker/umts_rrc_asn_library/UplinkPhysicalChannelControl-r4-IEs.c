/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UplinkPhysicalChannelControl-r4-IEs.h"

static asn_per_constraints_t asn_PER_type_tddOption_constr_4 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_tdd384_5[] = {
	{ ATF_POINTER, 5, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd384, timingAdvance),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_UL_TimingAdvanceControl_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timingAdvance"
		},
	{ ATF_POINTER, 4, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd384, alpha),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Alpha,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"alpha"
		},
	{ ATF_POINTER, 3, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd384, prach_ConstantValue),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConstantValueTdd,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"prach-ConstantValue"
		},
	{ ATF_POINTER, 2, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd384, pusch_ConstantValue),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConstantValueTdd,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pusch-ConstantValue"
		},
	{ ATF_POINTER, 1, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd384, openLoopPowerControl_IPDL_TDD),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OpenLoopPowerControl_IPDL_TDD_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"openLoopPowerControl-IPDL-TDD"
		},
};
static int asn_MAP_tdd384_oms_5[] = { 0, 1, 2, 3, 4 };
static ber_tlv_tag_t asn_DEF_tdd384_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd384_tag2el_5[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* timingAdvance at 9786 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* alpha at 9787 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* prach-ConstantValue at 9788 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* pusch-ConstantValue at 9789 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* openLoopPowerControl-IPDL-TDD at 9790 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd384_specs_5 = {
	sizeof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd384),
	offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd384, _asn_ctx),
	asn_MAP_tdd384_tag2el_5,
	5,	/* Count of tags in the map */
	asn_MAP_tdd384_oms_5,	/* Optional members */
	5, 0,	/* Root/Additions */
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
	5,	/* Elements count */
	&asn_SPC_tdd384_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd128_11[] = {
	{ ATF_POINTER, 1, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd128, ul_SynchronisationParameters),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UL_SynchronisationParameters_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-SynchronisationParameters"
		},
};
static int asn_MAP_tdd128_oms_11[] = { 0 };
static ber_tlv_tag_t asn_DEF_tdd128_tags_11[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd128_tag2el_11[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* ul-SynchronisationParameters at 9793 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd128_specs_11 = {
	sizeof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd128),
	offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption__tdd128, _asn_ctx),
	asn_MAP_tdd128_tag2el_11,
	1,	/* Count of tags in the map */
	asn_MAP_tdd128_oms_11,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd128_11 = {
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
	asn_DEF_tdd128_tags_11,
	sizeof(asn_DEF_tdd128_tags_11)
		/sizeof(asn_DEF_tdd128_tags_11[0]) - 1, /* 1 */
	asn_DEF_tdd128_tags_11,	/* Same as above */
	sizeof(asn_DEF_tdd128_tags_11)
		/sizeof(asn_DEF_tdd128_tags_11[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd128_11,
	1,	/* Elements count */
	&asn_SPC_tdd128_specs_11	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tddOption_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption, choice.tdd384),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_tdd384_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd384"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption, choice.tdd128),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd128_11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd128"
		},
};
static asn_TYPE_tag2member_t asn_MAP_tddOption_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tdd384 at 9786 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* tdd128 at 9793 */
};
static asn_CHOICE_specifics_t asn_SPC_tddOption_specs_4 = {
	sizeof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption),
	offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption, _asn_ctx),
	offsetof(struct UplinkPhysicalChannelControl_r4_IEs__tddOption, present),
	sizeof(((struct UplinkPhysicalChannelControl_r4_IEs__tddOption *)0)->present),
	asn_MAP_tddOption_tag2el_4,
	2,	/* Count of tags in the map */
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
	2,	/* Elements count */
	&asn_SPC_tddOption_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UplinkPhysicalChannelControl_r4_IEs_1[] = {
	{ ATF_POINTER, 2, offsetof(struct UplinkPhysicalChannelControl_r4_IEs, ccTrCH_PowerControlInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CCTrCH_PowerControlInfo_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ccTrCH-PowerControlInfo"
		},
	{ ATF_POINTER, 1, offsetof(struct UplinkPhysicalChannelControl_r4_IEs, specialBurstScheduling),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SpecialBurstScheduling,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"specialBurstScheduling"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPhysicalChannelControl_r4_IEs, tddOption),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_tddOption_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tddOption"
		},
};
static int asn_MAP_UplinkPhysicalChannelControl_r4_IEs_oms_1[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_UplinkPhysicalChannelControl_r4_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UplinkPhysicalChannelControl_r4_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ccTrCH-PowerControlInfo at 9782 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* specialBurstScheduling at 9783 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* tddOption at 9791 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UplinkPhysicalChannelControl_r4_IEs_specs_1 = {
	sizeof(struct UplinkPhysicalChannelControl_r4_IEs),
	offsetof(struct UplinkPhysicalChannelControl_r4_IEs, _asn_ctx),
	asn_MAP_UplinkPhysicalChannelControl_r4_IEs_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_UplinkPhysicalChannelControl_r4_IEs_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UplinkPhysicalChannelControl_r4_IEs = {
	"UplinkPhysicalChannelControl-r4-IEs",
	"UplinkPhysicalChannelControl-r4-IEs",
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
	asn_DEF_UplinkPhysicalChannelControl_r4_IEs_tags_1,
	sizeof(asn_DEF_UplinkPhysicalChannelControl_r4_IEs_tags_1)
		/sizeof(asn_DEF_UplinkPhysicalChannelControl_r4_IEs_tags_1[0]), /* 1 */
	asn_DEF_UplinkPhysicalChannelControl_r4_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_UplinkPhysicalChannelControl_r4_IEs_tags_1)
		/sizeof(asn_DEF_UplinkPhysicalChannelControl_r4_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UplinkPhysicalChannelControl_r4_IEs_1,
	3,	/* Elements count */
	&asn_SPC_UplinkPhysicalChannelControl_r4_IEs_specs_1	/* Additional specs */
};

