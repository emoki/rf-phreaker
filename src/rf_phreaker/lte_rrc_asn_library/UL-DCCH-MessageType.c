/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/UL-DCCH-MessageType.h"

static asn_per_constraints_t asn_PER_type_c1_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_c2_constr_20 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_messageClassExtension_constr_19 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_UL_DCCH_MessageType_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_c1_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.csfbParametersRequestCDMA2000),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CSFBParametersRequestCDMA2000,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"csfbParametersRequestCDMA2000"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.measurementReport),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasurementReport,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measurementReport"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.rrcConnectionReconfigurationComplete),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RRCConnectionReconfigurationComplete,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rrcConnectionReconfigurationComplete"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.rrcConnectionReestablishmentComplete),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RRCConnectionReestablishmentComplete,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rrcConnectionReestablishmentComplete"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.rrcConnectionSetupComplete),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RRCConnectionSetupComplete,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rrcConnectionSetupComplete"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.securityModeComplete),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SecurityModeComplete,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"securityModeComplete"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.securityModeFailure),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SecurityModeFailure,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"securityModeFailure"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.ueCapabilityInformation),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UECapabilityInformation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ueCapabilityInformation"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.ulHandoverPreparationTransfer),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ULHandoverPreparationTransfer,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ulHandoverPreparationTransfer"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.ulInformationTransfer),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ULInformationTransfer,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ulInformationTransfer"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.counterCheckResponse),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CounterCheckResponse,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"counterCheckResponse"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.ueInformationResponse_r9),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UEInformationResponse_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ueInformationResponse-r9"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.proximityIndication_r9),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ProximityIndication_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"proximityIndication-r9"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.rnReconfigurationComplete_r10),
		(ASN_TAG_CLASS_CONTEXT | (13 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RNReconfigurationComplete_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rnReconfigurationComplete-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.mbmsCountingResponse_r10),
		(ASN_TAG_CLASS_CONTEXT | (14 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MBMSCountingResponse_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mbmsCountingResponse-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__c1, choice.interFreqRSTDMeasurementIndication_r10),
		(ASN_TAG_CLASS_CONTEXT | (15 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_InterFreqRSTDMeasurementIndication_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"interFreqRSTDMeasurementIndication-r10"
		},
};
static asn_TYPE_tag2member_t asn_MAP_c1_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* csfbParametersRequestCDMA2000 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* measurementReport */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* rrcConnectionReconfigurationComplete */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* rrcConnectionReestablishmentComplete */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* rrcConnectionSetupComplete */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* securityModeComplete */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* securityModeFailure */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* ueCapabilityInformation */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* ulHandoverPreparationTransfer */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* ulInformationTransfer */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* counterCheckResponse */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* ueInformationResponse-r9 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 }, /* proximityIndication-r9 */
    { (ASN_TAG_CLASS_CONTEXT | (13 << 2)), 13, 0, 0 }, /* rnReconfigurationComplete-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (14 << 2)), 14, 0, 0 }, /* mbmsCountingResponse-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (15 << 2)), 15, 0, 0 } /* interFreqRSTDMeasurementIndication-r10 */
};
static asn_CHOICE_specifics_t asn_SPC_c1_specs_2 = {
	sizeof(struct UL_DCCH_MessageType__c1),
	offsetof(struct UL_DCCH_MessageType__c1, _asn_ctx),
	offsetof(struct UL_DCCH_MessageType__c1, present),
	sizeof(((struct UL_DCCH_MessageType__c1 *)0)->present),
	asn_MAP_c1_tag2el_2,
	16,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_c1_2 = {
	"c1",
	"c1",
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
	&asn_PER_type_c1_constr_2,
	asn_MBR_c1_2,
	16,	/* Elements count */
	&asn_SPC_c1_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_c2_20[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.ueAssistanceInformation_r11),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UEAssistanceInformation_r11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ueAssistanceInformation-r11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.inDeviceCoexIndication_r11),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_InDeviceCoexIndication_r11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"inDeviceCoexIndication-r11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.mbmsInterestIndication_r11),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MBMSInterestIndication_r11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mbmsInterestIndication-r11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare13),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare13"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare12),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare12"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare11),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare10),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare9),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare9"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare8),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare8"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare7),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare7"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare6),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare6"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare5),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare5"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare4),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare4"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare3),
		(ASN_TAG_CLASS_CONTEXT | (13 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare3"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare2),
		(ASN_TAG_CLASS_CONTEXT | (14 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, choice.spare1),
		(ASN_TAG_CLASS_CONTEXT | (15 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare1"
		},
};
static asn_TYPE_tag2member_t asn_MAP_c2_tag2el_20[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ueAssistanceInformation-r11 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* inDeviceCoexIndication-r11 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* mbmsInterestIndication-r11 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* spare13 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* spare12 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* spare11 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* spare10 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* spare9 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* spare8 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* spare7 */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* spare6 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* spare5 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 }, /* spare4 */
    { (ASN_TAG_CLASS_CONTEXT | (13 << 2)), 13, 0, 0 }, /* spare3 */
    { (ASN_TAG_CLASS_CONTEXT | (14 << 2)), 14, 0, 0 }, /* spare2 */
    { (ASN_TAG_CLASS_CONTEXT | (15 << 2)), 15, 0, 0 } /* spare1 */
};
static asn_CHOICE_specifics_t asn_SPC_c2_specs_20 = {
	sizeof(struct UL_DCCH_MessageType__messageClassExtension__c2),
	offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, _asn_ctx),
	offsetof(struct UL_DCCH_MessageType__messageClassExtension__c2, present),
	sizeof(((struct UL_DCCH_MessageType__messageClassExtension__c2 *)0)->present),
	asn_MAP_c2_tag2el_20,
	16,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_c2_20 = {
	"c2",
	"c2",
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
	&asn_PER_type_c2_constr_20,
	asn_MBR_c2_20,
	16,	/* Elements count */
	&asn_SPC_c2_specs_20	/* Additional specs */
};

static ber_tlv_tag_t asn_DEF_messageClassExtensionFuture_r11_tags_37[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_messageClassExtensionFuture_r11_specs_37 = {
	sizeof(struct UL_DCCH_MessageType__messageClassExtension__messageClassExtensionFuture_r11),
	offsetof(struct UL_DCCH_MessageType__messageClassExtension__messageClassExtensionFuture_r11, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_messageClassExtensionFuture_r11_37 = {
	"messageClassExtensionFuture-r11",
	"messageClassExtensionFuture-r11",
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
	asn_DEF_messageClassExtensionFuture_r11_tags_37,
	sizeof(asn_DEF_messageClassExtensionFuture_r11_tags_37)
		/sizeof(asn_DEF_messageClassExtensionFuture_r11_tags_37[0]) - 1, /* 1 */
	asn_DEF_messageClassExtensionFuture_r11_tags_37,	/* Same as above */
	sizeof(asn_DEF_messageClassExtensionFuture_r11_tags_37)
		/sizeof(asn_DEF_messageClassExtensionFuture_r11_tags_37[0]), /* 2 */
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	&asn_SPC_messageClassExtensionFuture_r11_specs_37	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_messageClassExtension_19[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension, choice.c2),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_c2_20,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"c2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType__messageClassExtension, choice.messageClassExtensionFuture_r11),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_messageClassExtensionFuture_r11_37,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"messageClassExtensionFuture-r11"
		},
};
static asn_TYPE_tag2member_t asn_MAP_messageClassExtension_tag2el_19[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* c2 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* messageClassExtensionFuture-r11 */
};
static asn_CHOICE_specifics_t asn_SPC_messageClassExtension_specs_19 = {
	sizeof(struct UL_DCCH_MessageType__messageClassExtension),
	offsetof(struct UL_DCCH_MessageType__messageClassExtension, _asn_ctx),
	offsetof(struct UL_DCCH_MessageType__messageClassExtension, present),
	sizeof(((struct UL_DCCH_MessageType__messageClassExtension *)0)->present),
	asn_MAP_messageClassExtension_tag2el_19,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_messageClassExtension_19 = {
	"messageClassExtension",
	"messageClassExtension",
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
	&asn_PER_type_messageClassExtension_constr_19,
	asn_MBR_messageClassExtension_19,
	2,	/* Elements count */
	&asn_SPC_messageClassExtension_specs_19	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UL_DCCH_MessageType_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType, choice.c1),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_c1_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"c1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UL_DCCH_MessageType, choice.messageClassExtension),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_messageClassExtension_19,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"messageClassExtension"
		},
};
static asn_TYPE_tag2member_t asn_MAP_UL_DCCH_MessageType_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* c1 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* messageClassExtension */
};
static asn_CHOICE_specifics_t asn_SPC_UL_DCCH_MessageType_specs_1 = {
	sizeof(struct UL_DCCH_MessageType),
	offsetof(struct UL_DCCH_MessageType, _asn_ctx),
	offsetof(struct UL_DCCH_MessageType, present),
	sizeof(((struct UL_DCCH_MessageType *)0)->present),
	asn_MAP_UL_DCCH_MessageType_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_UL_DCCH_MessageType = {
	"UL-DCCH-MessageType",
	"UL-DCCH-MessageType",
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
	&asn_PER_type_UL_DCCH_MessageType_constr_1,
	asn_MBR_UL_DCCH_MessageType_1,
	2,	/* Elements count */
	&asn_SPC_UL_DCCH_MessageType_specs_1	/* Additional specs */
};

