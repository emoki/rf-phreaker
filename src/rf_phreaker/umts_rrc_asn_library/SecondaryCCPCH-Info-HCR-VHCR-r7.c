/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/SecondaryCCPCH-Info-HCR-VHCR-r7.h"

static asn_per_constraints_t asn_PER_type_modeSpecificInfo_constr_2 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_tdd384_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd384, individualTimeslotInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IndividualTimeslotInfo_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"individualTimeslotInfo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd384, channelisationCode),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SCCPCH_ChannelisationCodeList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"channelisationCode"
		},
};
static ber_tlv_tag_t asn_DEF_tdd384_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd384_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* individualTimeslotInfo at 20578 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* channelisationCode at 20580 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd384_specs_3 = {
	sizeof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd384),
	offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd384, _asn_ctx),
	asn_MAP_tdd384_tag2el_3,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd384_3 = {
	"tdd384",
	"tdd384",
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
	asn_DEF_tdd384_tags_3,
	sizeof(asn_DEF_tdd384_tags_3)
		/sizeof(asn_DEF_tdd384_tags_3[0]) - 1, /* 1 */
	asn_DEF_tdd384_tags_3,	/* Same as above */
	sizeof(asn_DEF_tdd384_tags_3)
		/sizeof(asn_DEF_tdd384_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd384_3,
	2,	/* Elements count */
	&asn_SPC_tdd384_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd768_6[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd768, individualTimeslotInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IndividualTimeslotInfo_VHCR,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"individualTimeslotInfo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd768, channelisationCode),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SCCPCH_ChannelisationCodeList_VHCR,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"channelisationCode"
		},
};
static ber_tlv_tag_t asn_DEF_tdd768_tags_6[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd768_tag2el_6[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* individualTimeslotInfo at 20582 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* channelisationCode at 20584 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd768_specs_6 = {
	sizeof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd768),
	offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo__tdd768, _asn_ctx),
	asn_MAP_tdd768_tag2el_6,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd768_6 = {
	"tdd768",
	"tdd768",
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
	asn_DEF_tdd768_tags_6,
	sizeof(asn_DEF_tdd768_tags_6)
		/sizeof(asn_DEF_tdd768_tags_6[0]) - 1, /* 1 */
	asn_DEF_tdd768_tags_6,	/* Same as above */
	sizeof(asn_DEF_tdd768_tags_6)
		/sizeof(asn_DEF_tdd768_tags_6[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd768_6,
	2,	/* Elements count */
	&asn_SPC_tdd768_specs_6	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_modeSpecificInfo_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo, choice.tdd384),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_tdd384_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd384"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo, choice.tdd768),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd768_6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd768"
		},
};
static asn_TYPE_tag2member_t asn_MAP_modeSpecificInfo_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tdd384 at 20578 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* tdd768 at 20582 */
};
static asn_CHOICE_specifics_t asn_SPC_modeSpecificInfo_specs_2 = {
	sizeof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo),
	offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo, _asn_ctx),
	offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo, present),
	sizeof(((struct SecondaryCCPCH_Info_HCR_VHCR_r7__modeSpecificInfo *)0)->present),
	asn_MAP_modeSpecificInfo_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_modeSpecificInfo_2 = {
	"modeSpecificInfo",
	"modeSpecificInfo",
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
	&asn_PER_type_modeSpecificInfo_constr_2,
	asn_MBR_modeSpecificInfo_2,
	2,	/* Elements count */
	&asn_SPC_modeSpecificInfo_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SecondaryCCPCH_Info_HCR_VHCR_r7_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7, modeSpecificInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_modeSpecificInfo_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"modeSpecificInfo"
		},
};
static ber_tlv_tag_t asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SecondaryCCPCH_Info_HCR_VHCR_r7_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* modeSpecificInfo at 20580 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SecondaryCCPCH_Info_HCR_VHCR_r7_specs_1 = {
	sizeof(struct SecondaryCCPCH_Info_HCR_VHCR_r7),
	offsetof(struct SecondaryCCPCH_Info_HCR_VHCR_r7, _asn_ctx),
	asn_MAP_SecondaryCCPCH_Info_HCR_VHCR_r7_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7 = {
	"SecondaryCCPCH-Info-HCR-VHCR-r7",
	"SecondaryCCPCH-Info-HCR-VHCR-r7",
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
	asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7_tags_1,
	sizeof(asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7_tags_1)
		/sizeof(asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7_tags_1[0]), /* 1 */
	asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7_tags_1,	/* Same as above */
	sizeof(asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7_tags_1)
		/sizeof(asn_DEF_SecondaryCCPCH_Info_HCR_VHCR_r7_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SecondaryCCPCH_Info_HCR_VHCR_r7_1,
	1,	/* Elements count */
	&asn_SPC_SecondaryCCPCH_Info_HCR_VHCR_r7_specs_1	/* Additional specs */
};

