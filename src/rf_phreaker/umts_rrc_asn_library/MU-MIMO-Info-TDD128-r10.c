/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/MU-MIMO-Info-TDD128-r10.h"

static asn_per_constraints_t asn_PER_type_MU_MIMO_Info_TDD128_r10_constr_1 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_newOperation_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MU_MIMO_Info_TDD128_r10__newOperation, mu_MIMO_Operation),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MU_MIMO_Operation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mu-MIMO-Operation"
		},
	{ ATF_POINTER, 1, offsetof(struct MU_MIMO_Info_TDD128_r10__newOperation, standaloneMidambleInfo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_StandaloneMidambleInfo_TDD128,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"standaloneMidambleInfo"
		},
};
static int asn_MAP_newOperation_oms_3[] = { 1 };
static ber_tlv_tag_t asn_DEF_newOperation_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_newOperation_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* mu-MIMO-Operation at 19279 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* standaloneMidambleInfo at 19280 */
};
static asn_SEQUENCE_specifics_t asn_SPC_newOperation_specs_3 = {
	sizeof(struct MU_MIMO_Info_TDD128_r10__newOperation),
	offsetof(struct MU_MIMO_Info_TDD128_r10__newOperation, _asn_ctx),
	asn_MAP_newOperation_tag2el_3,
	2,	/* Count of tags in the map */
	asn_MAP_newOperation_oms_3,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_newOperation_3 = {
	"newOperation",
	"newOperation",
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
	asn_DEF_newOperation_tags_3,
	sizeof(asn_DEF_newOperation_tags_3)
		/sizeof(asn_DEF_newOperation_tags_3[0]) - 1, /* 1 */
	asn_DEF_newOperation_tags_3,	/* Same as above */
	sizeof(asn_DEF_newOperation_tags_3)
		/sizeof(asn_DEF_newOperation_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_newOperation_3,
	2,	/* Elements count */
	&asn_SPC_newOperation_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_MU_MIMO_Info_TDD128_r10_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MU_MIMO_Info_TDD128_r10, choice.Continue),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"continue"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MU_MIMO_Info_TDD128_r10, choice.newOperation),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_newOperation_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"newOperation"
		},
};
static asn_TYPE_tag2member_t asn_MAP_MU_MIMO_Info_TDD128_r10_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* continue at 19277 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* newOperation at 19279 */
};
static asn_CHOICE_specifics_t asn_SPC_MU_MIMO_Info_TDD128_r10_specs_1 = {
	sizeof(struct MU_MIMO_Info_TDD128_r10),
	offsetof(struct MU_MIMO_Info_TDD128_r10, _asn_ctx),
	offsetof(struct MU_MIMO_Info_TDD128_r10, present),
	sizeof(((struct MU_MIMO_Info_TDD128_r10 *)0)->present),
	asn_MAP_MU_MIMO_Info_TDD128_r10_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_MU_MIMO_Info_TDD128_r10 = {
	"MU-MIMO-Info-TDD128-r10",
	"MU-MIMO-Info-TDD128-r10",
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
	&asn_PER_type_MU_MIMO_Info_TDD128_r10_constr_1,
	asn_MBR_MU_MIMO_Info_TDD128_r10_1,
	2,	/* Elements count */
	&asn_SPC_MU_MIMO_Info_TDD128_r10_specs_1	/* Additional specs */
};

