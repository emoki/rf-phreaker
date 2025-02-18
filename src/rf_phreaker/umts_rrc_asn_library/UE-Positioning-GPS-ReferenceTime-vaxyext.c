/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UE-Positioning-GPS-ReferenceTime-vaxyext.h"

static int
memb_gps_Week_Cycle_Number_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 7)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_gps_Week_Cycle_Number_constr_2 = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_UE_Positioning_GPS_ReferenceTime_vaxyext_1[] = {
	{ ATF_POINTER, 1, offsetof(struct UE_Positioning_GPS_ReferenceTime_vaxyext, gps_Week_Cycle_Number),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_gps_Week_Cycle_Number_constraint_1,
		&asn_PER_memb_gps_Week_Cycle_Number_constr_2,
		0,
		"gps-Week-Cycle-Number"
		},
};
static int asn_MAP_UE_Positioning_GPS_ReferenceTime_vaxyext_oms_1[] = { 0 };
static ber_tlv_tag_t asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UE_Positioning_GPS_ReferenceTime_vaxyext_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* gps-Week-Cycle-Number at 28002 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UE_Positioning_GPS_ReferenceTime_vaxyext_specs_1 = {
	sizeof(struct UE_Positioning_GPS_ReferenceTime_vaxyext),
	offsetof(struct UE_Positioning_GPS_ReferenceTime_vaxyext, _asn_ctx),
	asn_MAP_UE_Positioning_GPS_ReferenceTime_vaxyext_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_UE_Positioning_GPS_ReferenceTime_vaxyext_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext = {
	"UE-Positioning-GPS-ReferenceTime-vaxyext",
	"UE-Positioning-GPS-ReferenceTime-vaxyext",
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
	asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext_tags_1,
	sizeof(asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext_tags_1)
		/sizeof(asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext_tags_1[0]), /* 1 */
	asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext_tags_1,	/* Same as above */
	sizeof(asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext_tags_1)
		/sizeof(asn_DEF_UE_Positioning_GPS_ReferenceTime_vaxyext_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UE_Positioning_GPS_ReferenceTime_vaxyext_1,
	1,	/* Elements count */
	&asn_SPC_UE_Positioning_GPS_ReferenceTime_vaxyext_specs_1	/* Additional specs */
};

