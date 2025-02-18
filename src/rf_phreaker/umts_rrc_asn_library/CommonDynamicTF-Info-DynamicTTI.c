/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/CommonDynamicTF-Info-DynamicTTI.h"

static asn_per_constraints_t asn_PER_type_commonTDD_Choice_constr_2 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_commonTDD_Choice_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CommonDynamicTF_Info_DynamicTTI__commonTDD_Choice, choice.bitModeRLC_SizeInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_BitModeRLC_SizeInfo,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"bitModeRLC-SizeInfo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CommonDynamicTF_Info_DynamicTTI__commonTDD_Choice, choice.octetModeRLC_SizeInfoType1),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_OctetModeRLC_SizeInfoType1,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"octetModeRLC-SizeInfoType1"
		},
};
static asn_TYPE_tag2member_t asn_MAP_commonTDD_Choice_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* bitModeRLC-SizeInfo at 14977 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* octetModeRLC-SizeInfoType1 at 14979 */
};
static asn_CHOICE_specifics_t asn_SPC_commonTDD_Choice_specs_2 = {
	sizeof(struct CommonDynamicTF_Info_DynamicTTI__commonTDD_Choice),
	offsetof(struct CommonDynamicTF_Info_DynamicTTI__commonTDD_Choice, _asn_ctx),
	offsetof(struct CommonDynamicTF_Info_DynamicTTI__commonTDD_Choice, present),
	sizeof(((struct CommonDynamicTF_Info_DynamicTTI__commonTDD_Choice *)0)->present),
	asn_MAP_commonTDD_Choice_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_commonTDD_Choice_2 = {
	"commonTDD-Choice",
	"commonTDD-Choice",
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
	&asn_PER_type_commonTDD_Choice_constr_2,
	asn_MBR_commonTDD_Choice_2,
	2,	/* Elements count */
	&asn_SPC_commonTDD_Choice_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_CommonDynamicTF_Info_DynamicTTI_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CommonDynamicTF_Info_DynamicTTI, commonTDD_Choice),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_commonTDD_Choice_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"commonTDD-Choice"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CommonDynamicTF_Info_DynamicTTI, numberOfTbSizeAndTTIList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NumberOfTbSizeAndTTIList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"numberOfTbSizeAndTTIList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CommonDynamicTF_Info_DynamicTTI, logicalChannelList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_LogicalChannelList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"logicalChannelList"
		},
};
static ber_tlv_tag_t asn_DEF_CommonDynamicTF_Info_DynamicTTI_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_CommonDynamicTF_Info_DynamicTTI_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* commonTDD-Choice at 14977 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* numberOfTbSizeAndTTIList at 14980 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* logicalChannelList at 14982 */
};
static asn_SEQUENCE_specifics_t asn_SPC_CommonDynamicTF_Info_DynamicTTI_specs_1 = {
	sizeof(struct CommonDynamicTF_Info_DynamicTTI),
	offsetof(struct CommonDynamicTF_Info_DynamicTTI, _asn_ctx),
	asn_MAP_CommonDynamicTF_Info_DynamicTTI_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_CommonDynamicTF_Info_DynamicTTI = {
	"CommonDynamicTF-Info-DynamicTTI",
	"CommonDynamicTF-Info-DynamicTTI",
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
	asn_DEF_CommonDynamicTF_Info_DynamicTTI_tags_1,
	sizeof(asn_DEF_CommonDynamicTF_Info_DynamicTTI_tags_1)
		/sizeof(asn_DEF_CommonDynamicTF_Info_DynamicTTI_tags_1[0]), /* 1 */
	asn_DEF_CommonDynamicTF_Info_DynamicTTI_tags_1,	/* Same as above */
	sizeof(asn_DEF_CommonDynamicTF_Info_DynamicTTI_tags_1)
		/sizeof(asn_DEF_CommonDynamicTF_Info_DynamicTTI_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CommonDynamicTF_Info_DynamicTTI_1,
	3,	/* Elements count */
	&asn_SPC_CommonDynamicTF_Info_DynamicTTI_specs_1	/* Additional specs */
};

