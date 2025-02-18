/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/ReplacedPDSCH-CodeInfo.h"

static asn_TYPE_member_t asn_MBR_ReplacedPDSCH_CodeInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReplacedPDSCH_CodeInfo, tfci_Field2),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MaxTFCI_Field2Value,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tfci-Field2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReplacedPDSCH_CodeInfo, spreadingFactor),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SF_PDSCH,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"spreadingFactor"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReplacedPDSCH_CodeInfo, codeNumber),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CodeNumberDSCH,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"codeNumber"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReplacedPDSCH_CodeInfo, multiCodeInfo),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MultiCodeInfo,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"multiCodeInfo"
		},
};
static ber_tlv_tag_t asn_DEF_ReplacedPDSCH_CodeInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_ReplacedPDSCH_CodeInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tfci-Field2 at 20224 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* spreadingFactor at 20225 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* codeNumber at 20226 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* multiCodeInfo at 20228 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ReplacedPDSCH_CodeInfo_specs_1 = {
	sizeof(struct ReplacedPDSCH_CodeInfo),
	offsetof(struct ReplacedPDSCH_CodeInfo, _asn_ctx),
	asn_MAP_ReplacedPDSCH_CodeInfo_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_ReplacedPDSCH_CodeInfo = {
	"ReplacedPDSCH-CodeInfo",
	"ReplacedPDSCH-CodeInfo",
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
	asn_DEF_ReplacedPDSCH_CodeInfo_tags_1,
	sizeof(asn_DEF_ReplacedPDSCH_CodeInfo_tags_1)
		/sizeof(asn_DEF_ReplacedPDSCH_CodeInfo_tags_1[0]), /* 1 */
	asn_DEF_ReplacedPDSCH_CodeInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_ReplacedPDSCH_CodeInfo_tags_1)
		/sizeof(asn_DEF_ReplacedPDSCH_CodeInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_ReplacedPDSCH_CodeInfo_1,
	4,	/* Elements count */
	&asn_SPC_ReplacedPDSCH_CodeInfo_specs_1	/* Additional specs */
};

