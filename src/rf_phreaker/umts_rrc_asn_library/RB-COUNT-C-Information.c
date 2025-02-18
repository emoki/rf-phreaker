/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/RB-COUNT-C-Information.h"

static asn_TYPE_member_t asn_MBR_RB_COUNT_C_Information_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RB_COUNT_C_Information, rb_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RB_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rb-Identity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RB_COUNT_C_Information, count_C_UL),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_COUNT_C,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"count-C-UL"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RB_COUNT_C_Information, count_C_DL),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_COUNT_C,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"count-C-DL"
		},
};
static ber_tlv_tag_t asn_DEF_RB_COUNT_C_Information_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_RB_COUNT_C_Information_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rb-Identity at 14175 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* count-C-UL at 14176 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* count-C-DL at 14178 */
};
static asn_SEQUENCE_specifics_t asn_SPC_RB_COUNT_C_Information_specs_1 = {
	sizeof(struct RB_COUNT_C_Information),
	offsetof(struct RB_COUNT_C_Information, _asn_ctx),
	asn_MAP_RB_COUNT_C_Information_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_RB_COUNT_C_Information = {
	"RB-COUNT-C-Information",
	"RB-COUNT-C-Information",
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
	asn_DEF_RB_COUNT_C_Information_tags_1,
	sizeof(asn_DEF_RB_COUNT_C_Information_tags_1)
		/sizeof(asn_DEF_RB_COUNT_C_Information_tags_1[0]), /* 1 */
	asn_DEF_RB_COUNT_C_Information_tags_1,	/* Same as above */
	sizeof(asn_DEF_RB_COUNT_C_Information_tags_1)
		/sizeof(asn_DEF_RB_COUNT_C_Information_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_RB_COUNT_C_Information_1,
	3,	/* Elements count */
	&asn_SPC_RB_COUNT_C_Information_specs_1	/* Additional specs */
};

