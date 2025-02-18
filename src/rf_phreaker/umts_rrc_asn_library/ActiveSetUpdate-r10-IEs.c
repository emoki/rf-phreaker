/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/ActiveSetUpdate-r10-IEs.h"

static asn_TYPE_member_t asn_MBR_ActiveSetUpdate_r10_IEs_1[] = {
	{ ATF_POINTER, 28, offsetof(struct ActiveSetUpdate_r10_IEs, activationTime),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ActivationTime,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"activationTime"
		},
	{ ATF_POINTER, 27, offsetof(struct ActiveSetUpdate_r10_IEs, newU_RNTI),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_U_RNTI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"newU-RNTI"
		},
	{ ATF_POINTER, 26, offsetof(struct ActiveSetUpdate_r10_IEs, newH_RNTI),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_H_RNTI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"newH-RNTI"
		},
	{ ATF_POINTER, 25, offsetof(struct ActiveSetUpdate_r10_IEs, newPrimary_E_RNTI),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_RNTI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"newPrimary-E-RNTI"
		},
	{ ATF_POINTER, 24, offsetof(struct ActiveSetUpdate_r10_IEs, newSecondary_E_RNTI),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_RNTI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"newSecondary-E-RNTI"
		},
	{ ATF_POINTER, 23, offsetof(struct ActiveSetUpdate_r10_IEs, cn_InformationInfo),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CN_InformationInfo_r6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cn-InformationInfo"
		},
	{ ATF_POINTER, 22, offsetof(struct ActiveSetUpdate_r10_IEs, dtx_drx_TimingInfo),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DTX_DRX_TimingInfo_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dtx-drx-TimingInfo"
		},
	{ ATF_POINTER, 21, offsetof(struct ActiveSetUpdate_r10_IEs, dtx_drx_Info),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DTX_DRX_Info_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dtx-drx-Info"
		},
	{ ATF_POINTER, 20, offsetof(struct ActiveSetUpdate_r10_IEs, hs_scch_LessInfo),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HS_SCCH_LessInfo_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"hs-scch-LessInfo"
		},
	{ ATF_POINTER, 19, offsetof(struct ActiveSetUpdate_r10_IEs, mimoParameters),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MIMO_Parameters_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mimoParameters"
		},
	{ ATF_POINTER, 18, offsetof(struct ActiveSetUpdate_r10_IEs, maxAllowedUL_TX_Power),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MaxAllowedUL_TX_Power,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"maxAllowedUL-TX-Power"
		},
	{ ATF_POINTER, 17, offsetof(struct ActiveSetUpdate_r10_IEs, ul_SecondaryCellInfoFDD),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_UL_SecondaryCellInfoFDD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-SecondaryCellInfoFDD"
		},
	{ ATF_POINTER, 16, offsetof(struct ActiveSetUpdate_r10_IEs, e_dch_ReconfigurationInfo_SecULFrequency),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_DCH_ReconfigurationInfo_SecULFrequency,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"e-dch-ReconfigurationInfo-SecULFrequency"
		},
	{ ATF_POINTER, 15, offsetof(struct ActiveSetUpdate_r10_IEs, rl_AdditionInformationList),
		(ASN_TAG_CLASS_CONTEXT | (13 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RL_AdditionInformationList_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rl-AdditionInformationList"
		},
	{ ATF_POINTER, 14, offsetof(struct ActiveSetUpdate_r10_IEs, rl_AdditionInformationList_SecULFreq),
		(ASN_TAG_CLASS_CONTEXT | (14 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RL_AdditionInformationList_SecULFreq,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rl-AdditionInformationList-SecULFreq"
		},
	{ ATF_POINTER, 13, offsetof(struct ActiveSetUpdate_r10_IEs, servingCellChangeParameters),
		(ASN_TAG_CLASS_CONTEXT | (15 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ServingCellChangeParameters,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"servingCellChangeParameters"
		},
	{ ATF_POINTER, 12, offsetof(struct ActiveSetUpdate_r10_IEs, rl_RemovalInformationList),
		(ASN_TAG_CLASS_CONTEXT | (16 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RL_RemovalInformationList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rl-RemovalInformationList"
		},
	{ ATF_POINTER, 11, offsetof(struct ActiveSetUpdate_r10_IEs, rl_RemovalInformationList_SecULFreq),
		(ASN_TAG_CLASS_CONTEXT | (17 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RL_RemovalInformationList_SecULFreq,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rl-RemovalInformationList-SecULFreq"
		},
	{ ATF_POINTER, 10, offsetof(struct ActiveSetUpdate_r10_IEs, tx_DiversityMode),
		(ASN_TAG_CLASS_CONTEXT | (18 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TX_DiversityMode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tx-DiversityMode"
		},
	{ ATF_POINTER, 9, offsetof(struct ActiveSetUpdate_r10_IEs, dpc_Mode),
		(ASN_TAG_CLASS_CONTEXT | (19 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DPC_Mode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dpc-Mode"
		},
	{ ATF_POINTER, 8, offsetof(struct ActiveSetUpdate_r10_IEs, serving_HSDSCH_CellInformation),
		(ASN_TAG_CLASS_CONTEXT | (20 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Serving_HSDSCH_CellInformation_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"serving-HSDSCH-CellInformation"
		},
	{ ATF_POINTER, 7, offsetof(struct ActiveSetUpdate_r10_IEs, e_dch_ReconfigurationInfo),
		(ASN_TAG_CLASS_CONTEXT | (21 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_DCH_ReconfigurationInfo_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"e-dch-ReconfigurationInfo"
		},
	{ ATF_POINTER, 6, offsetof(struct ActiveSetUpdate_r10_IEs, ul_16QAM_Config),
		(ASN_TAG_CLASS_CONTEXT | (22 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UL_16QAM_Config,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-16QAM-Config"
		},
	{ ATF_POINTER, 5, offsetof(struct ActiveSetUpdate_r10_IEs, e_dch_ReconfInfoSameCell),
		(ASN_TAG_CLASS_CONTEXT | (23 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_DCH_RL_InfoSameServingCell,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"e-dch-ReconfInfoSameCell"
		},
	{ ATF_POINTER, 4, offsetof(struct ActiveSetUpdate_r10_IEs, e_TFC_Boost_Info),
		(ASN_TAG_CLASS_CONTEXT | (24 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_TFC_Boost_Info_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"e-TFC-Boost-Info"
		},
	{ ATF_POINTER, 3, offsetof(struct ActiveSetUpdate_r10_IEs, e_DPDCH_PowerInterpolation),
		(ASN_TAG_CLASS_CONTEXT | (25 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_DPDCH_PowerInterpolation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"e-DPDCH-PowerInterpolation"
		},
	{ ATF_POINTER, 2, offsetof(struct ActiveSetUpdate_r10_IEs, dl_SecondaryCellInfoFDD),
		(ASN_TAG_CLASS_CONTEXT | (26 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DL_SecondaryCellInfoFDD_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dl-SecondaryCellInfoFDD"
		},
	{ ATF_POINTER, 1, offsetof(struct ActiveSetUpdate_r10_IEs, additionalDLSecCellInfoListFDD),
		(ASN_TAG_CLASS_CONTEXT | (27 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AdditionalDLSecCellInfoListFDD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"additionalDLSecCellInfoListFDD"
		},
};
static int asn_MAP_ActiveSetUpdate_r10_IEs_oms_1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 };
static ber_tlv_tag_t asn_DEF_ActiveSetUpdate_r10_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_ActiveSetUpdate_r10_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* activationTime at 1191 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* newU-RNTI at 1192 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* newH-RNTI at 1193 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* newPrimary-E-RNTI at 1194 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* newSecondary-E-RNTI at 1195 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* cn-InformationInfo at 1197 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* dtx-drx-TimingInfo at 1199 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* dtx-drx-Info at 1200 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* hs-scch-LessInfo at 1201 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* mimoParameters at 1202 */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* maxAllowedUL-TX-Power at 1203 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* ul-SecondaryCellInfoFDD at 1204 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 }, /* e-dch-ReconfigurationInfo-SecULFrequency at 1206 */
    { (ASN_TAG_CLASS_CONTEXT | (13 << 2)), 13, 0, 0 }, /* rl-AdditionInformationList at 1207 */
    { (ASN_TAG_CLASS_CONTEXT | (14 << 2)), 14, 0, 0 }, /* rl-AdditionInformationList-SecULFreq at 1209 */
    { (ASN_TAG_CLASS_CONTEXT | (15 << 2)), 15, 0, 0 }, /* servingCellChangeParameters at 1210 */
    { (ASN_TAG_CLASS_CONTEXT | (16 << 2)), 16, 0, 0 }, /* rl-RemovalInformationList at 1211 */
    { (ASN_TAG_CLASS_CONTEXT | (17 << 2)), 17, 0, 0 }, /* rl-RemovalInformationList-SecULFreq at 1213 */
    { (ASN_TAG_CLASS_CONTEXT | (18 << 2)), 18, 0, 0 }, /* tx-DiversityMode at 1214 */
    { (ASN_TAG_CLASS_CONTEXT | (19 << 2)), 19, 0, 0 }, /* dpc-Mode at 1215 */
    { (ASN_TAG_CLASS_CONTEXT | (20 << 2)), 20, 0, 0 }, /* serving-HSDSCH-CellInformation at 1216 */
    { (ASN_TAG_CLASS_CONTEXT | (21 << 2)), 21, 0, 0 }, /* e-dch-ReconfigurationInfo at 1217 */
    { (ASN_TAG_CLASS_CONTEXT | (22 << 2)), 22, 0, 0 }, /* ul-16QAM-Config at 1218 */
    { (ASN_TAG_CLASS_CONTEXT | (23 << 2)), 23, 0, 0 }, /* e-dch-ReconfInfoSameCell at 1219 */
    { (ASN_TAG_CLASS_CONTEXT | (24 << 2)), 24, 0, 0 }, /* e-TFC-Boost-Info at 1220 */
    { (ASN_TAG_CLASS_CONTEXT | (25 << 2)), 25, 0, 0 }, /* e-DPDCH-PowerInterpolation at 1221 */
    { (ASN_TAG_CLASS_CONTEXT | (26 << 2)), 26, 0, 0 }, /* dl-SecondaryCellInfoFDD at 1222 */
    { (ASN_TAG_CLASS_CONTEXT | (27 << 2)), 27, 0, 0 } /* additionalDLSecCellInfoListFDD at 1223 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ActiveSetUpdate_r10_IEs_specs_1 = {
	sizeof(struct ActiveSetUpdate_r10_IEs),
	offsetof(struct ActiveSetUpdate_r10_IEs, _asn_ctx),
	asn_MAP_ActiveSetUpdate_r10_IEs_tag2el_1,
	28,	/* Count of tags in the map */
	asn_MAP_ActiveSetUpdate_r10_IEs_oms_1,	/* Optional members */
	28, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_ActiveSetUpdate_r10_IEs = {
	"ActiveSetUpdate-r10-IEs",
	"ActiveSetUpdate-r10-IEs",
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
	asn_DEF_ActiveSetUpdate_r10_IEs_tags_1,
	sizeof(asn_DEF_ActiveSetUpdate_r10_IEs_tags_1)
		/sizeof(asn_DEF_ActiveSetUpdate_r10_IEs_tags_1[0]), /* 1 */
	asn_DEF_ActiveSetUpdate_r10_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_ActiveSetUpdate_r10_IEs_tags_1)
		/sizeof(asn_DEF_ActiveSetUpdate_r10_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_ActiveSetUpdate_r10_IEs_1,
	28,	/* Elements count */
	&asn_SPC_ActiveSetUpdate_r10_IEs_specs_1	/* Additional specs */
};

