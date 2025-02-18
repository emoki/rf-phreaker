/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UTRAN-DRX-CycleLengthCoefficient-r7.h"

static int
memb_drx_CycleLengthCoefficient_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 3 && value <= 9)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_drx_CycleLengthCoefficient2_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 3 && value <= 9)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_drx_CycleLengthCoefficient_constr_2 = {
	{ APC_CONSTRAINED,	 3,  3,  3,  9 }	/* (3..9) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_drx_CycleLengthCoefficient2_constr_3 = {
	{ APC_CONSTRAINED,	 3,  3,  3,  9 }	/* (3..9) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_UTRAN_DRX_CycleLengthCoefficient_r7_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UTRAN_DRX_CycleLengthCoefficient_r7, drx_CycleLengthCoefficient),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_drx_CycleLengthCoefficient_constraint_1,
		&asn_PER_memb_drx_CycleLengthCoefficient_constr_2,
		0,
		"drx-CycleLengthCoefficient"
		},
	{ ATF_POINTER, 2, offsetof(struct UTRAN_DRX_CycleLengthCoefficient_r7, drx_CycleLengthCoefficient2),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_drx_CycleLengthCoefficient2_constraint_1,
		&asn_PER_memb_drx_CycleLengthCoefficient2_constr_3,
		0,
		"drx-CycleLengthCoefficient2"
		},
	{ ATF_POINTER, 1, offsetof(struct UTRAN_DRX_CycleLengthCoefficient_r7, timeForDRXCycle2),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_T_319,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timeForDRXCycle2"
		},
};
static int asn_MAP_UTRAN_DRX_CycleLengthCoefficient_r7_oms_1[] = { 1, 2 };
static ber_tlv_tag_t asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UTRAN_DRX_CycleLengthCoefficient_r7_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* drx-CycleLengthCoefficient at 13607 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* drx-CycleLengthCoefficient2 at 13608 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* timeForDRXCycle2 at 13609 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UTRAN_DRX_CycleLengthCoefficient_r7_specs_1 = {
	sizeof(struct UTRAN_DRX_CycleLengthCoefficient_r7),
	offsetof(struct UTRAN_DRX_CycleLengthCoefficient_r7, _asn_ctx),
	asn_MAP_UTRAN_DRX_CycleLengthCoefficient_r7_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_UTRAN_DRX_CycleLengthCoefficient_r7_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7 = {
	"UTRAN-DRX-CycleLengthCoefficient-r7",
	"UTRAN-DRX-CycleLengthCoefficient-r7",
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
	asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7_tags_1,
	sizeof(asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7_tags_1)
		/sizeof(asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7_tags_1[0]), /* 1 */
	asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7_tags_1,	/* Same as above */
	sizeof(asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7_tags_1)
		/sizeof(asn_DEF_UTRAN_DRX_CycleLengthCoefficient_r7_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UTRAN_DRX_CycleLengthCoefficient_r7_1,
	3,	/* Elements count */
	&asn_SPC_UTRAN_DRX_CycleLengthCoefficient_r7_specs_1	/* Additional specs */
};

