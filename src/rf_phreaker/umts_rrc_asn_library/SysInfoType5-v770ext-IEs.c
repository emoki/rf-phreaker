/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/SysInfoType5-v770ext-IEs.h"

static asn_per_constraints_t asn_PER_type_modeSpecificInfo_constr_2 = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_sccpch_SystemInformation_MBMS_constr_13 = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_fdd_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__fdd, hs_dsch_CommonSystemInformation),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HS_DSCH_CommonSystemInformation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"hs-dsch-CommonSystemInformation"
		},
	{ ATF_POINTER, 1, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__fdd, hs_dsch_PagingSystemInformation),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HS_DSCH_PagingSystemInformation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"hs-dsch-PagingSystemInformation"
		},
};
static int asn_MAP_fdd_oms_3[] = { 1 };
static ber_tlv_tag_t asn_DEF_fdd_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_fdd_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* hs-dsch-CommonSystemInformation at 29640 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* hs-dsch-PagingSystemInformation at 29641 */
};
static asn_SEQUENCE_specifics_t asn_SPC_fdd_specs_3 = {
	sizeof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__fdd),
	offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__fdd, _asn_ctx),
	asn_MAP_fdd_tag2el_3,
	2,	/* Count of tags in the map */
	asn_MAP_fdd_oms_3,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_fdd_3 = {
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
	asn_DEF_fdd_tags_3,
	sizeof(asn_DEF_fdd_tags_3)
		/sizeof(asn_DEF_fdd_tags_3[0]) - 1, /* 1 */
	asn_DEF_fdd_tags_3,	/* Same as above */
	sizeof(asn_DEF_fdd_tags_3)
		/sizeof(asn_DEF_fdd_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_fdd_3,
	2,	/* Elements count */
	&asn_SPC_fdd_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd768_6[] = {
	{ ATF_POINTER, 3, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd768, pusch_SysInfoList_SFN),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PUSCH_SysInfoList_SFN_VHCR,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pusch-SysInfoList-SFN"
		},
	{ ATF_POINTER, 2, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd768, pdsch_SysInfoList_SFN),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PDSCH_SysInfoList_VHCR_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pdsch-SysInfoList-SFN"
		},
	{ ATF_POINTER, 1, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd768, prach_SystemInformationList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PRACH_SystemInformationList_VHCR_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"prach-SystemInformationList"
		},
};
static int asn_MAP_tdd768_oms_6[] = { 0, 1, 2 };
static ber_tlv_tag_t asn_DEF_tdd768_tags_6[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd768_tag2el_6[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pusch-SysInfoList-SFN at 29644 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* pdsch-SysInfoList-SFN at 29645 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* prach-SystemInformationList at 29650 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd768_specs_6 = {
	sizeof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd768),
	offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd768, _asn_ctx),
	asn_MAP_tdd768_tag2el_6,
	3,	/* Count of tags in the map */
	asn_MAP_tdd768_oms_6,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd768_6 = {
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
	asn_DEF_tdd768_tags_6,
	sizeof(asn_DEF_tdd768_tags_6)
		/sizeof(asn_DEF_tdd768_tags_6[0]) - 1, /* 1 */
	asn_DEF_tdd768_tags_6,	/* Same as above */
	sizeof(asn_DEF_tdd768_tags_6)
		/sizeof(asn_DEF_tdd768_tags_6[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd768_6,
	3,	/* Elements count */
	&asn_SPC_tdd768_specs_6	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd128_10[] = {
	{ ATF_POINTER, 1, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd128, prach_SystemInformationList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PRACH_SystemInformationList_LCR_v770ext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"prach-SystemInformationList"
		},
};
static int asn_MAP_tdd128_oms_10[] = { 0 };
static ber_tlv_tag_t asn_DEF_tdd128_tags_10[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd128_tag2el_10[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* prach-SystemInformationList at 29653 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd128_specs_10 = {
	sizeof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd128),
	offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd128, _asn_ctx),
	asn_MAP_tdd128_tag2el_10,
	1,	/* Count of tags in the map */
	asn_MAP_tdd128_oms_10,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd128_10 = {
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
	asn_DEF_tdd128_tags_10,
	sizeof(asn_DEF_tdd128_tags_10)
		/sizeof(asn_DEF_tdd128_tags_10[0]) - 1, /* 1 */
	asn_DEF_tdd128_tags_10,	/* Same as above */
	sizeof(asn_DEF_tdd128_tags_10)
		/sizeof(asn_DEF_tdd128_tags_10[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd128_10,
	1,	/* Elements count */
	&asn_SPC_tdd128_specs_10	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_modeSpecificInfo_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo, choice.fdd),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_fdd_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"fdd"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo, choice.tdd768),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd768_6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd768"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo, choice.tdd128),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_tdd128_10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd128"
		},
};
static asn_TYPE_tag2member_t asn_MAP_modeSpecificInfo_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* fdd at 29640 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* tdd768 at 29644 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* tdd128 at 29653 */
};
static asn_CHOICE_specifics_t asn_SPC_modeSpecificInfo_specs_2 = {
	sizeof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo),
	offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo, _asn_ctx),
	offsetof(struct SysInfoType5_v770ext_IEs__modeSpecificInfo, present),
	sizeof(((struct SysInfoType5_v770ext_IEs__modeSpecificInfo *)0)->present),
	asn_MAP_modeSpecificInfo_tag2el_2,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_modeSpecificInfo_2 = {
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
	&asn_PER_type_modeSpecificInfo_constr_2,
	asn_MBR_modeSpecificInfo_2,
	3,	/* Elements count */
	&asn_SPC_modeSpecificInfo_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_sccpch_SystemInformation_MBMS_13[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS, choice.mcchOnSCCPCHusedOnlyForMBMS),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SCCPCH_SystemInformation_MBMS_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mcchOnSCCPCHusedOnlyForMBMS"
		},
};
static asn_TYPE_tag2member_t asn_MAP_sccpch_SystemInformation_MBMS_tag2el_13[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* mcchOnSCCPCHusedOnlyForMBMS at 29666 */
};
static asn_CHOICE_specifics_t asn_SPC_sccpch_SystemInformation_MBMS_specs_13 = {
	sizeof(struct SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS),
	offsetof(struct SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS, _asn_ctx),
	offsetof(struct SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS, present),
	sizeof(((struct SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS *)0)->present),
	asn_MAP_sccpch_SystemInformation_MBMS_tag2el_13,
	1,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_sccpch_SystemInformation_MBMS_13 = {
	"sccpch-SystemInformation-MBMS",
	"sccpch-SystemInformation-MBMS",
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
	&asn_PER_type_sccpch_SystemInformation_MBMS_constr_13,
	asn_MBR_sccpch_SystemInformation_MBMS_13,
	1,	/* Elements count */
	&asn_SPC_sccpch_SystemInformation_MBMS_specs_13	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SysInfoType5_v770ext_IEs_1[] = {
	{ ATF_POINTER, 4, offsetof(struct SysInfoType5_v770ext_IEs, modeSpecificInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_modeSpecificInfo_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"modeSpecificInfo"
		},
	{ ATF_POINTER, 3, offsetof(struct SysInfoType5_v770ext_IEs, sccpch_SystemInformationList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SCCPCH_SystemInformationList_HCR_VHCR_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sccpch-SystemInformationList"
		},
	{ ATF_POINTER, 2, offsetof(struct SysInfoType5_v770ext_IEs, sccpch_SystemInformation_MBMS),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_sccpch_SystemInformation_MBMS_13,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sccpch-SystemInformation-MBMS"
		},
	{ ATF_POINTER, 1, offsetof(struct SysInfoType5_v770ext_IEs, tDD_MBSFNInformation),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TDD_MBSFNInformation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tDD-MBSFNInformation"
		},
};
static int asn_MAP_SysInfoType5_v770ext_IEs_oms_1[] = { 0, 1, 2, 3 };
static ber_tlv_tag_t asn_DEF_SysInfoType5_v770ext_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SysInfoType5_v770ext_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* modeSpecificInfo at 29642 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* sccpch-SystemInformationList at 29659 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* sccpch-SystemInformation-MBMS at 29666 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* tDD-MBSFNInformation at 29667 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SysInfoType5_v770ext_IEs_specs_1 = {
	sizeof(struct SysInfoType5_v770ext_IEs),
	offsetof(struct SysInfoType5_v770ext_IEs, _asn_ctx),
	asn_MAP_SysInfoType5_v770ext_IEs_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_SysInfoType5_v770ext_IEs_oms_1,	/* Optional members */
	4, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SysInfoType5_v770ext_IEs = {
	"SysInfoType5-v770ext-IEs",
	"SysInfoType5-v770ext-IEs",
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
	asn_DEF_SysInfoType5_v770ext_IEs_tags_1,
	sizeof(asn_DEF_SysInfoType5_v770ext_IEs_tags_1)
		/sizeof(asn_DEF_SysInfoType5_v770ext_IEs_tags_1[0]), /* 1 */
	asn_DEF_SysInfoType5_v770ext_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_SysInfoType5_v770ext_IEs_tags_1)
		/sizeof(asn_DEF_SysInfoType5_v770ext_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SysInfoType5_v770ext_IEs_1,
	4,	/* Elements count */
	&asn_SPC_SysInfoType5_v770ext_IEs_specs_1	/* Additional specs */
};

