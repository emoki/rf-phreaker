/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UE-RadioAccessCapabilityInfo.h"

static asn_TYPE_member_t asn_MBR_UE_RadioAccessCapabilityInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UE_RadioAccessCapabilityInfo, ue_RadioAccessCapability),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_RadioAccessCapability,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-RadioAccessCapability"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_RadioAccessCapabilityInfo, ue_RadioAccessCapability_v370ext),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_RadioAccessCapability_v370ext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-RadioAccessCapability-v370ext"
		},
};
static ber_tlv_tag_t asn_DEF_UE_RadioAccessCapabilityInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UE_RadioAccessCapabilityInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ue-RadioAccessCapability at 13095 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* ue-RadioAccessCapability-v370ext at 13097 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UE_RadioAccessCapabilityInfo_specs_1 = {
	sizeof(struct UE_RadioAccessCapabilityInfo),
	offsetof(struct UE_RadioAccessCapabilityInfo, _asn_ctx),
	asn_MAP_UE_RadioAccessCapabilityInfo_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UE_RadioAccessCapabilityInfo = {
	"UE-RadioAccessCapabilityInfo",
	"UE-RadioAccessCapabilityInfo",
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
	asn_DEF_UE_RadioAccessCapabilityInfo_tags_1,
	sizeof(asn_DEF_UE_RadioAccessCapabilityInfo_tags_1)
		/sizeof(asn_DEF_UE_RadioAccessCapabilityInfo_tags_1[0]), /* 1 */
	asn_DEF_UE_RadioAccessCapabilityInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_UE_RadioAccessCapabilityInfo_tags_1)
		/sizeof(asn_DEF_UE_RadioAccessCapabilityInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UE_RadioAccessCapabilityInfo_1,
	2,	/* Elements count */
	&asn_SPC_UE_RadioAccessCapabilityInfo_specs_1	/* Additional specs */
};

