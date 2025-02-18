/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/PUSCH-SysInfo.h"

static asn_TYPE_member_t asn_MBR_PUSCH_SysInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PUSCH_SysInfo, pusch_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PUSCH_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pusch-Identity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PUSCH_SysInfo, pusch_Info),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PUSCH_Info,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pusch-Info"
		},
	{ ATF_POINTER, 2, offsetof(struct PUSCH_SysInfo, usch_TFS),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_TransportFormatSet,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"usch-TFS"
		},
	{ ATF_POINTER, 1, offsetof(struct PUSCH_SysInfo, usch_TFCS),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_TFCS,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"usch-TFCS"
		},
};
static int asn_MAP_PUSCH_SysInfo_oms_1[] = { 2, 3 };
static ber_tlv_tag_t asn_DEF_PUSCH_SysInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_PUSCH_SysInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pusch-Identity at 20097 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* pusch-Info at 20098 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* usch-TFS at 20099 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* usch-TFCS at 20100 */
};
static asn_SEQUENCE_specifics_t asn_SPC_PUSCH_SysInfo_specs_1 = {
	sizeof(struct PUSCH_SysInfo),
	offsetof(struct PUSCH_SysInfo, _asn_ctx),
	asn_MAP_PUSCH_SysInfo_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_PUSCH_SysInfo_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_PUSCH_SysInfo = {
	"PUSCH-SysInfo",
	"PUSCH-SysInfo",
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
	asn_DEF_PUSCH_SysInfo_tags_1,
	sizeof(asn_DEF_PUSCH_SysInfo_tags_1)
		/sizeof(asn_DEF_PUSCH_SysInfo_tags_1[0]), /* 1 */
	asn_DEF_PUSCH_SysInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_PUSCH_SysInfo_tags_1)
		/sizeof(asn_DEF_PUSCH_SysInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_PUSCH_SysInfo_1,
	4,	/* Elements count */
	&asn_SPC_PUSCH_SysInfo_specs_1	/* Additional specs */
};

