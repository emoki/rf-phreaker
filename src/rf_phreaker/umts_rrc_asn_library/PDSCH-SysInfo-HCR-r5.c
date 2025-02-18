/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/PDSCH-SysInfo-HCR-r5.h"

static asn_TYPE_member_t asn_MBR_PDSCH_SysInfo_HCR_r5_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PDSCH_SysInfo_HCR_r5, pdsch_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PDSCH_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pdsch-Identity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PDSCH_SysInfo_HCR_r5, pdsch_Info),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PDSCH_Info,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pdsch-Info"
		},
	{ ATF_POINTER, 2, offsetof(struct PDSCH_SysInfo_HCR_r5, dsch_TransportChannelsInfo),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DSCH_TransportChannelsInfo,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dsch-TransportChannelsInfo"
		},
	{ ATF_POINTER, 1, offsetof(struct PDSCH_SysInfo_HCR_r5, dsch_TFCS),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_TFCS,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dsch-TFCS"
		},
};
static int asn_MAP_PDSCH_SysInfo_HCR_r5_oms_1[] = { 2, 3 };
static ber_tlv_tag_t asn_DEF_PDSCH_SysInfo_HCR_r5_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_PDSCH_SysInfo_HCR_r5_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pdsch-Identity at 19578 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* pdsch-Info at 19579 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* dsch-TransportChannelsInfo at 19580 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* dsch-TFCS at 19581 */
};
static asn_SEQUENCE_specifics_t asn_SPC_PDSCH_SysInfo_HCR_r5_specs_1 = {
	sizeof(struct PDSCH_SysInfo_HCR_r5),
	offsetof(struct PDSCH_SysInfo_HCR_r5, _asn_ctx),
	asn_MAP_PDSCH_SysInfo_HCR_r5_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_PDSCH_SysInfo_HCR_r5_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_PDSCH_SysInfo_HCR_r5 = {
	"PDSCH-SysInfo-HCR-r5",
	"PDSCH-SysInfo-HCR-r5",
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
	asn_DEF_PDSCH_SysInfo_HCR_r5_tags_1,
	sizeof(asn_DEF_PDSCH_SysInfo_HCR_r5_tags_1)
		/sizeof(asn_DEF_PDSCH_SysInfo_HCR_r5_tags_1[0]), /* 1 */
	asn_DEF_PDSCH_SysInfo_HCR_r5_tags_1,	/* Same as above */
	sizeof(asn_DEF_PDSCH_SysInfo_HCR_r5_tags_1)
		/sizeof(asn_DEF_PDSCH_SysInfo_HCR_r5_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_PDSCH_SysInfo_HCR_r5_1,
	4,	/* Elements count */
	&asn_SPC_PDSCH_SysInfo_HCR_r5_specs_1	/* Additional specs */
};

