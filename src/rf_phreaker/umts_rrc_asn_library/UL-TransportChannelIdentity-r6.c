/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UL-TransportChannelIdentity-r6.h"

static asn_per_constraints_t asn_PER_type_UL_TransportChannelIdentity_r6_constr_1 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_dch_usch_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TransportChannelIdentity_r6__dch_usch, ul_TransportChannelType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UL_TrCH_Type,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-TransportChannelType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TransportChannelIdentity_r6__dch_usch, ul_TransportChannelIdentity),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TransportChannelIdentity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-TransportChannelIdentity"
		},
};
static ber_tlv_tag_t asn_DEF_dch_usch_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_dch_usch_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ul-TransportChannelType at 15872 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* ul-TransportChannelIdentity at 15874 */
};
static asn_SEQUENCE_specifics_t asn_SPC_dch_usch_specs_2 = {
	sizeof(struct UL_TransportChannelIdentity_r6__dch_usch),
	offsetof(struct UL_TransportChannelIdentity_r6__dch_usch, _asn_ctx),
	asn_MAP_dch_usch_tag2el_2,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_dch_usch_2 = {
	"dch-usch",
	"dch-usch",
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
	asn_DEF_dch_usch_tags_2,
	sizeof(asn_DEF_dch_usch_tags_2)
		/sizeof(asn_DEF_dch_usch_tags_2[0]) - 1, /* 1 */
	asn_DEF_dch_usch_tags_2,	/* Same as above */
	sizeof(asn_DEF_dch_usch_tags_2)
		/sizeof(asn_DEF_dch_usch_tags_2[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_dch_usch_2,
	2,	/* Elements count */
	&asn_SPC_dch_usch_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UL_TransportChannelIdentity_r6_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TransportChannelIdentity_r6, choice.dch_usch),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_dch_usch_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dch-usch"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_TransportChannelIdentity_r6, choice.e_dch),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_DCH_MAC_d_FlowIdentity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"e-dch"
		},
};
static asn_TYPE_tag2member_t asn_MAP_UL_TransportChannelIdentity_r6_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* dch-usch at 15872 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* e-dch at 15876 */
};
static asn_CHOICE_specifics_t asn_SPC_UL_TransportChannelIdentity_r6_specs_1 = {
	sizeof(struct UL_TransportChannelIdentity_r6),
	offsetof(struct UL_TransportChannelIdentity_r6, _asn_ctx),
	offsetof(struct UL_TransportChannelIdentity_r6, present),
	sizeof(((struct UL_TransportChannelIdentity_r6 *)0)->present),
	asn_MAP_UL_TransportChannelIdentity_r6_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_UL_TransportChannelIdentity_r6 = {
	"UL-TransportChannelIdentity-r6",
	"UL-TransportChannelIdentity-r6",
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
	&asn_PER_type_UL_TransportChannelIdentity_r6_constr_1,
	asn_MBR_UL_TransportChannelIdentity_r6_1,
	2,	/* Elements count */
	&asn_SPC_UL_TransportChannelIdentity_r6_specs_1	/* Additional specs */
};

