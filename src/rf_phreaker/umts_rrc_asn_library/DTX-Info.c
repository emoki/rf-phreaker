/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/DTX-Info.h"

static int
memb_ue_dtx_cycle2DefaultSG_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 38)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_e_dch_TTI_Length_constr_2 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_ue_dtx_cycle2DefaultSG_constr_6 = {
	{ APC_CONSTRAINED,	 6,  6,  0,  38 }	/* (0..38) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_e_dch_TTI_Length_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info__e_dch_TTI_Length, choice.dtx_e_dch_TTI_10ms),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DTX_E_DCH_TTI_10ms,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dtx-e-dch-TTI-10ms"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info__e_dch_TTI_Length, choice.dtx_e_dch_TTI_2ms),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DTX_E_DCH_TTI_2ms,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dtx-e-dch-TTI-2ms"
		},
};
static asn_TYPE_tag2member_t asn_MAP_e_dch_TTI_Length_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* dtx-e-dch-TTI-10ms at 17704 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* dtx-e-dch-TTI-2ms at 17706 */
};
static asn_CHOICE_specifics_t asn_SPC_e_dch_TTI_Length_specs_2 = {
	sizeof(struct DTX_Info__e_dch_TTI_Length),
	offsetof(struct DTX_Info__e_dch_TTI_Length, _asn_ctx),
	offsetof(struct DTX_Info__e_dch_TTI_Length, present),
	sizeof(((struct DTX_Info__e_dch_TTI_Length *)0)->present),
	asn_MAP_e_dch_TTI_Length_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_e_dch_TTI_Length_2 = {
	"e-dch-TTI-Length",
	"e-dch-TTI-Length",
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
	&asn_PER_type_e_dch_TTI_Length_constr_2,
	asn_MBR_e_dch_TTI_Length_2,
	2,	/* Elements count */
	&asn_SPC_e_dch_TTI_Length_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_DTX_Info_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info, e_dch_TTI_Length),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_e_dch_TTI_Length_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"e-dch-TTI-Length"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info, ue_dtx_cycle2InactivityThreshold),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_DTX_Cycle2InactivityThreshold,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-dtx-cycle2InactivityThreshold"
		},
	{ ATF_POINTER, 2, offsetof(struct DTX_Info, ue_dtx_cycle2DefaultSG),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_ue_dtx_cycle2DefaultSG_constraint_1,
		&asn_PER_memb_ue_dtx_cycle2DefaultSG_constr_6,
		0,
		"ue-dtx-cycle2DefaultSG"
		},
	{ ATF_POINTER, 1, offsetof(struct DTX_Info, ue_dtx_long_preamble_length),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_DTX_long_preamble_length,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-dtx-long-preamble-length"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info, mac_InactivityThreshold),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MAC_InactivityThreshold,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mac-InactivityThreshold"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info, cqi_dtx_Timer),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CQI_DTX_Timer,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cqi-dtx-Timer"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info, ue_dpcch_Burst1),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_DPCCH_Burst,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-dpcch-Burst1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTX_Info, ue_dpcch_Burst2),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_DPCCH_Burst,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-dpcch-Burst2"
		},
};
static int asn_MAP_DTX_Info_oms_1[] = { 2, 3 };
static ber_tlv_tag_t asn_DEF_DTX_Info_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_DTX_Info_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* e-dch-TTI-Length at 17704 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ue-dtx-cycle2InactivityThreshold at 17707 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* ue-dtx-cycle2DefaultSG at 17708 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* ue-dtx-long-preamble-length at 17710 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* mac-InactivityThreshold at 17711 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* cqi-dtx-Timer at 17712 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* ue-dpcch-Burst1 at 17713 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* ue-dpcch-Burst2 at 17715 */
};
static asn_SEQUENCE_specifics_t asn_SPC_DTX_Info_specs_1 = {
	sizeof(struct DTX_Info),
	offsetof(struct DTX_Info, _asn_ctx),
	asn_MAP_DTX_Info_tag2el_1,
	8,	/* Count of tags in the map */
	asn_MAP_DTX_Info_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_DTX_Info = {
	"DTX-Info",
	"DTX-Info",
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
	asn_DEF_DTX_Info_tags_1,
	sizeof(asn_DEF_DTX_Info_tags_1)
		/sizeof(asn_DEF_DTX_Info_tags_1[0]), /* 1 */
	asn_DEF_DTX_Info_tags_1,	/* Same as above */
	sizeof(asn_DEF_DTX_Info_tags_1)
		/sizeof(asn_DEF_DTX_Info_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_DTX_Info_1,
	8,	/* Elements count */
	&asn_SPC_DTX_Info_specs_1	/* Additional specs */
};

