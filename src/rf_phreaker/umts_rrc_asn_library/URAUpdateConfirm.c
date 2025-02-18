/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/URAUpdateConfirm.h"

static asn_per_constraints_t asn_PER_type_criticalExtensions_constr_17 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_criticalExtensions_constr_11 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_URAUpdateConfirm_constr_1 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static ber_tlv_tag_t asn_DEF_nonCriticalExtensions_tags_8[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_nonCriticalExtensions_specs_8 = {
	sizeof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions__v690NonCriticalExtensions__nonCriticalExtensions),
	offsetof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions__v690NonCriticalExtensions__nonCriticalExtensions, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nonCriticalExtensions_8 = {
	"nonCriticalExtensions",
	"nonCriticalExtensions",
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
	asn_DEF_nonCriticalExtensions_tags_8,
	sizeof(asn_DEF_nonCriticalExtensions_tags_8)
		/sizeof(asn_DEF_nonCriticalExtensions_tags_8[0]) - 1, /* 1 */
	asn_DEF_nonCriticalExtensions_tags_8,	/* Same as above */
	sizeof(asn_DEF_nonCriticalExtensions_tags_8)
		/sizeof(asn_DEF_nonCriticalExtensions_tags_8[0]), /* 2 */
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	&asn_SPC_nonCriticalExtensions_specs_8	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_v690NonCriticalExtensions_6[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions__v690NonCriticalExtensions, uraUpdateConfirm_v690ext),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_URAUpdateConfirm_v690ext_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-v690ext"
		},
	{ ATF_POINTER, 1, offsetof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions__v690NonCriticalExtensions, nonCriticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_nonCriticalExtensions_8,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtensions"
		},
};
static int asn_MAP_v690NonCriticalExtensions_oms_6[] = { 1 };
static ber_tlv_tag_t asn_DEF_v690NonCriticalExtensions_tags_6[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_v690NonCriticalExtensions_tag2el_6[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* uraUpdateConfirm-v690ext at 9925 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nonCriticalExtensions at 9926 */
};
static asn_SEQUENCE_specifics_t asn_SPC_v690NonCriticalExtensions_specs_6 = {
	sizeof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions__v690NonCriticalExtensions),
	offsetof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions__v690NonCriticalExtensions, _asn_ctx),
	asn_MAP_v690NonCriticalExtensions_tag2el_6,
	2,	/* Count of tags in the map */
	asn_MAP_v690NonCriticalExtensions_oms_6,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_v690NonCriticalExtensions_6 = {
	"v690NonCriticalExtensions",
	"v690NonCriticalExtensions",
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
	asn_DEF_v690NonCriticalExtensions_tags_6,
	sizeof(asn_DEF_v690NonCriticalExtensions_tags_6)
		/sizeof(asn_DEF_v690NonCriticalExtensions_tags_6[0]) - 1, /* 1 */
	asn_DEF_v690NonCriticalExtensions_tags_6,	/* Same as above */
	sizeof(asn_DEF_v690NonCriticalExtensions_tags_6)
		/sizeof(asn_DEF_v690NonCriticalExtensions_tags_6[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_v690NonCriticalExtensions_6,
	2,	/* Elements count */
	&asn_SPC_v690NonCriticalExtensions_specs_6	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_laterNonCriticalExtensions_4[] = {
	{ ATF_POINTER, 2, offsetof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions, uraUpdateConfirm_r3_add_ext),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-r3-add-ext"
		},
	{ ATF_POINTER, 1, offsetof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions, v690NonCriticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_v690NonCriticalExtensions_6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"v690NonCriticalExtensions"
		},
};
static int asn_MAP_laterNonCriticalExtensions_oms_4[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_laterNonCriticalExtensions_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_laterNonCriticalExtensions_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* uraUpdateConfirm-r3-add-ext at 9923 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* v690NonCriticalExtensions at 9925 */
};
static asn_SEQUENCE_specifics_t asn_SPC_laterNonCriticalExtensions_specs_4 = {
	sizeof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions),
	offsetof(struct URAUpdateConfirm__r3__laterNonCriticalExtensions, _asn_ctx),
	asn_MAP_laterNonCriticalExtensions_tag2el_4,
	2,	/* Count of tags in the map */
	asn_MAP_laterNonCriticalExtensions_oms_4,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_laterNonCriticalExtensions_4 = {
	"laterNonCriticalExtensions",
	"laterNonCriticalExtensions",
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
	asn_DEF_laterNonCriticalExtensions_tags_4,
	sizeof(asn_DEF_laterNonCriticalExtensions_tags_4)
		/sizeof(asn_DEF_laterNonCriticalExtensions_tags_4[0]) - 1, /* 1 */
	asn_DEF_laterNonCriticalExtensions_tags_4,	/* Same as above */
	sizeof(asn_DEF_laterNonCriticalExtensions_tags_4)
		/sizeof(asn_DEF_laterNonCriticalExtensions_tags_4[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_laterNonCriticalExtensions_4,
	2,	/* Elements count */
	&asn_SPC_laterNonCriticalExtensions_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_r3_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__r3, uraUpdateConfirm_r3),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_URAUpdateConfirm_r3_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-r3"
		},
	{ ATF_POINTER, 1, offsetof(struct URAUpdateConfirm__r3, laterNonCriticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_laterNonCriticalExtensions_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"laterNonCriticalExtensions"
		},
};
static int asn_MAP_r3_oms_2[] = { 1 };
static ber_tlv_tag_t asn_DEF_r3_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_r3_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* uraUpdateConfirm-r3 at 9920 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* laterNonCriticalExtensions at 9923 */
};
static asn_SEQUENCE_specifics_t asn_SPC_r3_specs_2 = {
	sizeof(struct URAUpdateConfirm__r3),
	offsetof(struct URAUpdateConfirm__r3, _asn_ctx),
	asn_MAP_r3_tag2el_2,
	2,	/* Count of tags in the map */
	asn_MAP_r3_oms_2,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_r3_2 = {
	"r3",
	"r3",
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
	asn_DEF_r3_tags_2,
	sizeof(asn_DEF_r3_tags_2)
		/sizeof(asn_DEF_r3_tags_2[0]) - 1, /* 1 */
	asn_DEF_r3_tags_2,	/* Same as above */
	sizeof(asn_DEF_r3_tags_2)
		/sizeof(asn_DEF_r3_tags_2[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_r3_2,
	2,	/* Elements count */
	&asn_SPC_r3_specs_2	/* Additional specs */
};

static ber_tlv_tag_t asn_DEF_nonCriticalExtensions_tags_16[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_nonCriticalExtensions_specs_16 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5__v690NonCriticalExtensions__nonCriticalExtensions),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5__v690NonCriticalExtensions__nonCriticalExtensions, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nonCriticalExtensions_16 = {
	"nonCriticalExtensions",
	"nonCriticalExtensions",
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
	asn_DEF_nonCriticalExtensions_tags_16,
	sizeof(asn_DEF_nonCriticalExtensions_tags_16)
		/sizeof(asn_DEF_nonCriticalExtensions_tags_16[0]) - 1, /* 1 */
	asn_DEF_nonCriticalExtensions_tags_16,	/* Same as above */
	sizeof(asn_DEF_nonCriticalExtensions_tags_16)
		/sizeof(asn_DEF_nonCriticalExtensions_tags_16[0]), /* 2 */
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	&asn_SPC_nonCriticalExtensions_specs_16	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_v690NonCriticalExtensions_14[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5__v690NonCriticalExtensions, uraUpdateConfirm_v690ext),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_URAUpdateConfirm_v690ext_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-v690ext"
		},
	{ ATF_POINTER, 1, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5__v690NonCriticalExtensions, nonCriticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_nonCriticalExtensions_16,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtensions"
		},
};
static int asn_MAP_v690NonCriticalExtensions_oms_14[] = { 1 };
static ber_tlv_tag_t asn_DEF_v690NonCriticalExtensions_tags_14[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_v690NonCriticalExtensions_tag2el_14[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* uraUpdateConfirm-v690ext at 9936 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nonCriticalExtensions at 9937 */
};
static asn_SEQUENCE_specifics_t asn_SPC_v690NonCriticalExtensions_specs_14 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5__v690NonCriticalExtensions),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5__v690NonCriticalExtensions, _asn_ctx),
	asn_MAP_v690NonCriticalExtensions_tag2el_14,
	2,	/* Count of tags in the map */
	asn_MAP_v690NonCriticalExtensions_oms_14,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_v690NonCriticalExtensions_14 = {
	"v690NonCriticalExtensions",
	"v690NonCriticalExtensions",
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
	asn_DEF_v690NonCriticalExtensions_tags_14,
	sizeof(asn_DEF_v690NonCriticalExtensions_tags_14)
		/sizeof(asn_DEF_v690NonCriticalExtensions_tags_14[0]) - 1, /* 1 */
	asn_DEF_v690NonCriticalExtensions_tags_14,	/* Same as above */
	sizeof(asn_DEF_v690NonCriticalExtensions_tags_14)
		/sizeof(asn_DEF_v690NonCriticalExtensions_tags_14[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_v690NonCriticalExtensions_14,
	2,	/* Elements count */
	&asn_SPC_v690NonCriticalExtensions_specs_14	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_r5_12[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5, uraUpdateConfirm_r5),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_URAUpdateConfirm_r5_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-r5"
		},
	{ ATF_POINTER, 1, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5, v690NonCriticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_v690NonCriticalExtensions_14,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"v690NonCriticalExtensions"
		},
};
static int asn_MAP_r5_oms_12[] = { 1 };
static ber_tlv_tag_t asn_DEF_r5_tags_12[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_r5_tag2el_12[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* uraUpdateConfirm-r5 at 9934 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* v690NonCriticalExtensions at 9936 */
};
static asn_SEQUENCE_specifics_t asn_SPC_r5_specs_12 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__r5, _asn_ctx),
	asn_MAP_r5_tag2el_12,
	2,	/* Count of tags in the map */
	asn_MAP_r5_oms_12,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_r5_12 = {
	"r5",
	"r5",
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
	asn_DEF_r5_tags_12,
	sizeof(asn_DEF_r5_tags_12)
		/sizeof(asn_DEF_r5_tags_12[0]) - 1, /* 1 */
	asn_DEF_r5_tags_12,	/* Same as above */
	sizeof(asn_DEF_r5_tags_12)
		/sizeof(asn_DEF_r5_tags_12[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_r5_12,
	2,	/* Elements count */
	&asn_SPC_r5_specs_12	/* Additional specs */
};

static ber_tlv_tag_t asn_DEF_nonCriticalExtensions_tags_23[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_nonCriticalExtensions_specs_23 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7__v860NonCriticalExtensions__nonCriticalExtensions),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7__v860NonCriticalExtensions__nonCriticalExtensions, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nonCriticalExtensions_23 = {
	"nonCriticalExtensions",
	"nonCriticalExtensions",
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
	asn_DEF_nonCriticalExtensions_tags_23,
	sizeof(asn_DEF_nonCriticalExtensions_tags_23)
		/sizeof(asn_DEF_nonCriticalExtensions_tags_23[0]) - 1, /* 1 */
	asn_DEF_nonCriticalExtensions_tags_23,	/* Same as above */
	sizeof(asn_DEF_nonCriticalExtensions_tags_23)
		/sizeof(asn_DEF_nonCriticalExtensions_tags_23[0]), /* 2 */
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	&asn_SPC_nonCriticalExtensions_specs_23	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_v860NonCriticalExtensions_21[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7__v860NonCriticalExtensions, uraUpdateConfirm_v860ext),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_URAUpdateConfirm_v860ext_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-v860ext"
		},
	{ ATF_POINTER, 1, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7__v860NonCriticalExtensions, nonCriticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_nonCriticalExtensions_23,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtensions"
		},
};
static int asn_MAP_v860NonCriticalExtensions_oms_21[] = { 1 };
static ber_tlv_tag_t asn_DEF_v860NonCriticalExtensions_tags_21[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_v860NonCriticalExtensions_tag2el_21[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* uraUpdateConfirm-v860ext at 9946 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nonCriticalExtensions at 9947 */
};
static asn_SEQUENCE_specifics_t asn_SPC_v860NonCriticalExtensions_specs_21 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7__v860NonCriticalExtensions),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7__v860NonCriticalExtensions, _asn_ctx),
	asn_MAP_v860NonCriticalExtensions_tag2el_21,
	2,	/* Count of tags in the map */
	asn_MAP_v860NonCriticalExtensions_oms_21,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_v860NonCriticalExtensions_21 = {
	"v860NonCriticalExtensions",
	"v860NonCriticalExtensions",
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
	asn_DEF_v860NonCriticalExtensions_tags_21,
	sizeof(asn_DEF_v860NonCriticalExtensions_tags_21)
		/sizeof(asn_DEF_v860NonCriticalExtensions_tags_21[0]) - 1, /* 1 */
	asn_DEF_v860NonCriticalExtensions_tags_21,	/* Same as above */
	sizeof(asn_DEF_v860NonCriticalExtensions_tags_21)
		/sizeof(asn_DEF_v860NonCriticalExtensions_tags_21[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_v860NonCriticalExtensions_21,
	2,	/* Elements count */
	&asn_SPC_v860NonCriticalExtensions_specs_21	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_r7_18[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7, uraUpdateConfirm_r7),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_URAUpdateConfirm_r7_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-r7"
		},
	{ ATF_POINTER, 2, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7, uraUpdateConfirm_r7_add_ext),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"uraUpdateConfirm-r7-add-ext"
		},
	{ ATF_POINTER, 1, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7, v860NonCriticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_v860NonCriticalExtensions_21,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"v860NonCriticalExtensions"
		},
};
static int asn_MAP_r7_oms_18[] = { 1, 2 };
static ber_tlv_tag_t asn_DEF_r7_tags_18[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_r7_tag2el_18[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* uraUpdateConfirm-r7 at 9942 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* uraUpdateConfirm-r7-add-ext at 9944 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* v860NonCriticalExtensions at 9946 */
};
static asn_SEQUENCE_specifics_t asn_SPC_r7_specs_18 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__r7, _asn_ctx),
	asn_MAP_r7_tag2el_18,
	3,	/* Count of tags in the map */
	asn_MAP_r7_oms_18,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_r7_18 = {
	"r7",
	"r7",
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
	asn_DEF_r7_tags_18,
	sizeof(asn_DEF_r7_tags_18)
		/sizeof(asn_DEF_r7_tags_18[0]) - 1, /* 1 */
	asn_DEF_r7_tags_18,	/* Same as above */
	sizeof(asn_DEF_r7_tags_18)
		/sizeof(asn_DEF_r7_tags_18[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_r7_18,
	3,	/* Elements count */
	&asn_SPC_r7_specs_18	/* Additional specs */
};

static ber_tlv_tag_t asn_DEF_criticalExtensions_tags_24[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_criticalExtensions_specs_24 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__criticalExtensions),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions__criticalExtensions, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_criticalExtensions_24 = {
	"criticalExtensions",
	"criticalExtensions",
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
	asn_DEF_criticalExtensions_tags_24,
	sizeof(asn_DEF_criticalExtensions_tags_24)
		/sizeof(asn_DEF_criticalExtensions_tags_24[0]) - 1, /* 1 */
	asn_DEF_criticalExtensions_tags_24,	/* Same as above */
	sizeof(asn_DEF_criticalExtensions_tags_24)
		/sizeof(asn_DEF_criticalExtensions_tags_24[0]), /* 2 */
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	&asn_SPC_criticalExtensions_specs_24	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_criticalExtensions_17[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions, choice.r7),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_r7_18,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"r7"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions, choice.criticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_criticalExtensions_24,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"criticalExtensions"
		},
};
static asn_TYPE_tag2member_t asn_MAP_criticalExtensions_tag2el_17[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* r7 at 9942 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* criticalExtensions at 9950 */
};
static asn_CHOICE_specifics_t asn_SPC_criticalExtensions_specs_17 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions, _asn_ctx),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions, present),
	sizeof(((struct URAUpdateConfirm__later_than_r3__criticalExtensions__criticalExtensions *)0)->present),
	asn_MAP_criticalExtensions_tag2el_17,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_criticalExtensions_17 = {
	"criticalExtensions",
	"criticalExtensions",
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
	&asn_PER_type_criticalExtensions_constr_17,
	asn_MBR_criticalExtensions_17,
	2,	/* Elements count */
	&asn_SPC_criticalExtensions_specs_17	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_criticalExtensions_11[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions, choice.r5),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_r5_12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"r5"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions, choice.criticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_criticalExtensions_17,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"criticalExtensions"
		},
};
static asn_TYPE_tag2member_t asn_MAP_criticalExtensions_tag2el_11[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* r5 at 9934 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* criticalExtensions at 9949 */
};
static asn_CHOICE_specifics_t asn_SPC_criticalExtensions_specs_11 = {
	sizeof(struct URAUpdateConfirm__later_than_r3__criticalExtensions),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions, _asn_ctx),
	offsetof(struct URAUpdateConfirm__later_than_r3__criticalExtensions, present),
	sizeof(((struct URAUpdateConfirm__later_than_r3__criticalExtensions *)0)->present),
	asn_MAP_criticalExtensions_tag2el_11,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_criticalExtensions_11 = {
	"criticalExtensions",
	"criticalExtensions",
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
	&asn_PER_type_criticalExtensions_constr_11,
	asn_MBR_criticalExtensions_11,
	2,	/* Elements count */
	&asn_SPC_criticalExtensions_specs_11	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_later_than_r3_9[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3, rrc_TransactionIdentifier),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RRC_TransactionIdentifier,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rrc-TransactionIdentifier"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm__later_than_r3, criticalExtensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_criticalExtensions_11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"criticalExtensions"
		},
};
static ber_tlv_tag_t asn_DEF_later_than_r3_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_later_than_r3_tag2el_9[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rrc-TransactionIdentifier at 9931 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* criticalExtensions at 9939 */
};
static asn_SEQUENCE_specifics_t asn_SPC_later_than_r3_specs_9 = {
	sizeof(struct URAUpdateConfirm__later_than_r3),
	offsetof(struct URAUpdateConfirm__later_than_r3, _asn_ctx),
	asn_MAP_later_than_r3_tag2el_9,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_later_than_r3_9 = {
	"later-than-r3",
	"later-than-r3",
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
	asn_DEF_later_than_r3_tags_9,
	sizeof(asn_DEF_later_than_r3_tags_9)
		/sizeof(asn_DEF_later_than_r3_tags_9[0]) - 1, /* 1 */
	asn_DEF_later_than_r3_tags_9,	/* Same as above */
	sizeof(asn_DEF_later_than_r3_tags_9)
		/sizeof(asn_DEF_later_than_r3_tags_9[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_later_than_r3_9,
	2,	/* Elements count */
	&asn_SPC_later_than_r3_specs_9	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_URAUpdateConfirm_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm, choice.r3),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_r3_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"r3"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct URAUpdateConfirm, choice.later_than_r3),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_later_than_r3_9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"later-than-r3"
		},
};
static asn_TYPE_tag2member_t asn_MAP_URAUpdateConfirm_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* r3 at 9920 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* later-than-r3 at 9931 */
};
static asn_CHOICE_specifics_t asn_SPC_URAUpdateConfirm_specs_1 = {
	sizeof(struct URAUpdateConfirm),
	offsetof(struct URAUpdateConfirm, _asn_ctx),
	offsetof(struct URAUpdateConfirm, present),
	sizeof(((struct URAUpdateConfirm *)0)->present),
	asn_MAP_URAUpdateConfirm_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_URAUpdateConfirm = {
	"URAUpdateConfirm",
	"URAUpdateConfirm",
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
	&asn_PER_type_URAUpdateConfirm_constr_1,
	asn_MBR_URAUpdateConfirm_1,
	2,	/* Elements count */
	&asn_SPC_URAUpdateConfirm_specs_1	/* Additional specs */
};

