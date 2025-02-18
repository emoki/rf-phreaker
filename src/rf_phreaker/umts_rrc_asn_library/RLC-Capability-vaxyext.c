/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/RLC-Capability-vaxyext.h"

static asn_TYPE_member_t asn_MBR_RLC_Capability_vaxyext_1[] = {
	{ ATF_POINTER, 1, offsetof(struct RLC_Capability_vaxyext, totalRLC_AM_BufferSize),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TotalRLC_AM_BufferSize_vaxyext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"totalRLC-AM-BufferSize"
		},
};
static int asn_MAP_RLC_Capability_vaxyext_oms_1[] = { 0 };
static ber_tlv_tag_t asn_DEF_RLC_Capability_vaxyext_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_RLC_Capability_vaxyext_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* totalRLC-AM-BufferSize at 12501 */
};
static asn_SEQUENCE_specifics_t asn_SPC_RLC_Capability_vaxyext_specs_1 = {
	sizeof(struct RLC_Capability_vaxyext),
	offsetof(struct RLC_Capability_vaxyext, _asn_ctx),
	asn_MAP_RLC_Capability_vaxyext_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_RLC_Capability_vaxyext_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_RLC_Capability_vaxyext = {
	"RLC-Capability-vaxyext",
	"RLC-Capability-vaxyext",
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
	asn_DEF_RLC_Capability_vaxyext_tags_1,
	sizeof(asn_DEF_RLC_Capability_vaxyext_tags_1)
		/sizeof(asn_DEF_RLC_Capability_vaxyext_tags_1[0]), /* 1 */
	asn_DEF_RLC_Capability_vaxyext_tags_1,	/* Same as above */
	sizeof(asn_DEF_RLC_Capability_vaxyext_tags_1)
		/sizeof(asn_DEF_RLC_Capability_vaxyext_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_RLC_Capability_vaxyext_1,
	1,	/* Elements count */
	&asn_SPC_RLC_Capability_vaxyext_specs_1	/* Additional specs */
};

