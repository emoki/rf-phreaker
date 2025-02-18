/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/IntegrityProtectionModeCommand.h"

static asn_per_constraints_t asn_PER_type_IntegrityProtectionModeCommand_constr_1 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_startIntegrityProtection_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IntegrityProtectionModeCommand__startIntegrityProtection, integrityProtInitNumber),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IntegrityProtInitNumber,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"integrityProtInitNumber"
		},
};
static ber_tlv_tag_t asn_DEF_startIntegrityProtection_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_startIntegrityProtection_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* integrityProtInitNumber at 11809 */
};
static asn_SEQUENCE_specifics_t asn_SPC_startIntegrityProtection_specs_2 = {
	sizeof(struct IntegrityProtectionModeCommand__startIntegrityProtection),
	offsetof(struct IntegrityProtectionModeCommand__startIntegrityProtection, _asn_ctx),
	asn_MAP_startIntegrityProtection_tag2el_2,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_startIntegrityProtection_2 = {
	"startIntegrityProtection",
	"startIntegrityProtection",
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
	asn_DEF_startIntegrityProtection_tags_2,
	sizeof(asn_DEF_startIntegrityProtection_tags_2)
		/sizeof(asn_DEF_startIntegrityProtection_tags_2[0]) - 1, /* 1 */
	asn_DEF_startIntegrityProtection_tags_2,	/* Same as above */
	sizeof(asn_DEF_startIntegrityProtection_tags_2)
		/sizeof(asn_DEF_startIntegrityProtection_tags_2[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_startIntegrityProtection_2,
	1,	/* Elements count */
	&asn_SPC_startIntegrityProtection_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_modify_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IntegrityProtectionModeCommand__modify, dl_IntegrityProtActivationInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IntegrityProtActivationInfo,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dl-IntegrityProtActivationInfo"
		},
};
static ber_tlv_tag_t asn_DEF_modify_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_modify_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* dl-IntegrityProtActivationInfo at 11812 */
};
static asn_SEQUENCE_specifics_t asn_SPC_modify_specs_4 = {
	sizeof(struct IntegrityProtectionModeCommand__modify),
	offsetof(struct IntegrityProtectionModeCommand__modify, _asn_ctx),
	asn_MAP_modify_tag2el_4,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_modify_4 = {
	"modify",
	"modify",
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
	asn_DEF_modify_tags_4,
	sizeof(asn_DEF_modify_tags_4)
		/sizeof(asn_DEF_modify_tags_4[0]) - 1, /* 1 */
	asn_DEF_modify_tags_4,	/* Same as above */
	sizeof(asn_DEF_modify_tags_4)
		/sizeof(asn_DEF_modify_tags_4[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_modify_4,
	1,	/* Elements count */
	&asn_SPC_modify_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_IntegrityProtectionModeCommand_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IntegrityProtectionModeCommand, choice.startIntegrityProtection),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_startIntegrityProtection_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"startIntegrityProtection"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IntegrityProtectionModeCommand, choice.modify),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_modify_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"modify"
		},
};
static asn_TYPE_tag2member_t asn_MAP_IntegrityProtectionModeCommand_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* startIntegrityProtection at 11809 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* modify at 11812 */
};
static asn_CHOICE_specifics_t asn_SPC_IntegrityProtectionModeCommand_specs_1 = {
	sizeof(struct IntegrityProtectionModeCommand),
	offsetof(struct IntegrityProtectionModeCommand, _asn_ctx),
	offsetof(struct IntegrityProtectionModeCommand, present),
	sizeof(((struct IntegrityProtectionModeCommand *)0)->present),
	asn_MAP_IntegrityProtectionModeCommand_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_IntegrityProtectionModeCommand = {
	"IntegrityProtectionModeCommand",
	"IntegrityProtectionModeCommand",
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
	&asn_PER_type_IntegrityProtectionModeCommand_constr_1,
	asn_MBR_IntegrityProtectionModeCommand_1,
	2,	/* Elements count */
	&asn_SPC_IntegrityProtectionModeCommand_specs_1	/* Additional specs */
};

