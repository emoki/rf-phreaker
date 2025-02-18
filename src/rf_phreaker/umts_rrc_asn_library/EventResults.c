/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/EventResults.h"

static asn_per_constraints_t asn_PER_type_EventResults_constr_1 = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_EventResults_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.intraFreqEventResults),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IntraFreqEventResults,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"intraFreqEventResults"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.interFreqEventResults),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_InterFreqEventResults,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"interFreqEventResults"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.interRATEventResults),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_InterRATEventResults,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"interRATEventResults"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.trafficVolumeEventResults),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TrafficVolumeEventResults,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"trafficVolumeEventResults"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.qualityEventResults),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_QualityEventResults,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"qualityEventResults"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.ue_InternalEventResults),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_UE_InternalEventResults,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-InternalEventResults"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.ue_positioning_MeasurementEventResults),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_UE_Positioning_MeasurementEventResults,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-positioning-MeasurementEventResults"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EventResults, choice.spare),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spare"
		},
};
static asn_TYPE_tag2member_t asn_MAP_EventResults_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* intraFreqEventResults at 23471 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* interFreqEventResults at 23472 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* interRATEventResults at 23473 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* trafficVolumeEventResults at 23474 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* qualityEventResults at 23475 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* ue-InternalEventResults at 23476 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* ue-positioning-MeasurementEventResults at 23477 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* spare at 23478 */
};
static asn_CHOICE_specifics_t asn_SPC_EventResults_specs_1 = {
	sizeof(struct EventResults),
	offsetof(struct EventResults, _asn_ctx),
	offsetof(struct EventResults, present),
	sizeof(((struct EventResults *)0)->present),
	asn_MAP_EventResults_tag2el_1,
	8,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_EventResults = {
	"EventResults",
	"EventResults",
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
	&asn_PER_type_EventResults_constr_1,
	asn_MBR_EventResults_1,
	8,	/* Elements count */
	&asn_SPC_EventResults_specs_1	/* Additional specs */
};

