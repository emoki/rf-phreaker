/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/InterFreqCellInfoSI-List-RSCP-LCR.h"

static asn_TYPE_member_t asn_MBR_InterFreqCellInfoSI_List_RSCP_LCR_1[] = {
	{ ATF_POINTER, 2, offsetof(struct InterFreqCellInfoSI_List_RSCP_LCR, removedInterFreqCellList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_RemovedInterFreqCellList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"removedInterFreqCellList"
		},
	{ ATF_POINTER, 1, offsetof(struct InterFreqCellInfoSI_List_RSCP_LCR, newInterFreqCellList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NewInterFreqCellSI_List_RSCP_LCR_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"newInterFreqCellList"
		},
};
static int asn_MAP_InterFreqCellInfoSI_List_RSCP_LCR_oms_1[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_InterFreqCellInfoSI_List_RSCP_LCR_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* removedInterFreqCellList at 24190 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* newInterFreqCellList at 24191 */
};
static asn_SEQUENCE_specifics_t asn_SPC_InterFreqCellInfoSI_List_RSCP_LCR_specs_1 = {
	sizeof(struct InterFreqCellInfoSI_List_RSCP_LCR),
	offsetof(struct InterFreqCellInfoSI_List_RSCP_LCR, _asn_ctx),
	asn_MAP_InterFreqCellInfoSI_List_RSCP_LCR_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_InterFreqCellInfoSI_List_RSCP_LCR_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR = {
	"InterFreqCellInfoSI-List-RSCP-LCR",
	"InterFreqCellInfoSI-List-RSCP-LCR",
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
	asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR_tags_1,
	sizeof(asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR_tags_1)
		/sizeof(asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR_tags_1[0]), /* 1 */
	asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR_tags_1,	/* Same as above */
	sizeof(asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR_tags_1)
		/sizeof(asn_DEF_InterFreqCellInfoSI_List_RSCP_LCR_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_InterFreqCellInfoSI_List_RSCP_LCR_1,
	2,	/* Elements count */
	&asn_SPC_InterFreqCellInfoSI_List_RSCP_LCR_specs_1	/* Additional specs */
};

