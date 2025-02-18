/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UE-Positioning-GPS-DGPS-Corrections.h"

static asn_TYPE_member_t asn_MBR_UE_Positioning_GPS_DGPS_Corrections_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Positioning_GPS_DGPS_Corrections, gps_TOW),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GPS_TOW_1sec,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"gps-TOW"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Positioning_GPS_DGPS_Corrections, statusHealth),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DiffCorrectionStatus,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"statusHealth"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Positioning_GPS_DGPS_Corrections, dgps_CorrectionSatInfoList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DGPS_CorrectionSatInfoList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dgps-CorrectionSatInfoList"
		},
};
static ber_tlv_tag_t asn_DEF_UE_Positioning_GPS_DGPS_Corrections_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UE_Positioning_GPS_DGPS_Corrections_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* gps-TOW at 27911 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* statusHealth at 27912 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* dgps-CorrectionSatInfoList at 27914 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UE_Positioning_GPS_DGPS_Corrections_specs_1 = {
	sizeof(struct UE_Positioning_GPS_DGPS_Corrections),
	offsetof(struct UE_Positioning_GPS_DGPS_Corrections, _asn_ctx),
	asn_MAP_UE_Positioning_GPS_DGPS_Corrections_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UE_Positioning_GPS_DGPS_Corrections = {
	"UE-Positioning-GPS-DGPS-Corrections",
	"UE-Positioning-GPS-DGPS-Corrections",
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
	asn_DEF_UE_Positioning_GPS_DGPS_Corrections_tags_1,
	sizeof(asn_DEF_UE_Positioning_GPS_DGPS_Corrections_tags_1)
		/sizeof(asn_DEF_UE_Positioning_GPS_DGPS_Corrections_tags_1[0]), /* 1 */
	asn_DEF_UE_Positioning_GPS_DGPS_Corrections_tags_1,	/* Same as above */
	sizeof(asn_DEF_UE_Positioning_GPS_DGPS_Corrections_tags_1)
		/sizeof(asn_DEF_UE_Positioning_GPS_DGPS_Corrections_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UE_Positioning_GPS_DGPS_Corrections_1,
	3,	/* Elements count */
	&asn_SPC_UE_Positioning_GPS_DGPS_Corrections_specs_1	/* Additional specs */
};

