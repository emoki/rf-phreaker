/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UL-SecondaryCellInfoFDD.h"

static asn_per_constraints_t asn_PER_type_UL_SecondaryCellInfoFDD_constr_1 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_newConfiguration_3[] = {
	{ ATF_POINTER, 3, offsetof(struct UL_SecondaryCellInfoFDD__newConfiguration, secondaryServingEDCHCell_Info),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SecondaryServingEDCHCell_Info,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"secondaryServingEDCHCell-Info"
		},
	{ ATF_POINTER, 2, offsetof(struct UL_SecondaryCellInfoFDD__newConfiguration, secondaryEDCH_Info_Common),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SecondaryEDCH_Info_Common,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"secondaryEDCH-Info-Common"
		},
	{ ATF_POINTER, 1, offsetof(struct UL_SecondaryCellInfoFDD__newConfiguration, dl_InformationPerSecondaryRL_List),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DL_InformationPerSecondaryRL_List,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dl-InformationPerSecondaryRL-List"
		},
};
static int asn_MAP_newConfiguration_oms_3[] = { 0, 1, 2 };
static ber_tlv_tag_t asn_DEF_newConfiguration_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_newConfiguration_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* secondaryServingEDCHCell-Info at 13533 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* secondaryEDCH-Info-Common at 13534 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* dl-InformationPerSecondaryRL-List at 13535 */
};
static asn_SEQUENCE_specifics_t asn_SPC_newConfiguration_specs_3 = {
	sizeof(struct UL_SecondaryCellInfoFDD__newConfiguration),
	offsetof(struct UL_SecondaryCellInfoFDD__newConfiguration, _asn_ctx),
	asn_MAP_newConfiguration_tag2el_3,
	3,	/* Count of tags in the map */
	asn_MAP_newConfiguration_oms_3,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_newConfiguration_3 = {
	"newConfiguration",
	"newConfiguration",
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
	asn_DEF_newConfiguration_tags_3,
	sizeof(asn_DEF_newConfiguration_tags_3)
		/sizeof(asn_DEF_newConfiguration_tags_3[0]) - 1, /* 1 */
	asn_DEF_newConfiguration_tags_3,	/* Same as above */
	sizeof(asn_DEF_newConfiguration_tags_3)
		/sizeof(asn_DEF_newConfiguration_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_newConfiguration_3,
	3,	/* Elements count */
	&asn_SPC_newConfiguration_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UL_SecondaryCellInfoFDD_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_SecondaryCellInfoFDD, choice.Continue),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"continue"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_SecondaryCellInfoFDD, choice.newConfiguration),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_newConfiguration_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"newConfiguration"
		},
};
static asn_TYPE_tag2member_t asn_MAP_UL_SecondaryCellInfoFDD_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* continue at 13531 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* newConfiguration at 13533 */
};
static asn_CHOICE_specifics_t asn_SPC_UL_SecondaryCellInfoFDD_specs_1 = {
	sizeof(struct UL_SecondaryCellInfoFDD),
	offsetof(struct UL_SecondaryCellInfoFDD, _asn_ctx),
	offsetof(struct UL_SecondaryCellInfoFDD, present),
	sizeof(((struct UL_SecondaryCellInfoFDD *)0)->present),
	asn_MAP_UL_SecondaryCellInfoFDD_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_UL_SecondaryCellInfoFDD = {
	"UL-SecondaryCellInfoFDD",
	"UL-SecondaryCellInfoFDD",
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
	&asn_PER_type_UL_SecondaryCellInfoFDD_constr_1,
	asn_MBR_UL_SecondaryCellInfoFDD_1,
	2,	/* Elements count */
	&asn_SPC_UL_SecondaryCellInfoFDD_specs_1	/* Additional specs */
};

