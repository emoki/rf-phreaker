/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/CPCH-SetInfo.h"

static asn_TYPE_member_t asn_MBR_CPCH_SetInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, cpch_SetID),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CPCH_SetID,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cpch-SetID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, transportFormatSet),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_TransportFormatSet,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"transportFormatSet"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, tfcs),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_TFCS,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tfcs"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, ap_PreambleScramblingCode),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AP_PreambleScramblingCode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ap-PreambleScramblingCode"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, ap_AICH_ChannelisationCode),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AP_AICH_ChannelisationCode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ap-AICH-ChannelisationCode"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, cd_PreambleScramblingCode),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CD_PreambleScramblingCode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cd-PreambleScramblingCode"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, cd_CA_ICH_ChannelisationCode),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CD_CA_ICH_ChannelisationCode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cd-CA-ICH-ChannelisationCode"
		},
	{ ATF_POINTER, 2, offsetof(struct CPCH_SetInfo, cd_AccessSlotSubchannelList),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CD_AccessSlotSubchannelList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cd-AccessSlotSubchannelList"
		},
	{ ATF_POINTER, 1, offsetof(struct CPCH_SetInfo, cd_SignatureCodeList),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CD_SignatureCodeList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cd-SignatureCodeList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, deltaPp_m),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DeltaPp_m,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"deltaPp-m"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, ul_DPCCH_SlotFormat),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UL_DPCCH_SlotFormat,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-DPCCH-SlotFormat"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, n_StartMessage),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_N_StartMessage,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"n-StartMessage"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, n_EOT),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_N_EOT,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"n-EOT"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, channelAssignmentActive),
		(ASN_TAG_CLASS_CONTEXT | (13 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ChannelAssignmentActive,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"channelAssignmentActive"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, cpch_StatusIndicationMode),
		(ASN_TAG_CLASS_CONTEXT | (14 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CPCH_StatusIndicationMode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cpch-StatusIndicationMode"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CPCH_SetInfo, pcpch_ChannelInfoList),
		(ASN_TAG_CLASS_CONTEXT | (15 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PCPCH_ChannelInfoList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pcpch-ChannelInfoList"
		},
};
static int asn_MAP_CPCH_SetInfo_oms_1[] = { 7, 8 };
static ber_tlv_tag_t asn_DEF_CPCH_SetInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_CPCH_SetInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* cpch-SetID at 16418 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* transportFormatSet at 16419 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* tfcs at 16420 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* ap-PreambleScramblingCode at 16421 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* ap-AICH-ChannelisationCode at 16422 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* cd-PreambleScramblingCode at 16423 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* cd-CA-ICH-ChannelisationCode at 16424 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* cd-AccessSlotSubchannelList at 16425 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* cd-SignatureCodeList at 16426 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* deltaPp-m at 16427 */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* ul-DPCCH-SlotFormat at 16428 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* n-StartMessage at 16429 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 }, /* n-EOT at 16430 */
    { (ASN_TAG_CLASS_CONTEXT | (13 << 2)), 13, 0, 0 }, /* channelAssignmentActive at 16433 */
    { (ASN_TAG_CLASS_CONTEXT | (14 << 2)), 14, 0, 0 }, /* cpch-StatusIndicationMode at 16434 */
    { (ASN_TAG_CLASS_CONTEXT | (15 << 2)), 15, 0, 0 } /* pcpch-ChannelInfoList at 16436 */
};
static asn_SEQUENCE_specifics_t asn_SPC_CPCH_SetInfo_specs_1 = {
	sizeof(struct CPCH_SetInfo),
	offsetof(struct CPCH_SetInfo, _asn_ctx),
	asn_MAP_CPCH_SetInfo_tag2el_1,
	16,	/* Count of tags in the map */
	asn_MAP_CPCH_SetInfo_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_CPCH_SetInfo = {
	"CPCH-SetInfo",
	"CPCH-SetInfo",
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
	asn_DEF_CPCH_SetInfo_tags_1,
	sizeof(asn_DEF_CPCH_SetInfo_tags_1)
		/sizeof(asn_DEF_CPCH_SetInfo_tags_1[0]), /* 1 */
	asn_DEF_CPCH_SetInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_CPCH_SetInfo_tags_1)
		/sizeof(asn_DEF_CPCH_SetInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CPCH_SetInfo_1,
	16,	/* Elements count */
	&asn_SPC_CPCH_SetInfo_specs_1	/* Additional specs */
};

