/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/MBMS-CommonRBInformation-r6.h"

static asn_TYPE_member_t asn_MBR_MBMS_CommonRBInformation_r6_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MBMS_CommonRBInformation_r6, commonRBIdentity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MBMS_CommonRBIdentity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"commonRBIdentity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MBMS_CommonRBInformation_r6, pdcp_Info),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PDCP_Info_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pdcp-Info"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MBMS_CommonRBInformation_r6, rlc_Info),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RLC_Info_MTCH_r6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rlc-Info"
		},
};
static ber_tlv_tag_t asn_DEF_MBMS_CommonRBInformation_r6_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_MBMS_CommonRBInformation_r6_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* commonRBIdentity at 30544 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* pdcp-Info at 30545 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* rlc-Info at 30547 */
};
static asn_SEQUENCE_specifics_t asn_SPC_MBMS_CommonRBInformation_r6_specs_1 = {
	sizeof(struct MBMS_CommonRBInformation_r6),
	offsetof(struct MBMS_CommonRBInformation_r6, _asn_ctx),
	asn_MAP_MBMS_CommonRBInformation_r6_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_MBMS_CommonRBInformation_r6 = {
	"MBMS-CommonRBInformation-r6",
	"MBMS-CommonRBInformation-r6",
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
	asn_DEF_MBMS_CommonRBInformation_r6_tags_1,
	sizeof(asn_DEF_MBMS_CommonRBInformation_r6_tags_1)
		/sizeof(asn_DEF_MBMS_CommonRBInformation_r6_tags_1[0]), /* 1 */
	asn_DEF_MBMS_CommonRBInformation_r6_tags_1,	/* Same as above */
	sizeof(asn_DEF_MBMS_CommonRBInformation_r6_tags_1)
		/sizeof(asn_DEF_MBMS_CommonRBInformation_r6_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_MBMS_CommonRBInformation_r6_1,
	3,	/* Elements count */
	&asn_SPC_MBMS_CommonRBInformation_r6_specs_1	/* Additional specs */
};

