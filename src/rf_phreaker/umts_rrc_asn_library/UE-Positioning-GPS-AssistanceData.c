/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UE-Positioning-GPS-AssistanceData.h"

static asn_TYPE_member_t asn_MBR_UE_Positioning_GPS_AssistanceData_1[] = {
	{ ATF_POINTER, 10, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_ReferenceTime),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_ReferenceTime,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-ReferenceTime"
		},
	{ ATF_POINTER, 9, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_ReferenceLocation),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferenceLocation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-ReferenceLocation"
		},
	{ ATF_POINTER, 8, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_DGPS_Corrections),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_DGPS_Corrections,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-DGPS-Corrections"
		},
	{ ATF_POINTER, 7, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_NavigationModel),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_NavigationModel,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-NavigationModel"
		},
	{ ATF_POINTER, 6, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_IonosphericModel),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_IonosphericModel,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-IonosphericModel"
		},
	{ ATF_POINTER, 5, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_UTC_Model),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_UTC_Model,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-UTC-Model"
		},
	{ ATF_POINTER, 4, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_Almanac),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_Almanac,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-Almanac"
		},
	{ ATF_POINTER, 3, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_AcquisitionAssistance),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_AcquisitionAssistance,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-AcquisitionAssistance"
		},
	{ ATF_POINTER, 2, offsetof(struct UE_Positioning_GPS_AssistanceData, ue_positioning_GPS_Real_timeIntegrity),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BadSatList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-GPS-Real-timeIntegrity"
		},
	{ ATF_POINTER, 1, offsetof(struct UE_Positioning_GPS_AssistanceData, dummy),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_Positioning_GPS_ReferenceCellInfo,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dummy"
		},
};
static int asn_MAP_UE_Positioning_GPS_AssistanceData_oms_1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static ber_tlv_tag_t asn_DEF_UE_Positioning_GPS_AssistanceData_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UE_Positioning_GPS_AssistanceData_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ue-positioning-GPS-ReferenceTime at 27837 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ue-positioning-GPS-ReferenceLocation at 27838 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* ue-positioning-GPS-DGPS-Corrections at 27839 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* ue-positioning-GPS-NavigationModel at 27840 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* ue-positioning-GPS-IonosphericModel at 27841 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* ue-positioning-GPS-UTC-Model at 27842 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* ue-positioning-GPS-Almanac at 27843 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* ue-positioning-GPS-AcquisitionAssistance at 27845 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* ue-positioning-GPS-Real-timeIntegrity at 27846 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 } /* dummy at 27849 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UE_Positioning_GPS_AssistanceData_specs_1 = {
	sizeof(struct UE_Positioning_GPS_AssistanceData),
	offsetof(struct UE_Positioning_GPS_AssistanceData, _asn_ctx),
	asn_MAP_UE_Positioning_GPS_AssistanceData_tag2el_1,
	10,	/* Count of tags in the map */
	asn_MAP_UE_Positioning_GPS_AssistanceData_oms_1,	/* Optional members */
	10, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UE_Positioning_GPS_AssistanceData = {
	"UE-Positioning-GPS-AssistanceData",
	"UE-Positioning-GPS-AssistanceData",
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
	asn_DEF_UE_Positioning_GPS_AssistanceData_tags_1,
	sizeof(asn_DEF_UE_Positioning_GPS_AssistanceData_tags_1)
		/sizeof(asn_DEF_UE_Positioning_GPS_AssistanceData_tags_1[0]), /* 1 */
	asn_DEF_UE_Positioning_GPS_AssistanceData_tags_1,	/* Same as above */
	sizeof(asn_DEF_UE_Positioning_GPS_AssistanceData_tags_1)
		/sizeof(asn_DEF_UE_Positioning_GPS_AssistanceData_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UE_Positioning_GPS_AssistanceData_1,
	10,	/* Elements count */
	&asn_SPC_UE_Positioning_GPS_AssistanceData_specs_1	/* Additional specs */
};

