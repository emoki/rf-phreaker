/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/RB-InformationChanged-r6.h"

static asn_per_constraints_t asn_PER_type_rb_Change_constr_3 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_rb_Change_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RB_InformationChanged_r6__rb_Change, choice.release),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"release"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RB_InformationChanged_r6__rb_Change, choice.re_mapToDefaultRb),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RB_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"re-mapToDefaultRb"
		},
};
static asn_TYPE_tag2member_t asn_MAP_rb_Change_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* release at 14240 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* re-mapToDefaultRb at 14242 */
};
static asn_CHOICE_specifics_t asn_SPC_rb_Change_specs_3 = {
	sizeof(struct RB_InformationChanged_r6__rb_Change),
	offsetof(struct RB_InformationChanged_r6__rb_Change, _asn_ctx),
	offsetof(struct RB_InformationChanged_r6__rb_Change, present),
	sizeof(((struct RB_InformationChanged_r6__rb_Change *)0)->present),
	asn_MAP_rb_Change_tag2el_3,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_rb_Change_3 = {
	"rb-Change",
	"rb-Change",
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
	&asn_PER_type_rb_Change_constr_3,
	asn_MBR_rb_Change_3,
	2,	/* Elements count */
	&asn_SPC_rb_Change_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_RB_InformationChanged_r6_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RB_InformationChanged_r6, rb_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RB_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rb-Identity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RB_InformationChanged_r6, rb_Change),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_rb_Change_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rb-Change"
		},
};
static ber_tlv_tag_t asn_DEF_RB_InformationChanged_r6_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_RB_InformationChanged_r6_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rb-Identity at 14238 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* rb-Change at 14240 */
};
static asn_SEQUENCE_specifics_t asn_SPC_RB_InformationChanged_r6_specs_1 = {
	sizeof(struct RB_InformationChanged_r6),
	offsetof(struct RB_InformationChanged_r6, _asn_ctx),
	asn_MAP_RB_InformationChanged_r6_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_RB_InformationChanged_r6 = {
	"RB-InformationChanged-r6",
	"RB-InformationChanged-r6",
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
	asn_DEF_RB_InformationChanged_r6_tags_1,
	sizeof(asn_DEF_RB_InformationChanged_r6_tags_1)
		/sizeof(asn_DEF_RB_InformationChanged_r6_tags_1[0]), /* 1 */
	asn_DEF_RB_InformationChanged_r6_tags_1,	/* Same as above */
	sizeof(asn_DEF_RB_InformationChanged_r6_tags_1)
		/sizeof(asn_DEF_RB_InformationChanged_r6_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_RB_InformationChanged_r6_1,
	2,	/* Elements count */
	&asn_SPC_RB_InformationChanged_r6_specs_1	/* Additional specs */
};

