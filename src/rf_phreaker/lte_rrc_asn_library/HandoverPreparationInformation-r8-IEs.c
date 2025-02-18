/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-InterNodeDefinitions"
 * 	found in "EUTRA-InterNodeDefinitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/HandoverPreparationInformation-r8-IEs.h"

static asn_TYPE_member_t asn_MBR_HandoverPreparationInformation_r8_IEs_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct HandoverPreparationInformation_r8_IEs, ue_RadioAccessCapabilityInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_CapabilityRAT_ContainerList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-RadioAccessCapabilityInfo"
		},
	{ ATF_POINTER, 4, offsetof(struct HandoverPreparationInformation_r8_IEs, as_Config),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AS_Config,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"as-Config"
		},
	{ ATF_POINTER, 3, offsetof(struct HandoverPreparationInformation_r8_IEs, rrm_Config),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RRM_Config,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rrm-Config"
		},
	{ ATF_POINTER, 2, offsetof(struct HandoverPreparationInformation_r8_IEs, as_Context),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AS_Context,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"as-Context"
		},
	{ ATF_POINTER, 1, offsetof(struct HandoverPreparationInformation_r8_IEs, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HandoverPreparationInformation_v920_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtension"
		},
};
static int asn_MAP_HandoverPreparationInformation_r8_IEs_oms_1[] = { 1, 2, 3, 4 };
static ber_tlv_tag_t asn_DEF_HandoverPreparationInformation_r8_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_HandoverPreparationInformation_r8_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ue-RadioAccessCapabilityInfo */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* as-Config */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* rrm-Config */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* as-Context */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* nonCriticalExtension */
};
static asn_SEQUENCE_specifics_t asn_SPC_HandoverPreparationInformation_r8_IEs_specs_1 = {
	sizeof(struct HandoverPreparationInformation_r8_IEs),
	offsetof(struct HandoverPreparationInformation_r8_IEs, _asn_ctx),
	asn_MAP_HandoverPreparationInformation_r8_IEs_tag2el_1,
	5,	/* Count of tags in the map */
	asn_MAP_HandoverPreparationInformation_r8_IEs_oms_1,	/* Optional members */
	4, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_HandoverPreparationInformation_r8_IEs = {
	"HandoverPreparationInformation-r8-IEs",
	"HandoverPreparationInformation-r8-IEs",
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
	asn_DEF_HandoverPreparationInformation_r8_IEs_tags_1,
	sizeof(asn_DEF_HandoverPreparationInformation_r8_IEs_tags_1)
		/sizeof(asn_DEF_HandoverPreparationInformation_r8_IEs_tags_1[0]), /* 1 */
	asn_DEF_HandoverPreparationInformation_r8_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_HandoverPreparationInformation_r8_IEs_tags_1)
		/sizeof(asn_DEF_HandoverPreparationInformation_r8_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_HandoverPreparationInformation_r8_IEs_1,
	5,	/* Elements count */
	&asn_SPC_HandoverPreparationInformation_r8_IEs_specs_1	/* Additional specs */
};

