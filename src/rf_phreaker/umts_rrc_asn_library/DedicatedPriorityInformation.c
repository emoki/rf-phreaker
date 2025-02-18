/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/DedicatedPriorityInformation.h"

static asn_per_constraints_t asn_PER_type_action_constr_2 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_configureDedicatedPriorities_4[] = {
	{ ATF_POINTER, 2, offsetof(struct DedicatedPriorityInformation__action__configureDedicatedPriorities, t_322),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_T_322,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"t-322"
		},
	{ ATF_POINTER, 1, offsetof(struct DedicatedPriorityInformation__action__configureDedicatedPriorities, priorityLevelList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PriorityLevelList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"priorityLevelList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DedicatedPriorityInformation__action__configureDedicatedPriorities, eutraDetection),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"eutraDetection"
		},
};
static int asn_MAP_configureDedicatedPriorities_oms_4[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_configureDedicatedPriorities_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_configureDedicatedPriorities_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* t-322 at 11124 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* priorityLevelList at 11125 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* eutraDetection at 11126 */
};
static asn_SEQUENCE_specifics_t asn_SPC_configureDedicatedPriorities_specs_4 = {
	sizeof(struct DedicatedPriorityInformation__action__configureDedicatedPriorities),
	offsetof(struct DedicatedPriorityInformation__action__configureDedicatedPriorities, _asn_ctx),
	asn_MAP_configureDedicatedPriorities_tag2el_4,
	3,	/* Count of tags in the map */
	asn_MAP_configureDedicatedPriorities_oms_4,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_configureDedicatedPriorities_4 = {
	"configureDedicatedPriorities",
	"configureDedicatedPriorities",
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
	asn_DEF_configureDedicatedPriorities_tags_4,
	sizeof(asn_DEF_configureDedicatedPriorities_tags_4)
		/sizeof(asn_DEF_configureDedicatedPriorities_tags_4[0]) - 1, /* 1 */
	asn_DEF_configureDedicatedPriorities_tags_4,	/* Same as above */
	sizeof(asn_DEF_configureDedicatedPriorities_tags_4)
		/sizeof(asn_DEF_configureDedicatedPriorities_tags_4[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_configureDedicatedPriorities_4,
	3,	/* Elements count */
	&asn_SPC_configureDedicatedPriorities_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_action_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DedicatedPriorityInformation__action, choice.clearDedicatedPriorities),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"clearDedicatedPriorities"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DedicatedPriorityInformation__action, choice.configureDedicatedPriorities),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_configureDedicatedPriorities_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"configureDedicatedPriorities"
		},
};
static asn_TYPE_tag2member_t asn_MAP_action_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* clearDedicatedPriorities at 11122 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* configureDedicatedPriorities at 11124 */
};
static asn_CHOICE_specifics_t asn_SPC_action_specs_2 = {
	sizeof(struct DedicatedPriorityInformation__action),
	offsetof(struct DedicatedPriorityInformation__action, _asn_ctx),
	offsetof(struct DedicatedPriorityInformation__action, present),
	sizeof(((struct DedicatedPriorityInformation__action *)0)->present),
	asn_MAP_action_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_action_2 = {
	"action",
	"action",
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
	&asn_PER_type_action_constr_2,
	asn_MBR_action_2,
	2,	/* Elements count */
	&asn_SPC_action_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_DedicatedPriorityInformation_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DedicatedPriorityInformation, action),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_action_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"action"
		},
};
static ber_tlv_tag_t asn_DEF_DedicatedPriorityInformation_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_DedicatedPriorityInformation_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* action at 11122 */
};
static asn_SEQUENCE_specifics_t asn_SPC_DedicatedPriorityInformation_specs_1 = {
	sizeof(struct DedicatedPriorityInformation),
	offsetof(struct DedicatedPriorityInformation, _asn_ctx),
	asn_MAP_DedicatedPriorityInformation_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_DedicatedPriorityInformation = {
	"DedicatedPriorityInformation",
	"DedicatedPriorityInformation",
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
	asn_DEF_DedicatedPriorityInformation_tags_1,
	sizeof(asn_DEF_DedicatedPriorityInformation_tags_1)
		/sizeof(asn_DEF_DedicatedPriorityInformation_tags_1[0]), /* 1 */
	asn_DEF_DedicatedPriorityInformation_tags_1,	/* Same as above */
	sizeof(asn_DEF_DedicatedPriorityInformation_tags_1)
		/sizeof(asn_DEF_DedicatedPriorityInformation_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_DedicatedPriorityInformation_1,
	1,	/* Elements count */
	&asn_SPC_DedicatedPriorityInformation_specs_1	/* Additional specs */
};

