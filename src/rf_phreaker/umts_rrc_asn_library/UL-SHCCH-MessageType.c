/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Class-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UL-SHCCH-MessageType.h"

static asn_per_constraints_t asn_PER_type_UL_SHCCH_MessageType_constr_1 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_UL_SHCCH_MessageType_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_SHCCH_MessageType, choice.puschCapacityRequest),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PUSCHCapacityRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"puschCapacityRequest"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_SHCCH_MessageType, choice.spare),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare"
		},
};
static asn_TYPE_tag2member_t asn_MAP_UL_SHCCH_MessageType_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* puschCapacityRequest at 294 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* spare at 295 */
};
static asn_CHOICE_specifics_t asn_SPC_UL_SHCCH_MessageType_specs_1 = {
	sizeof(struct UL_SHCCH_MessageType),
	offsetof(struct UL_SHCCH_MessageType, _asn_ctx),
	offsetof(struct UL_SHCCH_MessageType, present),
	sizeof(((struct UL_SHCCH_MessageType *)0)->present),
	asn_MAP_UL_SHCCH_MessageType_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_UL_SHCCH_MessageType = {
	"UL-SHCCH-MessageType",
	"UL-SHCCH-MessageType",
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
	&asn_PER_type_UL_SHCCH_MessageType_constr_1,
	asn_MBR_UL_SHCCH_MessageType_1,
	2,	/* Elements count */
	&asn_SPC_UL_SHCCH_MessageType_specs_1	/* Additional specs */
};

