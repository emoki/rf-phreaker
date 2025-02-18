/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/MeasConfig.h"

static asn_per_constraints_t asn_PER_type_speedStatePars_constr_12 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_setup_14[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasConfig__speedStatePars__setup, mobilityStateParameters),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MobilityStateParameters,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mobilityStateParameters"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasConfig__speedStatePars__setup, timeToTrigger_SF),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SpeedStateScaleFactors,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timeToTrigger-SF"
		},
};
static ber_tlv_tag_t asn_DEF_setup_tags_14[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_setup_tag2el_14[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* mobilityStateParameters */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* timeToTrigger-SF */
};
static asn_SEQUENCE_specifics_t asn_SPC_setup_specs_14 = {
	sizeof(struct MeasConfig__speedStatePars__setup),
	offsetof(struct MeasConfig__speedStatePars__setup, _asn_ctx),
	asn_MAP_setup_tag2el_14,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_setup_14 = {
	"setup",
	"setup",
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
	asn_DEF_setup_tags_14,
	sizeof(asn_DEF_setup_tags_14)
		/sizeof(asn_DEF_setup_tags_14[0]) - 1, /* 1 */
	asn_DEF_setup_tags_14,	/* Same as above */
	sizeof(asn_DEF_setup_tags_14)
		/sizeof(asn_DEF_setup_tags_14[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_setup_14,
	2,	/* Elements count */
	&asn_SPC_setup_specs_14	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_speedStatePars_12[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasConfig__speedStatePars, choice.release),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"release"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasConfig__speedStatePars, choice.setup),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_setup_14,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"setup"
		},
};
static asn_TYPE_tag2member_t asn_MAP_speedStatePars_tag2el_12[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* release */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* setup */
};
static asn_CHOICE_specifics_t asn_SPC_speedStatePars_specs_12 = {
	sizeof(struct MeasConfig__speedStatePars),
	offsetof(struct MeasConfig__speedStatePars, _asn_ctx),
	offsetof(struct MeasConfig__speedStatePars, present),
	sizeof(((struct MeasConfig__speedStatePars *)0)->present),
	asn_MAP_speedStatePars_tag2el_12,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_speedStatePars_12 = {
	"speedStatePars",
	"speedStatePars",
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
	&asn_PER_type_speedStatePars_constr_12,
	asn_MBR_speedStatePars_12,
	2,	/* Elements count */
	&asn_SPC_speedStatePars_specs_12	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_MeasConfig_1[] = {
	{ ATF_POINTER, 13, offsetof(struct MeasConfig, measObjectToRemoveList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasObjectToRemoveList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measObjectToRemoveList"
		},
	{ ATF_POINTER, 12, offsetof(struct MeasConfig, measObjectToAddModList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasObjectToAddModList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measObjectToAddModList"
		},
	{ ATF_POINTER, 11, offsetof(struct MeasConfig, reportConfigToRemoveList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReportConfigToRemoveList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"reportConfigToRemoveList"
		},
	{ ATF_POINTER, 10, offsetof(struct MeasConfig, reportConfigToAddModList),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReportConfigToAddModList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"reportConfigToAddModList"
		},
	{ ATF_POINTER, 9, offsetof(struct MeasConfig, measIdToRemoveList),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasIdToRemoveList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measIdToRemoveList"
		},
	{ ATF_POINTER, 8, offsetof(struct MeasConfig, measIdToAddModList),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasIdToAddModList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measIdToAddModList"
		},
	{ ATF_POINTER, 7, offsetof(struct MeasConfig, quantityConfig),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_QuantityConfig,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"quantityConfig"
		},
	{ ATF_POINTER, 6, offsetof(struct MeasConfig, measGapConfig),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_MeasGapConfig,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measGapConfig"
		},
	{ ATF_POINTER, 5, offsetof(struct MeasConfig, s_Measure),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RSRP_Range,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"s-Measure"
		},
	{ ATF_POINTER, 4, offsetof(struct MeasConfig, preRegistrationInfoHRPD),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PreRegistrationInfoHRPD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"preRegistrationInfoHRPD"
		},
	{ ATF_POINTER, 3, offsetof(struct MeasConfig, speedStatePars),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_speedStatePars_12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"speedStatePars"
		},
	{ ATF_POINTER, 2, offsetof(struct MeasConfig, measObjectToAddModList_v9e0),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasObjectToAddModList_v9e0,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measObjectToAddModList-v9e0"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasConfig, measIdToAddModList_v12xy),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasIdToAddModList_v12xy,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measIdToAddModList-v12xy"
		},
};
static int asn_MAP_MeasConfig_oms_1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
static ber_tlv_tag_t asn_DEF_MeasConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_MeasConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measObjectToRemoveList */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* measObjectToAddModList */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* reportConfigToRemoveList */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* reportConfigToAddModList */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* measIdToRemoveList */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* measIdToAddModList */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* quantityConfig */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* measGapConfig */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* s-Measure */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* preRegistrationInfoHRPD */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* speedStatePars */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* measObjectToAddModList-v9e0 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 } /* measIdToAddModList-v12xy */
};
static asn_SEQUENCE_specifics_t asn_SPC_MeasConfig_specs_1 = {
	sizeof(struct MeasConfig),
	offsetof(struct MeasConfig, _asn_ctx),
	asn_MAP_MeasConfig_tag2el_1,
	13,	/* Count of tags in the map */
	asn_MAP_MeasConfig_oms_1,	/* Optional members */
	11, 2,	/* Root/Additions */
	10,	/* Start extensions */
	14	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_MeasConfig = {
	"MeasConfig",
	"MeasConfig",
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
	asn_DEF_MeasConfig_tags_1,
	sizeof(asn_DEF_MeasConfig_tags_1)
		/sizeof(asn_DEF_MeasConfig_tags_1[0]), /* 1 */
	asn_DEF_MeasConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasConfig_tags_1)
		/sizeof(asn_DEF_MeasConfig_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_MeasConfig_1,
	13,	/* Elements count */
	&asn_SPC_MeasConfig_specs_1	/* Additional specs */
};

