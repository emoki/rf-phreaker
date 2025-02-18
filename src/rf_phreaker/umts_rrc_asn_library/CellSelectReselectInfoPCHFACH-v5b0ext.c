/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/CellSelectReselectInfoPCHFACH-v5b0ext.h"

static asn_TYPE_member_t asn_MBR_CellSelectReselectInfoPCHFACH_v5b0ext_1[] = {
	{ ATF_POINTER, 6, offsetof(struct CellSelectReselectInfoPCHFACH_v5b0ext, q_Hyst_l_S_PCH),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Q_Hyst_S_Fine,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"q-Hyst-l-S-PCH"
		},
	{ ATF_POINTER, 5, offsetof(struct CellSelectReselectInfoPCHFACH_v5b0ext, q_Hyst_l_S_FACH),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Q_Hyst_S_Fine,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"q-Hyst-l-S-FACH"
		},
	{ ATF_POINTER, 4, offsetof(struct CellSelectReselectInfoPCHFACH_v5b0ext, q_Hyst_2_S_PCH),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Q_Hyst_S_Fine,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"q-Hyst-2-S-PCH"
		},
	{ ATF_POINTER, 3, offsetof(struct CellSelectReselectInfoPCHFACH_v5b0ext, q_Hyst_2_S_FACH),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Q_Hyst_S_Fine,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"q-Hyst-2-S-FACH"
		},
	{ ATF_POINTER, 2, offsetof(struct CellSelectReselectInfoPCHFACH_v5b0ext, t_Reselection_S_PCH),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_T_Reselection_S,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"t-Reselection-S-PCH"
		},
	{ ATF_POINTER, 1, offsetof(struct CellSelectReselectInfoPCHFACH_v5b0ext, t_Reselection_S_FACH),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_T_Reselection_S_Fine,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"t-Reselection-S-FACH"
		},
};
static int asn_MAP_CellSelectReselectInfoPCHFACH_v5b0ext_oms_1[] = { 0, 1, 2, 3, 4, 5 };
static ber_tlv_tag_t asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_CellSelectReselectInfoPCHFACH_v5b0ext_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* q-Hyst-l-S-PCH at 22727 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* q-Hyst-l-S-FACH at 22728 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* q-Hyst-2-S-PCH at 22729 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* q-Hyst-2-S-FACH at 22730 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* t-Reselection-S-PCH at 22731 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* t-Reselection-S-FACH at 22732 */
};
static asn_SEQUENCE_specifics_t asn_SPC_CellSelectReselectInfoPCHFACH_v5b0ext_specs_1 = {
	sizeof(struct CellSelectReselectInfoPCHFACH_v5b0ext),
	offsetof(struct CellSelectReselectInfoPCHFACH_v5b0ext, _asn_ctx),
	asn_MAP_CellSelectReselectInfoPCHFACH_v5b0ext_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_CellSelectReselectInfoPCHFACH_v5b0ext_oms_1,	/* Optional members */
	6, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext = {
	"CellSelectReselectInfoPCHFACH-v5b0ext",
	"CellSelectReselectInfoPCHFACH-v5b0ext",
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
	asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext_tags_1,
	sizeof(asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext_tags_1)
		/sizeof(asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext_tags_1[0]), /* 1 */
	asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext_tags_1,	/* Same as above */
	sizeof(asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext_tags_1)
		/sizeof(asn_DEF_CellSelectReselectInfoPCHFACH_v5b0ext_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CellSelectReselectInfoPCHFACH_v5b0ext_1,
	6,	/* Elements count */
	&asn_SPC_CellSelectReselectInfoPCHFACH_v5b0ext_specs_1	/* Additional specs */
};

