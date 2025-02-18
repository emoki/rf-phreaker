/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/MeasurementCapabilityExt2.h"

static asn_TYPE_member_t asn_MBR_MeasurementCapabilityExt2_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasurementCapabilityExt2, compressedModeMeasCapabFDDList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CompressedModeMeasCapabFDDList2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"compressedModeMeasCapabFDDList"
		},
	{ ATF_POINTER, 3, offsetof(struct MeasurementCapabilityExt2, compressedModeMeasCapabTDDList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CompressedModeMeasCapabTDDList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"compressedModeMeasCapabTDDList"
		},
	{ ATF_POINTER, 2, offsetof(struct MeasurementCapabilityExt2, compressedModeMeasCapabGSMList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CompressedModeMeasCapabGSMList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"compressedModeMeasCapabGSMList"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasurementCapabilityExt2, compressedModeMeasCapabMC),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CompressedModeMeasCapabMC,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"compressedModeMeasCapabMC"
		},
};
static int asn_MAP_MeasurementCapabilityExt2_oms_1[] = { 1, 2, 3 };
static ber_tlv_tag_t asn_DEF_MeasurementCapabilityExt2_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_MeasurementCapabilityExt2_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* compressedModeMeasCapabFDDList at 11939 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* compressedModeMeasCapabTDDList at 11940 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* compressedModeMeasCapabGSMList at 11941 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* compressedModeMeasCapabMC at 11942 */
};
static asn_SEQUENCE_specifics_t asn_SPC_MeasurementCapabilityExt2_specs_1 = {
	sizeof(struct MeasurementCapabilityExt2),
	offsetof(struct MeasurementCapabilityExt2, _asn_ctx),
	asn_MAP_MeasurementCapabilityExt2_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_MeasurementCapabilityExt2_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_MeasurementCapabilityExt2 = {
	"MeasurementCapabilityExt2",
	"MeasurementCapabilityExt2",
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
	asn_DEF_MeasurementCapabilityExt2_tags_1,
	sizeof(asn_DEF_MeasurementCapabilityExt2_tags_1)
		/sizeof(asn_DEF_MeasurementCapabilityExt2_tags_1[0]), /* 1 */
	asn_DEF_MeasurementCapabilityExt2_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasurementCapabilityExt2_tags_1)
		/sizeof(asn_DEF_MeasurementCapabilityExt2_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_MeasurementCapabilityExt2_1,
	4,	/* Elements count */
	&asn_SPC_MeasurementCapabilityExt2_specs_1	/* Additional specs */
};

